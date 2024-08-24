#include "Cheat.h"

void Cheat::AimBot()
{
    while (g.Run)
    {
        CPed target = FindBestTarget();

        if (IsKeyDown(g.AimKey0) || IsKeyDown(g.AimKey1))
        {
            if (!Vec3_Empty(target.BoneList[NECK]))
            {
                uintptr_t camera = m.Read<uintptr_t>(m.BaseAddress + offset::Camera);
                Vector3 ViewAngle = m.Read<Vector3>(camera + 0x3D0); // 0x40
                Vector3 CameraPos = m.Read<Vector3>(camera + 0x60);

                Vector3 Angle = CalcAngle(CameraPos, target.BoneList[NECK]);
                NormalizeAngles(Angle);
                Vector3 Delta = Angle - ViewAngle;
                NormalizeAngles(Delta);
                Vector3 WriteAngle = ViewAngle + Delta;
                NormalizeAngles(WriteAngle);

                if (!Vec3_Empty(WriteAngle))
                {
                    m.Write<Vector3>(camera + 0x3D0, WriteAngle);
                }
            }
        }

        Sleep(1);
    }
}

void Cheat::Misc()
{
    while (g.Run)
    {
        // GodMode
        if (g.GodMode && m.Read<bool>(local.ptr + offset::m_pGodMode) == false)
            m.Write<bool>(local.ptr + offset::m_pGodMode, true);
        else if (!g.GodMode && m.Read<bool>(local.ptr + offset::m_pGodMode) == true)
            m.Write<bool>(local.ptr + offset::m_pGodMode, false);

        if (g.NoRecoil)
            m.Write<float>(local.current_weapon + offset::m_WepRecoil, 0.f);

        if (g.NoSpread)
            m.Write<float>(local.current_weapon + offset::m_WepSpread, 0.f);

        if (g.RangeBypass)
            m.Write<float>(local.current_weapon + offset::m_WepRange, 999.f);

        Sleep(100);
    }
}

void Cheat::UpdateList()
{
    while (g.Run)
    {
        std::vector<CPed> list;
        GWorld = m.Read<uintptr_t>(m.BaseAddress + offset::GameWorld);
        local.ptr = m.Read<uintptr_t>(GWorld + 0x8);
        ViewPort = m.Read<uintptr_t>(m.BaseAddress + offset::ViewPort);

        // Access EntityList
        uintptr_t ReplayInterface = m.Read<uintptr_t>(m.BaseAddress + offset::ReplayInterface);
        uintptr_t EntityListPtr = m.Read<uintptr_t>(ReplayInterface + 0x18);
        uintptr_t EntityList = m.Read<uintptr_t>(EntityListPtr + 0x100);

        for (int i = 0; i < 256; i++)
        {
            CPed ped = CPed{};
            uintptr_t player = m.Read<uintptr_t>(EntityList + (i * 0x10));
            
            if (player == local.ptr)
                continue;
            else if (!ped.get_player(player))
                continue;
            else if (!ped.Update())
                continue;

            list.push_back(ped);
        }

        this->EntityList = list;
        Sleep(500);
    }
}

CPed Cheat::FindBestTarget()
{
    CPed target{};
    CPed* pLocal = &local;
    Matrix ViewMatrix = m.Read<Matrix>(ViewPort + 0x24C);

    float MinFov = 9999.f;
    Vector2 Center = Vector2(g.GameRect.right / 2.f, g.GameRect.bottom / 2.f);

    for (auto& ped : EntityList)
    {
        CPed* pEntity = &ped;

        // Checks
        if (!pLocal->Update())
            break;
        else if (!pEntity->Update())
            continue;

        Vector2 pScreen{};
        if (!WorldToScreen(ViewMatrix, pEntity->BoneList[NECK], pScreen))
            continue;

        float FOV = abs((Center - pScreen).Length());

        if (FOV < g.AimFov)
        {
            if (FOV < MinFov)
            {
                target = ped;
                MinFov = FOV;
                continue;
            }
        }
    }

    return target;
}