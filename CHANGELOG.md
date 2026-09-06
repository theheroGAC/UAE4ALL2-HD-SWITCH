# Changelog — UAE4ALL2 HD (Nintendo Switch)

All notable features, quality-of-life enhancements, and bug fixes for **UAE4ALL2 HD** on Nintendo Switch.

---

## Version 1.02

A major release packed with new features designed to eliminate classic Amiga emulation hassles and take full advantage of the Nintendo Switch hardware.

### 1. Fast-Forward / Turbo Mode
- **What it does**: Classic Amiga floppy games often had lengthy loading times or unskippable intro sequences. Turbo mode runs the CPU and drives at maximum possible speed until the game is ready to play.
- **How to use it**:
  - **On-the-fly**: Hold down the **ZR** trigger to instantly fast-forward emulation; release it to return to normal speed.
  - **Toggle**: Press **L** during gameplay to open the **Quick Menu** and set `"Turbo: ON"` (or back to `"OFF"`).

### 2. Single Joy-Con Mode (Instant 2-Player Co-op / VS)
- **What it does**: Play two-player classics like *Sensible Soccer*, *Speedball 2*, *Lotus 2*, *Micro Machines*, or *Worms* without needing an extra Pro Controller: simply detach both Joy-Cons and use them horizontally.
- **How to use it**:
  - Enable `"Single Joy-Con Mode"` under the **Controls** tab in the main menu or from the **Quick Menu** (**L** button).
  - Works seamlessly in both **TV Docked** mode and **Tabletop** mode with the console kickstand open.
  - **SL** and **SR** shoulder buttons act as Fire 1 and Fire 2; face buttons and analog stick are calibrated for ergonomic play.
  - Joy-Con 1 controls Amiga Joystick Port 1 (Player 1), Joy-Con 2 controls Amiga Joystick Port 0 (Player 2).

### 3. Multi-Disk Playlist Support (.m3u)
- **What it does**: For multi-floppy games (such as *Monkey Island*, *Simon the Sorcerer*, or *Beneath a Steel Sky*), there is no need to exit to the main menu to swap disks.
- **How to use it**:
  - Create a plain text file with `.m3u` extension listing your ADF disk filenames in order (e.g. `Monkey_Disk1.adf`, `Monkey_Disk2.adf`, etc.).
  - Select and boot the `.m3u` file: when the game asks for the next disk, press **ZL + D-Pad Right** (or **ZL + D-Pad Left** to go back) or select the disk from the **Quick Menu** (**L**). The disk swap occurs instantly with an on-screen confirmation.

### 4. Compressed CHD Image Support (.chd)
- **What it does**: CD-ROM images (Amiga CD32) and virtual hard drives (.hdf) take up precious space on your microSD card. The compressed CHD format reduces file sizes by 50% to 70% with zero decompression files written to disk.
- **How to use it**:
  - Select `.chd` files directly for the CD32 drive or as HDF Hardfiles.
  - The emulator decodes hunks on-the-fly directly in RAM at high speed, preventing SD card wear and eliminating decompression wait times.

### 5. Adjustable Stereo Separation (Comfortable Headphone Audio)
- **What it does**: Original Amiga Paula sound hardware separated audio rigidly: 2 channels hard-left (100%) and 2 channels hard-right (100%). When playing on the Switch with headphones, this can cause ear fatigue.
- **How to use it**:
  - Under the **Display & Audio** menu or directly from the **Quick Menu**, choose between 5 profiles: **0% (Mono)**, **25%**, **50% (Recommended for headphones)**, **75%**, and **100% (Original Amiga)**.
  - At 50%, music and sound effects blend smoothly across both ears for a natural listening experience.

### 6. Quick Save & Quick Load
- **What it does**: Save and resume your game at any moment without disrupting gameplay.
- **In-Game Shortcuts**:
  - **ZL + R**: Instantly save state to the active slot (Quick Save).
  - **ZL + L**: Instantly reload state from the active slot (Quick Load).
  - **ZL + D-Pad Up / Down**: Cycle active save slot (1 through 5).
  - An on-screen toast notification confirms every save, load, and slot change.

### 7. In-Game Quick Menu (L Shoulder Button)
- **What it does**: Press the **L** shoulder button during gameplay to bring up a translucent on-screen overlay. From here, you can toggle Turbo, adjust stereo separation, quick save/load, swap M3U disks, eject floppy drives, or capture an HD screenshot without interrupting the game.

### 8. Built-in Switch FTP Server
- **What it does**: Transfer games, ADF floppies, WHDLoad archives, and Kickstart ROMs wirelessly from your PC to your Switch without removing the microSD card.
- **How to use it**:
  - Open the **System** tab and select **FTP File Transfer**.
  - On your PC, connect via FileZilla, WinSCP, or Windows File Explorer to the IP address displayed on screen on port `5000` (anonymous login, no password).
  - Press **B**, **A**, or tap the touchscreen to exit the FTP server and return to the menu.

### 9. Stability Fixes & Bug Resolutions
- **Launch crash fixed**: Resolved the Horizon OS boot crash (*"The software was closed because an error occurred"*) caused by dynamic text relocations in the ELF binary; all modules are now built in native Position Independent Code (PIC/PIE) compliant with Switch OS security.
- **WHDLoad second-launch bug resolved**: Fixed an issue where returning to the menu after a WHDLoad session and launching a second game would boot into the AmigaDOS CLI prompt instead of running the game.
