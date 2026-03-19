#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mmap.h>
#include <stdint.h>

// These headers come from the Intel SoC EDS hwlib
// Make sure your Makefile has the -I flag pointing to them!
#include "socal/socal.h"
#include "socal/hps.h"

// 1. The physical base address of the Lightweight HPS-to-FPGA bridge.
// ALT_LWFPGASLVS_OFST is defined in the hps.h header as 0xFF200000
#define HW_REGS_BASE (ALT_LWFPGASLVS_OFST)

// 2. The span of the memory block we want to map into Linux.
// 2MB (0x00200000) is the standard size of the entire lightweight bridge window.
#define HW_REGS_SPAN (0x00200000)

// 3. A mask used to safely calculate the offset later
#define HW_REGS_MASK (HW_REGS_SPAN - 1)

// 4. YOUR CUSTOM OFFSET
// Look in Qsys at the "Base" column for your PIO component. 
// If it says 0x00000000, leave this as is. If it says 0x40, change it to 0x40.
#define PIO_LED_OFFSET 0x00000000

int main() {
    void *virtual_base;
    int fd;
    volatile uint32_t *led_pio_ptr;

    // A. Open the physical memory device file
    if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return 1;
    }

    // B. Map the physical memory to our Linux virtual memory space
    virtual_base = mmap(NULL, HW_REGS_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, HW_REGS_BASE);

    if (virtual_base == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(fd);
        return 1;
    }

    // C. Calculate the exact virtual pointer to our PIO register
    // We take the base pointer mmap gave us, and add the offset defined in Qsys
    led_pio_ptr = (uint32_t *)(virtual_base + ((HW_REGS_BASE + PIO_LED_OFFSET) & HW_REGS_MASK));

    // D. Do the hardware control! Let's blink it 10 times.
    printf("Starting FPGA communication test...\n");
    for (int i = 0; i < 10; i++) {
        // Write a 1 to drive the PIO wire HIGH
        *led_pio_ptr = 1;
        usleep(500000); // Sleep for 500ms (half a second)

        // Write a 0 to drive the PIO wire LOW
        *led_pio_ptr = 0;
        usleep(500000); 
    }
    printf("Test complete.\n");

    // E. Clean up like a good citizen
    if (munmap(virtual_base, HW_REGS_SPAN) != 0) {
        printf("ERROR: munmap() failed...\n");
    }
    close(fd);

    return 0;
}