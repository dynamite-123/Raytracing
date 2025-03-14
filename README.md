# Ray Tracing in C

This project demonstrates the fundamentals of ray tracing using C and SDL2. The program renders a simple scene using ray tracing techniques.

## Features

- Basic ray tracing algorithm
- Sphere and plane intersection calculations
- Lighting and shading effects
- SDL2-based rendering

## Prerequisites

Make sure you have the following installed:

- [GCC](https://gcc.gnu.org/) (MinGW for Windows)
- [SDL2](https://www.libsdl.org/)

## Compilation

To compile the program, run the following command:

```sh
gcc main.c -Isrc\include -Lsrc\lib -lmingw32 -lSDL2main -lSDL2 -o main.exe
```

## Execution

After compiling, run the program using:

```sh
.\main
```

## File Structure

```
project-root/
│── src/
│   ├── include/        # Header files
│   ├── lib/            # SDL2 libraries
│── main.c             # Main program file
│── README.md          # Project documentation
```

## Dependencies

- [Simple DirectMedia Layer (SDL2)](https://www.libsdl.org/) for graphics rendering

## Future Enhancements

- Add support for reflections and refractions
- Implement texture mapping
- Optimize performance with multi-threading

## License

This project is licensed under the MIT License.

## Acknowledgments

- Inspired by various ray tracing tutorials and books
- Uses SDL2 for rendering



