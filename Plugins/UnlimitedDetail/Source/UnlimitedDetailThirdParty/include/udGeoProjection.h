#ifndef udGeoProjection_h__
#define udGeoProjection_h__

//! @file udGeoProjection.h
//! udGeoProjection.h provides a udSDK wrapper for udGeoZone

#include "udError.h"

#ifdef __cplusplus
extern "C" {
#endif

//!
//! Loads a set of zones from a JSON file where each member is defined as "AUTHORITY:SRID" (eg. "EPSG:32756")
//!
//! @param pJSONStr A pointer to a JSON string that contains the new zones to load
//! @param pLoaded [optional] If non-null, will be set to the number of zones successfully loaded
//! @param pFailed [optional] If non-null, will be set to the number of zones that failed to load
//! @note udGeoProjection_UnloadZones needs to be called to free loaded zones. This function can be called multiple times to load more zones
//!
UDSDKDLL_API enum udError udGeoProjection_LoadZonesFromJSON(const char *pJSONStr, int *pLoaded, int *pFailed);

//!
//! Unloads all loaded zones (only needs to be called once to unload all previously loaded zones from udGeoProjection_LoadZonesFromJSON)
//!
UDSDKDLL_API enum udError udGeoProjection_UnloadZones();

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // udGeoProjection_h__
