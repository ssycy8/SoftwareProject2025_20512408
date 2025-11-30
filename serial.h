#ifndef SERIAL_H
#define SERIAL_H

// ------------------------------------------------------------
// Serial Communication Header
// Declares the functions implemented in serial.c
// ------------------------------------------------------------

// Sends one line of G-code out
void PrintBuffer(const char *buffer);

// Waits for the robot firmware to send '$'
void WaitForDollar(void);

#endif
