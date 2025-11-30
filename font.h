#ifndef FONT_H
#define FONT_H

#define FONT_LINES 1027   // 字体数据的总行数，根据你的文件实际填写

typedef struct {
    int a;
    int b;
    int c;
} FontData;

extern FontData font[FONT_LINES];

void LoadFontData(void);

#endif
