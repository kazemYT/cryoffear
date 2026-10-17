/* CoF-SourceCode
 * source : .\CoF_Syringe.cpp
 * built  : 2012-03-21 21:35:13 UTC (PDB signature 1332365713, age 17)
 */
#include "cof_decls.h"

void __cdecl weapon_syringe(entvars_s *pev)
{
  GetClassPtr_CSyringe_(pev);
}

void __thiscall CSyringe__Spawn(CSyringe *this)
{
  edict_s *v1; // eax

  this->pev->classname = (int)("weapon_syringe" - gpGlobals->pStringBase);
  (*(void (__thiscall **)(CSyringe *))&this->gap0[48])(this);
  this->m_iId = 8;
  v1 = ENT__ov1(this->pev);
  g_engfuncs.pfnSetModel(v1, "models/weapons/syringe/w_syringe.mdl");
  if ( this->pev->frags <= 0.0 )
    this->m_iDefaultAmmo = 1;
  else
    this->m_iDefaultAmmo = (unsigned __int64)this->pev->frags;
  CBasePlayerItem__FallInit((CBasePlayerItem *)this);
  this->m_iSprintIdleAnim1 = 7;
  this->m_iSprintIdleAnim2 = 666;
  while ( !this->script )
    this->script = (int)("inventoryitems/weapons/weapon_syringe.txt" - gpGlobals->pStringBase);
  this->pev->renderfx = 99;
  this->strwmodel = (int)("models/weapons/syringe/w_syringe.mdl" - gpGlobals->pStringBase);
}

void __thiscall CSyringe__Precache(CSyringe *this)
{
  PRECACHE_MODEL("models/weapons/syringe/v_syringe.mdl");
  PRECACHE_MODEL("models/weapons/syringe/w_syringe.mdl");
  PRECACHE_MODEL("models/null.mdl");
  PRECACHE_SOUND("weapons/syringe/syringe_inject.wav");
  PRECACHE_SOUND("weapons/syringe/syringe_insert.wav");
  if ( g_pGameRules )
  {
    if ( g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
      PRECACHE_MODEL("police/models/weapons/syringe/p_syringe.mdl");
  }
}

int __thiscall CSyringe__GetItemInfo(CSyringe *this, ItemInfo *p)
{
  p->pszName = &gpGlobals->pStringBase[this->pev->classname];
  p->pszAmmo1 = "syringe";
  p->iMaxAmmo1 = 10;
  p->pszAmmo2 = 0;
  p->iMaxAmmo2 = -1;
  p->iMaxClip = -1;
  p->iSlot = 3;
  p->iPosition = 0;
  p->iId = 8;
  p->iWeight = 1;
  p->iFlags = 64;
  return 1;
}

int __thiscall CSyringe__Deploy(CSyringe *this)
{
  this->m_iSprintState = 0;
  if ( !this->m_pPlayer->m_bFirstDeploy[this->m_iId] )
  {
    this->m_pPlayer->m_bFirstDeploy[this->m_iId] = 1;
    UTIL_ProMessage(
      (CBaseEntity *)this->m_pPlayer,
      "Looks like morphine. This is strong stuff, so I'd better be careful with it.",
      5,
      0);
  }
  if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
    return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
             "models/weapons/syringe/v_syringe.mdl",
             "police/models/weapons/syringe/p_syringe.mdl",
             1,
             "crowbar",
             1,
             0);
  else
    return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
             "models/weapons/syringe/v_syringe.mdl",
             "models/null.mdl",
             1,
             "crowbar",
             1,
             0);
}

void __thiscall CSyringe__Holster(CSyringe *this)
{
  float v1; // [esp+Ch] [ebp-48h]

  v1 = gpGlobals->time + 0.5;
  this->m_pPlayer->m_flNextAttack = v1;
  CBaseEntity__ThinkSet((CBaseEntity *)this, 0, "NULL");
  CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 2, 1, 0);
}

void __thiscall CSyringe__Redeploy(CSyringe *this)
{
  CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 1, 1, 0);
  this->m_pPlayer->m_flNextAttack = gpGlobals->time + 1.0;
}

void __thiscall CSyringe__DestroyItem(CSyringe *this)
{
  if ( this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType] < 1 )
  {
    if ( this->m_pPlayer
      && this->m_pPlayer->m_pActiveItem
      && this->m_pPlayer->m_pActiveItem == this
      && this->m_pPlayer->m_pLastItem )
    {
      CBasePlayer__SelectLastItem(this->m_pPlayer, 1);
    }
    if ( this->m_pPlayer )
    {
      if ( !strcmp(this->m_pPlayer->m_sQuickSel1, &gpGlobals->pStringBase[this->pev->classname]) )
      {
        strcpy(this->m_pPlayer->m_sQuickSel1, byte_1019EB05);
        MESSAGE_BEGIN__ov4_2(1, gmsgQSlotClear, 0, this->m_pPlayer->pev);
        g_engfuncs.pfnWriteByte(1);
        g_engfuncs.pfnWriteByte(0);
        g_engfuncs.pfnMessageEnd();
        this->m_pPlayer->m_iQuickSlotSlot[1] = 0;
      }
      if ( !strcmp(this->m_pPlayer->m_sQuickSel2, &gpGlobals->pStringBase[this->pev->classname]) )
      {
        strcpy(this->m_pPlayer->m_sQuickSel2, byte_1019EB05);
        MESSAGE_BEGIN__ov4_2(1, gmsgQSlotClear, 0, this->m_pPlayer->pev);
        g_engfuncs.pfnWriteByte(2);
        g_engfuncs.pfnWriteByte(0);
        g_engfuncs.pfnMessageEnd();
        this->m_pPlayer->m_iQuickSlotSlot[2] = 0;
      }
      if ( !strcmp(this->m_pPlayer->m_sQuickSel3, &gpGlobals->pStringBase[this->pev->classname]) )
      {
        strcpy(this->m_pPlayer->m_sQuickSel3, byte_1019EB05);
        MESSAGE_BEGIN__ov4_2(1, gmsgQSlotClear, 0, this->m_pPlayer->pev);
        g_engfuncs.pfnWriteByte(3);
        g_engfuncs.pfnWriteByte(0);
        g_engfuncs.pfnMessageEnd();
        this->m_pPlayer->m_iQuickSlotSlot[3] = 0;
      }
      this->m_pPlayer->pev->weapons &= ~(1 << this->m_iId);
      CBasePlayer__HasItemInSlot(this->m_pPlayer, (char *)&gpGlobals->pStringBase[this->script], 1);
      (*(void (__thiscall **)(CBasePlayer *, CSyringe *))&this->m_pPlayer->gap0[144])(this->m_pPlayer, this);
    }
    CBasePlayerItem__Kill((CBasePlayerItem *)this);
  }
  else
  {
    CSyringe__Redeploy((CSyringe *)this);
  }
}

void __thiscall CSyringe__Inject(CSyringe *this)
{
  if ( g_pGameRules
    && !g_pGameRules->__vftable->IsMultiplayer(g_pGameRules)
    && this->m_pPlayer->m_fMorphineTripTime > (double)gpGlobals->time
    && !this->m_pPlayer->m_bIsTripping )
  {
    CBasePlayer__MorphineTrip(this->m_pPlayer);
  }
  ++this->m_pPlayer->playerstats.syringes_used;
  this->m_pPlayer->m_iMorphineRecover = (unsigned __int64)gSkillData.syringeHeal;
  CBasePlayer__MorphineSound(this->m_pPlayer);
  this->m_pPlayer->m_fMorphineTripTime = g_engfuncs.pfnCVarGetFloat("sv_morphinetriptime") + gpGlobals->time;
  if ( !this->m_pPlayer->m_bInfiniteAmmo )
    --this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType];
  if ( this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType] < 0 )
    this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType] = 0;
  if ( this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType] < 1 )
    CBaseEntity__ThinkSet((CBaseEntity *)this, (void (__thiscall *)(CBaseEntity *))CSyringe__DestroyItem, "&CSyringe:: DestroyItem");
  else
    CBaseEntity__ThinkSet((CBaseEntity *)this, (void (__thiscall *)(CBaseEntity *))CSyringe__Redeploy, "&CSyringe:: Redeploy");
  (*(void (__thiscall **)(CSyringe *, int))&this->gap0[8])(this, 1069547520);
  this->b_HasUsed = 1;
}

void __thiscall CSyringe__BladeRetract(CSyringe *this)
{
  CBasePlayer__EnableControl(this->m_pPlayer, 1);
  CBasePlayer__ViewLock(this->m_pPlayer, 0, 0.0);
  if ( !this->m_pPlayer->m_bInfiniteAmmo )
  {
    CBaseEntity__ThinkSet((CBaseEntity *)this, (void (__thiscall *)(CBaseEntity *))CSyringe__DestroyItem, "&CSyringe:: DestroyItem");
    (*(void (__thiscall **)(CSyringe *, int))&this->gap0[8])(this, 1050253722);
  }
}

void __thiscall CSyringe__SecondaryAttack(CSyringe *this)
{
  Vector *v1; // eax
  Vector *v2; // eax
  edict_s *v3; // eax
  _DWORD *v4; // eax
  double SequenceTime; // st7
  const Vector *v6; // [esp-10h] [ebp-D4h]
  Vector *v7; // [esp-10h] [ebp-D4h]
  edict_s *v8; // [esp-8h] [ebp-CCh]
  int v9; // [esp-4h] [ebp-C8h]
  Vector v10; // [esp+Ch] [ebp-B8h] BYREF
  Vector result; // [esp+18h] [ebp-ACh] BYREF
  Vector v12; // [esp+24h] [ebp-A0h] BYREF
  Vector v13; // [esp+30h] [ebp-94h] BYREF
  int animDesired; // [esp+7Ch] [ebp-48h]
  CBasePlayer *pNerdToRevive; // [esp+80h] [ebp-44h]
  CBaseEntity *pEntity; // [esp+84h] [ebp-40h]
  TraceResult tr; // [esp+88h] [ebp-3Ch] BYREF
  CSyringe *thisa; // [esp+C0h] [ebp-4h]

  thisa = this;
  if ( this->m_flNextSecondaryAttack <= (double)gpGlobals->time && !thisa->m_iSprintState )
  {
    if ( g_pGameRules )
    {
      if ( g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
      {
        TraceResult__TraceResult__ov1(&tr);
        UTIL_MakeVectors(&thisa->m_pPlayer->pev->angles);
        UTIL_MakeVectors(&thisa->m_pPlayer->pev->v_angle);
        v8 = ENT__ov1(thisa->m_pPlayer->pev);
        v6 = Vector__operator_mul(&gpGlobals->v_forward, &result, 128.0);
        v1 = Vector__operator_plus(
               &thisa->m_pPlayer->pev->origin,
               &v10,
               &thisa->m_pPlayer->pev->view_ofs);
        v7 = Vector__operator_plus(v1, &v12, v6);
        v2 = Vector__operator_plus(
               &thisa->m_pPlayer->pev->origin,
               &v13,
               &thisa->m_pPlayer->pev->view_ofs);
        UTIL_TraceLine__ov5(v2, v7, dont_ignore_monsters, v8, &tr);
        if ( 1.0 != tr.flFraction )
        {
          if ( tr.pHit )
          {
            g_engfuncs.pfnAlertMessage(at_console, "Trace hit something\n");
            pEntity = 0;
            while ( 1 )
            {
              pEntity = UTIL_FindEntityInSphere(pEntity, &tr.vecEndPos, 64.0);
              if ( !pEntity )
                break;
              if ( CBaseEntity__IsPlayer((CBaseEntity *)pEntity) )
              {
                if ( !CBaseEntity__IsAlive((CBaseEntity *)pEntity) )
                {
                  pNerdToRevive = GetClassPtr_CBasePlayer_(pEntity->pev);
                  if ( pNerdToRevive )
                  {
                    if ( !pNerdToRevive->m_bCantBeRevived
                      && !EHANDLE__operator_int(&pNerdToRevive->pPlayerReviving)
                      && !pNerdToRevive->m_bCoopGameOver )
                    {
                      if ( !thisa->m_pPlayer->m_bInfiniteAmmo )
                        --thisa->m_pPlayer->m_rgAmmo[thisa->m_iPrimaryAmmoType];
                      if ( thisa->m_pPlayer->m_rgAmmo[thisa->m_iPrimaryAmmoType] < 0 )
                        thisa->m_pPlayer->m_rgAmmo[thisa->m_iPrimaryAmmoType] = 0;
                      if ( thisa->m_pPlayer->m_rgAmmo[thisa->m_iPrimaryAmmoType] < 1 )
                        CBaseEntity__ThinkSet(
                          (CBaseEntity *)thisa,
                          (void (__thiscall *)(CBaseEntity *))CSyringe__DestroyItem,
                          "&CSyringe:: DestroyItem");
                      else
                        CBaseEntity__ThinkSet(
                          (CBaseEntity *)thisa,
                          (void (__thiscall *)(CBaseEntity *))CSyringe__Redeploy,
                          "&CSyringe:: Redeploy");
                      (*(void (__thiscall **)(CSyringe *, int))&thisa->gap0[8])(thisa, 1069547520);
                      thisa->b_HasUsed = 1;
                      CBasePlayer__ToThirdPerson(thisa->m_pPlayer);
                      thisa->m_pPlayer->m_flReviveTime = gpGlobals->time;
                      if ( (thisa->m_pPlayer->pev->flags & 0x4000) != 0 )
                        animDesired = CBaseAnimating__LookupSequence((CBaseAnimating *)thisa->m_pPlayer, "crouch_cpr_up");
                      else
                        animDesired = CBaseAnimating__LookupSequence((CBaseAnimating *)thisa->m_pPlayer, "cpr_up");
                      if ( animDesired == -1 )
                        animDesired = 0;
                      if ( thisa->m_pPlayer->pev->sequence != animDesired
                        || !thisa->m_pPlayer->m_fSequenceLoops )
                      {
                        thisa->m_pPlayer->pev->frame = 0.0;
                      }
                      thisa->m_pPlayer->pev->gaitsequence = 0;
                      v9 = animDesired;
                      v3 = ENT__ov1(thisa->m_pPlayer->pev);
                      v4 = g_engfuncs.pfnGetModelPtr(v3);
                      SequenceTime = GetSequenceTime(v4, v9);
                      thisa->m_pPlayer->m_flSequenceOverrideTime = SequenceTime + gpGlobals->time;
                      thisa->m_pPlayer->pev->fuser3 = 4.0;
                      thisa->m_pPlayer->m_flGetupTime = thisa->m_pPlayer->m_flSequenceOverrideTime;
                      EHANDLE__operator_assign(&thisa->m_pPlayer->pPlayerToRevive, 0);
                      if ( thisa->m_pPlayer->pev->sequence != animDesired )
                      {
                        thisa->m_pPlayer->pev->sequence = animDesired;
                        thisa->m_pPlayer->pev->frame = 0.0;
                        CBaseAnimating__ResetSequenceInfo((CBaseAnimating *)thisa->m_pPlayer);
                      }
                      CBasePlayer__RevivePlayer(pNerdToRevive);
                      EHANDLE__operator_assign(&pNerdToRevive->pPlayerReviving, 0);
                      thisa->m_flNextSecondaryAttack = gpGlobals->time + 5.0;
                      thisa->m_flNextPrimaryAttack = thisa->m_flNextSecondaryAttack;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

void __thiscall CSyringe__PrimaryAttack(CSyringe *this)
{
  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time && !this->m_iSprintState )
  {
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 3, 1, 0);
    CBasePlayer__PlayerAnimation(this->m_pPlayer, "syringe_use", 0);
    (*(void (__thiscall **)(CSyringe *, int))&this->gap0[8])(this, 0x40000000);
    CBaseEntity__ThinkSet((CBaseEntity *)this, (void (__thiscall *)(CBaseEntity *))CSyringe__Inject, "Inject");
    this->m_flNextSecondaryAttack = gpGlobals->time + 5.0;
    this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  }
}

void __thiscall CSyringe__WeaponIdle(CSyringe *this)
{
  edict_s *v1; // eax
  _DWORD *v2; // eax
  int weaponanim; // [esp-4h] [ebp-54h]

  if ( UTIL_WeaponTimeBase() >= this->m_flTimeWeaponIdle
    && this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && !this->m_iSprintState )
  {
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 0, 1, 0);
    weaponanim = this->m_pPlayer->pev->weaponanim;
    v1 = ENT__ov1(this->pev);
    v2 = g_engfuncs.pfnGetModelPtr(v1);
    this->m_flTimeWeaponIdle = GetSequenceTime(v2, weaponanim) + gpGlobals->time;
  }
}

void __thiscall CSyringe__ItemPostFrame(CSyringe *this)
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
  int weaponanim; // [esp-4h] [ebp-60h]
  int v12; // [esp-4h] [ebp-60h]
  int v13; // [esp-4h] [ebp-60h]
  int v14; // [esp-4h] [ebp-60h]
  int v15; // [esp-4h] [ebp-60h]
  float v16; // [esp+4Ch] [ebp-10h]
  float time; // [esp+50h] [ebp-Ch]
  float timea; // [esp+50h] [ebp-Ch]
  float timeb; // [esp+50h] [ebp-Ch]
  float timec; // [esp+50h] [ebp-Ch]
  float timed; // [esp+50h] [ebp-Ch]
  float speed; // [esp+54h] [ebp-8h]

  speed = Vector__Length2D(&this->m_pPlayer->pev->velocity);
  if ( !this->m_fInReload && this->m_iSprintState != 2 && this->m_flNextPrimaryAttack < (double)gpGlobals->time )
  {
    if ( CBasePlayer__SufficientlyOffTheGround(this->m_pPlayer) )
    {
      if ( !this->m_iSprintState )
      {
        this->m_iSprintState = 5;
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 6, 1, 0);
        weaponanim = this->m_pPlayer->pev->weaponanim;
        v1 = ENT__ov1(this->pev);
        v2 = g_engfuncs.pfnGetModelPtr(v1);
        time = GetSequenceTime(v2, weaponanim);
        this->m_flNextPrimaryAttack = gpGlobals->time + time * 0.5;
        this->m_iNextSprintAnim = time + gpGlobals->time;
      }
    }
    else if ( this->m_iSprintState == 5 )
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 8, 1, 0);
      v12 = this->m_pPlayer->pev->weaponanim;
      v3 = ENT__ov1(this->pev);
      v4 = g_engfuncs.pfnGetModelPtr(v3);
      timea = GetSequenceTime(v4, v12);
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
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 6, 1, 0);
      v13 = this->m_pPlayer->pev->weaponanim;
      v5 = ENT__ov1(this->pev);
      v6 = g_engfuncs.pfnGetModelPtr(v5);
      timeb = GetSequenceTime(v6, v13);
      this->m_flNextPrimaryAttack = gpGlobals->time + timeb * 0.5;
      this->m_iNextSprintAnim = timeb + gpGlobals->time;
    }
    if ( (this->m_pPlayer->pev->flags & 0x40000) != 0
      && speed > 0.0
      && this->m_iSprintState != 5 )
    {
      v16 = Vector__Length2D(&this->m_pPlayer->pev->velocity);
      if ( this->m_iSprintState == 1 && this->m_iNextSprintAnim < (double)gpGlobals->time && v16 != 0.0 )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 7, 1, 0);
        v14 = this->m_pPlayer->pev->weaponanim;
        v7 = ENT__ov1(this->pev);
        v8 = g_engfuncs.pfnGetModelPtr(v7);
        timec = GetSequenceTime(v8, v14);
        this->m_iNextSprintAnim = timec + gpGlobals->time;
      }
    }
    if ( ((this->m_pPlayer->pev->flags & 0x40000) == 0 || speed <= 0.0)
      && this->m_iNextSprintAnim < (double)gpGlobals->time
      && this->m_iSprintState == 1 )
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 8, 1, 0);
      v15 = this->m_pPlayer->pev->weaponanim;
      v9 = ENT__ov1(this->pev);
      v10 = g_engfuncs.pfnGetModelPtr(v9);
      timed = GetSequenceTime(v10, v15);
      this->m_flNextPrimaryAttack = timed + gpGlobals->time;
      this->m_iSprintState = 0;
    }
  }
  CBasePlayerWeapon__ItemPostFrame((CBasePlayerWeapon *)this);
}

CSyringe *__cdecl GetClassPtr_CSyringe_(entvars_s *a)
{
  edict_s *v1; // eax
  edict_s *v2; // eax
  CSyringe *v4; // [esp+Ch] [ebp-5Ch]
  CSyringe *v5; // [esp+14h] [ebp-54h]
  entvars_s *pev; // [esp+58h] [ebp-10h]
  CSyringe *aa; // [esp+70h] [ebp+8h]

  pev = a;
  if ( !a )
  {
    v1 = g_engfuncs.pfnCreateEntity();
    pev = VARS__ov1(v1);
  }
  v2 = ENT__ov1(pev);
  aa = (CSyringe *)GET_PRIVATE(v2);
  if ( !aa )
  {
    v5 = (CSyringe *)CBaseEntity__operator_new__ov2(0x1ECu, pev);
    if ( v5 )
      v4 = CSyringe__CSyringe(v5);
    else
      v4 = 0;
    aa = v4;
    v4->pev = pev;
  }
  return aa;
}

CSyringe *__thiscall CSyringe__CSyringe(CSyringe *this)
{
  CBasePlayerWeapon__CBasePlayerWeapon((CBasePlayerWeapon *)this);
  this->__vftable = (CBasePlayerWeapon_vtbl *)&CSyringe___vftable_;
  return this;
}

int __thiscall CSyringe__ShouldWeaponIdle(CSyringe *this)
{
  return 1;
}

