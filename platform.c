#include <stdio.h>
#include "platform.h"
#include "serial.h"

static int penIsDown = 0;

// --------------------- Pen Up ----------------------
void PenUp(void) {
    if (!penIsDown) return;

    PrintBuffer("M05\n");   // ADD \n
    WaitForDollar();
    penIsDown = 0;
}

// --------------------- Pen Down ----------------------
void PenDown(void) {
    if (penIsDown) return;

    PrintBuffer("M03\n");   // ADD \n
    WaitForDollar();
    penIsDown = 1;
}

// --------------------- MoveTo ----------------------
void MoveTo(int x, int y) {
    char buf[64];
    sprintf(buf, "G00 X%d Y%d\n", x, y);  // ADD \n
    PrintBuffer(buf);
    WaitForDollar();
}

// --------------------- DrawTo ----------------------
void DrawTo(int x, int y) {
    char buf[64];
    sprintf(buf, "G01 X%d Y%d\n", x, y);  // ADD \n
    PrintBuffer(buf);
    WaitForDollar();
}
