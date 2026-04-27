# udGeometry

The **udGeometry** object provides an interface to filter Nuclideon Unlimited Detail models using geometric filters. 

## Typedefs

### typedef uint32_t udGeometryCrc(const struct udGeometry \*pGeometry)

Optional function to return a crc of ADDITIONAL data outside the structure, such as pointers in a CSG/Inverse type etc. 

### typedef void udGeometryDeinit(struct udGeometry \*pGeometry)

This sets up pFilterOut by doing the pMatrix transform on pFilterIn (which isn’t modified)- pFilterOut needs to be deinited after this. 

## Enums

### enum udGeometryType

The currently supported geometry types 

*Values:*

| Value | Description |
|-------|-------------|
| `udGT_Inverse` | An inversion filter; flips the udGeometryTestResult of the child udGeometry node. |
| `udGT_CircleXY` | A 2D Circle with an infinite Z value. |
| `udGT_RectangleXY` | A 2D Rectangle with an infinite Z value. |
| `udGT_PolygonXY` | A 2D Polygon with rotation (quaternion) to define the up of the polygon. |
| `udGT_PolygonPerspective` | A 2D polygon with a perspective projection to the screen plane. |
| `udGT_Capsule` | A line with a radius from the line; forming hemispherical caps at the end of the line. |
| `udGT_Sphere` | A radius from a point. |
| `udGT_HalfSpace` | A binary space partition allowing 1 side of a plane. |
| `udGT_AABB` | An axis aligned box; Use with caution. OBB while less performant correctly handles transforms. |
| `udGT_OBB` | An oriented bounding box using half size and orientation. |
| `udGT_CSG` | A constructed solid geometry that uses a udGeometryCSGOperation to join to child udGeometry nodes. |
| `udGT_Attribute` | Filter based on attribute values (automatic pass if no attribute information passed to test function). |
| `udGT_Count` | Count helper value to iterate this enum. |

### enum udGeometryComparator

The currently supported geometry comparator types (used in attribute filtering) 

*Values:*

| Value | Description |
|-------|-------------|
| `udGC_EQ` | Equal, param is tolerance (0 = none). |
| `udGC_NE` | Not equal, param is tolerance (0 = none). |
| `udGC_GT` | Greater than, param is range limit (0 = none). |
| `udGC_GE` | Greater than or Equal, param is range limit (0 = none). |
| `udGC_LT` | Less rhan, param is range limit (0 = none). |
| `udGC_LE` | Less than or equal, param is range limit (0 = none). |
| `udGC_AND_ANY` | Bitwise AND, true if value AND comparands != 0, param is unused (should be zero). |
| `udGC_AND_ALL` | Bitwise AND, true if value AND comparands == comparand, param is unused (should be zero). |

### enum udGeometryVoxelNodeFlags

*Values:*

| Value | Description |
|-------|-------------|
| `udGVNF_None` | Default no flags present. |
| `udGVNF_RenderLeaf` | The voxel is either a leaf or being rendered as a leaf. |

### enum udGeometryCSGOperation

The Constructive Solid Geometry operations 

*Values:*

| Value | Description |
|-------|-------------|
| `udGCSGO_Union` | A union CSG operation; any point matching the one or the other geometry (OR operation). |
| `udGCSGO_Difference` | A subtractive CSG operation; any point in the first geometry but not matching the second geometry (XOR operation). |
| `udGCSGO_Intersection` | An intersection CSG operation; any point that matches both geometries (AND operation). |

### enum udGeometryTestResult

The results of a geometry test 

*Values:*

| Value | Description |
|-------|-------------|
| `udGTR_Reject` | The node is either totally outside of the geometry filter OR fails attribute filter. |
| `udGTR_Accept` | The node is both totally inside of the geometry AND fully matches attribute filter (and no further tests are required). |
| `udGTR_Partial` | The node is partiall filtered, should be accepted but child nodes must be re-tested (eg overlapping the boundary of the geometry). |
| `udGTR_CompletelyOutside` |  |
| `udGTR_CompletelyInside` |  |
| `udGTR_PartiallyOverlap` |  |

## Functions

### enum udGeometryTestResult udGeometryTestFunc(const struct udGeometry \*pGeometry, const struct udGeometryVoxelNode \*pVoxel)

The function that will be called for each node until the node is either inside or outside of the geometry. 

### enum [udError](udError.md) udGeometryTransform(const struct udGeometry \*pFilterIn, struct udGeometry \*pFilterOut, const udDouble4x4 \*pMatrix)

This sets up pFilterOut by doing the pMatrix transform on pFilterIn (which isn’t modified)- pFilterOut needs to be deinited after this. 

### enum [udError](udError.md) udGeometry_InitInverse(struct udGeometry \*pGeometry, const struct udGeometry \*pSource)

Helper to initialise a geometry that simply inverts another primitive (CompletelyOutside <-> CompletelyInside) 

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `pSource` | The Geometry to inverse |

### enum [udError](udError.md) udGeometry_InitCircleXY(struct udGeometry \*pGeometry, const udDouble2 centre, double radius)

Helper to initialise a 2D circle extended to infinity in Z (elevation) 

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `centre` | The centre of the Circle |
| `radius` | The radius of the circle |

### enum [udError](udError.md) udGeometry_InitRectangleXY(struct udGeometry \*pGeometry, const udDouble2 point1, const udDouble2 point2)

Helper to initialise a 2D rectangle extended to infinity in Z (elevation) 

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `point1` | The first point to define a rectangle |
| `point2` | The second point to define a rectangle |

### enum [udError](udError.md) udGeometry_InitPolygonXY(struct udGeometry \*pGeometry, const udDouble3 \*pXYCoords, uint32_t count, const udDouble3 polygonNomal)

Helper to initialise a Polygon shape extened to infinity along a direction 

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `pXYCoords` | the list of 2D positions defining the polygon |
| `count` | the number of points in pXYCoords list |
| `polygonNormal` | the normal vector to the polygon |

### enum [udError](udError.md) udGeometry_InitPolygonPerspective(struct udGeometry \*pGeometry, const udDouble2 \*pXYCoords, uint32_t count, udDouble4x4 projectionMatrix, udDouble4x4 cameraMatrix, double nearPlaneOffset, double farPlaneOffset)

Helper to initialise a Polygon shape extended to infinity with a perspective projection 

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `pXYCoords` | the list of 2D positions defining the polygon |
| `count` | the number of points in pXYCoords list |
| `projectionMatrix` | The model to world projection matrix |
| `cameraMatrix` | The projection matrix of world to screen |
| `nearPlaneOffset` | The offset off the near plane to detect if voxel is visible by the camera |
| `farPlaneOffset` | The offset off the far plane to detect if voxel is visible by the camera |

### enum [udError](udError.md) udGeometry_InitCSG(struct udGeometry \*pGeometry, const struct udGeometry \*pGeometry1, const struct udGeometry \*pGeometry2, enum udGeometryCSGOperation function)

Helper to initialise a CSG shape 

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `pGeometry1` | First Geometry |
| `pGeometry2` | Second Geometry |
| `function` | the function to apply to these 2 geometries (Union, Difference, Intersection) |

### enum [udError](udError.md) udGeometry_InitHalfSpace(struct udGeometry \*pGeometry, const udDouble3 point, const udDouble3 normal)

Helper to initialise a plane extended to infinity in the direction of its normal 

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `point` | The first point to define the space |
| `normal` | The normal vector of the defined space |

### enum [udError](udError.md) udGeometry_InitCapsule(struct udGeometry \*pGeometry, const udDouble3 point1, const udDouble3 point2, double radius)

Helper to initialise a Capsule 

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `point1` | First point to define a capsule at this position |
| `point2` | Second point to define a capsule |
| `radius` | Radius of the capsule |

### enum [udError](udError.md) udGeometry_InitSphere(struct udGeometry \*pGeometry, const udDouble3 center, double radius)

Helper to initialise a Sphere 

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `center` | The center of the Sphere |
| `radius` | The radius of the sphere |

### enum [udError](udError.md) udGeometry_InitAABBFromMinMax(struct udGeometry \*pGeometry, const udDouble3 point1, const udDouble3 point2)

Helper to initialise an Axis Aligned Box using the min and max point 

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `point1` | First point to define a box starting at this position |
| `point2` | Last point to define a box ending at this position |

### enum [udError](udError.md) udGeometry_InitAABBFromCentreExtents(struct udGeometry \*pGeometry, const udDouble3 centre, const udDouble3 extents)

Helper to initialise an Axis Aligned Box using center and extents 

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `centre` | The centre of the Axis Aligned Box |
| `extents` | The dimension of the Axis Aligned Box |

### enum [udError](udError.md) udGeometry_InitOBB(struct udGeometry \*pGeometry, const udDouble3 centerPoint, const udDouble3 extents, const udDouble3 rotations)

Helper to initialise an arbitrarily aligned three dimensional box, centered at centerPoint, rotated about the center

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `centerPoint` | The centre of the box |
| `extents` | The distances from the center to the sides (half the size of the dimensions of the box) |
| `rotations` | The rotations of the box in radians about x,y,z |

### enum [udError](udError.md) udGeometry_InitAttributeInt64(struct udGeometry \*pGeometry, enum udGeometryComparator comp, int64_t value, int64_t tolerance, enum [udStdAttribute](udAttributes.md) attr, const struct [udAttributeDescriptor](udAttributes.md) \*pDesc)

Helper to initialise an attribute equality filter, testing the attribute for equality with integer based comparitors

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `comp` | The type of comparison, for example udGC_EQ for equality comparison |
| `value` | Value to compare node’s attribute with |
| `tolerance` | For udGC_EQ comparisons, values +/- the tolerance is considered a match (0.0 for exact match) |
| `attr` | Attribute from standard attribute set (ignored if pDesc is non-null, use udSA_Count) |
| `pDesc` | A descriptor for testing non-standard attributes (pass null if using a standard attribute) |

### enum [udError](udError.md) udGeometry_InitAttributeFloat64(struct udGeometry \*pGeometry, enum udGeometryComparator comp, double value, double tolerance, enum [udStdAttribute](udAttributes.md) attr, const struct [udAttributeDescriptor](udAttributes.md) \*pDesc)

Helper to initialise an attribute equality filter, testing the attribute for equality with float based comparitors

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The preallocated udGeometry to init |
| `comp` | The type of comparison, for example udGC_EQ for equality comparison |
| `value` | Value to compare node’s attribute with |
| `tolerance` | For udGC_EQ comparisons, values +/- the tolerance is considered a match (0.0 for exact match) |
| `attr` | Attribute from standard attribute set (ignored if pDesc is non-null, use udSA_Count) |
| `pDesc` | A descriptor for testing non-standard attributes (pass null if using a standard attribute) |

### void udGeometry_Deinit(struct udGeometry \*pGeometry)

This cleans up internal allocations

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | The geometry to deinitialise |

### uint32_t udGeometry_CRC(const struct udGeometry \*pGeometry)

Return a crc of the geometry (and sub-geometry in the case of CSG etc)

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | Pointer to geometry |

**Returns:** The CRC of the geometry, or zero if pGeometry is null

### enum [udError](udError.md) udGeometry_HasType(const struct udGeometry \*pGeometry, enum udGeometryType type)

Return true if the geometry (or sub-geometry in the case of CSG etc) contains the given type

| Parameter | Description |
|-----------|-------------|
| `pGeometry` | Pointer to geometry |
| `type` | The type of geometry to test for |

**Returns:** udE_Success if the type is present in the geometry, otherwise udE_NotFound

### enum [udError](udError.md) udGeometry_Create(struct udGeometry \*\*ppGeometry)

Helper to create a pointer to an allocated udGeometry struct. This is a convenience for wrapping libraries that do not need or have a concept of the underlying object It is NOT recommended to use this function in applications where creating a udGeometry struct directly is possible (either using an allocation or on stack)

| Parameter | Description |
|-----------|-------------|
| `ppGeometry` | Pointer to memory location with which to return the allocated struct |

### void udGeometry_Destroy(struct udGeometry \*\*ppGeometry)

Free the struct allocated by udGeometry_Create udGeometry_DeInit should be called on the struct first before calling this function. Calling this function on a udGeometry struct that was not allocated using udGeometry_Create may result in a crash

| Parameter | Description |
|-----------|-------------|
| `ppGeometry` | Pointer to memory location of struct to free |


## Structs

### struct udGeometryVoxelNode

The geometric representation of a Node in a Unlimited Detail Model.

| Field | Type | Description |
|-------|------|-------------|
| `minPos` | `udDouble3` | The Bottom, Left, Front corner of the voxel (closest to the origin). |
| `childSize` | `double` | The half size of the voxel (which is the same size as this voxels children). |
| `pNode` | `const struct udNode \*` | Optional pointer to the node for testing attributes. |
| `childDepth` | `uint8_t` | Optional depth down the tree value for additional context (0=unspecified, 1=root etc). |
| `flags` | `uint8_t` | Optional flags, set from enum udGeometryVoxelNodeFlags. |

### struct udGeometryCircleXY

The geometric representation of a Circle.

| Field | Type | Description |
|-------|------|-------------|
| `centre` | `udDouble2` | The centre of the circle. |
| `radius` | `double` | The radius of the circle. |

### struct udGeometryRectangleXY

The geometric representation of a Rectangle.

| Field | Type | Description |
|-------|------|-------------|
| `minPoint` | `udDouble2` | The lowest point of the rectangle. |
| `maxPoint` | `udDouble2` | The highest point of the rectangle. |

### struct udGeometryPolygonXYZ

The geometric representation of a Polygon.

| Field | Type | Description |
|-------|------|-------------|
| `pointCount` | `uint32_t` | The number of points defining the polygon. |
| `pointsList` | `udDouble3 \*` | The list of points defining the polygon. |
| `polygonNormal` | `udDouble3` | The polygon normal. |
| `rotationQuat` | `udDoubleQuat` | The rotation of the polygon compare to Z axis. |

### struct udGeometryPolygonPerspective

The geometric representation of a Polygon with a perspective projection.

| Field | Type | Description |
|-------|------|-------------|
| `pointCount` | `uint32_t` | The number of points defining the polygon. |
| `pointsList` | `udDouble3 \*` | The list of points defining the polygon. |
| `rotationQuat` | `udDouble4` | The rotation of the polygon. |
| `worldToScreen` | `udDouble4x4` | The matrix to project from World space to Screen space. |
| `projectionMatrix` | `udDouble4x4` | The matrix to project the points of the polygon. |
| `cameraMatrix` | `udDouble4x4` | The camera matrix. |
| `normRight` | `udDouble3` | The normal on the right of the plane. |
| `normLeft` | `udDouble3` | The normal on the left of the plane. |
| `normTop` | `udDouble3` | The normal on the top of the plane. |
| `normBottom` | `udDouble3` | The normal on the bottom of the plane. |
| `nearPlane` | `double` | the near plane distance |
| `farPlane` | `double` | The far plane distance. |

### struct udGeometryCapsule

Stores the properties of a geometric capsule

| Field | Type | Description |
|-------|------|-------------|
| `point1` | `udDouble3` | One end of the line. |
| `point2` | `udDouble3` | The other end of the line. |
| `radius` | `double` | The radius around the line. |
| `axisVector` | `udDouble3` | The vector of the line. |
| `length` | `double` | The length of the line. |

### struct udGeometrySphere

Stores the properties of a geometric sphere

| Field | Type | Description |
|-------|------|-------------|
| `center` | `udDouble3` | The center of the sphere. |
| `radius` | `double` | The radius of the sphere. |

### struct udGeometryHalfSpace

Stores the properties of a geometric half space

| Field | Type | Description |
|-------|------|-------------|
| `plane` | `udDouble4` | The parameters to define the plane (normal XYZ and offset from origin). |

### struct udGeometryAABB

Stores the properties of a geometric axis aligned bounding box

| Field | Type | Description |
|-------|------|-------------|
| `center` | `udDouble3` | The point at the center of the AABB. |
| `extents` | `udDouble3` | The half space size of the AABB. |

### struct udGeometryOBB

Stores the properties of a geometric axis aligned bounding box (extending AABB)

| Field | Type | Description |
|-------|------|-------------|
| `center` | `udDouble3` | The point at the center of the AABB. |
| `extents` | `udDouble3` | The half space size of the AABB. |
| `rotationMatrix` | `udDouble4x4` | The transform that represents the rotation. |

### struct udGeometryInverse

Stores the properties of an inversed udGeometry node

| Field | Type | Description |
|-------|------|-------------|
| `pInverseOf` | `const struct udGeometry \*` | The inverse geometry. |
| `owns` | `int` | If non-zero pInverseOf is owned by this need (and will need to be cleaned up). |

### struct udGeometryCSG

Stores the properties of a CSG udGeometry node

| Field | Type | Description |
|-------|------|-------------|
| `pFirst` | `const struct udGeometry \*` | The first geometry. |
| `pSecond` | `const struct udGeometry \*` | The second geometry. |
| `operation` | `enum udGeometryCSGOperation` | The operation applied to the 2 geometries. |
| `owns` | `int` | non zero if it owns both children |

### struct udGeometryAttribute

Stores the properties of a attribute udGeometry node

| Field | Type | Description |
|-------|------|-------------|
| `attr` | `enum [udStdAttribute](udAttributes.md)` | For custom attributes this should be udSA_Count, otherwise the appropriate enum value. |
| `desc` | `struct [udAttributeDescriptor](udAttributes.md)` | Attribute descriptor. |
| `u` | `uint64_t` | Any unsigned integer typed values. |
| `i` | `int64_t` | Any signed integer typed values. |
| `f32` | `float` | Any float typed values. |
| `f64` | `double` | Any double-precision typed values. |
| `value` | `union udGeometryAttribute::[anonymous]` | The value for the comparison, with the expected type derived from the type in the descriptor. |
| `param` | `union udGeometryAttribute::[anonymous]` | Optional comparitor-specific parameter, such as the tolerance when using the EQ operator. Default to zero. |
| `comp` | `enum udGeometryComparator` | The comparison operator. |

### struct udGeometry

Stores the information required for all udGeometry shapes 

> [!WARNING]
> This struct will change drastically as udSDK shifts to programable query filters

| Field | Type | Description |
|-------|------|-------------|
| `pTestFunc` | `udGeometryTestFunc \*` | The function to call to test the geometry. |
| `pTransformFunc` | `udGeometryTransform \*` | The function to transform this geometry using a linear matrix. |
| `pExtraCRCFunc` | `udGeometryCrc \*` | When non-null, the function to perform crc calculation on ADDITIONAL data outside the base structure that represents the geometry (0 is valid for no extra data). |
| `pDeinitFunc` | `udGeometryDeinit \*` | The function that is called when this is cleaned up. |
| `inverse` | `struct udGeometryInverse` |  |
| `circleXY` | `struct udGeometryCircleXY` |  |
| `rectangleXY` | `struct udGeometryRectangleXY` |  |
| `polygonXYZ` | `struct udGeometryPolygonXYZ` |  |
| `polygonPerspective` | `struct udGeometryPolygonPerspective` |  |
| `capsule` | `struct udGeometryCapsule` |  |
| `sphere` | `struct udGeometrySphere` |  |
| `halfSpace` | `struct udGeometryHalfSpace` |  |
| `aabb` | `struct udGeometryAABB` |  |
| `obb` | `struct udGeometryOBB` |  |
| `csg` | `struct udGeometryCSG` |  |
| `attribute` | `struct udGeometryAttribute` |  |
| `data` | `union udGeometry::[anonymous]` | The geometry used. |
| `type` | `enum udGeometryType` | The type of the geometry for internal verification. |
