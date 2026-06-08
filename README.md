# Unlimited Detail for Unreal Engine

An Unreal Engine 5 plugin that streams and renders massive **Unlimited Detail (`.UDS`) point clouds** using Nuclideon's udSDK. Datasets can be loaded from [udCloud](https://udcloud.nuclideon.com/), a self-hosted server, or directly from disk.

![Unlimited Detail rendering inside Unreal](mdcontent/example_unreal_1.png)

---

## Contents

- [Features](#features)
- [Requirements](#requirements)
- [Quick start](#quick-start)
- [Installation](#installation)
- [Configuring your udCloud API key](#configuring-your-udcloud-api-key)
- [Adding a point cloud to a scene](#adding-a-point-cloud-to-a-scene)
- [Blueprint API](#blueprint-api)
- [Sample assets](#sample-assets)
- [Building from source](#building-from-source)
- [Known limitations](#known-limitations)
- [Support](#support)
- [Credits](#credits)
- [License](#license)

---

## Features

- Stream `.UDS` point clouds from udCloud, a self-hosted udSDK server, or local files
- `UUDComponent` — a `UPrimitiveComponent` you can drop on any Actor or Blueprint
- Composite scene view extension that blends point cloud color and depth with the rest of the Unreal scene
- Project Settings panel for server URL and API key
- Built against udSDK 2.6

## Requirements

| | |
|---|---|
| Unreal Engine | **5.5 or newer** (uses renderer internal headers that moved in 5.5) |
| Platforms | Windows 64-bit, Linux (Ubuntu 25.10 / GCC x64). macOS is in progress — see [Known limitations](#known-limitations). |
| Account | A [udCloud](https://udcloud.nuclideon.com/) account for an API key, or access to a self-hosted udSDK server |

---

## Quick start

1. Get a udCloud API key from [udcloud.nuclideon.com](https://udcloud.nuclideon.com/) (see [Configuring your udCloud API key](#configuring-your-udcloud-api-key)).
2. Drop this plugin into your project's `Plugins/` folder (see [Installation](#installation)).
3. Open the project. In **Edit → Project Settings → Plugins → Unlimited Detail (udSDK)**, set:
   - **Server Path** → `https://udcloud.nuclideon.com`
   - **API Key** → paste your key
4. Restart the editor.
5. Add a **UD** component to any Actor, set its **URL** to a `.UDS` (e.g. `https://models.nuclideon.com/Japan/0_1_0.uds`), give the component a large scale, and drag the actor into your level.

That's it - Unlimited Detail will start streaming and rendering.

---

## Installation

### Option A — Pre-built release (recommended)

1. Download the latest release from the [Releases page](https://github.com/Nuclideon/UnrealIntegration/releases).
2. In your Unreal project root (next to your `.uproject` file), create a `Plugins/` folder if it doesn't already exist.
3. Extract the release archive into `Plugins/` so you end up with:

   ```
   YourProject/
   ├── YourProject.uproject
   └── Plugins/
       └── UnlimitedDetail/
           ├── UnlimitedDetail.uplugin
           ├── Source/
           └── ...
   ```
4. Right-click your `.uproject` → **Generate Visual Studio project files** (Windows) and rebuild, or just open the project — Unreal will prompt to rebuild the plugin module.

### Option B — From source

Clone this repository directly into your project's `Plugins/` folder:

```sh
cd YourProject/Plugins
git clone https://github.com/Nuclideon/UnrealIntegration UnlimitedDetail
```

Then regenerate project files and rebuild as above. See [Building from source](#building-from-source) for platform notes.

---

## Configuring your udCloud API key

The plugin requires a valid udSDK login before it can render. The easiest source is a [udCloud](https://udcloud.nuclideon.com/) account.

1. Go to [udcloud.nuclideon.com](https://udcloud.nuclideon.com/) and sign in.

   ![udCloud welcome](mdcontent/udcloud_Welcome.png)

2. Click your display name (top right) → **API Keys**.

   ![udCloud display name menu](mdcontent/udcloud_display_name_clicked.png)

3. Click **Create API Key**, give it a display name, optionally set an expiry, and click **Create**.

   ![Create API key](mdcontent/udcloud_create_apikey.png)

4. In the API key list, open the **…** menu on the new key and choose **Copy API Key to Clipboard**.

   ![Copy API key](mdcontent/udcloud_copy_apikey.png)

A key looks like this (this is a fake example — yours will be different):

```
eyJhcGlrZXlpZCI6IjAxMjM0sdf343fsdf33vsTIyMjItMzMzMy00NDQ0NTU1NTY2NjYiLCJ1c2VyaWQiOiIwMTIzNDU2NASD4334DD3dAIyLTMzMzMtNDQ0NDU1NTU2NjY2IiwidmVyc2lvbiI6IjEifQ==
```

> **Treat the key like a password.** Anyone with the string can use anything your account can. Prefer keys with a short expiry where possible, and never commit them to source control.

Then in Unreal:

1. **Edit → Project Settings**, scroll to **Plugins → Unlimited Detail (udSDK)**.

   ![Project Settings — Unlimited Detail](mdcontent/projectsettings_APIKey.png)

2. Set **Server Path** to `https://udcloud.nuclideon.com` (or your self-hosted server URL).
3. Paste your key into **API Key**.
4. **Restart the editor.** The plugin authenticates at startup; it will not begin rendering until a successful login.

If authentication fails, the editor shows one of:

| Error | Cause |
|---|---|
| ![Server unreachable](mdcontent/apikey_fail_Server.png) | `Server Path` is empty or unreachable |
| ![Invalid key](mdcontent/apikey_fail_invalid_key.png) | The API key is malformed, expired, or revoked |

> Settings are stored in `Config/DefaultUnlimitedDetail.ini`. Because that file contains your API key, you should add it to your project's `.gitignore`.

---

## Adding a point cloud to a scene

1. In the Content Browser, right-click → **Blueprint Class → Actor**, and give it a name.

   ![Create a Blueprint actor](mdcontent/example_create_blueprint.png)

2. Open the new Blueprint. In the components panel, click **+ Add** and search for **UD**.

   ![Add UD component](mdcontent/example_component_search.png)

3. With the **UD** component selected, set:
   - **URL** — a `.UDS` URL (e.g. `https://models.nuclideon.com/Japan/0_1_0.uds`) or absolute path to a local `.UDS` file
   - **Scale** — start large (e.g. 1000×1000×1000); most production datasets are huge in world units

   ![Set URL and scale](mdcontent/example_large_scale.png)

4. Compile and save the Blueprint, then drag it into a level. The point cloud begins streaming immediately.

   ![Rendering in Unreal](mdcontent/example_unreal_2.png)

You can also add the UD component directly to a C++ Actor class — it derives from `UPrimitiveComponent` and behaves like any other scene component.

---

## Blueprint API

The `UUDComponent` exposes the following Blueprint-accessible members:

| Member | Type | Description |
|---|---|---|
| `URL` | `String` (property) | Source of the `.UDS` to load. Setting this at runtime triggers a reload. |
| `Get Url` | function | Returns the current URL. |
| `Set Url` | function | Sets the URL and reloads the point cloud. |
| `Refresh Point Cloud` | function | Unloads and reloads the current URL — useful after server-side changes. |
| `Reset Scale` | function | Resets the component scale to a sensible default for the loaded dataset. |

All functions live under the **UnlimitedDetail** category in the Blueprint editor.

---

## Sample assets

A public demo dataset is hosted at:

```
https://models.nuclideon.com/Japan/0_1_0.uds
```

Drop that URL into any UD component to verify your setup is working without uploading a dataset of your own.

You can also point the component at any absolute path to a `.UDS` file on local disk.

---

## Building from source

### Windows (x64)

Out of the box. The `udSDK.dll` is copied from `Plugins/UnlimitedDetail/Source/udSDK/lib/win_x64/` into your project's `Binaries/Win64/` folder during build.

### Linux (Ubuntu 25.10 / GCC x64)

Build with the standard Unreal Linux toolchain. The plugin links against `libudSDK.so` from `Plugins/UnlimitedDetail/Source/udSDK/lib/ubuntu25.10_GCC_x64/` and bundles it into `Binaries/Linux/`.

### macOS

Not yet supported. The udSDK distribution ships a `.dmg` rather than a usable `.dylib`; once a `.dylib` is extracted and the build script is filled in (see the macOS block in [`UnlimitedDetail.Build.cs`](Plugins/UnlimitedDetail/Source/UnlimitedDetail/UnlimitedDetail.Build.cs)), Mac builds will be enabled.

---

## Known limitations

- **macOS is not yet supported.** Building for Mac throws a `BuildException` with extraction instructions. See [`UnlimitedDetail.Build.cs`](Plugins/UnlimitedDetail/Source/UnlimitedDetail/UnlimitedDetail.Build.cs).
- **Object picking is a work in progress.** Hit-testing against Unlimited Detail geometry from Blueprint/C++ is partially implemented and not yet shipping-ready.
- **The `UnlimitedDetail` runtime module's `PlatformAllowList` currently lists `Win64` only** in [`UnlimitedDetail.uplugin`](Plugins/UnlimitedDetail/UnlimitedDetail.uplugin). Add `"Linux"` (and `"Mac"` once available) to that list before packaging for those platforms.

---

## Support

- File issues at [github.com/Nuclideon/UnrealIntegration/issues](https://github.com/Nuclideon/UnrealIntegration/issues).
- Email [info@nuclideon.com](mailto:info@nuclideon.com) for licensing or commercial enquiries.

---

## Credits

The original Unreal Engine 4 integration this plugin is built upon was created by community members [zengweicheng666](https://github.com/zengweicheng666) and [EuleeStar](https://github.com/EuleeStar) — see the [original UE4 repository](https://github.com/zengweicheng666/UdSDKProject). The Unreal Engine 5 plugin is maintained by [Nuclideon](https://nuclideon.com/).

---

## License

- **Plugin source** — see the repository's `LICENSE` file.
- **udSDK** — Nuclideon's terms apply; see [`udSDKLicense.md`](Plugins/UnlimitedDetail/Source/udSDK/udSDKLicense.md).
