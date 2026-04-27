# udCompare

udCompare.h provides an interface to compare Unlimited Detail models. 

## Functions

### enum [udError](udError.md) udCompare_BPA(struct udConvertContext \*pConvertContext, struct udCompareBPAOptions \*pOptions)

Compares input models using the Ball-Pivot Algorithm (BPA). A meshing operation is first performed using BPA followed by a cloud to model (C2M) comparison

> [!NOTE]
> This function does not start the conversion process, this allows the user to make additional changes to the convert job.

| Parameter | Description |
|-----------|-------------|
| `pConvertContext` | The convert context to be used to compare the models. |
| `pOptions` | The parameters passed to the BPA algorithm |

**Returns:** A [udError](udError.md) value based on the result of setting up BPA on the input models.


## Structs

### struct udCompareBPAOptions

Contains the options for the comparison algorithm

| Field | Type | Description |
|-------|------|-------------|
| `pBaseModelPath` | `const char \*` |  |
| `pComparisonModelPath` | `const char \*` | The path to the UDS model that pComparisonModel will be compared against. |
| `pOutputName` | `const char \*` | The path to the UDS model for comparison. |
| `meshingOptions` | `struct [udMeshingBPAOptions](udMeshing.md)` | The path that the displacement result UDS will be written to. |
