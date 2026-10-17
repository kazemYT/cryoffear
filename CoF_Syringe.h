struct __cppobj __declspec(align(4)) CSyringe : CBasePlayerWeapon
{
  bool b_HasUsed;
};

enum syringe_e : __int32
{
  SYRINGE_IDLE = 0x0,
  SYRINGE_DRAW = 0x1,
  SYRINGE_HOLSTER = 0x2,
  SYRINGE_USE = 0x3,
  SYRINGE_STAB = 0x4,
  SYRINGE_STAB_MISS = 0x5,
  SYRINGE_SPRINT_TO = 0x6,
  SYRINGE_SPRINT_IDLE = 0x7,
  SYRINGE_SPRINT_FROM = 0x8,
};