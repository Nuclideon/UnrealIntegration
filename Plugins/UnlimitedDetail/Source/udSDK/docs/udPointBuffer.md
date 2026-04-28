# udPointBuffer

The udPointBuffer object provides an interface to add or get points from udPointClouds 

## Functions

### enum [udError](udError.md) udPointBufferIndices_Create(struct udPointBufferIndices \*\*ppIndices, uint32_t numIndices)

Create a point buffer indices object

> [!NOTE]
> The application should call **udPointBufferIndices_Destroy** with `ppIndices` to destroy the point buffer indices object once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `ppIndices` | The pointer pointer of the udPointBufferIndices. This will allocate an instance of `udPointBufferIndices` into `ppIndices` |
| `numIndices` | The maximum number of indices that this object will contain (these are preallocated to avoid allocations later) |

**Returns:** A [udError](udError.md) value based on creation status.

### enum [udError](udError.md) udPointBufferIndices_Destroy(struct udPointBufferIndices \*\*ppIndices)

Destroys the udPointBufferIndices.

> [!NOTE]
> The value of `ppIndices` will be set to `NULL`.

| Parameter | Description |
|-----------|-------------|
| `ppIndices` | The pointer pointer of the udPointBufferIndices. This will deallocate any memory used. |

**Returns:** A [udError](udError.md) value based on the result of the destruction.

### enum [udError](udError.md) udPointBufferF64_Create(struct udPointBufferF64 \*\*ppBuffer, uint32_t maxPoints, struct [udAttributeSet](udAttributes.md) \*pAttributes)

Create a 64bit floating point, point buffer object

> [!NOTE]
> The application should call **udPointBufferF64_Destroy** with `ppBuffer` to destroy the point buffer object once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `ppBuffer` | The pointer pointer of the udPointBufferF64. This will allocate an instance of `udPointBufferF64` into `ppBuffer`. |
| `maxPoints` | The maximum number of points that this buffer will contain (these are preallocated to avoid allocations later) |
| `pAttributes` | The pointer to the [udAttributeSet](udAttributes.md) containing information on the attributes that will be available in this point buffer; NULL will have no attributes. An internal copy is made of this attribute set. |

**Returns:** A [udError](udError.md) value based on creation status.

### enum [udError](udError.md) udPointBufferF64_Destroy(struct udPointBufferF64 \*\*ppBuffer)

Destroys the udPointBufferF64.

> [!NOTE]
> The value of `ppBuffer` will be set to `NULL`.

| Parameter | Description |
|-----------|-------------|
| `ppBuffer` | The pointer pointer of the ppBuffer. This will deallocate any memory used. |

**Returns:** A [udError](udError.md) value based on the result of the destruction.

### enum [udError](udError.md) udPointBufferI64_Create(struct udPointBufferI64 \*\*ppBuffer, uint32_t maxPoints, struct [udAttributeSet](udAttributes.md) \*pAttributes)

Create a 64bit integer, point buffer object

> [!NOTE]
> The application should call **udPointBufferI64_Destroy** with `ppBuffer` to destroy the point buffer object once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `ppBuffer` | The pointer pointer of the udPointBufferI64. This will allocate an instance of `udPointBufferI64` into `ppBuffer`. |
| `maxPoints` | The maximum number of points that this buffer will contain (these are preallocated to avoid allocations later) |
| `pAttributes` | The pointer to the [udAttributeSet](udAttributes.md) containing information on the attributes that will be available in this point buffer; NULL will have no attributes. An internal copy is made of this attribute set. |

**Returns:** A [udError](udError.md) value based on creation status.

### enum [udError](udError.md) udPointBufferI64_Destroy(struct udPointBufferI64 \*\*ppBuffer)

Destroys the udPointBufferI64.

> [!NOTE]
> The value of `ppBuffer` will be set to `NULL`.

| Parameter | Description |
|-----------|-------------|
| `ppBuffer` | The pointer pointer of the ppBuffer. This will deallocate any memory used. |

**Returns:** A [udError](udError.md) value based on the result of the destruction.

### enum [udError](udError.md) udPointBufferU64_Create(struct udPointBufferU64 \*\*ppBuffer, uint32_t maxPoints, struct [udAttributeSet](udAttributes.md) \*pAttributes)

Create a 64bit unsigned integer, point buffer object

> [!NOTE]
> The application should call **udPointBufferU64_Destroy** with `ppBuffer` to destroy the point buffer object once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `ppBuffer` | The pointer pointer of the udPointBufferU64. This will allocate an instance of `udPointBufferU64` into `ppBuffer`. |
| `maxPoints` | The maximum number of points that this buffer will contain (these are preallocated to avoid allocations later) |
| `pAttributes` | The pointer to the [udAttributeSet](udAttributes.md) containing information on the attributes that will be available in this point buffer; NULL will have no attributes. An internal copy is made of this attribute set. |

**Returns:** A [udError](udError.md) value based on creation status.

### enum [udError](udError.md) udPointBufferU64_Destroy(struct udPointBufferU64 \*\*ppBuffer)

Destroys the udPointBufferU64.

> [!NOTE]
> The value of `ppBuffer` will be set to `NULL`.

| Parameter | Description |
|-----------|-------------|
| `ppBuffer` | The pointer pointer of the ppBuffer. This will deallocate any memory used. |

**Returns:** A [udError](udError.md) value based on the result of the destruction.


## Structs

### struct udPointBufferIndices

Stores a set of indices to be used with a **udPointBuffer**

| Field | Type | Description |
|-------|------|-------------|
| `count` | `uint32_t` | Total number of indices currently contained in this object. |
| `capacity` | `uint32_t` | Total number of indices that can fit in this object. |
| `indices[1]` | `uint32_t` | Array of indices, real length of the array is stored in capacity. |

### struct udPointBufferF64

Stores a set of points and their attributes that have positions as double (64bit float) values

| Field | Type | Description |
|-------|------|-------------|
| `pPositions` | `double \*` | Flat array of XYZ positions in the format XYZXYZXYZXYZXYZXYZXYZ… |
| `pAttributes` | `uint8_t \*` | Byte array of attribute data ordered as specified in `attributes`. |
| `pRangeMaskData` | `uint8_t \*` | Array of interleaved rangemask blobs, each of rangeMaskStride size, with the array being pointCount/pointsAllocated length/reservation. |
| `rangeMaskPresent[4]` | `uint64_t` | Masks for 64,32,16 and 8 bit rangemask presence respectively. Rangemasks are ordered by size, anf sub-ordered by attribute index. |
| `attributes` | `struct [udAttributeSet](udAttributes.md)` | Information on the attributes that are available in this point buffer. |
| `attributeStride` | `uint32_t` | Total number of bytes between the start of the attibutes of one point and the first byte of the next attribute. |
| `rangeMaskStride` | `uint32_t` | Rounded/aligned stride between rangeMasks in pRangeMaskData. |
| `pointCount` | `uint32_t` | How many points are currently contained in this buffer. |
| `pointsAllocated` | `uint32_t` | Total number of points that can fit in this udPointBufferF64. |
| `\_reserved` | `uint32_t` | Reserved for internal use. |

### struct udPointBufferI64

Stores a set of points and their attributes that have positions as Int64 values

| Field | Type | Description |
|-------|------|-------------|
| `pPositions` | `int64_t \*` | Flat array of XYZ positions in the format XYZXYZXYZXYZXYZXYZXYZ… |
| `pAttributes` | `uint8_t \*` | Byte array of attribute data ordered as specified in `attributes`. |
| `pRangeMaskData` | `uint8_t \*` | Array of interleaved rangemask blobs, each of rangeMaskStride size, with the array being pointCount/pointsAllocated length/reservation. |
| `rangeMaskPresent[4]` | `uint64_t` | Masks for 64,32,16 and 8 bit rangemask presence respectively. Rangemasks are ordered by size, anf sub-ordered by attribute index. |
| `attributes` | `struct [udAttributeSet](udAttributes.md)` | Information on the attributes that are available in this point buffer. |
| `attributeStride` | `uint32_t` | Total number of bytes between the start of the attibutes of one point and the first byte of the next attribute. |
| `rangeMaskStride` | `uint32_t` | Rounded/aligned stride between rangeMasks in pRangeMaskData. |
| `pointCount` | `uint32_t` | How many points are currently contained in this buffer. |
| `pointsAllocated` | `uint32_t` | Total number of points that can fit in this udPointBufferF64. |
| `\_reserved` | `uint32_t` | Reserved for internal use. |

### struct udPointBufferU64

Stores a set of points and their attributes that have positions as UInt64 values

| Field | Type | Description |
|-------|------|-------------|
| `pPositions` | `uint64_t \*` | Flat array of XYZ positions in the format XYZXYZXYZXYZXYZXYZXYZ… |
| `pAttributes` | `uint8_t \*` | Byte array of attribute data ordered as specified in `attributes`. |
| `pRangeMaskData` | `uint8_t \*` | Array of interleaved rangemask blobs, each of rangeMaskStride size, with the array being pointCount/pointsAllocated length/reservation. |
| `rangeMaskPresent[4]` | `uint64_t` | Masks for 64,32,16 and 8 bit rangemask presence respectively. Rangemasks are ordered by size, anf sub-ordered by attribute index. |
| `attributes` | `struct [udAttributeSet](udAttributes.md)` | Information on the attributes that are available in this point buffer. |
| `attributeStride` | `uint32_t` | Total number of bytes between the start of the attibutes of one point and the first byte of the next attribute. |
| `rangeMaskStride` | `uint32_t` | Rounded/aligned stride between rangeMasks in pRangeMaskData. |
| `pointCount` | `uint32_t` | How many points are currently contained in this buffer. |
| `pointsAllocated` | `uint32_t` | Total number of points that can fit in this udPointBufferF64. |
| `\_reserved` | `uint32_t` | Reserved for internal use. |
