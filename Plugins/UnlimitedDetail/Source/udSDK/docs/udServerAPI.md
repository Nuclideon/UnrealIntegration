# udServerAPI

The **udServerAPI** module provides an interface to communicate with a Nuclideon udServer API directly in a simple fashion. 

## Functions

### enum [udError](udError.md) udServerAPI_Query(struct udContext \*pContext, const char \*pAPIAddress, const char \*pJSON, const char \*\*ppResult)

Queries provided API on the specified Nuclideon udServer.

> [!NOTE]
> The application should call **udServerAPI_ReleaseResult** with `ppResult` to destroy the data once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The context to execute the query with. |
| `pAPIAddress` | The API address to query, this is the part of the address *after* `/api/`. The rest of the address is constructed from the context provided. |
| `pJSON` | The JSON text to POST to the API address. |
| `ppResult` | A pointer to a location in which the result data is to be stored. |

**Returns:** A [udError](udError.md) value based on the result of the API query.

### enum [udError](udError.md) udServerAPI_QueryWithProgress(struct udContext \*pContext, const char \*pAPIAddress, const char \*pJSON, const char \*\*ppResult, [udProgressCallback](udError.md) \*pProgressCallback, void \*pProgressUserData)

Queries provided API on the specified Nuclideon udServer.

> [!NOTE]
> The application should call **udServerAPI_ReleaseResult** with `ppResult` to destroy the data once it’s no longer needed.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The context to execute the query with. |
| `pAPIAddress` | The API address to query, this is the part of the address *after* `/api/`. The rest of the address is constructed from the context provided. |
| `pJSON` | The JSON text to POST to the API address. |
| `ppResult` | A pointer to a location in which the result data is to be stored. |
| `pProgressCallback` | A function callback when there are progress updates |
| `pProgressUserData` | A pointer that will be passed to the pProgressCallback |

**Returns:** A [udError](udError.md) value based on the result of the API query.

### enum [udError](udError.md) udServerAPI_ReleaseResult(const char \*\*ppResult)

Destroys the result that was allocated.

> [!NOTE]
> The value of `ppResult` will be set to `NULL`.

| Parameter | Description |
|-----------|-------------|
| `ppResult` | A pointer to a location in which the result data is stored. |
