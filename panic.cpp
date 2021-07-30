//Basic panic messages
#include "panic.h"
#include "BasicRenderer.h"
#include "kernelUtil.h"
#include "interrupts/interrupts.h"

//Stack trace code
extern "C" void walk_stack();
#include <execinfo.h>

//Aliases
#define Print GlobalRenderer->Print
#define Next GlobalRenderer->Next
#define Clear GlobalRenderer->Clear
#define Colour GlobalRenderer->Colour

#define blue 0x000606c0
#define red 0xffee3333
#define black 0x00000000
#define yellow 0xffbbbb33
#define green 0xff33ee33

//Defaults
const char* panicLoc = "an unknown fault";
const char* lmo = "N/A";
const char* AHCIInit = "No";
const char* OSVersion = "Blep OS v0.0.1 (Closed alpha)";
const char* KernelVersion = "BlepKernel v0.1_r21";

const char* systemStatus = "OK";

void PanicPrint(const char* panicMessage){//Print generic kernel panic messages

    GlobalRenderer->ClearColour = blue;
    //Clear();
    //GlobalRenderer->CursorPosition = {0, 32};

    Next();
    Colour = 0xffffffff;
    Print("================ Kernel panic ================");
    Next();
    Next();
    Print("The system encountered a ");
    Colour = 0xffffff33;
    Print(panicMessage);
    Colour = 0xffffffff;
    Print(", most likely caused by ");
    Colour = 0xffffff33; 
    Print(panicLoc);
    Colour = 0xffffffff;
    Print(".");
}

void PanicDump(){

    Next();
    Next();
    Print("--- OS info ---");
    Next();
    Print("OS version: ");
    Colour = 0xffffff33; 
    Print(OSVersion);
    Colour = 0xffffffff;
    Next();
    Print("Kernel version: ");
    Colour = 0xffffff33; 
    Print(KernelVersion);
    Colour = 0xffffffff;
    Next();
    Next();
    Print("--- Debug info ---");
    Next();
    Next();
    Print("Last memory operation: ");
    Colour = 0xffffff33; 
    Print(lmo);
    Colour = 0xffffffff;
    Next();
    Print("AHCI init finished? ");
    Colour = 0xffffff33; 
    Print(AHCIInit);
    Colour = 0xffffffff;
    Next();
    Next();
    Print("Stack trace: ");
    Next();
    
    Print("(Not yet implemented)");


    Next();
    Next();
    Colour = 0xffffffff;
    Print("If none of this makes sense to you, send an image of this screen to '<address goes here>'");
    Next();
    Colour = 0xffffff33;
    Print("===End kernel panic===");
}

void Stop(){//"Halt and catch fire"

    asm ("cli");
    Next();
    
    if(systemStatus == "Panic"){Colour = red;}
    if(systemStatus == "Exited"){Colour = yellow;}
    if(systemStatus == "OK"){Colour = green;}

    GlobalRenderer->CursorPosition = {0, (GlobalRenderer->TargetFramebuffer->Height - 16)};
    Print(" > System halted. You may now turn off your PC or virtual machine.");
    GlobalRenderer->CursorPosition = {(GlobalRenderer->TargetFramebuffer->Width - 136), (GlobalRenderer->TargetFramebuffer->Height - 16)};
    Print("Status: ");
    Print(systemStatus);
    while (true) asm ("hlt");
}

void Panic(const char* panicMessage){
    systemStatus = "Panic";
    PanicPrint(panicMessage);
    PanicDump();
    Stop();
}

void Panic(const char* panicMessage, const char* Info){
    systemStatus = "Panic";
    PanicPrint(panicMessage);
    Next();
    Print(Info);
    PanicDump();
    Stop();
}

void ReturnPanic(){//An instance of Panic exclusively for if the kernel returns prematurely
    systemStatus = "Exited";
    Colour = 0xffffffff;
    Next();
    Print("The main kernel loop exited safely and did not trigger any exceptions.");
    Next();
    Print("Note: If you're trying to force a shutdown, this is not how you do it!");
    Colour = yellow;
    Stop();
}