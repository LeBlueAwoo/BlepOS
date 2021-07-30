#pragma once

#define stopColour 0xffee3333

extern const char* panicLoc;    //Panic location
extern const char* lmo;         //Last memory operation
extern const char* AHCIInit;    //AHCI init finished?
extern const char* OSVersion;
extern const char* KernelVersion;

void Panic(const char* panicMessage);
void Panic(const char* panicMessage, const char* Info);
void ReturnPanic();

void Stop();