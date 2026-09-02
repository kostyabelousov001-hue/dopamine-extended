#include "clearsword_krw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysctl.h>

// Forward declarations from ClearSword
extern int clearsword_run(void);
extern uint64_t g_kernel_base;
extern uint64_t g_kernel_slide;

// Dopamine compatibility - these will be set after clearsword_run()
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

int clearsword_krw_init(void) {
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
    cs_kernel_base = clearsword_get_kernel_base();
    cs_kernel_slide = clearsword_get_kernel_slide();
    
    printf("[ClearSword] Kernel base: 0x%llx\n", cs_kernel_base);
    printf("[ClearSword] Kernel slide: 0x%llx\n", cs_kernel_slide);
    
    cs_initialized = 1;
    return 0;
}

uint64_t clearsword_get_kernel_base(void) {
    return cs_kernel_base;
}

uint64_t clearsword_get_kernel_slide(void) {
    return cs_kernel_slide;
}

int clearsword_kread64(uint64_t kaddr, uint64_t *val) {
    if (!cs_initialized) return -1;
    // Use ClearSword's kernel read
    extern int early_kread64(uint64_t kaddr);
    *val = (uint64_t)early_kread64(kaddr);
    return 0;
}

int clearsword_kwrite64(uint64_t kaddr, uint64_t val) {
    if (!cs_initialized) return -1;
    // Use ClearSword's kernel write (if available)
    // For now, this is a placeholder
    printf("[ClearSword] kwrite64 not implemented yet\n");
    return -1;
}

int clearsword_kreadbuf(uint64_t kaddr, void *buf, size_t size) {
    if (!cs_initialized) return -1;
    
    uint64_t *out = (uint64_t *)buf;
    size_t count = size / sizeof(uint64_t);
    
    for (size_t i = 0; i < count; i++) {
        uint64_t val;
        int ret = clearsword_kread64(kaddr + (i * sizeof(uint64_t)), &val);
        if (ret != 0) return ret;
        out[i] = val;
    }
    
    // Handle remaining bytes
    size_t remaining = size % sizeof(uint64_t);
    if (remaining > 0) {
        uint64_t val;
        int ret = clearsword_kread64(kaddr + (count * sizeof(uint64_t)), &val);
        if (ret != 0) return ret;
        memcpy(buf + (count * sizeof(uint64_t)), &val, remaining);
    }
    
    return 0;
}

int clearsword_kwritebuf(uint64_t kaddr, const void *buf, size_t size) {
    if (!cs_initialized) return -1;
    printf("[ClearSword] kwritebuf not implemented yet\n");
    return -1;
}

int clearsword_physread64(uint64_t pa, uint64_t *val) {
    if (!cs_initialized) return -1;
    printf("[ClearSword] physread64 not implemented yet\n");
    return -1;
}

int clearsword_physwrite64(uint64_t pa, uint64_t val) {
    if (!cs_initialized) return -1;
    printf("[ClearSword] physwrite64 not implemented yet\n");
    return -1;
}
