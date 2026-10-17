/* CoF-SourceCode -- reconstructed from hl12.pdb + hl12.c (Hex-Rays 9.2)
 * module : .\debughl\CoF_M16.obj
 * source : .\CoF_M16.cpp
 * built  : 2012-03-21 21:35:13 UTC (PDB signature 1332365713, age 17)
 * rule   : Class::member -> Class__member, `name' -> _name_ (see tools/rebuild_tree.py)
 */
#include "cof_decls.h"

void __cdecl weapon_m16(entvars_s *pev)
{
  GetClassPtr_CM16_(pev);
}

void __cdecl weapon_mp5k(entvars_s *pev)
{
  GetClassPtr_CM16_(pev);
}

void __thiscall CM16__StartSuicide(CM16 *this)
{
  const Vector *v1; // eax
  edict_s *v2; // eax
  edict_s *v3; // eax
  edict_s *v4; // eax
  int v5; // [esp+Ch] [ebp-54h]
  Vector v6; // [esp+10h] [ebp-50h] BYREF
  CM16 *thisa; // [esp+5Ch] [ebp-4h]

  thisa = this;
  (*(void (__thiscall **)(CM16 *, int))&this->gap0[8])(this, 1082130432);
  CBaseEntity__ThinkSet((CBaseEntity *)thisa, (void (__thiscall *)(CBaseEntity *))CM16__SuicideShot, "&CM16::SuicideShot");
  CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 17, 1, 0);
  thisa->m_iSuicideButtonsPressed = 0;
  thisa->m_iSuicideButtonsNeeded = g_engfuncs.pfnRandomLong(10, 15);
  UTIL_ScreenShake(&thisa->m_pPlayer->pev->origin, 12.0, 100.0, 2.0, 1000.0);
  v1 = Vector__Vector__ov4(&v6, 255.0, 0.0, 0.0);
  UTIL_ScreenFade((CBaseEntity *)thisa->m_pPlayer, v1, 2.0, 0.0, 0x7Du, 0);
  thisa->m_pPlayer->pev->fuser3 = 10.0;
  CBasePlayer__ShowHint(thisa->m_pPlayer, (int)("suicide" - gpGlobals->pStringBase), 0);
  v5 = g_engfuncs.pfnRandomLong(0, 2);
  if ( v5 )
  {
    if ( v5 == 1 )
    {
      v3 = ENT__ov1(thisa->m_pPlayer->pev);
      EMIT_SOUND_DYN(v3, 2, "player/Vocal/Suicide/suicide_panic2.wav", 1.0, 0.80000001, 0, 100);
    }
    else if ( v5 == 2 )
    {
      v4 = ENT__ov1(thisa->m_pPlayer->pev);
      EMIT_SOUND_DYN(v4, 2, "player/Vocal/Suicide/suicide_panic3.wav", 1.0, 0.80000001, 0, 100);
    }
  }
  else
  {
    v2 = ENT__ov1(thisa->m_pPlayer->pev);
    EMIT_SOUND_DYN(v2, 2, "player/Vocal/Suicide/suicide_panic1.wav", 1.0, 0.80000001, 0, 100);
  }
}

void __thiscall CM16__SuicideShot(CM16 *this)
{
  edict_s *v1; // eax
  int v2; // [esp-4h] [ebp-58h]

  if ( this->m_iClip )
  {
    this->m_pPlayer->pev->health = 0.0;
    (*(void (__thiscall **)(CBasePlayer *, entvars_s *, int))&this->m_pPlayer->gap0[108])(
      this->m_pPlayer,
      this->m_pPlayer->pev,
      1);
    v2 = g_engfuncs.pfnRandomLong(0, 10) + 95;
    v1 = ENT__ov1(this->m_pPlayer->pev);
    EMIT_SOUND_DYN(v1, 0, "weapons/m16/m16_fire.wav", 1.0, 0.80000001, 0, v2);
  }
  else
  {
    CBasePlayerWeapon__PlayEmptySound((CBasePlayerWeapon *)this);
    this->m_fEmptyClickTime = gpGlobals->time + 0.25;
    CM16__StopSuicide((CM16 *)this);
  }
}

void __thiscall CM16__StopSuicide(CM16 *this)
{
  const Vector *v1; // eax
  Vector v2; // [esp+Ch] [ebp-50h] BYREF
  CM16 *thisa; // [esp+58h] [ebp-4h]

  thisa = this;
  CBaseEntity__ThinkSet((CBaseEntity *)this, 0, "NULL");
  thisa->m_iSuicideButtonsPressed = 0;
  thisa->m_iSuicideState = 0;
  v1 = Vector__Vector__ov4(&v2, 128.0, 128.0, 128.0);
  UTIL_ScreenFade((CBaseEntity *)thisa->m_pPlayer, v1, 0.5, 0.0, 0xFFu, 0);
  if ( thisa->b_BurstMode )
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 7, 1, 0);
  else
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 0, 1, 0);
  if ( thisa->m_pPlayer->pev->fuser3 == 10.0 )
    thisa->m_pPlayer->pev->fuser3 = 0.0;
  thisa->m_pPlayer->m_flNextAttack = gpGlobals->time + 1.0;
  thisa->m_flTimeWeaponIdle = gpGlobals->time + 1.0;
  thisa->m_flNextSecondaryAttack = thisa->m_flTimeWeaponIdle;
  thisa->m_flNextPrimaryAttack = thisa->m_flNextSecondaryAttack;
}

void __thiscall CM16__Spawn(CM16 *this)
{
  edict_s *v1; // eax

  this->pev->classname = (int)("weapon_m16" - gpGlobals->pStringBase);
  (*(void (__thiscall **)(CM16 *))&this->gap0[48])(this);
  v1 = ENT__ov1(this->pev);
  g_engfuncs.pfnSetModel(v1, "models/weapons/m16/w_m16.mdl");
  this->m_iId = 9;
  this->m_iSprintIdleAnim1 = 15;
  this->m_iSprintIdleAnim2 = 666;
  this->b_BurstMode = 1;
  this->m_flKickPerShot = 0.75;
  if ( this->pev->frags <= 0.0 )
  {
    if ( this->pev->frags == -2.0 )
      this->m_iClip = -666;
    this->m_iDefaultAmmo = 20;
  }
  else
  {
    this->m_iDefaultAmmo = (unsigned __int64)this->pev->frags;
  }
  while ( !this->script )
    this->script = (int)("inventoryitems/weapons/weapon_m16.txt" - gpGlobals->pStringBase);
  this->pev->renderfx = 99;
  this->m_bCanSuicide = 1;
  this->strwmodel = (int)("models/weapons/m16/w_m16.mdl" - gpGlobals->pStringBase);
  CBasePlayerItem__FallInit((CBasePlayerItem *)this);
}

void __thiscall CM16__Precache(CM16 *this)
{
  PRECACHE_MODEL("models/weapons/m16/v_m16.mdl");
  PRECACHE_MODEL("models/weapons/m16/w_m16.mdl");
  PRECACHE_MODEL("models/null.mdl");
  this->m_iShell = PRECACHE_MODEL("models/556shell.mdl");
  PRECACHE_MODEL("models/w_9mmclip.mdl");
  PRECACHE_SOUND("weapons/item_get.wav");
  PRECACHE_SOUND("weapons/m16/m16_cock.wav");
  PRECACHE_SOUND("weapons/m16/m16_magin.wav");
  PRECACHE_SOUND("weapons/m16/m16_magout.wav");
  if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
    PRECACHE_MODEL("police/models/weapons/m16/p_m16.mdl");
  PRECACHE_SOUND("weapons/m16/m16_fire.wav");
}

int __thiscall CM16__GetItemInfo(CM16 *this, ItemInfo *p)
{
  p->pszName = &gpGlobals->pStringBase[this->pev->classname];
  p->pszAmmo1 = "m16";
  p->iMaxAmmo1 = 200;
  p->pszAmmo2 = 0;
  p->iMaxAmmo2 = -1;
  p->iMaxClip = 20;
  p->iSlot = 4;
  p->iPosition = 0;
  p->iFlags = 0;
  this->m_iId = 9;
  p->iId = 9;
  p->iWeight = 5;
  return 1;
}

int __thiscall CM16__Deploy(CM16 *this)
{
  this->m_iSprintState = 0;
  this->shoot_num = 0;
  if ( this->m_iClip == -666 )
    this->m_iClip = 0;
  this->m_iSuicideState = this->m_iSuicideState == 666;
  CBasePlayer__ShowHint(this->m_pPlayer, (int)("weaponfunctionm16" - gpGlobals->pStringBase), 0);
  if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
  {
    if ( this->b_BurstMode )
      return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
               "models/weapons/m16/v_m16.mdl",
               "police/models/weapons/m16/p_m16.mdl",
               7,
               "mp5",
               0,
               0);
    else
      return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
               "models/weapons/m16/v_m16.mdl",
               "police/models/weapons/m16/p_m16.mdl",
               0,
               "mp5",
               0,
               0);
  }
  else if ( this->b_BurstMode )
  {
    return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this, "models/weapons/m16/v_m16.mdl", "models/null.mdl", 7, "mp5", 0, 0);
  }
  else
  {
    return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this, "models/weapons/m16/v_m16.mdl", "models/null.mdl", 0, "mp5", 0, 0);
  }
}

void __thiscall CM16__Holster(CM16 *this)
{
  const Vector *v1; // eax
  float v2; // [esp+Ch] [ebp-54h]
  Vector v3; // [esp+10h] [ebp-50h] BYREF
  CM16 *thisa; // [esp+5Ch] [ebp-4h]

  thisa = this;
  if ( this->m_iSuicideState )
  {
    CBaseEntity__ThinkSet((CBaseEntity *)thisa, 0, "NULL");
    thisa->m_iSuicideButtonsPressed = 0;
    thisa->m_iSuicideState = 0;
    v1 = Vector__Vector__ov4(&v3, 128.0, 128.0, 128.0);
    UTIL_ScreenFade((CBaseEntity *)thisa->m_pPlayer, v1, 0.5, 0.0, 0xFFu, 0);
  }
  if ( thisa->b_BurstMode )
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 12, 1, 0);
  else
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 5, 1, 0);
  v2 = gpGlobals->time + 0.5;
  thisa->m_pPlayer->m_flNextAttack = v2;
}

void __thiscall CM16__Shoot(CM16 *this)
{
  Vector *v1; // eax
  Vector *v2; // eax
  Vector *v3; // eax
  Vector *v4; // eax
  int v5; // eax
  const Vector *v6; // eax
  float v7; // eax
  const edict_s *v8; // eax
  Vector *v9; // eax
  edict_s *v10; // eax
  Vector v11; // [esp-3Ch] [ebp-180h] BYREF
  Vector v12; // [esp-30h] [ebp-174h] BYREF
  Vector v13; // [esp-24h] [ebp-168h] BYREF
  int v14; // [esp-18h] [ebp-15Ch]
  const char *v15; // [esp-14h] [ebp-158h]
  int m_iId; // [esp-10h] [ebp-154h]
  float v17; // [esp-Ch] [ebp-150h]
  entvars_s *p_vecShellOrigin; // [esp-8h] [ebp-14Ch]
  int random_seed; // [esp-4h] [ebp-148h]
  float v20; // [esp+Ch] [ebp-138h]
  Vector v21; // [esp+10h] [ebp-134h] BYREF
  Vector v22; // [esp+1Ch] [ebp-128h] BYREF
  Vector v23; // [esp+28h] [ebp-11Ch] BYREF
  Vector result; // [esp+34h] [ebp-110h] BYREF
  Vector v25; // [esp+40h] [ebp-104h] BYREF
  Vector v26; // [esp+4Ch] [ebp-F8h] BYREF
  Vector v27; // [esp+58h] [ebp-ECh] BYREF
  Vector v28; // [esp+64h] [ebp-E0h] BYREF
  Vector v29; // [esp+70h] [ebp-D4h] BYREF
  Vector v30; // [esp+7Ch] [ebp-C8h] BYREF
  Vector v31; // [esp+94h] [ebp-B0h] BYREF
  int pitch; // [esp+E0h] [ebp-64h]
  float PlayerSpeed; // [esp+E4h] [ebp-60h]
  Vector vecDir; // [esp+E8h] [ebp-5Ch] BYREF
  Vector vecAiming; // [esp+F4h] [ebp-50h] BYREF
  Vector vecSrc; // [esp+100h] [ebp-44h] BYREF
  Vector vecShellEnd; // [esp+10Ch] [ebp-38h] BYREF
  Vector vecShellSrc; // [esp+118h] [ebp-2Ch] BYREF
  int flags; // [esp+124h] [ebp-20h]
  Vector vecShellOrigin; // [esp+128h] [ebp-1Ch] BYREF
  Vector vecShellVelocity; // [esp+134h] [ebp-10h] BYREF
  CM16 *thisa; // [esp+140h] [ebp-4h]

  thisa = this;
  if ( !this->m_iSprintState && !thisa->m_iSuicideState )
  {
    if ( thisa->m_pPlayer->pev->waterlevel == 3 )
    {
      if ( thisa->m_fEmptyClickTime < (double)gpGlobals->time )
      {
        if ( thisa->m_bIronSights )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 25, 1, 0);
        }
        else if ( thisa->b_BurstMode )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 24, 1, 0);
        }
        else
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 23, 1, 0);
        }
        CBasePlayerWeapon__PlayEmptySound((CBasePlayerWeapon *)thisa);
        thisa->m_fEmptyClickTime = gpGlobals->time + 0.25;
      }
    }
    else if ( thisa->m_iClip > 0 )
    {
      random_seed = (int)Vector__operator_mul(&gpGlobals->v_forward, &result, 40.0);
      v17 = (int)(*(float *)&(int){ (int)(Vector__operator_mul(&gpGlobals->v_up, &v22, 200.0)) });
      v1 = Vector__operator_mul(&gpGlobals->v_right, &v21, 220.0);
      v2 = Vector__operator_plus(v1, &v23, (const Vector *)LODWORD(v17));
      Vector__operator_plus(v2, &vecShellVelocity, (const Vector *)random_seed);
      random_seed = (int)Vector__operator_mul(&gpGlobals->v_right, &v28, 20.0);
      p_vecShellOrigin = (entvars_s *)&vecShellOrigin;
      v17 = (int)(*(float *)&(int){ (int)(Vector__operator_mul(&gpGlobals->v_forward, &v26, 80.0)) });
      m_iId = (int)&v27;
      v3 = Vector__operator_plus(&thisa->pev->origin, &v25, &thisa->pev->view_ofs);
      v4 = Vector__operator_plus(v3, &v27, (const Vector *)LODWORD(v17));
      Vector__operator_plus(v4, &vecShellOrigin, (const Vector *)random_seed);
      EjectBrass(&vecShellOrigin, &vecShellVelocity, thisa->pev->angles.y, thisa->m_iShell, 1);
      MESSAGE_BEGIN__ov4_2(1, gmsgParticle, 0, thisa->m_pPlayer->pev);
      v5 = CBaseEntity__entindex((CBaseEntity *)thisa);
      g_engfuncs.pfnWriteShort(v5);
      g_engfuncs.pfnWriteString("aurora/gunsmoke.aur");
      g_engfuncs.pfnWriteByte(1);
      g_engfuncs.pfnWriteString("models/weapons/m16/v_m16.mdl");
      g_engfuncs.pfnWriteShort(0);
      g_engfuncs.pfnMessageEnd();
      if ( !thisa->m_pPlayer->m_bInfiniteAmmo )
        --thisa->m_iClip;
      flags = thisa->m_pPlayer->m_iViewValue != 1;
      UTIL_MakeVectors(&thisa->m_pPlayer->pev->v_angle);
      CBasePlayer__GetGunPosition((CBasePlayer *)thisa->m_pPlayer, &vecShellSrc);
      v6 = Vector__operator_mul(&gpGlobals->v_right, &v29, 32.0);
      Vector__operator_plus(&vecShellSrc, &vecShellEnd, v6);
      random_seed = 0;
      p_vecShellOrigin = 0;
      v17 = 0.0;
      m_iId = thisa->m_iId;
      v15 = 0;
      v14 = 0;
      LODWORD(v13.z) = (int)&vecShellEnd;
      HIWORD(v7) = HIWORD(thisa);
      LODWORD(v13.y) = (int)&thisa->m_pPlayer->pev->origin;
      v13.x = 0.0;
      LOWORD(v7) = m_usThirdFlash;
      v12.z = v7;
      v8 = ENT__ov1(thisa->m_pPlayer->pev);
      g_engfuncs.pfnPlaybackEvent(
        flags,
        v8,
        LOWORD(v12.z),
        0.0,
        (float *)LODWORD(v13.y),
        &vecShellEnd.x,
        0.0,
        0.0,
        m_iId,
        0,
        0,
        0);
      CBasePlayer__PlayerAnimation(thisa->m_pPlayer, "m16_shoot", 0);
      v20 = (int)(*(float *)&(int){ (int)(g_engfuncs.pfnRandomLong(0, 2)) });
      if ( v20 == 0.0 )
      {
        CBasePlayer__ViewPunch(thisa->m_pPlayer, 1.0, 1.0, 1.0);
      }
      else if ( LODWORD(v20) == 1 )
      {
        CBasePlayer__ViewPunch(thisa->m_pPlayer, -1.0, 1.0, 1.0);
      }
      else if ( LODWORD(v20) == 2 )
      {
        CBasePlayer__ViewPunch(thisa->m_pPlayer, 1.0, 1.0, -1.0);
      }
      if ( (thisa->m_pPlayer->pev->flags & 0x4000) != 0 )
        UTIL_ScreenShake(&thisa->m_pPlayer->pev->origin, 2.0, 0.1, 0.1, 2.0);
      else
        UTIL_ScreenShake(&thisa->m_pPlayer->pev->origin, 5.0, 0.25, 0.15000001, 2.0);
      if ( thisa->m_bIronSights )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 21, 1, 0);
      }
      else if ( thisa->b_BurstMode )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 9, 1, 0);
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 2, 1, 0);
      }
      CBasePlayer__SetAnimation(thisa->m_pPlayer, PLAYER_ATTACK1);
      thisa->m_pPlayer->pev->effects |= 2u;
      v9 = Vector__operator_plus(
             &thisa->m_pPlayer->pev->v_angle,
             &v30,
             &thisa->m_pPlayer->pev->punchangle);
      UTIL_MakeVectors(v9);
      CBasePlayer__GetGunPosition((CBasePlayer *)thisa->m_pPlayer, &vecSrc);
      CBasePlayer__GetAutoaimVector(thisa->m_pPlayer, &vecAiming, 0.17364818);
      Vector__Vector__ov1(&vecDir);
      PlayerSpeed = Vector__Length2D(&thisa->m_pPlayer->pev->velocity);
      thisa->m_flCurrentKick = thisa->m_flCurrentKick + thisa->m_flKickPerShot;
      thisa->m_flNextKickReductionTime = gpGlobals->time + 0.35;
      random_seed = thisa->m_pPlayer->random_seed;
      p_vecShellOrigin = thisa->m_pPlayer->pev;
      LODWORD(v17) = (unsigned __int64)gSkillData.DmgM16;
      m_iId = 2;
      v15 = (const char *)3;
      v14 = 1174405120;
      Vector__Vector__ov2(&v13, &thisa->m_AccuracyVector);
      Vector__Vector__ov2(&v12, &vecAiming);
      Vector__Vector__ov2(&v11, &vecSrc);
      vecDir = *CBaseEntity__FireBulletsPlayer(
                  (CBaseEntity *)thisa->m_pPlayer,
                  &v31,
                  1u,
                  v11,
                  v12,
                  v13,
                  *(float *)&v14,
                  *(float *)&v15,
                  m_iId,
                  SLODWORD(v17),
                  p_vecShellOrigin,
                  random_seed);
      CBasePlayer__ViewKnock(thisa->m_pPlayer, 3.0);
      pitch = 100;
      random_seed = 100;
      p_vecShellOrigin = 0;
      v17 = 0.80000001;
      m_iId = 1065353216;
      v15 = "weapons/m16/m16_fire.wav";
      v14 = 0;
      v10 = ENT__ov1(thisa->m_pPlayer->pev);
      EMIT_SOUND_DYN(v10, v14, v15, *(float *)&m_iId, v17, (int)p_vecShellOrigin, random_seed);
      thisa->m_pPlayer->m_iExtraSoundTypes = 1;
      v20 = gpGlobals->time + 0.2;
      thisa->m_pPlayer->m_flStopExtraSoundTime = v20;
      if ( thisa->b_BurstMode && ++thisa->shoot_num < 3 )
      {
        (*(void (__thiscall **)(CM16 *, int))&thisa->gap0[8])(thisa, 1028443341);
        CBaseEntity__ThinkSet((CBaseEntity *)thisa, (void (__thiscall *)(CBaseEntity *))CM16__Shoot, "Shoot");
      }
    }
    else if ( thisa->m_fFireOnEmpty )
    {
      if ( thisa->m_fEmptyClickTime < (double)gpGlobals->time )
      {
        if ( thisa->m_bIronSights )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 25, 1, 0);
        }
        else if ( thisa->b_BurstMode )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 24, 1, 0);
        }
        else
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 23, 1, 0);
        }
        CBasePlayerWeapon__PlayEmptySound((CBasePlayerWeapon *)thisa);
        thisa->m_fEmptyClickTime = gpGlobals->time + 0.25;
      }
    }
    else
    {
      CM16__Reload((CM16 *)thisa);
    }
  }
}

void __thiscall CM16__WeaponToggle(CM16 *this)
{
  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && !this->m_iSprintState
    && !this->m_iSuicideState )
  {
    if ( this->m_bIronSights )
    {
      if ( this->b_BurstMode )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 33, 1, 0);
        this->b_BurstMode = 0;
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 32, 1, 0);
        this->b_BurstMode = 1;
      }
    }
    else if ( this->b_BurstMode )
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 13, 1, 0);
      this->b_BurstMode = 0;
    }
    else
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 6, 1, 0);
      this->b_BurstMode = 1;
    }
    this->m_flNextSecondaryAttack = gpGlobals->time + 1.0;
    this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
    this->m_flTimeWeaponIdle = gpGlobals->time + 1.0;
  }
}

void __thiscall CM16__PrimaryAttack(CM16 *this)
{
  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && !this->m_iSprintState
    && !this->m_iSuicideState
    && (this->m_pPlayer->m_afButtonPressed & 1) != 0 )
  {
    if ( this->shoot_num >= 3 )
      this->shoot_num = 0;
    if ( this->m_iClip > 0 )
    {
      CM16__Shoot((CM16 *)this);
      if ( this->b_BurstMode )
      {
        this->m_flNextPrimaryAttack = gpGlobals->time + 0.75;
        this->m_flNextSecondaryAttack = gpGlobals->time + 0.75;
      }
      else
      {
        this->m_flNextPrimaryAttack = gpGlobals->time + 0.1;
        this->m_flNextSecondaryAttack = gpGlobals->time + 0.1;
      }
      this->m_flTimeWeaponIdle = gpGlobals->time + 0.66;
    }
    else if ( this->m_fFireOnEmpty )
    {
      CBasePlayerWeapon__PlayEmptySound((CBasePlayerWeapon *)this);
      this->m_flNextSecondaryAttack = gpGlobals->time + 0.8;
      this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
      this->m_flTimeWeaponIdle = gpGlobals->time + 0.8;
    }
    else
    {
      CM16__Reload((CM16 *)this);
    }
  }
}

void __thiscall CM16__SecondaryAttack(CM16 *this)
{
  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && !this->m_iSprintState
    && !this->m_iSuicideState
    && !this->m_bIronSights
    && this->m_pPlayer->m_fStamina > 0.0 )
  {
    (*(void (__thiscall **)(CBasePlayer *, int))&this->m_pPlayer->gap0[8])(this->m_pPlayer, 1047233823);
    CBaseEntity__ThinkSet(
      (CBaseEntity *)this->m_pPlayer,
      (void (__thiscall *)(CBaseEntity *))CBasePlayer__MeleePushBack,
      "&CBasePlayer::MeleePushBack");
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 22, 1, 0);
    CBasePlayer__PlayerAnimation(this->m_pPlayer, "m16_melee", 0);
    this->m_flTimeWeaponIdle = gpGlobals->time + 1.0;
    this->m_flNextSecondaryAttack = this->m_flTimeWeaponIdle;
    this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  }
}

void __thiscall CM16__Reload(CM16 *this)
{
  int v1; // [esp+Ch] [ebp-4Ch]

  if ( this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType] > 0
    && this->m_iSprintState != 1
    && this->m_iSprintState <= 2
    && !this->m_iSuicideState
    && !this->m_bWaitingToReloadIronsights )
  {
    if ( this->m_bIronSights )
    {
      this->m_bWaitingToReloadIronsights = 1;
    }
    else if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
           && this->m_flNextSecondaryAttack <= (double)gpGlobals->time )
    {
      if ( 20 - this->m_iClip >= this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType] )
        v1 = this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType];
      else
        v1 = 20 - this->m_iClip;
      if ( v1 )
      {
        this->m_iSprintState = 2;
        this->shoot_num = 0;
        if ( this->b_BurstMode )
        {
          if ( this->m_iClip )
          {
            this->m_iClip = 0;
            CBasePlayerWeapon__DefaultReload((CBasePlayerWeapon *)this, 20, 10, 3.0, 0, 0);
            CBasePlayer__PlayerAnimation(this->m_pPlayer, "m16_reload", 0);
          }
          else
          {
            this->m_iClip = 0;
            CBasePlayerWeapon__DefaultReload((CBasePlayerWeapon *)this, 20, 11, 4.0, 0, 0);
            CBasePlayer__PlayerAnimation(this->m_pPlayer, "m16_reloadempty", 0);
          }
        }
        else if ( this->m_iClip )
        {
          this->m_iClip = 0;
          CBasePlayerWeapon__DefaultReload((CBasePlayerWeapon *)this, 20, 3, 3.0, 0, 0);
          CBasePlayer__PlayerAnimation(this->m_pPlayer, "m16_reload", 0);
        }
        else
        {
          this->m_iClip = 0;
          CBasePlayerWeapon__DefaultReload((CBasePlayerWeapon *)this, 20, 4, 4.0, 0, 0);
          CBasePlayer__PlayerAnimation(this->m_pPlayer, "m16_reloadempty", 0);
        }
      }
    }
  }
}

void __thiscall CM16__WeaponIdle(CM16 *this)
{
  ;
}

void __thiscall CM16__ItemPostFrame(CM16 *this)
{
  const Vector *v1; // eax
  edict_s *v2; // eax
  edict_s *v3; // eax
  _DWORD *v4; // eax
  edict_s *v5; // eax
  _DWORD *v6; // eax
  edict_s *v7; // eax
  _DWORD *v8; // eax
  edict_s *v9; // eax
  _DWORD *v10; // eax
  edict_s *v11; // eax
  _DWORD *v12; // eax
  float amplitude; // [esp+0h] [ebp-84h]
  float frequency; // [esp+4h] [ebp-80h]
  int v15; // [esp+Ch] [ebp-78h]
  int v16; // [esp+Ch] [ebp-78h]
  int weaponanim; // [esp+Ch] [ebp-78h]
  int v18; // [esp+Ch] [ebp-78h]
  int v19; // [esp+Ch] [ebp-78h]
  int v20; // [esp+Ch] [ebp-78h]
  Vector v21; // [esp+24h] [ebp-60h] BYREF
  float v22; // [esp+70h] [ebp-14h]
  float time; // [esp+74h] [ebp-10h]
  float speed; // [esp+78h] [ebp-Ch]
  int pitch; // [esp+7Ch] [ebp-8h]
  CM16 *thisa; // [esp+80h] [ebp-4h]

  thisa = this;
  if ( this->m_iSprintState == 2 && !thisa->m_fInReload )
    thisa->m_iSprintState = 0;
  if ( thisa->m_bWaitingToReloadIronsights
    && !thisa->m_pPlayer->m_bInPhoneCall
    && thisa->m_pPlayer->m_fPhoneCallTime <= (double)gpGlobals->time
    && thisa->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && thisa->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && thisa->m_flNextTertiaryAttack <= (double)gpGlobals->time
    && !thisa->m_iSprintState
    && !thisa->m_iSuicideState )
  {
    if ( thisa->m_bIronSights )
    {
      thisa->m_bIronSights = 0;
      CM16__IronsightsFrom((CM16 *)thisa);
    }
    else
    {
      thisa->m_bWaitingToReloadIronsights = 0;
      CM16__Reload((CM16 *)thisa);
    }
  }
  if ( thisa->m_iSuicideState == 2 )
  {
    v1 = Vector__Vector__ov4(&v21, 0.0, 0.0, 0.0);
    UTIL_ScreenFade((CBaseEntity *)thisa->m_pPlayer, v1, 0.5, 0.5, 0x80u, 0);
    if ( (thisa->m_pPlayer->m_afButtonPressed & 1) != 0 || (thisa->m_pPlayer->m_afButtonPressed & 0x800) != 0 )
    {
      ++thisa->m_iSuicideButtonsPressed;
      frequency = (float)g_engfuncs.pfnRandomLong(5, 9);
      amplitude = (float)g_engfuncs.pfnRandomLong(5, 9);
      UTIL_ScreenShake(
        &thisa->m_pPlayer->pev->origin,
        amplitude,
        frequency,
        0.15000001,
        2.0);
      if ( g_engfuncs.pfnRandomLong(0, 2) == 2 )
      {
        pitch = g_engfuncs.pfnRandomLong(0, 15) + 90;
        v15 = pitch;
        v2 = ENT__ov1(thisa->m_pPlayer->pev);
        EMIT_SOUND_DYN(v2, 0, "weapons/mobile/punch_swing.wav", 1.0, 0.80000001, 0, v15);
      }
    }
    if ( thisa->m_iSuicideButtonsPressed >= thisa->m_iSuicideButtonsNeeded )
      CM16__StopSuicide((CM16 *)thisa);
  }
  if ( thisa->m_iSuicideState == 1 )
  {
    if ( thisa->m_iSprintState && thisa->m_iNextSprintAnim < (double)gpGlobals->time )
    {
      thisa->m_flNextPrimaryAttack = gpGlobals->time + 0.33;
      thisa->m_flTimeWeaponIdle = gpGlobals->time + 0.35;
      thisa->m_iNextSprintAnim = gpGlobals->time + 0.33;
      thisa->m_iSprintState = 0;
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 16, 1, 0);
    }
    else if ( thisa->m_iNextSprintAnim < (double)gpGlobals->time && !thisa->m_iSprintState )
    {
      thisa->m_iSuicideState = 2;
      CM16__StartSuicide((CM16 *)thisa);
    }
  }
  speed = Vector__Length2D(&thisa->m_pPlayer->pev->velocity);
  time = 0.0;
  if ( !thisa->m_fInReload
    && !thisa->m_iSuicideState
    && thisa->m_iSprintState != 2
    && thisa->m_flNextPrimaryAttack < (double)gpGlobals->time )
  {
    if ( !CBasePlayer__SufficientlyOffTheGround(thisa->m_pPlayer)
      || thisa->m_bIronSights
      || thisa->m_flNextTertiaryAttack >= (double)gpGlobals->time )
    {
      if ( thisa->m_iSprintState == 5 )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 16, 1, 0);
        weaponanim = thisa->m_pPlayer->pev->weaponanim;
        v5 = ENT__ov1(thisa->pev);
        v6 = g_engfuncs.pfnGetModelPtr(v5);
        time = GetSequenceTime(v6, weaponanim);
        thisa->m_flNextPrimaryAttack = time + gpGlobals->time;
        thisa->m_flTimeWeaponIdle = time + gpGlobals->time;
        thisa->m_iSprintState = 0;
      }
    }
    else if ( !thisa->m_iSprintState )
    {
      thisa->m_iSprintState = 5;
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 14, 1, 0);
      v16 = thisa->m_pPlayer->pev->weaponanim;
      v3 = ENT__ov1(thisa->pev);
      v4 = g_engfuncs.pfnGetModelPtr(v3);
      time = GetSequenceTime(v4, v16);
      thisa->m_flNextPrimaryAttack = gpGlobals->time + time * 0.5;
      thisa->m_iNextSprintAnim = time + gpGlobals->time;
    }
    if ( speed > 0.0
      && (thisa->m_pPlayer->pev->flags & 0x40000) != 0
      && thisa->m_iSprintState != 5
      && thisa->m_iSprintState != 1 )
    {
      thisa->m_iSprintState = 1;
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 14, 1, 0);
      v18 = thisa->m_pPlayer->pev->weaponanim;
      v7 = ENT__ov1(thisa->pev);
      v8 = g_engfuncs.pfnGetModelPtr(v7);
      time = GetSequenceTime(v8, v18);
      thisa->m_flNextSecondaryAttack = gpGlobals->time + time * 0.5;
      thisa->m_flNextPrimaryAttack = thisa->m_flNextSecondaryAttack;
      thisa->m_iNextSprintAnim = time + gpGlobals->time;
      thisa->m_flTimeWeaponIdle = time / 2.0 + gpGlobals->time;
    }
    if ( (thisa->m_pPlayer->pev->flags & 0x40000) != 0
      && speed > 0.0
      && thisa->m_iSprintState != 5 )
    {
      v22 = Vector__Length2D(&thisa->m_pPlayer->pev->velocity);
      if ( thisa->m_iSprintState == 1 && thisa->m_iNextSprintAnim < (double)gpGlobals->time && v22 != 0.0 )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 15, 1, 0);
        v19 = thisa->m_pPlayer->pev->weaponanim;
        v9 = ENT__ov1(thisa->pev);
        v10 = g_engfuncs.pfnGetModelPtr(v9);
        time = GetSequenceTime(v10, v19);
        thisa->m_iNextSprintAnim = time + gpGlobals->time;
      }
    }
    if ( ((thisa->m_pPlayer->pev->flags & 0x40000) == 0 || speed <= 0.0)
      && thisa->m_iNextSprintAnim < (double)gpGlobals->time
      && thisa->m_iSprintState == 1 )
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 16, 1, 0);
      v20 = thisa->m_pPlayer->pev->weaponanim;
      v11 = ENT__ov1(thisa->pev);
      v12 = g_engfuncs.pfnGetModelPtr(v11);
      time = GetSequenceTime(v12, v20);
      thisa->m_flNextSecondaryAttack = time + gpGlobals->time;
      thisa->m_flNextPrimaryAttack = thisa->m_flNextSecondaryAttack;
      thisa->m_flTimeWeaponIdle = time + gpGlobals->time;
      thisa->m_iSprintState = 0;
    }
  }
  CBasePlayerWeapon__ItemPostFrame((CBasePlayerWeapon *)thisa);
}

void __thiscall CM16__IronsightsTo(CM16 *this)
{
  const char *DescriptionFromItem; // eax
  const char *v2; // eax
  const char *v3; // eax
  const char *v4; // eax
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  const char *v8; // eax
  edict_s *v9; // eax
  _DWORD *v10; // eax
  int weaponanim; // [esp-4h] [ebp-54h]

  DescriptionFromItem = CBasePlayer__GetDescriptionFromItem(
                          this->m_pPlayer,
                          "ironsight_forward",
                          (char *)&gpGlobals->pStringBase[this->script]);
  if ( strlen(DescriptionFromItem) )
  {
    v2 = CBasePlayer__GetDescriptionFromItem(
           this->m_pPlayer,
           "ironsight_forward",
           (char *)&gpGlobals->pStringBase[this->script]);
    this->m_fIronSightsForward = atof(v2);
  }
  v3 = CBasePlayer__GetDescriptionFromItem(
         this->m_pPlayer,
         "ironsight_right",
         (char *)&gpGlobals->pStringBase[this->script]);
  if ( strlen(v3) )
  {
    v4 = CBasePlayer__GetDescriptionFromItem(
           this->m_pPlayer,
           "ironsight_right",
           (char *)&gpGlobals->pStringBase[this->script]);
    this->m_fIronSightsRight = atof(v4);
  }
  v5 = CBasePlayer__GetDescriptionFromItem(
         this->m_pPlayer,
         "ironsight_up",
         (char *)&gpGlobals->pStringBase[this->script]);
  if ( strlen(v5) )
  {
    v6 = CBasePlayer__GetDescriptionFromItem(
           this->m_pPlayer,
           "ironsight_up",
           (char *)&gpGlobals->pStringBase[this->script]);
    this->m_fIronSightsUp = atof(v6);
  }
  v7 = CBasePlayer__GetDescriptionFromItem(
         this->m_pPlayer,
         "ironsight_zoom",
         (char *)&gpGlobals->pStringBase[this->script]);
  if ( strlen(v7) )
  {
    v8 = CBasePlayer__GetDescriptionFromItem(
           this->m_pPlayer,
           "ironsight_zoom",
           (char *)&gpGlobals->pStringBase[this->script]);
    this->m_iIronSightsZoom = atoi(v8);
  }
  MESSAGE_BEGIN__ov4_2(1, gmsgIronSights, 0, this->m_pPlayer->pev);
  g_engfuncs.pfnWriteCoord(this->m_fIronSightsForward);
  g_engfuncs.pfnWriteCoord(this->m_fIronSightsRight);
  g_engfuncs.pfnWriteCoord(this->m_fIronSightsUp);
  g_engfuncs.pfnWriteByte(this->m_iIronSightsZoom);
  g_engfuncs.pfnWriteByte(1);
  g_engfuncs.pfnMessageEnd();
  MESSAGE_BEGIN__ov4_2(1, gmsgCameraZoom, 0, this->m_pPlayer->pev);
  g_engfuncs.pfnWriteCoord(350.0);
  g_engfuncs.pfnWriteByte(0);
  g_engfuncs.pfnWriteByte(0);
  g_engfuncs.pfnMessageEnd();
  this->m_pPlayer->pev->vuser2.x = (float)this->m_iIronSightsZoom;
  CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 18, 1, 0);
  this->m_bIronSights = 1;
  this->m_flNextTertiaryAttack = gpGlobals->time + 0.3;
  this->m_flNextSecondaryAttack = this->m_flNextTertiaryAttack;
  this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  weaponanim = this->m_pPlayer->pev->weaponanim;
  v9 = ENT__ov1(this->pev);
  v10 = g_engfuncs.pfnGetModelPtr(v9);
  this->m_flTimeWeaponIdle = GetSequenceTime(v10, weaponanim) + gpGlobals->time;
}

void __thiscall CM16__IronsightsFrom(CM16 *this)
{
  const char *DescriptionFromItem; // eax
  const char *v2; // eax
  const char *v3; // eax
  const char *v4; // eax
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  const char *v8; // eax
  edict_s *v9; // eax
  _DWORD *v10; // eax
  int weaponanim; // [esp-4h] [ebp-54h]

  DescriptionFromItem = CBasePlayer__GetDescriptionFromItem(
                          this->m_pPlayer,
                          "ironsight_forward",
                          (char *)&gpGlobals->pStringBase[this->script]);
  if ( strlen(DescriptionFromItem) )
  {
    v2 = CBasePlayer__GetDescriptionFromItem(
           this->m_pPlayer,
           "ironsight_forward",
           (char *)&gpGlobals->pStringBase[this->script]);
    this->m_fIronSightsForward = atof(v2);
  }
  v3 = CBasePlayer__GetDescriptionFromItem(
         this->m_pPlayer,
         "ironsight_right",
         (char *)&gpGlobals->pStringBase[this->script]);
  if ( strlen(v3) )
  {
    v4 = CBasePlayer__GetDescriptionFromItem(
           this->m_pPlayer,
           "ironsight_right",
           (char *)&gpGlobals->pStringBase[this->script]);
    this->m_fIronSightsRight = atof(v4);
  }
  v5 = CBasePlayer__GetDescriptionFromItem(
         this->m_pPlayer,
         "ironsight_up",
         (char *)&gpGlobals->pStringBase[this->script]);
  if ( strlen(v5) )
  {
    v6 = CBasePlayer__GetDescriptionFromItem(
           this->m_pPlayer,
           "ironsight_up",
           (char *)&gpGlobals->pStringBase[this->script]);
    this->m_fIronSightsUp = atof(v6);
  }
  v7 = CBasePlayer__GetDescriptionFromItem(
         this->m_pPlayer,
         "ironsight_zoom",
         (char *)&gpGlobals->pStringBase[this->script]);
  if ( strlen(v7) )
  {
    v8 = CBasePlayer__GetDescriptionFromItem(
           this->m_pPlayer,
           "ironsight_zoom",
           (char *)&gpGlobals->pStringBase[this->script]);
    this->m_iIronSightsZoom = atoi(v8);
  }
  MESSAGE_BEGIN__ov4_2(1, gmsgIronSights, 0, this->m_pPlayer->pev);
  g_engfuncs.pfnWriteCoord(0.0);
  g_engfuncs.pfnWriteCoord(0.0);
  g_engfuncs.pfnWriteCoord(0.0);
  g_engfuncs.pfnWriteByte(0);
  g_engfuncs.pfnWriteByte(0);
  g_engfuncs.pfnMessageEnd();
  MESSAGE_BEGIN__ov4_2(1, gmsgCameraZoom, 0, this->m_pPlayer->pev);
  g_engfuncs.pfnWriteCoord(350.0);
  g_engfuncs.pfnWriteByte(0);
  g_engfuncs.pfnWriteByte(0);
  g_engfuncs.pfnMessageEnd();
  this->m_pPlayer->pev->vuser2.x = 90.0;
  CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 20, 1, 0);
  this->m_bIronSights = 0;
  this->m_flNextTertiaryAttack = gpGlobals->time + 0.3;
  this->m_flNextSecondaryAttack = this->m_flNextTertiaryAttack;
  this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  weaponanim = this->m_pPlayer->pev->weaponanim;
  v9 = ENT__ov1(this->pev);
  v10 = g_engfuncs.pfnGetModelPtr(v9);
  this->m_flTimeWeaponIdle = GetSequenceTime(v10, weaponanim) + gpGlobals->time;
}

void __thiscall CM16__Fidget(CM16 *this)
{
  int v1; // [esp+Ch] [ebp-48h]
  int v2; // [esp+Ch] [ebp-48h]

  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && this->m_flTimeWeaponIdle <= (double)gpGlobals->time
    && !this->m_iSprintState
    && !this->m_iSuicideState
    && g_engfuncs.pfnRandomLong(0, 599) == 50
    && !this->m_bIronSights )
  {
    if ( this->b_BurstMode )
    {
      v1 = g_engfuncs.pfnRandomLong(0, 2);
      if ( v1 )
      {
        if ( v1 == 1 )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 30, 1, 0);
        }
        else if ( v1 == 2 )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 31, 1, 0);
        }
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 29, 1, 0);
      }
    }
    else
    {
      v2 = g_engfuncs.pfnRandomLong(0, 2);
      if ( v2 )
      {
        if ( v2 == 1 )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 27, 1, 0);
        }
        else if ( v2 == 2 )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 28, 1, 0);
        }
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 26, 1, 0);
      }
    }
  }
}

void __thiscall CM16__TertiaryAttack(CM16 *this)
{
  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && this->m_flNextTertiaryAttack <= (double)gpGlobals->time
    && !this->m_iSprintState
    && !this->m_iSuicideState
    && (this->m_pPlayer->m_afButtonPressed & 0x40) != 0
    && (0.0 != g_engfuncs.pfnCVarGetFloat("ironsights_toggle") || !this->m_bIronSights) )
  {
    this->m_bIronSights = !this->m_bIronSights;
    if ( this->m_bIronSights )
      CM16__IronsightsTo((CM16 *)this);
    else
      CM16__IronsightsFrom((CM16 *)this);
  }
}

void __cdecl ammo_m16(entvars_s *pev)
{
  GetClassPtr_CM16Ammo_(pev);
}

CM16 *__cdecl GetClassPtr_CM16_(entvars_s *a)
{
  edict_s *v1; // eax
  edict_s *v2; // eax
  CM16 *v4; // [esp+Ch] [ebp-5Ch]
  CM16 *v5; // [esp+14h] [ebp-54h]
  entvars_s *pev; // [esp+58h] [ebp-10h]
  CM16 *aa; // [esp+70h] [ebp+8h]

  pev = a;
  if ( !a )
  {
    v1 = g_engfuncs.pfnCreateEntity();
    pev = VARS__ov1(v1);
  }
  v2 = ENT__ov1(pev);
  aa = (CM16 *)GET_PRIVATE(v2);
  if ( !aa )
  {
    v5 = (CM16 *)CBaseEntity__operator_new__ov2(0x1F4u, pev);
    if ( v5 )
      v4 = CM16__CM16(v5);
    else
      v4 = 0;
    aa = v4;
    v4->pev = pev;
  }
  return aa;
}

CM16Ammo *__cdecl GetClassPtr_CM16Ammo_(entvars_s *a)
{
  edict_s *v1; // eax
  edict_s *v2; // eax
  CM16Ammo *v4; // [esp+Ch] [ebp-5Ch]
  CM16Ammo *v5; // [esp+14h] [ebp-54h]
  entvars_s *pev; // [esp+58h] [ebp-10h]
  CM16Ammo *aa; // [esp+70h] [ebp+8h]

  pev = a;
  if ( !a )
  {
    v1 = g_engfuncs.pfnCreateEntity();
    pev = VARS__ov1(v1);
  }
  v2 = ENT__ov1(pev);
  aa = (CM16Ammo *)GET_PRIVATE(v2);
  if ( !aa )
  {
    v5 = (CM16Ammo *)CBaseEntity__operator_new__ov2(0xDCu, pev);
    if ( v5 )
      v4 = CM16Ammo__CM16Ammo(v5);
    else
      v4 = 0;
    aa = v4;
    v4->pev = pev;
  }
  return aa;
}

CM16 *__thiscall CM16__CM16(CM16 *this)
{
  CBasePlayerWeapon__CBasePlayerWeapon((CBasePlayerWeapon *)this);
  this->__vftable = (CBasePlayerWeapon_vtbl *)&CM16___vftable_;
  return this;
}

int __thiscall CM16__iItemSlot(CM16 *this)
{
  return 1;
}

CM16Ammo *__thiscall CM16Ammo__CM16Ammo(CM16Ammo *this)
{
  CBasePlayerAmmo__CBasePlayerAmmo((CBasePlayerAmmo *)this);
  this->__vftable = (CM16Ammo_vtbl *)&CM16Ammo___vftable_;
  return this;
}

void __thiscall CM16Ammo__Spawn(CM16Ammo *this)
{
  edict_s *v1; // eax

  CM16Ammo__Precache((CM16Ammo *)this);
  v1 = ENT__ov1(this->pev);
  g_engfuncs.pfnSetModel(v1, "models/ammo/ammo_m16.mdl");
  CBasePlayerAmmo__Spawn((CBasePlayerAmmo *)this);
}

void __thiscall CM16Ammo__Precache(CM16Ammo *this)
{
  PRECACHE_MODEL("models/ammo/ammo_m16.mdl");
  PRECACHE_SOUND("weapons/item_get.wav");
}

int __thiscall CM16Ammo__AddAmmo(CM16Ammo *this, CBaseEntity *pOther)
{
  edict_s *v2; // eax

  if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
  {
    if ( CBaseEntity__GiveAmmo((CBaseEntity *)pOther, 20, "m16", 60) != -1 )
    {
LABEL_4:
      v2 = ENT__ov1(this->pev);
      EMIT_SOUND(v2, 3, "weapons/item_get.wav", 1.0, 0.80000001);
      return 1;
    }
  }
  else if ( CBaseEntity__GiveAmmo((CBaseEntity *)pOther, 20, "m16", 200) != -1 )
  {
    goto LABEL_4;
  }
  return 0;
}

