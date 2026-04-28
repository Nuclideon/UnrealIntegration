# udTriangleVoxelizer

The **udTriangleVoxelizer** object provides an interface to convert triangles to voxels to be added to a convert job. 

## Functions

### enum [udError](udError.md) udTriangleVoxelizer_Create(struct udTriangleVoxelizer \*\*ppVoxelizer, double gridRes)

Creates a udTriangleVoxelizer object at the specified grid resolution.

> [!NOTE]
> The application should call **udTriangleVoxelizer_Destroy** with `ppTriRaster` to destroy the object once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `ppVoxelizer` | A pointer to a location in which the new udTriangleVoxelizer object is stored. |
| `gridRes` | The intended grid resolution of the convert job. |

**Returns:** A [udError](udError.md) value based on the result of the triangle voxelizer creation.

### enum [udError](udError.md) udTriangleVoxelizer_Destroy(struct udTriangleVoxelizer \*\*ppVoxelizer)

Destroys a udTriangleVoxelizer object that was created using **udTriangleVoxelizer_Create**.

> [!NOTE]
> The value of `ppTriRaster` will be set to `NULL`.

| Parameter | Description |
|-----------|-------------|
| `ppVoxelizer` | A pointer to a udTriangleVoxelizer object which is to be destroyed. |

**Returns:** A [udError](udError.md) value based on the result of the object destruction.

### enum [udError](udError.md) udTriangleVoxelizer_SetTriangle(struct udTriangleVoxelizer \*pVoxelizer, const double \*pV0, const double \*pV1, const double \*pV2)

Set the vertices of the triangle, this primes a new triangle.

> [!NOTE]
> Triangle will be treated as a line if v1 == v2 (v2 is degenerate)

> [!WARNING]
> This will overwrite any existing unread points from a previous triangle

| Parameter | Description |
|-----------|-------------|
| `pVoxelizer` | The voxelizer to be used to set the triangle. |
| `pV0` | The first vertex in the triangle. |
| `pV1` | The second vertex in the triangle. |
| `pV2` | The third vertex in the triangle. |

**Returns:** A [udError](udError.md) value based on the result of setting the triangle.

### enum [udError](udError.md) udTriangleVoxelizer_GetPoints(struct udTriangleVoxelizer \*pVoxelizer, double \*\*ppPositions, double \*\*ppBarycentricWeights, uint32_t \*pPointCount, uint32_t maxPoints)

Get the voxelized points from the current triangle.

> [!NOTE]
> Returns a portion of voxelized points from current triangle, call repeatedly until \*pPointCount is zero meaning the triangle is fully voxelized.

> [!NOTE]
> The udTriangleVoxelizer object owns the arrays returned via ppPositions and ppBarycentricWeights.

| Parameter | Description |
|-----------|-------------|
| `pVoxelizer` | The voxelizer to be used to get the points. |
| `ppPositions` | A pointer to be populated with an array of positions. |
| `ppBarycentricWeights` | A pointer to be populated with an array of Barycentric weights. |
| `pPointCount` | A pointer to be populated with the number of poisitions and weights. |
| `maxPoints` | The maximum number of points to be returned. |

**Returns:** A [udError](udError.md) value based on the result of getting the points.
