# UAE4ALL2 HD — Nintendo Switch Edition v1.00

A modern, high-performance Nintendo Switch release of **UAE4ALL2 HD**, the Amiga emulator for OCS, ECS, and AGA chipsets.

Release documentation: [`CHANGELOG.md`](CHANGELOG.md). License is available in [`LICENSE`](LICENSE) / [`copying`](copying).

This repository contains the complete Nintendo Switch source tree and ready-to-run release packages:

- **`uae4all2hd.nro`** — Nintendo Switch homebrew executable.
- **`uae4all2hd_switch.zip`** — Full standalone release archive ready to be extracted to SD card.

---

## Features in this Nintendo Switch Release

- **Full Amiga Emulation**: Amiga 500, 500+, 600, 1200 and CD32 hardware emulation (OCS, ECS, and AGA).
- **High-Performance CPU Cores**: Optimized 68000 and 68020 processor emulation.
- **Floppy Disk Support**: ADF, ADZ, DMS, IPF, FDI, and ZIP floppy disk images across DF0-DF3.
- **CAPS / IPF Support**: Built-in CAPS decoder for original commercial Amiga floppy dumps with copy-protection support.
- **Hard Disk Support (HDF & Folders)**: 4 HDF image slots and Amiga directory mounting (`DH0:`).
- **Integrated HDF Manager**: Create, format, and backup Fast File System (FFS) hard disks (from 50 MB to 4000 MB) directly within the GUI.
- **Dedicated WHDLoad Library & Launcher**:
  - 1-click game execution with automatic Amiga 1200 AGA hardware preset configuration.
  - Native high-performance LHA decompressor (`-lh5-`, `-lh4-`, `-lh0-`) with real-time extraction progress indicator.
  - Pre-bundled official WHDLoad binaries (`C:WHDLoad`, `C:WHDLoadCD32`, `C:DIC`, `C:Patcher`, `C:RawDIC`, `C:WArc`, `S:WHDLoad.prefs`).
  - Automatic Kickstart mapping and aliasing for WHDLoad slaves.
  - Custom WHDLoad Arguments editor with native on-screen keyboard.
  - Fast alphabetical jumping (**L / R** shoulders) across installed games.
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
    ├── covers/                  # Downloaded and custom game boxart
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
| **A** | Fire Button 1 |
| **B** | Fire Button 2 / Jump |
| **X / Y** | Configurable Custom Buttons (Space, Return, Autofire) |
| **L Shoulder** | Quick Menu (Resume, Savestate, Eject, Screenshot) |
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
- **SPS (Software Preservation Society)** for CAPS / IPF image decoding support

Please preserve the original project credits and license notices when redistributing or modifying this project.

## Legal notice

UAE4ALL2 HD is intended for use with legally acquired Amiga software and Kickstart ROMs. Amiga, UAE4ALL and related trademarks belong to their respective owners. This repository does not include copyrighted Kickstart ROMs, commercial games or commercial disk images.

## License

See `copying` and the original source files for the applicable license notices.
