# udRenderTarget

The **udRenderTarget** object provides an interface to specify a viewport to render to. Once instantiated, the **udRenderTarget** can have its targets set, providing both a colour and depth output of the render which will utilize the matrices provided to the SetMatrix function. 

## Enums

### enum udRenderTargetMatrix

These are the various matrix types used within the render target 

*Values:*

| Value | Description |
|-------|-------------|
| `udRTM_Camera` | The local to world-space transform of the camera (View is implicitly set as the inverse). |
| `udRTM_View` | The view-space transform for the model (does not need to be set explicitly). |
| `udRTM_Projection` | The projection matrix (default is 60 degree LH). |
| `udRTM_Viewport` | Viewport scaling matrix (default width and height of viewport). |
| `udRTM_Count` | Total number of matrix types. Used internally but can be used as an iterator max when checking matrix information. |

## Functions

### enum [udError](udError.md) udRenderTarget_Create(struct udContext \*pContext, struct udRenderTarget \*\*ppRenderTarget, struct udRenderContext \*pRenderer, uint32_t width, uint32_t height)

Create a udRenderTarget with a viewport using `width` and `height`.

> [!NOTE]
> The application should call **udRenderTarget_Destroy** with `ppRenderTarget` to destroy the object once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The context to be used to create the render target. |
| `ppRenderTarget` | The pointer pointer of the udRenderTarget. This will allocate an instance of udRenderTarget into `ppRenderTarget`. |
| `pRenderer` | The renderer associated with the render target. |
| `width` | The width of the viewport. |
| `height` | The height of the viewport. |

**Returns:** A [udError](udError.md) value based on the result of the render target creation.

### enum [udError](udError.md) udRenderTarget_Destroy(struct udRenderTarget \*\*ppRenderTarget)

Destroys the instance of `ppRenderTarget`.

> [!NOTE]
> The value of `ppRenderTarget` will be set to `NULL`.

| Parameter | Description |
|-----------|-------------|
| `ppRenderTarget` | The pointer pointer of the udRenderTarget. This will deallocate the instance of udRenderTarget. |

**Returns:** A [udError](udError.md) value based on the result of the render target destruction.

### enum [udError](udError.md) udRenderTarget_SetTargets(struct udRenderTarget \*pRenderTarget, void \*pColorBuffer, uint32_t colorClearValue, void \*pDepthBuffer)

Set a memory buffers that a render target will write to.

> [!NOTE]
> This internally calls udRenderTarget_SetTargetsWithPitch with both color and depth pitches set to 0.

| Parameter | Description |
|-----------|-------------|
| `pRenderTarget` | The render target to associate a target buffer with. |
| `pColorBuffer` | The color buffer, if null the buffer will not be rendered to anymore. |
| `colorClearValue` | The clear value to clear the color buffer with. |
| `pDepthBuffer` | The depth buffer, required |

**Returns:** A [udError](udError.md) value based on the result of setting the targets.

### enum [udError](udError.md) udRenderTarget_SetTargetsWithPitch(struct udRenderTarget \*pRenderTarget, void \*pColorBuffer, uint32_t colorClearValue, void \*pDepthBuffer, uint32_t colorPitchInBytes, uint32_t depthPitchInBytes)

Set a memory buffers that a render target will write to (with pitch).

| Parameter | Description |
|-----------|-------------|
| `pRenderTarget` | The render target to associate a target buffer with. |
| `pColorBuffer` | The color buffer, if null the buffer will not be rendered to anymore. |
| `colorClearValue` | The clear value to clear the color buffer with. |
| `pDepthBuffer` | The depth buffer, required |
| `colorPitchInBytes` | The number of bytes that make up a row of the color buffer. |
| `depthPitchInBytes` | The number of bytes that make up a row of the depth buffer. |

**Returns:** A [udError](udError.md) value based on the result of setting the targets.

### enum [udError](udError.md) udRenderTarget_GetMatrix(const struct udRenderTarget \*pRenderTarget, enum udRenderTargetMatrix matrixType, double cameraMatrix\[16\])

Get the matrix associated with `pRenderTarget` of type `matrixType` and fill it in `cameraMatrix`.

| Parameter | Description |
|-----------|-------------|
| `pRenderTarget` | The render target to get the matrix from. |
| `matrixType` | The type of matrix to get. |
| `cameraMatrix` | The array of 16 doubles which gets filled out with the matrix. |

**Returns:** A [udError](udError.md) value based on the result of getting the matrix.

### enum [udError](udError.md) udRenderTarget_SetMatrix(struct udRenderTarget \*pRenderTarget, enum udRenderTargetMatrix matrixType, const double cameraMatrix\[16\])

Set the matrix associated with `pRenderTarget` of type `matrixType` and get it from `cameraMatrix`.

| Parameter | Description |
|-----------|-------------|
| `pRenderTarget` | The render target to set the matrix to. |
| `matrixType` | The type of matrix to set. |
| `cameraMatrix` | The array of 16 doubles to fill out the internal matrix with. |

**Returns:** A [udError](udError.md) value based on the result of setting the matrix.

### enum [udError](udError.md) udRenderTarget_SetLogarithmicDepthPlanes(struct udRenderTarget \*pRenderTarget, double nearPlane, double farPlane)

Set the logarithmic depth near and far planes that will be used for logarithmic rendering. Note: These values are only used when the ‘udRCF_LogarithmicDepth’ rendering flag is set.

| Parameter | Description |
|-----------|-------------|
| `pRenderTarget` | The render target to set the matrix to. |
| `nearPlane` | The value that the near plane will be set to. |
| `farPlane` | The value that the far plane will be set to. |
