# udStreamer

## Functions

### enum [udError](udError.md) udStreamer_Init(uint64_t memoryThresholdBytes)

Initialises the UDS streamer

> [!NOTE]
> If the streamer hasn’t been initialised before loading a UDS or creating a udRenderContext it will be initialised during those using default values

> [!WARNING]
> If memoryThresholdBytes is non-zero (which will use the default amount of memory) the return code will be udE_CalledMoreThanOnce if the streamer has already been started

| Parameter | Description |
|-----------|-------------|
| `memoryThresholdBytes` | Sets the threshold for how much memory the streaming system should *attempt* to stay below in bytes. Set as 0 to use the default amount of memory for the current platform. |

### enum [udError](udError.md) udStreamer_Deinit()

Deinitialises the UDS streamer (reference counted). This must be called once for every call to udStreamer_Init regardless of return code of that function to decrease the reference count. 

### enum [udError](udError.md) udStreamer_Update(struct udStreamerStatus \*pStatus)

Updates the UDS streamer manually (used in conjuction with udRCF_ManualStreamerUpdate)

> [!NOTE]
> The application should call this immediately after the last render for the frame

| Parameter | Description |
|-----------|-------------|
| `pStatus` | A structure to write streaming information to; Use NULL if the information isn’t required |


## Structs

### struct udStreamerStatus

Stores returned information from a streamer update

| Field | Type | Description |
|-------|------|-------------|
| `active` | `uint32_t` | Not 0 if streamer has blocked to load, or models are awaiting destruction. |
| `highestBlockPriority` | `int` | Highest priority of any block waiting to be loaded (reduces to zero as streaming completes). |
| `modelErrors` | `enum [udError](udError.md)` | Any errors from streaming. |
| `avgBytesPerSecond` | `int` | Data Throughput. |
| `blocksInQueue` | `int` | How many blocks (sections of a pointcloud) are waiting to be loaded. |
| `blocksInFlight` | `int` | How many blocks are actively being loaded. |
| `freeableBlocksLocked` | `int` | How many blocks are loaded that aren’t being used right now. |
| `blockMemoryInUse` | `int64_t` | Total (approximate) memory in use by the streamer (in bytes). |
| `positionMemoryInUse` | `int64_t` | Amount of memory used by positional data for all blocks loaded. |
| `freeableMemory` | `int64_t` | Amount of memory used by blocks on the freeable list. |
| `blocksReadSinceLastUpdate` | `int` | Number of blocks whose read was started. |
| `blocksLoadedSinceLastUpdate` | `int` | Number of blocks that actually finished and unpacked. |
| `blocksActive` | `int` | Number of blocks potentially loadable before next update. |
| `modelsActive` | `int` | Number of models actively requesting blocks. |
| `totalBlocksLoaded` | `int` | How many blocks are loaded. |
| `starvedTimeMsSinceLastUpdate` | `int` | Number of milliseconds spent with waiting for more work that came on the very on the next update. |
