# udCloudFile

The udCloudFile object provide an interface for accessing data of files hosted in udCloud 


## Structs

### struct udCloudFile

This represents a udCloud File

| Field | Type | Description |
|-------|------|-------------|
| `ID[64]` | `char` | The id from udCloud. |
| `projID[64]` | `char` | The project id it belongs to from udCloud. |
| `pPath` | `char \*` | The path of the udCloud File. |
| `pCreated` | `char \*` | The time this udCloud File was created. |
| `pTier` | `char \*` | The tier where this udCloud File is stored in udCloud. |
| `pTimeToLive` | `char \*` | If the udCloud File will be auto-deleted this is the timestamp for when that will occur. |
| `size` | `uint64_t` | The size of the udCloud File. |
| `isFolder` | `uint32_t` | != 0 if the udCloud File is a folder |
| `isShared` | `uint32_t` | != 0 if the udCloud File is shared |
