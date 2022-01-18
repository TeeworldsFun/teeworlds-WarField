/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "supgun.h"

#include <base/math.h>
#include <base/vmath.h>
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>

#include "../../entities/projectile.h"

CRocket::CRocket(CGameWorld *pGameWorld, int Owner, vec2 Pos, vec2 Dir)
	: CEntity(pGameWorld, CGameWorld::ENTTYPE_SUPGUN)
{
	m_Direction = Dir;
	m_LifeSpan = Server()->TickSpeed() * 2.5f;
	m_StartTick = Server()->Tick();
	m_Explosive = true;
	m_StartPos = Pos;

    m_Owner = Owner;

	GameWorld()->InsertEntity(this);
}

void CRocket::Reset()
{
	GameServer()->m_World.DestroyEntity(this);
}

void CRocket::ProcessExplosion()
{
	GameServer()->m_World.DestroyEntity(this);
}

vec2 CRocket::GetPosAtTime(float Time)
{
	float Curvature = 0;
	float Speed = 0;

	Curvature = 0;
	Speed = 5;

	return CalcPos(m_Pos, m_Direction, Curvature, Speed, Time);
}

void CRocket::Tick()
{
	float Pt = (Server()->Tick()-m_StartTick-1)/(float)Server()->TickSpeed();
	float Ct = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();
	vec2 PrevPos = GetPosAtTime(Pt);
	vec2 CurPos = GetPosAtTime(Ct);
	int Collide = GameServer()->Collision()->IntersectLine(PrevPos, CurPos, &CurPos, 0);
	CCharacter *OwnerChar = GameServer()->GetPlayerChar(m_Owner);
	CCharacter *TargetChr = GameServer()->m_World.IntersectCharacter(PrevPos, CurPos, 4.0f, CurPos, OwnerChar);
	vec2 WitchPortalAt;

	m_Pos = CurPos;

	m_LifeSpan--;

	if(TargetChr || Collide || m_LifeSpan < 0 || GameLayerClipped(CurPos))
	{
		if(m_LifeSpan >= 0)
			GameServer()->CreateSound(CurPos, SOUND_RIFLE_FIRE);
		
		ProcessExplosion();
	}
}

void CRocket::TickPaused()
{
	++m_StartTick;
}

void CRocket::FillInfo(CNetObj_Projectile *pProj)
{
	pProj->m_X = (int)m_Pos.x;
	pProj->m_Y = (int)m_Pos.y;
	pProj->m_VelX = (m_Direction.x*20.0f);
	pProj->m_VelY = (m_Direction.y*20.0f);
	pProj->m_StartTick = Server()->Tick();
	pProj->m_Type = WEAPON_GUN;
}

void CRocket::Snap(int SnappingClient)
{
	if (NetworkClipped(SnappingClient))
		return;
	
	
	CNetObj_Laser *pObj = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(
		NETOBJTYPE_LASER, m_ID, sizeof(CNetObj_Laser)));
	
	if(!pObj)
		return;
	
	pObj->m_X = (int)m_Pos.x;
	pObj->m_Y = (int)m_Pos.y;
	pObj->m_FromX = (int)m_Pos.x;
	pObj->m_FromY = (int)m_Pos.y;
	pObj->m_StartTick = m_StartTick;
}
