// #include <multiboot.h>
// #include <stdint.h>

/* TODO: split off into multiboot.h */
typedef struct multiboot Multiboot;
/* TODO: define this struct */

/* end split */

int main(u32 multibootMagic, Multiboot* multibootPointer) {
    return 0xDEADBABA;
}
