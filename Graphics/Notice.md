If I wish to replicate in other PCs:

## Installations

1. Got MinGW64 from `choco`
2. Got FreeGLUT from `https://www.transmissionzero.co.uk/software/freeglut-devel/` as a precompiled binary ZIP, from which I extracted files as needed into `ProgramData/mingw64/mingw64/` (Later I actually just used `cmake` because version wasn't the latest)
3. Did the same for GLEW and GLFW from their official website (Got the Win64 ones, but should be same with FreeGLUT) and put it in respective `lib/` and `include/`. 
4. Got Raylib from their repository and similar process as above
5. Put the `.dll` files in the project directory (Or in `SysWOW64` but this is not what I follow)

```
└── 📁Graphics
    └── ...
    └── libfreeglut.dll
    └── glew32.dll
    └── glfw3.dll
    └── raylib.dll
    └── ...
```

## Compiling

1. For only FreeGLUT:
```shell
g++ -IC:\ProgramData\mingw64\mingw64\include first.c -o f -LC:\ProgramData\mingw64\mingw64\lib -lfreeglut -lopengl32 -lglu32
```
2. For FreeGLUT + GLEW
```shell
g++ -IC:\ProgramData\mingw64\mingw64\include first.cpp -o f -LC:\ProgramData\mingw64\mingw64\lib -lfreeglut -lopengl32 -lglu32 -lglew32
```
3. For GLFW + GLEW
```shell
g++ -IC:/ProgramData/mingw64/mingw64/include -IC:/ProgramData/mingw64/mingw64/include/GLFW -LC:/ProgramData/mingw64/mingw64/lib -o f gflw.cpp -lglfw3 -lglew32 -lopengl32 -lgdi32 -lglu32
```
4. For GL + GLFW
```shell
g++ -IC:/ProgramData/mingw64/mingw64/include -IC:/ProgramData/mingw64/mingw64/include/GLFW -LC:/ProgramData/mingw64/mingw64/lib -o f quick.cpp -lfreeglut -lopengl32 -lglu32 -lglfw3 -lgdi32
```
5. With `raylib.h`
```shell
gcc -o r InitialRay.c -I"C:/ProgramData/mingw64/mingw64/include" -L"C:/ProgramData/mingw64/mingw64/lib" -lraylib -lopengl32 -lgdi32 -lwinmm
```
6. Using `<windows.h>`
```shell
g++ first.cpp -lgdi32 -lwinmm
```
## C/C++ Extension

Refer to `.vscode/c_cpp_properties.json`. This is simply for 