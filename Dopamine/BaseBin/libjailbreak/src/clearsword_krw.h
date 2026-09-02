#ifndef clearsword_krw_h
#define clearsword_krw_h

#include <stdint.h>
#include <stdbool.h>

// Initialize ClearSword exploit for iOS 18.7.3
// Returns 0 on success, non-zero on failure
int clearsword_krw_init(void);

// Get kernel base address (after successful init)
uint64_t clearsword_get_kernel_base(void);

// Get kernel slide (after successful init)
uint64_t clearsword_get_kernel_slide(void);

// Kernel read/write functions
int clearsword_kread64(uint64_t kaddr, uint64_t *val);
int clearsword_kwrite64(uint64_t kaddr, uint64_t val);
int clearsword_kreadbuf(uint64_t kaddr, void *buf, size_t size);
int clearsword_kwritebuf(uint64_t kaddr, const void *buf, size_t size);

// Physical read/write
int clearsword_physread64(uint64_t pa, uint64_t *val);
int clearsword_physwrite64(uint64_t pa, uint64_t val);

#endif /* clearsword_krw_h */
