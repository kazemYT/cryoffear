/* CoF-SourceCode -- reconstructed from hl12.pdb + hl12.c (Hex-Rays 9.2)
 * module : .\debughl\CoF_Glock.obj
 * source : .\CoF_Glock.cpp
 * built  : 2012-03-21 21:35:13 UTC (PDB signature 1332365713, age 17)
 * rule   : Class::member -> Class__member, `name' -> _name_ (see tools/rebuild_tree.py)
 */
#include "cof_decls.h"

void __cdecl weapon_beretta(entvars_s *pev)
{
  GetClassPtr_CGlock_(pev);
}

void __cdecl weapon_glock(entvars_s *pev)
{
  GetClassPtr_CGlock_(pev);
}

void __thiscall CGlock__StartSuicide(CGlock *this)
{
  const Vector *v1; // eax
  edict_s *v2; // eax
  edict_s *v3; // eax
  edict_s *v4; // eax
  int v5; // [esp+Ch] [ebp-54h]
  Vector v6; // [esp+10h] [ebp-50h] BYREF
  CGlock *thisa; // [esp+5Ch] [ebp-4h]

  thisa = this;
  (*(void (__thiscall **)(CGlock *, int))&this->gap0[8])(this, 1082130432);
  CBaseEntity__ThinkSet((CBaseEntity *)thisa, (void (__thiscall *)(CBaseEntity *))CGlock__SuicideShot, "&CGlock::SuicideShot");
  if ( thisa->m_iClip )
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 16, 1, 0);
  else
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 19, 1, 0);
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

void __thiscall CGlock__SuicideShot(CGlock *this)
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
    EMIT_SOUND_DYN(v1, 1, "weapons/glock/glock_fire.wav", 1.0, 0.80000001, 0, v2);
  }
  else
  {
    CBasePlayerWeapon__PlayEmptySound((CBasePlayerWeapon *)this);
    this->m_fEmptyClickTime = gpGlobals->time + 0.25;
    CGlock__StopSuicide((CGlock *)this);
  }
}

void __thiscall CGlock__StopSuicide(CGlock *this)
{
  const Vector *v1; // eax
  Vector v2; // [esp+Ch] [ebp-50h] BYREF
  CGlock *thisa; // [esp+58h] [ebp-4h]

  thisa = this;
  CBaseEntity__ThinkSet((CBaseEntity *)this, 0, "NULL");
  thisa->m_iSuicideButtonsPressed = 0;
  thisa->m_iSuicideState = 0;
  v1 = Vector__Vector__ov4(&v2, 128.0, 128.0, 128.0);
  UTIL_ScreenFade((CBaseEntity *)thisa->m_pPlayer, v1, 0.5, 0.0, 0xFFu, 0);
  if ( thisa->m_pPlayer->pev->fuser3 == 10.0 )
    thisa->m_pPlayer->pev->fuser3 = 0.0;
  if ( thisa->m_iClip )
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 6, 1, 0);
  else
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 7, 1, 0);
  thisa->m_pPlayer->m_flNextAttack = gpGlobals->time + 1.0;
  thisa->m_flTimeWeaponIdle = gpGlobals->time + 1.0;
  thisa->m_flNextSecondaryAttack = thisa->m_flTimeWeaponIdle;
  thisa->m_flNextPrimaryAttack = thisa->m_flNextSecondaryAttack;
}

void __thiscall CGlock__Spawn(CGlock *this)
{
  edict_s *v1; // eax

  this->pev->classname = (int)("weapon_glock" - gpGlobals->pStringBase);
  (*(void (__thiscall **)(CGlock *))&this->gap0[48])(this);
  v1 = ENT__ov1(this->pev);
  g_engfuncs.pfnSetModel(v1, "models/weapons/glock/w_glock.mdl");
  this->m_iId = 3;
  this->m_iSprintIdleAnim1 = 12;
  this->m_iSprintIdleAnim2 = 13;
  this->m_flKickPerShot = 1.25;
  if ( this->pev->frags <= 0.0 )
  {
    if ( this->pev->frags == -2.0 )
      this->m_iClip = -666;
    this->m_iDefaultAmmo = 15;
  }
  else
  {
    this->m_iDefaultAmmo = (unsigned __int64)this->pev->frags;
  }
  this->m_bCanDualWield = 1;
  while ( !this->script )
    this->script = (int)("inventoryitems/weapons/weapon_glock.txt" - gpGlobals->pStringBase);
  this->pev->renderfx = 99;
  this->m_bCanSuicide = 1;
  this->strwmodel = (int)("models/weapons/glock/w_glock.mdl" - gpGlobals->pStringBase);
  CBasePlayerItem__FallInit((CBasePlayerItem *)this);
}

void __thiscall CGlock__Precache(CGlock *this)
{
  PRECACHE_MODEL("models/weapons/glock/v_glock.mdl");
  PRECACHE_MODEL("models/weapons/glock/w_glock.mdl");
  PRECACHE_MODEL("models/null.mdl");
  if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
    PRECACHE_MODEL("police/models/weapons/glock/p_glock.mdl");
  this->m_iShell = PRECACHE_MODEL("models/shell.mdl");
  PRECACHE_MODEL("models/w_9mmclip.mdl");
  PRECACHE_SOUND("weapons/item_get.wav");
  PRECACHE_SOUND("weapons/glock/glock_switch.wav");
  PRECACHE_SOUND("weapons/glock/glock_magin.wav");
  PRECACHE_SOUND("weapons/glock/glock_magout.wav");
  PRECACHE_SOUND("weapons/glock/glock_magplace.wav");
  PRECACHE_SOUND("weapons/glock/glock_rackback.wav");
  PRECACHE_SOUND("weapons/glock/glock_slide.wav");
  PRECACHE_SOUND("weapons/rifle/rifle_insert.wav");
  PRECACHE_SOUND("weapons/glock/glock_fire.wav");
}

int __thiscall CGlock__GetItemInfo(CGlock *this, ItemInfo *p)
{
  p->pszName = &gpGlobals->pStringBase[this->pev->classname];
  p->pszAmmo1 = "glock";
  p->iMaxAmmo1 = 150;
  p->pszAmmo2 = 0;
  p->iMaxAmmo2 = -1;
  p->iMaxClip = 15;
  p->iSlot = 4;
  p->iPosition = 0;
  p->iFlags = 0;
  this->m_iId = 3;
  p->iId = 3;
  p->iWeight = 5;
  return 1;
}

int __thiscall CGlock__Deploy(CGlock *this)
{
  if ( this->m_bTaclight )
  {
    if ( (this->m_pPlayer->m_iFlashlightFlags & 4) != 0 )
      this->pev->body = 2;
    else
      this->pev->body = 1;
    CBasePlayerWeapon__SendWeaponBody((CBasePlayerWeapon *)this, this->m_pPlayer, this->pev->body);
  }
  if ( !this->m_bTaclight && this->pev->body )
  {
    this->pev->body = 0;
    CBasePlayerWeapon__SendWeaponBody((CBasePlayerWeapon *)this, this->m_pPlayer, this->pev->body);
  }
  this->m_iSprintState = 0;
  this->m_iSuicideState = this->m_iSuicideState == 666;
  if ( this->m_iClip == -666 )
    this->m_iClip = 0;
  if ( this->m_pPlayer->m_bFirstDeploy[this->m_iId] )
  {
    if ( this->m_iClip )
    {
      if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
        return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
                 "models/weapons/glock/v_glock.mdl",
                 "police/models/weapons/glock/p_glock.mdl",
                 6,
                 "onehanded",
                 0,
                 0);
      else
        return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
                 "models/weapons/glock/v_glock.mdl",
                 "models/null.mdl",
                 6,
                 "onehanded",
                 0,
                 0);
    }
    else if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
    {
      return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
               "models/weapons/glock/v_glock.mdl",
               "police/models/weapons/glock/p_glock.mdl",
               7,
               "onehanded",
               0,
               0);
    }
    else
    {
      return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
               "models/weapons/glock/v_glock.mdl",
               "models/null.mdl",
               7,
               "onehanded",
               0,
               0);
    }
  }
  else
  {
    this->m_pPlayer->m_bFirstDeploy[this->m_iId] = 1;
    CBasePlayer__ShowHint(this->m_pPlayer, (int)("ironsights" - gpGlobals->pStringBase), 0);
    if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
      return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
               "models/weapons/glock/v_glock.mdl",
               "police/models/weapons/glock/p_glock.mdl",
               29,
               "onehanded",
               0,
               0);
    else
      return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
               "models/weapons/glock/v_glock.mdl",
               "models/null.mdl",
               29,
               "onehanded",
               0,
               0);
  }
}

void __thiscall CGlock__Holster(CGlock *this)
{
  const Vector *v1; // eax
  float v2; // [esp+Ch] [ebp-54h]
  Vector v3; // [esp+10h] [ebp-50h] BYREF
  CGlock *thisa; // [esp+5Ch] [ebp-4h]

  thisa = this;
  if ( this->m_iClip )
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 8, 1, 0);
  else
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 9, 1, 0);
  if ( thisa->m_iSuicideState )
  {
    CBaseEntity__ThinkSet((CBaseEntity *)thisa, 0, "NULL");
    thisa->m_iSuicideButtonsPressed = 0;
    thisa->m_iSuicideState = 0;
    v1 = Vector__Vector__ov4(&v3, 128.0, 128.0, 128.0);
    UTIL_ScreenFade((CBaseEntity *)thisa->m_pPlayer, v1, 0.5, 0.0, 0xFFu, 0);
    if ( thisa->m_pPlayer->pev->fuser3 == 10.0 )
      thisa->m_pPlayer->pev->fuser3 = 0.0;
  }
  if ( (thisa->m_pPlayer->m_iFlashlightFlags & 4) != 0 )
    thisa->m_pPlayer->m_iFlashlightFlags &= ~4u;
  v2 = gpGlobals->time + 0.5;
  thisa->m_pPlayer->m_flNextAttack = v2;
}

void __thiscall CGlock__ToggleSwitch(CGlock *this)
{
  int v1; // edx

  if ( (this->m_pPlayer->m_iFlashlightFlags & 4) != 0 )
    v1 = this->m_pPlayer->m_iFlashlightFlags & 0xFFFFFFFB;
  else
    v1 = this->m_pPlayer->m_iFlashlightFlags | 4;
  this->m_pPlayer->m_iFlashlightFlags = v1;
}

void __thiscall CGlock__Fidget(CGlock *this)
{
  int v1; // [esp+Ch] [ebp-48h]

  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && this->m_flTimeWeaponIdle <= (double)gpGlobals->time
    && !this->m_iSprintState
    && !this->m_iSuicideState
    && !this->m_bIronSights
    && g_engfuncs.pfnRandomLong(0, 599) == 50 )
  {
    v1 = g_engfuncs.pfnRandomLong(0, 2);
    if ( v1 )
    {
      if ( v1 == 1 )
      {
        if ( this->m_iClip )
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 23, 1, 0);
        else
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 24, 1, 0);
      }
      else if ( v1 == 2 )
      {
        if ( this->m_iClip )
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 25, 1, 0);
        else
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 26, 1, 0);
      }
    }
    else if ( this->m_iClip )
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 21, 1, 0);
    }
    else
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 22, 1, 0);
    }
  }
}

void __thiscall CGlock__WeaponToggle(CGlock *this)
{
  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && this->m_bTaclight
    && !this->m_bIronSights
    && !this->m_iSprintState
    && !this->m_iSuicideState )
  {
    if ( this->m_iClip )
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 17, 1, 0);
    else
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 18, 1, 0);
    (*(void (__thiscall **)(CGlock *, int))&this->gap0[8])(this, 1050253722);
    CBaseEntity__ThinkSet((CBaseEntity *)this, (void (__thiscall *)(CBaseEntity *))CGlock__ToggleSwitch, "&CGlock::ToggleSwitch");
    this->m_flTimeWeaponIdle = gpGlobals->time + 0.66;
    this->m_flNextSecondaryAttack = this->m_flTimeWeaponIdle;
    this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  }
}

void __thiscall CGlock__SecondaryAttack(CGlock *this)
{
  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && !this->m_iSprintState
    && !this->m_iSuicideState
    && !this->m_bIronSights )
  {
    (*(void (__thiscall **)(CBasePlayer *, int))&this->m_pPlayer->gap0[8])(this->m_pPlayer, 1050253722);
    CBaseEntity__ThinkSet(
      (CBaseEntity *)this->m_pPlayer,
      (void (__thiscall *)(CBaseEntity *))CBasePlayer__WeaponMelee,
      "&CBasePlayer::WeaponMelee");
    CBasePlayer__PlayerAnimation(this->m_pPlayer, "pistol_melee", 0);
    if ( this->m_iClip )
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 27, 1, 0);
    else
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 28, 1, 0);
    this->m_flTimeWeaponIdle = gpGlobals->time + 1.0;
    this->m_flNextSecondaryAttack = this->m_flTimeWeaponIdle;
    this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  }
}

void __thiscall CGlock__PrimaryAttack(CGlock *this)
{
  int v1; // eax
  const Vector *v2; // eax
  float v3; // eax
  const edict_s *v4; // eax
  Vector *v5; // eax
  Vector *v6; // eax
  Vector *v7; // eax
  Vector *v8; // eax
  Vector *v9; // eax
  edict_s *v10; // eax
  Vector v11; // [esp-28h] [ebp-180h] BYREF
  Vector v12; // [esp-1Ch] [ebp-174h] BYREF
  Vector v13; // [esp-10h] [ebp-168h] BYREF
  int v14; // [esp-4h] [ebp-15Ch]
  const char *v15; // [esp+0h] [ebp-158h]
  int m_iId; // [esp+4h] [ebp-154h]
  float p; // [esp+8h] [ebp-150h]
  float v18; // [esp+Ch] [ebp-14Ch]
  int random_seed; // [esp+10h] [ebp-148h]
  float v20; // [esp+20h] [ebp-138h]
  Vector result; // [esp+24h] [ebp-134h] BYREF
  Vector v22; // [esp+30h] [ebp-128h] BYREF
  Vector v23; // [esp+48h] [ebp-110h] BYREF
  Vector v24; // [esp+54h] [ebp-104h] BYREF
  Vector v25; // [esp+60h] [ebp-F8h] BYREF
  Vector v26; // [esp+6Ch] [ebp-ECh] BYREF
  Vector v27; // [esp+78h] [ebp-E0h] BYREF
  Vector v28; // [esp+84h] [ebp-D4h] BYREF
  Vector v29; // [esp+90h] [ebp-C8h] BYREF
  Vector v30; // [esp+9Ch] [ebp-BCh] BYREF
  Vector v31; // [esp+A8h] [ebp-B0h] BYREF
  int pitch; // [esp+F4h] [ebp-64h]
  Vector vecShellOrigin; // [esp+F8h] [ebp-60h] BYREF
  Vector vecShellVelocity; // [esp+104h] [ebp-54h] BYREF
  float PlayerSpeed; // [esp+110h] [ebp-48h]
  Vector vecDir; // [esp+114h] [ebp-44h] BYREF
  Vector vecAiming; // [esp+120h] [ebp-38h] BYREF
  Vector vecSrc; // [esp+12Ch] [ebp-2Ch] BYREF
  Vector vecShellEnd; // [esp+138h] [ebp-20h] BYREF
  Vector vecShellSrc; // [esp+144h] [ebp-14h] BYREF
  int flags; // [esp+150h] [ebp-8h]
  CGlock *thisa; // [esp+154h] [ebp-4h]

  thisa = this;
  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && !thisa->m_iSprintState
    && !thisa->m_iSuicideState
    && (thisa->m_pPlayer->m_afButtonPressed & 1) != 0 )
  {
    if ( thisa->m_pPlayer->pev->waterlevel == 3 )
    {
      if ( thisa->m_bIronSights )
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 35, 1, 0);
      else
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 20, 1, 0);
      if ( thisa->m_fEmptyClickTime < (double)gpGlobals->time )
      {
        CBasePlayerWeapon__PlayEmptySound((CBasePlayerWeapon *)thisa);
        thisa->m_fEmptyClickTime = gpGlobals->time + 0.5;
      }
      thisa->m_flNextPrimaryAttack = gpGlobals->time + 0.5;
      thisa->m_flNextSecondaryAttack = gpGlobals->time + 0.5;
    }
    else if ( thisa->m_iClip > 0 )
    {
      MESSAGE_BEGIN__ov4_2(1, gmsgParticle, 0, thisa->m_pPlayer->pev);
      v1 = CBaseEntity__entindex((CBaseEntity *)thisa);
      g_engfuncs.pfnWriteShort(v1);
      g_engfuncs.pfnWriteString("aurora/gunsmoke.aur");
      g_engfuncs.pfnWriteByte(1);
      g_engfuncs.pfnWriteString("models/weapons/glock/v_glock.mdl");
      g_engfuncs.pfnWriteShort(0);
      g_engfuncs.pfnMessageEnd();
      if ( !thisa->m_pPlayer->m_bInfiniteAmmo )
        --thisa->m_iClip;
      flags = thisa->m_pPlayer->m_iViewValue != 1;
      UTIL_MakeVectors(&thisa->m_pPlayer->pev->v_angle);
      CBasePlayer__GetGunPosition((CBasePlayer *)thisa->m_pPlayer, &vecShellSrc);
      v2 = Vector__operator_mul(&gpGlobals->v_right, &result, 32.0);
      Vector__operator_plus(&vecShellSrc, &vecShellEnd, v2);
      random_seed = 0;
      v18 = 0.0;
      p = 0.0;
      m_iId = thisa->m_iId;
      v15 = 0;
      v14 = 0;
      LODWORD(v13.z) = (int)&vecShellEnd;
      HIWORD(v3) = HIWORD(thisa);
      LODWORD(v13.y) = (int)&thisa->m_pPlayer->pev->origin;
      v13.x = 0.0;
      LOWORD(v3) = m_usThirdFlash;
      v12.z = v3;
      v4 = ENT__ov1(thisa->m_pPlayer->pev);
      g_engfuncs.pfnPlaybackEvent(
        flags,
        v4,
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
      CBasePlayer__PlayerAnimation(thisa->m_pPlayer, "pistol_shoot", 0);
      CBasePlayer__SetAnimation(thisa->m_pPlayer, PLAYER_ATTACK1);
      thisa->m_pPlayer->pev->effects |= 2u;
      v5 = Vector__operator_plus(
             &thisa->m_pPlayer->pev->v_angle,
             &v22,
             &thisa->m_pPlayer->pev->punchangle);
      UTIL_MakeVectors(v5);
      CBasePlayer__GetGunPosition((CBasePlayer *)thisa->m_pPlayer, &vecSrc);
      CBasePlayer__GetAutoaimVector(thisa->m_pPlayer, &vecAiming, 0.17364818);
      Vector__Vector__ov1(&vecDir);
      PlayerSpeed = Vector__Length2D(&thisa->m_pPlayer->pev->velocity);
      thisa->m_flCurrentKick = thisa->m_flCurrentKick + thisa->m_flKickPerShot;
      thisa->m_flNextKickReductionTime = gpGlobals->time + 0.55;
      random_seed = thisa->m_pPlayer->random_seed;
      v18 = *(float *)&thisa->m_pPlayer->pev;
      LODWORD(p) = (unsigned __int64)gSkillData.DmgGlock;
      m_iId = 2;
      v15 = (const char *)3;
      v14 = 1174405120;
      Vector__Vector__ov2(&v13, &thisa->m_AccuracyVector);
      Vector__Vector__ov2(&v12, &vecAiming);
      Vector__Vector__ov2(&v11, &vecSrc);
      vecDir = *CBaseEntity__FireBulletsPlayer(
                  (CBaseEntity *)thisa->m_pPlayer,
                  &v23,
                  1u,
                  v11,
                  v12,
                  v13,
                  *(float *)&v14,
                  *(float *)&v15,
                  m_iId,
                  SLODWORD(p),
                  (entvars_s *)LODWORD(v18),
                  random_seed);
      thisa->m_flTimeWeaponIdle = gpGlobals->time + 1.0;
      random_seed = 1065353216;
      v18 = 1.0;
      v20 = (int)(*(float *)&(int){ (int)(g_engfuncs.pfnRandomLong(-2, 2)) });
      p = (float)SLODWORD(v20);
      CBasePlayer__ViewPunch(thisa->m_pPlayer, p, v18, *(float *)&random_seed);
      if ( g_pGameRules && !g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
      {
        random_seed = (int)Vector__operator_mul(&gpGlobals->v_forward, &v27, 40.0);
        v18 = (int)(*(float *)&(int){ (int)(&vecShellVelocity) });
        p = (int)(*(float *)&(int){ (int)(Vector__operator_mul(&gpGlobals->v_up, &v25, 200.0)) });
        m_iId = (int)&v26;
        v6 = Vector__operator_mul(&gpGlobals->v_right, &v24, 220.0);
        v7 = Vector__operator_plus(v6, (Vector *)m_iId, (const Vector *)LODWORD(p));
        Vector__operator_plus(v7, (Vector *)LODWORD(v18), (const Vector *)random_seed);
        random_seed = (int)Vector__operator_mul(&gpGlobals->v_right, &v31, 20.0);
        v18 = (int)(*(float *)&(int){ (int)(&vecShellOrigin) });
        p = (int)(*(float *)&(int){ (int)(Vector__operator_mul(&gpGlobals->v_forward, &v29, 80.0)) });
        m_iId = (int)&v30;
        v8 = Vector__operator_plus(&thisa->pev->origin, &v28, &thisa->pev->view_ofs);
        v9 = Vector__operator_plus(v8, (Vector *)m_iId, (const Vector *)LODWORD(p));
        Vector__operator_plus(v9, (Vector *)LODWORD(v18), (const Vector *)random_seed);
        EjectBrass(&vecShellOrigin, &vecShellVelocity, thisa->pev->angles.y, thisa->m_iShell, 1);
      }
      if ( (thisa->m_pPlayer->pev->flags & 0x4000) != 0 )
        UTIL_ScreenShake(&thisa->m_pPlayer->pev->origin, 2.0, 0.1, 0.1, 2.0);
      else
        UTIL_ScreenShake(&thisa->m_pPlayer->pev->origin, 5.0, 0.25, 0.15000001, 2.0);
      if ( thisa->m_bIronSights )
      {
        if ( thisa->m_iClip )
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 34, 1, 0);
        else
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 38, 1, 0);
      }
      else if ( thisa->m_iClip )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 2, 1, 0);
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 3, 1, 0);
      }
      CBasePlayer__ViewKnock(thisa->m_pPlayer, 3.0);
      pitch = g_engfuncs.pfnRandomLong(0, 10) + 95;
      random_seed = pitch;
      v18 = 0.0;
      p = 0.80000001;
      m_iId = 1065353216;
      v15 = "weapons/glock/glock_fire.wav";
      v14 = 1;
      v10 = ENT__ov1(thisa->m_pPlayer->pev);
      EMIT_SOUND_DYN(v10, v14, v15, *(float *)&m_iId, p, SLODWORD(v18), random_seed);
      thisa->m_pPlayer->m_iExtraSoundTypes = 1;
      v20 = gpGlobals->time + 0.2;
      thisa->m_pPlayer->m_flStopExtraSoundTime = v20;
      thisa->m_flNextPrimaryAttack = gpGlobals->time + 0.1;
      thisa->m_flNextSecondaryAttack = gpGlobals->time + 1.0;
      if ( thisa->m_iClip <= 0 )
        thisa->m_flNextPrimaryAttack = gpGlobals->time + 1.0;
    }
    else
    {
      if ( thisa->m_fFireOnEmpty )
      {
        if ( thisa->m_bIronSights )
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 35, 1, 0);
        else
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 20, 1, 0);
        if ( thisa->m_fEmptyClickTime < (double)gpGlobals->time )
        {
          CBasePlayerWeapon__PlayEmptySound((CBasePlayerWeapon *)thisa);
          thisa->m_fEmptyClickTime = gpGlobals->time + 0.5;
        }
      }
      else
      {
        CGlock__Reload((CGlock *)thisa);
      }
      thisa->m_flNextPrimaryAttack = gpGlobals->time + 0.5;
      thisa->m_flNextSecondaryAttack = gpGlobals->time + 0.5;
    }
  }
}

void __thiscall CGlock__Reload(CGlock *this)
{
  int v1; // [esp+Ch] [ebp-4Ch]

  if ( this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType] > 0
    && this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_iSprintState != 1
    && this->m_iSprintState <= 2
    && !this->m_iSuicideState
    && !this->m_bWaitingToReloadIronsights )
  {
    if ( this->m_bIronSights )
    {
      this->m_bWaitingToReloadIronsights = 1;
    }
    else
    {
      if ( 15 - this->m_iClip >= this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType] )
        v1 = this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType];
      else
        v1 = 15 - this->m_iClip;
      if ( v1 )
      {
        this->m_fReloadSpeed = 0.0;
        this->m_iSprintState = 2;
        if ( this->m_iClip )
        {
          this->m_iClip = 0;
          CBasePlayerWeapon__DefaultReload((CBasePlayerWeapon *)this, 15, 4, 2.5999999, 0, 0);
          CBasePlayer__PlayerAnimation(this->m_pPlayer, "pistol_reload", 0);
        }
        else
        {
          this->m_iClip = 0;
          CBasePlayerWeapon__DefaultReload((CBasePlayerWeapon *)this, 15, 5, 3.5, 0, 0);
          CBasePlayer__PlayerAnimation(this->m_pPlayer, "pistol_reloadempty", 0);
        }
      }
    }
  }
}

void __thiscall CGlock__WeaponIdle(CGlock *this)
{
  edict_s *v1; // eax
  _DWORD *v2; // eax
  double SequenceTime; // st7
  int weaponanim; // [esp-4h] [ebp-60h]
  Vector result; // [esp+Ch] [ebp-50h] BYREF
  CGlock *thisa; // [esp+58h] [ebp-4h]

  thisa = this;
  CBasePlayer__GetAutoaimVector(this->m_pPlayer, &result, 0.087155744);
  if ( thisa->m_flTimeWeaponIdle <= (double)gpGlobals->time && !thisa->m_iSprintState && !thisa->m_iSuicideState )
  {
    if ( thisa->m_bIronSights )
    {
      if ( thisa->m_iClip )
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 32, 1, 0);
      else
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 33, 1, 0);
    }
    else if ( thisa->m_iClip )
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 0, 1, 0);
    }
    else
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 1, 1, 0);
    }
    weaponanim = thisa->m_pPlayer->pev->weaponanim;
    v1 = ENT__ov1(thisa->pev);
    v2 = g_engfuncs.pfnGetModelPtr(v1);
    SequenceTime = GetSequenceTime(v2, weaponanim);
    thisa->m_flTimeWeaponIdle = SequenceTime + gpGlobals->time;
  }
}

void __thiscall CGlock__AttachTaclight(CGlock *this)
{
  edict_s *v1; // eax

  v1 = CBaseEntity__edict((CBaseEntity *)this);
  EMIT_SOUND_DYN(v1, 2, "weapons/sleeve_generic3.wav", 1.0, 0.80000001, 0, 100);
  this->m_bTaclight = 1;
  if ( (this->m_pPlayer->m_iFlashlightFlags & 4) != 0 )
    this->pev->body = 2;
  else
    this->pev->body = 1;
  CBasePlayerWeapon__SendWeaponBody((CBasePlayerWeapon *)this, this->m_pPlayer, this->pev->body);
  this->m_bWaitingToFix = 0;
  CBasePlayer__ShowHint(this->m_pPlayer, (int)("weaponfunctionglock" - gpGlobals->pStringBase), 0);
  if ( this->m_iClip )
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 6, 1, 0);
  else
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 7, 1, 0);
  this->m_pPlayer->m_flNextAttack = gpGlobals->time + 1.0;
  this->m_pPlayer->m_flNextAttack = gpGlobals->time + 1.0;
  this->m_flNextTertiaryAttack = this->m_pPlayer->m_flNextAttack;
  this->m_flNextSecondaryAttack = this->m_flNextTertiaryAttack;
  this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
}

void __thiscall CGlock__IronsightsTo(CGlock *this)
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
  if ( this->m_iClip )
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 30, 1, 0);
  else
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 31, 1, 0);
  this->m_bIronSights = 1;
  this->m_flNextTertiaryAttack = gpGlobals->time + 0.3;
  this->m_flNextSecondaryAttack = this->m_flNextTertiaryAttack;
  this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  weaponanim = this->m_pPlayer->pev->weaponanim;
  v9 = ENT__ov1(this->pev);
  v10 = g_engfuncs.pfnGetModelPtr(v9);
  this->m_flTimeWeaponIdle = GetSequenceTime(v10, weaponanim) + gpGlobals->time;
}

void __thiscall CGlock__IronsightsFrom(CGlock *this)
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
  if ( this->m_iClip )
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 36, 1, 0);
  else
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 37, 1, 0);
  this->m_bIronSights = 0;
  this->m_flNextTertiaryAttack = gpGlobals->time + 0.3;
  this->m_flNextSecondaryAttack = this->m_flNextTertiaryAttack;
  this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  weaponanim = this->m_pPlayer->pev->weaponanim;
  v9 = ENT__ov1(this->pev);
  v10 = g_engfuncs.pfnGetModelPtr(v9);
  this->m_flTimeWeaponIdle = GetSequenceTime(v10, weaponanim) + gpGlobals->time;
}

void __thiscall CGlock__TertiaryAttack(CGlock *this)
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
      CGlock__IronsightsTo((CGlock *)this);
    else
      CGlock__IronsightsFrom((CGlock *)this);
  }
}

void __thiscall CGlock__MidAttachTaclight(CGlock *this)
{
  edict_s *v1; // eax

  v1 = CBaseEntity__edict((CBaseEntity *)this);
  EMIT_SOUND_DYN(v1, 2, "weapons/rifle/rifle_insert.wav", 1.0, 0.80000001, 0, 100);
  (*(void (__thiscall **)(CGlock *, int))&this->gap0[8])(this, 1065353216);
  CBaseEntity__ThinkSet((CBaseEntity *)this, (void (__thiscall *)(CBaseEntity *))CGlock__AttachTaclight, "&CGlock::AttachTaclight");
  this->m_pPlayer->m_flNextAttack = gpGlobals->time + 5.0;
  this->m_flNextTertiaryAttack = this->m_pPlayer->m_flNextAttack;
  this->m_flNextSecondaryAttack = this->m_flNextTertiaryAttack;
  this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
}

void __thiscall CGlock__ItemPostFrame(CGlock *this)
{
  edict_s *v1; // eax
  const Vector *v2; // eax
  edict_s *v3; // eax
  edict_s *v4; // eax
  _DWORD *v5; // eax
  edict_s *v6; // eax
  _DWORD *v7; // eax
  edict_s *v8; // eax
  _DWORD *v9; // eax
  edict_s *v10; // eax
  _DWORD *v11; // eax
  edict_s *v12; // eax
  _DWORD *v13; // eax
  float amplitude; // [esp+20h] [ebp-84h]
  float frequency; // [esp+24h] [ebp-80h]
  int v16; // [esp+2Ch] [ebp-78h]
  int v17; // [esp+2Ch] [ebp-78h]
  int weaponanim; // [esp+2Ch] [ebp-78h]
  int v19; // [esp+2Ch] [ebp-78h]
  int v20; // [esp+2Ch] [ebp-78h]
  int v21; // [esp+2Ch] [ebp-78h]
  float v22; // [esp+40h] [ebp-64h]
  Vector v23; // [esp+44h] [ebp-60h] BYREF
  float v24; // [esp+90h] [ebp-14h]
  float time; // [esp+94h] [ebp-10h]
  float speed; // [esp+98h] [ebp-Ch]
  int pitch; // [esp+9Ch] [ebp-8h]
  CGlock *thisa; // [esp+A0h] [ebp-4h]

  thisa = this;
  if ( !this->m_iSprintState
    && !thisa->m_iSuicideState
    && thisa->m_flNextPrimaryAttack < (double)gpGlobals->time
    && thisa->m_flNextSecondaryAttack < (double)gpGlobals->time
    && thisa->m_flNextTertiaryAttack < (double)gpGlobals->time
    && 0.0 == g_engfuncs.pfnCVarGetFloat("ironsights_toggle")
    && thisa->m_bIronSights
    && ((thisa->m_pPlayer->m_afButtonReleased
       | thisa->m_pPlayer->m_afButtonPressed
       | thisa->m_pPlayer->pev->button)
      & 0x40) == 0 )
  {
    thisa->m_bIronSights = 0;
    CGlock__IronsightsFrom((CGlock *)thisa);
  }
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
      CGlock__IronsightsFrom((CGlock *)thisa);
    }
    else
    {
      thisa->m_bWaitingToReloadIronsights = 0;
      CGlock__Reload((CGlock *)thisa);
    }
  }
  if ( thisa->m_bTaclight )
  {
    if ( (thisa->m_pPlayer->m_iFlashlightFlags & 4) != 0 )
    {
      if ( thisa->pev->body != 2 )
        thisa->pev->body = 2;
    }
    else if ( thisa->pev->body != 1 )
    {
      thisa->pev->body = 1;
    }
    CBasePlayerWeapon__SendWeaponBody((CBasePlayerWeapon *)thisa, thisa->m_pPlayer, thisa->pev->body);
  }
  if ( !thisa->m_bTaclight && thisa->pev->body )
  {
    thisa->pev->body = 0;
    CBasePlayerWeapon__SendWeaponBody((CBasePlayerWeapon *)thisa, thisa->m_pPlayer, thisa->pev->body);
  }
  if ( thisa->m_bWaitingToFix
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
      CGlock__IronsightsFrom((CGlock *)thisa);
    }
    if ( thisa->m_iClip )
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 8, 1, 0);
    else
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 9, 1, 0);
    v22 = gpGlobals->time + 0.5;
    thisa->m_pPlayer->m_flNextAttack = v22;
    (*(void (__thiscall **)(CGlock *, int))&thisa->gap0[8])(thisa, 1065353216);
    CBaseEntity__ThinkSet(
      (CBaseEntity *)thisa,
      (void (__thiscall *)(CBaseEntity *))CGlock__MidAttachTaclight,
      "&CGlock::MidAttachTaclight");
    v1 = CBaseEntity__edict((CBaseEntity *)thisa);
    EMIT_SOUND_DYN(v1, 2, "weapons/sleeve_generic2.wav", 1.0, 0.80000001, 0, 100);
    thisa->m_pPlayer->m_flNextAttack = gpGlobals->time + 5.0;
    thisa->m_flNextTertiaryAttack = thisa->m_pPlayer->m_flNextAttack;
    thisa->m_flNextSecondaryAttack = thisa->m_flNextTertiaryAttack;
    thisa->m_flNextPrimaryAttack = thisa->m_flNextSecondaryAttack;
  }
  if ( thisa->m_iSprintState == 2 && !thisa->m_fInReload )
    thisa->m_iSprintState = 0;
  if ( thisa->m_iSuicideState == 2 )
  {
    v2 = Vector__Vector__ov4(&v23, 0.0, 0.0, 0.0);
    UTIL_ScreenFade((CBaseEntity *)thisa->m_pPlayer, v2, 0.5, 0.5, 0x80u, 0);
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
        v16 = pitch;
        v3 = ENT__ov1(thisa->m_pPlayer->pev);
        EMIT_SOUND_DYN(v3, 0, "weapons/mobile/punch_swing.wav", 1.0, 0.80000001, 0, v16);
      }
    }
    if ( thisa->m_iSuicideButtonsPressed >= thisa->m_iSuicideButtonsNeeded )
      CGlock__StopSuicide((CGlock *)thisa);
  }
  if ( thisa->m_iSuicideState == 1 )
  {
    if ( thisa->m_iSprintState && thisa->m_iNextSprintAnim < (double)gpGlobals->time )
    {
      thisa->m_flNextPrimaryAttack = gpGlobals->time + 0.33;
      thisa->m_flTimeWeaponIdle = gpGlobals->time + 0.35;
      thisa->m_iNextSprintAnim = gpGlobals->time + 0.33;
      thisa->m_iSprintState = 0;
      if ( thisa->m_iClip )
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 14, 1, 0);
      else
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 15, 1, 0);
    }
    else if ( thisa->m_iNextSprintAnim < (double)gpGlobals->time && !thisa->m_iSprintState )
    {
      thisa->m_iSuicideState = 2;
      CGlock__StartSuicide((CGlock *)thisa);
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
        if ( thisa->m_iClip )
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 41, 1, 0);
        else
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 42, 1, 0);
        weaponanim = thisa->m_pPlayer->pev->weaponanim;
        v6 = ENT__ov1(thisa->pev);
        v7 = g_engfuncs.pfnGetModelPtr(v6);
        time = GetSequenceTime(v7, weaponanim);
        thisa->m_flNextPrimaryAttack = time + gpGlobals->time;
        thisa->m_flTimeWeaponIdle = time + gpGlobals->time;
        thisa->m_iSprintState = 0;
      }
    }
    else if ( !thisa->m_iSprintState )
    {
      thisa->m_iSprintState = 5;
      if ( thisa->m_iClip )
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 39, 1, 0);
      else
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 40, 1, 0);
      v17 = thisa->m_pPlayer->pev->weaponanim;
      v4 = ENT__ov1(thisa->pev);
      v5 = g_engfuncs.pfnGetModelPtr(v4);
      time = GetSequenceTime(v5, v17);
      thisa->m_flNextPrimaryAttack = gpGlobals->time + time * 0.5;
      thisa->m_iNextSprintAnim = time + gpGlobals->time;
    }
    if ( speed > 0.0
      && (thisa->m_pPlayer->pev->flags & 0x40000) != 0
      && thisa->m_iSprintState != 5
      && thisa->m_iSprintState != 1 )
    {
      thisa->m_iSprintState = 1;
      if ( thisa->m_iClip )
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 10, 1, 0);
      else
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 11, 1, 0);
      v19 = thisa->m_pPlayer->pev->weaponanim;
      v8 = ENT__ov1(thisa->pev);
      v9 = g_engfuncs.pfnGetModelPtr(v8);
      time = GetSequenceTime(v9, v19);
      thisa->m_flNextPrimaryAttack = gpGlobals->time + time * 0.5;
      thisa->m_iNextSprintAnim = time + gpGlobals->time;
    }
    if ( (thisa->m_pPlayer->pev->flags & 0x40000) != 0
      && speed > 0.0
      && thisa->m_iSprintState != 5 )
    {
      v24 = Vector__Length2D(&thisa->m_pPlayer->pev->velocity);
      if ( thisa->m_iSprintState == 1 && thisa->m_iNextSprintAnim < (double)gpGlobals->time && v24 != 0.0 )
      {
        if ( thisa->m_iClip )
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 12, 1, 0);
        else
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 13, 1, 0);
        v20 = thisa->m_pPlayer->pev->weaponanim;
        v10 = ENT__ov1(thisa->pev);
        v11 = g_engfuncs.pfnGetModelPtr(v10);
        time = GetSequenceTime(v11, v20);
        thisa->m_iNextSprintAnim = time + gpGlobals->time;
      }
    }
    if ( ((thisa->m_pPlayer->pev->flags & 0x40000) == 0 || speed <= 0.0)
      && thisa->m_iNextSprintAnim < (double)gpGlobals->time
      && thisa->m_iSprintState == 1 )
    {
      if ( thisa->m_iClip )
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 14, 1, 0);
      else
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 15, 1, 0);
      v21 = thisa->m_pPlayer->pev->weaponanim;
      v12 = ENT__ov1(thisa->pev);
      v13 = g_engfuncs.pfnGetModelPtr(v12);
      time = GetSequenceTime(v13, v21);
      thisa->m_flNextPrimaryAttack = gpGlobals->time + 0.33;
      thisa->m_flTimeWeaponIdle = gpGlobals->time + 0.35;
      thisa->m_iSprintState = 0;
    }
  }
  CBasePlayerWeapon__ItemPostFrame((CBasePlayerWeapon *)thisa);
}

void __cdecl ammo_glock(entvars_s *pev)
{
  GetClassPtr_CGlockAmmo_(pev);
}

CGlock *__cdecl GetClassPtr_CGlock_(entvars_s *a)
{
  edict_s *v1; // eax
  edict_s *v2; // eax
  CGlock *v4; // [esp+Ch] [ebp-5Ch]
  CGlock *v5; // [esp+14h] [ebp-54h]
  entvars_s *pev; // [esp+58h] [ebp-10h]
  CGlock *aa; // [esp+70h] [ebp+8h]

  pev = a;
  if ( !a )
  {
    v1 = g_engfuncs.pfnCreateEntity();
    pev = VARS__ov1(v1);
  }
  v2 = ENT__ov1(pev);
  aa = (CGlock *)GET_PRIVATE(v2);
  if ( !aa )
  {
    v5 = (CGlock *)CBaseEntity__operator_new__ov2(0x1F4u, pev);
    if ( v5 )
      v4 = CGlock__CGlock(v5);
    else
      v4 = 0;
    aa = v4;
    v4->pev = pev;
  }
  return aa;
}

CGlockAmmo *__cdecl GetClassPtr_CGlockAmmo_(entvars_s *a)
{
  edict_s *v1; // eax
  edict_s *v2; // eax
  CGlockAmmo *v4; // [esp+Ch] [ebp-5Ch]
  CGlockAmmo *v5; // [esp+14h] [ebp-54h]
  entvars_s *pev; // [esp+58h] [ebp-10h]
  CGlockAmmo *aa; // [esp+70h] [ebp+8h]

  pev = a;
  if ( !a )
  {
    v1 = g_engfuncs.pfnCreateEntity();
    pev = VARS__ov1(v1);
  }
  v2 = ENT__ov1(pev);
  aa = (CGlockAmmo *)GET_PRIVATE(v2);
  if ( !aa )
  {
    v5 = (CGlockAmmo *)CBaseEntity__operator_new__ov2(0xDCu, pev);
    if ( v5 )
      v4 = CGlockAmmo__CGlockAmmo(v5);
    else
      v4 = 0;
    aa = v4;
    v4->pev = pev;
  }
  return aa;
}

CGlock *__thiscall CGlock__CGlock(CGlock *this)
{
  CBasePlayerWeapon__CBasePlayerWeapon((CBasePlayerWeapon *)this);
  this->__vftable = (CBasePlayerWeapon_vtbl *)&CGlock___vftable_;
  return this;
}

int __thiscall CGlock__iItemSlot(CGlock *this)
{
  return 1;
}

CGlockAmmo *__thiscall CGlockAmmo__CGlockAmmo(CGlockAmmo *this)
{
  CBasePlayerAmmo__CBasePlayerAmmo((CBasePlayerAmmo *)this);
  this->__vftable = (CGlockAmmo_vtbl *)&CGlockAmmo___vftable_;
  return this;
}

void __thiscall CGlockAmmo__Spawn(CGlockAmmo *this)
{
  edict_s *v1; // eax

  CGlockAmmo__Precache((CGlockAmmo *)this);
  v1 = ENT__ov1(this->pev);
  g_engfuncs.pfnSetModel(v1, "models/ammo/clip.mdl");
  CBasePlayerAmmo__Spawn((CBasePlayerAmmo *)this);
}

void __thiscall CGlockAmmo__Precache(CGlockAmmo *this)
{
  PRECACHE_MODEL("models/ammo/clip.mdl");
  PRECACHE_SOUND("weapons/item_get.wav");
}

int __thiscall CGlockAmmo__AddAmmo(CGlockAmmo *this, CBaseEntity *pOther)
{
  edict_s *v2; // eax

  if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
  {
    if ( CBaseEntity__GiveAmmo((CBaseEntity *)pOther, 15, "glock", 45) != -1 )
    {
LABEL_4:
      v2 = ENT__ov1(this->pev);
      EMIT_SOUND(v2, 3, "weapons/item_get.wav", 1.0, 0.80000001);
      return 1;
    }
  }
  else if ( CBaseEntity__GiveAmmo((CBaseEntity *)pOther, 15, "glock", 150) != -1 )
  {
    goto LABEL_4;
  }
  return 0;
}

