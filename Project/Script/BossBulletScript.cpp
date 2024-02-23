#include "pch.h"
#include "BossBulletScript.h"

BossBulletScript::BossBulletScript()
	: CScript((UINT)SCRIPT_TYPE::BOSSBULLETSCRIPT)
	, m_TargetObject(nullptr)
	, ShotTime(0.f)
	, BulletLife(0.f)
	, OffsetX(0.f, 0.f, 0.f)
	, ShootDir(0.f, 0.f, 0.f)
{
}

BossBulletScript::~BossBulletScript()
{
}

void BossBulletScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>(); // ī�޶�ũ��Ʈ �������� 
	ShootDir = (mBossScript->GetOwner()->Transform()->GetRelativePos() - CameraScript->GetOwner()->Transform()->GetRelativePos()).Normalize();

	Vec3 ParentPos = CameraScript->GetOwner()->Transform()->GetRelativePos(); // ī�޶� ��ġ
	//Transform()->SetRelativeScale(Vec3(0.1f, 0.1f, 0.1f));
}

void BossBulletScript::tick()
{
	ShotTime += DT;

	Vec3 BulletPos = Transform()->GetRelativePos();
	BulletPos -= ShootDir * DT * 500.f;
	Transform()->SetRelativePos(BulletPos);


	if (ShotTime > 5.0f)
	{
		ShotTime = 0.f;
		mBossScript->SetBulletBool(false);
		BulletCheck = true;
	}

	if (BulletCheck)
	{
		BulletLife += DT;

		if (BulletLife > 10.f)
		{
			DestroyObject(GetOwner());
			BulletCheck = false;
			BulletLife = 0.f;
		}
	}
}

void BossBulletScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Empty" == _Other->GetOwner()->GetName())
	{
		DestroyObject(GetOwner());
		mBossScript->SetBulletBool(false);
	}
}
