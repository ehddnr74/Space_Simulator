#include "pch.h"
#include "BulletScript.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"

BulletScript::BulletScript()
	: CScript((UINT)SCRIPT_TYPE::BULLETSCRIPT)
	, m_TargetObject(nullptr)
	, ShotTime(0.f)
	, OffsetX(0.f, 0.f, 0.f)
	, ShootDir(0.f, 0.f, 0.f)
{
}

BulletScript::~BulletScript()
{
}

void BulletScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	OffsetX = CameraScript->GetvRight();
	ShootDir = CameraScript->GetvFront();

	Vec3 ParentPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	Vec3 ParentRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();

	ParentPos += OffsetX * 50.f;
	ParentPos += ShootDir * 500.f;

	Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
	Transform()->SetRelativeRot(Vec3(ParentRot));
	Transform()->SetRelativePos(Vec3(ParentPos));
}

void BulletScript::tick()
{
	ShotTime += DT;

	Vec3 BulletPos = Transform()->GetRelativePos();
	BulletPos += ShootDir * DT * 1500.f;
	Transform()->SetRelativePos(BulletPos);


	if (ShotTime > 2.0f)
	{
		ShotTime = 0.f;
		DestroyObject(GetOwner());
	}

}

void BulletScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* pOtherObject = _Other->GetOwner();

	if (L"House" == _Other->GetOwner()->GetName())
	{
		DestroyObject(GetOwner());
	}
}
