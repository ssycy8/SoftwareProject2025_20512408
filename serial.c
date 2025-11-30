#include <stdio.h>
#include <string.h>
#include "serial.h"

// ------------------------------------------------------------
// Serial Communication Layer
// ------------------------------------------------------------

// 1 = simulator mode (prints to console)
// 0 = real hardware mode (UART)
#define SERIAL_SIMULATOR_MODE 1

//--------------------------------------------------------------
// PrintBuffer: sends one line of G-code out
//--------------------------------------------------------------
void PrintBuffer(const char *buffer) {
#if SERIAL_SIMULATOR_MODE
    // Simulator: print EXACTLY what is passed in
    // Do NOT add extra newline here!
    printf("%s", buffer);
#else
    // Real hardware UART write
    UART_WriteString(buffer);   // already contains '\n' if needed
#endif
}

//--------------------------------------------------------------
// WaitForDollar: waits until firmware sends '$'
//--------------------------------------------------------------
void WaitForDollar(void) {
#if SERIAL_SIMULATOR_MODE
    // no waiting in simulator mode
    return;
#else
    char c;
    do {
        c = UART_ReadChar();
    } while (c != '$');
#endif
}
