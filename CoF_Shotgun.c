/* CoF-SourceCode -- reconstructed from hl12.pdb + hl12.c (Hex-Rays 9.2)
 * module : .\debughl\CoF_Shotgun.obj
 * source : .\CoF_Shotgun.cpp
 * built  : 2012-03-21 21:35:13 UTC (PDB signature 1332365713, age 17)
 * rule   : Class::member -> Class__member, `name' -> _name_ (see tools/rebuild_tree.py)
 */

void __cdecl weapon_shotgun(entvars_s *pev)
{
  GetClassPtr_CShotgun_(pev);
}

void __thiscall CShotgun__Spawn(CShotgun *this)
{
  edict_s *v1; // eax

  this->pev->classname = (int)("weapon_shotgun" - gpGlobals->pStringBase);
  (*(void (__thiscall **)(CShotgun *))&this->gap0[48])(this);
  this->m_iId = 4;
  v1 = ENT__ov1(this->pev);
  g_engfuncs.pfnSetModel(v1, "models/weapons/shotgun/w_shotgun.mdl");
  this->m_iSprintIdleAnim1 = 9;
  this->m_iSprintIdleAnim2 = 666;
  this->m_bCanSuicide = 1;
  if ( this->pev->frags <= 0.0 )
  {
    if ( this->pev->frags == -2.0 )
      this->m_iClip = -666;
    this->m_iDefaultAmmo = 5;
  }
  else
  {
    this->m_iDefaultAmmo = (unsigned __int64)this->pev->frags;
  }
  while ( !this->script )
    this->script = (int)("inventoryitems/weapons/weapon_shotgun.txt" - gpGlobals->pStringBase);
  this->pev->renderfx = 99;
  this->strwmodel = (int)("models/weapons/shotgun/w_shotgun.mdl" - gpGlobals->pStringBase);
  CBasePlayerItem__FallInit((CBasePlayerItem *)this);
}

void __thiscall CShotgun__Precache(CShotgun *this)
{
  PRECACHE_MODEL("models/weapons/shotgun/v_shotgun.mdl");
  PRECACHE_MODEL("models/weapons/shotgun/w_shotgun.mdl");
  if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
    PRECACHE_MODEL("police/models/weapons/shotgun/p_shotgun.mdl");
  PRECACHE_MODEL("models/null.mdl");
  this->m_iShell = PRECACHE_MODEL("models/shotgunshell.mdl");
  PRECACHE_SOUND("weapons/item_get.wav");
  PRECACHE_SOUND("weapons/shotgun/shoot.wav");
  PRECACHE_SOUND("weapons/shotgun/insert.wav");
  PRECACHE_SOUND("weapons/shotgun/pump_forward.wav");
  PRECACHE_SOUND("weapons/shotgun/pump_back.wav");
  PRECACHE_SOUND("weapons/shotgun/pump_seq.wav");
}

int __thiscall CShotgun__GetItemInfo(CShotgun *this, ItemInfo *p)
{
  p->pszName = &gpGlobals->pStringBase[this->pev->classname];
  p->pszAmmo1 = "buckshot";
  p->iMaxAmmo1 = 50;
  p->pszAmmo2 = 0;
  p->iMaxAmmo2 = -1;
  p->iMaxClip = 5;
  p->iSlot = 5;
  p->iPosition = 0;
  p->iFlags = 0;
  this->m_iId = 4;
  p->iId = 4;
  p->iWeight = 20;
  return 1;
}

int __thiscall CShotgun__Deploy(CShotgun *this)
{
  if ( this->m_iClip == -666 )
    this->m_iClip = 0;
  this->m_iSuicideState = this->m_iSuicideState == 666;
  this->m_iSprintState = 0;
  if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
    return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
             "models/weapons/shotgun/v_shotgun.mdl",
             "police/models/weapons/shotgun/p_shotgun.mdl",
             6,
             "shotgun",
             1,
             0);
  else
    return CBasePlayerWeapon__DefaultDeploy((CBasePlayerWeapon *)this,
             "models/weapons/shotgun/v_shotgun.mdl",
             "models/null.mdl",
             6,
             "shotgun",
             1,
             0);
}

void __thiscall CShotgun__Holster(CShotgun *this)
{
  const Vector *v1; // eax
  float v2; // [esp+Ch] [ebp-54h]
  Vector v3; // [esp+10h] [ebp-50h] BYREF
  CShotgun *thisa; // [esp+5Ch] [ebp-4h]

  thisa = this;
  CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 7, 1, 0);
  v2 = gpGlobals->time + 0.5;
  thisa->m_pPlayer->m_flNextAttack = v2;
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
}

void __thiscall CShotgun__SecondaryAttack(CShotgun *this)
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
    CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 18, 1, 0);
    CBasePlayer__PlayerAnimation(this->m_pPlayer, "shotgun_melee", 0);
    this->m_flTimeWeaponIdle = gpGlobals->time + 1.0;
    this->m_flNextSecondaryAttack = this->m_flTimeWeaponIdle;
    this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  }
}

void __thiscall CShotgun__PrimaryAttack(CShotgun *this)
{
  int v1; // eax
  const Vector *v2; // eax
  float v3; // eax
  const edict_s *v4; // eax
  edict_s *v5; // eax
  double v6; // st7
  Vector v7; // [esp-1Ch] [ebp-F4h] BYREF
  Vector v8; // [esp-10h] [ebp-E8h] BYREF
  Vector v9; // [esp-4h] [ebp-DCh] BYREF
  float v10; // [esp+8h] [ebp-D0h]
  float v11; // [esp+Ch] [ebp-CCh]
  int m_iId; // [esp+10h] [ebp-C8h]
  float p; // [esp+14h] [ebp-C4h]
  float v14; // [esp+18h] [ebp-C0h]
  int random_seed; // [esp+1Ch] [ebp-BCh]
  float v16; // [esp+2Ch] [ebp-ACh]
  Vector result; // [esp+30h] [ebp-A8h] BYREF
  Vector v18; // [esp+48h] [ebp-90h] BYREF
  Vector vecDir; // [esp+94h] [ebp-44h] BYREF
  Vector vecAiming; // [esp+A0h] [ebp-38h] BYREF
  Vector vecSrc; // [esp+ACh] [ebp-2Ch] BYREF
  Vector vecShellEnd; // [esp+B8h] [ebp-20h] BYREF
  Vector vecShellSrc; // [esp+C4h] [ebp-14h] BYREF
  int flags; // [esp+D0h] [ebp-8h]
  CShotgun *thisa; // [esp+D4h] [ebp-4h]

  thisa = this;
  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && (thisa->m_pPlayer->m_afButtonPressed & 1) != 0
    && !thisa->m_iSprintState
    && !thisa->m_iSuicideState )
  {
    if ( thisa->m_pPlayer->pev->waterlevel == 3 )
    {
      if ( thisa->m_fEmptyClickTime < (double)gpGlobals->time )
      {
        CBasePlayerWeapon__PlayEmptySound((CBasePlayerWeapon *)thisa);
        thisa->m_fEmptyClickTime = gpGlobals->time + 0.25;
      }
    }
    else
    {
      if ( thisa->m_fInReload && !thisa->pev->iuser2 )
        thisa->pev->iuser2 = 1;
      if ( thisa->m_iClip > 0 || thisa->m_fInReload )
      {
        if ( !thisa->m_fInReload )
        {
          thisa->m_pPlayer->m_iWeaponVolume = 1000;
          thisa->m_pPlayer->m_iWeaponFlash = 256;
          CBaseEntity__ThinkSet((CBaseEntity *)thisa, (void (__thiscall *)(CBaseEntity *))CShotgun__LolShell, "LolShell");
          v16 = gpGlobals->time + 0.45;
          thisa->pev->nextthink = v16;
          MESSAGE_BEGIN__ov4_2(1, gmsgParticle, 0, thisa->m_pPlayer->pev);
          v1 = CBaseEntity__entindex((CBaseEntity *)thisa);
          g_engfuncs.pfnWriteShort(v1);
          g_engfuncs.pfnWriteString("aurora/gunsmoke.aur");
          g_engfuncs.pfnWriteByte(1);
          g_engfuncs.pfnWriteString("models/weapons/shotgun/v_shotgun.mdl");
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
          v14 = 0.0;
          p = 0.0;
          m_iId = thisa->m_iId;
          v11 = 0.0;
          v10 = 0.0;
          LODWORD(v9.z) = (int)&vecShellEnd;
          HIWORD(v3) = HIWORD(thisa);
          LODWORD(v9.y) = (int)&thisa->m_pPlayer->pev->origin;
          v9.x = 0.0;
          LOWORD(v3) = m_usThirdFlash;
          v8.z = v3;
          v4 = ENT__ov1(thisa->m_pPlayer->pev);
          g_engfuncs.pfnPlaybackEvent(
            flags,
            v4,
            LOWORD(v8.z),
            0.0,
            (float *)LODWORD(v9.y),
            &vecShellEnd.x,
            0.0,
            0.0,
            m_iId,
            0,
            0,
            0);
          CBasePlayer__PlayerAnimation(thisa->m_pPlayer, "shotgun_shoot", 0);
          UTIL_ScreenShake(
            &thisa->m_pPlayer->pev->origin,
            7.0,
            0.34999999,
            0.15000001,
            2.0);
          if ( thisa->m_bIronSights )
            CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 16, 1, 0);
          else
            CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 1, 1, 0);
          random_seed = 100;
          v14 = 0.0;
          p = 0.80000001;
          m_iId = 1065353216;
          LODWORD(v11) = (int)"weapons/shotgun/shoot.wav";
          LODWORD(v10) = 1;
          v5 = ENT__ov1(thisa->m_pPlayer->pev);
          EMIT_SOUND_DYN(v5, 1, "weapons/shotgun/shoot.wav", 1.0, 0.80000001, 0, 100);
          thisa->m_pPlayer->pev->effects |= 2u;
          CBasePlayer__GetGunPosition((CBasePlayer *)thisa->m_pPlayer, &vecSrc);
          CBasePlayer__GetAutoaimVector(thisa->m_pPlayer, &vecAiming, 0.087155744);
          Vector__Vector__ov1(&vecDir);
          random_seed = thisa->m_pPlayer->random_seed;
          v14 = *(float *)&thisa->m_pPlayer->pev;
          LODWORD(p) = (unsigned __int64)gSkillData.DmgShotgun;
          m_iId = 0;
          LODWORD(v11) = 3;
          v10 = 2048.0;
          Vector__Vector__ov4(&v9, 0.069760002, 0.069760002, 0.069760002);
          Vector__Vector__ov2(&v8, &vecAiming);
          Vector__Vector__ov2(&v7, &vecSrc);
          CBaseEntity__FireBulletsPlayer(
            (CBaseEntity *)thisa->m_pPlayer,
            &v18,
            8u,
            v7,
            v8,
            v9,
            v10,
            v11,
            m_iId,
            SLODWORD(p),
            (entvars_s *)LODWORD(v14),
            random_seed);
          random_seed = 0x40000000;
          v14 = 2.0;
          v16 = (int)(*(float *)&(int){ (int)(g_engfuncs.pfnRandomLong(-4, 4)) });
          p = (float)SLODWORD(v16);
          CBasePlayer__ViewPunch(thisa->m_pPlayer, p, v14, *(float *)&random_seed);
          CBasePlayer__ViewKnock(thisa->m_pPlayer, 5.0);
          if ( !thisa->m_iClip && thisa->m_pPlayer->m_rgAmmo[thisa->m_iPrimaryAmmoType] <= 0 )
            CBasePlayer__SetSuitUpdate(thisa->m_pPlayer, "!HEV_AMO0", 0, 0);
          thisa->m_flNextPrimaryAttack = gpGlobals->time + 1.0;
          if ( thisa->m_iClip )
            v6 = gpGlobals->time + 5.0;
          else
            v6 = gpGlobals->time + 1.0;
          thisa->m_flTimeWeaponIdle = v6;
          thisa->m_fInSpecialReload = 0;
        }
      }
      else if ( !thisa->m_iClip && thisa->m_fEmptyClickTime < (double)gpGlobals->time )
      {
        CBasePlayerWeapon__PlayEmptySound((CBasePlayerWeapon *)thisa);
        thisa->m_fEmptyClickTime = gpGlobals->time + 0.25;
      }
    }
  }
}

void __thiscall CShotgun__IronsightsTo(CShotgun *this)
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
  CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 14, 1, 0);
  this->m_bIronSights = 1;
  this->m_flNextTertiaryAttack = gpGlobals->time + 0.3;
  this->m_flNextSecondaryAttack = this->m_flNextTertiaryAttack;
  this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  weaponanim = this->m_pPlayer->pev->weaponanim;
  v9 = ENT__ov1(this->pev);
  v10 = g_engfuncs.pfnGetModelPtr(v9);
  this->m_flTimeWeaponIdle = GetSequenceTime(v10, weaponanim) + gpGlobals->time;
}

void __thiscall CShotgun__IronsightsFrom(CShotgun *this)
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
  CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 17, 1, 0);
  this->m_bIronSights = 0;
  this->m_flNextTertiaryAttack = gpGlobals->time + 0.3;
  this->m_flNextSecondaryAttack = this->m_flNextTertiaryAttack;
  this->m_flNextPrimaryAttack = this->m_flNextSecondaryAttack;
  weaponanim = this->m_pPlayer->pev->weaponanim;
  v9 = ENT__ov1(this->pev);
  v10 = g_engfuncs.pfnGetModelPtr(v9);
  this->m_flTimeWeaponIdle = GetSequenceTime(v10, weaponanim) + gpGlobals->time;
}

void __thiscall CShotgun__TertiaryAttack(CShotgun *this)
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
      CShotgun__IronsightsTo((CShotgun *)this);
    else
      CShotgun__IronsightsFrom((CShotgun *)this);
  }
}

void __thiscall CShotgun__ShellInsert(CShotgun *this)
{
  ++this->m_iClip;
  --this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType];
  this->m_fInSpecialReload = 1;
}

void __thiscall CShotgun__Reload(CShotgun *this)
{
  float v1; // [esp+Ch] [ebp-48h]

  if ( this->m_pPlayer->m_rgAmmo[this->m_iPrimaryAmmoType] > 0 && this->m_iClip != 5 )
  {
    if ( !this->m_iClip )
      this->pev->iuser1 = 1;
    if ( this->m_iSprintState != 1
      && this->m_iSprintState <= 2
      && !this->m_iSuicideState
      && this->m_flNextPrimaryAttack <= (double)gpGlobals->time
      && !this->m_bWaitingToReloadIronsights )
    {
      if ( this->m_bIronSights )
      {
        this->m_bWaitingToReloadIronsights = 1;
      }
      else
      {
        this->m_iSprintState = 2;
        if ( this->m_fInSpecialReload )
        {
          if ( this->m_fInSpecialReload == 1 && this->m_flTimeWeaponIdle <= (double)gpGlobals->time )
          {
            this->m_fInSpecialReload = 2;
            CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 3, 1, 0);
            CBasePlayer__PlayerAnimation(this->m_pPlayer, "shotgun_reload_insert", 0);
            this->m_pPlayer->m_flSequenceOverrideTime = gpGlobals->time + 1.0;
            this->m_flNextReload = gpGlobals->time + 0.6;
            this->m_flTimeWeaponIdle = gpGlobals->time + 0.65;
            (*(void (__thiscall **)(CShotgun *, int))&this->gap0[8])(this, 1051260355);
            CBaseEntity__ThinkSet((CBaseEntity *)this, (void (__thiscall *)(CBaseEntity *))CShotgun__ShellInsert, "ShellInsert");
          }
        }
        else
        {
          this->pev->iuser2 = 0;
          CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 2, 1, 0);
          this->m_fInSpecialReload = 1;
          v1 = UTIL_WeaponTimeBase() + 0.5;
          this->m_pPlayer->m_flNextAttack = v1;
          this->m_flTimeWeaponIdle = gpGlobals->time + 0.5;
          this->m_flNextPrimaryAttack = gpGlobals->time + 0.51;
          CBasePlayer__PlayerAnimation(this->m_pPlayer, "shotgun_reload_start", 0);
          this->m_pPlayer->m_flSequenceOverrideTime = gpGlobals->time + 1.0;
        }
      }
    }
  }
}

void __thiscall CShotgun__Fidget(CShotgun *this)
{
  int v1; // [esp+Ch] [ebp-48h]

  if ( this->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && this->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && this->m_flTimeWeaponIdle <= (double)gpGlobals->time
    && !this->m_iSprintState
    && !this->m_iSuicideState
    && g_engfuncs.pfnRandomLong(0, 599) == 50
    && !this->m_bIronSights )
  {
    v1 = g_engfuncs.pfnRandomLong(0, 2);
    if ( v1 )
    {
      if ( v1 == 1 )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 12, 1, 0);
      }
      else if ( v1 == 2 )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 13, 1, 0);
      }
    }
    else
    {
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)this, 11, 1, 0);
    }
  }
}

void __thiscall CShotgun__WeaponIdle(CShotgun *this)
{
  edict_s *v1; // eax
  _DWORD *v2; // eax
  double SequenceTime; // st7
  int weaponanim; // [esp-4h] [ebp-60h]
  Vector result; // [esp+Ch] [ebp-50h] BYREF
  CShotgun *thisa; // [esp+58h] [ebp-4h]

  thisa = this;
  CBasePlayer__GetAutoaimVector(this->m_pPlayer, &result, 0.087155744);
  if ( thisa->m_flTimeWeaponIdle <= (double)gpGlobals->time
    && thisa->m_flNextPrimaryAttack <= (double)gpGlobals->time
    && thisa->m_flNextSecondaryAttack <= (double)gpGlobals->time
    && !thisa->m_iSprintState
    && !thisa->m_iSuicideState )
  {
    if ( thisa->m_bIronSights )
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 15, 1, 0);
    else
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 0, 1, 0);
    weaponanim = thisa->m_pPlayer->pev->weaponanim;
    v1 = ENT__ov1(thisa->pev);
    v2 = g_engfuncs.pfnGetModelPtr(v1);
    SequenceTime = GetSequenceTime(v2, weaponanim);
    thisa->m_flTimeWeaponIdle = SequenceTime + gpGlobals->time;
  }
}

void __thiscall CShotgun__StartSuicide(CShotgun *this)
{
  const Vector *v1; // eax
  edict_s *v2; // eax
  edict_s *v3; // eax
  edict_s *v4; // eax
  int v5; // [esp+Ch] [ebp-54h]
  Vector v6; // [esp+10h] [ebp-50h] BYREF
  CShotgun *thisa; // [esp+5Ch] [ebp-4h]

  thisa = this;
  (*(void (__thiscall **)(CShotgun *, int))&this->gap0[8])(this, 1082130432);
  CBaseEntity__ThinkSet((CBaseEntity *)thisa, (void (__thiscall *)(CBaseEntity *))CShotgun__SuicideShot, "&CShotgun::SuicideShot");
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

void __thiscall CShotgun__SuicideShot(CShotgun *this)
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
    EMIT_SOUND_DYN(v1, 1, "weapons/shotgun/shoot.wav", 1.0, 0.80000001, 0, v2);
  }
  else
  {
    CBasePlayerWeapon__PlayEmptySound((CBasePlayerWeapon *)this);
    this->m_fEmptyClickTime = gpGlobals->time + 0.25;
    CShotgun__StopSuicide((CShotgun *)this);
  }
}

void __thiscall CShotgun__StopSuicide(CShotgun *this)
{
  const Vector *v1; // eax
  Vector v2; // [esp+Ch] [ebp-50h] BYREF
  CShotgun *thisa; // [esp+58h] [ebp-4h]

  thisa = this;
  CBaseEntity__ThinkSet((CBaseEntity *)this, 0, "NULL");
  thisa->m_iSuicideButtonsPressed = 0;
  thisa->m_iSuicideState = 0;
  v1 = Vector__Vector__ov4(&v2, 128.0, 128.0, 128.0);
  UTIL_ScreenFade((CBaseEntity *)thisa->m_pPlayer, v1, 0.5, 0.0, 0xFFu, 0);
  if ( thisa->m_pPlayer->pev->fuser3 == 10.0 )
    thisa->m_pPlayer->pev->fuser3 = 0.0;
  CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 6, 1, 0);
  thisa->m_pPlayer->m_flNextAttack = gpGlobals->time + 1.0;
  thisa->m_flTimeWeaponIdle = gpGlobals->time + 1.0;
  thisa->m_flNextSecondaryAttack = thisa->m_flTimeWeaponIdle;
  thisa->m_flNextPrimaryAttack = thisa->m_flNextSecondaryAttack;
}

void __thiscall CShotgun__ItemPostFrame(CShotgun *this)
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
  CShotgun *thisa; // [esp+80h] [ebp-4h]

  thisa = this;
  if ( this->m_fInSpecialReload
    && (thisa->m_pPlayer->m_afButtonPressed & 1) != 0
    && !thisa->pev->iuser2
    && thisa->m_iClip >= 1 )
  {
    thisa->pev->iuser2 = 1;
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
      CShotgun__StopSuicide((CShotgun *)thisa);
  }
  if ( thisa->m_iSuicideState == 1 )
  {
    if ( thisa->m_iSprintState && thisa->m_iNextSprintAnim < (double)gpGlobals->time )
    {
      thisa->m_flNextPrimaryAttack = gpGlobals->time + 0.33;
      thisa->m_flTimeWeaponIdle = gpGlobals->time + 0.35;
      thisa->m_iNextSprintAnim = gpGlobals->time + 0.33;
      thisa->m_iSprintState = 0;
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 10, 1, 0);
    }
    else if ( thisa->m_iNextSprintAnim < (double)gpGlobals->time && !thisa->m_iSprintState )
    {
      thisa->m_iSuicideState = 2;
      CShotgun__StartSuicide((CShotgun *)thisa);
    }
  }
  if ( thisa->m_bWaitingToReloadIronsights
    && !thisa->m_fInSpecialReload
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
      CShotgun__IronsightsFrom((CShotgun *)thisa);
    }
    else
    {
      thisa->m_bWaitingToReloadIronsights = 0;
      CShotgun__Reload((CShotgun *)thisa);
    }
  }
  if ( thisa->m_flTimeWeaponIdle < (double)gpGlobals->time && thisa->m_fInSpecialReload )
  {
    if ( thisa->pev->iuser2 )
    {
      if ( thisa->pev->iuser1 )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 5, 1, 0);
        thisa->m_flNextPrimaryAttack = gpGlobals->time + 0.6;
        CBasePlayer__PlayerAnimation(thisa->m_pPlayer, "shotgun_reload_endempty", 0);
      }
      else
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 4, 1, 0);
        thisa->m_flNextPrimaryAttack = gpGlobals->time + 0.5;
        CBasePlayer__PlayerAnimation(thisa->m_pPlayer, "shotgun_reload_end", 0);
      }
      thisa->m_iSprintState = 0;
      thisa->pev->iuser1 = 0;
      thisa->m_fInSpecialReload = 0;
      thisa->m_flTimeWeaponIdle = gpGlobals->time + 1.0;
      thisa->pev->iuser2 = 0;
    }
    else if ( thisa->m_iClip == 5 || !thisa->m_pPlayer->m_rgAmmo[thisa->m_iPrimaryAmmoType] )
    {
      if ( thisa->pev->iuser1 )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 5, 1, 0);
        thisa->m_flNextPrimaryAttack = gpGlobals->time + 0.6;
        CBasePlayer__PlayerAnimation(thisa->m_pPlayer, "shotgun_reload_endempty", 0);
      }
      else
      {
        CBasePlayer__PlayerAnimation(thisa->m_pPlayer, "shotgun_reloadend", 0);
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 4, 1, 0);
        thisa->m_flNextPrimaryAttack = gpGlobals->time + 0.5;
      }
      thisa->m_iSprintState = 0;
      thisa->pev->iuser1 = 0;
      thisa->m_fInSpecialReload = 0;
      thisa->m_flTimeWeaponIdle = gpGlobals->time + 1.0;
      thisa->pev->iuser2 = 0;
    }
    else
    {
      CShotgun__Reload((CShotgun *)thisa);
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
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 10, 1, 0);
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
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 8, 1, 0);
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
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 8, 1, 0);
      v18 = thisa->m_pPlayer->pev->weaponanim;
      v7 = ENT__ov1(thisa->pev);
      v8 = g_engfuncs.pfnGetModelPtr(v7);
      time = GetSequenceTime(v8, v18);
      thisa->m_flNextPrimaryAttack = gpGlobals->time + time * 0.5;
      thisa->m_iNextSprintAnim = time + gpGlobals->time;
    }
    if ( (thisa->m_pPlayer->pev->flags & 0x40000) != 0
      && speed > 0.0
      && thisa->m_iSprintState != 5 )
    {
      v22 = Vector__Length2D(&thisa->m_pPlayer->pev->velocity);
      if ( thisa->m_iSprintState == 1 && thisa->m_iNextSprintAnim < (double)gpGlobals->time && v22 != 0.0 )
      {
        CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 9, 1, 0);
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
      CBasePlayerWeapon__SendWeaponAnim((CBasePlayerWeapon *)thisa, 10, 1, 0);
      v20 = thisa->m_pPlayer->pev->weaponanim;
      v11 = ENT__ov1(thisa->pev);
      v12 = g_engfuncs.pfnGetModelPtr(v11);
      time = GetSequenceTime(v12, v20);
      thisa->m_flNextPrimaryAttack = time + gpGlobals->time;
      thisa->m_iSprintState = 0;
    }
  }
  CBasePlayerWeapon__ItemPostFrame((CBasePlayerWeapon *)thisa);
}

void __thiscall CShotgun__LolShell(CShotgun *this)
{
  Vector *v1; // eax
  Vector *v2; // eax
  Vector *v3; // eax
  Vector *v4; // eax
  const Vector *v5; // [esp-Ch] [ebp-D4h]
  const Vector *v6; // [esp-Ch] [ebp-D4h]
  const Vector *v7; // [esp-4h] [ebp-CCh]
  const Vector *v8; // [esp-4h] [ebp-CCh]
  Vector v9; // [esp+Ch] [ebp-BCh] BYREF
  Vector v10; // [esp+18h] [ebp-B0h] BYREF
  Vector v11; // [esp+24h] [ebp-A4h] BYREF
  Vector result; // [esp+30h] [ebp-98h] BYREF
  Vector v13; // [esp+3Ch] [ebp-8Ch] BYREF
  Vector v14; // [esp+48h] [ebp-80h] BYREF
  Vector v15; // [esp+54h] [ebp-74h] BYREF
  Vector v16; // [esp+60h] [ebp-68h] BYREF
  Vector vecShellOrigin; // [esp+ACh] [ebp-1Ch] BYREF
  Vector vecShellVelocity; // [esp+B8h] [ebp-10h] BYREF
  CShotgun *thisa; // [esp+C4h] [ebp-4h]

  thisa = this;
  v7 = Vector__operator_mul(&gpGlobals->v_forward, &result, 40.0);
  v5 = Vector__operator_mul(&gpGlobals->v_up, &v10, 200.0);
  v1 = Vector__operator_mul(&gpGlobals->v_right, &v9, 60.0);
  v2 = Vector__operator_plus(v1, &v11, v5);
  Vector__operator_plus(v2, &vecShellVelocity, v7);
  v8 = Vector__operator_mul(&gpGlobals->v_right, &v16, 30.0);
  v6 = Vector__operator_mul(&gpGlobals->v_forward, &v14, 45.0);
  v3 = Vector__operator_plus(&thisa->pev->origin, &v13, &thisa->pev->view_ofs);
  v4 = Vector__operator_plus(v3, &v15, v6);
  Vector__operator_plus(v4, &vecShellOrigin, v8);
  EjectBrass(&vecShellOrigin, &vecShellVelocity, thisa->pev->angles.y, thisa->m_iShell, 2);
}

void __cdecl ammo_shells(entvars_s *pev)
{
  GetClassPtr_CShotgunAmmo_(pev);
}

CShotgun *__cdecl GetClassPtr_CShotgun_(entvars_s *a)
{
  edict_s *v1; // eax
  edict_s *v2; // eax
  CShotgun *v4; // [esp+Ch] [ebp-5Ch]
  CShotgun *v5; // [esp+14h] [ebp-54h]
  entvars_s *pev; // [esp+58h] [ebp-10h]
  CShotgun *aa; // [esp+70h] [ebp+8h]

  pev = a;
  if ( !a )
  {
    v1 = g_engfuncs.pfnCreateEntity();
    pev = VARS__ov1(v1);
  }
  v2 = ENT__ov1(pev);
  aa = (CShotgun *)GET_PRIVATE(v2);
  if ( !aa )
  {
    v5 = (CShotgun *)CBaseEntity__operator_new__ov2(0x1F4u, pev);
    if ( v5 )
      v4 = CShotgun__CShotgun(v5);
    else
      v4 = 0;
    aa = v4;
    v4->pev = pev;
  }
  return aa;
}

CShotgunAmmo *__cdecl GetClassPtr_CShotgunAmmo_(entvars_s *a)
{
  edict_s *v1; // eax
  edict_s *v2; // eax
  CShotgunAmmo *v4; // [esp+Ch] [ebp-5Ch]
  CShotgunAmmo *v5; // [esp+14h] [ebp-54h]
  entvars_s *pev; // [esp+58h] [ebp-10h]
  CShotgunAmmo *aa; // [esp+70h] [ebp+8h]

  pev = a;
  if ( !a )
  {
    v1 = g_engfuncs.pfnCreateEntity();
    pev = VARS__ov1(v1);
  }
  v2 = ENT__ov1(pev);
  aa = (CShotgunAmmo *)GET_PRIVATE(v2);
  if ( !aa )
  {
    v5 = (CShotgunAmmo *)CBaseEntity__operator_new__ov2(0xDCu, pev);
    if ( v5 )
      v4 = CShotgunAmmo__CShotgunAmmo(v5);
    else
      v4 = 0;
    aa = v4;
    v4->pev = pev;
  }
  return aa;
}

CShotgun *__thiscall CShotgun__CShotgun(CShotgun *this)
{
  CBasePlayerWeapon__CBasePlayerWeapon((CBasePlayerWeapon *)this);
  this->__vftable = (CBasePlayerWeapon_vtbl *)&CShotgun___vftable_;
  return this;
}

int __thiscall CShotgun__iItemSlot(CShotgun *this)
{
  return 3;
}

CShotgunAmmo *__thiscall CShotgunAmmo__CShotgunAmmo(CShotgunAmmo *this)
{
  CBasePlayerAmmo__CBasePlayerAmmo((CBasePlayerAmmo *)this);
  this->__vftable = (CShotgunAmmo_vtbl *)&CShotgunAmmo___vftable_;
  return this;
}

void __thiscall CShotgunAmmo__Spawn(CShotgunAmmo *this)
{
  edict_s *v1; // eax

  CShotgunAmmo__Precache((CShotgunAmmo *)this);
  v1 = ENT__ov1(this->pev);
  g_engfuncs.pfnSetModel(v1, "models/ammo/ammo_shotshells.mdl");
  CBasePlayerAmmo__Spawn((CBasePlayerAmmo *)this);
  this->pev->iuser1 = 9;
}

void __thiscall CShotgunAmmo__Precache(CShotgunAmmo *this)
{
  PRECACHE_MODEL("models/ammo/ammo_shotshells.mdl");
  PRECACHE_SOUND("weapons/item_get.wav");
}

int __thiscall CShotgunAmmo__AddAmmo(CShotgunAmmo *this, CBaseEntity *pOther)
{
  edict_s *v3; // eax

  if ( this->pev->message )
  {
    if ( CBaseEntity__GiveAmmo((CBaseEntity *)pOther, this->pev->message, "buckshot", 50) == -1 )
      return 0;
    goto LABEL_10;
  }
  if ( g_pGameRules && g_pGameRules->__vftable->IsMultiplayer(g_pGameRules) )
  {
    if ( CBaseEntity__GiveAmmo((CBaseEntity *)pOther, this->pev->iuser1, "buckshot", 27) == -1 )
      return 0;
    goto LABEL_10;
  }
  if ( CBaseEntity__GiveAmmo((CBaseEntity *)pOther, 9, "buckshot", 50) != -1 )
  {
LABEL_10:
    v3 = ENT__ov1(this->pev);
    EMIT_SOUND(v3, 3, "weapons/item_get.wav", 1.0, 0.80000001);
    return 1;
  }
  return 0;
}

