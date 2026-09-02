#ifndef PRIMITIVES_CLEARSWORD_H
#define PRIMITIVES_CLEARSWORD_H

#include <stdint.h>
#include <stdbool.h>

// Initialize ClearSword exploit for iOS 18.7.3
// Returns 0 on success, non-zero on failure
int clearsword_primitives_init(void);

// Get kernel base address (after successful init)
uint64_t clearsword_get_kernel_base(void);

// Get kernel slide (after successful init)
uint64_t clearsword_get_kernel_slide(void);

// Kernel read/write functions (called by gPrimitives)
int clearsword_kreadbuf(uint64_t kaddr, void* output, size_t size);
int clearsword_kwritebuf(uint64_t kaddr, const void* input, size_t size);
int clearsword_physreadbuf(uint64_t physaddr, void* output, size_t size);
int clearsword_physwritebuf(uint64_t physaddr, const void* input, size_t size);

#endif /* PRIMITIVES_CLEARSWORD_H */
