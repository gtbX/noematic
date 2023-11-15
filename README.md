# Noematic

/What is old is new again./

Noematic is an interpreter for dialog files used by [The Talos Principle](http://croteam.com/talosprinciple/), targetting retro computers such as the IBM PC (other platforms pending).
It was designed specifically to run the text adventure mini-games released with the "Road to Gehenna" expansion, but can simulate some portions of the main game dialog as well.

Noematic may also prove useful to mod developers who wish to test their dialog files without needing to boot up the full game.

## Usage

Noematic requires the original dialog files extracted from The "Talos Principle"assets in order to function. They are not included as part of this repository.

To extract, navigate to your game installation directory. For Steam users, right click on the game in your Library, then `Manage->Browse Local Game Files`.
Enter the `Content/Talos` subfolder and note the `*.gro` files.
These are actually renamed `.zip` files, and can be opened by any zip extractor.Depending on which one you open, there may be a `Content/Talos/Databases/ComputerTerminalDialogs` folder containing `.dlg` files. These are the files that Noematic operates on.

Once extracted from the game archive(s), you can run them by providing them as a command line argument to the `noematic` binary (`NOEMATIC.EXE` on DOS).
For example:

```
noematic.exe DLC_Aaru.dlg
```

## Limitations

Many of the text adventures included in "Road to Gehenna" will operate standalone like this.
However, most of the game dialog expects to run as part of the larger game, and won't operate as expected.
In particular, the `include` directive is not (yet) implemented, so cross-linking between .dlg files won't work.
Also, anything that keys off of events in the 3D game world won't work, for reasons that should be obvious.

## Porting

Noematic is written in ANSI C to try for a wide array of potential platforms.
Currently it runs on MS-DOS and modern Linux systems.
It's written in a modular style, where platform-specific code is isolated to specific C files that are compiled (or not) for the desired platform.
In general, .h files contain all function declarations, and the corresponding .c files contain platform-independent code.
Platform-dependent code is tagged as such in the file name.
For example, `slow.h` contains declarations for timing functions, while `slow_dos.c` contains the DOS implementation.

To support a new platform, the appropriate implementations will need to be selected/written and compiled for it.

Currently, the `Makefile` exists to create the Linux version, as well as regenerate `lex_yy.c` and `y_tab.c` from the lex and yacc input files.
There is also a Borland Turbo C++ 1.01 project file `NOEMATIC.PRJ` for compiling on DOS.
Note that the lex and yacc output file names differ slightly from their standardized form for DOS compatibility.

## Acknowledgements
[The Talos Principle](https://en.wikipedia.org/wiki/The_Talos_Principle) is a video game released in 2014 by Croteam and published by Devolver Digital.

476f 6f64 204c 7563 6b0a
