#include "pch.h"
#include "BlackholeScript.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"

BlackholeScript::BlackholeScript()
	: CScript((UINT)SCRIPT_TYPE::BLACKHOLESCRIPT)
{
}

BlackholeScript::~BlackholeScript()
{
}

void BlackholeScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
}

void BlackholeScript::tick()
{
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

	if (Tele_in)
	{
		CameraPos = Vec3(1637.662f, 1713.724f, 1005604.875f);
		CameraScript->GetOwner()->Transform()->SetRelativePos(CameraPos);
		Tele_in = false;
	}
}

void BlackholeScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Empty" == _Other->GetOwner()->GetName())
	{
		Tele_in = true;
	}
}
