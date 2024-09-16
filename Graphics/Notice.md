If I wish to replicate in other PCs:

## Installations

1. Got MinGW64 from `choco`
2. Got FreeGLUT from `https://www.transmissionzero.co.uk/software/freeglut-devel/` as a precompiled binary ZIP, from which I extracted files as needed into `ProgramData/mingw64/mingw64/`
3. Did the same for GLEW and GLFW from their official website (Got the Win64 ones) and put it in respective `lib/` and `include/`.
4. Put the `.dll` files in the project directory

```
└── 📁Graphics
    └── ...
    └── freeglut.dll
    └── glew32.dll
    └── glfw3.dll
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
## C/C++ Extension

Refer to `.vscode/c_cpp_properties.json`.