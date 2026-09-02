# Dopamine + ClearSword (iOS 18.7.3)

## Overview
Modified Dopamine jailbreak using ClearSword exploit for iPhone XS (A12) running iOS 18.7.3.

## What Was Done
1. ✅ Integrated ClearSword exploit into Dopamine
2. ✅ Added iOS 18.7.3 specific offsets for A12
3. ✅ Created ClearSword primitives wrapper
4. ✅ Modified main.m to use ClearSword instead of Corellium

## Files Created/Modified

### New Files (in libjailbreak/src/):
- `primitives_ClearSword.h` - Header for ClearSword integration
- `primitives_ClearSword.m` - ClearSword implementation

### Modified Files:
- `main_ClearSword.m` - Uses ClearSword instead of Corellium
- `utils.c` - Added iOS 18.7.3 offsets

## Build Instructions

### Prerequisites
- Xcode 15+
- iOS SDK
- Provisioning profile for iPhone XS

### Steps
1. Clone Dopamine repository
2. Copy ClearSword files to `BaseBin/libjailbreak/src/`
3. Replace `main.m` with `main_ClearSword.m`
4. Build using Makefile:
```bash
cd Dopamine
make clean
make
```

### Alternative: Build Standalone ClearSword Test
```bash
cd ClearSwordDopamine
make test
```

## Offsets for iOS 18.7.3 (A12)
```c
g_offsets.inpcb_icmp6filt = 0x148;
g_offsets.socket_so_count = 0x254;
g_offsets.socket_so_background_thread = 0x2b0;
g_offsets.thread_t_ro = 0x378;  // A12 specific
g_offsets.thread_ro_proc = 0x18;
```

## Testing
1. Build the project
2. Sign with provisioning profile
3. Deploy to iPhone XS on iOS 18.7.3
4. Run Dopamine app
5. Check console output for successful exploitation

## Known Limitations
- kwritebuf not fully implemented (read-only exploit)
- Need to test on real device
- UI not modified yet

## Next Steps
1. Test on real device
2. Implement kernel write
3. Design improved UI
4. Package for distribution
