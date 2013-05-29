﻿// created by i-saint
// distributed under Creative Commons Attribution (CC BY) license.
// https://github.com/i-saint/DynamicObjLoader

#include <windows.h>

//#define dpDisable
//#define dpLinkStatic
#define dpLinkDynamic
#include "DynamicPatcher.h"

#ifdef _WIN64
#   define dpPlatform "x64"
#else
#   define dpPlatform "Win32"
#endif
#ifdef _DEBUG
#   define dpConfiguration "Debug"
#else
#   define dpConfiguration "Release"
#endif

dpNoInline void OverriddenByLib1()
{
    ::Sleep(1);
}

dpNoInline void OverriddenByLib2()
{
    ::Sleep(2);
}

dpNoInline void OverriddenByDll()
{
    ::Sleep(3);
}


int main(int argc, char *argv[])
{
    dpInitialize();
    dpLoad("Test_Dll.dll");
    dpLoad("Test_Lib.lib");
    dpLink();

    printf("DynamicPatcher Test_UseLibDll\n");
    for(;;) {
        OverriddenByLib1();
        OverriddenByLib2();
        OverriddenByDll();
        ::Sleep(1000);
        dpUpdate();
    }
    dpFinalize();
}