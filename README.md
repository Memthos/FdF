*This project has been created as part of the 42 curriculum by mperrine.*

## Description

`FdF` is a project that renders a 3D wireframe representation of a landscape from a file.
The mandatory part asks for a simple isometric projection.
Bonus features add a second projection (perspective), zoom, panning, rotation and color per vertex support - defaulting to white when no color is specified.

## Instructions

A `Makefile` is provided to compile the project.

**Build**
```bash
make
make bonus
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

**Usage**
```bash
./fdf map_file.fdf
```

**Controls**

- **ESC** - Close the program
- **WASD** - Move the map
- **UIOJKL** - Rotate the map
- **Mouse Wheel** - Zoom in and out

## Resources

AI was used to better understand the maths behind this project and to check spelling errors in this readme.

This [medium](https://medium.com/@amehri_tarik/fdf-42-a-detailed-walkthrough-7184cca317fc) was useful to better understand how the projection algorithm I use works.
