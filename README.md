# UAE4ALL2 HD — Nintendo Switch Edition v1.04

A modern, high-performance Nintendo Switch release of **UAE4ALL2 HD**, the Amiga emulator for OCS, ECS, and AGA chipsets.

Release documentation: [`CHANGELOG.md`](CHANGELOG.md). License is available in [`LICENSE`](LICENSE) / [`copying`](copying).

This repository contains the complete Nintendo Switch source tree and ready-to-run release packages:

- **`uae4all2hd.nro`** — Nintendo Switch homebrew executable.
- **`uae4all2hd_switch.zip`** — Full standalone release archive ready to be extracted to SD card.

> [!NOTE]
> Looking for the PS Vita version? The official PS Vita release is available here:
> **[UAE4ALL2-HD-VITA](https://github.com/theheroGAC/UAE4ALL2-HD-VITA)**

---

## Features in this Nintendo Switch Release

- **Enhanced Game Library with Boxart & Metadata (v1.04)**:
  - Unified library browser with support for ADF, ADZ, DMS, IPF, LHA, WHDLoad, M3U, ZIP, and HDF games with 1-click launch (**A**), filter selection (**X**), and options (**Y**).
  - High-definition cover artwork rendering in the preview panel with aspect ratio preservation and single-surface RAM caching.
  - Multi-path artwork search across 7 standard directory locations (`./data/covers/`, `./covers/`, `sdmc:/...`, RomFS).
  - Built-in offline Amiga metadata database containing **2,599 games** (Title, Year, Developer, Publisher, Genre, Players) with smart fuzzy search tolerant to dump tags and disk suffixes.
  - In-app Cover Downloader powered by `libcurl`: download boxart directly on console via **(Y) -> Download Cover** in the Library or the WHDLoad menu.
  - Configurable cover download server URL in `./data/covers/source.txt`.
- **Full Amiga Emulation**: Amiga 500, 500+, 600, 1200 and CD32 hardware emulation (OCS, ECS, and AGA).
- **High-Performance CPU Cores**: Optimized Motorola 68000 and 68020 processor emulation with advanced condition code accuracy, normalized status register flags, corrected shift/rotate limits, and full 32-bit arithmetic.
- **Floppy Disk Support**: ADF, ADZ, DMS, IPF, FDI, and ZIP floppy disk images across DF0-DF3.
- **CAPS / IPF Support**: Built-in CAPS decoder for original commercial Amiga floppy dumps with copy-protection support.
- **Hard Disk Support (HDF & Folders)**: 4 HDF image slots and Amiga directory mounting (`DH0:`).
- **Integrated HDF Manager**: Create, format, and backup Fast File System (FFS) hard disks (from 50 MB to 4000 MB) directly within the GUI.
- **Dedicated WHDLoad Library & Launcher**:
  - 1-click game execution with automatic Amiga 1200 AGA hardware preset configuration.
  - Native high-performance LHA decompressor (`-lh5-`, `-lh4-`, `-lh0-`) with real-time extraction progress indicator and post-install launch confirmation dialog.
  - Automatic case-insensitive alphabetical sorting (**A to Z**) with support for up to **4,096 games** simultaneously.
  - Pre-bundled official WHDLoad binaries (`C:WHDLoad`, `C:WHDLoadCD32`, `C:DIC`, `C:Patcher`, `C:RawDIC`, `C:WArc`, `S:WHDLoad.prefs`).
  - Automatic Kickstart mapping and aliasing for WHDLoad slaves.
  - Custom WHDLoad Arguments editor with native on-screen keyboard.
  - Fast alphabetical jumping (**L / R** shoulders and D-Pad Left/Right) across installed games.
- **Authentic Mechanical Disk Audio Engine**:
  - Built-in Ogg Vorbis sound decoder (`stb_vorbis`) for genuine, high-fidelity floppy and hard drive sound samples (`floppy_drive.ogg`, `hard_drive.ogg`).
  - Realistic motor spin, track stepping, seek, and read/write acoustic simulation.
- **Save States**: 4 independent save slots with screenshot thumbnails and per-game state naming.
- **Touchscreen Mouse & Gestures**:
  - 1-finger tap = Left mouse click
  - 2-fingers tap / hold = Right mouse click
  - 1-finger drag = Move mouse cursor
  - 2-fingers drag = Left mouse drag & drop
  - 3-fingers drag = Right mouse drag & drop
- **Controls & Input**:
  - Direct 1:1 Nintendo Switch Joy-Con and Pro Controller physical button mapping.
  - Dedicated **Amiga Mouse Configuration** modal: map mouse to Right/Left Stick, D-Pad, or Touchscreen, adjust sensitivity (1x-10x) and acceleration curves, configure hold-to-slow (0.5x to 0.0625x) and hold-to-fast (1.5x to 5x) button modifiers, swap Left/Right buttons, and toggle Direct Touchscreen vs Trackpad modes.
  - Configurable Autofire rates (Slow, Medium, Turbo) and trigger modes.
  - In-game Virtual Keyboard (`vkbd`) toggled with **+ (Plus)** with deadzone filtering and full Joy-Con navigation.
- **High-Definition Switch GUI**:
  - Crisp HD interface (720p handheld / 1080p docked) across 9 intuitive tabs: Floppy, Hard Disk, WHDLoad, Presets, Hardware, Display, Controls, Savestates, and System.
  - Subpixel antialiased font rendering with balanced colors.
  - Live DF0-DF3 and HDF activity indicators.
- **Built-in Native Switch FTP Server**:
  - Integrated wireless FTP service running on port `5000` (BSD sockets).
  - Standard RFC 959 compliance, Extended Passive Mode (`EPSV`), and UTF-8 support for seamless transfer with FileZilla, WinSCP, or Windows Explorer.
  - Non-blocking server loop with instant exit on **B**, **A**, **+**, or touchscreen tap.
- **CD32 Emulation**: Akiko CD controller with ISO, raw BIN, and multi-track CUE images with CD audio mixing.
- **Compressed CHD Image Support**: Direct block decoding of `.chd` images for CD-ROM (CD32) and Hard Disks (HDF) with zero decompression overhead on RAM or SD card.
- **Multi-Disk Playlist (`.m3u`)**: Fast in-game disk swapping across up to 16 disks with hotkeys (`ZL + D-Pad Left/Right`) and Quick Menu integration.
- **Fast-Forward (Turbo Mode)**: Hold **ZR** or toggle via Quick Menu to skip disk loading screens and slow Amiga sequences.
- **5-Level Stereo Separation**: Customizable panning profiles (0% Mono, 25%, 50% Headphones, 75%, 100% Original Amiga).
- **Single Joy-Con Mode (Instant 2-Player Co-op / VS)**: Detach both Joy-Cons and play Amiga multiplayer classics (e.g. Sensible World of Soccer, Speedball 2, Lotus 2, Worms, Micro Machines) horizontally in Tabletop or TV Docked mode with SL/SR shoulder and face button fire support.
- **Advanced Display Filters & Shaders**: Complete suite of visual rendering modes including **CRT-Lottes** (simulated CRT shadow mask, Gaussian scanlines, and subtle vignette), **CRT-Easymode** (high-visibility aperture grille scanlines), **Scanlines (50%)**, **Scale2x** (pixel-art vectorized edge smoothing), **Sharp Bilinear** (pixel-perfect integer prescale with smooth interpolation), **Bilinear**, **Point (Nearest)**, and **Pixel-Perfect Integer** scaling.
- **Expanded Aspect Ratios**: Full support for authentic **4:3**, classic European monitor **5:4**, widescreen **16:9**, and **16:10 Wide** display aspect ratios.
- **Auto Crop & Screen Offsets**: Real-time black border detection (Both, Vertical, Horizontal) and fine X/Y positioning.
- **Quick Save & Quick Load**: On-the-fly savestates with native on-screen toast notifications (`ZL + R`, `ZL + L`, `ZL + Up/Down`).
- **Screenshots**: High-resolution PNG captures saved directly to `./screenshots/`.

---

## Directory Structure

When installed on the Nintendo Switch SD card (e.g. `sdmc:/switch/uae4all2/`):

```text
sdmc:/switch/uae4all2/
├── uae4all2hd.nro               # Main application binary
├── kickstarts/                  # Amiga Kickstart ROM files
├── roms/                        # ADF, IPF, HDF, and LHA game images
├── WHDLoad/                     # Root folder for installed WHDLoad games
├── saves/                       # In-game save states (.asf)
├── conf/                        # Saved custom configurations (.conf)
├── thumbs/                      # Save state screenshot previews (.png)
├── tmp/                         # Temporary working directory
└── data/                        # UI assets, fonts, sounds and base tools
    ├── whdload_base/            # Pre-bundled Amiga WHDLoad system tools (C/ and S/)
    ├── sounds/                  # Authentic floppy and hard disk OGG samples
    ├── covers/                  # Downloaded and custom game boxart (.png, .jpg) & source.txt
    ├── gameinfo/                # Offline game metadata database (games.json)
    └── font.ttf                 # TrueType UI font
```

---

## Installation

1. Copy `uae4all2hd.nro` to `sdmc:/switch/uae4all2/` (or extract `uae4all2hd_switch.zip` to the root of your SD card).
2. Copy legally obtained Kickstart ROMs to:
   ```text
   sdmc:/switch/uae4all2/kickstarts/
   ```
3. Copy your Amiga disk images (`.adf`, `.ipf`, `.hdf`, `.lha`) to `sdmc:/switch/uae4all2/roms/` (or any preferred folder on your SD card).
4. Launch **UAE4All2 HD** from the Nintendo Switch Homebrew Menu.
5. Select your disk, HDF, or WHDLoad game from the menu and press **+ (Plus)** or **A** to boot.

---

## Native FTP File Transfer

UAE4All2 HD includes a built-in FTP server on Nintendo Switch:

1. Open the **System** tab in the menu and select **FTP File Transfer**.
2. The FTP server starts immediately and displays your local IP address:
   ```text
   ftp://<SWITCH_IP>:5000
   ```
3. On your PC, open **FileZilla**, **WinSCP**, or Windows Explorer, enter the displayed IP address and port `5000` (anonymous login).
4. Transfer ADF, HDF, WHDLoad `.lha` files, and Kickstarts directly to the SD card.
5. Press **B**, **A**, **+ (Plus)**, or tap the screen to cleanly stop the FTP server and return to the System menu.

---

## Game Covers & Metadata Guide (v1.04)

UAE4All2 HD v1.04 includes a unified cover artwork loader, live metadata display, and an in-app cover downloader.

### How Game Covers Work
When browsing games in the **Game Library** or **WHDLoad** tabs, the emulator automatically displays matching boxart and metadata in the right-hand preview panel:
- **Aspect Ratio Preserved**: Covers are rendered crisply without distortion.
- **Memory Optimized**: Only the currently selected game's cover is loaded into RAM (single-surface engine).
- **Metadata Database**: Built-in offline database with **2,599 Amiga games** showing Year, Genre, Developer, Publisher, and Number of Players.

### 1. Adding Covers Manually (SD Card or FTP)
You can copy your own boxart images directly to your microSD card (via a PC card reader or the built-in FTP server):

1. Place `.png` or `.jpg` image files into:
   ```text
   sdmc:/switch/uae4all2/data/covers/
   ```
   *(Alternative: you can also place the image directly inside the same folder as the game ROM).*
2. **File Naming Rules**:
   - Match the game title: `Turrican II.png`
   - Or match the ROM filename: `Turrican II (Disk 1).adf.png`
   - Common dump tags and suffixes (e.g. `(Disk 1 of 2)`, `[AGA]`, `(v1.2)`) are ignored automatically when matching.

### 2. Downloading Covers Directly on Switch (Wi-Fi)
With your Nintendo Switch connected to Wi-Fi, you can download boxart directly without leaving the emulator:

1. Open the **Game Library** or **WHDLoad** tab.
2. Highlight the game you want a cover for.
3. Press **(Y)** on your controller to open the **Options Dialog**.
4. Select **"Download Cover"**.
5. The emulator connects via HTTP/HTTPS, downloads the cover, saves it to `data/covers/`, and immediately refreshes the preview.

### 3. Configuring the Cover Server URL
The download server URL is configurable via a simple text file:
```text
sdmc:/switch/uae4all2/data/covers/source.txt
```
Enter your preferred HTTP or HTTPS base URL on the first line:
```text
https://my-server.example.com/amiga/covers
```
The downloader appends `/<game_title>.png` (and falls back to `.jpg`) with URL percent-encoding.

---

## Controls

### Menu & File Browser Navigation

| Button | Action |
|---|---|
| **A** | Confirm / Select / Insert Disk / Launch |
| **B** | Back / Cancel / Toggle Floppy Write-Protect (PROT/RW) |
| **X** | Action / Install LHA / HDF Manager / Reboot Amiga |
| **Y** | Eject Disk / Clear / Reset |
| **L / R Shoulders** | Jump alphabetically to previous / next letter (A–Z) in game & disk lists |
| **ZL / ZR** | Previous / Next Menu Tab (or Page Up / Down in file lists) |
| **+ (Plus)** | Boot Amiga / Resume Emulation |
| **- (Minus)** | Toggle Favorite in WHDLoad library |
| **D-Pad / Left Stick** | Navigate menu items |
| **Touchscreen** | Direct UI touch selection |

### In-Game Controls

| Button | Action |
|---|---|
| **Left Stick / D-Pad** | Amiga Joystick (Port 2 / Port 1) |
| **B** | Fire Button 1 |
| **A** | Fire Button 2 / Jump |
| **X / Y** | Configurable Custom Buttons (Space, Return, Autofire) |
| **L Shoulder** | Quick Menu (Resume, Savestate, Turbo, Stereo, M3U Swap, Eject, Screenshot) |
| **ZR (Hold)** | Fast-Forward / Turbo Mode |
| **ZL + R** | Quick Save to active slot |
| **ZL + L** | Quick Load from active slot |
| **ZL + D-Pad Up / Down** | Cycle Quick Save Slot (1–5) |
| **ZL + D-Pad Right / Left** | Next / Previous Disk in `.m3u` playlist |
| **+ (Plus)** | Toggle Virtual On-Screen Keyboard (`vkbd`) |
| **- (Minus)** | Open Main Menu / Pause Emulation |
| **Touchscreen** | Mouse Pointer & Multi-touch Buttons |

### Virtual On-Screen Keyboard (`vkbd`) Controls

| Button | Action |
|---|---|
| **D-Pad / Left Stick** | Navigate cursor between virtual keys |
| **A (or X)** | Type / Press selected key |
| **B** | Backspace / Delete character |
| **X** | Shift (Uppercase / Symbols) |
| **Y** | Reset sticky modifier keys (Ctrl, Alt, Amiga) |
| **Right Stick (Up/Down)** | Move virtual keyboard position on screen |
| **Right Stick (Left/Right)** | Adjust keyboard transparency level |
| **+ (Plus)** | Close virtual keyboard |

---

## Special Features & In-Game Utilities

### Fast-Forward / Turbo Mode
Skip slow disk loading sequences, long intro screens, and floppy wait times:
- **Hold ZR Trigger**: Instantly fast-forwards the emulation as long as held; release to return to normal speed.
- **Quick Menu (L Shoulder)**: Toggle **Turbo: ON** for hands-free, continuous fast-forward until toggled back to **OFF**.

### Single Joy-Con Mode (2-Player Multiplayer)
Play Amiga co-op and versus classics (e.g. *Sensible Soccer*, *Speedball 2*, *Lotus 2*, *Worms*) anywhere without needing extra controllers:
- **Activate**: Enable `"Single Joy-Con Mode"` in the **Controls** menu tab or via the **Quick Menu** (**L**).
- **Detach Joy-Cons**: Both Joy-Cons are held horizontally. Works in both **TV Docked** mode and **Tabletop** mode (with the console kickstand open).
- **Controls**:
  - **SL / SR shoulders**: Fire 1 / Fire 2.
  - **Face buttons**: Directional actions & secondary fire.
  - **Analog Stick**: 8-way digital Amiga joystick movement.
  - **+ / - buttons**: Open menu / pause emulation.
  - Joy-Con 1 is assigned to Amiga Port 1 (Player 1); Joy-Con 2 is assigned to Amiga Port 0 (Player 2).

### 2-Player Mode with Separate Controllers (Detached Joy-Cons / Pro Controllers)
Play two-player games (e.g. *Golden Axe*, *Speedball 2*, *Lotus 2*) with **each player on their own controller** — including the two Joy-Cons detached from the console and held horizontally:

1. **Detach both Joy-Cons** from the console (or use two Pro Controllers / any combination of controllers). Once detached and held horizontally, the system sees them as **two separate controllers**.
2. Open the menu (**- (Minus)**) and go to the **Controls** tab, then set:
   - **Joystick Port** = `Amiga Port 1 (Joystick Port)`
   - **Single Joy-Con Mode (2 Players)** = **OFF** — with it OFF, each detached Joy-Con counts as an individual controller; leave it ON only for the paired single-controller mode described above.
   - **Number of Players** = **2** — required, otherwise Player 2 stays disabled.
   - **Custom Button Remapping** = OFF (default mapping).
3. Boot the game. In the game's title screen select the **2 PLAYER** option using Player 1's joystick and confirm with Fire.
4. Player assignments:
   - **Player 1** = controller index 0 → Amiga Port 1 (full button mapping: **B** = Fire 1, **A** = Fire 2, Left Stick / D-Pad = movement).
   - **Player 2** = controller index 1 → Amiga Port 0 (D-Pad / arrows = movement, **B**-equivalent button = Fire 1, **A**-equivalent button = Fire 2).
   - To find out which physical Joy-Con is Player 1, move the D-Pad on one of them at the title screen and see which player responds.

> [!TIP]
> A detached **left** Joy-Con has no dedicated face buttons; if Player 2 can move but not fire, give the **right** Joy-Con to Player 2 (it has the full A / B / X / Y button set).

> [!NOTE]
> With **Number of Players = 1** (default), the second Amiga port is reserved for mouse emulation and Player 2 input is ignored — this is the recommended setup for single-player games.


### Multi-Disk Playlist (`.m3u`)
Effortless disk swapping for multi-floppy games (e.g. *Monkey Island*, *Beneath a Steel Sky*):
- Create a text file with `.m3u` extension containing the names of your ADF files in order, one per line:
  ```text
  Monkey_Disk1.adf
  Monkey_Disk2.adf
  Monkey_Disk3.adf
  Monkey_Disk4.adf
  ```
- Insert the `.m3u` file into drive DF0.
- When prompted by the game to change disks, press **ZL + D-Pad Right** (next disk) or **ZL + D-Pad Left** (previous disk), or select the disk directly from the **Quick Menu** (**L**).
- An on-screen toast notification displays the newly inserted disk name.

### Compressed CHD Image Support (`.chd`)
Save substantial microSD card space with CHD compressed disk images:
- **CD32 CD-ROMs & Amiga Hardfiles (HDF)** can be loaded directly in `.chd` format.
- Reduces storage requirements by 50% to 70% with zero decompression overhead or wear on the microSD card.

### Stereo Separation (Audio Panning)
Amiga's Paula sound chip outputs 2 channels hard-left and 2 channels hard-right (100% panning), which can be fatiguing when using headphones on the Nintendo Switch:
- Open the **Quick Menu** (**L**) or the **Display/Audio** menu tab to select between 5 stereo separation profiles:
  - **0% (Mono)**
  - **25%**
  - **50% (Recommended for headphones)**
  - **75%**
  - **100% (Original Amiga hard-panning)**

### Quick Save & Quick Load
Save and reload game states in real-time without leaving gameplay:
- **ZL + R**: Quick Save to the active slot.
- **ZL + L**: Quick Load from the active slot.
- **ZL + D-Pad Up / Down**: Cycle active save slot (1 through 5).
- On-screen toast notifications confirm each save, load, and slot change.

### Video Filters & Display Scaling
Customize your display presentation via the **Display** menu tab:

| Filter / Shader | Description |
|---|---|
| **None** | Default nearest-neighbor scaling (auto 2x / 3x / 4x integer scaling when auto-crop is disabled). |
| **Sharp Bilinear** | Prescales to the highest integer multiple with nearest-neighbor, then scales to target display size with bilinear filtering to prevent pixel shimmering and uneven pixel sizes. |
| **Bilinear** | Full bilinear interpolation for a soft, smoothed image. |
| **Point (Nearest)** | Direct nearest-neighbor scaling preserving sharp square pixels at any resolution. |
| **CRT-Lottes** | Authentic cathode-ray tube emulation featuring an RGB triad phosphor aperture mask, non-linear Gaussian beam scanlines, and subtle vignette corner falloff. |
| **CRT-Easymode** | Clean, high-visibility CRT simulation combining an aperture grille subpixel pattern with beam scanline boost. |
| **Scanlines (50%)** | Classic horizontal scanlines at 50% opacity for a retro arcade monitor aesthetic. |
| **Scale2x** | Vectorized pixel-art smoothing algorithm that rounds corner edges while maintaining razor-sharp diagonal clarity without blur. |
| **Pixel-Perfect Integer** | Clamps display scaling to exact integer factors (e.g. 2x, 3x, 4x) for absolute geometric fidelity. |

#### Aspect Ratio Options
Under **Vertical Lines & Aspect**, choose how the Amiga image fills the Nintendo Switch display:
- **Upscaled (4:3)**: Standard authentic Amiga TV / monitor aspect ratio.
- **5:4**: Matches classic European Commodore 1084 / Microvitec CRT monitors.
- **16:9 Fullscreen**: Stretches video to completely fill the 16:9 Switch display (720p handheld / 1080p docked).
- **16:10 Wide**: Proportional wide aspect ratio delivering larger active playfield area with balanced geometry.

---

## Kickstart ROM Compatibility Table

Place your Kickstart ROMs in `sdmc:/switch/uae4all2/kickstarts/`:

| System | Version | Filename (UAE4ALL) | Amiga Forever / TOSEC Alias | Size | MD5 |
|---|---|---|---|---|---|
| A1000 | KS v1.1 rev 31.034 NTSC | `kick31034.A1000` | `amiga-os-110-ntsc.rom` | 262144 | `0b8442c311caa54fb12ec88eaaa9facf` |
| A1000 | KS v1.1 rev 32.034 PAL | `kick32034.A1000` | `amiga-os-110-pal.rom` | 262144 | `1fa1f93d3d7b51271dd1356b8b2b45a9` |
| A500-A2000 | KS v1.2 rev 33.180 | `kick12.rom`, `kick33180.A500` | `amiga-os-120.rom` | 262144 | `85ad74194e87c08904327de1a9443b7a` |
| A500-A2000 | KS v1.3 rev 34.005 | `kick13.rom`, `kick34005.A500` | `amiga-os-130.rom` | 262144 | `82a21c1890cae844b3df741f2762d48d` |
| A500+ | KS v2.04 rev 37.175 | `kick20.rom`, `kick37175.A500` | `amiga-os-204.rom` | 524288 | `dc10d7bdd1b6f450773dfb558477c230` |
| A600 | KS v2.05 rev 37.350 | `kick37350.A600` | `amiga-os-205-a600.rom` | 524288 | `465646c9b6729f77eea5314d1f057951` |
| A600-A2000 | KS v3.1 rev 40.063 | `kick40063.A600` | `amiga-os-310-a600.rom` | 524288 | `e40a5dfb3d017ba8779faba30cbd1c8e` |
| A1200 | KS v3.0 rev 39.106 | `kick39106.A1200` | `amiga-os-300-a1200.rom` | 524288 | `b7cc148386aa631136f510cd29e42fc3` |
| A1200 | KS v3.1 rev 40.068 | `kick31.rom`, `kick40068.A1200` | `amiga-os-310-a1200.rom` | 524288 | `646773759326fbac3b2311fd8c8793ee` |
| A4000 | KS v3.0 rev 39.106 | `kick39106.A4000` | `amiga-os-300-a4000.rom` | 524288 | `9b8bdd5a3fd32c2a5a6f5b1aefc799a5` |
| A4000 | KS v3.1 rev 40.068 | `kick40068.A4000` | `amiga-os-310-a4000.rom` | 524288 | `9bdedde6a4f33555b4a270c8ca53297d` |
| CD32 | KS + Extended v3.1 rev 40.060 | `kick40060.CD32` | combined 1 MiB image | 1048576 | `f2f241bf094168cfb9e7805dc2856433` |
| CD32 | KS v3.1 rev 40.060 | `kick40060.CD32` | `amiga-os-310-cd32.rom` | 524288 | `5f8924d013dd57a89cf349f4cdedc6b1` |
| CD32 | Extended ROM rev 40.060 | `kick40060.CD32.ext` | `amiga-os-310-cd32-ext.rom` | 524288 | `bb72565701b1b6faece07d68ea5da639` |

---

## Machine Hardware Presets

| Preset | CPU | Chipset | Kickstart | RAM Configuration |
|---|---|---|---|---|
| **Amiga 500** | 68000 (7 MHz) | OCS | 1.3 | 512 KiB Chip + 512 KiB Slow RAM |
| **Amiga 500+** | 68000 (7 MHz) | ECS | 2.04 | 1 MiB Chip + 1 MiB Fast RAM |
| **Amiga 600** | 68000 (7 MHz) | ECS | 2.05 | 2 MiB Chip + 8 MiB Fast RAM |
| **Amiga 1200** | 68020 (14 MHz) | AGA | 3.1 | 2 MiB Chip + 4 MiB Fast RAM |
| **Amiga CD32** | 68020 (14 MHz) | AGA | 3.1 CD32 + Ext | 2 MiB Chip + Akiko Controller |

---

## Building from Source

Prerequisites:
- [devkitPro](https://devkitpro.org/) with `devkitA64`, `libnx`, and Switch portlibs (`switch-sdl2`, `switch-sdl2_image`, `switch-sdl2_ttf`, `switch-libpng`, `switch-libjpeg-turbo`, `switch-libarchive`, `switch-zlib`, `switch-bzip2`).

Build steps:
```bash
export DEVKITPRO=/opt/devkitpro
export PATH=/opt/devkitpro/portlibs/switch/bin:/opt/devkitpro/devkitA64/bin:/opt/devkitpro/tools/bin:$PATH

mkdir build-switch && cd build-switch
cmake .. -DBUILD_NX=ON -DCMAKE_BUILD_TYPE=Release
make uae4all2.nro uae4all2_switch.zip
```

Output files:
- `uae4all2hd.nro`
- `uae4all2hd_switch.zip`

---

## Credits and acknowledgements

This project is a derivative work and would not exist without the original UAE4ALL and Vita ports. Full credit and thanks go to the original authors and contributors:

- **Chui**, **john4p**, **TomB**, **notaz**, **Bernd Schneider**, **Toni Wilen**, **Pickle**, **smoku**, **AnotherGuest**, **Anonymous engineer**, **finkel**, **Lubomyr**, **pelya** (Original UAE4ALL / UAE4ALL2 authors)
- **Cpasjuste** for the original Vita port, SDL-Vita work, shader support and performance improvements
- **rsn8887** for the Vita/Switch work and the UAE4ALL2 improvements (https://github.com/rsn8887/uae4all2)
- **theheroGAC** for the UAE4ALL2 HD Vita project, HD menu design, WHDLoad integration, CD32 & HDF enhancements (https://github.com/theheroGAC/UAE4ALL2-HD-VITA)
- **ScHlAuChi** for testing, ideas and virtual-keyboard contributions
- **wronghands** for the menu font, keyboard styles and design ideas
- **CrashMidnick** for the French virtual keyboard
- **Xerpi** and **frangarCJ** for Vita2D and shader-library work
- **The VitaSDK Team** for VitaSDK toolchain and libraries
- **Bert Jahn (Wepl)** for WHDLoad (http://www.whdload.de)
- **Aminet** for the Amiga software and WHDLoad game archive (https://aminet.net)
- **Timothy Lottes** for the CRT-Lottes shadow mask & CRT emulation shader
- **aliaspider** for the CRT-Easymode aperture grille shader
- **Andrea Mazzoleni** for the Scale2x pixel-art scaling algorithm
- **SPS (Software Preservation Society)** for CAPS / IPF image decoding support
- **Romain Tisserand (rtissera)** for libchdr (CHD image decompression library), and **Aaron Giles / The MAME Team** for the original CHD format and compression code

Please preserve the original project credits and license notices when redistributing or modifying this project.

## Legal notice

UAE4ALL2 HD is intended for use with legally acquired Amiga software and Kickstart ROMs. Amiga, UAE4ALL and related trademarks belong to their respective owners. This repository does not include copyrighted Kickstart ROMs, commercial games or commercial disk images.

## License

See `copying` and the original source files for the applicable license notices.
