# udGeoZone

udGeoZone.h provides support for transforming geodetic and cartesian coordinates 

## Defines

### udGeoZone_SetFromWKT

## Enums

### enum udGeoZoneEllipsoid

Supported udGeoZone ellipsoids 

*Values:*

| Value | Description |
|-------|-------------|
| `udGZE_WGS84` | EPSG:7030. |
| `udGZE_Airy1830` | EPSG:7001. |
| `udGZE_AiryModified` | EPSG:7002. |
| `udGZE_Bessel1841` | EPSG:7004. |
| `udGZE_BesselModified` | EPSG:7005. |
| `udGZE_Clarke1866` | EPSG:7008. |
| `udGZE_Clarke1880IGN` | EPSG:7011. |
| `udGZE_GRS80` | EPSG:7019. |
| `udGZE_Intl1924` | EPSG:7022 (Same numbers as Hayford). |
| `udGZE_WGS72` | EPSG:7043. |
| `udGZE_CGCS2000` | EPSG:1024. |
| `udGZE_Clarke1858` | EPSG:7007. |
| `udGZE_Clarke1880FOOT` | EPSG:7055. |
| `udGZE_Krassowsky1940` | EPSG:7024. |
| `udGZE_Everest1930M` | EPSG:7018. |
| `udGZE_Mars` |  |
| `udGZE_Moon` |  |
| `udGZE_IAG1975` |  |
| `udGZE_Everest1830` |  |
| `udGZE_GRS67` |  |
| `udGZE_ANS` | EPSG:7003. |
| `udGZE_INS` | EPSG:7021. |
| `udGZE_Count` |  |

### enum udGeoZoneGeodeticDatum

Supported udGeoZone geodetic datums 

*Values:*

| Value | Description |
|-------|-------------|
| `udGZGD_WGS84` | EPSG:4326. |
| `udGZGD_ED50` | EPSG:4230. |
| `udGZGD_ETRS89` | EPSG:4258,4936. |
| `udGZGD_TM75` | EPSG:4300. |
| `udGZGD_NAD27` | EPSG:4267. |
| `udGZGD_NAD27CGQ77` | EPSG:4609. |
| `udGZGD_NAD83` | EPSG:4269. |
| `udGZGD_NAD83_1996` | EPSG:6307. |
| `udGZGD_NAD83_CSRS` | EPSG:2955. |
| `udGZGD_NAD83_NSRS2007` | EPSG:3465. |
| `udGZGD_NAD83_2011` | EPSG:6318. |
| `udGZGD_NTF` | EPSG:4275. |
| `udGZGD_OSGB36` | EPSG:4277. |
| `udGZGD_Potsdam` | EPSG:4746. |
| `udGZGD_Tokyo` | EPSG:7414. |
| `udGZGD_WGS72` | EPSG:4322. |
| `udGZGD_JGD2000` | EPSG:4612. |
| `udGZGD_JGD2011` | EPSG:6668. |
| `udGZGD_GDA94` | EPSG:4283. |
| `udGZGD_GDA2020` | EPSG:7844. |
| `udGZGD_RGF93` | EPSG:4171. |
| `udGZGD_NAD83_HARN` | EPSG:4152. |
| `udGZGD_CGCS2000` | EPSG:4490. |
| `udGZGD_HK1980` | EPSG:4611. |
| `udGZGD_SVY21` | EPSG:4757. |
| `udGZGD_MGI` | EPSG:6312. |
| `udGZGD_NZGD2000` | EPSG:2193. |
| `udGZGD_AMERSFOORT` | EPSG:28992. |
| `udGZGD_TRI1903` | EPSG:30200. |
| `udGZGD_VANUA1915` | EPSG:3139. |
| `udGZGD_DEALUL1970` | EPSG:31700. |
| `udGZGD_SINGGRID` | EPSG:19920. |
| `udGZGD_MARS_MERC` | EPSG:49974,49975. |
| `udGZGD_MARS_PCPF` | EPSG:8705. |
| `udGZGD_MOON_MERC` | EPSG:30174,30175. |
| `udGZGD_MOON_PCPF` | EPSG:30100,30100. |
| `udGZGD_DBREF` | EPSG:5681. |
| `udGZGD_DHDN` | EPSG:4314. |
| `udGZGD_SJTSK03` | EPSG:8353. |
| `udGZGD_PULK1942` | EPSG:4284. |
| `udGZGD_PULK194258` | EPSG:4179. |
| `udGZGD_PULK194283` | EPSG:4178. |
| `udGZGD_PULK1995` | EPSG:20004. |
| `udGZGD_WGS_72BE` | EPSG:32401. |
| `udGZGD_BEIJING1954` | EPSG:21413. |
| `udGZGD_NEWBEIJING` | EPSG:4555. |
| `udGZGD_XIAN1980` | EPSG:4610. |
| `udGZGD_TIMB1948` | EPSG:28973. |
| `udGZGD_NZGD49` | EPSG:4272. |
| `udGZGD_SWEREF99` | EPSG:4619. |
| `udGZGD_SAD69` | EPSG:4291. |
| `udGZGD_GR96` | EPSG:4747. |
| `udGZGD_DGN95` | EPSG:4755. |
| `udGZGD_UCS2000` | EPSG:5561. |
| `udGZGD_H94` | EPSG:4148. |
| `udGZGD_ID74` | EPSG:4238. |
| `udGZGD_NGO1948` | EPSG:4273. |
| `udGZGD_RGF93v2b` | EPSG:9782. |
| `udGZGD_Count` |  |

### enum udGeoZoneProjectionType

Supported udGeoZone projection types 

*Values:*

| Value | Description |
|-------|-------------|
| `udGZPT_Unknown` |  |
| `udGZPT_ECEF` |  |
| `udGZPT_LongLat` |  |
| `udGZPT_LatLong` |  |
| `udGZPT_TransverseMercator` |  |
| `udGZPT_LambertConformalConic2SP` |  |
| `udGZPT_WebMercator` |  |
| `udGZPT_CassiniSoldner` |  |
| `udGZPT_CassiniSoldnerHyperbolic` |  |
| `udGZPT_SterographicObliqueNEquatorial` |  |
| `udGZPT_SterographicPolar_vB` |  |
| `udGZPT_Mercator` |  |
| `udGZPT_Krovak` |  |
| `udGZPT_KrovakNorthOrientated` |  |
| `udGZPT_HotineObliqueMercatorvA` |  |
| `udGZPT_HotineObliqueMercatorvB` |  |
| `udGZPT_AlbersEqualArea` |  |
| `udGZPT_EquidistantCylindrical` |  |
| `udGZPT_Count` |  |

## Functions

### enum [udError](udError.md) udGeoZone_GetGeodeticDatumDescriptor(const struct udGeoZoneGeodeticDatumDescriptor \*\*ppDescriptor, enum udGeoZoneGeodeticDatum datum)

Get a geodetic datum descriptor by index 

| Parameter | Description |
|-----------|-------------|
| `ppDescriptor` | A pointer to a descriptor pointer that will be set to the requested datum descriptor |
| `datum` | The geodetic datum index |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_GetGeodeticDatumDescriptors(const struct udGeoZoneGeodeticDatumDescriptor \*\*ppDescriptors, int32_t \*pCount)

Get the full array of geodetic datum descriptors 

| Parameter | Description |
|-----------|-------------|
| `ppDescriptors` | A pointer to a descriptor pointer that will be set to the first element of the array |
| `pCount` | Optional pointer to receive the number of elements in the array |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_GetEllipsoidInfo(const struct udGeoZoneEllipsoidInfo \*\*ppEllipsoid, enum udGeoZoneEllipsoid ellipsoid)

Get an ellipsoid info entry by index 

| Parameter | Description |
|-----------|-------------|
| `ppEllipsoid` | A pointer to an ellipsoid info pointer that will be set to the requested entry |
| `ellipsoid` | The ellipsoid index |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_GetEllipsoidInfoArray(const struct udGeoZoneEllipsoidInfo \*\*ppEllipsoids, int32_t \*pCount)

Get the full array of standard ellipsoid info entries 

| Parameter | Description |
|-----------|-------------|
| `ppEllipsoids` | A pointer to an ellipsoid info pointer that will be set to the first element of the array |
| `pCount` | Optional pointer to receive the number of elements in the array |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_LoadZonesFromJSON(const char \*pJSONStr, int \*pLoaded, int \*pFailed)

Loads a set of zones from a JSON file where each member is defined as “AUTHORITY:SRID” (eg. “EPSG:32756”)

| Parameter | Description |
|-----------|-------------|
| `pJSONStr` | A JSON-formatted string containing all the zones |
| `pLoaded` | Pointer to an integer that has the count of zones successfully loaded |
| `pFailed` | Pointer to an integer that has the count of zones unsuccessfully loaded |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_UnloadZones()

Unloads all loaded zones (only needs to be called once to unload all) 

* **Returns:**
  A [udError](udError.md) code, typically udE_Success 

### enum [udError](udError.md) udGeoZone_FindSRID(int32_t \*pSRIDCode, const udDouble3 \*pLatLong, enum udGeoZoneGeodeticDatum datum)

Find an appropriate SRID code for a given lat/long within UTM/WGS84 (for example using datum udGZGD_WGS84) 

| Parameter | Description |
|-----------|-------------|
| `pSRIDCode` | A pointer to which the SRID code is written upon success |
| `pLatLong` | A pointer to a udDouble3 where x is the latitude, y is the longitude (z is ignored) |
| `datum` | The geodetic datum (normally udGZGD_WGS84) |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_SetFromSRID(struct udGeoZone \*pZone, int32_t sridCode)

Set the zone structure parameters from a given srid code 

| Parameter | Description |
|-----------|-------------|
| `pZone` | A udGeoZone structure that will be overwritten with parameters for the given sridCode |
| `sridCode` | The sridCode for the desired zone |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_SetFromWellKnownText(struct udGeoZone \*pZone, const char \*pWKT)

Initialise a geozone structure from well known text 

| Parameter | Description |
|-----------|-------------|
| `pZone` | A udGeoZone structure that will be overwritten with parameters taken from the supplied Well Known Text |
| `pWKT` | A Well Known Text formatted string |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_GetWellKnownText(const char \*\*ppWKT, const struct udGeoZone \*pZone)

Get the Well Known Text for a zone 

> [!NOTE]
> The Well Known Text must be freed using udGeoZone_FreeWellKnownText

| Parameter | Description |
|-----------|-------------|
| `ppWKT` | A pointer to a string pointer that will be assigned with an allocated WKT string for the given zone |
| `pZone` | A valid udGeoZone structure used to generate the Well Known Text |

**Returns:** A [udError](udError.md) code

### void udGeoZone_FreeWellKnownText(const char \*\*ppWKT)

Free the Well Known Text returned by udGeoZone_GetWellKnownText 

| Parameter | Description |
|-----------|-------------|
| `ppWKT` | A pointer to a string pointer that was returned by udGeoZone_GetWellKnownText |

### enum [udError](udError.md) udGeoZone_LatLongToCartesian(udDouble3 \*pCartesian, const struct udGeoZone \*pZone, const udDouble3 \*pLatLong, enum udGeoZoneGeodeticDatum datum)

Convert a point from lat/long to the cartesian coordinate system defined by the zone 

| Parameter | Description |
|-----------|-------------|
| `pCartesian` | A pointer to a udDouble3 overwritten with the cartesian value of the transformed LatLong |
| `pZone` | A valid udGeoZone defining the coordinate system |
| `pLatLong` | A pointer to a udDouble3 containing the Latitude in x, Longitude in y, and altitude in Z |
| `datum` | The geodetic datum for the latlong coordinates, typically udGZGD_WGS84 |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_CartesianToLatLong(udDouble3 \*pLatLong, const struct udGeoZone \*pZone, const udDouble3 \*pPosition, enum udGeoZoneGeodeticDatum datum)

Convert a point from the cartesian coordinate system defined by the zone to lat/long 

| Parameter | Description |
|-----------|-------------|
| `pLatLong` | A pointer to a udDouble3 overwritten with the transformed Latitude in x, Longitude in y, and altitude in Z |
| `pZone` | A valid udGeoZone defining the coordinate system |
| `pCartesian` | A pointer to a udDouble3 containing the cartesian coordinates |
| `datum` | The geodetic datum for the latlong coordinates, typically udGZGD_WGS84 |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_LatLongToGeocentric(udDouble3 \*pGeocentric, const udDouble3 \*pLatLong, const struct udGeoZoneEllipsoidInfo \*pEllipsoid)

Conversion to and from Geocentric 

| Parameter | Description |
|-----------|-------------|
| `pGeocentric` | A pointer to a udDouble3 overwritten with the transformed geocentric coordinates |
| `pLatLong` | A pointer to a udDouble3 containing the Latitude in x, Longitude in y, and altitude in Z |
| `pEllipsoid` | The ellipsoid parameters as specified in the datum |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_GeocentricToLatLong(udDouble3 \*pLatLong, const udDouble3 \*pGeoCentric, const struct udGeoZoneEllipsoidInfo \*pEllipsoid)

Conversion to and from Geocentric 

| Parameter | Description |
|-----------|-------------|
| `pLatLong` | A pointer to a udDouble3 with the Latitude in x, Longitude in y, and altitude in Z |
| `pGeocentric` | A pointer to a udDouble3 containing the geocentric coordinates |
| `pEllipsoid` | The ellipsoid parameters as specified in the datum |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_ConvertDatum(udDouble3 \*pOutLatLong, const udDouble3 \*pInLatLong, enum udGeoZoneGeodeticDatum currentDatum, enum udGeoZoneGeodeticDatum newDatum)

Convert a lat/long pair in one datum to another datum 

| Parameter | Description |
|-----------|-------------|
| `pOutLatLong` | A pointer to a udDouble3 with the output Latitude in x, Longitude in y, and altitude in Z |
| `pInLatLong` | A pointer to a udDouble3 with the input Latitude in x, Longitude in y, and altitude in Z |
| `currentDatum` | The datum that the pInLatLong references |
| `newDatum` | The datum that the pOutLatLong references |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_TransformPoint(udDouble3 \*pTransformed, const udDouble3 \*pPoint, const struct udGeoZone \*pSourceZone, const struct udGeoZone \*pDestZone)

Transform a point from one zone to another 

| Parameter | Description |
|-----------|-------------|
| `pTransformed` | A pointer to a udDouble3 with the output transformed coordinates, which may be cartesian or latlong depending on the destination zone |
| `pPoint` | A pointer to a udDouble3 with the input coordinates, which may be cartesian or latlong depending on the source zone |
| `pSourceZone` | The zone that pPoint references |
| `pDestZone` | The zone the point is transformed to, which pTransformed references |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_TransformMatrix(udDouble4x4 \*pTransformed, const udDouble4x4 \*pMatrix, const struct udGeoZone \*pSourceZone, const struct udGeoZone \*pDestZone)

Transform a matrix from one zone to another 

| Parameter | Description |
|-----------|-------------|
| `pTransformed` | A pointer to a matrix that has been transformed to the destination zone |
| `pMatrix` | A pointer to a matrix that is in the source zone coordinate system |
| `pSourceZone` | The zone that pMatrix references |
| `pDestZone` | The zone that pTransformed references |

**Returns:** A [udError](udError.md) code

### enum [udError](udError.md) udGeoZone_UpdateSphereoidInfo(struct udGeoZone \*pZone)

Complete setup of a udGeoZone 

> [!NOTE]
> This is called after changing parameters of the zone

| Parameter | Description |
|-----------|-------------|
| `pZone` | The zone to complete the setup of |

**Returns:** A [udError](udError.md) code


## Structs

### struct udGeoZone

udGeoZone structure. Do not rely on element order as they may change in a future release.

| Field | Type | Description |
|-------|------|-------------|
| `datum` | `enum udGeoZoneGeodeticDatum` |  |
| `projection` | `enum udGeoZoneProjectionType` |  |
| `latLongBoundMin` | `udDouble2` |  |
| `latLongBoundMax` | `udDouble2` |  |
| `meridian` | `double` |  |
| `parallel` | `double` | Parallel of origin for Transverse Mercator. |
| `latProjCentre` | `double` | Latitude of Projection Centre for Krovak Projection. |
| `coLatConeAxis` | `double` | Co Latitude of the cone axis for Krovak Projection. |
| `flattening` | `double` |  |
| `semiMajorAxis` | `double` |  |
| `semiMinorAxis` | `double` |  |
| `thirdFlattening` | `double` |  |
| `eccentricity` | `double` |  |
| `eccentricitySq` | `double` |  |
| `radius` | `double` |  |
| `scaleFactor` | `double` |  |
| `n[10]` | `double` |  |
| `alpha[9]` | `double` |  |
| `beta[9]` | `double` |  |
| `firstParallel` | `double` |  |
| `secondParallel` | `double` |  |
| `falseNorthing` | `double` |  |
| `falseEasting` | `double` |  |
| `unitMetreScale` | `double` | 1.0 for metres, 0.3048006096012192 for feet |
| `zone` | `int32_t` |  |
| `srid` | `int32_t` |  |
| `datumShortName[16]` | `char` |  |
| `datumName[64]` | `char` |  |
| `zoneName[64]` | `char` | Full name for zone, only 33 characters required for longest known name “Japan Plane Rectangular CS XVIII”. |
| `displayName[128]` | `char` | This is the human readable name; often just datumShortName & zoneName concatenated. |
| `knownDatum` | `char` | boolean |
| `datumSrid` | `int32_t` |  |
| `toWGS84` | `char` | boolean |
| `axisInfo` | `char` | boolean |
| `zoneSpheroid` | `enum udGeoZoneEllipsoid` |  |
| `paramsHelmert7[7]` | `double` | TO-WGS84 as { Tx, Ty, Tz, Rx, Ry, Rz, DS }. |

### struct udGeoZoneGeodeticDatumDescriptor

Geodetic Datum descriptor, stored globally as g_udGZ_GeodeticDatumDescriptors

| Field | Type | Description |
|-------|------|-------------|
| `pFullName` | `const char \*` |  |
| `pShortName` | `const char \*` |  |
| `pDatumName` | `const char \*` |  |
| `ellipsoid` | `enum udGeoZoneEllipsoid` |  |
| `paramsHelmert7[7]` | `double` | TO-WGS84 as { Tx, Ty, Tz, Rx, Ry, Rz, DS }. |
| `epsg` | `int32_t` | epsg code for the datum |
| `authority` | `int32_t` | authority for this datum |
| `exportAxisInfo` | `char` |  |
| `exportToWGS84` | `char` |  |

### struct udGeoZoneEllipsoidInfo

Ellipsoid info

| Field | Type | Description |
|-------|------|-------------|
| `pName` | `const char \*` |  |
| `semiMajorAxis` | `double` |  |
| `flattening` | `double` |  |
| `authorityEpsg` | `int32_t` |  |
