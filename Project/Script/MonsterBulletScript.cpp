#include "pch.h"
#include "MonsterBulletScript.h"

MonsterBulletScript::MonsterBulletScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERBULLETSCRIPT)
	, m_TargetObject(nullptr)
	, ShotTime(0.f)
	, OffsetX(0.f, 0.f, 0.f)
	, ShootDir(0.f, 0.f, 0.f)
{
}

MonsterBulletScript::~MonsterBulletScript()
{
}

void MonsterBulletScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>(); // ī�޶�ũ��Ʈ �������� 
	//OffsetX = CameraScript->GetvRight(); //ī�޶��� x�����
	ShootDir = (MonsterScript->GetOwner()->Transform()->GetRelativePos() - CameraScript->GetOwner()->Transform()->GetRelativePos()).Normalize(); 

	Vec3 ParentPos = CameraScript->GetOwner()->Transform()->GetRelativePos(); // ī�޶� ��ġ
	Transform()->SetRelativeScale(Vec3(0.1f, 0.1f, 0.1f));
}

void MonsterBulletScript::tick()
{
	ShotTime += DT;

	Vec3 BulletPos = Transform()->GetRelativePos();
	BulletPos -= ShootDir * DT * 1000.f;
	Transform()->SetRelativePos(BulletPos);


	if (ShotTime > 5.0f)
	{
		ShotTime = 0.f;
		DestroyObject(GetOwner());
		MonsterScript->SetBulletBool(false);
	}
}

void MonsterBulletScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Empty" == _Other->GetOwner()->GetName())
	{
		DestroyObject(GetOwner());
		MonsterScript->SetBulletBool(false);

		CameraScript->SetHitPost(true);
	}
}