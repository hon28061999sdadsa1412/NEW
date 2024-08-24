#include "CPed.h"

bool CPed::get_player(uintptr_t& base)
{
    ptr = base;
    return ptr == NULL ? false : true;
}

uintptr_t CPed::get_weapon()
{
    uintptr_t weapon_mgr = m.Read<uintptr_t>(ptr + offset::m_pWeaponManager);

    return m.Read<uintptr_t>(weapon_mgr + 0x20);
}

bool CPed::isPlayer()
{
    return player_info != NULL;
}

bool CPed::isDead()
{
    return m_fHealth <= 0 || m_pVecPosition == Vector3(0.f, 0.f, 0.f);
}

bool CPed::Update()
{
    player_info = m.Read<uintptr_t>(ptr + offset::m_pInfo);
    current_weapon = get_weapon();

    m_fHealth = m.Read<float>(ptr + offset::m_pHealth);
    m_pVecPosition = m.Read<Vector3>(ptr + offset::m_pLocation);

    if (isDead())
        return false;

    m_fArmor = m.Read<float>(ptr + offset::m_pArmor);
    m_fMaxHealth = m.Read<float>(ptr + offset::m_pMaxHealth);
    m_pBoneMatrix = m.Read<Matrix>(ptr + offset::m_bMatrix);
    UpdateBones();

    return true;
}

void CPed::UpdateBones()
{
    CBone bone = m.Read<CBone>(ptr + offset::m_pBoneList);
    BoneList[HEAD] = Vec3_Transform(&bone.gHead, &m_pBoneMatrix);
    BoneList[LEFTFOOT] = Vec3_Transform(&bone.gLeftFoot, &m_pBoneMatrix);
    BoneList[RIGHTFOOT] = Vec3_Transform(&bone.gRightFoot, &m_pBoneMatrix);
    BoneList[LEFTANKLE] = Vec3_Transform(&bone.gLeftAnkle, &m_pBoneMatrix);
    BoneList[RIGHTANKLE] = Vec3_Transform(&bone.gRightAnkle, &m_pBoneMatrix);
    BoneList[LEFTHAND] = Vec3_Transform(&bone.gLeftHand, &m_pBoneMatrix);
    BoneList[RIGHTHAND] = Vec3_Transform(&bone.gRightHand, &m_pBoneMatrix);
    BoneList[NECK] = Vec3_Transform(&bone.gNeck, &m_pBoneMatrix);
    BoneList[HIP] = Vec3_Transform(&bone.gHip, &m_pBoneMatrix);
}

/*
Vector3 CPed::GetBonePosition(const int& BoneID)
{
    Vector3 bone = m.Read<Vector3>(ptr + offset::m_pBoneList + (BoneID * 0x10)); // 0x430
    Vector3 transform = Vec3_Transform(&bone, &m_bMatrix);

    return transform;
}*/