#include <engine/shared/config.h>

#include <game/mapitems.h>

#include <game/server/entities/character.h>
#include <game/server/entities/flag.h>
#include <game/server/player.h>
#include <game/server/gamecontext.h>
#include "mod.h"

CGameControllerMOD::CGameControllerMOD(class CGameContext *pGameServer)
: IGameController(pGameServer)
{
	m_apFlags[0] = 0;
	m_apFlags[1] = 0;
	m_pGameType = "Killer";
	m_GameFlags = GAMEFLAG_TEAMS|GAMEFLAG_FLAGS;
	m_aTeamscore[TEAM_RED] = 5000;
	m_aTeamscore[TEAM_BLUE] = 5000;
}

bool CGameControllerMOD::OnEntity(int Index, vec2 Pos)
{
}

void CGameControllerMOD::DoWincheck()
{
	if(m_GameOverTick == -1 && !m_Warmup)
	{
		// check score win condition
		if(((m_aTeamscore[TEAM_RED] <= 0 || m_aTeamscore[TEAM_BLUE] <= 0)) ||
			(g_Config.m_SvTimelimit > 0 && (Server()->Tick()-m_RoundStartTick) >= g_Config.m_SvTimelimit*Server()->TickSpeed()*60))
		{
			if(m_SuddenDeath)
			{
				if(m_aTeamscore[TEAM_RED]/100 != m_aTeamscore[TEAM_BLUE]/100)
					EndRound();
			}
			else
			{
				if(m_aTeamscore[TEAM_RED] != m_aTeamscore[TEAM_BLUE])
					EndRound();
				else
					m_SuddenDeath = 1;
			}
		}
	}
}

void CGameControllerMOD::Snap(int SnappingClient)
{
	IGameController::Snap(SnappingClient);

	CNetObj_GameData *pGameDataObj = (CNetObj_GameData *)Server()->SnapNewItem(NETOBJTYPE_GAMEDATA, 0, sizeof(CNetObj_GameData));
	if(!pGameDataObj)
		return;

    CFlag *RedF = m_apFlags[TEAM_RED];
    CFlag *BlueF = m_apFlags[TEAM_BLUE];

    if(RedF)
    {
        pGameDataObj->m_TeamscoreRed = RedF->GetHealth();
        m_aTeamscore[TEAM_RED] = RedF->GetHealth();
        pGameDataObj->m_FlagCarrierRed = FLAG_ATSTAND;
    }
    else
        pGameDataObj->m_FlagCarrierBlue = FLAG_MISSING;

    if(BlueF)
    {
        pGameDataObj->m_TeamscoreBlue = BlueF->GetHealth();
        m_aTeamscore[TEAM_BLUE] = BlueF->GetHealth();
        pGameDataObj->m_FlagCarrierBlue = FLAG_ATSTAND;
    }
    else
        pGameDataObj->m_FlagCarrierBlue = FLAG_MISSING;

}

void CGameControllerMOD::Tick()
{
	IGameController::Tick();

	if(GameServer()->m_World.m_ResetRequested || GameServer()->m_World.m_Paused)
		return;

	for(int fi = 0; fi < 2; fi++)
	{
		CFlag *F = m_apFlags[fi];

		if(!F)
			continue;
	}
}
