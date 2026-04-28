# udPointCloud

The **udPointCloud** object provides an interface to load a Nuclideon Unlimited Detail model. Once instantiated, the **udPointCloud** can be queried for metadata information, and rendered with the udRenderContext functions. Future releases will allow users to also query the pointcloud data itself, providing the ability to export to LAS or render sub-sections of the pointcloud. 

## Functions

### enum [udError](udError.md) udPointCloud_Load(struct udContext \*pContext, struct udPointCloud \*\*ppModel, const char \*modelLocation, struct udPointCloudHeader \*pHeader)

Load a udPointCloud from `modelLocation`.

> [!NOTE]
> The application should call **udPointCloud_Unload** with `ppModel` to destroy the object once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The context to be used to load the model. |
| `ppModel` | The pointer pointer of the udPointCloud. This will allocate an instance of `udPointCloud` into `ppModel`. |
| `modelLocation` | The location to load the model from. This may be a file location, or a supported protocol (HTTP, HTTPS, FTP). |
| `pHeader` | If non-null, the provided udPointCloudHeader structure will be writen to |

**Returns:** A [udError](udError.md) value based on the result of the model load.

### enum [udError](udError.md) udPointCloud_LoadAdv(struct udContext \*pContext, struct udPointCloud \*\*ppModel, const char \*modelLocation, struct udPointCloudHeader \*pHeader, struct udPointCloudLoadOptions \*pOptions)

Load a udPointCloud from `modelLocation` with additional load options.

> [!NOTE]
> The application should call **udPointCloud_Unload** with `ppModel` to destroy the object once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The context to be used to load the model. |
| `ppModel` | The pointer pointer of the udPointCloud. This will allocate an instance of `udPointCloud` into `ppModel`. |
| `modelLocation` | The location to load the model from. This may be a file location, or a supported protocol (HTTP, HTTPS, FTP). |
| `pHeader` | If non-null, the provided udPointCloudHeader structure will be writen to |
| `pOptions` | If non-null, the options to be applied when loading the model. |

**Returns:** A [udError](udError.md) value based on the result of the model load.

### enum [udError](udError.md) udPointCloud_Unload(struct udPointCloud \*\*ppModel)

Destroys the udPointCloud.

> [!NOTE]
> The value of `ppModel` will be set to `NULL`.

| Parameter | Description |
|-----------|-------------|
| `ppModel` | The pointer pointer of the udPointCloud. This will deallocate any internal memory used. It may take a few frames before the streamer releases the internal memory. |

**Returns:** A [udError](udError.md) value based on the result of the model unload.

### enum [udError](udError.md) udPointCloud_GetMetadata(struct udPointCloud \*pPointCloud, const char \*\*ppJSONMetadata)

Get the metadata associated with this object.

| Parameter | Description |
|-----------|-------------|
| `pPointCloud` | The point cloud model to get the metadata from. |
| `ppJSONMetadata` | The metadata(in JSON) from the model. |

**Returns:** A [udError](udError.md) value based on the result of getting the model metadata.

### enum [udError](udError.md) udPointCloud_GetHeader(struct udPointCloud \*pPointCloud, struct udPointCloudHeader \*pHeader)

Get the matrix of this model.

> [!NOTE]
> All Unlimited Detail models are assumed to be from { 0, 0, 0 } to { 1, 1, 1 }. Any scaling applied to the model will be in this matrix along with the translation and rotation.

| Parameter | Description |
|-----------|-------------|
| `pPointCloud` | The point cloud model to get the matrix from. |
| `pHeader` | The header structure to fill out |

**Returns:** A [udError](udError.md) value based on the result of getting the model header.

### enum [udError](udError.md) udPointCloud_Export(struct udPointCloud \*pModel, const char \*pExportFilename, const struct [udGeometry](udGeometry.md) \*pFilter, float \*pProgress)

Exports a point cloud

> [!WARNING]
> If an existing file exists this function will try override it

| Parameter | Description |
|-----------|-------------|
| `pModel` | The loaded pointcloud to export. |
| `pExportFilename` | The path and filename to export the point cloud to. This should be a file location with write permissions. Supported formats are .UDS and .LAS. |
| `pFilter` | If non-NULL this filter will be applied on the export to export a subsection |
| `pProgress` | If non-NULL, this will be updated with a (estimated) progress throughout the export. Ranges between 0.f - 1.f |

**Returns:** A [udError](udError.md) value based on the result of the model export

### enum [udError](udError.md) udPointCloud_GetNodeColour(const struct udPointCloud \*pModel, const struct udVoxelID \*pVoxelID, uint32_t \*pColour)

Gets the default colour for a specific voxel in a given point cloud

> [!WARNING]
> Calling this with invalid inputs can easily crash the program

| Parameter | Description |
|-----------|-------------|
| `pModel` | The point cloud to get a default colour for. |
| `pVoxelID` | The voxelID provided by picking or to voxel shaders |
| `pColour` | The address to write the colour of the given voxel to |

**Returns:** A [udError](udError.md) value based on the result of getting the colour

### enum [udError](udError.md) udPointCloud_GetNodeColour64(const struct udPointCloud \*pModel, const struct udVoxelID \*pVoxelID, uint64_t \*pColour)

Gets the default colour for a specific voxel in a given point cloud

> [!WARNING]
> Calling this with invalid inputs can easily crash the program

| Parameter | Description |
|-----------|-------------|
| `pModel` | The point cloud to get a default colour for. |
| `pVoxelID` | The voxelID provided by picking or to voxel shaders |
| `pColour` | The address to write the colour of the given voxel to |

**Returns:** A [udError](udError.md) value based on the result of getting the colour

### enum [udError](udError.md) udPointCloud_GetAttributeAddress(struct udPointCloud \*pModel, const struct udVoxelID \*pVoxelID, uint32_t attributeOffset, const void \*\*ppAttributeAddress)

Gets the pointer to the attribute offset on a specific voxel in a point cloud

> [!WARNING]
> Calling this with invalid inputs can easily crash the program

| Parameter | Description |
|-----------|-------------|
| `pModel` | The point cloud to get an address for. |
| `pVoxelID` | The node provided by picking or to voxel shaders |
| `attributeOffset` | The attribute offset from udAttributeSet_GetOffsetOfNamedAttribute or udAttributeSet_GetOffsetOfStandardAttribute |
| `ppAttributeAddress` | The pointer will be updated with the address to the attribute |

**Returns:** A [udError](udError.md) value based on the result of getting the attribute address

### enum [udError](udError.md) udPointCloud_GetStreamingStatus(struct udPointCloud \*pModel)

Gets the streamer status for the model

> [!NOTE]
> udE_Success indicates the model is streaming successfully, other errors indicate other specific issues

| Parameter | Description |
|-----------|-------------|
| `pModel` | The point cloud to get the status of. |

**Returns:** A [udError](udError.md) value indicating the internal streamer status for this model.

### enum [udError](udError.md) udPointCloud_GetSourceAttributes(struct udPointCloud \*pModel, struct [udAttributeSet](udAttributes.md) \*pAttributeSet)

Gets the [udAttributeSet](udAttributes.md) of the model

> [!NOTE]
> udAttributeSet_Destroy must be called on pAttributeSet

| Parameter | Description |
|-----------|-------------|
| `pModel` | The point cloud to get original attributes of. |
| `pAttributeSet` | The attributeSet to be populated |

**Returns:** A [udError](udError.md) value indicating success of fetching the attributes

### enum [udError](udError.md) udPointCloud_SetAntiOctree(struct udPointCloud \*pModel, struct udPointCloud \*pAntiOctreeModel)

Set the Anti Octree of the model

| Parameter | Description |
|-----------|-------------|
| `pModel` | The point cloud to get assigned a new Anti Octree. |
| `pAntiOctreeModel` | The point cloud to be used as anti octree |

**Returns:** A [udError](udError.md) value indicating success setting the anti octree to this PointCloud

### enum [udError](udError.md) udPointCloud_GetHistogramData(struct udPointCloud \*pModel, uint32_t attributeIndex, uint64_t \*pHistogram, uint32_t \*pHistogramSize, double \*pMin, double \*pIncrement, uint64_t \*pHistogramMax, uint64_t \*pHistogramTotal)

Get a histogram of an attribute for this point cloud (if calculated at convert time)

| Parameter | Description |
|-----------|-------------|
| `pPointCloud` | Pointer to the point cloud to get histogram from |
| `attributeIndex` | Index of the attribute within the pointcloud attribute to of the pointcloud |
| `pHistogram` | An array of 64 uint64s to be populated with the bins of the histogram |
| `pHistogramSize` | Pointer to be populated with the number of 64 bit bins in the histogram |
| `pMin` | Pointer to be populated with the minimum value in the histogram (may be NULL) |
| `pIncrement` | Pointer to be populated with the width of the histogram buckets (may be NULL) |
| `pHistogramMax` | Pointer to be populated with the maximum count recorded in the histogram (may be NULL) |
| `pHistogramTotal` | Pointer to be populated with the total points represented in the histogram (may be NULL) |

**Returns:** A [udError](udError.md) value indicating success of getting the histogram for this point cloud

### enum [udError](udError.md) udPointCloud_GetAttrMinMaxF64(struct udPointCloud \*pModel, uint32_t index, double \*pMin, double \*pMax)

Get the min and max values of an attribute in a point cloud as doubles

| Parameter | Description |
|-----------|-------------|
| `pModel` | The pointer to the point cloud to get the min and max from |
| `index` | The index of the attribute to retrieve the min and max of |
| `pMin` | A pointer to store the resultant min in |
| `pMax` | A pointer to store the resultant max in |

**Returns:** A [udError](udError.md) value indicating success of getting the attribute min and max values, udE_NotFound if the attribute is not present

### enum [udError](udError.md) udPointCloud_GetAttrMinMaxI64(struct udPointCloud \*pModel, uint32_t index, int64_t \*pMin, int64_t \*pMax)

Get the min and max values of an attribute in a point cloud as 64 bit signed integers

| Parameter | Description |
|-----------|-------------|
| `pModel` | The pointer to the point cloud to get the min and max from |
| `index` | The index of the attribute to retrieve the min and max of |
| `pMin` | A pointer to store the resultant min in |
| `pMax` | A pointer to store the resultant max in |

**Returns:** A [udError](udError.md) value indicating success of getting the attribute min and max values, udE_NotFound if the attribute is not present

### enum [udError](udError.md) udPointCloud_GetAttrMinMaxU64(struct udPointCloud \*pModel, uint32_t index, uint64_t \*pMin, uint64_t \*pMax)

Get the min and max values of an attribute in a point cloud as 64 bit unsigned integers

| Parameter | Description |
|-----------|-------------|
| `pModel` | The pointer to the point cloud to get the min and max from |
| `index` | The index of the attribute to retrieve the min and max of |
| `pMin` | A pointer to store the resultant min in |
| `pMax` | A pointer to store the resultant max in |

**Returns:** A [udError](udError.md) value indicating success of getting the attribute min and max values, udE_NotFound if the attribute is not present


## Structs

### struct udVoxelID

Combines the traverse context and node index to uniquely identify a node

| Field | Type | Description |
|-------|------|-------------|
| `index` | `uint64_t` | Internal index value. |
| `pTrav` | `const void \*` | Internal traverse info. |
| `pRenderInfo` | `void \*` | Internal render info. |

### struct udPointCloudHeader

Stores basic information about a udPointCloud

| Field | Type | Description |
|-------|------|-------------|
| `scaledRange` | `double` | The point cloud’s range multiplied by the voxel size. |
| `unitMeterScale` | `double` | The scale to apply to convert to/from metres (after scaledRange is applied to the unitCube). |
| `totalLODLayers` | `uint32_t` | The total number of LOD layers in this octree. |
| `convertedResolution` | `double` | The resolution this model was converted at. |
| `storedMatrix[16]` | `double` | This matrix is the ‘default’ internal matrix to go from a unit cube to the full size. |
| `attributes` | `struct [udAttributeSet](udAttributes.md)` | The attributes contained in this pointcloud. |
| `baseOffset[3]` | `double` | The offset to the root of the pointcloud in unit cube space. |
| `pivot[3]` | `double` | The pivot point of the model, in unit cube space. |
| `boundingBoxCenter[3]` | `double` | The center of the bounding volume, in unit cube space. |
| `boundingBoxExtents[3]` | `double` | The extents of the bounding volume, in unit cube space. |

### struct udPointCloudLoadOptions

Contains additional loading options passed to `udPointCloud_LoadAdv`

| Field | Type | Description |
|-------|------|-------------|
| `numberAttributesLimited` | `uint32_t` | indicates whether to limit attributes uing the limitAttributes array |
| `pLimitedAttributes` | `uint32_t \*` | array of booleans corresponding to the pAttributes array in the models original [udAttributeSet](udAttributes.md) indicating which attributes to load from the pointcloud |
