# udContext

The **udContext** object provides an interface to connect and communicate with a Nuclideon udServer. Once instantiated, the **udContext** can be passed into many udSDK functions to provide a context to operate within. 

## Functions

### enum [udError](udError.md) udContext_ConnectStart(struct udContextPartial \*\*ppPartialContext, const char \*pServerURL, const char \*pApplicationName, const char \*pApplicationVersion, const char \*\*ppApprovePath, const char \*\*ppApproveCode)

Establishes a connection to a Nuclideon udCloud and creates a new udContext object.

> [!NOTE]
> The application should call udContext_ConnectComplete or udContext_ConnectCancel with ppPartialContext to destroy the object

| Parameter | Description |
|-----------|-------------|
| `ppPartialContext` | A pointer to a location in which the new udContextPartial object is stored. |
| `pServerURL` | A Server URL to the Nuclideon udCloud instance. |
| `pApplicationName` | The name of the application using udSDK. |
| `pApplicationVersion` | The version of the application using udSDK. |
| `ppApprovePath` | The address that needs to be opened in a browser window (if this is nullptr proceed to udContext_ConnectComplete) |
| `ppApproveCode` | A code that the user can use to verify their session in the udCloud API on another device (can be NULL) |

**Returns:** A [udError](udError.md) value based on the result of the connection creation.

### enum [udError](udError.md) udContext_ConnectComplete(struct udContext \*\*ppContext, struct udContextPartial \*\*ppPartialContext)

Establishes a connection to a Nuclideon udCloud server and creates a new udContext object.

> [!NOTE]
> The application should call **udContext_Disconnect** with `ppContext` to destroy the object once it’s no longer needed.

> [!WARNING]
> ppApprovePath from udContext_ConnectStart will be invalid after this call

| Parameter | Description |
|-----------|-------------|
| `ppContext` | A pointer to a location in which the new udContext object is stored. |
| `ppPartialContext` | A pointer to the udContextPartial created from udContext_ConnectStart (will be freed on a successful login). |

**Returns:** A [udError](udError.md) value based on the result of the connection creation.

### enum [udError](udError.md) udContext_ConnectCancel(struct udContextPartial \*\*ppPartialContext)

Cancels a login attempt to a Nuclideon udCloud server;

| Parameter | Description |
|-----------|-------------|
| `ppPartialContext` | A pointer to the udContextPartial created from udContext_ConnectStart (will be freed). |

**Returns:** A [udError](udError.md) value based on the result of the connection cleanup.

### enum [udError](udError.md) udContext_ConnectWithKey(struct udContext \*\*ppContext, const char \*pServerURL, const char \*pApplicationName, const char \*pApplicationVersion, const char \*pKey)

Establishes a connection to Nuclideon udCloud server and creates a new udContext object.

> [!NOTE]
> The application should call udContext_Disconnect with `ppContext` to destroy the object once it’s no longer needed.

> [!WARNING]
> When used from the Emscripten/WebAssembly builds it will try start a domain session when pKey is NULL

| Parameter | Description |
|-----------|-------------|
| `ppContext` | A pointer to a location in which the new udContext object is stored. |
| `pServerURL` | A URL to a Nuclideon udCloud server to connect to. |
| `pApplicationName` | The name of the application using udSDK. |
| `pApplicationVersion` | The version of the application using udSDK. |
| `pKey` | The provided key that will start the context |

**Returns:** A [udError](udError.md) value based on the result of the connection creation.

### enum [udError](udError.md) udContext_ConnectFromDomain(struct udContext \*\*ppContext, const char \*pServerURL, const char \*pApplicationName)

Establishes a (legacy) connection to a Nuclideon udServer and creates a new udContext object.

> [!NOTE]
> The application should call **udContext_Disconnect** with `ppContext` to destroy the object once it’s no longer needed.

> [!WARNING]
> This connect function is specific to the Emscripten/WebAssembly builds and will return udE_Unsupported on all other platforms

| Parameter | Description |
|-----------|-------------|
| `ppContext` | A pointer to a location in which the new udContext object is stored. |
| `pServerURL` | A URL to a Nuclideon udServer to connect to. |
| `pApplicationName` | The name of the application connecting to the Nuclideon udServer. |

**Returns:** A [udError](udError.md) value based on the result of the connection creation.

### enum [udError](udError.md) udContext_TryResume(struct udContext \*\*ppContext, const char \*pURL, const char \*pApplicationName, const char \*pUsername, uint32_t tryDongle)

Attempts to reestablish a connection to Nuclideon udCloud, Nuclideon udServer (or run offline with an offline context) and creates a new udContext object.

> [!NOTE]
> This function will try use a session from a dongle first if that is supported; passing null to pURL, pApplicationName and pUsername will test the dongle but will otherwise be invalid

> [!WARNING]
> The application should call udContext_Disconnect with `ppContext` to destroy the object once it’s no longer needed.

> [!WARNING]
> This function can crash with some debuggers attached when trying to read from a dongle. If debugging, ensure that tryDongle is set to 0.

| Parameter | Description |
|-----------|-------------|
| `ppContext` | A pointer to a location in which the new udContext object is stored. |
| `pURL` | A URL to a Nuclideon udServer to connect to. |
| `pApplicationName` | The name of the application connecting to the Nuclideon udServer. |
| `pUsername` | The username of the user connecting to the Nuclideon udServer. |
| `tryDongle` | If 0, the dongle will not be checked (on platforms that support dongles). |

**Returns:** A [udError](udError.md) value based on the result of the connection creation.

### enum [udError](udError.md) udContext_Disconnect(struct udContext \*\*ppContext, uint32_t endSession)

Disconnects and destroys a udContext object that was created using one of the context creation functions.

> [!NOTE]
> The value of `ppContext` will be set to `NULL`.

> [!WARNING]
> If other resources are still referencing this context this will return udE_NotAllowed until those resources are destroyed first

| Parameter | Description |
|-----------|-------------|
| `ppContext` | A pointer to a udContext object which is to be disconnected and destroyed. |
| `endSession` | Not 0 if the session will be ended (cannot be resumed) |

**Returns:** A [udError](udError.md) value based on the result of the connection destruction.

### enum [udError](udError.md) udContext_GetSessionInfo(struct udContext \*pContext, struct udSessionInfo \*pInfo)

Get the session information from an active udContext.

| Parameter | Description |
|-----------|-------------|
| `pContext` | The udContext to get the session info for. |
| `pInfo` | The preallocated structure to copy the info into. |

**Returns:** A [udError](udError.md) value based on the result of copying the structure


## Structs

### struct udSessionInfo

This structure stores information about the current session

| Field | Type | Description |
|-------|------|-------------|
| `apiVersion` | `uint32_t` | The version of the API of the remote system (0 is offine, 1 is legacy udServer, 2 is udCloud). |
| `isDomain` | `uint32_t` | If this is not 0 then this is a domain session (0 is non-domain session). |
| `isPremium` | `uint32_t` | If this session will have access to premium features. |
| `expiresTimestamp` | `double` | The timestamp in UTC when the session will automatically end. |
| `displayName[1024]` | `char` | The null terminated display name of the user. |
| `otherLicenses[1024]` | `char` | Comma seperated list of other licenses available for this user; common ones include “xr”, “defence”, “transport”, & “resources”. |
