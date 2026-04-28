# udScene

The udScene and udSceneNode objects provide an interface for storing and syncronising geolocated projects between udSDK sessions 

> [!NOTE]
> The GeoJSON provided by this implementation is not fully compliant with RFC7946

> [!WARNING]
> Antimeridian Cutting (Section 3.1.9) and handling the poles (Secion 5.3) are not fully working in this implementation

> [!WARNING]
> This module does not currently expose the functionality to sync with the server. This will be added in a future release.

## Enums

### enum udSceneAltitudeType

*Values:*

| Value | Description |
|-------|-------------|
| `udSceneAltitudeType_Absolute` | The position is from the ellipsoid (or just ECEF). |
| `udSceneAltitudeType_Relative` | The position is relative to the terrain. |
| `udSceneAltitudeType_Clamp` | The position is clamped to the terrain. |
| `udSceneAltitudeType_Count` |  |

### enum udSceneGeometryType

These are the geometry types for nodes 

*Values:*

| Value | Description |
|-------|-------------|
| `udPGT_None` | There is no geometry associated with this node. |
| `udPGT_Point` | pCoordinates is a single 3D position |
| `udPGT_MultiPoint` | Array of udPGT_Point, pCoordinates is an array of 3D positions. |
| `udPGT_LineString` | pCoordinates is an array of 3D positions forming an open line |
| `udPGT_MultiLineString` | Array of udPGT_LineString; pCoordinates is NULL and children will be present. |
| `udPGT_Polygon` | pCoordinates will be a closed linear ring (the outside), there MAY be children that are interior as pChildren udPGT_MultiLineString items, these should be counted as islands of the external ring. |
| `udPGT_MultiPolygon` | pCoordinates is null, children will be udPGT_Polygon (which still may have internal islands) |
| `udPGT_GeometryCollection` | Array of geometries; pCoordinates is NULL and children may be present of any type. |
| `udPGT_Count` | Total number of geometry types. Used internally but can be used as an iterator max when displaying different type modes. |
| `udPGT_Internal` | Used internally when calculating other types. Do not use. |

### enum udSceneNodeType

This represents the type of data stored in the node. 

> [!NOTE]
> The `itemtypeStr` in the udSceneNode is a string version. This enum serves to simplify the reading of standard types. The the string in brackets at the end of the comment is the string.

*Values:*

| Value | Description |
|-------|-------------|
| `udPNT_Custom` | Need to check the itemtypeStr string manually. |
| `udPNT_PointCloud` | A Nuclideon Unlimited Detail Point Cloud file (“UDS”). |
| `udPNT_PointOfInterest` | A point, line or region describing a location of interest (“POI”). |
| `udPNT_Folder` | A folder of other nodes (“Folder”). |
| `udPNT_Media` | An Image, Movie, Audio file or other media object (“Media”). |
| `udPNT_Viewpoint` | An Camera Location & Orientation (“Camera”). |
| `udPNT_VisualisationSettings` | Visualisation settings (itensity, map height etc) (“VizSet”). |
| `udPNT_I3S` | An Indexed 3d Scene Layer (I3S) or Scene Layer Package (SLPK) dataset (“I3S”). |
| `udPNT_3DTiles` | A 3D tile dataset using the open-source Cesium standard format (“3DTiles”). |
| `udPNT_Water` | A region describing the location of a body of water (“Water”). |
| `udPNT_ViewShed` | A point describing where to generate a view shed from (“ViewMap”). |
| `udPNT_Polygon` | A polygon model, usually an OBJ or FBX (“Polygon”). |
| `udPNT_QueryFilter` | A query filter to be applied to all PointCloud types in the scene (“QFilter”). |
| `udPNT_Places` | A collection of places that can be grouped together at a distance (“Places”). |
| `udPNT_HeightMeasurement` | A height measurement object (“MHeight”). |
| `udPNT_GTFS` | A General Transit Feed Specification object (“GTFS”). |
| `udPNT_LassoNode` | A Lasso Selection Folder (“LNode”). |
| `udPNT_QueryGroup` | A Group of Query node being represented as one node (“QGroup”). |
| `udPNT_BasicShape` |  |
| `udPNT_XRef` | An external reference to another udScene. The target URI is stored in the node’s pURI (“XRef”). Generally either a file path or a share-code “nuclideon:scene/{sceneID}/{orgID}/{projID}” (“XRef”). |
| `udPNT_Count` | Total number of node types. Used internally but can be used as an iterator max when displaying different type modes. |

### enum udSceneXRefFlags

Flags for udSceneNode_ResolveXRef 

*Values:*

| Value | Description |
|-------|-------------|
| `udSceneXRefFlags_None` | Default behaviour: load the referenced scene synchronously and splice its children under the xref node. |

### enum udSceneUserFlag

This represents the flags for scene users 

*Values:*

| Value | Description |
|-------|-------------|
| `udSceneUserFlag_HasHead` | User has a head. |
| `udSceneUserFlag_HasAnchorAndScale` | User has a world anchor point. This usually indicates they are using a VR Cave or Table. |
| `udSceneUserFlag_LeftHand` | User has a left hand/wand. |
| `udSceneUserFlag_RightHand` | User has a right hand/wand. |

### enum udSceneLoadSource

This represents where the scene was loaded from/saved to most recently and where future calls to udScene_Save will go 

*Values:*

| Value | Description |
|-------|-------------|
| `udSceneLoadSource_Memory` | The scene source exists in memory; udScene_CreateInMemory, udScene_LoadFromMemory or udScene_SaveToMemory. |
| `udSceneLoadSource_Server` | The scene source exists from the server; udScene_CreateInServer, udScene_LoadFromServer or udScene_SaveToServer. |
| `udSceneLoadSource_URI` | The scene source exists from a file or URL; udScene_CreateInFile, udScene_LoadFromFile or udScene_SaveToFile. |
| `udSceneLoadSource_Count` | Total number of source types. Used internally but can be used as an iterator max when displaying different source types. |

## Functions

### enum [udError](udError.md) udScene_CreateInMemory(struct udContext \*pContext, struct udScene \*\*ppScene, const char \*pName)

Create an empty, local only, instance of `udScene`.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use to creae in memory |
| `ppScene` | The pointer pointer of the udScene. This will allocate an instance of udScene into `ppScene`. |
| `pName` | The name of the scene, this will be the name of the root item. |

**Returns:** A [udError](udError.md) value based on the result of the project creation.

### enum [udError](udError.md) udScene_CreateInFile(struct udContext \*pContext, struct udScene \*\*ppScene, const char \*pName, const char \*pFilename)

Create an empty, local only, instance of `udScene`.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use to create ina file |
| `ppScene` | The pointer pointer of the udScene. This will allocate an instance of udScene into `ppScene`. |
| `pName` | The name of the project, this will be the name of the root item. |
| `pFilename` | The path to create the project at. |

**Returns:** A [udError](udError.md) value based on the result of the project creation.

### enum [udError](udError.md) udScene_CreateInServer(struct udContext \*pContext, struct udScene \*\*ppScene, const char \*pName, const char \*pOrgID, const char \*pProjID)

Create an empty project in the server and the local instance of `udScene`.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use to load the project, read/write permissions will be based on the current session. |
| `ppScene` | The pointer pointer of the udScene. This will allocate an instance of udScene into `ppScene`. |
| `pName` | The name of the project, this will be the name of the root item. |
| `pOrgID` | The ID for the udCloud organisation that the scene will belong to |
| `pProjectID` | The ID for the udCloud project that the scene will belong to |

**Returns:** A [udError](udError.md) value based on the result of the project creation.

### enum [udError](udError.md) udScene_LoadFromMemory(struct udContext \*pContext, struct udScene \*\*ppScene, const char \*pGeoJSON)

Create a local only instance of `udScene` filled in with the contents of a GeoJSON string.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use to load from memory |
| `ppScene` | The pointer pointer of the udScene. This will allocate an instance of udScene into `ppScene`. |
| `pGeoJSON` | The GeoJSON string of the project, this will be unpacked into udSceneNode items. |

**Returns:** A [udError](udError.md) value based on the result of the project creation.

### enum [udError](udError.md) udScene_LoadFromFile(struct udContext \*pContext, struct udScene \*\*ppScene, const char \*pFilename)

Create a local only instance of `udScene` filled in with the contents of the specified project file.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use to load from a file |
| `ppScene` | The pointer pointer of the udScene. This will allocate an instance of udScene into `ppScene`. |
| `pFilename` | The project file URL. |

**Returns:** A [udError](udError.md) value based on the result of the project creation.

### enum [udError](udError.md) udScene_LoadFromServer(struct udContext \*pContext, struct udScene \*\*ppScene, const char \*pOrgID, const char \*pProjID, const char \*pSceneID, [udProgressCallback](udError.md) \*pProgressCallback, void \*pProgressUserData)

Create a local instance of `udScene` filled in from the server.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use to load the scene, read/write permissions will be based on the current session. |
| `ppScene` | The pointer pointer of the udScene. This will allocate an instance of udScene into `ppScene`. |
| `pOrgID` | The ID for the organisation in udCloud that the scene belongs to |
| `pProjID` | The ID for the project in udCloud that the scene belongs to |
| `pSceneID` | The ID for the scene that is being requested |
| `pProgressCallback` | A function callback when there are progress updates |
| `pProgressUserData` | A pointer that will be passed to the pProgressCallback |

**Returns:** A [udError](udError.md) value based on the result of the project creation.

### enum [udError](udError.md) udScene_MergeScenes(struct udContext \*pContext, struct udScene \*pScene, struct udScene \*pSceneToMerge)

Update a local instance of `udScene` by merging elements from another `udScene`.

> [!NOTE]
> pSceneToMerge will be empty after this operation.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use to load the scene, read/write permissions will be based on the current session. |
| `pScene` | The pointer of the udScene to update. |
| `pSceneToMerge` | The pointer of the udScene to merge its elements into previous udScene |

**Returns:** A [udError](udError.md) value based on the result of the merge.

### enum [udError](udError.md) udScene_Release(struct udScene \*\*ppScene)

Destroy the instance of the scene.

> [!WARNING]
> The pUserData item should be already released from every node before calling this.

| Parameter | Description |
|-----------|-------------|
| `ppScene` | The pointer pointer of the udScene. This will deallocate the instance of the scene as well as destroying all nodes. |

**Returns:** A [udError](udError.md) value based on the result of the scene destruction.

### enum [udError](udError.md) udScene_Save(struct udScene \*pScene)

Export a scene to where it was loaded from (server or file).

| Parameter | Description |
|-----------|-------------|
| `pScene` | The pointer to a valid udScene that will saved. This will fail immediately for scenes loaded from memory |

**Returns:** A [udError](udError.md) value based on the result of the scene save

### enum [udError](udError.md) udScene_Update(struct udScene \*pScene, struct udSceneUpdateInfo \*pUpdateInfo)

Update a scene to where it was loaded from (server or file).

| Parameter | Description |
|-----------|-------------|
| `pScene` | The pointer to a valid udScene that will saved. This will fail immediately for scenes loaded from memory |
| `pUpdateInfo` | The data that would be updated |

**Returns:** A [udError](udError.md) value based on the result of the scene save

### enum [udError](udError.md) udScene_SaveToMemory(struct udContext \*pContext, struct udScene \*pScene, const char \*\*ppMemory)

Export a scene to a GeoJSON string in memory.

> [!WARNING]
> The memory is stored in the udScene and subsequent calls will destroy older versions, the buffer is released when the scene is released.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use to save the scene to memory. |
| `pScene` | The pointer to a valid udScene that will be exported as GeoJSON. |
| `ppMemory` | The pointer pointer to a string that will contain the exported GeoJSON. |

**Returns:** A [udError](udError.md) value based on the result of the scene export.

### enum [udError](udError.md) udScene_SaveToServer(struct udContext \*pContext, struct udScene \*pScene, const char \*pOrgID, const char \*pProjID)

Create an scene in the server from an existing udScene

> [!NOTE]
> pScene will point to the newly created scene if this is successful

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use to upload the scene, write permissions will be based on the current session. |
| `pScene` | The udScene to upload. |
| `pOrgID` | The ID for the udCloud organisation that the scene will belong to |
| `pProjectID` | The ID for the udCloud project that the scene will belong to |

**Returns:** A [udError](udError.md) value based on the result of the scene creation.

### enum [udError](udError.md) udScene_SaveToFile(struct udContext \*pContext, struct udScene \*pScene, const char \*pPath)

Create an scene in the server from an existing udScene

> [!NOTE]
> pScene will point to the newly created file if this is successful

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use to save the scene to file. |
| `pScene` | The udScene to save out. |
| `pPath` | The new path to save the scene to |

**Returns:** A [udError](udError.md) value based on the result of the scene creation.

### enum [udError](udError.md) udScene_GetSceneRoot(struct udScene \*pScene, struct udSceneNode \*\*ppRootNode)

Get the scene root node.

> [!NOTE]
> This node will always have itemtype of type udPNT_Folder and cannot (and will not) have sibling nodes.

> [!NOTE]
> The name of the scene is the name of the returned root node.

| Parameter | Description |
|-----------|-------------|
| `pScene` | The pointer to a valid udScene. |
| `ppRootNode` | The pointer pointer to a node that will contain the node. The node ownership still belongs to the pScene. |

**Returns:** A [udError](udError.md) value based on the result of getting the root node.

### enum [udError](udError.md) udScene_GetSceneID(struct udScene \*pScene, const char \*\*ppSceneID)

Get the scene ID (for server projects).

> [!NOTE]
> Returns udE_NotFound for non-server projects

| Parameter | Description |
|-----------|-------------|
| `pScene` | The pointer to a valid udScene. |
| `ppSceneID` | The pointer pointer to memory that will contain the scene ID. The ownership still belongs to the pScene. |

**Returns:** A [udError](udError.md) value based on the result of getting the root node.

### enum [udError](udError.md) udScene_HasUnsavedChanges(struct udScene \*pScene)

Get the state of unsaved local changes

| Parameter | Description |
|-----------|-------------|
| `pScene` | The pointer to a valid udScene. |

**Returns:** udE_Success if there a unsaved changes, udE_NotFound when no local changes exist and other [udError](udError.md) values for errors

### enum [udError](udError.md) udScene_GetLoadSource(struct udScene \*pScene, enum udSceneLoadSource \*pSource)

Gets the current source of a given udScene

| Parameter | Description |
|-----------|-------------|
| `pScene` | The pointer to a valid udScene. |
| `pSource` | The pointer to memory to write the source of pScene to |

**Returns:** udE_Success if wrote source, error otherwise

### enum [udError](udError.md) udSceneNode_Create(struct udSceneNode \*\*ppNode, struct udSceneNode \*pParent, const char \*pType, const char \*pName, const char \*pURI, void \*pUserData)

 Create a node in a project. The owning scene is derived from pParent.

> [!NOTE]
> The udSceneNode_\* mutation APIs below derive the owning scene from the node (or parent node) - so a node that was spliced in via udSceneNode_ResolveXRef correctly routes mutations to its sub-scene without the caller having to pick between the host and sub-scene pointer. The node must be attached to a scene.

| Parameter | Description |
|-----------|-------------|
| `ppNode` | A pointer pointer to the node that will be created. This can be NULL if getting the node back isn’t required. |
| `pParent` | The parent node of the item. Must be attached to a scene. |
| `pType` | The string representing the type of the item. This can be a defined string provided by udScene_GetTypeName or a custom type. Cannot be NULL. |
| `pName` | A human readable name for the item. If this item is NULL it will attempt to generate a name from the pURI or the pType strings. |
| `pURI` | The URL, filename or other URI containing where to find this item. These should be absolute paths where applicable (preferably HTTPS) to ensure maximum interop with other packages. |
| `pUserData` | A pointer to data provided by the application to store in the `pUserData` item in the udSceneNode. |

**Returns:** A [udError](udError.md) value based on the result of the node being created in the project.

### enum [udError](udError.md) udSceneNode_MoveChild(struct udSceneNode \*pCurrentParent, struct udSceneNode \*pNewParent, struct udSceneNode \*pNode, struct udSceneNode \*pInsertBeforeChild)

Move a node to reorder within the current parent or move to a different parent.

| Parameter | Description |
|-----------|-------------|
| `pCurrentParent` | The current parent of pNode. |
| `pNewParent` | The intended new parent of pNode. |
| `pNode` | The node to move. |
| `pInsertBeforeChild` | The node that will be after pNode after the move. Set as NULL to be the last child of pNewParent. |

**Returns:** A [udError](udError.md) value based on the result of the move.

### enum [udError](udError.md) udSceneNode_RemoveChild(struct udSceneNode \*pParentNode, struct udSceneNode \*pNode)

Remove a node from the project.

> [!WARNING]
> Ensure that the pUserData point of pNode has been released before calling this.

| Parameter | Description |
|-----------|-------------|
| `pParentNode` | The parent of the node to be removed. |
| `pNode` | The node to remove from the project. |

**Returns:** A [udError](udError.md) value based on the result of removing the node.

### enum [udError](udError.md) udSceneNode_SetName(struct udSceneNode \*pNode, const char \*pNodeName)

Set the human readable name of a node.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to change the name of. |
| `pNodeName` | The new name of the node. This is duplicated internally. |

**Returns:** A [udError](udError.md) value based on the result of setting the name.

### enum [udError](udError.md) udSceneNode_SetVisibility(struct udSceneNode \*pNode, int visibility)

Set the visibility of the node

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to change the visibility. |
| `visibility` | The new visibility of the node (non-zero for visible). |

**Returns:** A [udError](udError.md) value based on the result of updating the visibility.

### enum [udError](udError.md) udSceneNode_SetURI(struct udSceneNode \*pNode, const char \*pNodeURI)

Set the URI of a node.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to change the name of. |
| `pNodeURI` | The new URI of the node. This is duplicated internally. |

**Returns:** A [udError](udError.md) value based on the result of setting the URI.

### enum [udError](udError.md) udSceneNode_SetBoundingBox(struct udSceneNode \*pNode, double boundingBox\[6\])

Set a bounding box for the node.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to change the bounding box of. |
| `boundingBox` | An array of doubles representing the bounds of the node, ordered as \[West, South, Floor, East, North, Ceiling\] |

**Returns:** A [udError](udError.md) value based on the result of setting the bounding box.

### enum [udError](udError.md) udSceneNode_SetTimeSpan(struct udSceneNode \*pNode, double start, double end)

Set a time span for the node.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to change the time span of. |
| `start` | A Unix Epoch in Seconds. The node will be relevant after this timestamp. Set to -1.0 to unassign. |
| `end` | A Unix Epoch in Seconds. The node will be relevant before this timestamp. Set to -1.0 to unassign. |

**Returns:** A [udError](udError.md) value based on the result of setting the time span.

### enum [udError](udError.md) udSceneNode_SetGeometry(struct udSceneNode \*pNode, enum udSceneGeometryType nodeType, int geometryCount, double \*pCoordinates)

Set the new geometry of a node.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to change the geometry of. |
| `nodeType` | The new type of the geometry |
| `geometryCount` | How many coordinates are being added |
| `pCoordinates` | A pointer to the new coordinates (this is an array that should be 3x the length of geometryCount). Ordered in \[ longitude0, latitude0, altitude0, …, longitudeN, latitudeN, altitudeN \] order. |

**Returns:** A [udError](udError.md) value based on the result of setting the geometry.

### enum [udError](udError.md) udSceneNode_SetGeometryAltitudeType(struct udSceneNode \*pSceneNode, enum udSceneAltitudeType altitudeType)

Set the altitude type for the node.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to change the altitude type of. |
| `altitudeType` | The altitude type |

**Returns:** A [udError](udError.md) value based on the result of setting the time span.

### enum [udError](udError.md) udSceneNode_GetMetadataInt(struct udSceneNode \*pNode, const char \*pMetadataKey, int32_t \*pInt, int32_t defaultValue)

Get a metadata item of a node as an integer.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to get the metadata from. |
| `pMetadataKey` | The name of the metadata key. |
| `pInt` | The pointer to the memory to write the metadata to |
| `defaultValue` | The value to write to pInt if the metadata item isn’t in the udSceneNode or if it isn’t of an integer type |

**Returns:** A [udError](udError.md) value based on the result of reading the metadata into pInt.

### enum [udError](udError.md) udSceneNode_SetMetadataInt(struct udSceneNode \*pNode, const char \*pMetadataKey, int32_t iValue)

Set a metadata item of a node from an integer.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to set the metadata on. |
| `pMetadataKey` | The name of the metadata key. |
| `iValue` | The integer value to write to the metadata key |

**Returns:** A [udError](udError.md) value based on the result of writing the metadata into the node.

### enum [udError](udError.md) udSceneNode_GetMetadataUint(struct udSceneNode \*pNode, const char \*pMetadataKey, uint32_t \*pInt, uint32_t defaultValue)

Get a metadata item of a node as an unsigned integer.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to get the metadata from. |
| `pMetadataKey` | The name of the metadata key. |
| `pInt` | The pointer to the memory to write the metadata to |
| `defaultValue` | The value to write to pInt if the metadata item isn’t in the udSceneNode or if it isn’t of an integer type |

**Returns:** A [udError](udError.md) value based on the result of reading the metadata into pInt.

### enum [udError](udError.md) udSceneNode_SetMetadataUint(struct udSceneNode \*pNode, const char \*pMetadataKey, uint32_t iValue)

Set a metadata item of a node from an unsigned integer.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to set the metadata on. |
| `pMetadataKey` | The name of the metadata key. |
| `iValue` | The unsigned integer value to write to the metadata key |

**Returns:** A [udError](udError.md) value based on the result of writing the metadata into the node.

### enum [udError](udError.md) udSceneNode_GetMetadataInt64(struct udSceneNode \*pNode, const char \*pMetadataKey, int64_t \*pInt64, int64_t defaultValue)

Get a metadata item of a node as a 64 bit integer.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to get the metadata from. |
| `pMetadataKey` | The name of the metadata key. |
| `pInt64` | The pointer to the memory to write the metadata to |
| `defaultValue` | The value to write to pInt64 if the metadata item isn’t in the udSceneNode or if it isn’t of an integer type |

**Returns:** A [udError](udError.md) value based on the result of reading the metadata into pInt64.

### enum [udError](udError.md) udSceneNode_SetMetadataInt64(struct udSceneNode \*pNode, const char \*pMetadataKey, int64_t i64Value)

Set a metadata item of a node from a 64 bit integer.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to set the metadata on. |
| `pMetadataKey` | The name of the metadata key. |
| `i64Value` | The integer value to write to the metadata key |

**Returns:** A [udError](udError.md) value based on the result of writing the metadata into the node.

### enum [udError](udError.md) udSceneNode_GetMetadataDouble(struct udSceneNode \*pNode, const char \*pMetadataKey, double \*pDouble, double defaultValue)

Get a metadata item of a node as a double.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to get the metadata from. |
| `pMetadataKey` | The name of the metadata key. |
| `pDouble` | The pointer to the memory to write the metadata to |
| `defaultValue` | The value to write to pDouble if the metadata item isn’t in the udSceneNode or if it isn’t of an integer or floating point type |

**Returns:** A [udError](udError.md) value based on the result of reading the metadata into pDouble.

### enum [udError](udError.md) udSceneNode_SetMetadataDouble(struct udSceneNode \*pNode, const char \*pMetadataKey, double doubleValue)

Set a metadata item of a node from a double.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to set the metadata on. |
| `pMetadataKey` | The name of the metadata key. |
| `doubleValue` | The double value to write to the metadata key |

**Returns:** A [udError](udError.md) value based on the result of writing the metadata into the node.

### enum [udError](udError.md) udSceneNode_GetMetadataBool(struct udSceneNode \*pNode, const char \*pMetadataKey, uint32_t \*pBool, uint32_t defaultValue)

Get a metadata item of a node as a boolean.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to get the metadata from. |
| `pMetadataKey` | The name of the metadata key. |
| `pBool` | The pointer to the memory to write the metadata to (0=false, !0=true) |
| `defaultValue` | The value to write to pBool if the metadata item isn’t in the udSceneNode or if it isn’t of a boolean type |

**Returns:** A [udError](udError.md) value based on the result of reading the metadata into pBool.

### enum [udError](udError.md) udSceneNode_SetMetadataBool(struct udSceneNode \*pNode, const char \*pMetadataKey, uint32_t boolValue)

Set a metadata item of a node from a boolean.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to set the metadata on. |
| `pMetadataKey` | The name of the metadata key. |
| `boolValue` | The boolean value to write to the metadata key (0=false, !0=true) |

**Returns:** A [udError](udError.md) value based on the result of writing the metadata into the node.

### enum [udError](udError.md) udSceneNode_GetMetadataString(struct udSceneNode \*pNode, const char \*pMetadataKey, const char \*\*ppString, const char \*pDefaultValue)

Get a metadata item of a node as a string.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to get the metadata from. |
| `pMetadataKey` | The name of the metadata key. |
| `ppString` | The pointer pointer to the memory of the string. This is owned by the udSceneNode and should be copied if required to be stored for a long period. |
| `pDefaultValue` | The value to write to ppString if the metadata item isn’t in the udSceneNode or if it isn’t of a string type |

**Returns:** A [udError](udError.md) value based on the result of reading the metadata into ppString.

### enum [udError](udError.md) udSceneNode_SetMetadataString(struct udSceneNode \*pNode, const char \*pMetadataKey, const char \*pString)

Set a metadata item of a node from a string.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to set the metadata on. |
| `pMetadataKey` | The name of the metadata key. |
| `pString` | The string to write to the metadata key. This is duplicated internally. |

**Returns:** A [udError](udError.md) value based on the result of writing the metadata into the node.

### enum [udError](udError.md) udSceneNode_SetMetadataNull(struct udSceneNode \*pNode, const char \*pMetadataKey)

Set a metadata item of a node to null.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to set the metadata item on. |
| `pMetadataKey` | The name of the metadata key. |

**Returns:** A [udError](udError.md) value based on the result of writing the metadata into the node.

### enum [udError](udError.md) udSceneNode_GetMetadataObjectJSON(struct udSceneNode \*pNode, const char \*pMetadataKey, char \*pBuffer, int bufferLen, int \*pStrLen)

Get a metadata item of a node as a null terminated JSON string.

> [!NOTE]
> pStrLen will be filled if pMetadataKey is valid which allows for calling it again with a bigger pBuffer

> [!NOTE]
> There is intentionally no equivilent “udSceneNode_SetMetadataObjectJSON” as this time

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to get the metadata from. |
| `pMetadataKey` | The name of the metadata key or NULL to get the full metadata object. |
| `pBuffer` | The pointer to a preallocated buffer that you own (or NULL if trying to get the length via pStrLen). |
| `bufferLen` | The usable size of pBuffer in bytes (0 if pBuffer is NULL) |
| `pStrLen` | The size of the total string required (including null terminator) |

**Returns:** A [udError](udError.md) value based on the result of writing the metadata JSON into pBuffer.

### const char \*udScene_GetTypeName(enum udSceneNodeType itemtype)

Get the standard type string name for an itemtype

| Parameter | Description |
|-----------|-------------|
| `itemtype` | The udSceneNodeType value |

**Returns:** A string containing the standard name for the item in the udSceneNodeType enum. This is internal and should not be freed.

### enum [udError](udError.md) udScene_DeleteServerProject(struct udContext \*pContext, const char \*pOrgID, const char \*pProjID, const char \*pSceneID)

Deletes a project from the server

| Parameter | Description |
|-----------|-------------|
| `pContext` | The udContext to use to communicate with the server |
| `pOrgID` | The ID for the udCloud organisation that the scene belongs to |
| `pProjectID` | The ID for the udCloud project that the scene belongs to |
| `pSceneID` | The ID of the scene to delete |

**Returns:** A [udError](udError.md) result (udE_Success if it was deleted, other status codes depending on result)

### enum [udError](udError.md) udScene_SetLinkShareStatus(struct udContext \*pContext, uint32_t isSharableToAnyoneWithTheLink, const char \*pOrgID, const char \*pProjID, const char \*pSceneID)

Sets the share status of a project on the server

| Parameter | Description |
|-----------|-------------|
| `pContext` | The udContext to use to communicate with the server |
| `isSharableToAnyoneWithTheLink` | Not 0 if the project should be able to be loaded by anyone with the link, 0 otherwise |
| `pOrgID` | The ID for the udCloud organisation that the scene will belong to |
| `pProjectID` | The ID for the udCloud project that the scene will belong to |
| `pSceneID` | The ID of the project to update the share status of |

**Returns:** A [udError](udError.md) result (udE_Success if it was updated, other status codes depending on result)

### enum [udError](udError.md) udScene_GetSessionID(struct udScene \*pScene, const char \*\*ppSessionID)

Get the session ID (for server projects).

> [!NOTE]
> Returns udE_NotFound for non-server projects

| Parameter | Description |
|-----------|-------------|
| `pScene` | The pointer to a valid udScene. |
| `ppSessionID` | The pointer pointer to memory that will contain the session ID. The ownership still belongs to the pScene. |

**Returns:** A [udError](udError.md) value based on the result of getting the root node.

### enum [udError](udError.md) udScene_QueueMessage(struct udScene \*pScene, const char \*pTargetSessionID, const char \*pMessageType, const char \*pMessagePayload)

Queues a message to be sent on next project update (for server projects).

| Parameter | Description |
|-----------|-------------|
| `pScene` | The pointer to the active udScene. |
| `pTargetSessionID` | The session ID of the user who will receive this message. Passing in ‘nullptr’ to this parameter indicates all users (except the sender) will receive this message. |
| `pMessageType` | pMessageType User defined message type. |
| `pMessagePayload` | User defined payload. |

**Returns:** A [udError](udError.md) result (udE_Success if the message was successfully queued, other status codes depending on result)

### enum [udError](udError.md) udScene_SaveThumbnail(struct udScene \*pScene, const char \*pImageBase64)

Saves a project thumbnail in base64 format to the server (udCloud only).

| Parameter | Description |
|-----------|-------------|
| `pScene` | The pointer to a valid udScene to save the thumbnail to. |
| `pImageBase64` | The base64 encoded thumbnail. |

**Returns:** A [udError](udError.md) value based on the result of the save.

### enum [udError](udError.md) udSceneNode_GetOwningScene(struct udSceneNode \*pNode, struct udScene \*\*ppScene)

Get the udScene that owns a given node. 

> [!NOTE]
> For nodes that were spliced in via udSceneNode_ResolveXRef this returns the referenced (sub)scene, not the host. The node-mutation APIs (udSceneNode_SetName etc.) derive this internally - mutations always route to the owning scene.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to query. |
| `ppScene` | The pointer pointer that will be written with the owning scene. Ownership remains with the scene. |

**Returns:** udE_Success if the owning scene was returned. udE_InvalidParameter on null args.

### enum [udError](udError.md) udScene_GetRelativeBase(struct udScene \*pScene, const char \*\*ppBase)

Get the base that relative URIs in this scene resolve against. 

> [!NOTE]
> For file scenes this is the directory containing the scene file. For server scenes it’s the “_file” endpoint URL for the owning project. Concatenate with a node’s relative pURI to produce an absolute URL/path.

| Parameter | Description |
|-----------|-------------|
| `pScene` | The scene to query. |
| `ppBase` | Output: a borrowed pointer to the scene’s relative base string. Valid until the scene is released or its file path changes via udScene_SaveToFile. Set to NULL for in-memory scenes with no on-disk or server backing. |

**Returns:** udE_Success on success; udE_InvalidParameter if pScene or ppBase is NULL.

### enum [udError](udError.md) udSceneNode_GetRelativeBase(struct udSceneNode \*pNode, const char \*\*ppBase)

Get the relative base for a node’s owning scene. Equivalent to udSceneNode_GetOwningScene followed by udScene_GetRelativeBase, but in one call. 

| Parameter | Description |
|-----------|-------------|
| `pNode` | The node to query. For xref-spliced nodes this returns the sub-scene’s base, not the host’s - so relative URIs on those nodes resolve against the file that xref’d them in. |
| `ppBase` | Output: a borrowed pointer to the owning scene’s relative base (may be NULL for in-memory scenes). |

**Returns:** udE_Success on success; udE_InvalidParameter if pNode/ppBase is NULL or the node isn’t attached to a scene.

### enum [udError](udError.md) udSceneNode_ResolveXRef(struct udSceneNode \*pNode, enum udSceneXRefFlags flags)

Resolve an xref (external reference) node by loading the referenced scene and attaching its content under pNode.

> [!NOTE]
> The referenced scene becomes a sub-scene owned by the host. Its nodes report their own owning-scene pointer via udSceneNode_GetOwningScene, and mutations routed through the node-mutation APIs (SetName, SetURI, etc.) reach the sub-scene automatically. Sync operations (udScene_Save / udScene_Update) still operate only on their direct scene; use udScene_UpdateResolvedXRefs to fan out over attached sub-scenes.

> [!NOTE]
> Coordinate reprojection between the host and sub-scene CRS is NOT performed by this call. Callers that need it should read the projectcrs metadata on both roots and reproject themselves (or use udScene_MergeScenes for a copy-and-transform workflow instead).

> [!NOTE]
> Two URI forms are supported: a local/remote file path resolved via udScene_LoadFromFile, or a share-code of the form “nuclideon:scene/{sceneID}/{orgID}/{projID}” (with an optional “@camera” suffix which is ignored) resolved via udScene_LoadFromServer. Cycle detection compares file paths for file URIs and (orgID, projID, sceneID) triples for share codes, so a scene cannot xref itself through either form.

| Parameter | Description |
|-----------|-------------|
| `pNode` | An xref node (itemtype == udPNT_XRef) with pURI set to a reachable scene file. Must be attached to a scene. |
| `flags` | See udSceneXRefFlags. |

**Returns:** udE_Success on success; udE_NotAllowed if the node isn’t an xref; udE_CalledMoreThanOnce if the node is already resolved; udE_NotFound if the URI can’t be loaded; udE_OutOfSync if a cycle is detected (the URI is already part of this host’s xref ancestry).

### enum [udError](udError.md) udSceneNode_CollapseXRef(struct udSceneNode \*pNode)

Collapse a previously resolved xref node, detaching and releasing the referenced sub-scene.

| Parameter | Description |
|-----------|-------------|
| `pNode` | An xref node that was previously resolved via udSceneNode_ResolveXRef. |

**Returns:** udE_Success on success; udE_NothingToDo if the node is not currently resolved; udE_NotAllowed if the node isn’t an xref.

### enum [udError](udError.md) udSceneNode_IsXRefResolved(struct udSceneNode \*pNode, uint32_t \*pIsResolved)

Query whether an xref node currently has a resolved sub-scene attached.

| Parameter | Description |
|-----------|-------------|
| `pNode` | The xref node to query. |
| `pIsResolved` | Output: set to 1 if resolved, 0 otherwise. May be NULL. |

**Returns:** udE_Success if pNode is an xref node; udE_NotAllowed otherwise.

### enum [udError](udError.md) udScene_UpdateResolvedXRefs(struct udScene \*pScene, struct udSceneUpdateInfo \*pUpdateInfo, struct udSceneUpdateResult \*pResults, uint32_t resultsCapacity, uint32_t \*pResultsWritten)

Fan udScene_Update across the host scene and every resolved xref sub-scene.

> [!NOTE]
> There is no cross-scene transaction: if the host syncs but a sub-scene fails, the host change is already committed. Callers should inspect pResults to decide how to recover.

> [!NOTE]
> Collaboration/user-list fields inside pUpdateInfo are scene-scoped and are applied to each scene independently; this is the honest behaviour because the server tracks presence per scene.

| Parameter | Description |
|-----------|-------------|
| `pScene` | The host scene. |
| `pUpdateInfo` | The update info passed to each udScene_Update call (same struct reused; see note). |
| `pResults` | Optional output array that receives one udSceneUpdateResult per scene touched. May be NULL if only the count is needed. |
| `resultsCapacity` | The number of entries available in pResults. Ignored if pResults is NULL. |
| `pResultsWritten` | Output: the number of scenes that were processed (equals host + count of resolved xrefs). |

**Returns:** udE_Success if every scene returned udE_Success or udE_NothingToDo; udE_Failure if any individual update reported a hard error (per-scene detail is in pResults); udE_BufferTooSmall if pResults is non-NULL and too small to hold all results.

### enum [udError](udError.md) udScene_SaveResolvedXRefs(struct udScene \*pScene, struct udSceneUpdateResult \*pResults, uint32_t resultsCapacity, uint32_t \*pResultsWritten)

Fan udScene_Save across the host scene and every resolved xref sub-scene.

> [!NOTE]
> There is no cross-scene transaction: if the host saves but a sub-scene fails, the host change is already written. Callers should inspect pResults to decide how to recover.

| Parameter | Description |
|-----------|-------------|
| `pScene` | The host scene. |
| `pResults` | Optional output array that receives one udSceneUpdateResult per scene touched. May be NULL. |
| `resultsCapacity` | The number of entries available in pResults. Ignored if pResults is NULL. |
| `pResultsWritten` | Output: the number of scenes that were processed (equals host + count of resolved xrefs). |

**Returns:** udE_Success if every scene saved successfully; udE_Failure if any individual save reported a hard error (per-scene detail is in pResults); udE_BufferTooSmall if pResults is non-NULL and too small to hold all results.


## Structs

### struct udScenePosition

This represents a position in 3D 

> [!NOTE]
> contains x,y,z and heading, pitch (generally of a camera) in the project CRS

| Field | Type | Description |
|-------|------|-------------|
| `x` | `double` | The x coordiante of the item. |
| `y` | `double` | The y coordiante of the item. |
| `z` | `double` | The z coordiante of the item. |
| `heading` | `double` | The heading of the item. |
| `pitch` | `double` | The pitch of the item. |
| `roll` | `double` | The roll of the item. |

### struct udSceneNodeSelected

This represents the selected scene node of a user

| Field | Type | Description |
|-------|------|-------------|
| `id[37]` | `char` | The uuid of the selected node. |

### struct udSceneMessage

This represents the message sent to other users (or to us) in a scene during collaboration

| Field | Type | Description |
|-------|------|-------------|
| `pMessageType` | `const char \*` | The type of the message. |
| `pMessagePayload` | `const char \*` | The payload of the message. |
| `pTargetSessionID` | `const char \*` | The session ID of the message. |
| `pReceivedFromSessionID` | `const char \*` | The session Id where it’s been received. |

### struct udSceneUser

This represents the user info (used for collaboration)

| Field | Type | Description |
|-------|------|-------------|
| `pDisplayName` | `const char \*` | The name to display for this user. |
| `pSceneSessionID` | `const char \*` | The current scene/session ID this user is log in. |
| `lastUpdated` | `double` | The time its position was been last updated \[server time\]. |
| `userFlags` | `enum udSceneUserFlag` | Flag to know if user is using XR. |
| `selectedNodesCount` | `uint32_t` | The number of node selected. |
| `selectedNodesList` | `struct udSceneNodeSelected \*` | The selected nodes. |
| `headCamera` | `struct udScenePosition` | The position of the head or camera for the active viewer. |
| `handRight` | `struct udScenePosition` | The position of the right hand for the active viewer if udSceneUserFlag_HasHands is set in userFlags. |
| `handLeft` | `struct udScenePosition` | The position of the left hand for the active viewer if udSceneUserFlag_HasHands is set in userFlags. |
| `worldAnchorPoint` | `udDouble4` | The position of the world anchor point if udSceneUserFlag_HasAnchorAndScale is set; xyz are a position in world space and w is the scale factor. |

### struct udSceneNode

Stores the state of a node. 

> [!WARNING]
> This struct is exposed to avoid having a huge API of accessor functions but it should be treated as read only with the exception of `pUserData`. Making changes to the internal data will cause issues syncronising data

| Field | Type | Description |
|-------|------|-------------|
| `isVisible` | `int` | Non-zero if the node is visible and should be drawn in the scene. |
| `UUID[37]` | `char` | Unique identifier for this node “id”. |
| `lastUpdate` | `double` | The last time this node was updated in UTC. |
| `itemtype` | `enum udSceneNodeType` | The type of this node, see udSceneNodeType for more information. |
| `itemtypeStr[8]` | `char` | The string representing the type of node. If its a known type during node creation `itemtype` will be set to something other than udPNT_Custom. |
| `pName` | `const char \*` | Human readable name of the item. |
| `pURI` | `const char \*` | The address or filename that the resource can be found. |
| `hasBoundingBox` | `uint32_t` | Set to not 0 if this nodes boundingBox item is filled out. |
| `boundingBox[6]` | `double` | The bounds of this model, ordered as \[West, South, Floor, East, North, Ceiling\]. |
| `timeSpanBegin` | `double` | Unix Epoch in Seconds. This node is relevant after this timestamp. -1.0 if not assigned. |
| `timeSpanEnd` | `double` | Unix Epoch in Seconds. This node is relevant until this timestamp. -1.0 if not assigned. |
| `altitudeType` | `enum udSceneAltitudeType` |  |
| `geomtype` | `enum udSceneGeometryType` | Indicates what geometry can be found in this model. See the udSceneGeometryType documentation for more information. |
| `geomCount` | `int` | How many geometry items can be found on this model. |
| `pCoordinates` | `double \*` | The positions of the geometry of this node (NULL this this node doesn’t have points). The format is \[X0,Y0,Z0,…Xn,Yn,Zn\]. |
| `pParent` | `struct udSceneNode \*` | This is the parent item of the current node (NULL if root node). |
| `pNextSibling` | `struct udSceneNode \*` | This is the next item in the scene (NULL if no further siblings). |
| `pFirstChild` | `struct udSceneNode \*` | Some types (“folder”, “collection”, “polygon”…) have children nodes, NULL if there are no children. |
| `pUserData)` | `void (\*pUserDataCleanup)(struct udSceneNode \*pNode, void \*` | When a project node is deleted, this function is called first. |
| `pUserData` | `void \*` | This is application specific user data. The application should traverse the tree to release these before releasing the udScene. |
| `pInternalData` | `struct udSceneNodeInternal \*` | Internal udSDK specific state for this node. |

### struct udSceneUpdateInfo

This represents the update info given/received to/by udScene_Update 

> [!WARNING]
> Memory is Freed on next call of udScene_Updte()

| Field | Type | Description |
|-------|------|-------------|
| `forceSync` | `uint32_t` | If this is non-zero the sync to the server will happen immediately and the update call will block. |
| `lastUpdatedTime` | `double` | The timestamp that the scene was last updated (local time). |
| `userFlags` | `enum udSceneUserFlag` | User flags to define the device and other properties. |
| `selectedNodesCount` | `uint32_t` | The length of pSelectedNodesList. |
| `pSelectedNodesList` | `struct udSceneNodeSelected \*` | The list of selected nodes. |
| `headCamera` | `struct udScenePosition` | The position of the head or camera for the active viewer. |
| `handRight` | `struct udScenePosition` | The position of the right hand for the active viewer if udSceneUserFlag_HasHands is set in userFlags. |
| `handLeft` | `struct udScenePosition` | The position of the left hand for the active viewer if udSceneUserFlag_HasHands is set in userFlags. |
| `worldAnchorPoint` | `udDouble4` | The position of the world anchor point if udSceneUserFlag_HasAnchorAndScale is set; xyz are a position in world space and w is the scale factor. |
| `pUserList` | `struct udSceneUser \*` | The list of other users in this scene. |
| `usersCount` | `uint32_t` | The number of users in the scene (and length of pUserList). |
| `pReceivedMessages` | `struct udSceneMessage \*` | The list of messages. |
| `receivedMessagesCount` | `uint32_t` | The length of pReceivedMessages. |

### struct udSceneUpdateResult

Per-scene result entry returned by udScene_UpdateResolvedXRefs.

| Field | Type | Description |
|-------|------|-------------|
| `pScene` | `struct udScene \*` | The scene that was updated (the host scene or one of its resolved xref sub-scenes). Ownership unchanged. |
| `result` | `enum [udError](udError.md)` | The result of calling udScene_Update on pScene. |
