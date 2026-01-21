*This project has been created as part of the 42 curriculum by mperrine.*

## Description

`FdF` (Fil de Fer, meaning "wireframe" in French) is a graphics project from the 42 curriculum that creates a 3D wireframe representation of a landscape from a map file. The program reads a map with height values and displays it as a wireframe mesh using isometric projection.

The program handles:
- Reading and parsing map files (.fdf format)
- Wireframe rendering using the MacroLibX graphics library
- Window management and user interactions

## Instructions

A `Makefile` is provided to compile the project.

**Build**
```bash
make
```

**Clean**
```bash
make clean
make fclean
```

**Rebuild**
```bash
make re
```

## Usage
```bash
./fdf map_file.fdf
```

Example:
```bash
./fdf maps/42.fdf
```

Controls

- **ESC** - Close the program

## Resources

This project was developed without the use of any AI tools.
