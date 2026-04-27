# udGeoProjection

udGeoProjection.h provides a udSDK wrapper for [udGeoZone](udGeoZone.md)

## Functions

### enum [udError](udError.md) udGeoProjection_LoadZonesFromJSON(const char \*pJSONStr, int \*pLoaded, int \*pFailed)

Loads a set of zones from a JSON file where each member is defined as “AUTHORITY:SRID” (eg. “EPSG:32756”)

> [!NOTE]
> udGeoProjection_UnloadZones needs to be called to free loaded zones. This function can be called multiple times to load more zones

| Parameter | Description |
|-----------|-------------|
| `pJSONStr` | A pointer to a JSON string that contains the new zones to load |
| `pLoaded` | \[optional\] If non-null, will be set to the number of zones successfully loaded |
| `pFailed` | \[optional\] If non-null, will be set to the number of zones that failed to load |

### enum [udError](udError.md) udGeoProjection_UnloadZones()

Unloads all loaded zones (only needs to be called once to unload all previously loaded zones from udGeoProjection_LoadZonesFromJSON)
