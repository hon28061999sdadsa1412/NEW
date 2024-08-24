#pragma once
#include <string>
#include <Windows.h>

struct Globals
{
    // System(Base
    bool Run = false;
    bool ShowMenu = false;

    // GameData
    HWND GameHwnd = NULL;
    RECT GameRect{};
    POINT GamePoint{};
    std::string ProcName;

    // Aim
    bool AimBot = true;
    float AimFov = 100.f;

    // Visual
    bool ESP = true;
    bool ESP_Box = true;
    bool ESP_Line = false;
    bool ESP_Distance = true;
    bool ESP_HealthBar = true;
    bool ESP_Skeleton = true;
    float ESP_MaxDistance = 1000.f;

    // Misc
    bool GodMode = false;
    bool NoRecoil = false;
    bool NoSpread = false;
    bool RangeBypass = false;

    // System(Cheat
    bool Crosshair = false;
    bool StreamProof = false;

    // Key
    int MenuKey = VK_INSERT;
    int AimKey0 = VK_RBUTTON;
    int AimKey1 = VK_LBUTTON;
};

extern Globals g;
extern bool IsKeyDown(int VK);
extern const char* KeyNames[];