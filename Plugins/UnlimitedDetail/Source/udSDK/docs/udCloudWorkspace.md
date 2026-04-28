# udCloudWorkspace

The udCloudWorkspace object provides an interface for accessing data of workspace hosted in udCloud 

## Functions

### enum [udError](udError.md) udCloudWorkspace_GetWorkspaceList(struct udContext \*pContext, struct udCloudWorkspace \*\*ppCloudWorkspaces, int \*pCount)

Get a list of available Workspaces hosted in udCloud

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use. |
| `ppCloudWorkspaces` | The pointer pointer of the udCloudWorkspace. |
| `pCount` | The number of Workspace in ppCloudWorkspaces. |

**Returns:** A [udError](udError.md) value based on the result of the query on udCloud.

### enum [udError](udError.md) udCloudWorkspace_ReleaseWorkspaceList(struct udCloudWorkspace \*\*ppCloudWorkspaces, int count)

Destroys the list of Workspaces that was created by udCloudWorkspace_GetWorkspaceList

| Parameter | Description |
|-----------|-------------|
| `ppCloudWorkspaces` | The list of Workspaces to be destroyed. |
| `count` | The number of udCloudWorkspace in ppCloudWorkspaces. |

**Returns:** A [udError](udError.md) value based on the memory been freed.

### enum [udError](udError.md) udCloudWorkspace_GetProjectList(struct udContext \*pContext, struct udCloudWorkspace \*pCloudWorkspace, struct [udCloudProject](udCloudProject.md) \*\*ppCloudProjects, int \*pCount)

Get a list of available Projects owned by a specific Workspace in udCloud

| Parameter | Description |
|-----------|-------------|
| `pContext` | The pointer to the udContext of the session to use. |
| `pCloudWorkspace` | The pointer of the udCloudWorkspace. |
| `ppCloudProjects` | A list of Projects returned. |
| `pCount` | The number of projects in ppCloudProject. |

**Returns:** A [udError](udError.md) value based on the result of the query on udCloud.

### enum [udError](udError.md) udCloudWorkspace_ReleaseProjectList(struct [udCloudProject](udCloudProject.md) \*\*ppCloudProjects, int count)

Destroys the list of Projects that was created by udCloudWorkspace_GetProjectList

| Parameter | Description |
|-----------|-------------|
| `ppCloudProjects` | The list of Projects to be destroyed. |
| `count` | The number of [udCloudProject](udCloudProject.md) in ppCloudProjects. |

**Returns:** A [udError](udError.md) value based on the memory been freed.


## Structs

### struct udCloudWorkspace

This represents a udCloud Workspace

| Field | Type | Description |
|-------|------|-------------|
| `ID[64]` | `char` | The workspace id from udCloud. |
| `pName` | `char \*` | The name of the workspace. |
| `permissions` | `uint64_t` | The permissions of this workspace. |
| `isPendingDelete` | `uint32_t` | A flag to know if the workspace will be deleted shortly. |
