#include <stdio.h>
#include <stdlib.h>
#include "font.h"

FontData font[FONT_LINES];

void LoadFontData(void)
{
    FILE *fp = fopen("SingleStrokeFont.txt", "r");
    if (!fp)
    {
        printf("Error: cannot open SingleStrokeFont.txt\n");
        exit(1);
    }

    for (int i = 0; i < FONT_LINES; i++)
    {
        fscanf(fp, "%d %d %d", &font[i].a, &font[i].b, &font[i].c);
    }

    fclose(fp);
}
