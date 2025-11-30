#ifndef PLATFORM_H
#define PLATFORM_H

// ------------------------------------------------------------
// Platform Layer Header
// Declares the motion-level functions used by main.c
// ------------------------------------------------------------

// Lift the pen (stop drawing)
void PenUp(void);

// Lower the pen (start drawing)
void PenDown(void);

// Move rapidly to position (x, y) without drawing
void MoveTo(int x, int y);

// Draw a line to position (x, y) with pen down
void DrawTo(int x, int y);

#endif
