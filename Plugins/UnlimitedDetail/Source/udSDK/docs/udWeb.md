# udWeb

This is an optional helper module to assist with doing web requests. Internally it uses libcURL with the global settings (proxy and certificates information) from `udConfig`. As this is not a core module, it does not accept a `udContext` and can be used without having a udServer available. 

## Enums

### enum udWebMethod

These are the support HTTP method types in udWeb 

*Values:*

| Value | Description |
|-------|-------------|
| `udWM_HEAD` | Performs a HEAD request. |
| `udWM_GET` | Performs a GET request. |
| `udWM_POST` | Performs a POST request. |

## Functions

### enum [udError](udError.md) udWeb_Request(const char \*pURL, const char \*\*ppResponse, uint64_t \*pResponseLength, int \*pHTTPResponseCode)

This sends a GET request to a given URL, the response (if any) is written to `ppResponse`.

> [!NOTE]
> This function internally just calls `udWeb_RequestAdv` with the option members being zeroed, except for the method which is set to `udWM_GET`.

| Parameter | Description |
|-----------|-------------|
| `pURL` | The URL to request. |
| `ppResponse` | This will be modified with a pointer to internal udSDK memory with the contents of the request. You must call `udWeb_ReleaseResponse` to free this memory. |
| `pResponseLength` | If non-null, the pointer’s memory will be set to the length of `ppResponse`. |
| `pHTTPResponseCode` | If non-null this will be set to the HTTP status code. See https ://www.ietf.org/assignments/http-status-codes/http-status-codes.xml for status codes. |

**Returns:** A [udError](udError.md) value based on the result of the HTTP request.

### enum [udError](udError.md) udWeb_RequestAdv(const char \*pURL, struct udWebOptions options, const char \*\*ppResponse, uint64_t \*pResponseLength, int \*pHTTPResponseCode)

This sends a request to a given URL using the specified options, the response (if any) is written to `ppResponse`.

| Parameter | Description |
|-----------|-------------|
| `pURL` | The URL to request. |
| `options` | The options for the request, see above for details. |
| `ppResponse` | This will be modified with a pointer to internal udSDK memory with the contents of the request. You must call `udWeb_ReleaseResponse` to free this memory. |
| `pResponseLength` | If non-null, the pointer’s memory will be set to the length of `ppResponse`. |
| `pHTTPResponseCode` | If non-null this will be set to the HTTP status code. See https ://www.ietf.org/assignments/http-status-codes/http-status-codes.xml for status codes. |

**Returns:** A [udError](udError.md) value based on the result of the HTTP request.

### enum [udError](udError.md) udWeb_ReleaseResponse(const char \*\*ppResponse)

Frees memory of a prior call to `udWeb_Request` or `udWeb_RequestAdv`.

| Parameter | Description |
|-----------|-------------|
| `ppResponse` | A pointer to a pointer containing the response from a prior call to `udWeb_Request` or `udWeb_RequestAdv`. |

**Returns:** A [udError](udError.md) value based on the result of releasing the HTTP response.


## Structs

### struct udWebOptions

This structure stores the options for a udWeb request

> [!NOTE]
> The default values for the members except `method` is `NULL` or `0`.

| Field | Type | Description |
|-------|------|-------------|
| `method` | `enum udWebMethod` | The HTTP method to use for the request. |
| `pPostData` | `const uint8_t \*` | The data to send to the server as part of a POST request. |
| `postLength` | `uint64_t` | The length of the data being sent to the server. |
| `rangeBegin` | `uint64_t` | The position of the first byte in the requested file to receive data from. |
| `rangeEnd` | `uint64_t` | The position of the last byte in the requested file to receive data from. |
| `pAuthUsername` | `const char \*` | The username to use when authenticating with the server. |
| `pAuthPassword` | `const char \*` | The password to use when authenticating with the server. |
| `pCookie` | `const char \*` | A cookie to include in the header. |
| `pContext` | `struct udContext \*` | If this is provided and pURL is on the same domain as the pContext server the API details will be passed through. |
