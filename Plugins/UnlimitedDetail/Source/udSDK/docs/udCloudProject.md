# udCloudProject

The udCloudProject object provide an interface for accessing data of projects hosted in udCloud 

## Functions

### enum [udError](udError.md) udCloudProject_GetFileList(struct udContext \*pContext, struct udCloudProject \*pCloudProject, struct [udCloudFile](udCloudFile.md) \*\*ppCloudFiles, int \*pCount)

Get a list of available Files owned by a specific Project in udCloud

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use |
| `pCloudProject` | The pointer of the udCloudProject. |
| `ppCloudFiles` | A list of Files returned. |
| `pCount` | The number of Files in ppCloudFiles. |

**Returns:** A [udError](udError.md) value based on the result of the query on udCloud.

### enum [udError](udError.md) udCloudProject_ReleaseFileList(struct [udCloudFile](udCloudFile.md) \*\*ppCloudFiles, int count)

Destroys the list of Files that was created by udCloudProject_GetFileList

| Parameter | Description |
|-----------|-------------|
| `ppCloudFiles` | The list of Files to be destroyed. |
| `count` | The number of Files in ppCloudFiles. |

**Returns:** A [udError](udError.md) value based on the memory been freed.

### enum [udError](udError.md) udCloudProject_GetSceneList(struct udContext \*pContext, struct udCloudProject \*pCloudProject, struct [udCloudScene](udCloudScene.md) \*\*ppCloudScenes, int \*pCount)

Get a list of available scenes owned by a specific Project in udCloud

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use |
| `pCloudProject` | The pointer of the udCloudProject. |
| `ppCloudScenes` | A list of Scenes returned. |
| `pCount` | The number of scenes in ppCloudScenes. |

**Returns:** A [udError](udError.md) value based on the result of the query on udCloud.

### enum [udError](udError.md) udCloudProject_ReleaseSceneList(struct [udCloudScene](udCloudScene.md) \*\*ppCloudScenes, int count)

Destroys the list of Scenes that was created by udCloudProject_GetSceneList

| Parameter | Description |
|-----------|-------------|
| `ppCloudScenes` | The list of Scenes to be destroyed. |
| `count` | The number of Scenes in ppCloudScenes. |

**Returns:** A [udError](udError.md) value based on the memory been freed.


## Structs

### struct udCloudProject

This represents a udCloud Project

| Field | Type | Description |
|-------|------|-------------|
| `ID[64]` | `char` | The project id from udCloud. |
| `orgID[64]` | `char` | The workspace it belongs to from udCloud. |
| `pName` | `char \*` | The name of the project. |
| `created` | `double` | The time this project was created. |
| `optionalPermissions` | `uint64_t` | The permissions of this project. |
