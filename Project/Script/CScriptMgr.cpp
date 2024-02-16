#include "pch.h"
#include "CScriptMgr.h"

#include "BulletScript.h"
#include "CCameraMoveScript.h"
#include "CCameraScript.h"
#include "CGravityScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CPlanet_Lotating.h"
#include "CPlayerScript.h"
#include "CTestScript.h"
#include "MeteoScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"BulletScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CCameraScript");
	_vec.push_back(L"CGravityScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CPlanet_Lotating");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CTestScript");
	_vec.push_back(L"MeteoScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"BulletScript" == _strScriptName)
		return new BulletScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CCameraScript" == _strScriptName)
		return new CCameraScript;
	if (L"CGravityScript" == _strScriptName)
		return new CGravityScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CPlanet_Lotating" == _strScriptName)
		return new CPlanet_Lotating;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CTestScript" == _strScriptName)
		return new CTestScript;
	if (L"MeteoScript" == _strScriptName)
		return new MeteoScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::ULLETSCRIPT:
		return new BulletScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERASCRIPT:
		return new CCameraScript;
		break;
	case (UINT)SCRIPT_TYPE::GRAVITYSCRIPT:
		return new CGravityScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::PLANET_LOTATING:
		return new CPlanet_Lotating;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::TESTSCRIPT:
		return new CTestScript;
		break;
	case (UINT)SCRIPT_TYPE::METEOSCRIPT:
		return new MeteoScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::ULLETSCRIPT:
		return L"BulletScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::CAMERASCRIPT:
		return L"CCameraScript";
		break;

	case SCRIPT_TYPE::GRAVITYSCRIPT:
		return L"CGravityScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::PLANET_LOTATING:
		return L"CPlanet_Lotating";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::TESTSCRIPT:
		return L"CTestScript";
		break;

	case SCRIPT_TYPE::METEOSCRIPT:
		return L"MeteoScript";
		break;

	}
	return nullptr;
}