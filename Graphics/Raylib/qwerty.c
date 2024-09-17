#include <raylib.h>
#include <string.h>

#define KEY_SIZE        40
#define KEY_SPACING     5
#define ROW_SPACING     15
#define MAX_WORD_LENGTH 20

Vector2 GetKeyPosition(int keyIndex, int row) {
  static const int xOffsets[] = { 0, 15, 10 };
  static const int numKeysPerRow[] = { 10, 10, 9 };
  int xOffset = xOffsets[row];
  int yOffset = row * (KEY_SIZE + ROW_SPACING);

  int x = (keyIndex % numKeysPerRow[row]) * (KEY_SIZE + KEY_SPACING) + 100 +
          xOffset;
  int y = yOffset + 50;
  return (Vector2){ x, y };
}

int main(void) {
  const int screenWidth = 640;
  const int screenHeight = 480;
  InitWindow(screenWidth, screenHeight, "Type Away!");

  Color normalColor = BLACK;
  Color pressedColor = DARKGRAY;
  const char *keys[] = { "QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM" };
  // States
  bool keyStates[26] = { false };
  char typedWord[MAX_WORD_LENGTH] = { 0 };
  int wordLength = 0;

  while (!WindowShouldClose()) {
    for (int i = 0; i < 26; i++)
      keyStates[i] = IsKeyDown(KEY_A + i);

    // Check for typing characters
    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < strlen(keys[row]); col++) {
        char keyChar = keys[row][col];
        if (IsKeyPressed(keyChar - 'A' + KEY_A)) {
          if (wordLength < MAX_WORD_LENGTH - 1) {
            typedWord[wordLength++] = keyChar;
            typedWord[wordLength] = '\0';
          }
        }
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);
    int keyIndex = 0;
    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < strlen(keys[row]); col++) {
        char keyChar = keys[row][col];
        Vector2 keyPosition = GetKeyPosition(keyIndex, row);

        // Determine color
        Color keyColor = keyStates[keyChar - 'A'] ? pressedColor : normalColor;
        DrawRectangle(keyPosition.x, keyPosition.y, KEY_SIZE, KEY_SIZE,
                      keyColor);
        DrawText(TextFormat("%c", keyChar), keyPosition.x + 12,
                 keyPosition.y + 10, 20, RAYWHITE);

        keyIndex++;
      }
    }

    // Typed text
    DrawText(typedWord, 50, screenHeight - 100, 40, RAYWHITE);
    if (IsKeyPressed(KEY_SPACE)) {
      memset(typedWord, 0, sizeof(typedWord));
      wordLength = 0;
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
