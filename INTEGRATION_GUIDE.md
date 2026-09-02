# ClearSword Integration for Dopamine (iOS 18.7.3)

## Overview
This guide explains how to integrate ClearSword exploit into Dopamine jailbreak for iPhone XS (A12) running iOS 18.7.3.

## Status
- ✅ ClearSword supports iOS 15.0 - 26.0.1
- ✅ iOS 18.7.3 offsets verified for A12
- ⚠️ Integration with Dopamine needs testing on real device

## Files Created
```
ClearSwordDopamine/
├── clearsword_krw.h    # Dopamine-compatible header
├── clearsword_krw.c    # Dopamine-compatible wrapper
├── utils.c             # Modified with iOS 18.7 offsets
├── poc.c               # Modified with getter functions
├── test.c              # Test program
└── Makefile            # Build system
```

## Integration Steps

### 1. Copy Files to Dopamine
```bash
# Copy ClearSword library files
cp clearsword_krw.h clearsword_krw.c /path/to/Dopamine/BaseBin/libjailbreak/
cp *.c *.h /path/to/Dopamine/BaseBin/libjailbreak/clearsword/
```

### 2. Modify Dopamine's krw.c
Replace `krw-corellium.m` with ClearSword:

```objc
// In BaseBin/dopamine/src/main.m
#include "clearsword_krw.h"

int main(int argc, char *argv[]) {
    // Initialize ClearSword instead of Corellium
    int ret = clearsword_krw_init();
    if (ret != 0) {
        printf("Failed to initialize ClearSword\n");
        return 1;
    }
    
    // Get kernel base for Dopamine
    uint64_t kernelBase = clearsword_get_kernel_base();
    uint64_t kernelSlide = clearsword_get_kernel_slide();
    
    // Continue with Dopamine jailbreak...
}
```

### 3. Update Dopamine's Makefile
Add to `BaseBin/libjailbreak/Makefile`:
```makefile
LIBJAILBREAK_SRCS += \
    clearsword_krw.c \
    poc.c \
    utils.c \
    socket.c \
    surface.c \
    phys_oob.c \
    kmem.c \
    krw.c \
    free_thread.c
```

### 4. Build
```bash
cd ClearSwordDopamine
make all
make test  # Test on simulator or device
```

## Offsets for iOS 18.7.3 (A12)
```c
// From utils.c
g_offsets.inpcb_icmp6filt = 0x148;
g_offsets.socket_so_count = 0x254;
g_offsets.socket_so_background_thread = 0x2b0;
g_offsets.thread_t_ro = 0x378;  // A12 specific
g_offsets.thread_ro_proc = 0x18;
```

## Testing
1. Build the test program
2. Deploy to iPhone XS on iOS 18.7.3
3. Run `./clearsword_test`
4. Verify kernel base and slide are returned

## Notes
- DarkSword is NOT needed for iOS 18.7.3
- ClearSword is more stable and supports newer iOS versions
- Test thoroughly on real device before releasing
