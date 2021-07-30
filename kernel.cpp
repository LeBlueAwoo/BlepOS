#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    panicLoc = ("_start (Kernel main loop)");

    GlobalRenderer->Colour = 0xffbababa;
    GlobalRenderer->Print("Kernel loaded successfully");
    GlobalRenderer->Next();
    GlobalRenderer->Colour = 0xfffaff55;
    GlobalRenderer->Print("Starting Blep OS...");
    GlobalRenderer->Next();
    GlobalRenderer->Colour = 0xffd3d7cf;

    /*--------------------------------------------------*/
    
    
    
    /*--------------------------------------------------*/

    while (true){
        //Main loop - DO NOT BREAK!

        //GlobalRenderer->CursorPosition = {0, (GlobalRenderer->TargetFramebuffer->Height - 32)};
        //const char* pos = ("(", (char*)MousePosition.X, ",", (char*)MousePosition.Y, ")");
        //GlobalRenderer->Print(pos);
        GlobalRenderer->Print("No userland or system processes to start...");
        GlobalRenderer->Next();
        while (true);
        break;
    }


    //If the main loop exits, tell the user and halt the CPU
    ReturnPanic();
}

//Over 2500 lines!