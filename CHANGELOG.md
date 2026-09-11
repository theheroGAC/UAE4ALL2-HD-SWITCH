# Changelog — UAE4ALL2 HD (Nintendo Switch)

All notable features, quality-of-life enhancements, and bug fixes for **UAE4ALL2 HD** on Nintendo Switch.

## Version 1.04
- **1-Click Game Library**: Added a unified Game Library as the default tab, featuring automatic detection and 1-click launch for WHDLoad, ADF floppies, M3U playlists, HDF, and CD32 games with boxart previews and quick filtering.
- **Game Library Cover Artwork**: Integrated unified cover manager supporting multi-path search (7 directories including RomFS and SD card) with single-surface RAM caching.
- **Game Metadata Display**: Real-time display of Title, Year, Developer, Publisher, Genre, and Players in both Game Library and WHDLoad preview panels.
- **Built-in Offline Amiga Database**: Embedded database containing **2,599 games** with fuzzy matching tolerant to dump tags, disk numbers, and naming variations.
- **In-App Cover Downloader (libcurl)**: Added real HTTP/HTTPS cover art downloading directly from the console into `./data/covers/` with server URL configuration (`source.txt`).
- **Library Options Dialog Integration**: Added "Download Cover" directly into the **(Y)** Library Options menu without altering controller button bindings.
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
