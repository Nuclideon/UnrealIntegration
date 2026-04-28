# udVersion

The **udVersion** object provides an interface to query the version of the loaded udSDK library. 

## Defines

### UDSDK_MAJOR_VERSION

The major version part of the library version. 

### UDSDK_MINOR_VERSION

The minor version part of the library version. 

### UDSDK_PATCH_VERSION

The patch version part of the library version. 

## Functions

### enum [udError](udError.md) udVersion_GetVersion(struct udVersion \*pVersion)

Populates the provided structure with the version information for the loaded udSDK library.

| Parameter | Description |
|-----------|-------------|
| `pVersion` | The version structure which will be populated with the version information. |

**Returns:** A [udError](udError.md) value based on the result of getting the version information.


## Structs

### struct udVersion

Stores the version information for the loaded udSDK library.

| Field | Type | Description |
|-------|------|-------------|
| `major` | `uint8_t` | The major version part of the library version. |
| `minor` | `uint8_t` | The minor version part of the library version. |
| `patch` | `uint8_t` | The patch version part of the library version. |
