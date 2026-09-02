#include <stdio.h>
#include <stdlib.h>
#include "poc.h"

int main(int argc, char *argv[]) {
    printf("=== ClearSword for Dopamine (iOS 18.7.3) ===\n\n");
    
    printf("Starting ClearSword exploit...\n");
    int result = clearsword_run();
    
    if (result == 0) {
        printf("\n[SUCCESS] Exploit completed!\n");
        printf("Kernel Base: 0x%llx\n", g_ctx.kernel_base);
        printf("Kernel Slide: 0x%llx\n", g_ctx.kernel_slide);
        printf("\nTo integrate with Dopamine:\n");
        printf("1. Copy clearsword_krw.h/c to libjailbreak/\n");
        printf("2. Add clearsword_krw.c to Makefile\n");
        printf("3. Call clearsword_krw_init() instead of corellium_krw_init()\n");
    } else {
        printf("\n[FAILED] Exploit failed with code: %d\n", result);
        return 1;
    }
    
    return 0;
}
