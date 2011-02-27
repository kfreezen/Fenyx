#include <gdt.h>

const u8 PRESENT = 1<<7;
const u8 ACCESS1 = 1<<4;

Privilege priv;
Executable exec;
Direction dir; 
Conform conforming;
RW rw;
Granularity gran; 
Size bits;

extern gdtFlush(GdtDesc* d);

Real_GdtEntry gdt[5];

/**
	gdt layout
**/

GdtDesc AssembleGdtDesc(u16 size, GDT address) {
	GdtDesc d;
	
	d.size = (sizeof(Real_GdtEntry)*size)-1;
	d.address = (u32) address;
	
	return d;
}
/**

AssembleGdtDesc(size, address)
	This returns the GdtDesc with made with size and address

**/

GdtEntry AssembleGdtEntry(u32 base, u32 limit, u32 privilege, u32 executable, u32 direction, u32 read_write, u32 granularity, u32 bitSize) {
	GdtEntry e;
	e.base = base;
	e.limit = limit;
	
	e.accessByte = 0;
	e.accessByte = PRESENT | ACCESS1;
	e.accessByte |= (privilege & 0x3) << 5;
	e.accessByte |= (executable & 1) << 3;
	e.accessByte |= (direction & 1) << 2;
	e.accessByte |= (read_write & 1) << 1;
	
	e.flags = 0;
	e.flags |= (granularity & 1) << 7;
	e.flags |= (bitSize & 1) << 6;
	
	return e;
}
/**

AssembleGdtEntry(base, limit, privilege, executable, direction, read_write, granularity, bitSize)
	This assembles an abstract GdtEntry from the arguments and returns it

**/

Real_GdtEntry AssembleReal_GdtEntry(GdtEntry e) {
	Real_GdtEntry r;
	r.limit0To15 = (e.limit & 0xFFFF);
	r.limit16To19AndFlags = (e.limit >> 16) & 0x0F;
	
	r.base0To15 = (e.base & 0xFFFF);
	r.base16To23 = (e.base >> 16) & 0xFF;
	r.base24To31 = (e.base >> 24) & 0xFF;
	
	r.accessByte = e.accessByte;
	
	r.limit16To19AndFlags |= (e.flags & 0xF0);
	
	return r;
}
/**

AssembleReal_GdtEntry(e)
	This function assembles a real GdtEntry from the abstract GdtEntry in the arguments and returns it.

**/

void GdtInit() {
	GdtDesc desc = AssembleGdtDesc(5, gdt);
	
	Real_GdtEntry null = {0,0,0,0,0,0};
	
	u8* vidmem = 0xb8000;
	vidmem[2] = 'c';
	
	gdt[0] = null;
	gdt[1] = AssembleReal_GdtEntry(AssembleGdtEntry(0x0, 0xFFFFFFFF, KERNEL, DATA, UP, READ, _4K, _32) );
	gdt[2] = AssembleReal_GdtEntry(AssembleGdtEntry(0x0, 0xFFFFFFFF, KERNEL, CODE, UP, READ_WRITE, _4K, _32) );
	gdt[3] = AssembleReal_GdtEntry(AssembleGdtEntry(0x0, 0xFFFFFFFF, USER, DATA, UP, READ_WRITE, _4K, _32) );
	gdt[4] = AssembleReal_GdtEntry(AssembleGdtEntry(0x0, 0xFFFFFFFF, USER, CODE, UP, READ, _4K, _32) );

	vidmem[4] = 'd';
	
	gdtFlush(&desc); // The triple-fault point
	
	vidmem[6] = 'e';
}
/**

GdtInit()
	This function initializes the GDT
	
**/
