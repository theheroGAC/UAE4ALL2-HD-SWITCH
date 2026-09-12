# UAE4ALL2 HD — Nintendo Switch Edition (v1.05)

A modern, high-performance, and user-friendly Amiga emulator for Nintendo Switch, supporting Amiga 500, 500+, 600, 1200 (AGA), and CD32 hardware.

This repository provides the complete Nintendo Switch source code and ready-to-run release packages:
- **`uae4all2hd.nro`**: Nintendo Switch homebrew executable.
- **`uae4all2hd_switch.zip`**: Complete standalone release package ready to be extracted to a microSD card.

Release notes and version history are available in [`CHANGELOG.md`](CHANGELOG.md). License information is provided in [`copying`](copying) and [`LICENSE`](LICENSE).

---

## Quick Start: Play in 3 Simple Steps

You do not need to be an Amiga expert to get started. Follow these three steps:

### 1. Copy Files to MicroSD
- Download the standalone release archive **`uae4all2hd_switch.zip`**.
- Extract the archive to the root of your Nintendo Switch microSD card.
- All emulator files will reside in:
  ```text
  sdmc:/switch/uae4all2/
  ```

### 2. Add Kickstart BIOS ROMs
Like original Amiga computers, the emulator requires Kickstart ROM files to boot. Place your legally acquired Kickstart ROMs into:
```text
sdmc:/switch/uae4all2/kickstarts/
```

> [!TIP]
> The two essential Kickstart files that boot the vast majority of games are:
> - `kick13.rom` (Kickstart 1.3 for Amiga 500 games)
> - `kick31.rom` (Kickstart 3.1 for Amiga 1200 AGA games)

### 3. Add Games and Launch
- Copy your game files (`.lha`, `.adf`, `.hdf`, `.iso`, `.chd`) into the `roms/` or `WHDLoad/` folder.
- Boot your Nintendo Switch into the Homebrew Menu and launch **UAE4All2 HD**.
- Select your game in the **Game Library** and press **A** to launch with 1 click.

---

## Controls Guide

### Menu & File Browser Navigation

| Button | Action |
|---|---|
| **A** | Confirm / Launch game / Enter directory |
| **B** | Back / Cancel |
| **X** | Install LHA package / Hard Disk Manager / Reboot Amiga |
| **Y** | Game Options (Download Cover via Wi-Fi, Eject floppy) |
| **L / R Shoulders** | Alphabetical jump (A to Z) across game lists |
| **ZL / ZR** | Switch menu tabs (Library, Floppy, Display, Controls, System) |
| **+ (Plus)** | Boot / Resume emulation |
| **- (Minus)** | Toggle Favorite status in game list |
| **Left Stick / D-Pad** | Navigate menu items and lists |
| **Touchscreen** | Direct UI touch selection |

---

### In-Game Controls

| Button | Amiga Function |
|---|---|
| **Left Stick / D-Pad** | Amiga Joystick (Directional movement) |
| **B** | Fire Button 1 (Primary fire / action) |
| **A** | Fire Button 2 / Jump |
| **X / Y** | Custom mapped buttons (Space, Return, Autofire) |
| **L Shoulder** | Quick Menu overlay (Save, Load, Turbo, Audio, Screenshot) |
| **ZR (Hold)** | Fast-Forward / Turbo Mode (skip disk loading screens) |
| **+ (Plus)** | Toggle Virtual On-Screen Keyboard |
| **- (Minus)** | Pause emulation and open Main Menu |
| **Touchscreen** | Amiga Mouse pointer (one finger tap = left click, two fingers tap = right click) |

---

### Dedicated Pinball Mode (v1.05)

If you play Amiga pinball classics like *Pinball Dreams*, *Pinball Fantasies*, *Pinball Illusions*, or *Slam Tilt*, you can turn your Nintendo Switch into an authentic pinball machine:

1. Open the menu with **- (Minus)** and go to the **Controls** tab.
2. Toggle **`Pinball Mode (L/R Flippers)`** to **ON** (or select **`Profile 2 (Pinball)`**).

**Pinball Button Mapping:**
- **L or ZL**: Left Flipper
- **R or ZR**: Right Flipper
- **X or Stick Down**: Plunger / Launch ball (Down Arrow + Space)
- **A / B / Y**: Directional table nudge (left, right, center)

---

### 2-Player Multiplayer

Play two-player Amiga games like *Sensible World of Soccer*, *Micro Machines*, *Speedball 2*, *Lotus 2*, or *Worms*:

#### Option 1: Single Joy-Con Mode (Horizontal Joy-Cons)
1. Detach both Joy-Cons from the console and hold them horizontally.
2. Open the menu (**-**), open the **Controls** tab, and set **`Single Joy-Con Mode (2 Players)`** to **ON**.
3. Use the stick to move and the **SL / SR** shoulder buttons to fire. Player 1 is assigned to Joy-Con 1 and Player 2 to Joy-Con 2.

#### Option 2: Dual Independent Controllers (Pro Controllers / Joy-Con Pairs)
1. Connect both controllers to the Nintendo Switch.
2. In the **Controls** tab, set:
   - **Number of Players** = **2**
   - **Joystick Port** = `Amiga Port 1 (Joystick Port)`
   - **Single Joy-Con Mode** = **OFF**
3. Start the game and choose 2-Player mode on the game's title screen. Controller 1 controls Amiga Port 1 (Player 1) and Controller 2 controls Amiga Port 0 (Player 2).

---

### Handy In-Game Hotkeys

Perform common actions during gameplay without entering the configuration menu:
- **`ZL + R`**: Instant Quick Save to the active save slot.
- **`ZL + L`**: Instant Quick Load from the active save slot.
- **`ZL + D-Pad Up / Down`**: Cycle active save slot (1 through 5).
- **`ZL + D-Pad Left / Right`**: Swap floppy disks in multi-disk `.m3u` playlists.
- **`ZR (Hold)`**: Fast-forward emulation to bypass slow loading sequences.
- **`+ (Plus)`**: Open or close the virtual keyboard. Move it or adjust opacity using the Right Stick.

---

## Main Features Explained Simply

- **1-Click Game Library with Artwork & Metadata**:
  Browse all your installed games (WHDLoad, ADF floppies, HDF hardfiles, CD32 images, M3U playlists) in one unified screen with high-resolution boxart, release year, developer, publisher, genre, and player count. Select any game and press **A** to launch immediately.
- **In-App Cover Downloader (Wi-Fi)**:
  Download official boxart directly onto the console without a PC. Highlight any game, press **(Y)** to open the Options dialog, and select **"Download Cover"**.
- **Smooth 60 FPS Menus without Slowdowns (v1.05)**:
  All game lists, metadata, and boxart references are cached in RAM. Browsing hundreds of games is instant, responsive, and completely free from microSD card reading bottlenecks or stutter.
- **Automatic Hardware Profiles (v1.05)**:
  The emulator automatically detects whether a WHDLoad game was designed for an Amiga 500 (OCS/ECS) or an Amiga 1200 (AGA) and applies the correct CPU architecture and memory layout. Clear color badges (Green for A500, Orange for A1200) indicate the active profile.
- **Accurate Graphics & Speed Calibration**:
  Fixes timing issues in classic games: resolved the crash in *Shadow Dancer* during ninja movement, and fixed the doubled speed and distorted audio in *Golden Axe* by dynamically assigning the ideal blitter mode.
- **Built-in Wireless FTP Server (v1.05)**:
  Transfer games, Kickstarts, covers, and saves over Wi-Fi using FileZilla, WinSCP, or a smartphone without removing the microSD card. Full RFC 3659 parity (`MLSD`/`MLST`) guarantees flawless directory listing with no `502 Command not implemented` errors.
- **Retro CRT Display Filters & Aspect Ratios**:
  Enjoy authentic cathode-ray tube rendering with **CRT-Lottes** (phosphor mask, beam scanlines, and vignette) and **CRT-Easymode**, or razor-sharp pixel-art with **Sharp Bilinear** and **Scale2x**. Supports authentic **4:3**, classic monitor **5:4**, widescreen **16:9**, and **16:10 Wide**.
- **Authentic Mechanical Drive Audio**:
  Real acoustic sound simulation using genuine audio samples for floppy drive motor spinning, track seeking, and hard disk access.
- **Headphone-Friendly Stereo Panning**:
  Amiga's original 100% hard-left / hard-right stereo separation can be fatiguing with headphones. UAE4ALL2 allows adjusting stereo separation (e.g. 50% or mono) for comfortable listening.

---

## MicroSD Folder Structure

All files reside inside `sdmc:/switch/uae4all2/`:

```text
sdmc:/switch/uae4all2/
├── uae4all2hd.nro               # Main application binary
├── kickstarts/                  # Amiga Kickstart ROM files (BIOS)
├── roms/                        # Game images (.adf, .ipf, .hdf, .lha, .chd)
├── WHDLoad/                     # Extracted WHDLoad game folders
├── saves/                       # In-game save states (.asf)
├── conf/                        # Saved custom game configurations (.conf)
├── thumbs/                      # Save state screenshot previews (.png)
├── screenshots/                 # User captured gameplay screenshots (.png)
└── data/
    ├── covers/                  # Boxart image files (.png, .jpg) & source.txt
    ├── sounds/                  # Floppy and hard drive mechanical audio samples (.ogg)
    └── gameinfo/                # Offline Amiga database with 2,500+ games (games.json)
```

---

## Kickstart ROM Compatibility Guide

Place your Kickstart ROM files into `sdmc:/switch/uae4all2/kickstarts/` using these recommended filenames:

| Amiga Model | Version | Recommended Filename | Description |
|---|---|---|---|
| **Amiga 500** | Kickstart 1.3 | **`kick13.rom`** | Essential for most classic games (1985–1992) |
| **Amiga 1200** | Kickstart 3.1 | **`kick31.rom`** | Essential for AGA games and WHDLoad titles |
| **Amiga 500+** | Kickstart 2.04 | **`kick20.rom`** | Compatible with ECS titles |
| **Amiga 600** | Kickstart 2.05 | **`kick37350.A600`** | Specific to Amiga 600 systems |
| **Amiga CD32** | Kickstart 3.1 | **`kick40060.CD32`** | Primary BIOS for CD32 games |
| **Amiga CD32** | Extended ROM | **`kick40060.CD32.ext`** | Akiko controller and CD-ROM filesystem |

---

## Frequently Asked Questions (FAQ)

### 1. A game shows a black screen or fails to boot. What should I check?
- Ensure you have placed `kick13.rom` (for Amiga 500 games) and `kick31.rom` (for Amiga 1200 AGA games) inside `sdmc:/switch/uae4all2/kickstarts/`.
- If the game is a WHDLoad title, verify if it requires Amiga 500 or Amiga 1200 hardware. You can force the desired hardware model under the **WHDLoad** menu tab using **WHDLoad Hardware**.

### 2. How do I connect to the Switch from my PC via Wi-Fi (FTP)?
1. Ensure your Nintendo Switch and PC are connected to the same local Wi-Fi network.
2. In UAE4ALL2, open the **System** tab and select **FTP File Transfer**.
3. Note the displayed IP address and port (e.g. `ftp://192.168.1.15:5000`).
4. On your PC, open **FileZilla** or **WinSCP**, enter the IP address into the Host field and `5000` into the Port field, and connect as an Anonymous user.
5. You can copy games, manage files, and upload covers directly over Wi-Fi.

### 3. How do multi-disk games work (.m3u)?
Create a plain text file named with an `.m3u` extension containing the names of your floppy disk images in order, one per line:
```text
Monkey_Island_Disk1.adf
Monkey_Island_Disk2.adf
Monkey_Island_Disk3.adf
Monkey_Island_Disk4.adf
```
Load the `.m3u` file into drive DF0. When prompted by the game to change disks, press **`ZL + D-Pad Right`** to switch to the next disk.

### 4. How do I install WHDLoad games (.lha)?
1. Copy the `.lha` file into `sdmc:/switch/uae4all2/roms/`.
2. In the emulator's **WHDLoad** tab, press **X** on the file to install it. The archive is automatically extracted to `WHDLoad/`, and a prompt will ask if you want to boot the game immediately.

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

## Credits and Acknowledgements

- **Original UAE4ALL / UAE4ALL2 authors**: Chui, john4p, TomB, notaz, Bernd Schneider, Toni Wilen, Pickle, smoku, AnotherGuest, Anonymous engineer, finkel, Lubomyr, pelya.
- **Cpasjuste**: Original Vita port, SDL-Vita, shaders and performance optimizations.
- **rsn8887**: Vita and Switch ports, controller mappings and UAE4ALL2 enhancements.
- **theheroGAC**: UAE4ALL2 HD Vita project, HD menu design, WHDLoad integration, CD32 & HDF enhancements ([UAE4ALL2-HD-VITA](https://github.com/theheroGAC/UAE4ALL2-HD-VITA)).
- **Bert Jahn (Wepl)**: Author of WHDLoad (http://www.whdload.de).
- **Timothy Lottes**: CRT-Lottes shader.
- **aliaspider**: CRT-Easymode shader.
- **Andrea Mazzoleni**: Scale2x algorithm.
- **Software Preservation Society**: CAPS / IPF floppy decoding.
- **Romain Tisserand & MAME Team**: libchdr (CHD compression).

---

## Legal Notice and License

UAE4ALL2 HD is intended for use with legally acquired Amiga software and Kickstart ROMs. Amiga is a registered trademark of its respective owners. This software is released under the GNU General Public License v2 (GPL-2.0). See [`copying`](copying) for details.
