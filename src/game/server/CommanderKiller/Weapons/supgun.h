/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_ENTITIES_ROCKET_H
#define GAME_SERVER_ENTITIES_ROCKET_H

#include "../../entity.h"

class CRocket : public CEntity
{
public:
	CRocket(CGameWorld *pGameWorld, int Owner, vec2 Pos, vec2 Dir);

	vec2 GetPosAtTime(float Time);
	void FillInfo(CNetObj_Projectile *pProj);

	virtual void Reset();
	virtual void Tick();
	virtual void TickPaused();
	virtual void Snap(int SnappingClient);

private:
	void ProcessExplosion();

	vec2 m_Direction;
	int m_LifeSpan;
	int m_StartTick;
	bool m_Explosive;

    int m_Owner;

	vec2 m_StartPos;
	bool m_TakeDamageMode;
};

#endif // GAME_SERVER_ENTITIES_ROCKET_H
