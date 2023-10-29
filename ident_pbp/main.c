#include <pspsdk.h>
#include <pspkernel.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>

#define RGB(r, g, b) (0xFF000000 | ((b) << 16) | ((g) << 8) | (r))
#define RED RGB(255, 0, 0)
#define BLACK RGB(0, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(50, 140, 255)
#define ORANGE RGB(255, 127, 0)
#define WHITE RGB(255, 255, 255)
#define VER_MAJOR 1
#define VER_MINOR 0
#define VER_BUILD " final"

PSP_MODULE_INFO("iypcwc", 0, VER_MAJOR, VER_MINOR);
PSP_MAIN_THREAD_ATTR(0);
PSP_HEAP_SIZE_KB(1024);

#include "../kernel_prx/kernel_prx.h"
#define printf pspDebugScreenPrintf

int main(int argc, char*argv[]) {
	pspDebugScreenInit();
	pspDebugScreenClear();
	printf("\niypcwc v%i.%i%s\n\n", VER_MAJOR, VER_MINOR, VER_BUILD);

	SceUID mod = pspSdkLoadStartModule("kernel.prx", PSP_MEMORY_PARTITION_KERNEL);
	if (mod < 0) {
		printf("Error: LoadStart() returned 0x%08x\n", mod);
		sceKernelDelayThread(3*1000*1000);
		sceKernelExitGame();
	}

	u32 baryon; prxSysconGetBaryonVersion(&baryon);
	u32 tachyon = prxSysregGetTachyonVersion();
	
	switch(tachyon) {
		case 0x00600000: {
			switch(baryon) {
				case 0x00243000: {
					pspDebugScreenSetBackColor(BLUE);
					printf("ta-088v3! CANNOT install cIPL\n\n");
					break;
				}
			}
			break;
		}

		default: {
			pspDebugScreenSetBackColor(GREEN);
			printf("NOT ta-088v3! CAN install cIPL\n\n");
			break;
		}
	}

	printf("Tachyon : 0x%08x\n", tachyon);
	printf("Baryon : 0x%08x\n", baryon);

	sceKernelDelayThread(9*1000*1000);
	sceKernelExitGame();

	return 0;
}
