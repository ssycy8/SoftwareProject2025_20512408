#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "serial.h"

// ----------------------
// Font data structure
// ----------------------
typedef struct {
    int a;   // X or command 999
    int b;   // Y or ASCII
    int c;   // Pen state or N
} FontData;

#define FONT_LINES 1027
FontData font[FONT_LINES];

// ----------------------
// Global drawing cursor
// ----------------------
int cursorX = 0;
int cursorY = 0;

float scale = 8.0;   // character scaling

// ----------------------
// Load font file
// ----------------------
void LoadFontData() {
    FILE *fp = fopen("SingleStrokeFont.txt", "r");
    if (!fp) {
        printf("Error: Cannot open SingleStrokeFont.txt\n");
        exit(1);
    }

    for (int i = 0; i < FONT_LINES; i++) {
        if (fscanf(fp, "%d %d %d", &font[i].a, &font[i].b, &font[i].c) != 3) {
            printf("Error reading font file at line %d\n", i);
            fclose(fp);
            exit(1);
        }
    }

    fclose(fp);

    // ⭐⭐⭐ 加入调试输出 ———— 检查字体文件是否正常加载
    printf("DEBUG: font[0] = %d %d %d\n", font[0].a, font[0].b, font[0].c);
    printf("DEBUG: font[1] = %d %d %d\n", font[1].a, font[1].b, font[1].c);
}

// ----------------------
// Draw a character using the font data
// ----------------------
void DrawChar(int ascii)
{
    int maxX = 0;

    for (int i = 0; i < FONT_LINES; i++)
    {
        if (font[i].a == 999 && font[i].b == ascii)
        {
            int N = font[i].c;

            for (int j = 1; j <= N; j++)
            {
                int dx  = font[i+j].a;
                int dy  = font[i+j].b;
                int pen = font[i+j].c;

                // ⭐ dx, dy = ABSOLUTE FONT POINTS — DO NOT ACCUMULATE!
                if (dx > maxX)
                    maxX = dx;

                int worldX = cursorX + (int)(dx * scale);
                int worldY = cursorY + (int)(dy * scale);

                if (pen == 0) {
                    PenUp();
                    MoveTo(worldX, worldY);
                } else {
                    PenDown();
                    DrawTo(worldX, worldY);
                }
            }

            cursorX += (int)(maxX * scale) + 5;  // 字间距

            return;
        }
    }
}


// ----------------------
// Main Program
// ----------------------
int main() {
    printf("DEBUG: Program started!\n");

    LoadFontData();   // ← 会打印 DEBUG 信息
    LoadFontData();

    printf("DEBUG: font[0] = %d %d %d\n", font[0].a, font[0].b, font[0].c);
    printf("DEBUG: font[1] = %d %d %d\n", font[1].a, font[1].b, font[1].c);

    FILE *fp = fopen("Test.txt", "r");
    if (!fp) {
        printf("Error: Cannot open Test.txt\n");
        return 1;
    }

    char ch;

    while ((ch = fgetc(fp)) != EOF) {

        // CR = 13 → reset X
        if (ch == 13) {
            cursorX = 0;
            continue;
        }

        // LF = 10 → move down by 5mm
        if (ch == 10) {
            cursorY -= (int)(5.0 * scale);
            continue;
        }

        // Draw normal character
        DrawChar((int)ch);
    }

    fclose(fp);

    // End at origin with pen up
    PenUp();
    MoveTo(0, 0);

    return 0;
}




