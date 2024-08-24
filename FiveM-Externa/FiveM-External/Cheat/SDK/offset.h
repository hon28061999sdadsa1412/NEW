#pragma once

/*
// b2944
namespace offset
{
    // Base
    constexpr auto GameWorld = 0x257BEA0;
    constexpr auto ReplayInterface = 0x1F42068;
    constexpr auto ViewPort = 0x1FEAAC0;
    constexpr auto Camera = 0x1FEB698;

    // Ped
    constexpr auto m_pBoneMatrix = 0x60;
    constexpr auto m_pLocation = 0x90;
    constexpr auto m_pGodMode = 0x189;
    constexpr auto m_pHealth = 0x280;
    constexpr auto m_pMaxHealth = 0x284;
    constexpr auto m_pBoneList = 0x410;
    constexpr auto m_pArmor = 0x150C;
   
    // Pointer
    constexpr auto m_pInfo = 0x10A8;          // PlayerInfo
    constexpr auto m_pWeaponManager = 0x10B8; // WeaponManager

    // CurrentWeapon (WepaonManager + 0x20)
    constexpr auto m_WepSpread = 0x74;
    constexpr auto m_WepRecoil = 0x2F4;
    constexpr auto m_WepRange  = 0x28C;
}
*/

// b2699
namespace offset
{
    // Base
    constexpr auto GameWorld = 0x26684D8;
    constexpr auto ReplayInterface = 0x20304C8;
    constexpr auto ViewPort = 0x20D8C90;
    constexpr auto Camera = 0x20D9868;

    // Ped
    constexpr auto m_bMatrix = 0x60;
    constexpr auto m_pLocation = 0x90;
    constexpr auto m_pGodMode = 0x189;
    constexpr auto m_pHealth = 0x280;
    constexpr auto m_pMaxHealth = 0x2A0;
    constexpr auto m_pBoneList = 0x430;
    constexpr auto m_pArmor = 0x1530;

    // Pointer
    constexpr auto m_pInfo = 0x10C8;          // PlayerInfo
    constexpr auto m_pWeaponManager = 0x10D8; // WeaponManager
    
    // CurrentWeapon (WepaonManager + 0x20)
    constexpr auto m_WepSpread = 0x84;
    constexpr auto m_WepRecoil = 0x2F4;
    constexpr auto m_WepRange = 0x28C;
}