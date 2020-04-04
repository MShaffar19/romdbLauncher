# romdb Launcher

[![](https://github.com/romdb/romdbLauncher/workflows/CI/badge.svg)](https://github.com/romdb/romdbLauncher/actions?query=workflow%3ACI)

[romdb](https://github.com/romdb/romdb) is a [SQLite](https://sqlite.org) based archive format used to store files and metadata. Its main purpose is to store collections of ROM files for 8-bit/16-bit video game consoles.

romdb Launcher is a windows application that can load romdb files and run the configured emulator for that system.

# How to use

On the first run, the app will create an empty `config.txt` file in the user's roaming folder. You must edit this file to load romdb files.

You can then search for files and open them with a configured emulator. Romdb Launcher will minimize while the emulator is running and restore itself after you close it.

![romdb Launcher](https://user-images.githubusercontent.com/63014699/78453836-e00d9000-7683-11ea-92d5-f1657fb439c3.png)

### Portable mode

To use romdb Launcher in portable mode, create a `config.txt` file next to `romdbLauncher.exe`

### config.txt

* romdb files in network paths won't load correctly
* emulators must support loading rom files by passing the filename as an argument
* you can have many `system` option blocks for as many systems as you want

```
# romdb Launcher configuration

# romdb files to load
romdb=
romdb=

# romdb Launcher options
position=100,100
size=640,480
deleteFileOnClose=true
allSystems=true
includeMedia=true
activeSystems=
currentSearch=

# system options
# 
# system - romdb system code to configure
# emulator - full path of emulator
# args - arguments to pass to emulator. full rom path will be appended at the end to load or by replacing %file%
# rompath - path of cache folder to extract roms. this path should be created just for romdb Launcher
# alias - use the same system configuation of the current system
#
system=
emulator=
args=
rompath=
#alias=
```

1. example configuration file for an emulator for multiple systems

```
# romdb files to load
romdb=Z:\roms\master.system.db
romdb=Z:\roms\game.gear.db

# systems
system=genesis
emulator=Z:\Fusion\Fusion.exe
args=
rompath=Z:\Fusion\romdb
alias=32x
alias=game gear
alias=master system
```

2. same example using the %file% argument

```
# romdb files to load
romdb=Z:\roms\master.system.db
romdb=Z:\roms\game.gear.db

# systems
system=genesis
emulator=Z:\Fusion\Fusion.exe
args=%file%
rompath=Z:\Fusion\romdb
alias=32x
alias=game gear
alias=master system
```
