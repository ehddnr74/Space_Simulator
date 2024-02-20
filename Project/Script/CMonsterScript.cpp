#include "pch.h"
#include "CMonsterScript.h"
#include "CCameraScript.h"
#include "time.h"


CMonsterScript::CMonsterScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
	, HP(100)
	, RandomPos(1)
	, MoveTime(0.f)

{
}

CMonsterScript::~CMonsterScript()
{
}



void CMonsterScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();

	//Vec3 MonsterPos = Transform()->GetRelativePos();
	//Vec3 CameraFront = CameraScript->GetvFront();

	//MonsterPos.z = CameraFront.z * 3000;

	//Transform()->SetRelativePos(MonsterPos);
}

void CMonsterScript::tick()
{
	if (HP <= 0) // 추후 폭발 애니메이션 추가 // 셰이더 맞으면 빨갛게 하이라이트 
	{
		DestroyObject(GetOwner());
	}

	Vec3 MonsterPos = Transform()->GetRelativePos();
	Vec3 CameraRight = CameraScript->GetvRight();
	Vec3 CameraFront = CameraScript->GetvFront();

	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	Vec3 CameraRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();
	Transform()->SetRelativeRot(CameraRot);

	
	if (abs(MonsterPos.z - CameraPos.z) <= abs(CameraFront.z * 1000))
	{
		MoveTime += DT;
		if (MoveTime >= 1.5f)
		{
			MoveTime = 0.f;
			srand(time(NULL));
			RandomPos = rand() % 2 + 1;
		}

		if (RandomPos == 1)
		{
			MonsterPos -= CameraRight * DT * 100;
			Transform()->SetRelativePos(MonsterPos);
		}
		else // RandomPos == 2 인 경우 
		{
			MonsterPos += CameraRight * DT * 100;
			Transform()->SetRelativePos(MonsterPos);
		}
	}
	else
	{
		Vec3 TarGetDir = (MonsterPos - CameraPos).Normalize();

		MonsterPos -= TarGetDir * DT * 100.f;

		Transform()->SetRelativePos(MonsterPos);
	}

}

void CMonsterScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Bullet" == _Other->GetOwner()->GetName()) //5방컷
	{
		HP -= 10;
	}
}

