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
	Vec3 CameraRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();


	if (Tele_in)
	{
		CameraPos = Vec3(23797.109f, -2210.932f, 990286.562f);
		//CameraRot = Vec3(1.47715068f, 3.29867244f, 0.0349065848f);
		CameraScript->GetOwner()->Transform()->SetRelativePos(CameraPos);
		//CameraScript->GetOwner()->Transform()->SetRelativeRot(CameraRot);

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
