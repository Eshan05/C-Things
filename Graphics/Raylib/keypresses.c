#include <raylib.h>

#define KEY_COUNT   26
#define KEY_SIZE    40
#define KEY_SPACING 10

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 600;
  InitWindow(screenWidth, screenHeight, "Keyboard Simulation");

  Color normalColor = LIGHTGRAY;
  Color pressedColor = DARKGRAY;
  Vector2 keyPositions[KEY_COUNT];
  for (int i = 0; i < KEY_COUNT; i++) {
    keyPositions[i].x = (i % 10) * (KEY_SIZE + KEY_SPACING) + 50;
    keyPositions[i].y = (i / 10) * (KEY_SIZE + KEY_SPACING) + 50;
  }

  while (!WindowShouldClose()) {
    bool keyStates[KEY_COUNT];
    for (int i = 0; i < KEY_COUNT; i++) {
      keyStates[i] = IsKeyDown(KEY_A + i);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < KEY_COUNT; i++) {
      Color keyColor = keyStates[i] ? pressedColor : normalColor;
      DrawRectangle(keyPositions[i].x, keyPositions[i].y, KEY_SIZE, KEY_SIZE,
                    keyColor);
      DrawText(TextFormat("%c", KEY_A + i), keyPositions[i].x + 10,
               keyPositions[i].y + 10, 20, BLACK);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
