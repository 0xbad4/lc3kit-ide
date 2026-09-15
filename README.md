# LC3kit IDE

A Qt 6-based integrated development environment for LC-3 assembly and emulation, built on top of the `lc3kit` library.

This project provides a desktop IDE for writing LC-3 assembly programs, assembling them, running or debugging them, and inspecting CPU state, registers, memory, symbols, logs, and breakpoints in a single interface.

## Overview

`LC3kit IDE` is designed for learning and experimenting with the LC-3 architecture. It combines:

- a code editor for LC-3 assembly source files
- syntax-aware highlighting for LC-3 assembly
- project tabs and file management
- assembly/export workflow
- execution of programs in a built-in VM
- debugging support with breakpoints and step controls
- live inspection of:
  - registers
  - flags
  - memory
  - symbol table
  - console output
  - logs
  - settings and diagnostics
- built-in example programs for common LC-3 exercises
- theme support (`charcoal` and `daisy`)

## Features

- Qt 6 GUI application with a custom frameless window style
- Embedded app resources, themes, icons, and sample programs
- QScintilla-powered editor experience
- LC-3 assembly and execution integrated with `lc3kit`
- Debugger-style panels for VM inspection and stepping
- Example programs from `assets/app/asm_examples`
- Cross-platform CMake build via `Qt6`, `QScintilla`, and `lc3kit`

## Project status

This repository contains the IDE front-end and UI shell. The core LC-3 functionality is provided by the external `lc3kit` library, which is fetched automatically at configure time via CMake.

## Requirements

Before building the project, make sure you have:

- CMake 3.28 or newer
- A C++20 compiler
- Qt 6 development libraries
- QScintilla for Qt 6
- Git (needed for the `lc3kit` dependency fetch)

Typical Linux package names include:

```bash
sudo apt update
sudo apt install build-essential cmake git qt6-base-dev qt6-tools-dev qt6-tools-dev-tools libqscintilla2-qt6-dev
```

On other distributions, install the equivalent Qt 6 and QScintilla development packages for your package manager.

## Build

From the project root:

```bash
cmake -S . -B build
cmake --build build --parallel
```

This project is configured to:

- enable Qt auto-generated MOC/UIC/RCC files
- fetch `lc3kit` from GitHub at configure time
- locate the QScintilla headers and library
- link the IDE against Qt widgets, core, GUI, and the `lc3kit` library

## Run

After building, run the application from the build output directory:

```bash
./build/lc3kit-ide
```

On some systems, the binary may be under a subdirectory of `build/` depending on generator output; check the generated build tree if needed.

## Runtime notes

- The app manifest is loaded from `assets/app/manifest.json`.
- Example assembly programs are exposed via the menu and loaded from the `asm_examples` list.
- Theme selection is managed through the bundled theme directories under `assets/themes`.
- Window state and user settings are persisted with `QSettings` under the application identity configured by the project.

## Typical workflow

1. Open or create an LC-3 assembly file.
2. Assemble the source to object format.
3. Run the program in the VM environment.
4. Use the debugger panels to inspect registers, memory, flags, and symbol tables.
5. Step through execution or resume from breakpoints.
6. Use bundled example files to learn common LC-3 patterns and behavior.

## Related project

This repository is the IDE layer for the `lc3kit` ecosystem. The implementation depends on the core library from:

- https://github.com/0xbad4/lc3kit

## Notes

- The project uses `FetchContent` to automatically pull the `lc3kit` dependency during configuration.
- The build is intentionally configured for Qt 6 and modern C++20.
- This README will evolve as the IDE gains additional features and polish.
