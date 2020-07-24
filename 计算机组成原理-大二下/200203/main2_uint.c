#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint16_t numA = 0xFFFF, numB = 0x0001;
    if(numA < numB) {
        printf("numA is smaller than numB!");
    }
    else {
        printf("numA is bigger than numB!");
    }
    return 0;
}
