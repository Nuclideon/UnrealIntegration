# udAttributes

udAttributes.h provides an interface to attribute streams of Unlimited Detail models. 

## Enums

### enum \[anonymous\]

*Values:*

| Value | Description |
|-------|-------------|
| `udAttributeSet_MaxDescriptors` | Hard limit on the number of attributes in a .uds pointcloud. |

### enum udStdAttribute

A list of standard UDS attributes 

*Values:*

| Value | Description |
|-------|-------------|
| `udSA_GPSTime` | udATI_float64 |
| `udSA_PrimitiveID` | udATI_uint32 |
| `udSA_PrimitiveU` | udATI_float32 Texture U coordinate passed to custom conversions involving primitives |
| `udSA_PrimitiveV` | udATI_float32 Texture V coordinate passed to custom conversions involving primitives |
| `udSA_PrimitiveMaterialID` | udATI_uint32 ID of texture as returned by udConvert_GetPrimitiveMaterialID, passed to custom conversions involving primitives |
| `udSA_ARGB` | udATI_color32 |
| `udSA_Normal` | udATI_normal32 |
| `udSA_Altitude` | udATI_float32 |
| `udSA_Red` | Legacy 16bit Red channel. |
| `udSA_Green` | Legacy 16bit Green channel. |
| `udSA_Blue` | Legacy 16bit Blue channel. |
| `udSA_Intensity` | udATI_uint16 |
| `udSA_NIR` | udATI_uint16 |
| `udSA_ScanAngle` | udATI_uint16 |
| `udSA_PointSourceID` | udATI_uint16 |
| `udSA_SourceFileID` | udATI_uint16 |
| `udSA_Classification` | udATI_uint8 |
| `udSA_ReturnNumber` | udATI_uint8 |
| `udSA_NumberOfReturns` | udATI_uint8 |
| `udSA_ClassificationFlags` | udATI_uint8 |
| `udSA_ScannerChannel` | udATI_uint8 |
| `udSA_ScanDirection` | udATI_uint8 |
| `udSA_EdgeOfFlightLine` | udATI_uint8 |
| `udSA_ScanAngleRank` | udATI_int8 |
| `udSA_LasUserData` | Specific LAS User data field (udATI_uint8). |
| `udSA_Count` | Count helper value to iterate this enum. |
| `udSA_AllAttributes` | Internal sentinal value used by some functions to indicate getting start of interleaved attributes. |
| `udSA_First` | Generally used to initialise an attribute value for use in loops. |

### enum udStdAttributeContent

The standard UDS attributes provided as a bitfield 

> [!NOTE]
> udStdAttributeContent enums are guaranteed to be 1 << associated udStdAttribute value

*Values:*

| Value | Description |
|-------|-------------|
| `udSAC_None` |  |
| `udSAC_GPSTime` |  |
| `udSAC_PrimitiveID` |  |
| `udSAC_PrimitiveU` |  |
| `udSAC_PrimitiveV` |  |
| `udSAC_PrimitiveMaterialID` |  |
| `udSAC_ARGB` |  |
| `udSAC_Normal` |  |
| `udSAC_Altitude` |  |
| `udSAC_Red` |  |
| `udSAC_Green` |  |
| `udSAC_Blue` |  |
| `udSAC_Intensity` |  |
| `udSAC_NIR` |  |
| `udSAC_ScanAngle` |  |
| `udSAC_PointSourceID` |  |
| `udSAC_SourceFileID` |  |
| `udSAC_Classification` |  |
| `udSAC_ReturnNumber` |  |
| `udSAC_NumberOfReturns` |  |
| `udSAC_ClassificationFlags` |  |
| `udSAC_ScannerChannel` |  |
| `udSAC_ScanDirection` |  |
| `udSAC_EdgeOfFlightLine` |  |
| `udSAC_ScanAngleRank` |  |
| `udSAC_LasUserData` |  |
| `udSAC_AllAttributes` |  |
| `udSAC_64BitAttributes` |  |
| `udSAC_32BitAttributes` |  |
| `udSAC_16BitAttributes` |  |

### enum udAttributeBlendType

These are the various options for how an attribute is calculated when merging voxels while generating LODs 

*Values:*

| Value | Description |
|-------|-------------|
| `udABT_Mean` | This blend type merges nearby voxels together and finds the mean value for the attribute on those nodes. |
| `udABT_FirstChild` | This blend type selects the value from one of the nodes and uses that. |
| `udABT_NoLOD` | This blend type has no information in LODs and is only stored in the highest detail level. |
| `udABT_OR` | This blend type does a bitwise OR of all of the children, and is only useful for flags. |
| `udABT_Count` | Total number of blend types. Used internally but can be used as an iterator max when checking attribute blend modes. |

### enum udAttributeTypeInfo

These are the types that could be contained in attributes 

*Values:*

| Value | Description |
|-------|-------------|
| `udATI_Invalid` |  |
| `udATI_SizeMask` |  |
| `udATI_SizeShift` |  |
| `udATI_ComponentCountMask` |  |
| `udATI_ComponentCountShift` |  |
| `udATI_Signed` |  |
| `udATI_Float` |  |
| `udATI_Color` |  |
| `udATI_Normal` |  |
| `udATI_uint8` |  |
| `udATI_uint16` |  |
| `udATI_uint32` |  |
| `udATI_uint64` |  |
| `udATI_int8` |  |
| `udATI_int16` |  |
| `udATI_int32` |  |
| `udATI_int64` |  |
| `udATI_float32` |  |
| `udATI_float64` |  |
| `udATI_color32` |  |
| `udATI_normal32` |  |
| `udATI_vec3f32` |  |

## Functions

### enum [udError](udError.md) udAttributeSet_Create(struct udAttributeSet \*pAttributeSet, enum udStdAttributeContent content, uint32_t additionalCustomAttributes)

Creates a udAttributeSet

> [!NOTE]
> The application should call udAttributeSet_Free with pAttributeSet to destroy the object once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `pAttributeSet` | The attribute set to allocate into |
| `content` | The standard attributes that will be created, provided as bitfields |
| `additionalCustomAttributes` | The count of additional attributes to generate, these will be added to the attribute set blank after the standard attributes |

**Returns:** A [udError](udError.md) value based on the result of the creation of the attribute set.

### enum [udError](udError.md) udAttributeSet_Destroy(struct udAttributeSet \*pAttributeSet)

Free the memory created by a call to udAttributeSet_Create

| Parameter | Description |
|-----------|-------------|
| `pAttributeSet` | The attribute set to free the resources of |

**Returns:** A [udError](udError.md) value based on the result of the destruction of the attribute set.

### enum [udError](udError.md) udAttributeSet_GetOffsetOfStandardAttribute(const struct udAttributeSet \*pAttributeSet, enum udStdAttribute attribute, uint32_t \*pOffset)

Gets the offset for a standard attribute so that further querying of that attribute can be performed

| Parameter | Description |
|-----------|-------------|
| `pAttributeSet` | The attribute set to get the offset for |
| `attribute` | The enum value of the attribute |
| `pOffset` | This pointer will be written to with the value of the offset if it is found |

**Returns:** A [udError](udError.md) value based on the result of writing the offset to pOffset

### enum [udError](udError.md) udAttributeSet_GetOffsetOfIndexedAttribute(const struct udAttributeSet \*pAttributeSet, uint32_t attributeIndex, uint32_t \*pOffset)

Gets the offset for an indexed attribute so that further querying of that attribute can be performed

| Parameter | Description |
|-----------|-------------|
| `pAttributeSet` | The attribute set to get the offset for |
| `attributeIndex` | The index of the attribute |
| `pOffset` | This pointer will be written to with the value of the offset if it is found |

**Returns:** A [udError](udError.md) value based on the result of writing the offset to pOffset

### enum [udError](udError.md) udAttributeSet_GetOffsetOfNamedAttribute(const struct udAttributeSet \*pAttributeSet, const char \*pName, uint32_t \*pOffset)

Gets the offset for a named attribute so that further querying of that attribute can be performed

| Parameter | Description |
|-----------|-------------|
| `pAttributeSet` | The attribute set to get the offset for |
| `pName` | The name of the attribute |
| `pOffset` | This pointer will be written to with the value of the offset if it is found |

**Returns:** A [udError](udError.md) value based on the result of writing the offset to pOffset

### enum [udError](udError.md) udAttributeSet_GetOffsetAndIndexOfNamedAttribute(const struct udAttributeSet \*pAttributeSet, const char \*pName, uint32_t \*pOffset, uint32_t \*pIndex)

Gets the offset and/or index for a named attribute so that further querying of that attribute can be performed

| Parameter | Description |
|-----------|-------------|
| `pAttributeSet` | The attribute set to get the offset for |
| `pName` | The name of the attribute |
| `pOffset` | Optional pointer to be written to with the value of the offset if it is found (may be null) |
| `pIndex` | Optional pointer to be written with the index of the attribute if found (may be null) |

**Returns:** A [udError](udError.md) value based on the result of writing the offset to pOffset

### enum [udError](udError.md) udAttributeSet_GetDescriptorOfNamedAttribute(const struct udAttributeSet \*pAttributeSet, const char \*pName, struct udAttributeDescriptor \*pDescriptor)

Gets the descriptor of a named attribute stored in a udAttributeSet

| Parameter | Description |
|-----------|-------------|
| `pAttributeSet` | The attribute set to get the descriptor from |
| `pName` | The name of the attribute |
| `pDescriptor` | This pointer to be written to with the value of the descriptor if it is found |

**Returns:** A [udError](udError.md) value based on the result of writing the descriptor to pDescriptor

### enum [udError](udError.md) udAttribute_GetDescriptorOfStandardAttribute(const enum udStdAttribute attribute, struct udAttributeDescriptor \*pDescriptor)

Gets the descriptor of a standard attribute

| Parameter | Description |
|-----------|-------------|
| `attribute` | The standard attribute to return the descriptor of |
| `pDescriptor` | This pointer to be written to with the value of the descriptor if it is found |

**Returns:** A [udError](udError.md) value based on the result of writing the descriptor to pDescriptor

### enum [udError](udError.md) udAttributeSet_EncodeNormal(uint32_t \*pEncoded, const float xyz\[3\])

Encodes a normal vector as a uint32 suitable for storage in the udNormal attribute field

| Parameter | Description |
|-----------|-------------|
| `pEncoded` | The pointer to store the result of encoding the normal in |
| `xyz` | An array representing the 3 components of the vector to be encoded. The vector must be normalised |

**Returns:** A [udError](udError.md) value based on the result of encoding the normal and writing it to pEncoded

### enum [udError](udError.md) udAttributeSet_DecodeNormal(uint32_t encoded, float xyz\[3\])

Decodes a normal vector as a uint32 to an array of 3 floats

| Parameter | Description |
|-----------|-------------|
| `encoded` | The encoded normal to be decoded |
| `xyz` | An array representing the 3 components of the decoded vector to be written to |

**Returns:** A [udError](udError.md) value indicating the success of the operation

### enum [udError](udError.md) udAttributeSet_GenerateAttributeSetCopyRuns(struct udAttributeSetCopyRuns \*pCopy, const struct udAttributeSet \*pTarget, const struct udAttributeSet \*pSource)

Generate a set of instructions mapping between byte arrays representing two attribute sets

| Parameter | Description |
|-----------|-------------|
| `pCopy` | a pointer to the udAttributeSetCopyRuns objects to be oppulated |
| `xyz` | An array representing the 3 components of the decoded vector to be written to |

**Returns:** A [udError](udError.md) value indicating the success of the operation


## Structs

### struct udAttributeDescriptor

Describes the contents of an attribute stream including its size, type and how it gets blended in LOD layers

| Field | Type | Description |
|-------|------|-------------|
| `typeInfo` | `enum udAttributeTypeInfo` | This contains information about the type. |
| `blendType` | `enum udAttributeBlendType` | Which blend type this attribute is using. |
| `name[64]` | `char` | Name of the attibute. |
| `prefix[16]` | `char` | Value prefix for display. |
| `suffix[16]` | `char` | Value suffix for display. |
| `histogramSize` | `uint16_t` | Size of histogram data, currently only 0 and 64 are valid values. |
| `rangeMaskSize` | `uint8_t` | Size in bytes of range mask data to keep for this attribute, currently only 1, 2, 4, and 8 are valid values. |

### struct udAttributeSet

Provides a set a attributes and includes an optimized lookup for standard types

| Field | Type | Description |
|-------|------|-------------|
| `content` | `enum udStdAttributeContent` | Which standard attributes are available (used to optimize lookups internally), they still appear in the descriptors. |
| `count` | `uint32_t` | How many udAttributeDescriptor objects are used in pDescriptors. |
| `allocated` | `uint32_t` | How many udAttributeDescriptor objects are allocated to be used in pDescriptors. |
| `pDescriptors` | `struct udAttributeDescriptor \*` | this contains the actual information on the attributes |

### struct udAttributeSetCopyRuns

A structure of “instruction” chunks to copy from one attribute set to another For example if source has color, intensity, custom1 and custom2, and the destination had color, classification and custom2, udAttributeSet_GetTansforms would provide an array of chunks to define the memcpy/memset’s required for color and custom2 In this example incomplete will be set to true to indicate at least one element is not written to in the copy instructions, so the entire structure should be initialised to zero beforehand (much simpler and potentially faster than trying to memset individual elements)

| Field | Type | Description |
|-------|------|-------------|
| `len` | `uint32_t` | the number of copy instructions stored |
| `incomplete` | `uint32_t` | If true, not all the attributes are present so memset target to zero beforehand. |
| `sourceOffset` | `uint32_t` | offset of the attribute in the source as returned by the udAttributeSet_GetOffset\* family of functions |
| `targetOffset` | `uint32_t` | offset of the attribute in the destination as returned by the udAttributeSet_GetOffset\* family of functions |
| `size` | `uint32_t` | size of the attribute in bytes |
| `(uint32_t)udAttributeSet_MaxDescriptors]` | `struct udAttributeSetCopyRuns::[anonymous] chunks(uint32_t)[udSA_Count +` | array of copy instructions |
