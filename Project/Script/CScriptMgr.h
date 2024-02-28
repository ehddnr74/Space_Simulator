#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	LACKHOLESCRIPT,
	OSSBULLETSCRIPT,
	OSSPLANETS,
	OSSSCRIPT,
	OSSSHILED,
	ULLETSCRIPT,
	CAMERAMOVESCRIPT,
	CAMERASCRIPT,
	GRAVITYSCRIPT,
	MISSILESCRIPT,
	MONSTERSCRIPT,
	PLANET_LOTATING,
	PLAYERSCRIPT,
	TESTSCRIPT,
	EBUGSCRIPT,
	ADING,
	ITPOSTSCRIPT,
	YPERLOOPSCRIPT,
	ETEOSCRIPT,
	ONSTERBULLETSCRIPT,
	HYPERLOOPSCRIPT,
	METEOSCRIPT,
	MONSTERBULLETSCRIPT,
	BOSSPLANETS,
	BOSSBULLETSCRIPT,
	BLACKHOLESCRIPT,
	FADING,
	HITPOSTSCRIPT,
	DEBUGSCRIPT,
	BULLETSCRIPT,
	BOSSSCRIPT,
	BOSSSHILED,
	END,
};

using namespace std;

class CScript;

class CScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static CScript * GetScript(const wstring& _strScriptName);
	static CScript * GetScript(UINT _iScriptType);
	static const wchar_t * GetScriptName(CScript * _pScript);
};
