# udConfig

The **udConfig** functions all set global configuration options for the entire loaded shared library. 

## Functions

### enum [udError](udError.md) udConfig_ForceProxy(const char \*pProxyAddress)

This function can be used to override the internal proxy auto-detection used by cURL.

> [!NOTE]
> By default the proxy is attempted to be auto-detected. This fails in many proxy configurations.

| Parameter | Description |
|-----------|-------------|
| `pProxyAddress` | This is a null terminated string, can include port number and protocol. `192.168.0.1`, `169.123.123.1:80`, `` or ``. Setting this to either `NULL` or (empty string) `""` will reset to attempting auto-detection. |

**Returns:** A [udError](udError.md) value based on the result of forcing the proxy.

### enum [udError](udError.md) udConfig_SetProxyAuth(const char \*pProxyUsername, const char \*pProxyPassword)

This function is used in conjunction with `udConfig_ForceProxy` or the auto-detect proxy system to forward info from the user for their proxy details.

> [!NOTE]
> This is usually called after another udSDK function returns `[udE_ProxyAuthRequired](udError.md)`.

| Parameter | Description |
|-----------|-------------|
| `pProxyUsername` | This is a null terminated string of the username of the user for the proxy. |
| `pProxyPassword` | This is a null terminated string of the password of the user for the proxy. |

**Returns:** A [udError](udError.md) value based on the result of setting the proxy authentication.

### enum [udError](udError.md) udConfig_IgnoreCertificateVerification(uint32_t ignore)

Allows udSDK to connect to server with an unrecognized certificate authority, sometimes required for self-signed certificates or poorly configured proxies.

> [!NOTE]
> By default certificate verification is run (not ignored).

> [!WARNING]
> Ignoring certificate verification is very high risk. Do not enable this option by default and display clearly to the user that this setting will reduce the security of the entire system and they should only enable the setting if their system administrator has instructed them to do so.

| Parameter | Description |
|-----------|-------------|
| `ignore` | `0` if verification is to be processed, all other values if certificate verification should be skipped. |

**Returns:** A [udError](udError.md) value based on the result of ignoring the certificate verification.

### enum [udError](udError.md) udConfig_SetUserAgent(const char \*pUserAgent)

This function can be used to override the user agent used by cURL.

| Parameter | Description |
|-----------|-------------|
| `pUserAgent` | This is a null terminated string of the user agent. |

**Returns:** A [udError](udError.md) value based on the result of setting the user agent.

### enum [udError](udError.md) udConfig_SetConfigLocation(const char \*pLocation)

This function can be used to override the location that udSDK will save it’s configuration files.

> [!NOTE]
> By default, udSDK will attempt to use some known platform locations, in some cases failing to save entirely.

> [!NOTE]
> This location will have `/nuclideon/udsdk` appending to the end.

| Parameter | Description |
|-----------|-------------|
| `pLocation` | This is a null terminated string specifying a directory to save configurations files. |

**Returns:** A [udError](udError.md) value based on the result of setting the configuration location.
