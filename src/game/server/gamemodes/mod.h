/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_GAMEMODES_CTF_H
#define GAME_SERVER_GAMEMODES_CTF_H
#include <game/server/gamecontroller.h>
#include <game/server/entity.h>

class CGameControllerMOD : public IGameController
{
public:
	class CFlag *m_apFlags[2];

	CGameControllerMOD(class CGameContext *pGameServer);
	virtual void DoWincheck();
	virtual bool CanBeMovedOnBalance(int ClientID);
	virtual void Snap(int SnappingClient);
	virtual void Tick();

	virtual bool OnEntity(const char* pName, vec2 Pivot, vec2 P0, vec2 P1, vec2 P2, vec2 P3, int PosEnv);
	virtual int OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon);
};

#endif

