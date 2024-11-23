#include "MCXN947_cm33_core0.h"

int main() {
    SYSCON->AHBCLKCTRL0 |=(1<<19);

    GPIO0->PDDR |=(1<<10);

    while(1) {
        GPIO0->PDOR ^=(1<<10);

        for(volatile uint32_t i=0; i<1000000; i++) {}
    }
}
