#ifndef FUNCTION_H
#define FUNCTION_H

void MoveTo(int x, int y);
void PenUp();
void PenDown();
void DrawChar(int ascii);
void LoadFontData();
void PrintBuffer(const char *s);

extern int cursorX;
extern int cursorY;
extern float scale;

#endif
