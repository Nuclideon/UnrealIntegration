# udUtil

Helper functions for diverse use cases 

## Functions

### enum [udError](udError.md) udUtil_E57ExtractImages(const char \*pFileName, const char \*pFolderName, const char \*\*ppMetaData)

Extract Images from an e57 file

| Parameter | Description |
|-----------|-------------|
| `pFileName` | The e57 filename |
| `pFolderName` | The folder to extract the images into |
| `ppMetaData` | Optional char\* filled withmetadata from exported images (paths, position, rotation, shape) as JSON |

**Returns:** A [udError](udError.md) value based on the result of the extraction
