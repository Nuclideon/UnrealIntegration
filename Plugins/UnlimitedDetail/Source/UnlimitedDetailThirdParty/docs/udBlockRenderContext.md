# udBlockRenderContext

The **udBlockRenderContext** object provides an interface to render Nuclideon Unlimited Detail models, with callbacks to enable GPU renderering. It provides the ability to render by colour, intensity or classification; additionally allowing the user to query a specific pixel for information about the pointcloud data. 

## Functions

### udDouble3 udBlockRenderVertexData_GetFloatPosition(const struct udBlockRenderVertexData \*pData, uint32_t index)

Retrieves a voxel position in model space.

| Parameter | Description |
|-----------|-------------|
| `pData` | The block vertex data to query. |
| `index` | The voxel index. |

**Returns:** The voxel position in model space

### enum [udError](udError.md) udBlockRenderContext_Init(struct udBlockRenderGPUInterface \*pGPUInterface)

Create an instance of `udBlockRenderContext` for rendering.

| Parameter | Description |
|-----------|-------------|
| `pGPUInterface` | The pointer of the user-defined callbacks interface. |

**Returns:** A [udError](udError.md) value based on the result of the render context creation.

### enum [udError](udError.md) udBlockRenderContext_Deinit()

Destroy the instance of the renderer.

| Parameter | Description |
|-----------|-------------|
| `ppRenderer` | The pointer pointer of the udRenderContext. This will deallocate the instance of udRenderContext. |

**Returns:** A [udError](udError.md) value based on the result of the render context destruction.

### enum [udError](udError.md) udBlockRenderContext_Render(struct udRenderContext \*pRenderer, struct udRenderTarget \*pRenderView, struct [udRenderInstance](udRenderContext.md) \*pModels, int modelCount, struct [udRenderSettings](udRenderContext.md) \*pRenderOptions)

Render the models from the perspective of `pRenderView`.

| Parameter | Description |
|-----------|-------------|
| `pRenderer` | The renderer to render the scene. |
| `pRenderView` | The view to render from with the render buffers associated with it being filled out. |
| `pModels` | The array of models to use in render. |
| `modelCount` | The amount of models in pModels. |
| `pRenderOptions` | Additional render options. |

**Returns:** A [udError](udError.md) value based on the result of the render.

### uint32_t udRenderContext_GetModelId(const struct udBlockRenderModel \*pBlockRenderModel)

Get the unique user-defined id of the supplied model.

| Parameter | Description |
|-----------|-------------|
| `pBlockRenderModel` | The model whose id will be returned |

**Returns:** The unique id of the model.

### uint32_t udRenderContext_GetVoxelShader(const struct udBlockRenderModel \*pBlockRenderModel)

Get the voxel shader function pointer

| Parameter | Description |
|-----------|-------------|
| `pBlockRenderModel` | The model whose voxel shader function will be returned |

**Returns:** The voxel shader function of the model.

### enum [udError](udError.md) udRenderContext_LockBlock(void \*pBlock)

Locks an Unlimited Detail block, preventing it from being freed by the streamer.

| Parameter | Description |
|-----------|-------------|
| `pBlock` | A pointer to an internal Unlimited Detail block. |

**Returns:** A [udError](udError.md) value indicating the result of the lock update.

### enum [udError](udError.md) udRenderContext_UnlockBlock(void \*pBlock)

Unlocks an Unlimited Detail block, allowing the streamer to free it.

| Parameter | Description |
|-----------|-------------|
| `pBlock` | A pointer to an internal Unlimited Detail block. |

**Returns:** A [udError](udError.md) value indicating the result of the lock update.


## Structs

### struct udBlockRenderDrawList

Passed by the block renderer to the implementation to define what parts of the block need to be rendered

| Field | Type | Description |
|-------|------|-------------|
| `crc` | `uint32_t` | A crc representing inputs to the drawlist (eg listMask or geometry), allowing callers to cache if necessary. |
| `listMask` | `uint16_t` | When non-zero, the divisions the mask used to create the drawlist (with adjacent divisions merged), zero indicates non-merged/filtered list. |
| `drawCount` | `uint16_t` | Number of drawcalls to complete this block. |
| `draws[1]` | `struct udBlockRenderDrawList::DrawCall` |  |

### struct DrawCall

Stores the internal state of the draw call

| Field | Type | Description |
|-------|------|-------------|
| `start` | `uint16_t` | Starting index in the vertex buffer. |
| `count` | `uint16_t` | Number of points for this call. |
| `mask` | `uint16_t` | Mask of division this call is relevant to (bitwise and with supplied divisionMask to determine draw/skip). |

### struct udBlockRenderVertexData

Stores the vertex data needed to render a block

| Field | Type | Description |
|-------|------|-------------|
| `pBlock` | `void \*` | Pointer to internal block memory. |
| `pPointBuffer` | `const struct [udPointBufferU64](udPointBuffer.md) \*` | Pointer to points data. |
| `unitOctreeMultiplier` | `double` | Multiplier to take from integer octee space to 0..1 octree space. |
| `nodeSize` | `double` | Generally the w component for the size of the node (1.0 == root, 0.5 = level 1, 0.25, etc). |
| `childSize` | `double` | nodeSize \* 0.5 Currently legacy, with intent to switch everything to nodeSize |
| `modelToBlock` | `udDouble4x4` | Matrix to take a block from model space, to block space. |
| `distEye` | `double` | Distance of this block to the camera (in eye space). |

### struct udBlockRenderModel

Exposes data required to render a model

| Field | Type | Description |
|-------|------|-------------|
| `pRenderModel` | `struct udRenderModel \*` | Pointer to internal model. |
| `world` | `udDouble4x4` | World Matrix. |
| `worldView` | `udDouble4x4` | World-View Matrix. |
| `projection` | `udDouble4x4` | Projection Matrix. |
| `wvps` | `udDouble4x4` | World-View-Projection-Screen Matrix. |
| `frustumPlanes[6]` | `udDouble4` | Cached view frustum planes. |
| `eyePosMS` | `udDouble3` | Position of the eye in model space. |
| `cameraForward` | `udDouble3` | Forward vector of the camera in model space. |
| `cameraFacingDiag` | `udDouble3` | Vector that when transformed will be a diagonal line in screen space. |

### struct udBlockRenderInfo

Structure to hold rendering info for a single drawcall

| Field | Type | Description |
|-------|------|-------------|
| `pDrawList` | `struct udBlockRenderDrawList \*` | The draw list defining which points of the block are to be rendered. |
| `blockPriority` | `double` | The priority of the block. |
| `pointMode` | `enum [udRenderContextPointMode](udRenderContext.md)` | points/rectangles/cubes |
| `divisionsMask` | `uint16_t` | divisions mask, identifying which portions of the block are to be rendered |

### struct udBlockRenderGPUInterface

Structure that stores user-defined rendering callbacks (optional and required)

| Field | Type | Description |
|-------|------|-------------|
| `height)` | `void (\*pBeginRender)(void \*pGPUContext, const struct udRenderView \*pView, uint32_t width, uint32_t` | Called when rendering begins. |
| `pGPUContext)` | `void (\*pEndRender)(void \*` | Called when rendering ends. |
| `ppVertexBuffer)` | `enum [udError](udError.md) (\*pCreateVertexBuffer)(void \*pGPUContext, const struct udBlockRenderModel \*pModel, const struct udBlockRenderVertexData vertexData, void \* \*` | Called when vertex buffer is ready to be created. |
| `pVoxelShaderData)` | `enum [udError](udError.md) (\*pUploadVertexBuffer)(void \*pGPUContext, const struct udBlockRenderModel \*pModel, void \*pVertexBuffer, void \*` | Called when vertex buffer is ready to upload to GPU. |
| `pInfo)` | `enum [udError](udError.md) (\*pRenderVertexBuffer)(void \*pGPUContext, const struct udBlockRenderModel \*pModel, void \*pVertexBuffer, void \*pVoxelShaderData, const struct udBlockRenderInfo \*` | Called when vertex buffer is to be rendered. |
| `pVertexBuffer)` | `enum [udError](udError.md) (\*pDestroyVertexBuffer)(void \*pGPUContext, void \*` | Called when vertex buffer is to be destroyed. |
| `pGPUContext` | `void \*` | Internal pointer to user-defined storage. |
