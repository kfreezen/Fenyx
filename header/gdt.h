#ifndef GDT_H
#define GDT_H

#include <stdint.h>


struct Real_GdtEntry {
	u16 limit0To15;
	u16 base0To15;
	
	u8 base16To23;
	u8 accessByte;
	
	u8 limit16To19AndFlags;
	u8 base24To31;
} __attribute__((packed));

typedef struct Real_GdtEntry* GDT;

struct GdtDesc {
	u16 size;
	u32 address;
} __attribute__((packed));


typedef struct GdtDesc GdtDesc;
typedef struct Real_GdtEntry Real_GdtEntry;
typedef struct GdtEntry {
	u32 limit;
	u32 base;
	u8 accessByte;
	u8 flags;
} GdtEntry;

GdtDesc AssembleGdtDesc(u16 size, GDT address);

GdtEntry AssembleGdtEntry(u32 base, u32 limit, u32 privilege, u32 executable, u32 direction, u32 read_write, u32 granularity, u32 bitSize); // XXX

Real_GdtEntry AssembleReal_GdtEntry(GdtEntry e); // XXX

void GdtInit();

typedef enum Privilege {KERNEL=0, USER=3} Privilege;
typedef enum Executable {DATA, CODE} Executable;
typedef enum Direction {UP, DOWN} Direction;
typedef enum Conform {EQUAL_OR_LOWER, EQUAL} Conform;
typedef enum RW {READ, READ_WRITE} RW;
typedef enum Granularity {_1, _4K} Granularity;
typedef enum Size {_16, _32} Size;

#endif // GDT_H
