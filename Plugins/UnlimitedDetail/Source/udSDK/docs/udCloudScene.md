# udCloudScene

The udCloudScene object provide an interface for accessing data of Scenes hosted in udCloud 


## Structs

### struct udCloudScene

This represents a udCloud Scene

| Field | Type | Description |
|-------|------|-------------|
| `pName` | `char \*` | The name of the Scene. |
| `ID[64]` | `char` | The sceneid from udCloud. |
| `orgID[64]` | `char` | The workspace it belongs to from udCloud. |
| `projID[64]` | `char` | The project it belongs to from udCloud. |
| `created` | `double` | The time this scene was created. |
| `lastUpdated` | `double` | The time this scene was last updated. |
| `deletedTime` | `double` | The time this scene was deleted. |
| `isShared` | `uint32_t` | Is the scene shared. |
