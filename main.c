// main.c
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "serial.h"
#include "font.h"
#include "function.h"

// 全局游标和缩放（在 function.c 使用 extern）
int cursorX = 0;
int cursorY = 200;    // 基线位置（可调），越大字显示越靠上（模拟器坐标系）
float scale = 8.0f;   // 推荐起始值 6~20 之间，根据需要调整

int main(void)
{
    // 加载字体文件（SingleStrokeFont.txt 必须在程序运行的当前目录）
    LoadFontData();

    // 打开要写的文本（Test.txt 必须与 exe 同目录，或指定绝对路径）
    FILE *fp = fopen("Test.txt", "r");
    if (!fp) {
        printf("Cannot open Test.txt\n");
        return 1;
    }

    int ch;
    // 逐字符读取并绘制
    while ((ch = fgetc(fp)) != EOF) {
        // CR (13) 只复位 X（回到行首）
        if (ch == 13) {
            cursorX = 0;
            continue;
        }
        // LF (10) 换行：回到行首并向下移动 baseline
        if (ch == 10) {
            cursorX = 0;
            // 计算合理的行高：字体内高度大约 20 units -> lineHeight = 20*scale + 40 pixels
            int lineHeight = (int)(20.0f * scale) + 40;
            cursorY -= lineHeight;   // 向下移动（坐标系依你模拟器方向而定）
            continue;
        }

        // 正常字符
        DrawChar((int)ch);
    }

    fclose(fp);

    // 收尾：抬笔并回到原点
    PenUp();
    MoveTo(0, 0);

    return 0;
}
