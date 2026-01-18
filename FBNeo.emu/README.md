# FBNeo.emu

Multi-system arcade and console emulator for multiple platforms, part of the EX Emulators suite.

## Overview

FBNeo.emu is a comprehensive arcade and console emulator based on the FinalBurn Neo (FBNeo) emulator core. It provides accurate emulation of classic arcade hardware and select home consoles, with support for thousands of games across dozens of systems.

**Author:** Robert Broglia
**Website:** https://www.explusalpha.com/
**License:** Non-commercial use (FBNeo custom license - see License section)

## Supported Systems

### Capcom Systems
- **CPS-1 (CP System)** - Street Fighter, Final Fight, Captain Commando, etc.
- **CPS-2 (CP System II)** - Street Fighter Alpha/Zero series, Marvel vs Capcom, etc.
- **CPS-3 (CP System III)** - Street Fighter III series

### SNK Systems
- **Neo Geo MVS** - Multi Video System (arcade)
- **Neo Geo AES** - Advanced Entertainment System (home console)

### Sega Systems
- **System 16/16B** - Altered Beast, Golden Axe, Shinobi
- **System 18** - Moonwalker, Alien Storm
- **System 1/2** - Early arcade titles
- **Master System** - 8-bit home console
- **Game Gear** - Portable console
- **SG-1000** - First Sega home console

### Other Arcade Systems
- **Konami** - Various arcade boards (Gradius, Contra, etc.)
- **Data East** - Various arcade titles
- **Irem** - R-Type, Image Fight, etc.
- **Taito** - Space Invaders, Bubble Bobble, etc.
- **Namco** - Pac-Man, Galaga, etc.
- **Cave** - DonPachi series and other bullet-hell shooters
- **Psikyo** - Strikers 1945, Gunbird, etc.
- **Toaplan** - Various arcade shooters

### Home Consoles
- **PC Engine / TurboGrafx-16** - NEC's 16-bit console
- **SuperGrafx** - Enhanced PC Engine
- **Colecovision** - Early home console
- **MSX1** - Home computer standard
- **ZX Spectrum** - British home computer

### Supported File Formats

- `.zip` - Standard ZIP archives (most common)
- `.7z` - 7-Zip archives

## Features

### Emulation Features

- **Extensive Game Library**: Support for 5,000+ arcade and console games
- **High Compatibility**: Accurate emulation of original hardware behavior
- **Multiple CPU Cores**: 68000, Z80, ARM7, and many other processors
- **Save States**: Full save state support for all systems
- **NVRAM/SRAM Support**: Automatic save of high scores and game progress
- **Cheat Support**: Built-in cheat database for supported games
- **DIP Switch Configuration**: Arcade cabinet settings (difficulty, lives, etc.)

### Audio/Video Features

- **High-Quality Audio**: Accurate sound chip emulation (YM2610, YM2151, OKIM6295, etc.)
- **Multiple Resolutions**: Native resolution support for each system
- **Screen Rotation**: Support for vertical arcade games
- **Scanline Effects**: Optional CRT scanline simulation

### Special Features

- **ROM Set Flexibility**: Support for various ROM dump versions
- **Parent/Clone Detection**: Automatic handling of game variants
- **BIOS Selection**: Multiple BIOS versions per system
- **Macro Support**: Input macros for complex moves
- **Netplay Ready**: Codebase supports network play features

## Building

### Prerequisites

- **C++ Compiler**: GCC 16+, Clang 21+, or MSVC with C++20 support
- **Build Tools**: CMake 4.1+, GNU Make, pkg-config
- **Imagine SDK**: Cross-platform application framework

### Environment Setup

```bash
export IMAGINE_PATH=/path/to/imagine
export IMAGINE_SDK_PATH=$HOME/imagine-sdk
```

### Platform-Specific Builds

#### Linux

```bash
cd $IMAGINE_PATH
cmake --preset linux-x86_64
cmake --build build/linux-x86_64 --target install

cd FBNeo.emu
cmake --preset linux-x86_64
cmake --build build/linux-x86_64
```

#### Android

```bash
cd $IMAGINE_PATH/bundle/all
bash makeAll-android.sh install
```

#### iOS

```bash
cd $IMAGINE_PATH/bundle/all
bash makeAll-ios.sh install
```

### Build Configuration

- **CMake**: Main build configuration in `CMakeLists.txt`
- **Platform Makefiles**: `linux.mk`, `android.mk`, `ios.mk`, `pandora.mk`
- **Metadata**: `metadata/conf.mk` for package configuration

Key compiler definitions:
- `LSB_FIRST` - Little-endian byte order (x86, ARM)
- `FBNEO_COMPAT` - Enable compatibility features

## BIOS Requirements

FBNeo.emu requires BIOS files for certain systems. BIOS files must be placed in ZIP archives in the same directory as your ROM files or in the emulator's system directory.

### Neo Geo (neogeo.zip)

**Required files:**
- `neo-geo.rom` or `sp-s2.sp1` - Main BIOS
- `000-lo.lo` - Zoom lookup table
- `sfix.sfix` - Fix layer graphics
- `sm1.sm1` - Audio BIOS (Z80)

**Optional (for different regions):**
- `sp-s.sp1` - Japan BIOS
- `sp-45.sp1` - Asia BIOS
- `sp-u2.sp1` - Universe BIOS alternative
- `uni-bios.rom` - Universe BIOS (various versions)

### CPS-1 / CPS-2 / CPS-3

Most CPS games do not require separate BIOS files, as the BIOS is typically included in the game ROM sets. Some CPS-2 games may require:

- QSound audio samples (included in game ROM sets)

### Master System / Game Gear (Sega systems)

**Optional BIOS files (not required, but improve compatibility):**
- `bios.sms` - Master System BIOS
- `bios.gg` - Game Gear BIOS

### PC Engine / TurboGrafx-16

**Required for CD games:**
- `syscard3.pce` - System Card 3.0 (Super CD-ROM²)

### Colecovision

**Required:**
- `coleco.rom` - Colecovision BIOS

### MSX

**Required:**
- `msx.zip` containing MSX1 BIOS files

### BIOS File Placement

Place all BIOS files in ZIP archives named as specified above (e.g., `neogeo.zip`, `coleco.rom`) in:
1. The same directory as your game ROM files, OR
2. The emulator's system directory (platform-specific)

## ROM Set Information

FBNeo uses specific ROM set versions. For best compatibility:

- **ROM Set Version**: FBNeo ROM sets are based on current MAME sets with some differences
- **Parent ROMs**: Some games require "parent" ROM sets to be present
- **Clone ROMs**: Game variants (clones) may need parent ROM files
- **Split vs Merged**: FBNeo supports both split and merged ROM sets
- **CRC Checking**: Optional ROM verification for accuracy

**Important**: ROM files are copyrighted and must be obtained legally. This emulator does not include any ROM files.

## Resources

### Upstream Projects

- **FinalBurn Neo (FBNeo)**
  - Official Website: https://github.com/finalburnneo/FBNeo
  - Source Code: https://github.com/finalburnneo/FBNeo
  - Documentation: https://neo-source.com/
  - Forums: https://neo-source.com/
  - License: Custom non-commercial license

- **Imagine Framework**
  - GitHub: https://github.com/Rakashazi/emu-ex-plus-alpha
  - Website: http://www.explusalpha.com/home/imagine
  - License: GPL-3.0

- **EX Emulators Suite**
  - Main Project: https://github.com/Rakashazi/emu-ex-plus-alpha
  - Website: https://www.explusalpha.com/

### Additional Resources

- **Game Lists**: See FBNeo documentation for complete supported game lists
- **ROM Information**: https://github.com/libretro/FBNeo/tree/master/dats
- **Compatibility**: Check FBNeo forums for per-game compatibility

## License

**IMPORTANT - Non-Commercial License**

FBNeo.emu incorporates the FinalBurn Neo emulator core, which uses a **custom non-commercial license**. This differs from other emulators in the EX suite which use GPL-3.0.

### License Restrictions

You may freely:
- ✅ Use this emulator for personal, non-commercial purposes
- ✅ Modify the source code
- ✅ Share the source code and binaries

You may NOT:
- ❌ Sell this emulator or use it for commercial purposes
- ❌ Accept donations for FBNeo-based projects
- ❌ Distribute with copyrighted ROM images (unless legally authorized)

The EmuFramework and Imagine components remain under GPL-3.0, but the FBNeo core's license takes precedence for the combined work.

See the FBNeo `src/license.txt` file for complete license terms.

## Credits

- **FBNeo.emu Port**: Copyright © 2025 Robert Broglia
- **FinalBurn Neo Core**: Copyright © FBNeo Team
  - Based on FinalBurn and FinalBurn Alpha by Dave
  - Continued by Barry Harris, dink, and the FBNeo team
- **Imagine Framework**: Copyright © 2010-2025 Robert Broglia
- **Original Emulator Cores**: Various authors (MAME team, original hardware developers)

Special thanks to the FBNeo development team for their excellent multi-system arcade emulation work.
