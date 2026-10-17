/* CoF-SourceCode
 * source : .\CoF_MonsterBaby.cpp
 * built  : 2012-03-21 21:35:13 UTC (PDB signature 1332365713, age 17)
 */
#include "cof_decls.h"

void __cdecl monster_baby(entvars_s *pev)
{
  GetClassPtr_CBaby_(pev);
}

int __thiscall CBaby__Classify(CBaby *this)
{
  if ( this->m_iClass )
    return this->m_iClass;
  else
    return 7;
}

void __thiscall CBaby__SetYawSpeed(CBaby *this)
{
  this->pev->yaw_speed = (float)120;
}

int __thiscall CBaby__TakeDamage(
        CBaby *this,
        entvars_s *pevInflictor,
        entvars_s *pevAttacker,
        float flDamage,
        int bitsDamageType)
{
  Vector *v5; // eax
  const Vector *v6; // eax
  const Vector *v7; // eax
  Vector *v8; // eax
  Vector result; // [esp+Ch] [ebp-90h] BYREF
  Vector v11; // [esp+18h] [ebp-84h] BYREF
  Vector v12; // [esp+24h] [ebp-78h] BYREF
  Vector v13; // [esp+30h] [ebp-6Ch] BYREF
  Vector v14; // [esp+3Ch] [ebp-60h] BYREF
  float flForce; // [esp+88h] [ebp-14h]
  Vector vecDir; // [esp+8Ch] [ebp-10h] BYREF
  CBaby *thisa; // [esp+98h] [ebp-4h]

  thisa = this;
  if ( bitsDamageType == 2 )
  {
    v5 = Vector__operator_plus(&pevInflictor->absmin, &result, &pevInflictor->absmax);
    v6 = Vector__operator_mul(v5, &v11, 0.5);
    Vector__operator_minus__ov3(&thisa->pev->origin, &vecDir, v6);
    vecDir = *Vector__Normalize(&vecDir, &v12);
    flForce = CBaseMonster__DamageForce((CBaseMonster *)thisa, flDamage);
    v7 = Vector__operator_mul(&vecDir, &v13, flForce);
    v8 = Vector__operator_plus(&thisa->pev->velocity, &v14, v7);
    thisa->pev->velocity = *v8;
    flDamage = flDamage * 0.3;
  }
  if ( (*(int (__thiscall **)(CBaby *))&thisa->gap0[188])(thisa) && !thisa->m_bWaitingToDie )
    CBaby__PainSound((CBaby *)thisa);
  return CBaseMonster__TakeDamage((CBaseMonster *)thisa, pevInflictor, pevAttacker, flDamage, bitsDamageType);
}

void __thiscall CBaby__PainSound(CBaby *this)
{
  edict_s *v1; // eax
  const char *v2; // [esp-14h] [ebp-68h]
  int pitch; // [esp+4Ch] [ebp-8h]

  pitch = g_engfuncs.pfnRandomLong(0, 9) + 95;
  if ( g_engfuncs.pfnRandomLong(0, 5) < 2 )
  {
    v2 = CBaby__pPainSounds[g_engfuncs.pfnRandomLong(0, 1)];
    v1 = ENT__ov1(this->pev);
    EMIT_SOUND_DYN(v1, 2, v2, 1.0, 0.80000001, 0, pitch);
  }
}

void __thiscall CBaby__AlertSound(CBaby *this)
{
  edict_s *v1; // eax
  const char *v2; // [esp-14h] [ebp-68h]
  int v3; // [esp-4h] [ebp-58h]

  v3 = g_engfuncs.pfnRandomLong(0, 9) + 95;
  v2 = CBaby__pAlertSounds[g_engfuncs.pfnRandomLong(0, 2)];
  v1 = ENT__ov1(this->pev);
  EMIT_SOUND_DYN(v1, 2, v2, 1.0, 0.80000001, 0, v3);
}

void __thiscall CBaby__DeathSound(CBaby *this)
{
  edict_s *v1; // eax
  const char *v2; // [esp-14h] [ebp-68h]
  int v3; // [esp-4h] [ebp-58h]

  if ( this->pev->body != 1 )
  {
    g_engfuncs.pfnRandomLong(0, 9);
    v3 = g_engfuncs.pfnRandomLong(-5, 5) + 100;
    v2 = CBaby__pDeathSounds[g_engfuncs.pfnRandomLong(0, 1)];
    v1 = ENT__ov1(this->pev);
    EMIT_SOUND_DYN(v1, 2, v2, 1.0, 0.80000001, 0, v3);
  }
}

void __thiscall CBaby__AttackSound(CBaby *this)
{
  edict_s *v1; // eax
  const char *v2; // [esp-14h] [ebp-64h]
  int v3; // [esp-4h] [ebp-54h]

  v3 = g_engfuncs.pfnRandomLong(-5, 5) + 100;
  v2 = CBaby__pAttackSounds[g_engfuncs.pfnRandomLong(0, 1)];
  v1 = ENT__ov1(this->pev);
  EMIT_SOUND_DYN(v1, 0, v2, 1.0, 0.80000001, 0, v3);
}

void __thiscall CBaby__HandleAnimEvent(CBaby *this, MonsterEvent_t *pEvent)
{
  Vector v2; // [esp-20h] [ebp-98h] BYREF
  int v3; // [esp-14h] [ebp-8Ch]
  float v4; // [esp-10h] [ebp-88h]
  Vector v5; // [esp-Ch] [ebp-84h] BYREF
  int event; // [esp+Ch] [ebp-6Ch]
  CBaseEntity *pEntity; // [esp+58h] [ebp-20h]
  Vector VecAng; // [esp+5Ch] [ebp-1Ch] BYREF
  Vector VecSrc; // [esp+68h] [ebp-10h] BYREF
  CBaby *thisa; // [esp+74h] [ebp-4h]

  thisa = this;
  event = pEvent->event;
  if ( event == 1 || event == 2 )
  {
    CBaby__AttackSound(thisa);
  }
  else if ( event == 3 )
  {
    thisa->pev->body = 1;
    thisa->pev->health = 0.0;
    CBaby__FakeDeath(thisa);
    CBaby__AttackSound(thisa);
    Vector__Vector__ov1(&VecSrc);
    Vector__Vector__ov1(&VecAng);
    CBaseAnimating__GetAttachment((CBaseAnimating *)thisa, 0, &VecSrc, &VecAng);
    Vector__Vector__ov2(&v5, &thisa->pev->velocity);
    v4 = 120.0;
    v3 = 247;
    Vector__Vector__ov2(&v2, &VecSrc);
    SpawnBlood(v2, v3, v4, v5);
    pEntity = 0;
    while ( 1 )
    {
      pEntity = UTIL_FindEntityInSphere(pEntity, &VecSrc, 40.0);
      if ( !pEntity )
        break;
      if ( CBaseEntity__IsPlayer((CBaseEntity *)pEntity) )
        CBaby__TakeDamage(
          (CBaby *)pEntity,
          thisa->pev,
          thisa->pev,
          LODWORD(gSkillData.babyDmg),
          0);
    }
  }
  else
  {
    CBaseMonster__HandleAnimEvent((CBaseMonster *)thisa, pEvent);
  }
}

void __thiscall CBaby__Spawn(CBaby *this)
{
  edict_s *v1; // eax
  edict_s *v2; // eax
  Vector *v3; // eax
  Vector *v4; // eax
  const char *v5; // [esp-4h] [ebp-78h]
  Vector *v6; // [esp-4h] [ebp-78h]
  Vector v7; // [esp+Ch] [ebp-68h] BYREF
  Vector v8; // [esp+18h] [ebp-5Ch] BYREF
  Vector v9; // [esp+24h] [ebp-50h] BYREF
  CBaby *thisa; // [esp+70h] [ebp-4h]

  thisa = this;
  (*(void (__thiscall **)(CBaby *))&this->gap0[48])(this);
  if ( thisa->pev->model )
  {
    v5 = &gpGlobals->pStringBase[thisa->pev->model];
    v1 = ENT__ov1(thisa->pev);
    g_engfuncs.pfnSetModel(v1, v5);
  }
  else
  {
    v2 = ENT__ov1(thisa->pev);
    g_engfuncs.pfnSetModel(v2, "models/baby.mdl");
  }
  v6 = Vector__Vector__ov4(&v7, 12.0, 12.0, 72.0);
  v3 = Vector__Vector__ov4(&v8, -12.0, -12.0, 0.0);
  UTIL_SetSize(thisa->pev, v3, v6);
  thisa->pev->solid = 3;
  thisa->pev->movetype = 4;
  thisa->m_bloodColor = 247;
  if ( thisa->pev->health == 0.0 )
    thisa->pev->health = gSkillData.babyHealth;
  v4 = Vector__Vector__ov4(&v9, 0.0, 0.0, 28.0);
  thisa->pev->view_ofs = *v4;
  thisa->m_flFieldOfView = 0.5;
  thisa->m_MonsterState = MONSTERSTATE_NONE;
  thisa->m_afCapability = 832;
  CBaseMonster__MonsterInit((CBaseMonster *)thisa);
}

void __thiscall CBaby__Precache(CBaby *this)
{
  unsigned int i; // [esp+4Ch] [ebp-8h]
  unsigned int ia; // [esp+4Ch] [ebp-8h]
  unsigned int ib; // [esp+4Ch] [ebp-8h]
  unsigned int ic; // [esp+4Ch] [ebp-8h]

  if ( this->pev->model )
    PRECACHE_MODEL((char *)&gpGlobals->pStringBase[this->pev->model]);
  else
    PRECACHE_MODEL("models/baby.mdl");
  for ( i = 0; i < 2; ++i )
    PRECACHE_SOUND((char *)CBaby__pAttackSounds[i]);
  for ( ia = 0; ia < 2; ++ia )
    PRECACHE_SOUND((char *)CBaby__pDeathSounds[ia]);
  for ( ib = 0; ib < 3; ++ib )
    PRECACHE_SOUND((char *)CBaby__pAlertSounds[ib]);
  for ( ic = 0; ic < 2; ++ic )
    PRECACHE_SOUND((char *)CBaby__pPainSounds[ic]);
}

int __thiscall CBaby__IgnoreConditions(CBaby *this)
{
  int iIgnore; // [esp+4Ch] [ebp-8h]

  iIgnore = CBaseMonster__IgnoreConditions((CBaseMonster *)this);
  if ( this->m_Activity == ACT_MELEE_ATTACK1 && this->m_flNextFlinch >= (double)gpGlobals->time )
    iIgnore |= 0x300u;
  if ( (this->m_Activity == ACT_SMALL_FLINCH || this->m_Activity == ACT_BIG_FLINCH)
    && this->m_flNextFlinch < (double)gpGlobals->time )
  {
    this->m_flNextFlinch = gpGlobals->time + 2.0;
  }
  return iIgnore;
}

void __thiscall CBaby__FakeDeath(CBaby *this)
{
  edict_s *v1; // eax
  CBaseEntity *pOwner; // [esp+4Ch] [ebp-10h]

  CBaseMonster__Stop((CBaseMonster *)this);
  CBaseMonster__Remember((CBaseMonster *)this, 128);
  v1 = ENT__ov1(this->pev);
  EMIT_SOUND(v1, 1, "common/null.wav", 1.0, 0.80000001);
  this->m_IdealMonsterState = MONSTERSTATE_DEAD;
  CBaseMonster__SetConditions((CBaseMonster *)this, 256);
  pOwner = CBaseEntity__Instance__ov1(this->pev->owner);
  if ( pOwner )
  {
    CBaseEntity__DeathNotice((CBaseEntity *)pOwner, this->pev);
  }
  else if ( (this->pev->flags & 0x20) != 0 )
  {
    CBaseEntity__TouchSet((CBaseEntity *)this, 0, "NULL");
    CBaseMonster__BecomeDead((CBaseMonster *)this);
  }
  if ( this->pev->health < -99.0 )
    this->pev->health = 0.0;
  this->m_IdealMonsterState = MONSTERSTATE_DEAD;
  (*(void (__thiscall **)(CBaby *, _DWORD))&this->gap0[8])(this, 0);
}

void __thiscall CBaby__Killed(CBaby *this, entvars_s *pevAttacker, int iGib)
{
  edict_s *v3; // eax
  edict_s *v4; // eax
  CBaseEntity *pOwner; // [esp+4Ch] [ebp-14h]
  CBaseEntity *pAttacker; // [esp+50h] [ebp-10h]

  if ( !CBaseMonster__HasMemory((CBaseMonster *)this, 128) || !CBaseMonster__ShouldGibMonster((CBaseMonster *)this, iGib) )
  {
    pAttacker = CBaseEntity__Instance__ov1_2(pevAttacker);
    if ( pAttacker && CBaseEntity__IsPlayer((CBaseEntity *)pAttacker) )
    {
      if ( (this->m_iLastDamageType & 0x4000000) != 0 )
        ++pAttacker[7].m_iLFlags;
      else
        ++pAttacker[7].m_iStyle;
    }
    CBaseMonster__Remember((CBaseMonster *)this, 128);
    v3 = ENT__ov1(this->pev);
    EMIT_SOUND(v3, 1, "common/null.wav", 1.0, 0.80000001);
    v4 = ENT__ov1(this->pev);
    EMIT_SOUND(v4, 2, "common/null.wav", 1.0, 0.80000001);
    this->m_IdealMonsterState = MONSTERSTATE_DEAD;
    CBaseMonster__SetConditions((CBaseMonster *)this, 256);
    pOwner = CBaseEntity__Instance__ov1(this->pev->owner);
    if ( pOwner )
      CBaseEntity__DeathNotice((CBaseEntity *)pOwner, this->pev);
    if ( !CBaseMonster__ShouldGibMonster((CBaseMonster *)this, iGib) )
    {
      if ( (this->pev->flags & 0x20) != 0 )
      {
        CBaseEntity__TouchSet((CBaseEntity *)this, 0, "NULL");
        CBaseMonster__BecomeDead((CBaseMonster *)this);
      }
      if ( this->pev->health < -99.0 )
        this->pev->health = 0.0;
      this->m_IdealMonsterState = MONSTERSTATE_DEAD;
    }
  }
}

CBaby *__cdecl GetClassPtr_CBaby_(entvars_s *a)
{
  edict_s *v1; // eax
  edict_s *v2; // eax
  CBaby *v4; // [esp+Ch] [ebp-5Ch]
  CBaby *v5; // [esp+14h] [ebp-54h]
  entvars_s *pev; // [esp+58h] [ebp-10h]
  CBaby *aa; // [esp+70h] [ebp+8h]

  pev = a;
  if ( !a )
  {
    v1 = g_engfuncs.pfnCreateEntity();
    pev = VARS__ov1(v1);
  }
  v2 = ENT__ov1(pev);
  aa = (CBaby *)GET_PRIVATE(v2);
  if ( !aa )
  {
    v5 = (CBaby *)CBaseEntity__operator_new__ov2(0x35Cu, pev);
    if ( v5 )
      v4 = CBaby__CBaby(v5);
    else
      v4 = 0;
    aa = v4;
    v4->pev = pev;
  }
  return aa;
}

CBaby *__thiscall CBaby__CBaby(CBaby *this)
{
  CBaseMonster__CBaseMonster((CBaseMonster *)this);
  this->__vftable = (CBaseMonster_vtbl *)&CBaby___vftable_;
  return this;
}

int __thiscall CBaby__CheckRangeAttack1(CBaby *this, float flDot, float flDist)
{
  return 0;
}

int __thiscall CBaby__CheckRangeAttack2(CBaby *this, float flDot, float flDist)
{
  return 0;
}

