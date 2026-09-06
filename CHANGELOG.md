# Changelog — UAE4ALL2 HD (Nintendo Switch)

[English](#english) | [Italiano](#italiano)

---

## English

### Version 1.02

A major release packed with new quality-of-life features designed to eliminate classic Amiga emulation hassles and take full advantage of the Nintendo Switch hardware.

#### ⚡ 1. Fast-Forward / Turbo Mode (Skip the waiting times!)
- **What it does**: Classic Amiga floppy games often had lengthy loading times or unskippable intro sequences. Turbo mode runs CPU and drives at maximum possible speed until the game is ready to play.
- **How to use it**:
  - **On-the-fly**: Hold down the **ZR** trigger to instantly fast-forward emulation; release it to instantly return to normal speed.
  - **Toggle**: Press **L** during gameplay to open the **Quick Menu** and set `"Turbo: ON"` (or back to `"OFF"`).

#### 🎮 2. Single Joy-Con Mode (Instant 2-Player Co-op / VS)
- **What it does**: Want to play two-player classics like *Sensible Soccer*, *Speedball 2*, *Lotus 2*, *Micro Machines*, or *Worms*? No need for an extra Pro Controller: just detach both Joy-Cons and use them horizontally!
- **How to use it**:
  - Enable `"Single Joy-Con Mode"` under the **Controls** tab or from the **Quick Menu** (**L** button).
  - Works seamlessly in both **TV Docked** mode and **Tabletop** mode with the console kickstand open.
  - **SL** and **SR** shoulder buttons act as Fire 1 and Fire 2; face buttons and analog stick are calibrated for ergonomic play.
  - Joy-Con 1 controls Amiga Joystick Port 1 (Player 1), Joy-Con 2 controls Amiga Joystick Port 0 (Player 2).

#### 💽 3. Multi-Disk Playlist Support (.m3u)
- **What it does**: For multi-floppy games (such as *Monkey Island*, *Simon the Sorcerer*, or *Beneath a Steel Sky*), you no longer need to exit to the main menu to swap disks.
- **How to use it**:
  - Create a plain text file with `.m3u` extension listing your ADF disk filenames in order (e.g. `Monkey_Disk1.adf`, `Monkey_Disk2.adf`, etc.).
  - Select and boot the `.m3u` file: when the game asks for the next disk, press **ZL + D-Pad Right** (or **ZL + D-Pad Left** to go back) or select the disk from the **Quick Menu** (**L**). The disk swap occurs instantly with an on-screen confirmation!

#### 📦 4. Compressed CHD Image Support (.chd)
- **What it does**: CD-ROM images (Amiga CD32) and virtual hard drives (.hdf) take up precious gigabytes on your microSD card. The compressed CHD format reduces file sizes by 50% to 70% with zero decompression files written to disk.
- **How to use it**:
  - Select `.chd` files directly for the CD32 drive or as HDF Hardfiles.
  - The emulator decodes hunks on-the-fly directly in RAM at high speed, preventing SD card wear and eliminating decompression wait times.

#### 🎧 5. Adjustable Stereo Separation (Comfortable Headphone Audio)
- **What it does**: Original Amiga Paula sound hardware separated audio rigidly: 2 channels hard-left (100%) and 2 channels hard-right (100%). When playing on the Switch with headphones, this can cause ear fatigue.
- **How to use it**:
  - Under the **Display & Audio** menu or directly from the **Quick Menu**, choose between 5 profiles: **0% (Mono)**, **25%**, **50% (Recommended for headphones)**, **75%**, and **100% (Original Amiga)**.
  - At 50%, music and sound effects blend smoothly across both ears for a pleasant listening experience.

#### 💾 6. Quick Save & Quick Load
- **What it does**: Save and resume your game at any moment without disrupting gameplay.
- **In-Game Shortcuts**:
  - **ZL + R**: Instantly save state to the active slot (Quick Save).
  - **ZL + L**: Instantly reload state from the active slot (Quick Load).
  - **ZL + D-Pad Up / Down**: Cycle active save slot (1 through 5).
  - An on-screen toast notification confirms every save, load, and slot change.

#### ⚡ 7. In-Game Quick Menu (L Shoulder Button)
- **What it does**: Press the **L** shoulder button during gameplay to bring up a translucent on-screen overlay. From here, you can toggle Turbo, adjust stereo separation, quick save/load, swap M3U disks, eject floppy drives, or capture an HD screenshot without interrupting the game's atmosphere.

#### 🌐 8. Built-in Switch FTP Server
- **What it does**: Transfer games, ADF floppies, WHDLoad archives, and Kickstart ROMs wirelessly from your PC to your Switch without removing the microSD card.
- **How to use it**:
  - Open the **System** tab and select **FTP File Transfer**.
  - On your PC, connect via FileZilla, WinSCP, or Windows File Explorer to the IP address displayed on screen on port `5000` (anonymous login, no password).
  - Press **B**, **A**, or tap the touchscreen to exit the FTP server and return to the menu.

#### 🛠️ 9. Stability Fixes & Bug Resolutions
- **Launch crash fixed**: Resolved the Horizon OS boot crash (*"The software was closed because an error occurred"*) caused by dynamic text relocations in the ELF binary; all modules are now built in native Position Independent Code (PIC/PIE) compliant with Switch OS security.
- **WHDLoad second-launch bug resolved**: Fixed an issue where returning to the menu after a WHDLoad session and launching a second game would boot into the AmigaDOS CLI prompt instead of running the game.

---

## Italiano

### Versione 1.02

Una versione ricca di novità per rendere l'esperienza Amiga su Nintendo Switch più moderna, comoda e divertente.

#### ⚡ 1. Modalità Turbo / Fast-Forward (Basta attese nei caricamenti!)
- **A cosa serve**: I giochi Amiga su floppy disk spesso richiedevano caricamenti molto lunghi o mostravano schermate introduttive lente e non skippabili. Con la modalità Turbo, l'emulatore accelera al massimo la CPU e i drive fino a quando il gioco non è pronto per giocare.
- **Come si usa**:
  - **Al volo nel gioco**: Tieni premuto il grilletto **ZR** per velocizzare all'istante l'emulazione; rilascialo non appena vuoi tornare alla velocità normale.
  - **Fisso**: Premi il tasto **L** durante il gioco per aprire il **Quick Menu** e imposta la voce `"Turbo: ON"` (oppure torna su `"OFF"` quando vuoi).

#### 🎮 2. Modalità Single Joy-Con (Multiplayer a 2 giocatori istantaneo)
- **A cosa serve**: Vuoi giocare in due a classici come *Sensible World of Soccer*, *Speedball 2*, *Lotus Esprit Turbo Challenge 2*, *Micro Machines* o *Worms*? Non serve un secondo controller Pro: basta staccare i due Joy-Con della console e usarli in orizzontale!
- **Come si usa**:
  - Attiva la modalità `"Single Joy-Con Mode"` nella scheda **Controls** del menu principale oppure dal **Quick Menu** (tasto L).
  - Stacca i due Joy-Con: funzionano perfettamente sia con la console collegata alla TV (Docked) sia appoggiata su un tavolo con il cavalletto aperto (Tabletop).
  - I tasti dorsali **SL** e **SR** fungono da Fuoco 1 e Fuoco 2; anche i tasti frontali sono mappati per una presa ergonomica.
  - Il Joy-Con 1 controlla la porta Joystick 1 (Giocatore 1), mentre il Joy-Con 2 controlla la porta Joystick 0 (Giocatore 2).

#### 💽 3. Supporto Giochi Multi-Disco con Playlist (.m3u)
- **A cosa serve**: Per le avventure grafiche o i giochi divisi su più floppy (come *Monkey Island*, *Simon the Sorcerer*, *Beneath a Steel Sky*), non è più necessario tornare ogni volta al menu dell'emulatore per inserire il disco successivo.
- **Come si usa**:
  - Crea un semplice file di testo con estensione `.m3u` contenente la lista dei floppy (ad esempio: `Monkey_Disk1.adf`, `Monkey_Disk2.adf`, ecc.).
  - Seleziona e avvia il file `.m3u` dal menu: quando il gioco richiede il disco successivo, premi **ZL + Freccia Destra** (o **ZL + Freccia Sinistra** per tornare indietro) oppure scegli il disco dal **Quick Menu** (tasto L). Il cambio avviene immediatamente con tanto di notifica a schermo!

#### 📦 4. Supporto Immagini Compresse CHD (.chd)
- **A cosa serve**: I file dei CD-ROM (Amiga CD32) e gli hard disk virtuali (.hdf) occupano gigabyte di spazio prezioso sulla scheda microSD. Il formato compresso CHD permette di risparmiare dal 50% al 70% di spazio senza dover estrarre alcun file.
- **Come si usa**:
  - Puoi selezionare direttamente i file `.chd` per il lettore CD-ROM del CD32 o come Hardfile HDF.
  - L'emulatore legge e decomprime i singoli blocchi al volo direttamente in RAM, senza rallentamenti e senza usurare la memoria microSD della console.

#### 🎧 5. Separazione Stereo Regolabile (Stereo Separation)
- **A cosa serve**: L'hardware originale dell'Amiga separava nettamente i canali sonori: 2 canali a sinistra al 100% e 2 canali a destra al 100%. Giocando su Switch con gli auricolari o le cuffie, questo effetto "hard-panned" può risultare fastidioso per le orecchie.
- **Come si usa**:
  - Nel menu **Display & Audio** o direttamente dal **Quick Menu** puoi scegliere tra 5 livelli: **0% (Mono)**, **25%**, **50% (Ideale per cuffie)**, **75%**, **100% (Originale Amiga)**.
  - Con il valore impostato al 50%, la musica e gli effetti sonori si fondono in modo morbido e confortevole in cuffia.

#### 💾 6. Salvataggio e Caricamento Rapido (Quick Save & Quick Load)
- **A cosa serve**: Salvare e riprendere la partita in qualunque momento, senza interrompere l'azione di gioco.
- **Scorciatoie durante la partita**:
  - **ZL + R**: Salva istantaneamente nello slot corrente (Quick Save).
  - **ZL + L**: Ricarica istantaneamente la partita (Quick Load).
  - **ZL + Freccia Su / Giù**: Cambia lo slot di salvataggio attivo (da 1 a 5).
  - Una notifica a comparsa in alto a sinistra (toast OSD) conferma subito l'avvenuto salvataggio o caricamento.

#### ⚡ 7. Quick Menu in Gioco (Tasto L)
- **A cosa serve**: Premendo il dorsale **L** durante il gioco appare un menu leggero in trasparenza. Da qui puoi gestire rapidamente il Turbo, la separazione stereo, i salvataggi, il cambio disco M3U, l'espulsione del floppy o scattare uno screenshot senza dover aprire il menu completo.

#### 🌐 8. Server FTP Integrato
- **A cosa serve**: Inviare giochi, floppy ADF, archivi WHDLoad e Kickstart ROM dal PC alla Nintendo Switch via Wi-Fi, senza dover togliere la microSD dalla console.
- **Come si usa**:
  - Entra nella scheda **System** e seleziona **FTP File Transfer**.
  - Apri un client FTP sul PC (es. FileZilla, WinSCP o Gestione File di Windows) e connettiti all'indirizzo IP mostrato a schermo sulla porta `5000` (accesso anonimo, senza password).
  - Premi **B**, **A** o tocca lo schermo per chiudere il server e tornare subito al menu.

#### 🛠️ 9. Correzione Crash all'Avvio e Bug WHDLoad
- **Crash all'avvio risolto**: Risolto il blocco su Horizon OS (*"Il software è stato chiuso a causa di un errore"*) causato da rilocazioni dinamiche non permesse nei file ELF per Switch; ora l'intero motore è conforme al 100% alla sicurezza di Nintendo Switch.
- **Secondo avvio WHDLoad corretto**: Risolto il problema per cui tornando al menu dopo una partita WHDLoad e selezionando un secondo gioco, l'emulatore finiva nel prompt comandi AmigaDOS anziché lanciare il gioco.
