# Ray Tracing in C

This project demonstrates the fundamentals of ray tracing using C and SDL2. The program renders a simple scene using ray tracing techniques.
What is ray tracing?   <link>https://developer.nvidia.com/discover/ray-tracing</link>

## Features

- Basic ray tracing algorithm
- Lighting and shading effects
- SDL2-based rendering

## Prerequisites

Make sure you have the following installed:

- [GCC](https://gcc.gnu.org/) (MinGW for Windows)
<!-- - [SDL2](https://www.libsdl.org/) -->

## Compilation (On Windows using GCC)

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

## References

- [HirschDaniel: Coding Raytracing in C](https://youtu.be/2BLRLuczykM?si=pF6zifO4QdC-IUH8)
- [SDL2 documentation](https://wiki.libsdl.org/SDL2/FrontPage)
- [What is Raytracing](https://developer.nvidia.com/discover/ray-tracing)





