#include "pch.h"
#include "BossPlanets.h"
#include "CCameraScript.h"

BossPlanets::BossPlanets()
	: CScript((UINT)SCRIPT_TYPE::BOSSPLANETS)
{
}

BossPlanets::~BossPlanets()
{

}

void BossPlanets::begin()
{
	
}

void BossPlanets::tick()
{
	if (CameraScript != nullptr)
	{
		Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 CameraFront = CameraScript->GetvFront();
		Vec3 CameraRight = CameraScript->GetvRight();
	}

	if (Sirius != nullptr && BossScript != nullptr)
	{
		Vec3 BossPos = BossScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 SiriusPos = BossPos;
		SiriusPos.x = BossPos.x + 8000.f;
		Transform()->SetRelativePos(SiriusPos);
	}
	if (Volcanic != nullptr && BossScript != nullptr)
	{
		Vec3 BossPos = BossScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 VolcanicPos = BossPos;
		VolcanicPos.x = BossPos.x - 7000.f;
		Transform()->SetRelativePos(VolcanicPos);
	}
	//if (NarShaddaa != nullptr && BossScript != nullptr)
	//{
	//	Vec3 BossPos = BossScript->GetOwner()->Transform()->GetRelativePos();
	//	Vec3 NarShaddaaPos = BossPos;
	//	NarShaddaaPos.z = BossPos.z  + 5000.f;
	//	Transform()->SetRelativePos(NarShaddaaPos);
	//}
}
