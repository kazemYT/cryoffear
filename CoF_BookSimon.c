//----- (1007D560) --------------------------------------------------------
void __cdecl monster_booksimon(entvars_s *pev)
{
  GetClassPtr<CBookSimon>(pev);
}

//----- (1007D580) --------------------------------------------------------
int __thiscall CBookSimon::Save(CBookSimon *this, CSave *save)
{
  if ( !CBaseMonster::Save(this, save) )
    return 0;
  if ( this->pev->targetname )
    return CSave::WriteFields(
             save,
             &gpGlobals->pStringBase[this->pev->targetname],
             "CBookSimon",
             (const char *)this,
             CBookSimon::m_SaveData,
             7);
  return CSave::WriteFields(
           save,
           &gpGlobals->pStringBase[this->pev->classname],
           "CBookSimon",
           (const char *)this,
           CBookSimon::m_SaveData,
           7);
}

//----- (1007D620) --------------------------------------------------------
int __thiscall CBookSimon::Restore(CBookSimon *this, CRestore *restore)
{
  if ( CBaseMonster::Restore(this, restore) )
    return CRestore::ReadFields(restore, "CBookSimon", (char *)this, CBookSimon::m_SaveData, 7);
  else
    return 0;
}

//----- (1007D670) --------------------------------------------------------
BOOL __thiscall CBookSimon::CheckMeleeAttack1(CBookSimon *this, float flDot, float flDist)
{
  if ( this->pev->frags == 0.0 && this->m_iWeapon != 3 )
    return 0;
  return flDist <= 64.0
      && flDot >= 0.7
      && EHANDLE::operator int(&this->m_hEnemy)
      && (EHANDLE::operator->(&this->m_hEnemy)->pev->flags & 0x200) != 0;
}

//----- (1007D710) --------------------------------------------------------
BOOL __thiscall CBookSimon::CheckMeleeAttack2(CBookSimon *this, float flDot, float flDist)
{
  if ( this->pev->frags == 0.0 && this->m_iWeapon != 3 )
    return 0;
  return flDist <= 64.0
      && flDot >= 0.7
      && EHANDLE::operator int(&this->m_hEnemy)
      && (EHANDLE::operator->(&this->m_hEnemy)->pev->flags & 0x200) != 0;
}

//----- (1007D7B0) --------------------------------------------------------
int __thiscall CBookSimon::Classify(CBookSimon *this)
{
  if ( this->m_iClass )
    return this->m_iClass;
  else
    return 7;
}

//----- (1007D7F0) --------------------------------------------------------
void __thiscall CBookSimon::SetYawSpeed(CBookSimon *this)
{
  int ys; // [esp+4Ch] [ebp-8h]

  if ( this->pev->frags == 0.0 )
    ys = 120;
  else
    ys = 0;
  this->pev->yaw_speed = (float)ys;
}

//----- (1007D840) --------------------------------------------------------
void __thiscall CBookSimon::Spawn(CBookSimon *this)
{
  edict_s *v1; // eax
  edict_s *v2; // eax
  Vector *v3; // eax
  Vector *v4; // eax
  const Vector *v5; // eax
  const char *v6; // [esp-4h] [ebp-90h]
  Vector *v7; // [esp-4h] [ebp-90h]
  Vector v8; // [esp+10h] [ebp-7Ch] BYREF
  Vector v9; // [esp+1Ch] [ebp-70h] BYREF
  Vector v10; // [esp+28h] [ebp-64h] BYREF
  Vector v11; // [esp+34h] [ebp-58h] BYREF
  CBasePlayer *plr; // [esp+80h] [ebp-Ch]
  int i; // [esp+84h] [ebp-8h]
  CBookSimon *thisa; // [esp+88h] [ebp-4h]

  thisa = this;
  (*(void (__thiscall **)(CBookSimon *))&this->gap0[48])(this);
  if ( thisa->pev->model )
  {
    v6 = &gpGlobals->pStringBase[thisa->pev->model];
    v1 = ENT(thisa->pev);
    g_engfuncs.pfnSetModel(v1, v6);
  }
  else
  {
    v2 = ENT(thisa->pev);
    g_engfuncs.pfnSetModel(v2, "models/booksimon.mdl");
  }
  v7 = Vector::Vector(&v8, 12.0, 12.0, 72.0);
  v3 = Vector::Vector(&v9, -12.0, -12.0, 0.0);
  UTIL_SetSize(thisa->pev, v3, v7);
  thisa->pev->solid = 3;
  thisa->pev->movetype = 4;
  thisa->m_bloodColor = 247;
  if ( thisa->pev->health == 0.0 )
    thisa->pev->health = 100.0;
  v4 = Vector::Vector(&v10, 0.0, 0.0, 28.0);
  thisa->pev->view_ofs = *v4;
  thisa->m_flFieldOfView = 0.5;
  thisa->m_MonsterState = MONSTERSTATE_NONE;
  thisa->m_afCapability = 832;
  if ( thisa->pev->frags == 0.0 )
  {
    m_bHadSimonMode = 1;
    m_iSimonMode = 1;
    for ( i = 1; i <= gpGlobals->maxClients; ++i )
    {
      plr = (CBasePlayer *)UTIL_PlayerByIndex(i);
      if ( plr )
      {
        v5 = Vector::Vector(&v11, 0.0, 0.0, 0.0);
        UTIL_ScreenFade(plr, v5, 2.0, 0.0, 0xFFu, 0);
        MESSAGE_BEGIN(1, gmsgGreyFade, 0, plr->pev);
        g_engfuncs.pfnWriteByte(0);
        g_engfuncs.pfnWriteByte(0);
        g_engfuncs.pfnMessageEnd();
        CBasePlayer::PlayerSetMP3(plr, "fucked.mp3" - gpGlobals->pStringBase, 1, 1.0);
      }
    }
  }
  thisa->m_iDamageNeeded = 60;
  thisa->m_iWeapon = thisa->pev->iuser4;
  if ( thisa->pev->frags == 0.0 )
  {
    thisa->m_iWeapon = 0;
    CBaseAnimating::SetBodygroup(thisa, 2, 0);
    switch ( thisa->m_iWeapon )
    {
      case 0:
$L49364:
        CBaseAnimating::SetBodygroup(thisa, 0, 1);
        CBaseAnimating::SetBodygroup(thisa, 1, 0);
        thisa->m_iBulletsLoaded = 5;
        break;
      case 1:
$L49366:
        CBaseAnimating::SetBodygroup(thisa, 0, 3);
        CBaseAnimating::SetBodygroup(thisa, 1, 0);
        thisa->m_iBulletsLoaded = 15;
        break;
      case 2:
$L49365:
        CBaseAnimating::SetBodygroup(thisa, 0, 2);
        CBaseAnimating::SetBodygroup(thisa, 1, 1);
        thisa->m_iBulletsLoaded = 30;
        break;
      case 3:
$L49367_0:
        CBaseAnimating::SetBodygroup(thisa, 0, 4);
        CBaseAnimating::SetBodygroup(thisa, 1, 0);
        thisa->m_iBulletsLoaded = -1;
        break;
      default:
        break;
    }
  }
  else
  {
    if ( !thisa->pev->iuser2 )
      thisa->pev->iuser2 = 50;
    CBaseAnimating::SetBodygroup(thisa, 2, 0);
    switch ( thisa->m_iWeapon )
    {
      case 0:
        goto $L49364;
      case 1:
        goto $L49366;
      case 2:
        goto $L49365;
      case 3:
        goto $L49367_0;
      default:
        break;
    }
  }
  thisa->MonsterInit(thisa);
  if ( thisa->pev->frags == 0.0 )
    thisa->m_iDamageNeeded = 300;
  thisa->pev->health = (float)thisa->m_iDamageNeeded;
  thisa->pev->max_health = (float)thisa->m_iDamageNeeded;
  if ( thisa->pev->frags != 0.0 && !thisa->m_iAimState )
    thisa->pev->effects |= 0x80u;
}

//----- (1007DD60) --------------------------------------------------------
void __thiscall CBookSimon::SetActivity(CBookSimon *this, Activity NewActivity)
{
  entvars_s *v2; // esi
  entvars_s *v3; // esi
  entvars_s *pev; // esi
  entvars_s *v5; // esi
  entvars_s *v6; // esi
  entvars_s *v7; // esi
  int m_iWeapon; // [esp+Ch] [ebp-4Ch]
  int iSequence; // [esp+50h] [ebp-8h]

  if ( this->pev->frags != 0.0 )
    return;
  if ( NewActivity == ACT_IDLE )
  {
    if ( this->pev->frags == 0.0 )
    {
      iSequence = CBaseAnimating::LookupActivity(this, 1);
    }
    else
    {
      iSequence = CBaseAnimating::LookupActivity(this, 30);
      if ( this->pev->frags != 0.0 && this->m_iAimState == 2 && this->m_iDamageToHide < this->m_iDamageNeeded )
      {
        m_iWeapon = this->m_iWeapon;
        if ( m_iWeapon )
        {
          if ( m_iWeapon == 1 )
          {
            pev = this->pev;
            if ( pev->sequence == CBaseAnimating::LookupSequence(this, "glock_appear")
              || (v5 = this->pev, v5->sequence == CBaseAnimating::LookupSequence(this, "glock_idle")) )
            {
              if ( this->m_flSequenceTimeOverride < (double)gpGlobals->time )
              {
                CBaseMonster::SetSequenceByName(this, "glock_idle");
                return;
              }
            }
          }
          else if ( m_iWeapon == 2 )
          {
            v6 = this->pev;
            if ( v6->sequence == CBaseAnimating::LookupSequence(this, "tmp_appear")
              || (v7 = this->pev, v7->sequence == CBaseAnimating::LookupSequence(this, "tmp_idle")) )
            {
              if ( this->m_flSequenceTimeOverride < (double)gpGlobals->time )
              {
                CBaseMonster::SetSequenceByName(this, "tmp_idle");
                return;
              }
            }
          }
        }
        else
        {
          v2 = this->pev;
          if ( v2->sequence == CBaseAnimating::LookupSequence(this, "shotgun_appear")
            || (v3 = this->pev, v3->sequence == CBaseAnimating::LookupSequence(this, "shotgun_idle")) )
          {
            if ( this->m_flSequenceTimeOverride < (double)gpGlobals->time )
            {
              CBaseMonster::SetSequenceByName(this, "shotgun_idle");
              return;
            }
          }
        }
      }
    }
    goto LABEL_35;
  }
  if ( NewActivity == ACT_WALK )
  {
    if ( this->pev->frags == 0.0 )
    {
      iSequence = CBaseAnimating::LookupActivity(this, 3);
      goto LABEL_35;
    }
LABEL_7:
    iSequence = CBaseAnimating::LookupActivity(this, 48);
    goto LABEL_35;
  }
  if ( NewActivity != ACT_RUN )
  {
    iSequence = CBaseAnimating::LookupActivity(this, NewActivity);
    goto LABEL_35;
  }
  if ( this->pev->frags != 0.0 )
    goto LABEL_7;
  iSequence = CBaseAnimating::LookupActivity(this, 4);
LABEL_35:
  this->m_Activity = NewActivity;
  if ( iSequence <= -1 )
  {
    g_engfuncs.pfnAlertMessage(
      at_console,
      "%s has no sequence for act:%d\n",
      &gpGlobals->pStringBase[this->pev->classname],
      NewActivity);
    this->pev->sequence = 0;
  }
  else
  {
    if ( this->pev->sequence != iSequence || !this->m_fSequenceLoops )
      this->pev->frame = 0.0;
    this->pev->sequence = iSequence;
    CBaseAnimating::ResetSequenceInfo(this);
    this->SetYawSpeed(this);
  }
}

//----- (1007E0C0) --------------------------------------------------------
void __thiscall CBookSimon::Precache(CBookSimon *this)
{
  if ( this->pev->model )
    PRECACHE_MODEL((char *)&gpGlobals->pStringBase[this->pev->model]);
  else
    PRECACHE_MODEL("models/booksimon.mdl");
  PRECACHE_MODEL("sprites/muzzleflash.spr");
}

//----- (1007E120) --------------------------------------------------------
void __thiscall CBookSimon::RealKilled(CBookSimon *this)
{
  edict_s *v1; // eax
  CBaseEntity *pOwner; // [esp+4Ch] [ebp-1Ch]
  char *m_pMusicManager; // [esp+50h] [ebp-18h]
  CBasePlayer *plr; // [esp+54h] [ebp-14h]
  int i; // [esp+58h] [ebp-10h]

  for ( i = 1; i <= gpGlobals->maxClients; ++i )
  {
    plr = (CBasePlayer *)UTIL_PlayerByIndex(i);
    if ( plr )
    {
      m_pMusicManager = (char *)g_engfuncs.pfnCVarGetString("sv_coop_music");
      if ( m_pMusicManager )
      {
        if ( strlen(m_pMusicManager) > 1 )
          CBasePlayer::PlayerSetMP3(
            plr,
            m_pMusicManager - gpGlobals->pStringBase,
            m_iMusicManagerLoops,
            m_fMusicManagerFadeTime);
      }
    }
  }
  CBaseMonster::Remember(this, 128);
  v1 = ENT(this->pev);
  EMIT_SOUND(v1, 1, "common/null.wav", 1.0, 0.80000001);
  this->m_IdealMonsterState = MONSTERSTATE_DEAD;
  CBaseMonster::SetConditions(this, 256);
  pOwner = CBaseEntity::Instance(this->pev->owner);
  if ( pOwner )
    pOwner->DeathNotice(pOwner, this->pev);
  if ( (this->pev->flags & 0x20) != 0 )
  {
    CBaseEntity::TouchSet(this, 0, "NULL");
    this->BecomeDead(this);
  }
  if ( this->pev->health < -99.0 )
    this->pev->health = 0.0;
  this->m_IdealMonsterState = MONSTERSTATE_DEAD;
  UTIL_Remove(this);
}

//----- (1007E2C0) --------------------------------------------------------
void __thiscall CBookSimon::Killed(CBookSimon *this, entvars_s *pevAttacker, int iGib)
{
  const Vector *v3; // eax
  Vector v4; // [esp+Ch] [ebp-58h] BYREF
  CBasePlayer *plr; // [esp+58h] [ebp-Ch]
  int i; // [esp+5Ch] [ebp-8h]
  CBookSimon *thisa; // [esp+60h] [ebp-4h]

  thisa = this;
  if ( !this->pev->iuser1 )
  {
    if ( thisa->pev->frags == 0.0 )
    {
      thisa->pev->iuser1 = 1;
      m_iSimonMode = 0;
      for ( i = 1; i <= gpGlobals->maxClients; ++i )
      {
        plr = (CBasePlayer *)UTIL_PlayerByIndex(i);
        if ( plr )
        {
          v3 = Vector::Vector(&v4, 0.0, 0.0, 0.0);
          UTIL_ScreenFade(plr, v3, 2.0, 0.5, 0xFFu, 0);
          MESSAGE_BEGIN(1, gmsgGreyFade, 0, plr->pev);
          g_engfuncs.pfnWriteByte(1);
          g_engfuncs.pfnWriteByte(0);
          g_engfuncs.pfnMessageEnd();
          CBasePlayer::PlayerStopMP3(plr, 1.0);
        }
      }
      CBaseEntity::ThinkSet(
        thisa,
        (void (__thiscall *)(CBaseEntity *))CBookSimon::RealKilled,
        "&CBookSimon::RealKilled");
      (*(void (__thiscall **)(CBookSimon *, int))&thisa->gap0[8])(thisa, 0x40000000);
      thisa->pev->effects |= 0x80u;
    }
    else
    {
      CBookSimon::RealKilled(thisa);
    }
  }
}

//----- (1007E420) --------------------------------------------------------
void __thiscall CBookSimon::Use(
        CBookSimon *this,
        CBaseEntity *pActivator,
        CBaseEntity *pCaller,
        USE_TYPE useType,
        float value)
{
  edict_s *v5; // eax
  _DWORD *v6; // eax
  int sequence; // [esp-4h] [ebp-60h]
  int m_iWeapon; // [esp+Ch] [ebp-50h]
  CBasePlayer *pPlayer; // [esp+50h] [ebp-Ch]
  CBaseEntity *player; // [esp+54h] [ebp-8h]

  if ( pActivator )
  {
    this->pev->effects &= ~0x80u;
    this->m_iAimState = 2;
    if ( this->pev->frags == 0.0 )
    {
      this->m_bIsBoss = 1;
      player = UTIL_FindEntityByClassname(0, "player");
      if ( player )
      {
        if ( player->IsPlayer(player) )
        {
          pPlayer = GetClassPtr<CBasePlayer>(player->pev);
          if ( pPlayer )
          {
            pPlayer->m_bBossHealthBar = 1;
            pPlayer->m_sBossBarEmpty = "gfx/vgui/boss/simon_health_empty.tga" - gpGlobals->pStringBase;
            pPlayer->m_sBossBarFull = "gfx/vgui/boss/simon_health_full.tga" - gpGlobals->pStringBase;
            pPlayer->m_iBossMaxHealth = (unsigned __int64)this->pev->max_health;
            pPlayer->m_iBossCurrentHealth = (unsigned __int64)this->pev->health;
            pPlayer->m_sBossName = this->pev->targetname;
            MESSAGE_BEGIN(1, gmsgBossBar, 0, pPlayer->pev);
            g_engfuncs.pfnWriteByte(1);
            g_engfuncs.pfnWriteString(&gpGlobals->pStringBase[pPlayer->m_sBossBarEmpty]);
            g_engfuncs.pfnWriteString(&gpGlobals->pStringBase[pPlayer->m_sBossBarFull]);
            g_engfuncs.pfnWriteShort(pPlayer->m_iBossCurrentHealth);
            g_engfuncs.pfnWriteShort(pPlayer->m_iBossMaxHealth);
            g_engfuncs.pfnMessageEnd();
          }
        }
      }
    }
    m_iWeapon = this->m_iWeapon;
    if ( m_iWeapon )
    {
      if ( m_iWeapon == 1 )
      {
        CBaseMonster::SetSequenceByName(this, "glock_appear");
      }
      else if ( m_iWeapon == 2 )
      {
        CBaseMonster::SetSequenceByName(this, "tmp_appear");
      }
    }
    else
    {
      CBaseMonster::SetSequenceByName(this, "shotgun_appear");
    }
    sequence = this->pev->sequence;
    v5 = ENT(this->pev);
    v6 = g_engfuncs.pfnGetModelPtr(v5);
    this->m_flSequenceTimeOverride = GetSequenceTime(v6, sequence) + gpGlobals->time;
  }
}

//----- (1007E680) --------------------------------------------------------
int __thiscall CBookSimon::TakeDamage(
        CBookSimon *this,
        entvars_s *pevInflictor,
        entvars_s *pevAttacker,
        float flDamage,
        int bitsDamageType)
{
  Vector *v6; // eax
  const Vector *v7; // eax
  const Vector *v8; // eax
  Vector *v9; // eax
  Vector result; // [esp+10h] [ebp-94h] BYREF
  Vector v11; // [esp+1Ch] [ebp-88h] BYREF
  Vector v12; // [esp+28h] [ebp-7Ch] BYREF
  Vector v13; // [esp+34h] [ebp-70h] BYREF
  Vector v14; // [esp+40h] [ebp-64h] BYREF
  CBaseEntity *pTarget; // [esp+8Ch] [ebp-18h]
  float flForce; // [esp+90h] [ebp-14h]
  Vector vecDir; // [esp+94h] [ebp-10h] BYREF
  CBookSimon *thisa; // [esp+A0h] [ebp-4h]

  thisa = this;
  if ( (this->pev->effects & 0x80) != 0 )
    return 0;
  if ( thisa->pev->frags != 0.0 && thisa->m_iAimState == 3 )
    return 0;
  if ( bitsDamageType == 2 )
  {
    v6 = Vector::operator+(&pevInflictor->absmin, &result, &pevInflictor->absmax);
    v7 = Vector::operator*(v6, &v11, 0.5);
    Vector::operator-(&thisa->pev->origin, &vecDir, v7);
    vecDir = *Vector::Normalize(&vecDir, &v12);
    flForce = CBaseMonster::DamageForce(thisa, flDamage);
    v8 = Vector::operator*(&vecDir, &v13, flForce);
    v9 = Vector::operator+(&thisa->pev->velocity, &v14, v8);
    thisa->pev->velocity = *v9;
    flDamage = flDamage * 0.3;
  }
  if ( thisa->pev->frags != 0.0 )
  {
    if ( thisa->m_iDamageToHide >= thisa->m_iDamageNeeded )
      return 0;
    pTarget = UTIL_FindEntityByTargetname(0, &gpGlobals->pStringBase[thisa->pev->message]);
    if ( pTarget )
      ((void (__thiscall *)(CBaseEntity *, entvars_s *, entvars_s *, _DWORD, int))pTarget->TakeDamage)(
        pTarget,
        pevInflictor,
        pevAttacker,
        LODWORD(flDamage),
        bitsDamageType);
    thisa->m_iDamageToHide = (unsigned __int64)((double)thisa->m_iDamageToHide + flDamage);
    flDamage = 0.0;
    thisa->pev->health = (float)(thisa->m_iDamageNeeded - thisa->m_iDamageToHide);
    if ( thisa->pev->health <= 0.0 )
      thisa->pev->health = 1.0;
  }
  return CBaseMonster::TakeDamage(thisa, pevInflictor, pevAttacker, flDamage, bitsDamageType);
}

//----- (1007E8C0) --------------------------------------------------------
void __thiscall CBookSimon::MonsterThink(CBookSimon *this)
{
  Vector *v1; // eax
  const Vector *v2; // eax
  Vector *v3; // eax
  Vector *v4; // eax
  Vector *v5; // eax
  Vector *v6; // eax
  edict_s *v7; // eax
  Vector *v8; // eax
  edict_s *v9; // eax
  edict_s *v10; // eax
  CBaseEntity *v11; // eax
  Vector *v12; // eax
  edict_s *v13; // eax
  _DWORD *v14; // eax
  double SequenceTime; // st7
  entvars_s *v16; // esi
  entvars_s *pev; // esi
  entvars_s *v18; // esi
  CBaseEntity *v19; // eax
  edict_s *v20; // eax
  CBaseEntity *v21; // eax
  const Vector *v22; // eax
  Vector *v23; // eax
  Vector *v24; // eax
  Vector *v25; // eax
  Vector *v26; // eax
  int v27; // eax
  edict_s *v28; // eax
  edict_s *v29; // eax
  edict_s *v30; // eax
  edict_s *v31; // eax
  edict_s *v32; // eax
  edict_s *v33; // eax
  CBaseEntity *v34; // eax
  Vector *v35; // eax
  Vector2D *v36; // eax
  float x; // edx
  float y; // eax
  Vector2D *v39; // eax
  float v40; // edx
  CBaseEntity *v41; // eax
  double v42; // st7
  _BYTE v43[40]; // [esp-38h] [ebp-28Ch] BYREF
  int p_origin; // [esp-10h] [ebp-264h]
  Vector v45; // [esp-Ch] [ebp-260h] BYREF
  int v46; // [esp+0h] [ebp-254h]
  double v47; // [esp+Ch] [ebp-248h]
  Vector result; // [esp+14h] [ebp-240h] BYREF
  Vector v49; // [esp+20h] [ebp-234h] BYREF
  Vector v50; // [esp+2Ch] [ebp-228h] BYREF
  _BYTE v51[12]; // [esp+38h] [ebp-21Ch] BYREF
  Vector vecSpread; // [esp+44h] [ebp-210h] BYREF
  Vector v; // [esp+50h] [ebp-204h] BYREF
  Vector v54; // [esp+5Ch] [ebp-1F8h] BYREF
  Vector v55; // [esp+74h] [ebp-1E0h] BYREF
  Vector v56; // [esp+80h] [ebp-1D4h] BYREF
  Vector v57; // [esp+8Ch] [ebp-1C8h] BYREF
  _BYTE v58[12]; // [esp+98h] [ebp-1BCh] BYREF
  Vector v59; // [esp+A4h] [ebp-1B0h] BYREF
  Vector v60; // [esp+B0h] [ebp-1A4h] BYREF
  Vector v61; // [esp+BCh] [ebp-198h] BYREF
  Vector vecDir; // [esp+ECh] [ebp-168h] BYREF
  Vector2D v63; // [esp+F8h] [ebp-15Ch] BYREF
  Vector2D v64; // [esp+100h] [ebp-154h] BYREF
  float yaw; // [esp+14Ch] [ebp-108h]
  Vector2D vec2LOS; // [esp+150h] [ebp-104h] BYREF
  Vector v67; // [esp+158h] [ebp-FCh] BYREF
  Vector v68; // [esp+164h] [ebp-F0h] BYREF
  CBaseEntity *pHit; // [esp+170h] [ebp-E4h]
  Vector ChairOrg; // [esp+174h] [ebp-E0h] BYREF
  Vector angles; // [esp+180h] [ebp-D4h] BYREF
  Vector v72; // [esp+18Ch] [ebp-C8h] BYREF
  Vector AttachAng; // [esp+198h] [ebp-BCh] BYREF
  Vector origin; // [esp+1A4h] [ebp-B0h] BYREF
  CSprite *v75; // [esp+1B0h] [ebp-A4h]
  TraceResult tr; // [esp+1B4h] [ebp-A0h] BYREF
  CBasePlayer *pCastPlayer; // [esp+1ECh] [ebp-68h]
  CBaseEntity *player; // [esp+1F0h] [ebp-64h]
  int distance; // [esp+1F4h] [ebp-60h]
  CSprite *pSprite; // [esp+1F8h] [ebp-5Ch]
  Vector vecShootDir; // [esp+1FCh] [ebp-58h] BYREF
  Vector vecShootOrigin; // [esp+208h] [ebp-4Ch] BYREF
  Vector AttachAng2; // [esp+214h] [ebp-40h] BYREF
  Vector AttachOrg2; // [esp+220h] [ebp-34h] BYREF
  Vector AttachOrg; // [esp+22Ch] [ebp-28h] BYREF
  float flDistToEnemy; // [esp+238h] [ebp-1Ch]
  Vector vecEnemyPos; // [esp+23Ch] [ebp-18h] BYREF
  CBasePlayer *plr; // [esp+248h] [ebp-Ch]
  int i; // [esp+24Ch] [ebp-8h]
  CBookSimon *thisa; // [esp+250h] [ebp-4h]

  thisa = this;
  if ( (this->pev->effects & 0x80) != 0 )
  {
    CBaseMonster::MonsterThink(thisa);
  }
  else
  {
    if ( thisa->pev->frags == 0.0 )
    {
      if ( CBaseAnimating::GetBodygroup(thisa, 2) )
        CBaseAnimating::SetBodygroup(thisa, 2, 0);
      if ( thisa->m_flNextShootTime < (double)gpGlobals->time )
      {
        for ( i = 1; i <= gpGlobals->maxClients; ++i )
        {
          plr = (CBasePlayer *)UTIL_PlayerByIndex(i);
          if ( plr )
          {
            if ( (*(int (__thiscall **)(CBasePlayer *))&plr->gap0[188])(plr) )
            {
              if ( thisa->FInViewCone(thisa, plr) )
              {
                if ( (*(int (__thiscall **)(CBookSimon *, CBasePlayer *))&thisa->gap0[276])(thisa, plr) )
                {
                  Vector::Vector(&vecEnemyPos, &plr->pev->origin);
                  v1 = Vector::operator-(&vecEnemyPos, &result, &thisa->pev->origin);
                  flDistToEnemy = Vector::Length(v1);
                  if ( flDistToEnemy <= 1024.0 )
                  {
                    Vector::Vector(&AttachOrg);
                    Vector::Vector(&AttachOrg2);
                    Vector::Vector(&AttachAng2);
                    Vector::Vector(&vecShootOrigin);
                    UTIL_MakeVectors(&thisa->pev->angles);
                    v2 = Vector::Vector(&v49, 0.0, 0.0, 35.0);
                    vecShootOrigin = *Vector::operator+(&thisa->pev->origin, &v50, v2);
                    LODWORD(v45.z) = &vecShootDir;
                    LODWORD(v45.y) = &vecShootOrigin;
                    LODWORD(v45.x) = &v54;
                    p_origin = (int)&plr->pev->origin;
                    *(_DWORD *)&v43[36] = &v;
                    *(_DWORD *)&v43[32] = &plr->pev->origin;
                    v3 = (Vector *)(*(int (__thiscall **)(CBasePlayer *, _BYTE *, Vector *, Vector *))&plr->gap0[264])(
                                     plr,
                                     v51,
                                     &vecShootOrigin,
                                     &vecSpread);
                    v4 = Vector::operator-(v3, *(Vector **)&v43[32], &v);
                    v5 = Vector::operator+(v4, (Vector *)p_origin, &v54);
                    v6 = Vector::operator-(v5, &vecShootOrigin, &vecShootDir);
                    Vector::Normalize(v6, (Vector *)v46);
                    v46 = 100;
                    v45.z = 0.0;
                    v45.y = 0.80000001;
                    v45.x = 1.0;
                    p_origin = (int)"weapons/shotgun/shoot.wav";
                    *(_DWORD *)&v43[36] = 1;
                    v7 = ENT(thisa->pev);
                    EMIT_SOUND_DYN(v7, 1, "weapons/shotgun/shoot.wav", 1.0, 0.80000001, 0, 100);
                    v46 = 0;
                    LODWORD(v45.z) = 1;
                    LODWORD(v45.y) = 10;
                    LODWORD(v45.x) = 9;
                    p_origin = 1149239296;
                    Vector::Vector((Vector *)&v43[28], 0.043620002, 0.043620002, 0.043620002);
                    Vector::Vector((Vector *)&v43[16], &vecShootDir);
                    Vector::Vector((Vector *)&v43[4], &vecShootOrigin);
                    CBaseEntity::FireBullets(
                      thisa,
                      5u,
                      *(Vector *)&v43[4],
                      *(Vector *)&v43[16],
                      *(Vector *)&v43[28],
                      *(float *)&p_origin,
                      v45.x,
                      SLODWORD(v45.y),
                      SLODWORD(v45.z),
                      (entvars_s *)v46);
                    *((float *)&v47 + 1) = gpGlobals->time + 1.0;
                    thisa->m_flNextShootTime = g_engfuncs.pfnRandomFloat(0.0, 0.5) + *((float *)&v47 + 1);
                    CBaseAnimating::SetBodygroup(thisa, 2, 1);
                    CBaseAnimating::GetAttachment(thisa, 2, &AttachOrg2, &AttachAng2);
                    v46 = 0;
                    v8 = Vector::operator float *(&thisa->pev->origin);
                    MESSAGE_BEGIN(5, gmsgCustomDLight, &v8->x, (edict_s *)v46);
                    g_engfuncs.pfnWriteCoord(AttachOrg2.x);
                    g_engfuncs.pfnWriteCoord(AttachOrg2.y);
                    g_engfuncs.pfnWriteCoord(AttachOrg2.z);
                    g_engfuncs.pfnWriteByte(10);
                    g_engfuncs.pfnWriteByte(5);
                    g_engfuncs.pfnWriteByte(30);
                    g_engfuncs.pfnMessageEnd();
                    pSprite = CSprite::SpriteCreate("sprites/muzzleflash.spr", &AttachOrg2, 0);
                    CSprite::SetTransparency(pSprite, 5, 255, 255, 255, 128, 0);
                    CSprite::SetScale(pSprite, 0.25);
                    ((void (__thiscall *)(CSprite *, int))pSprite->SetNextThink)(pSprite, 1036831949);
                    CBaseEntity::ThinkSet(pSprite, CBaseEntity::SUB_Remove, "&CSprite::SUB_Remove");
                    LODWORD(v45.z) = 2;
                    v9 = CBaseEntity::edict(thisa);
                    CSprite::SetAttachment(pSprite, v9, SLODWORD(v45.z));
                    break;
                  }
                }
              }
            }
          }
        }
      }
    }
    if ( thisa->pev->frags != 0.0 )
    {
      if ( CBaseAnimating::GetBodygroup(thisa, 2) )
        CBaseAnimating::SetBodygroup(thisa, 2, 0);
      if ( !thisa->m_bCanSeePlayer && thisa->m_bTMPSound )
      {
        thisa->m_bTMPSound = 0;
        LODWORD(v45.z) = 100;
        v45.y = 0.0;
        v45.x = 0.80000001;
        p_origin = 1065353216;
        *(_DWORD *)&v43[36] = "weapons/tmp/tmp_shoot_end.wav";
        *(_DWORD *)&v43[32] = 1;
        v10 = ENT(thisa->pev);
        EMIT_SOUND_DYN(
          v10,
          *(int *)&v43[32],
          *(const char **)&v43[36],
          *(float *)&p_origin,
          v45.x,
          SLODWORD(v45.y),
          SLODWORD(v45.z));
      }
      distance = 0;
      if ( thisa->pPlayer && EHANDLE::operator int(&thisa->pPlayer->m_pWheelchair) )
      {
        LODWORD(v45.z) = &thisa->pev->origin;
        LODWORD(v45.y) = &v55;
        v11 = EHANDLE::operator->(&thisa->pPlayer->m_pWheelchair);
        v12 = Vector::operator-(&v11->pev->origin, (Vector *)LODWORD(v45.y), (const Vector *)LODWORD(v45.z));
        distance = (unsigned __int64)Vector::Length2D(v12);
      }
      if ( thisa->m_iBulletsLoaded <= 0 && thisa->m_iAimState == 1
        || thisa->m_iDamageToHide >= thisa->m_iDamageNeeded && thisa->m_iAimState == 1
        || thisa->m_iAimState == 1 && distance > 0 && distance <= thisa->pev->iuser2 )
      {
        thisa->m_iAimState = 3;
        HIDWORD(v47) = thisa->m_iWeapon;
        if ( HIDWORD(v47) )
        {
          if ( HIDWORD(v47) == 1 )
          {
            CBaseMonster::SetSequenceByName(thisa, "glock_disappear");
          }
          else if ( HIDWORD(v47) == 2 )
          {
            CBaseMonster::SetSequenceByName(thisa, "tmp_disappear");
          }
        }
        else
        {
          CBaseMonster::SetSequenceByName(thisa, "shotgun_disappear");
        }
        LODWORD(v45.z) = thisa->pev->sequence;
        v13 = ENT(thisa->pev);
        v14 = g_engfuncs.pfnGetModelPtr(v13);
        SequenceTime = GetSequenceTime(v14, SLODWORD(v45.z));
        thisa->m_flSequenceTimeOverride = SequenceTime + gpGlobals->time;
      }
    }
    if ( thisa->pev->frags == 0.0
      || thisa->m_iAimState != 3
      || thisa->m_flSequenceTimeOverride >= (double)gpGlobals->time )
    {
      if ( thisa->pev->frags != 0.0 && thisa->m_iAimState == 2 && thisa->m_iDamageToHide < thisa->m_iDamageNeeded )
      {
        HIDWORD(v47) = thisa->m_iWeapon;
        if ( HIDWORD(v47) )
        {
          if ( HIDWORD(v47) == 1 )
          {
            pev = thisa->pev;
            if ( pev->sequence == CBaseAnimating::LookupSequence(thisa, "glock_appear")
              && thisa->m_flSequenceTimeOverride < (double)gpGlobals->time )
            {
              thisa->m_iAimState = 1;
              CBaseMonster::SetSequenceByName(thisa, "glock_idle");
            }
          }
          else if ( HIDWORD(v47) == 2 )
          {
            v18 = thisa->pev;
            if ( v18->sequence == CBaseAnimating::LookupSequence(thisa, "tmp_appear")
              && thisa->m_flSequenceTimeOverride < (double)gpGlobals->time )
            {
              thisa->m_iAimState = 1;
              CBaseMonster::SetSequenceByName(thisa, "tmp_idle");
            }
          }
        }
        else
        {
          v16 = thisa->pev;
          if ( v16->sequence == CBaseAnimating::LookupSequence(thisa, "shotgun_appear")
            && thisa->m_flSequenceTimeOverride < (double)gpGlobals->time )
          {
            thisa->m_iAimState = 1;
            CBaseMonster::SetSequenceByName(thisa, "shotgun_idle");
          }
        }
      }
      thisa->m_bCanSeePlayer = 0;
      if ( thisa->pev->frags != 0.0 && thisa->m_iAimState == 1 )
      {
        if ( thisa->pPlayer )
        {
          if ( EHANDLE::operator int(&thisa->pPlayer->m_pWheelchair) )
          {
            TraceResult::TraceResult(&tr);
            Vector::Vector(&origin);
            Vector::Vector(&AttachAng);
            Vector::Vector(&v72);
            Vector::Vector(&angles);
            CBaseAnimating::GetAttachment(thisa, 0, &origin, &AttachAng);
            v19 = EHANDLE::operator->(&thisa->pPlayer->m_pWheelchair);
            Vector::Vector(&ChairOrg, &v19->pev->origin);
            ChairOrg.z = ChairOrg.z + 36.0;
            LODWORD(v45.z) = &tr;
            v20 = ENT(thisa->pev);
            UTIL_TraceLine(&origin, &ChairOrg, dont_ignore_monsters, v20, (TraceResult *)LODWORD(v45.z));
            if ( tr.pHit )
            {
              pHit = CBaseEntity::Instance(tr.pHit);
              if ( pHit )
              {
                v21 = EHANDLE::operator CBaseEntity *(&thisa->pPlayer->m_pWheelchair);
                if ( pHit == v21 )
                {
                  if ( !thisa->m_bCanSeePlayer )
                    thisa->m_bCanSeePlayer = 1;
                  if ( thisa->m_flNextShootTime < (double)gpGlobals->time && thisa->m_iBulletsLoaded > 0 )
                  {
                    Vector::Vector(&v68);
                    UTIL_MakeVectors(&thisa->pev->angles);
                    v22 = Vector::Vector(&v56, 0.0, 0.0, 35.0);
                    v68 = *Vector::operator+(&thisa->pev->origin, &v57, v22);
                    HIDWORD(v47) = EHANDLE::operator->(&thisa->pPlayer->m_pWheelchair);
                    LODWORD(v45.z) = &v67;
                    LODWORD(v45.y) = &v68;
                    LODWORD(v45.x) = &v61;
                    p_origin = (int)&EHANDLE::operator->(&thisa->pPlayer->m_pWheelchair)->pev->origin;
                    *(_DWORD *)&v43[36] = &v60;
                    *(_DWORD *)&v43[32] = &EHANDLE::operator->(&thisa->pPlayer->m_pWheelchair)->pev->origin;
                    *(_DWORD *)&v43[28] = &v59;
                    v23 = (Vector *)(*(int (__thiscall **)(_DWORD, _BYTE *, Vector *))(*(_DWORD *)HIDWORD(v47) + 264))(
                                      HIDWORD(v47),
                                      v58,
                                      &v68);
                    v24 = Vector::operator-(v23, *(Vector **)&v43[28], *(const Vector **)&v43[32]);
                    v25 = Vector::operator+(v24, *(Vector **)&v43[36], (const Vector *)p_origin);
                    v26 = Vector::operator-(v25, (Vector *)LODWORD(v45.x), (const Vector *)LODWORD(v45.y));
                    Vector::Normalize(v26, (Vector *)LODWORD(v45.z));
                    MESSAGE_BEGIN(1, gmsgMuzzleflash, 0, thisa->pPlayer->pev);
                    v27 = CBaseEntity::entindex(thisa);
                    g_engfuncs.pfnWriteShort(v27);
                    g_engfuncs.pfnWriteByte(1);
                    g_engfuncs.pfnMessageEnd();
                    HIDWORD(v47) = thisa->m_iWeapon;
                    if ( HIDWORD(v47) )
                    {
                      if ( HIDWORD(v47) == 1 )
                      {
                        LODWORD(v45.z) = 100;
                        v45.y = 0.0;
                        v45.x = 0.80000001;
                        p_origin = 1065353216;
                        *(_DWORD *)&v43[36] = "weapons/glock/glock_fire.wav";
                        *(_DWORD *)&v43[32] = 1;
                        v32 = ENT(thisa->pev);
                        EMIT_SOUND_DYN(
                          v32,
                          *(int *)&v43[32],
                          *(const char **)&v43[36],
                          *(float *)&p_origin,
                          v45.x,
                          SLODWORD(v45.y),
                          SLODWORD(v45.z));
                        v45.z = 0.0;
                        LODWORD(v45.y) = 1;
                        LODWORD(v45.x) = 4;
                        p_origin = 9;
                        *(_DWORD *)&v43[36] = 1149239296;
                        Vector::Vector((Vector *)&v43[24], 0.034899998, 0.034899998, 0.034899998);
                        Vector::Vector((Vector *)&v43[12], &v67);
                        Vector::Vector((Vector *)v43, &v68);
                        CBaseEntity::FireBullets(
                          thisa,
                          5u,
                          *(Vector *)v43,
                          *(Vector *)&v43[12],
                          *(Vector *)&v43[24],
                          *(float *)&v43[36],
                          *(float *)&p_origin,
                          SLODWORD(v45.x),
                          SLODWORD(v45.y),
                          (entvars_s *)LODWORD(v45.z));
                        v47 = gpGlobals->time + 0.6;
                        thisa->m_flNextShootTime = g_engfuncs.pfnRandomFloat(0.0, 0.5) + v47;
                        --thisa->m_iBulletsLoaded;
                        CBaseAnimating::GetAttachment(thisa, 1, &v72, &angles);
                        v75 = CSprite::SpriteCreate("sprites/muzzleflash.spr", &v72, 0);
                        CSprite::SetTransparency(v75, 5, 255, 255, 255, 128, 0);
                        CSprite::SetScale(v75, 0.1);
                        ((void (__thiscall *)(CSprite *, int))v75->SetNextThink)(v75, 1036831949);
                        CBaseEntity::ThinkSet(v75, CBaseEntity::SUB_Remove, "&CSprite::SUB_Remove");
                        LODWORD(v45.z) = 1;
                        v33 = CBaseEntity::edict(thisa);
                        CSprite::SetAttachment(v75, v33, SLODWORD(v45.z));
                      }
                      else if ( HIDWORD(v47) == 2 )
                      {
                        if ( !thisa->m_bTMPSound )
                        {
                          thisa->m_bTMPSound = 1;
                          LODWORD(v45.z) = 100;
                          v45.y = 0.0;
                          v45.x = 0.80000001;
                          p_origin = 1065353216;
                          *(_DWORD *)&v43[36] = "weapons/tmp/tmp_shoot_loop.wav";
                          *(_DWORD *)&v43[32] = 1;
                          v30 = ENT(thisa->pev);
                          EMIT_SOUND_DYN(
                            v30,
                            *(int *)&v43[32],
                            *(const char **)&v43[36],
                            *(float *)&p_origin,
                            v45.x,
                            SLODWORD(v45.y),
                            SLODWORD(v45.z));
                        }
                        --thisa->m_iBulletsLoaded;
                        CBaseAnimating::GetAttachment(thisa, 3, &v72, &angles);
                        v75 = CSprite::SpriteCreate("sprites/muzzleflash.spr", &v72, 0);
                        CSprite::SetTransparency(v75, 5, 255, 255, 255, 128, 0);
                        CSprite::SetScale(v75, 0.25);
                        ((void (__thiscall *)(CSprite *, int))v75->SetNextThink)(v75, 1036831949);
                        CBaseEntity::ThinkSet(v75, CBaseEntity::SUB_Remove, "&CSprite::SUB_Remove");
                        LODWORD(v45.z) = 3;
                        v31 = CBaseEntity::edict(thisa);
                        CSprite::SetAttachment(v75, v31, SLODWORD(v45.z));
                        v45.z = 0.0;
                        LODWORD(v45.y) = 1;
                        LODWORD(v45.x) = 1;
                        p_origin = 9;
                        *(_DWORD *)&v43[36] = 1149239296;
                        Vector::Vector((Vector *)&v43[24], 0.087159999, 0.087159999, 0.087159999);
                        Vector::Vector((Vector *)&v43[12], &v67);
                        Vector::Vector((Vector *)v43, &v68);
                        CBaseEntity::FireBullets(
                          thisa,
                          1u,
                          *(Vector *)v43,
                          *(Vector *)&v43[12],
                          *(Vector *)&v43[24],
                          *(float *)&v43[36],
                          *(float *)&p_origin,
                          SLODWORD(v45.x),
                          SLODWORD(v45.y),
                          (entvars_s *)LODWORD(v45.z));
                        thisa->m_flNextShootTime = gpGlobals->time + 0.09;
                      }
                    }
                    else
                    {
                      LODWORD(v45.z) = 100;
                      v45.y = 0.0;
                      v45.x = 0.80000001;
                      p_origin = 1065353216;
                      *(_DWORD *)&v43[36] = "weapons/shotgun/shoot.wav";
                      *(_DWORD *)&v43[32] = 1;
                      v28 = ENT(thisa->pev);
                      EMIT_SOUND_DYN(
                        v28,
                        *(int *)&v43[32],
                        *(const char **)&v43[36],
                        *(float *)&p_origin,
                        v45.x,
                        SLODWORD(v45.y),
                        SLODWORD(v45.z));
                      v45.z = 0.0;
                      LODWORD(v45.y) = 2;
                      LODWORD(v45.x) = 10;
                      p_origin = 9;
                      *(_DWORD *)&v43[36] = 1149239296;
                      Vector::Vector((Vector *)&v43[24], 0.043620002, 0.043620002, 0.043620002);
                      Vector::Vector((Vector *)&v43[12], &v67);
                      Vector::Vector((Vector *)v43, &v68);
                      CBaseEntity::FireBullets(
                        thisa,
                        5u,
                        *(Vector *)v43,
                        *(Vector *)&v43[12],
                        *(Vector *)&v43[24],
                        *(float *)&v43[36],
                        *(float *)&p_origin,
                        SLODWORD(v45.x),
                        SLODWORD(v45.y),
                        (entvars_s *)LODWORD(v45.z));
                      *((float *)&v47 + 1) = gpGlobals->time + 1.0;
                      thisa->m_flNextShootTime = g_engfuncs.pfnRandomFloat(0.0, 0.5) + *((float *)&v47 + 1);
                      --thisa->m_iBulletsLoaded;
                      CBaseAnimating::GetAttachment(thisa, 2, &v72, &angles);
                      v75 = CSprite::SpriteCreate("sprites/muzzleflash.spr", &v72, 0);
                      CSprite::SetTransparency(v75, 5, 255, 255, 255, 128, 0);
                      CSprite::SetScale(v75, 0.25);
                      ((void (__thiscall *)(CSprite *, int))v75->SetNextThink)(v75, 1036831949);
                      CBaseEntity::ThinkSet(v75, CBaseEntity::SUB_Remove, "&CSprite::SUB_Remove");
                      LODWORD(v45.z) = 2;
                      v29 = CBaseEntity::edict(thisa);
                      CSprite::SetAttachment(v75, v29, SLODWORD(v45.z));
                    }
                  }
                }
              }
            }
          }
        }
        else
        {
          player = UTIL_FindEntityByClassname(0, "player");
          if ( player )
          {
            if ( player->IsPlayer(player) )
            {
              pCastPlayer = GetClassPtr<CBasePlayer>(player->pev);
              if ( pCastPlayer )
                thisa->pPlayer = pCastPlayer;
            }
          }
        }
      }
      if ( thisa->pev->frags != 0.0 && thisa->pPlayer && EHANDLE::operator int(&thisa->pPlayer->m_pWheelchair) )
      {
        Vector2D::Vector2D(&vec2LOS);
        UTIL_MakeVectors(&thisa->pev->angles);
        LODWORD(v45.z) = &v63;
        LODWORD(v45.y) = &thisa->pev->origin;
        LODWORD(v45.x) = &vecDir;
        v34 = EHANDLE::operator->(&thisa->pPlayer->m_pWheelchair);
        v35 = Vector::operator-(&v34->pev->origin, (Vector *)LODWORD(v45.x), (const Vector *)LODWORD(v45.y));
        v36 = Vector::Make2D(v35, (Vector2D *)LODWORD(v45.z));
        x = v36->x;
        y = v36->y;
        vec2LOS.x = x;
        vec2LOS.y = y;
        v39 = Vector2D::Normalize(&vec2LOS, &v64);
        v40 = v39->y;
        vec2LOS.x = v39->x;
        vec2LOS.y = v40;
        p_origin = (int)&thisa->pev->origin;
        *(_DWORD *)&v43[36] = &v45;
        v41 = EHANDLE::operator->(&thisa->pPlayer->m_pWheelchair);
        Vector::operator-(&v41->pev->origin, *(Vector **)&v43[36], (const Vector *)p_origin);
        v42 = CBaseMonster::VecToYaw(thisa, v45);
        yaw = v42 - thisa->pev->angles.y;
        if ( yaw > 180.0 )
          yaw = yaw - 360.0;
        if ( yaw < -180.0 )
          yaw = yaw + 360.0;
        CBaseAnimating::SetBoneController(thisa, 2, yaw);
      }
      CBaseMonster::MonsterThink(thisa);
    }
    else
    {
      UTIL_Remove(thisa);
    }
  }
}

