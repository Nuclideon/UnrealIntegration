# udRenderContext

The **udRenderContext** object provides an interface to render Nuclideon Unlimited Detail models. It provides the ability to render by colour, intensity or classification; additionally allowing the user to query a specific pixel for information about the pointcloud data. 

## Enums

### enum udRenderContextPointMode

These are the various point modes available in udSDK 

*Values:*

| Value | Description |
|-------|-------------|
| `udRCPM_Rectangles` | This is the default, renders the voxels expanded as screen space rectangles. |
| `udRCPM_Cubes` | Renders the voxels as cubes. |
| `udRCPM_Points` | Renders voxels as a single point (Note: does not accurately reflect the ‘size’ of voxels). |
| `udRCPM_Count` | Total number of point modes. Used internally but can be used as an iterator max when displaying different point modes. |

### enum udRenderContextFlags

These are the various render flags available in udSDK 

*Values:*

| Value | Description |
|-------|-------------|
| `udRCF_None` | Render the points using the default configuration. |
| `udRCF_PreserveBuffers` | The colour and depth buffers won’t be cleared before drawing and existing depth will be respected. |
| `udRCF_ComplexIntersections` | This flag is required in some scenes where there is a very large amount of intersecting point clouds It will internally batch rendering with the udRCF_PreserveBuffers flag after the first render. |
| `udRCF_BlockingStreaming` | This forces the streamer to load as much of the pointcloud as required to give an accurate representation in the current view. A small amount of further refinement may still occur. |
| `udRCF_LogarithmicDepth` | Calculate the depth as a logarithmic distribution. |
| `udRCF_ManualStreamerUpdate` | The streamer won’t be updated internally but a render call without this flag or a manual streamer update will be required. |
| `udRCF_ZeroAlphaSkip` | If the voxel has 0 alpha (upper 8 bits) after the voxel shader then the voxel will not be drawn to the buffers (effectively skipped). |
| `udRCF_2PixelOpt` | Optimisation that allows the renderer to resolve the last 2 pixels simulataneously, this can result in slight inaccuracies (generally a few pixels) in the final image for a huge performance improvement. |
| `udRCF_DisableOrthographic` | Disables the renderer entering high-performance orthographic mode. |
| `udRCF_NoTraversal` | Skip octree traversal, instead reuse existing data from previous traversal. |
| `udRCF_DisableDrawCallFiltering` | Disables the splitting of blocks into multiple draw calls, when a filter is active. |

## Functions

### enum [udError](udError.md) udRenderContext_Create(struct udContext \*pContext, struct udRenderContext \*\*ppRenderer)

Create an instance of `udRenderContext` for rendering.

> [!NOTE]
> It is not recommended to have more than one instance of udRenderContext.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The context to be used to create the render context. |
| `ppRenderer` | The pointer pointer of the udRenderContext. This will allocate an instance of udRenderContext into `ppRenderer`. |

**Returns:** A [udError](udError.md) value based on the result of the render context creation.

### enum [udError](udError.md) udRenderContext_Destroy(struct udRenderContext \*\*ppRenderer)

Destroy the instance of the renderer.

| Parameter | Description |
|-----------|-------------|
| `ppRenderer` | The pointer pointer of the udRenderContext. This will deallocate the instance of udRenderContext. |

**Returns:** A [udError](udError.md) value based on the result of the render context destruction.

### enum [udError](udError.md) udRenderContext_Render(struct udRenderContext \*pRenderer, struct udRenderTarget \*pRenderView, struct udRenderInstance \*pModels, int modelCount, struct udRenderSettings \*pRenderOptions)

Render the models from the perspective of `pRenderView`.

| Parameter | Description |
|-----------|-------------|
| `pRenderer` | The renderer to render the scene. |
| `pRenderView` | The view to render from with the render buffers associated with it being filled out. |
| `pModels` | The array of models to use in render. |
| `modelCount` | The amount of models in pModels. |
| `pRenderOptions` | Additional render options. |

**Returns:** A [udError](udError.md) value based on the result of the render.


## Structs

### struct udRenderPicking

Stores both the input and output of the udSDK picking system

| Field | Type | Description |
|-------|------|-------------|
| `x` | `unsigned int` | Mouse X position in udRenderTarget space. |
| `y` | `unsigned int` | Mouse Y position in udRenderTarget space. |
| `hit` | `uint32_t` | Not 0 if a voxel was hit by this pick. |
| `isHighestLOD` | `uint32_t` | Not 0 if this voxel that was hit is as precise as possible. |
| `modelIndex` | `unsigned int` | Index of the model in the ppModels list. |
| `pointCenter[3]` | `double` | The center of the hit voxel in world space. |
| `voxelID` | `struct [udVoxelID](udPointCloud.md)` | The ID of the voxel that was hit by the pick; this ID is only valid for a very short period of time- Do any additional work using this ID this frame. |

### struct udRenderSettings

Stores the render settings used per render

| Field | Type | Description |
|-------|------|-------------|
| `flags` | `enum udRenderContextFlags` | Optional flags providing information about how to perform this render. |
| `pPick` | `struct udRenderPicking \*` | Optional This provides information about the voxel under the mouse. |
| `pointMode` | `enum udRenderContextPointMode` | The point mode for this render. |
| `pFilter` | `struct [udGeometry](udGeometry.md) \*` | Optional This filter is applied to all models in the scene. |
| `pointCount` | `uint32_t` | Optional (GPU Renderer) A hint to the renderer at the upper limit of voxels that are to be rendered. |
| `pointThreshold` | `float` | Optional (GPU Renderer) A hint of the minimum size (in screen space) of a voxel that the renderer will produce. |
| `forwardAxis[3]` | `double` | Optional (GPU Renderer) Override the forward axis of this render. |

### struct udRenderInstance

Stores the instance settings of a model to be rendered

| Field | Type | Description |
|-------|------|-------------|
| `pPointCloud` | `struct udPointCloud \*` | This is the point cloud to display. |
| `matrix[16]` | `double` | The world space matrix for this point cloud instance (this does not to be the default matrix) 

> [!NOTE]
> The default matrix for a model can be accessed from the associated [udPointCloudHeader](udPointCloud.md)> |
| `pFilter` | `const struct [udGeometry](udGeometry.md) \*` | Filter to override for this model, this one will be used instead of the global one applied in udRenderSettings. |
| `modelID` | `uint32_t` | (for GPU only) This value is considered as sceneID/objectID as well. |
| `pVoxelUserData)` | `uint32_t (\*pVoxelShader)(struct udPointCloud \*pPointCloud, const struct [udVoxelID](udPointCloud.md) \*pVoxelID, const void \*` | When the renderer goes to select a colour, it calls this function instead. |
| `pVoxelUserData` | `void \*` | If pVoxelShader is set, this parameter is passed to that function. |
| `opacity` | `double` | If this is a value between 0 and 1 this model will be rendered blended with the rest of the scene. If the alpha from pVoxelShader is 0, the alpha provided will be written to the colourBuffer otherwise it will be calculated using this opacity value. |
| `skipRender` | `uint32_t` | If set not 0 the model will not be rendered. |
