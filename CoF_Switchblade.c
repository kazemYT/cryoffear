/* CoF-SourceCode
 * source : .\CoF_Switchblade.cpp
 * built  : 2012-03-21 21:35:13 UTC (PDB signature 1332365713, age 17)
 */
#include "cof_decls.h"

void __cdecl weapon_knife(entvars_s *pev)
{
  GetClassPtr_CSwitchblade_(pev);
}

void __cdecl weapon_switchblade(entvars_s *pev)
{
  GetClassPtr_CSwitchblade_(pev);
}

void __thiscall CSwitchblade__Spawn(CSwitchblade *this)
{
  edict_s *v1; // eax

  this->pev->classname = (int)("weapon_switchblade" - gpGlobals->pStringBase);
  (*(void (__thiscall **)(CSwitchblade *))&this->gap0[48])(this);
  this->m_iId = 6;
  v1 = ENT__ov1(this->pev);
  g_engfuncs.pfnSetModel(v1, "models/weapons/switchblade/w_switchblade.mdl");
  this->m_iClip = -1;
  CBasePlayerItem__FallInit((CBasePlayerItem *)this);
  this->m_iSprintIdleAnim1 = 11;
  this->m_iSprintIdleAnim2 = 14;
  while ( !this->script )
    this->script = (int)("inventoryitems/weapons/weapon_switchblade.txt" - gpGlobals->pStringBase);
  this->pev->renderfx = 99;
  this->strwmodel = (int)("models/weapons/switchblade/w_switchblade.mdl" - gpGlobals->pStringBase);
}

void __thiscall CSwitchblade__Precache(CSwitchblade *this)
{
  PRECACHE_MODEL("models/weapons/switchblade/v_switchblade.mdl");
  PRECACHE_MODEL("models/weapons/switchblade/w_switchblade.mdl");
  PRECACHE_MODEL("models/null.mdl");
  PRECACHE_SOUND("weapons/switchblade/switchblade_hitwall1.wav");
  PRECACHE_SOUND("weapons/switchblade/switchblade_hitwall2.wav");
  PRECACHE_SOUND("weapons/switchblade/switchblade_hitbody1.wav");
  PRECACHE_SOUND("weapons/switchblade/switchblade_hitbody2.wav");
  PRECACHE_SOUND("weapons/switchblade/switchblade_swing.wav");
  PRECACHE_SOUND("weapons/switchblade/switchblade_draw.wav");
  PRECACHE_SOUND("weapons/switchblade/switchblade_draw2.wav");
  if ( g_pGameRules )
  {
    if ( g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
      PRECACHE_MODEL("police/models/weapons/switchblade/p_switchblade.mdl");
  }
}

int __thiscall CSwitchblade__GetItemInfo(CSwitchblade *this, ItemInfo *p)
{
  p->pszName = &gpGlobals->pStringBase[this->pev->classname];
  p->pszAmmo1 = 0;
  p->iMaxAmmo1 = -1;
  p->pszAmmo2 = 0;
  p->iMaxAmmo2 = -1;
  p->iMaxClip = -1;
  p->iSlot = 0;
  p->iPosition = 0;
  p->iId = 6;
  p->iWeight = 1;
  return 1;
}

int __thiscall CSwitchblade__Deploy(CSwitchblade *this)
{
  edict_s *v1; // eax
  edict_s *v3; // eax
  edict_s *v4; // eax
  edict_s *v5; // eax

  this->m_iSprintState = 0;
  if ( this->m_pPlayer->m_iSwitchbladeCuts >= 2 )
  {
    if ( this->m_pPlayer->m_iSwitchbladeCuts > 5 )
    {
      if ( this->m_pPlayer->m_iSwitchbladeCuts > 8 )
      {
        if ( this->m_iBloodAmount != 3 )
          this->m_iBloodAmount = 3;
      }
      else if ( this->m_iBloodAmount != 2 )
      {
        this->m_iBloodAmount = 2;
      }
    }
    else if ( this->m_iBloodAmount != 1 )
    {
      this->m_iBloodAmount = 1;
    }
  }
  else if ( this->m_iBloodAmount )
  {
    this->m_iBloodAmount = 0;
  }
  if ( this->pev->body != this->m_iBloodAmount )
  {
    this->pev->body = this->m_iBloodAmount;
    CBasePlayerWeapon__SendWeaponBody((CBasePlayerWeapon *)this, this->m_pPlayer, this->pev->body);
  }
  if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
  {
    if ( this->b_KnifeStance )
    {
      if ( this->pev->max_health != 1.0 )
      {
        v1 = ENT__ov1(this->m_pPlayer->pev);
        EMIT_SOUND(v1, 1, "weapons/switchblade/switchblade_draw2.wav", 1.0, 0.80000001);
      }
      return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
               "models/weapons/switchblade/v_switchblade.mdl",
               "police/models/weapons/switchblade/p_switchblade.mdl",
               6,
               "crowbar",
               0,
               0);
    }
    else
    {
      if ( this->pev->max_health != 1.0 )
      {
        v3 = ENT__ov1(this->m_pPlayer->pev);
        EMIT_SOUND(v3, 1, "weapons/switchblade/switchblade_draw.wav", 1.0, 0.80000001);
      }
      return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
               "models/weapons/switchblade/v_switchblade.mdl",
               "police/models/weapons/switchblade/p_switchblade.mdl",
               1,
               "crowbar",
               0,
               0);
    }
  }
  else if ( this->b_KnifeStance )
  {
    if ( this->pev->max_health != 1.0 )
    {
      v4 = ENT__ov1(this->m_pPlayer->pev);
      EMIT_SOUND(v4, 1, "weapons/switchblade/switchblade_draw2.wav", 1.0, 0.80000001);
    }
    return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
             "models/weapons/switchblade/v_switchblade.mdl",
             "models/null.mdl",
             6,
             "crowbar",
             0,
             0);
  }
  else
  {
    if ( this->pev->max_health != 1.0 )
    {
      v5 = ENT__ov1(this->m_pPlayer->pev);
      EMIT_SOUND(v5, 1, "weapons/switchblade/switchblade_draw.wav", 1.0, 0.80000001);
    }
    return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
             "models/weapons/switchblade/v_switchblade.mdl",
             "models/null.mdl",
             1,
             "crowbar",
             0,
             0);
  }
}

void __thiscall CSwitchblade__Holster(CSwitchblade *this)
{
  float v1; // [esp+Ch] [ebp-48h]

  if ( --this->m_pPlayer->m_iSwitchbladeCuts < 0 )
    this->m_pPlayer->m_iSwitchbladeCuts = 0;
  if ( this->b_KnifeStance )
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 7, 1, 0);
  else
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 2, 1, 0);
  v1 = gpGlobals->time + 0.5;
  this->m_pPlayer->m_flNextAttack = v1;
}

void __cdecl FindHullIntersectionSwitchblade(
        Vector *vecSrc,
        TraceResult *tr,
        float *mins,
        float *maxs,
        edict_s *pEntity)
{
  Vector *v5; // eax
  const Vector *v6; // eax
  Vector *v7; // eax
  Vector result; // [esp+Ch] [ebp-DCh] BYREF
  Vector v9; // [esp+18h] [ebp-D0h] BYREF
  Vector v10; // [esp+24h] [ebp-C4h] BYREF
  Vector v11; // [esp+30h] [ebp-B8h] BYREF
  float thisDistance; // [esp+7Ch] [ebp-6Ch]
  Vector vecEnd; // [esp+80h] [ebp-68h] BYREF
  Vector vecHullEnd; // [esp+8Ch] [ebp-5Ch] BYREF
  TraceResult tmpTrace; // [esp+98h] [ebp-50h] BYREF
  float *minmaxs[2]; // [esp+D0h] [ebp-18h]
  float distance; // [esp+D8h] [ebp-10h]
  int k; // [esp+DCh] [ebp-Ch]
  int j; // [esp+E0h] [ebp-8h]
  int i; // [esp+E4h] [ebp-4h]

  minmaxs[0] = mins;
  minmaxs[1] = maxs;
  TraceResult__TraceResult__ov1(&tmpTrace);
  Vector__Vector__ov2(&vecHullEnd, &tr->vecEndPos);
  Vector__Vector__ov1(&vecEnd);
  distance = 1000000.0;
  v5 = Vector__operator_minus__ov3(&vecHullEnd, &result, vecSrc);
  v6 = Vector__operator_mul(v5, &v9, 2.0);
  vecHullEnd = *Vector__operator_plus(vecSrc, &v10, v6);
  UTIL_TraceLine__ov5(vecSrc, &vecHullEnd, dont_ignore_monsters, pEntity, &tmpTrace);
  if ( tmpTrace.flFraction >= 1.0 )
  {
    for ( i = 0; i < 2; ++i )
    {
      for ( j = 0; j < 2; ++j )
      {
        for ( k = 0; k < 2; ++k )
        {
          vecEnd.x = vecHullEnd.x + *minmaxs[i];
          vecEnd.y = vecHullEnd.y + minmaxs[j][1];
          vecEnd.z = vecHullEnd.z + minmaxs[k][2];
          UTIL_TraceLine__ov5(vecSrc, &vecEnd, dont_ignore_monsters, pEntity, &tmpTrace);
          if ( tmpTrace.flFraction < 1.0 )
          {
            v7 = Vector__operator_minus__ov3(&tmpTrace.vecEndPos, &v11, vecSrc);
            thisDistance = Vector__Length(v7);
            if ( thisDistance < (double)distance )
            {
              qmemcpy(tr, &tmpTrace, sizeof(TraceResult));
              distance = thisDistance;
            }
          }
        }
      }
    }
  }
  else
  {
    qmemcpy(tr, &tmpTrace, sizeof(TraceResult));
  }
}

double __thiscall CSwitchblade__GetNextRageDecreaseTime(CSwitchblade *this)
{
  return 0.75;
}

void __thiscall CSwitchblade__RageReset(CSwitchblade *this)
{
  this->m_iRageNeeded = g_engfuncs.pfnRandomLong(4, 7);
}

void __thiscall CSwitchblade__RageAttack(CSwitchblade *this)
{
  CBaseEntity *v1; // [esp+Ch] [ebp-4Ch]
  int v2; // [esp+Ch] [ebp-4Ch]
  int v3; // [esp+Ch] [ebp-4Ch]
  int desangle; // [esp+50h] [ebp-8h]

  if ( EHANDLE__operator_int(&this->m_pPlayer->m_pLastAttackedEnemy) )
  {
    v1 = EHANDLE__operator_arrow(&this->m_pPlayer->m_pLastAttackedEnemy);
    if ( CBaseEntity__IsAlive((CBaseEntity *)v1) )
    {
      desangle = (unsigned __int64)(EHANDLE__operator_arrow(&this->m_pPlayer->m_pLastAttackedEnemy)->pev->angles.y + 180.0);
      if ( desangle > 360 )
        desangle -= 360;
      if ( desangle == 360 )
        desangle = 0;
      this->m_pPlayer->pev->angles.y = (float)desangle;
      this->m_pPlayer->pev->fixangle = 1;
    }
  }
  if ( this->b_KnifeStance )
  {
    v2 = g_engfuncs.pfnRandomLong(0, 2);
    if ( v2 )
    {
      if ( v2 == 1 )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 18, 1, 0);
      }
      else if ( v2 == 2 )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 19, 1, 0);
      }
    }
    else
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 8, 1, 0);
    }
    (*(void (__thiscall **)(CBasePlayer *, int))&this->m_pPlayer->gap0[8])(this->m_pPlayer, 1042536202);
    CBaseEntity__ThinkSet(
      (CBaseEntity *)this->m_pPlayer,
      (void (__thiscall *)(CBaseEntity *))CBasePlayer__MeleeHitThinkSwitchblade3,
      "CBasePlayer::MeleeHitThinkSwitchblade3");
    this->m_flNextPrimaryAttack = gpGlobals->time + 0.9;
  }
  else
  {
    v3 = g_engfuncs.pfnRandomLong(0, 2);
    if ( v3 )
    {
      if ( v3 == 1 || v3 == 2 )
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 16, 1, 0);
    }
    else
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 3, 1, 0);
    }
    (*(void (__thiscall **)(CBasePlayer *, int))&this->m_pPlayer->gap0[8])(this->m_pPlayer, 1042536202);
    CBaseEntity__ThinkSet(
      (CBaseEntity *)this->m_pPlayer,
      (void (__thiscall *)(CBaseEntity *))CBasePlayer__MeleeHitThinkSwitchblade3,
      "CBasePlayer::MeleeHitThinkSwitchblade3");
    this->m_flNextPrimaryAttack = gpGlobals->time + 0.5;
  }
}

void __thiscall CSwitchblade__Fidget(CSwitchblade *this)
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
    if ( this->b_KnifeStance )
    {
      v1 = g_engfuncs.pfnRandomLong(0, 2);
      if ( v1 )
      {
        if ( v1 == 1 )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 24, 1, 0);
        }
        else if ( v1 == 2 )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 25, 1, 0);
        }
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 23, 1, 0);
      }
    }
    else
    {
      v2 = g_engfuncs.pfnRandomLong(0, 2);
      if ( v2 )
      {
        if ( v2 == 1 )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 21, 1, 0);
        }
        else if ( v2 == 2 )
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 22, 1, 0);
        }
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 20, 1, 0);
      }
    }
  }
}

void __thiscall CSwitchblade__PrimaryAttack(CSwitchblade *this)
{
  edict_s *v1; // eax
  double v2; // st7
  int v3; // [esp+Ch] [ebp-48h]
  int v4; // [esp+Ch] [ebp-48h]

  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time && !this->m_iSprintState )
  {
    if ( !this->b_KnifeStance )
    {
      v1 = ENT__ov1(this->m_pPlayer->pev);
      EMIT_SOUND(v1, 1, "weapons/switchblade/switchblade_swing.wav", 1.0, 0.80000001);
    }
    if ( this->b_KnifeStance )
    {
      v3 = g_engfuncs.pfnRandomLong(0, 2);
      if ( v3 )
      {
        if ( v3 == 1 || v3 == 2 )
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 18, 1, 0);
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 8, 1, 0);
      }
      (*(void (__thiscall **)(CBasePlayer *, int))&this->m_pPlayer->gap0[8])(this->m_pPlayer, 1042536202);
      CBaseEntity__ThinkSet(
        (CBaseEntity *)this->m_pPlayer,
        (void (__thiscall *)(CBaseEntity *))CBasePlayer__MeleeHitThinkSwitchblade2,
        "CBasePlayer::MeleeHitThinkSwitchblade2");
      this->m_flNextPrimaryAttack = gpGlobals->time + 0.9;
      CBasePlayer__PlayerAnimation(this->m_pPlayer, "switchblade_attack2", 0);
    }
    else
    {
      v4 = g_engfuncs.pfnRandomLong(0, 2);
      if ( v4 )
      {
        if ( v4 == 1 || v4 == 2 )
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 16, 1, 0);
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 3, 1, 0);
      }
      (*(void (__thiscall **)(CBasePlayer *, int))&this->m_pPlayer->gap0[8])(this->m_pPlayer, 1042536202);
      CBaseEntity__ThinkSet(
        (CBaseEntity *)this->m_pPlayer,
        (void (__thiscall *)(CBaseEntity *))CBasePlayer__MeleeHitThinkSwitchblade,
        "CBasePlayer::MeleeHitThinkSwitchblade");
      this->m_flNextPrimaryAttack = gpGlobals->time + 0.5;
      CBasePlayer__PlayerAnimation(this->m_pPlayer, "switchblade_attack1", 0);
    }
    if ( this->b_KnifeStance )
      v2 = gpGlobals->time + 1.2;
    else
      v2 = gpGlobals->time + 1.0;
    this->m_flNextSecondaryAttack = v2;
    this->m_flTimeWeaponIdle = this->m_flNextSecondaryAttack;
  }
}

void __thiscall CSwitchblade__BloodFingerprint(CSwitchblade *this)
{
  ;
}

void __thiscall CSwitchblade__SecondaryAttack(CSwitchblade *this)
{
  if ( this->b_KnifeStance )
  {
    this->b_KnifeStance = 0;
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 9, 1, 0);
  }
  else
  {
    this->b_KnifeStance = 1;
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 4, 1, 0);
  }
  this->m_flNextSecondaryAttack = gpGlobals->time + 1.5;
  this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  this->m_flTimeWeaponIdle = gpGlobals->time + 1.5;
}

void __thiscall CSwitchblade__WeaponIdle(CSwitchblade *this)
{
  double v1; // st7

  if ( UTIL_WeaponTimeBase() >= this->m_flTimeWeaponIdle
    && this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && !this->m_iSprintState )
  {
    if ( this->b_KnifeStance )
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 5, 1, 0);
    else
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 0, 1, 0);
    v1 = UTIL_WeaponTimeBase();
    this->m_flTimeWeaponIdle = v1 + 5.0;
  }
}

void __thiscall CSwitchblade__ItemPostFrame(CSwitchblade *this)
{
  edict_s *v1; // eax
  _DWORD *v2; // eax
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
  edict_s *v13; // eax
  _DWORD *v14; // eax
  edict_s *v15; // eax
  _DWORD *v16; // eax
  edict_s *v17; // eax
  _DWORD *v18; // eax
  float time; // [esp+4Ch] [ebp-Ch]
  float timea; // [esp+4Ch] [ebp-Ch]
  float timeb; // [esp+4Ch] [ebp-Ch]
  float timec; // [esp+4Ch] [ebp-Ch]
  float timed; // [esp+4Ch] [ebp-Ch]
  float speed; // [esp+50h] [ebp-8h]

  if ( this->m_iSprintState == 2 && !this->m_fInReload )
    this->m_iSprintState = 0;
  if ( this->m_pPlayer->m_iSwitchbladeCuts >= 2 )
  {
    if ( this->m_pPlayer->m_iSwitchbladeCuts > 5 )
    {
      if ( this->m_pPlayer->m_iSwitchbladeCuts > 8 )
      {
        if ( this->m_iBloodAmount != 3 )
          this->m_iBloodAmount = 3;
      }
      else if ( this->m_iBloodAmount != 2 )
      {
        this->m_iBloodAmount = 2;
      }
    }
    else if ( this->m_iBloodAmount != 1 )
    {
      this->m_iBloodAmount = 1;
    }
  }
  else if ( this->m_iBloodAmount )
  {
    this->m_iBloodAmount = 0;
  }
  if ( this->pev->body != this->m_iBloodAmount )
  {
    this->pev->body = this->m_iBloodAmount;
    CBasePlayerWeapon__SendWeaponBody((CBasePlayerWeapon *)this, this->m_pPlayer, this->pev->body);
  }
  speed = Vector__Length2D(&this->m_pPlayer->pev->velocity);
  if ( !this->m_fInReload && this->m_iSprintState != 2 && this->m_flNextPrimaryAttack < (double)gpGlobals->time )
  {
    if ( CBasePlayer__SufficientlyOffTheGround(this->m_pPlayer) )
    {
      if ( !this->m_iSprintState )
      {
        this->m_iSprintState = 5;
        if ( this->b_KnifeStance )
        {
          v1 = ENT__ov1(this->pev);
          v2 = g_engfuncs.pfnGetModelPtr(v1);
          time = GetSequenceTime(v2, 13);
        }
        else
        {
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 10, 1, 0);
          v3 = ENT__ov1(this->pev);
          v4 = g_engfuncs.pfnGetModelPtr(v3);
          time = GetSequenceTime(v4, 10);
        }
        this->m_flNextPrimaryAttack = gpGlobals->time + time * 0.5;
        this->m_iNextSprintAnim = time + gpGlobals->time;
      }
    }
    else if ( this->m_iSprintState == 5 )
    {
      if ( this->b_KnifeStance )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 15, 1, 0);
        v5 = ENT__ov1(this->pev);
        v6 = g_engfuncs.pfnGetModelPtr(v5);
        timea = GetSequenceTime(v6, 15);
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 12, 1, 0);
        v7 = ENT__ov1(this->pev);
        v8 = g_engfuncs.pfnGetModelPtr(v7);
        timea = GetSequenceTime(v8, 12);
      }
      this->m_flNextPrimaryAttack = timea + gpGlobals->time;
      this->m_flTimeWeaponIdle = timea + gpGlobals->time;
      this->m_iSprintState = 0;
    }
    if ( speed > 0.0
      && (this->m_pPlayer->pev->flags & 0x40000) != 0
      && this->m_iSprintState != 5
      && this->m_iSprintState != 1 )
    {
      this->m_iSprintState = 1;
      if ( this->b_KnifeStance )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 13, 1, 0);
        v9 = ENT__ov1(this->pev);
        v10 = g_engfuncs.pfnGetModelPtr(v9);
        timeb = GetSequenceTime(v10, 13);
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 10, 1, 0);
        v11 = ENT__ov1(this->pev);
        v12 = g_engfuncs.pfnGetModelPtr(v11);
        timeb = GetSequenceTime(v12, 10);
      }
      this->m_flNextPrimaryAttack = gpGlobals->time + timeb * 0.5;
      this->m_iNextSprintAnim = timeb + gpGlobals->time;
    }
    if ( (this->m_pPlayer->pev->flags & 0x40000) != 0
      && speed > 0.0
      && this->m_iSprintState == 1
      && this->m_iNextSprintAnim < (double)gpGlobals->time
      && speed != 0.0 )
    {
      if ( this->b_KnifeStance )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 14, 1, 0);
        v13 = ENT__ov1(this->pev);
        v14 = g_engfuncs.pfnGetModelPtr(v13);
        timec = GetSequenceTime(v14, 14);
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 11, 1, 0);
        v15 = ENT__ov1(this->pev);
        v16 = g_engfuncs.pfnGetModelPtr(v15);
        timec = GetSequenceTime(v16, 11);
      }
      this->m_iNextSprintAnim = timec + gpGlobals->time;
    }
    if ( ((this->m_pPlayer->pev->flags & 0x40000) == 0 || speed <= 0.0)
      && this->m_iNextSprintAnim < (double)gpGlobals->time
      && this->m_iSprintState == 1 )
    {
      if ( this->b_KnifeStance )
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 15, 1, 0);
      else
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 12, 1, 0);
      v17 = ENT__ov1(this->pev);
      v18 = g_engfuncs.pfnGetModelPtr(v17);
      timed = GetSequenceTime(v18, 11);
      this->m_flNextPrimaryAttack = timed + gpGlobals->time;
      this->m_flTimeWeaponIdle = timed + gpGlobals->time;
      this->m_iSprintState = 0;
    }
  }
  CBasePlayerWeapon__ItemPostFrame((CBasePlayerWeapon *)this);
}

CSwitchblade *__cdecl GetClassPtr_CSwitchblade_(entvars_s *a)
{
  edict_s *v1; // eax
  edict_s *v2; // eax
  CSwitchblade *v4; // [esp+Ch] [ebp-5Ch]
  CSwitchblade *v5; // [esp+14h] [ebp-54h]
  entvars_s *pev; // [esp+58h] [ebp-10h]
  CSwitchblade *aa; // [esp+70h] [ebp+8h]

  pev = a;
  if ( !a )
  {
    v1 = g_engfuncs.pfnCreateEntity();
    pev = VARS__ov1(v1);
  }
  v2 = ENT__ov1(pev);
  aa = (CSwitchblade *)GET_PRIVATE(v2);
  if ( !aa )
  {
    v5 = (CSwitchblade *)CBaseEntity__operator_new__ov2(0x1F8u, pev);
    if ( v5 )
      v4 = CSwitchblade__CSwitchblade(v5);
    else
      v4 = 0;
    aa = v4;
    v4->pev = pev;
  }
  return aa;
}

CSwitchblade *__thiscall CSwitchblade__CSwitchblade(CSwitchblade *this)
{
  CBasePlayerWeapon__CBasePlayerWeapon((CBasePlayerWeapon *)this);
  this->__vftable = (CBasePlayerWeapon_vtbl *)&CSwitchblade___vftable_;
  return this;
}

int __thiscall CSwitchblade__ShouldWeaponIdle(CSwitchblade *this)
{
  return 1;
}

