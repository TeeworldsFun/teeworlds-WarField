#ifndef GAME_SERVER_CK_TANK_H
#define GAME_SERVER_CK_TANK_H

class CTank : public CEntity
{
public:
	CTank(CGameWorld *pGameWorld, vec2 Pos);

	int m_ExitTick;
	void Reset();
	void Tick();
	void Snap(int SnappingClient);
	void GiveEvent();
	void SearchChar();
	bool TestBox(vec2 Pos, vec2 Size);
	void MoveBox(vec2* pInoutPos, vec2* pInoutVel, vec2 Size, float Elasticity);

private:
	CCharacter* m_pTank;
    CPlayer* m_pPlayer;
	bool m_IsDropped;
	bool m_IsTaken;
	int m_DropTick;

	vec2 m_StartPos;

	vec2 m_Vel;

    vec2 m_aFrom[5];
    vec2 m_aTo[5];

    int m_aIDs[5];
};

#endif
