
#include "qspi4xy2-100.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

static void test_qspi4xy2_100(void) {
    // Randomize the inputs
    srand((unsigned)time(NULL));
    uint16_t x = rand() & 0xFFFF, y = rand() & 0xFFFF, z = rand() & 0xFFFF;
    // Make buffer
    uint8_t buf[10];
    bool buf_bool[20][4];
    q4x_make_buffer(buf, x, y, z);
    // Transfer buffer to bool buffer
    for(uint32_t i = 0; i < 20; i++) {
        uint8_t data = buf[i / 2];
        if (i % 2 == 0) data = data >> 4;
        else data = data & 0x0F;
        for (uint32_t j = 0; j < 4; j++) buf_bool[i][j] = data & (0x08 >> j);
    }
    // Print the buffer
    for (uint32_t i = 0; i < 4; i++) {
        // Draw the wave
        for (uint32_t j = 0; j < 20; j++) {
            printf("%s", buf_bool[j][i] == 0 ? "_" : "\033[31m-\033[0m");
        }
        switch (i) {
            case 0:
                printf("\tSYNC\n"); break;
            case 1:
                printf("\txPOS: %04X\n", x); break;
            case 2:
                printf("\tyPOS: %04X\n", y); break;
            case 3:
                printf("\tzPOS: %04X\n", z); break;
        }
    }
}

int main(void) {
    test_qspi4xy2_100();
    return 0;
}

