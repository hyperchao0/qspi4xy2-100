
#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Make a buffer for the QSPI to send a xy2-100 command
 * 
 * @param buf Buffer to fill
 * @param x X position
 * @param y Y position
 * @param z Z position
 */
static inline void q4x_make_buffer(uint8_t *buf, uint16_t x, uint16_t y, uint16_t z) {
    // Initialize buffer
    buf[0] = 0x88;
    buf[1] = 0xF8;
    for (int i = 2; i < 9; i++) buf[i] = 0x88;
    buf[9] = 0x80;
    // Initialize parity
    bool xp = 1, yp = 1, zp = 1;
    // Fill buffer
    for (uint8_t i =0; i < 16; i++) {
        uint8_t j = i / 2;
        if (i % 2 == 0) {
            if (x & (0x8000 >> i)) { buf[1 + j] |= 0x04; xp = !xp;}
            if (y & (0x8000 >> i)) { buf[1 + j] |= 0x02; yp = !yp;}
            if (z & (0x8000 >> i)) { buf[1 + j] |= 0x01; zp = !zp;}
        } else {
            if (x & (0x8000 >> i)) { buf[2 + j] |= 0x40; xp = !xp;}
            if (y & (0x8000 >> i)) { buf[2 + j] |= 0x20; yp = !yp;}
            if (z & (0x8000 >> i)) { buf[2 + j] |= 0x10; zp = !zp;}
        }
    }
    // Set parity
    if (xp) buf[9] |= 0x04;
    if (yp) buf[9] |= 0x02;
    if (zp) buf[9] |= 0x01;
    // Invert buffer
    // for (int i = 0; i < 10; i++) buf[i] = ~buf[i];
}

