# udQueryContext

The udQueryContext object provides an interface to query or filter pointclouds. 

## Functions

### enum [udError](udError.md) udQueryContext_Create(struct udContext \*pContext, struct udQueryContext \*\*ppQueryCtx, struct udPointCloud \*pPointCloud, const struct [udGeometry](udGeometry.md) \*pFilter)

Create an instance of a udQueryContext with a specific model.

> [!NOTE]
> A future release will add multiple model support and non-storedMatrix locations.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The context to be used to create the query context. |
| `ppQueryCtx` | The pointer pointer of the udQueryContext. This will allocate an instance of udQueryContext into `ppQuery`. |
| `pPointCloud` | The point cloud to run the query on, it is located at its storedMatrix location (this can be changed using udQueryContext_ChangePointCloud). |
| `pFilter` | The filter to use in this query (this can be changed using udQueryContext_ChangeFilter). |

**Returns:** A [udError](udError.md) value based on the result of the udQueryContext creation.

### enum [udError](udError.md) udQueryContext_ChangeFilter(struct udQueryContext \*pQueryCtx, const struct [udGeometry](udGeometry.md) \*pFilter)

Resets the udQueryContext and uses a new filter.

> [!NOTE]
> This will reset the query, any existing progress will be lost.

| Parameter | Description |
|-----------|-------------|
| `pQueryCtx` | The udQueryContext item previously created using udQueryContext_Create. |
| `pFilter` | The new filter to use in this query. |

**Returns:** A [udError](udError.md) value based on the result of the operation.

### enum [udError](udError.md) udQueryContext_ChangePointCloud(struct udQueryContext \*pQueryCtx, const struct udPointCloud \*pPointCloud)

Resets the udQueryContext and uses a different model.

> [!NOTE]
> This will reset the query, any existing progress will be lost.

| Parameter | Description |
|-----------|-------------|
| `pQueryCtx` | The udQueryContext item previously created using udQueryContext_Create. |
| `pPointCloud` | The new model to use in this query. |

**Returns:** A [udError](udError.md) value based on the result of the operation.

### enum [udError](udError.md) udQueryContext_ExecuteF64(struct udQueryContext \*pQueryCtx, struct [udPointBufferF64](udPointBuffer.md) \*pPointBuffer)

Gets the next set of points from an existing udQueryContext.

> [!NOTE]
> This should continue to be called until it returns udE_NotFound indicating the query has completed.

| Parameter | Description |
|-----------|-------------|
| `pQueryCtx` | The udQueryContext to execute. |
| `pPointBuffer` | The point buffer to write found points to. |

**Returns:** A [udError](udError.md) value based on the result of the operation.

### enum [udError](udError.md) udQueryContext_ExecuteI64(struct udQueryContext \*pQueryCtx, struct [udPointBufferI64](udPointBuffer.md) \*pPointBuffer)

Gets the next set of points from an existing udQueryContext.

> [!NOTE]
> This should continue to be called until it returns udE_NotFound indicating the query has completed.

| Parameter | Description |
|-----------|-------------|
| `pQueryCtx` | The udQueryContext to execute. |
| `pPointBuffer` | The point buffer to write found points to. |

**Returns:** A [udError](udError.md) value based on the result of the operation.

### enum [udError](udError.md) udQueryContext_Destroy(struct udQueryContext \*\*ppQueryCtx)

Destroy the instance of udQueryContext.

| Parameter | Description |
|-----------|-------------|
| `ppQueryCtx` | The pointer pointer of the udQueryContext. This will destroy the instance of udQueryContext in `ppQuery` and set it to NULL. |

**Returns:** A [udError](udError.md) value based on the result of the udQueryContext destruction.

### enum [udError](udError.md) udQuery_TestRenderVoxel(struct [udGeometry](udGeometry.md) \*pQueryFilter, double matrix\[16\], void \*pRenderInfo)

Test the specified voxel against the given udQueryFilter.

| Parameter | Description |
|-----------|-------------|
| `pQueryFilter` | The udQueryFilter to test. |
| `matrix` | The scene matrix for the model that contains the voxel being rendered. |
| `pRenderInfo` | The render info of the voxel being rendered. |

**Returns:** A [udError](udError.md) value based on the result of the test.
