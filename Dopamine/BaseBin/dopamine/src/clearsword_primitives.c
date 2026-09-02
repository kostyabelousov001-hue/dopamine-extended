#include "clearsword_primitives.h"
#include <stdio.h>
#include <string.h>

#include "exploit/poc.h"
#include "exploit/common.h"
#include "exploit/krw.h"
#include <libjailbreak/info.h>
#include <libjailbreak/primitives_external.h>

int clearsword_primitives_init(void)
{
    printf("[ClearSword] Initializing exploit...\n");

    int r = clearsword_run();
    if (r != 0) {
        printf("[ClearSword] Exploit failed: %d\n", r);
        return r;
    }

    printf("[ClearSword] Kernel base: 0x%llx\n", g_ctx.kernel_base);
    printf("[ClearSword] Kernel slide: 0x%llx\n", g_ctx.kernel_slide);

    gPrimitives.kreadbuf = clearsword_kreadbuf;
    gPrimitives.kwritebuf = clearsword_kwritebuf;
    gSystemInfo.kernelConstant.slide = g_ctx.kernel_slide;
    gPrimitives.krwMinSafeReadSize = 0x20;

    printf("[ClearSword] Primitives initialized successfully\n");
    return 0;
}
