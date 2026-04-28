# udConvert

The **udConvertContext** object provides an interface to create a Nuclideon Unlimited Detail model from a number of supported pointcloud formats. Once instantiated, the **udConvertContext** object can be populated with input files and various conversion settings, before initiating the conversion process. 

## Functions

### enum [udError](udError.md) udConvert_CreateContext(struct udContext \*pContext, struct udConvertContext \*\*ppConvertContext)

Create a udConvertContext to convert models to the Nuclideon file format.

> [!NOTE]
> The application should call **udConvert_DestroyContext** with `ppConvertContext` to destroy the object once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The context to be used to create the convert context. |
| `ppConvertContext` | The pointer pointer of the udConvertContext. This will allocate an instance of `udConvertContext` into `ppConvertContext`. |

**Returns:** A [udError](udError.md) value based on the result of the convert context creation.

### enum [udError](udError.md) udConvert_DestroyContext(struct udConvertContext \*\*ppConvertContext)

Destroys the instance of `ppConvertContext`.

> [!NOTE]
> The value of `ppConvertContext` will be set to `NULL`.

| Parameter | Description |
|-----------|-------------|
| `ppConvertContext` | The pointer pointer of the udConvertContext. This will deallocate the instance of `udConvertContext`. |

**Returns:** A [udError](udError.md) value based on the result of the convert context destruction.

### enum [udError](udError.md) udConvert_SetOutputFilename(struct udConvertContext \*pConvertContext, const char \*pFilename)

Sets the filename of the output UDS.

> [!NOTE]
> If the extension is .UDG the converter will generate a UDG file

> [!WARNING]
> If the .UDS extension isn’t set, this function will add the extension.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the output filename. |
| `pFilename` | The filename to set for the output. |

**Returns:** A [udError](udError.md) value based on the result of setting the output filename.

### enum [udError](udError.md) udConvert_SetTempDirectory(struct udConvertContext \*pConvertContext, const char \*pFolder)

Sets the temporary output directory for the conversion.

> [!NOTE]
> A trailing slash is not automatically added, this is to allow for a prefix for the temporary files instead of, or as well as, folders.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the temporary directory. |
| `pFolder` | The folder path to set for the temporary directory. |

**Returns:** A [udError](udError.md) value based on the result of setting the temporary directory.

### enum [udError](udError.md) udConvert_SetUseBounds(struct udConvertContext \*pConvertContext, const char \*pPointCloudBoundsPath)

Sets the bounds and point resolution for the conversion from a previously converted point cloud.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the point resolution. |
| `pPointCloudBoundsPath` | The UDS file path to be used to set the bounds and point resolution. |

**Returns:** A [udError](udError.md) value based on the result of setting the point resolution and min ,max bounds.

### enum [udError](udError.md) udConvert_SetPointResolution(struct udConvertContext \*pConvertContext, uint32_t override, double pointResolutionMeters)

Sets the point resolution for the conversion.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the point resolution. |
| `override` | A boolean value (0 is false) to indicate whether to override the point resolution or use the auto-detected value. |
| `pointResolutionMeters` | The point resolution in meters. |

**Returns:** A [udError](udError.md) value based on the result of setting the point resolution.

### enum [udError](udError.md) udConvert_IgnoreAttribute(struct udConvertContext \*pConvertContext, const char \*pAttributeName)

Flags an attribute to be ignored for the conversion.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the ignored attribute. |
| `pAttributeName` | The name of the attribute to be ignored. |

### enum [udError](udError.md) udConvert_RestoreAttribute(struct udConvertContext \*pConvertContext, const char \*pAttributeName)

Includes an attribute in the conversion if the attribute has previously been ignored.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to restore attribute. |
| `pAttributeName` | The name of the attribute to be restored. |

### enum [udError](udError.md) udConvert_SetAttributePrefix(struct udConvertContext \*pConvertContext, const char \*pAttributeName, const char \*pPrefix)

Sets the prefix of the attribute, used when displaying values to users.

> [!NOTE]
> The prefix has a limit of 15 characters, not including the null terminator.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the attribute prefix. |
| `pAttributeName` | The name of the attribute to set the prefix for. |
| `pPrefix` | The prefix to use for the attribute. |

### enum [udError](udError.md) udConvert_SetAttributeSuffix(struct udConvertContext \*pConvertContext, const char \*pAttributeName, const char \*pSuffix)

Sets the suffix of the attribute, used when displaying values to users.

> [!NOTE]
> The suffix has a limit of 15 characters, not including the null terminator.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the attribute suffix. |
| `pAttributeName` | The name of the attribute to set the suffix for. |
| `pSuffix` | The suffix to use for the attribute. |

### enum [udError](udError.md) udConvert_SetSRID(struct udConvertContext \*pConvertContext, uint32_t override, int srid)

Sets the SRID for the conversion.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the SRID and WKT using SRID. |
| `override` | A boolean value (0 is false) to indicate whether to override the SRID or use the auto-detected value. |
| `srid` | The SRID value to use. |

**Returns:** A [udError](udError.md) value based on the result of setting the SRID & WKT.

### enum [udError](udError.md) udConvert_SetWKT(struct udConvertContext \*pConvertContext, const char \*pWKT)

Sets the WKT for the conversion.

> [!NOTE]
> This will also enable the override on the SRID field (will not use the auto-detected value)

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the SRID and WKT using WKT. |
| `pWKT` | The WKT string to use. |

**Returns:** A [udError](udError.md) value based on the result of setting the SRID & WKT.

### enum [udError](udError.md) udConvert_SetGlobalOffset(struct udConvertContext \*pConvertContext, const double globalOffset\[3\])

This function adds the supplied global offset to each point in the model.

> [!NOTE]
> This is most useful for moving the origin of a model (or set of models) to the false easting and northing of an alternative geozone.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to set the offset within. |
| `globalOffset` | An array of 3 Doubles representing the desired offset in X, Y and then Z. |

**Returns:** A [udError](udError.md) value based on the result of setting the global offset.

### enum [udError](udError.md) udConvert_SetSkipErrorsWherePossible(struct udConvertContext \*pConvertContext, uint32_t ignoreParseErrorsWherePossible)

This function sets the convert context up to attempt to skip errors where it can.

> [!NOTE]
> In most situations this will mean that an input that is corrupt, malformed or not completely supported will be parsed as far as possible and if an error occurs it will skip the rest of this input and begin on the next.

> [!NOTE]
> Some importers may be able to skip to a later section in the file and continue conversion but this is up to the specific implementation of the importer.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the skip errors where possible option. |
| `ignoreParseErrorsWherePossible` | A boolean value (0 is false) to indicate whether to skip errors where possible. |

**Returns:** A [udError](udError.md) value based on the result of setting the skip errors where possible option.

### enum [udError](udError.md) udConvert_SetIncludeSourceFileID(struct udConvertContext \*pConvertContext, uint32_t includeSourceFileID)

This function sets the convert context to include a source file ID attribute channel, corresponding to a list of ID-filename pairs written to the metadata.

> [!NOTE]
> The udSourceFileID has a maximum size of 65,536, therefore any conversion performed with more than this amount of source files will have indices that overflow back to 0.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the include source file ID option. |
| `includeSourceFileID` | A boolean value (0 is false) to indicate whether to include the source file ID. |

**Returns:** A [udError](udError.md) value based on the result of setting the include source file ID option.

### enum [udError](udError.md) udConvert_SetEveryNth(struct udConvertContext \*pConvertContext, uint32_t everyNth)

`EveryNth` lets the importers know to only include every \*_n_\*th point. If this is set to 0 or 1, every point will be included.

> [!NOTE]
> For many file formats this will be significantly faster to process making this valuable as a tool to test if the resolution and geolocation settings are correct before doing a full conversion.

> [!NOTE]
> The first (0th) point is always included regardless of this value. Example: Setting this to `50` would:
1. Include the first point(point 0)
2. Skip 49 points
3. Include the 50th point
4. Skip another 49 points
5. Include the 100th point n. …and so on skipping 49 points and including the 50th until all points from this input are processed. The next input would then reset the count and include the 0th, skipping 49 etc.as before.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to set the everyNth param on |
| `everyNth` | How many *n_th points to include. Alternatively, how many (n - 1) points to skip for every point included in the export. \_See the example below for a bit more context on what this number means*. |

**Returns:** A [udError](udError.md) value based on the result of setting the every Nth option.

### enum [udError](udError.md) udConvert_SetPolygonVerticesOnly(struct udConvertContext \*pConvertContext, uint32_t polygonVerticesOnly)

This function sets the convert context up to skip rasterization of the polygons, leaving only the vertices.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the polygonVerticesOnly param on. |
| `polygonVerticesOnly` | A boolean value (0 is false) to indicate whether to skip rasterization of the polygons being converted, leaving only the vertices. |

**Returns:** A [udError](udError.md) value based on the result of setting the polygon vertices only option.

### enum [udError](udError.md) udConvert_SetRetainPrimitives(struct udConvertContext \*pConvertContext, uint32_t retainPrimitives)

This function sets the convert context up to retain rasterised primitives such as lines/triangles to be rendered at finer resolutions at runtime

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the polygonVerticesOnly param on. |
| `retainPrimitives` | A boolean value (0 is false) to indicate whether to retain the primitives in the output UDS file |

**Returns:** A [udError](udError.md) value based on the result of setting the retainPrimitives option.

### enum [udError](udError.md) udConvert_SetBakeLighting(struct udConvertContext \*pConvertContext, uint32_t bakeLighting)

This function sets the convert context up to set the udCIF_BakeLightning flag allowing the read point function to bake normals into the colour channel

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the polygonVerticesOnly param on. |
| `bakeLighting` | A boolean value (0 is false) to indicate whether to bake the normals into the colour channel in the output UDS file |

**Returns:** A [udError](udError.md) value based on the result of setting the retainPrimitives option.

### enum [udError](udError.md) udConvert_SetExportOtherEmbeddedAssets(struct udConvertContext \*pConvertContext, uint32_t exportImages)

This function sets the convert context up to set the udCIF_ExportImages flag allowing the open function to export images to png or jpg files

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the polygonVerticesOnly param on. |
| `exportImages` | A boolean value (0 is false) to indicate whether to export or not images contained in e57 files |

**Returns:** A [udError](udError.md) value based on the result of setting the exportImages option.

### enum [udError](udError.md) udConvert_SetMetadata(struct udConvertContext \*pConvertContext, const char \*pMetadataKey, const char \*pMetadataValue)

This adds a metadata key to the output UDS file. There are no restrictions on the key.

> [!NOTE]
> There are a number of ‘standard’ keys that are recommended to support.
- `Author`: The name of the company that owns or captured the data
- `Comment`: A miscellaneous information section
- `Copyright`: The copyright information
- `License`: The general license information

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to use to set the metadata key. |
| `pMetadataKey` | The name of the key.This is parsed as a JSON address. |
| `pMetadataValue` | The contents of the key, settings this as `NULL` will remove the key from the system (if it exists). This value is handled internal as a string (won’t be parsed as JSON). |

**Returns:** A [udError](udError.md) value based on the result of setting the metadata key and value.

### enum [udError](udError.md) udConvert_AddItem(struct udConvertContext \*pConvertContext, const char \*pFilename)

This adds an item to be converted in the convert context.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to add the item to. |
| `pFilename` | The file to add to the convert context. |

**Returns:** A [udError](udError.md) value based on the result of adding the item.

### enum [udError](udError.md) udConvert_RemoveItem(struct udConvertContext \*pConvertContext, uint64_t index)

This removes an item to be converted from the convert context.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to remove the item from. |
| `index` | The index of the item to remove from the convert context. |

**Returns:** A [udError](udError.md) value based on the result of removing the item.

### enum [udError](udError.md) udConvert_SetInputSourceProjection(struct udConvertContext \*pConvertContext, uint64_t index, int srid)

This specifies the projection of the source data.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to set the input source projection on. |
| `index` | The index of the item to set the source project on. |
| `srid` | The SRID to use for the specified item. |

**Returns:** A [udError](udError.md) value based on the result of setting the source projection.

### enum [udError](udError.md) udConvert_GetInfo(struct udConvertContext \*pConvertContext, const struct udConvertInfo \*\*ppInfo)

This provides a way to get the information of the convert context.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to retrieve the information from. |
| `ppInfo` | The pointer pointer of the udConvertInfo. This will be managed by the convert context and does not need to be deallocated. |

**Returns:** A [udError](udError.md) value based on the result of getting the information of the convert context.

### enum [udError](udError.md) udConvert_GetItemInfo(struct udConvertContext \*pConvertContext, uint64_t index, struct udConvertItemInfo \*pInfo)

This provides a way to get the information of a specific item in the convert context.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to retrieve the item information from. |
| `index` | The index of the item to retrieve the information for from the convert context. |
| `pInfo` | The pointer of the udConvertItemInfo. The will be populated by the convert context from an internal representation. |

**Returns:** A [udError](udError.md) value based on the result of getting the information of the specified item.

### enum [udError](udError.md) udConvert_DoConvert(struct udConvertContext \*pConvertContext)

This begins the conversion process for the provided convert context.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context on which to start the conversion. |

**Returns:** A [udError](udError.md) value based on the result of starting the conversion.

### enum [udError](udError.md) udConvert_Cancel(struct udConvertContext \*pConvertContext)

This cancels the running conversion for the provided convert context.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context on which to cancel the conversion. |

**Returns:** A [udError](udError.md) value based on the result of cancelling the conversion.

### enum [udError](udError.md) udConvert_Reset(struct udConvertContext \*pConvertContext)

This resets the status for the provided convert context, for example to re-run a previously completed conversion.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context on which to reset the status. |

**Returns:** A [udError](udError.md) value based on the result of resetting the status.

### enum [udError](udError.md) udConvert_GeneratePreview(struct udConvertContext \*pConvertContext, struct udPointCloud \*\*ppCloud)

This generates a preview of the provided convert context.

> [!NOTE]
> The application should call **udPointCloud_Unload** with `ppCloud` to destroy the object once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to generate the preview for. |
| `ppCloud` | The pointer pointer of the udPointCloud. This will allocate an instance of `udPointCloud` into `ppCloud`. |

**Returns:** A [udError](udError.md) value based on the result of genearting the preview.

### enum [udError](udError.md) udConvertPostProcessCallback(struct udConvertItemInfo \*pConvertInput, struct [udPointBufferF64](udPointBuffer.md) \*pBuffer, void \*pUserData)

Callback invoked on pointbuffers after being read in during the convert process to conditionally modify points based on buffer contents

| Parameter | Description |
|-----------|-------------|
| `pConvertInput` | The convert info associated with the current item being processed at the time the callback is invoked |
| `pBuffer` | The point buffer containing the points currently being read in prior to any processing done by convert (e.g. reprojection) |
| `pUserData` | Pointer to a struct containing user data used by this function- this may be freed by pCleanUpUserData on completion of processing of convert inputs if necessary |

**Returns:** A [udError](udError.md) to indicate the success of the postprocessing - returning anything other than udE_Success will cause the conversion to fail

### enum [udError](udError.md) udConvert_SetPostProcessCallback(struct udConvertContext \*pContext, udConvertPostProcessCallback \*pCallback, void \*pUserData, void (\*pCleanUpUserData)(void\*))

Postprocessing to perform on points as they are read in

| Parameter | Description |
|-----------|-------------|
| `pContext` | The convert context |
| `pCallback` | takes the convertInput, a point buffer, a pointer to user data (which must point to memory that is valid for the duration of the convert process); returns [udError](udError.md) This can be used to modify the points and their attributes as well as modify the contents of the userData Structure |
| `pUserData` | a pointer to any data used by the callback |
| `pCleanUpUserData` | a function called with pUserData as the argument once the input has finished processing |

**Returns:** A [udError](udError.md) value based on the result of setting the callback

### enum [udError](udError.md) udConvert_AddOutputAttribute(struct udConvertContext \*pContext, struct [udAttributeDescriptor](udAttributes.md) \*pAttribute)

Forces the produced UDS to include the specified attribute despite not being present in any input file. This is useful when these attributes are calculated using a postprocess callback The forced attribute may still be excluded using udConvert_IgnoreAttribute. This allows an attribute added to the conversion using this function to be added/ removed using ignore/restore attribute

| Parameter | Description |
|-----------|-------------|
| `pContext` | The convert context |
| `pAttribute` | descriptor of the attribute to be added. This is copied by the function |

**Returns:** A [udError](udError.md) value based on the result of setting the forced attribute
* **Returns:**
  udE_CountExceeded if the number of attributes exceeds the limit in a UDS 

### enum [udError](udError.md) udConvert_RemoveOutputAttribute(struct udConvertContext \*pContext, uint32_t index)

Removes the forced attribute at the index specified from the list

| Parameter | Description |
|-----------|-------------|
| `pContext` | The convert context |
| `index` | the index of from the array of forced attributes to remove |

**Returns:** A [udError](udError.md) value based on the result of removing the forced attribute

### enum [udError](udError.md) udConvert_SetAttributeRangeMaskSize(struct udConvertContext \*pContext, const char \*pAttributeName, uint8_t attributeRangeMaskSize)

Sets the range mask size used during this conversion: higher values improve precision when performing attribute filtering on the resultant point cloud

| Parameter | Description |
|-----------|-------------|
| `pContext` | The convert context |
| `pAttributeName` | the name of the attribute to set the range mask size for |
| `attributeRangeMaskSize` | the number of bytes to use for containing the range mask (0, 1, 2, 4, 8) |

**Returns:** A [udError](udError.md) value based on the result of setting the range mask size

### enum [udError](udError.md) udConvert_GetAttributeRangeMaskSize(struct udConvertContext \*pContext, const char \*pAttributeName, uint32_t \*pAttributeRangeMaskSize)

Gets the range mask size used for the attribute with the given name during this conversion

| Parameter | Description |
|-----------|-------------|
| `pContext` | The convert context |
| `pAttributeName` | the name of the attribute to get the range mask size for |
| `pAttributeRangeMaskSize` | the number of bytes to use for containing the range mask (0, 1, 2, 4, 8) |

**Returns:** A [udError](udError.md) value based on the result of getting the range mask size


## Structs

### struct udConvertInfo

Provides a copy of a subset of the convert state

| Field | Type | Description |
|-------|------|-------------|
| `pOutputName` | `const char \*` | The output filename. |
| `pTempFilesPrefix` | `const char \*` | The file prefix for temp files. |
| `pMetadata` | `const char \*` | The metadata that will be added to this model (in JSON format). |
| `attributes` | `struct [udAttributeSet](udAttributes.md)` | The attributes in this model. |
| `ignoredAttributesLength` | `int32_t` | The length of the ignored attributes list. |
| `ppIgnoredAttributes` | `const char \* \*` | The list of ignored attributes. |
| `globalOffset[3]` | `double` | This amount is added to every point during conversion. Useful for moving the origin of the entire scene to geolocate. |
| `minPointResolution` | `double` | The native resolution of the highest resolution file. |
| `maxPointResolution` | `double` | The native resolution of the lowest resolution file. |
| `skipErrorsWherePossible` | `uint32_t` | If not 0 it will continue processing other files if a file is detected as corrupt or incorrect. |
| `includeSourceFileID` | `uint32_t` | If not 0 this will embed source files to the udSourceFileID attribute channel of the output. |
| `everyNth` | `uint32_t` | If this value is >1, only every Nth point is included in the model. e.g. 4 means only every 4th point will be included, skipping 3/4 of the points. |
| `polygonVerticesOnly` | `uint32_t` | If not 0 it will skip rasterization of polygons in favour of just processing the vertices. |
| `retainPrimitives` | `uint32_t` | If not 0 rasterised primitives such as triangles/lines/etc are retained to be rendered at finer resolution if required at runtime. |
| `bakeLighting` | `uint32_t` | if not 0 bake the normals into the colour channel in the output UDS file |
| `exportOtherEmbeddedAssets` | `uint32_t` | if not 0 export images contained in e57 files |
| `overrideResolution` | `uint32_t` | Set to not 0 to stop the resolution from being recalculated. |
| `pointResolution` | `double` | The scale to be used in the conversion (either calculated or overriden). |
| `overrideSRID` | `uint32_t` | Set to not 0 to prevent the SRID being recalculated. |
| `srid` | `int` | The geospatial reference ID (either calculated or overriden). |
| `pWKT` | `const char \*` | The geospatial WKT string. |
| `totalPointsRead` | `uint64_t` | How many points have been read in this model. |
| `totalItems` | `uint64_t` | How many items are in the list. |
| `currentInputItem` | `uint64_t` | The index of the item that is currently being read. |
| `outputFileSize` | `uint64_t` | Size of the result UDS file. |
| `sourcePointCount` | `uint64_t` | Number of points added (may include duplicates or out of range points). |
| `uniquePointCount` | `uint64_t` | Number of unique points in the final model. |
| `discardedPointCount` | `uint64_t` | Number of duplicate or ignored out of range points. |
| `outputPointCount` | `uint64_t` | Number of points written to UDS (can be used for progress). |
| `peakDiskUsage` | `uint64_t` | Peak amount of disk space used including both temp files and the actual output file. |
| `peakTempFileUsage` | `uint64_t` | Peak amount of disk space that contained temp files. |
| `peakTempFileCount` | `uint32_t` | Peak number of temporary files written. |

### struct udConvertItemInfo

Provides a copy of a subset of a convert item state

| Field | Type | Description |
|-------|------|-------------|
| `pFilename` | `const char \*` | Name of the input file. |
| `pointsCount` | `int64_t` | This might be an estimate, -1 is no estimate is available. |
| `pointsRead` | `uint64_t` | Once conversation begins, this will give an indication of progress. |
| `estimatedResolution` | `double` | The estimated scale of the item. |
| `srid` | `int` | The calculated geospatial reference ID of the item. |
