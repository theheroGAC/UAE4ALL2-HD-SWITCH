# Changelog — UAE4ALL2 HD (Nintendo Switch)

All notable features, quality-of-life enhancements, and bug fixes for **UAE4ALL2 HD** on Nintendo Switch.

## Version 1.05

### User-Friendly Highlights
- **Smooth 60 FPS Menus (No More Slowdowns)**:
  - Game library navigation and cover browsing are now instantaneous and smooth.
  - Game listings, metadata, and artwork lookups are cached in RAM, completely eliminating microSD card read bottlenecks and stutter.
  - Smooth D-Pad and analog stick auto-repeat allows rapid, fluid navigation through large game collections.
- **Automatic Amiga Hardware Profiles (A500 / A1200 AGA)**:
  - Eliminates manual guesswork: the emulator automatically determines whether a WHDLoad game requires classic Amiga 500 or advanced Amiga 1200 AGA hardware.
  - Automatically configures the appropriate CPU (68000 or 68020) and memory settings.
  - Informative color badges in preview panels indicate the active hardware configuration (Green for A500 OCS, Orange for A1200 AGA).
- **Accurate Graphics & Speed Calibration (Shadow Dancer & Golden Axe)**:
  - **Shadow Dancer**: Fixed the game-freezing crash at address `$168CE` that previously occurred when the ninja began walking at the start of a level.
  - **Golden Axe and classic OCS titles**: Fixed the issue where gameplay and music ran at double speed with distorted audio; the emulator dynamically assigns the cycle-accurate blitter mode for optimal timing.
  - **Interactive WHDLoad Settings**: Added menu controls to inspect or manually override hardware profiles and blitter modes when desired.
- **Enhanced Wireless FTP Server (`ftpd pro` Parity)**:
  - Fixed the FileZilla `502 Command not implemented` directory listing error by implementing standard RFC 3659 commands (`MLSD` and `MLST`).
  - The built-in FTP server on port 5000 now provides full parity with dedicated homebrew FTP servers: instant folder listings, transfer pause/resume (`REST`), file/folder renaming (`RNFR`/`RNTO`), and virtual `/sdmc` browsing.
- **Dedicated Pinball Mode (L/R Flippers)**:
  - Added a direct toggle switch `Pinball Mode (L/R Flippers)` in the Controls menu for pinball games (*Pinball Dreams*, *Pinball Fantasies*, *Pinball Illusions*, *Slam Tilt*):
    - **L or ZL**: Left Flipper
    - **R or ZR**: Right Flipper
    - **X or Stick Down**: Plunger / Launch ball
    - **A / B / Y**: Table Nudge
  - Custom Control Profile 2 is clearly labeled as `Profile 2 (Pinball)` for quick access.
- **Retro CRT Shader Enhancements**:
  - The CRT-Lottes shader now properly saves and restores OpenGL pipeline state, ensuring clean menu rendering without visual artifacts or flickering.

---

### Technical Details & Internal Changes
- **WHDLoad Hardware Detection**: Auto-detects A500 vs A1200 based on `.slave` binary headers (`ws_Flags`) and title matching; assigns 68000/OCS or 68020/AGA presets.
- **Blitter Timing & Interrupt Race Condition**: Resolved Level 3 interrupt acknowledgment race condition in CPU core during BOB drawing; dynamically assigns cycle-exact blitter to OCS titles and immediate blitter to titles requiring fast blits.
- **Interactive WHDLoad Settings**: Added `WHDLoad Hardware` (AUTO / FORCE A500 / FORCE A1200) and `WHDLoad Blitter` (AUTO / FORCE NORMAL / FORCE IMMEDIATE / FORCE IMPROVED) with persistence in `uae4all.cfg`.
- **In-Memory Caching Engine**: Cached WHDLoad directory scans, metadata lookups, cover artwork indices, and favorites to avoid SD card I/O starvation; added analog/D-Pad key repeat smoothing.
- **RFC 3659 FTP Server Parity**: Implemented `MLSD`, `MLST`, `REST`, `APPE`, `RNFR`, `RNTO`, `FEAT`, standard UNIX aliases (`XPWD`, `XCWD`, `XCUP`, `XMKD`, `XRMD`), and virtual root `/sdmc` browsing.
- **Direct Pinball Remapping**: Injected direct flipper keys (`Left Shift`/`Alt`/`Arrow` on L/ZL, `Right Shift`/`Alt`/`Arrow` on R/ZR, `Down`/`Space` on X/Down) when `pinballMode` is enabled.


## Version 1.04
- **1-Click Game Library**: Added a unified Game Library as the default tab, featuring automatic detection and 1-click launch for WHDLoad, ADF floppies, M3U playlists, HDF, and CD32 games with boxart previews and quick filtering.
- **Game Library Cover Artwork**: Integrated unified cover manager supporting multi-path search (7 directories including RomFS and SD card) with single-surface RAM caching.
- **Game Metadata Display**: Real-time display of Title, Year, Developer, Publisher, Genre, and Players in both Game Library and WHDLoad preview panels.
- **Built-in Offline Amiga Database**: Embedded database containing **2,599 games** with fuzzy matching tolerant to dump tags, disk numbers, and naming variations.
- **In-App Cover Downloader (libcurl)**: Added real HTTP/HTTPS cover art downloading directly from the console into `./data/covers/` with server URL configuration (`source.txt`).
- **Library Options Dialog Integration**: Added "Download Cover" directly into the **(Y)** Library Options menu without altering controller button bindings.
- **Display Shaders & CRT Emulation**: Added **CRT-Lottes** (phosphor triad aperture mask, scanlines, subtle vignette), **CRT-Easymode** (aperture grille with scanline boost), **Scanlines (50%)**, **Scale2x** (vectorized pixel-art smoothing), and **Pixel-Perfect Integer** scaling alongside existing **Sharp Bilinear**, **Bilinear**, **Point**, and **None**.
- **16:10 Wide Aspect Ratio**: Added 16:10 display scaling option across all horizontal resolution presets.
- **Engine Memory Expansion**: Expanded metadata engine capacity up to 10,000 games concurrently.

## Version 1.03

- **CPU Core Accuracy**: Improved Motorola 68000/68020 emulation accuracy, fixing SR/CCR flag normalization, shift & rotate boundaries, and 68020 PC-relative CMPI flag formulas.
- **WHDLoad Post-Install Dialog**: Added confirmation prompt after installing a game from LHA to either launch immediately or return to the WHDLoad menu.
- **WHDLoad Alphabetical Sorting & 4,096 Games**: Installed games list is now automatically sorted from A to Z, with library capacity expanded up to 4,096 games.
- **Amiga Mouse Settings**: Added dedicated mouse configuration menu (analog stick/touchscreen mapping, sensitivity, acceleration curves, slow/fast modifiers, button swapping, and trackpad mode).

## Version 1.02

- **Fast-Forward / Turbo Mode**: Fast-forward emulation on-the-fly (hold ZR) or toggle via Quick Menu (L).
- **Single Joy-Con Mode**: 2-player local multiplayer using detached horizontal Joy-Cons.
- **Multi-Disk Playlist (.m3u)**: Seamless multi-floppy disk swapping via shortcut (ZL + D-Pad) or Quick Menu.
- **Compressed CHD Support**: Direct loading of compressed .chd images for CD32 and HDF hardfiles.
- **Stereo Separation**: Adjustable audio stereo blending (0% Mono to 100% Amiga stereo) for comfortable headphone play.
- **Quick Save & Quick Load**: Instant state save/load shortcuts (ZL + R / ZL + L) across 5 slots.
- **In-Game Quick Menu**: On-screen overlay (L button) for quick settings, disk swaps, and screenshots.
- **Built-in FTP Server**: Wireless file transfer over Wi-Fi on port 5000 under the System tab.
- **Bug Fixes**: Resolved Horizon OS startup crash and fixed WHDLoad CLI prompt issue on second game launch.
