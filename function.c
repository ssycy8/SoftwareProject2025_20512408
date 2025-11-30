// function.c
#include <stdio.h>
#include "function.h"
#include "font.h"
#include "platform.h"

// 这些变量在 main.c 或别处定义为全局
extern int cursorX;
extern int cursorY;
extern float scale;

#define CHAR_SPACING  (2)    // 字体内部最大 x 后再多加多少单位（字体坐标单位）
#define EXTRA_SPACE   (5)    // 放大之后的额外像素间距（像素/单位）

void DrawChar(int ascii)
{
    // 在 font[] 中查找字符头 (999 ascii N)
    for (int i = 0; i < FONT_LINES; i++)
    {
        if (font[i].a == 999 && font[i].b == ascii)
        {
            int N = font[i].c;          // 后面有 N 行点：每行 = x y pen
            int maxX = 0;

            // 从 i+1 开始到 i+N
            for (int j = 1; j <= N; j++)
            {
                int x   = font[i + j].a;   // 字体文件里的 x（绝对）
                int y   = font[i + j].b;   // 字体文件里的 y（绝对）
                int pen = font[i + j].c;   // 0 = pen up, 非0 = pen down

                int worldX = cursorX + (int)(x * scale);
                int worldY = cursorY + (int)(y * scale);

                if (pen == 0) {
                    PenUp();
                    MoveTo(worldX, worldY);
                } else {
                    PenDown();
                    DrawTo(worldX, worldY);
                }

                if (x > maxX) maxX = x;
            }

            // 用 maxX 前进（加一点间距），注意 scale 单位转换
            cursorX += (int)((maxX + CHAR_SPACING) * scale) + EXTRA_SPACE;

            return; // 绘完一个字符就返回
        }
    }

    // 如果找不到字符，稍微前进避免重叠
    cursorX += (int)(8 * scale);
}
