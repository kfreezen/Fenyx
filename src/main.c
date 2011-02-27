// #include <multiboot.h>
#include <stdint.h>
#include <gdt.h>

/* TODO: split off into multiboot.h */
typedef struct multiboot Multiboot;
/* TODO: define this struct */

/* end split */

/* version
	v0.0.8
*/

int main(u32 multibootMagic, Multiboot* multibootPointer) {
	u8* vidmem = 0xB8000;
	
	GdtInit();
	
	vidmem[2] = 'b';
	vidmem[3] = 0x07;
	
	return 0xE2D0F125;
}
