enum shotgun_e : __int32
{
  SHOTGUN_IDLE = 0x0,
  SHOTGUN_FIRE = 0x1,
  SHOTGUN_START_RELOAD = 0x2,
  SHOTGUN_RELOAD = 0x3,
  SHOTGUN_PUMP = 0x4,
  SHOTGUN_PUMP_EMPTY = 0x5,
  SHOTGUN_DRAW = 0x6,
  SHOTGUN_HOLSTER = 0x7,
  SHOTGUN_TO_SPRINT = 0x8,
  SHOTGUN_SPRINT = 0x9,
  SHOTGUN_FROM_SPRINT = 0xA,
  SHOTGUN_FIDGET_ONE = 0xB,
  SHOTGUN_FIDGET_TWO = 0xC,
  SHOTGUN_FIDGET_THREE = 0xD,
  SHOTGUN_IRON_TO = 0xE,
  SHOTGUN_IRON_IDLE = 0xF,
  SHOTGUN_IRON_SHOOT = 0x10,
  SHOTGUN_IRON_FROM = 0x11,
  SHOTGUN_MELEE = 0x12,
  SHOTGUN_SUICIDE = 0x13,
};

struct __cppobj CShotgun : CBasePlayerWeapon
{
  int m_fInReload;
  float m_flNextReload;
  int m_iShell;
};