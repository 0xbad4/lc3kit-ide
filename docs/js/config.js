window.SITE_CONFIG = {
  name: "LC3kit IDE",
  repo: "0xbad4/lc3kit-ide",
  coreRepo: "0xbad4/lc3kit",
  coreDocs: "https://0xbad4.github.io/lc3kit/",
  fallbackVersion: "1.0.0",
  license: "MIT",
  platforms: {
    windows: { label: "Windows", match: /(win|\.exe$|\.msi$)/i },
    macos: { label: "macOS", match: /(mac|darwin|osx|\.dmg$|\.pkg$)/i },
    linux: { label: "Linux", match: /(linux|\.appimage$|\.deb$|\.rpm$|\.tar\.(gz|xz)$)/i }
  },
  buildSteps: [
    "sudo apt update",
    "sudo apt install build-essential cmake git qt6-base-dev qt6-tools-dev qt6-tools-dev-tools libqscintilla2-qt6-dev",
    "git clone https://github.com/0xbad4/lc3kit-ide.git",
    "cd lc3kit-ide",
    "cmake -S . -B build",
    "cmake --build build --parallel",
    "./build/lc3kit-ide"
  ],
  institutions: [
    {
      name: "The University of Texas at Austin",
      course: "EE 306, Introduction to Computing",
      url: "https://users.ece.utexas.edu/~patt/23f.306/Handouts/descriptor.pdf"
    },
    {
      name: "Georgia Institute of Technology",
      course: "CS 2110, Computer Organization and Programming",
      url: "https://syllabus.gatech.edu/sites/default/files/2026-04/CS2110%20Syllabus%20Fall_2026_16.pdf"
    }
  ],
  panels: [
    {
      id: "registers",
      title: "Registers",
      image: "assets/img/registers.png",
      text: "R0 to R7, PC, PSR and the device registers (DDR, DSR, KBDR, KBSR, MCR), shown in hexadecimal, decimal and binary."
    },
    {
      id: "memory",
      title: "Memory",
      image: "assets/img/memory.png",
      text: "Memory contents by address, with hexadecimal, binary, decimal and string columns."
    },
    {
      id: "flags",
      title: "Flags",
      image: "assets/img/flags.png",
      text: "The condition codes N, Z and P and the processor priority bits PL, PR2, PR1 and PR0."
    },
    {
      id: "breakpoints",
      title: "Breakpoints",
      image: "assets/img/breakpoints.png",
      text: "The list of breakpoints by address, with the label at each address where one exists."
    },
    {
      id: "symtab",
      title: "Symbol table",
      image: "assets/img/symtab.png",
      text: "The labels resolved by the assembler, with the address and source line of each."
    },
    {
      id: "console",
      title: "Console",
      image: "assets/img/console.png",
      text: "Program output and keyboard input."
    }
  ]
};
