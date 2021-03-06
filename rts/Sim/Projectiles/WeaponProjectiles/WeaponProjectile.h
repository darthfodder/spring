/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef WEAPON_PROJECTILE_H
#define WEAPON_PROJECTILE_H

#include "Sim/Projectiles/Projectile.h"

struct WeaponDef;
class CPlasmaRepulser;
class CWeaponProjectile;
class CWeapon;

struct ProjectileParams {
	ProjectileParams()
		: ttl(0)
		, target(NULL)
		, owner(NULL)
		, weapon(NULL)
		, weaponDef(NULL)
	{
	}

	int ttl;
	float3 pos;
	float3 end;
	float3 speed;
	CWorldObject* target; // unit, feature or weapon projectile to intercept
	CUnit* owner;
	CWeapon* weapon;
	const WeaponDef* weaponDef;
};


/**
 * Base class for all projectiles originating from a weapon or having
 * weapon-properties. Uses data from a weapon definition.
 */
class CWeaponProjectile : public CProjectile
{
	CR_DECLARE(CWeaponProjectile);
public:
	enum {
		WEAPON_BASE_PROJECTILE           = (1 <<  0),
		WEAPON_BEAMLASER_PROJECTILE      = (1 <<  1),
		WEAPON_EMG_PROJECTILE            = (1 <<  2),
		WEAPON_EXPLOSIVE_PROJECTILE      = (1 <<  3),
		WEAPON_FIREBALL_PROJECTILE       = (1 <<  4),
		WEAPON_FLAME_PROJECTILE          = (1 <<  5),
		WEAPON_LARGEBEAMLASER_PROJECTILE = (1 <<  6),
		WEAPON_LASER_PROJECTILE          = (1 <<  7),
		WEAPON_LIGHTNING_PROJECTILE      = (1 <<  8),
		WEAPON_MISSILE_PROJECTILE        = (1 <<  9),
		WEAPON_STARBURST_PROJECTILE      = (1 << 10),
		WEAPON_TORPEDO_PROJECTILE        = (1 << 11),
	};

	CWeaponProjectile();
	CWeaponProjectile(const ProjectileParams& params, const bool isRay = false);
	virtual ~CWeaponProjectile();

	virtual void Collision();
	virtual void Collision(CFeature* feature);
	virtual void Collision(CUnit* unit);
	virtual void Update();
	/// @return 0=unaffected, 1=instant repulse, 2=gradual repulse
	virtual int ShieldRepulse(CPlasmaRepulser* shield, float3 shieldPos, float shieldForce, float shieldMaxSpeed) { return 0; }

	virtual void DrawOnMinimap(CVertexArray& lines, CVertexArray& points);

protected:
	void UpdateInterception();
	virtual void UpdateGroundBounce();
	bool TraveledRange();

public:
	/// true if we are a nuke and an anti is on the way
	bool targeted;
	const WeaponDef* weaponDef;

	CWorldObject* target;
	float3 targetPos;

	unsigned int weaponDefID;
	unsigned int cegID;

	int colorTeam;

protected:
	float3 startpos;

	int ttl;
	int bounces;
	bool keepBouncing;

public:
	void DependentDied(CObject* o);
	void PostLoad();
};

#endif /* WEAPON_PROJECTILE_H */
