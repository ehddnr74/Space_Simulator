#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	LACKHOLESCRIPT,
	OSSBULLETSCRIPT,
	OSSSCRIPT,
	ULLETSCRIPT,
	CAMERAMOVESCRIPT,
	CAMERASCRIPT,
	GRAVITYSCRIPT,
	MISSILESCRIPT,
	MONSTERSCRIPT,
	PLANET_LOTATING,
	PLAYERSCRIPT,
	TESTSCRIPT,
	YPERLOOPSCRIPT,
	ETEOSCRIPT,
	ONSTERBULLETSCRIPT,
	BLACKHOLESCRIPT,
	BOSSBULLETSCRIPT,
	BOSSSCRIPT,
	BULLETSCRIPT,
	HYPERLOOPSCRIPT,
	METEOSCRIPT,
	MONSTERBULLETSCRIPT,
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
