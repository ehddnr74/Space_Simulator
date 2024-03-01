#include "pch.h"
#include "CPlayerScript.h"
#include "CMissileScript.h"
#include "CCameraScript.h"

CMissileScript::CMissileScript()
	: CScript((UINT)SCRIPT_TYPE::MISSILESCRIPT)
	, m_TargetObject(nullptr)
	, ShotTime(0.f)
	, OffsetX(0.f, 0.f, 0.f)
	, ShootDir(0.f, 0.f, 0.f)
{
}

CMissileScript::~CMissileScript()
{

}

void CMissileScript::begin()
{
	MissileEmpty = new CGameObject;
	MissileEmpty->SetName(L"MissileEmpty");
	MissileEmpty->AddComponent(new CTransform);
	MissileEmpty->AddComponent(new CMeshRender);
	MissileEmpty->Transform()->SetRelativeScale(Vec3(0.001f, 0.001f, 0.001f));
	//Empty->Transform()->SetRelativePos()
	MissileEmpty->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	MissileEmpty->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);

	MissileEmpty->AddComponent(new CCollider2D);
	MissileEmpty->Collider2D()->SetOffsetPos(Vec3(-100000.f, 0.f, 100000.f));
	MissileEmpty->Collider2D()->SetOffsetScale(Vec3(200000.f, 200000.f, 200000.f));

	SpawnGameObject(MissileEmpty, Vec3(0.f, 0.f, 0.f), L"Player");

	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	OffsetX = CameraScript->GetvRight();
	Vec3 OffsetY = CameraScript->GetvUp();
	ShootDir = CameraScript->GetvFront();
	//ShootUp = 

	Vec3 ParentPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	Vec3 ParentRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();

	Vec3 MissileRot = Transform()->GetRelativeRot();

	//ParentPos += OffsetX * 50.f;
	ParentPos += OffsetY * 100.f;
	ParentPos += ShootDir * 100.f;

	Transform()->SetRelativeScale(Vec3(50.0f, 50.0f, 50.0f));
	Transform()->SetRelativeRot(Vec3(ParentRot+MissileRot));
	Transform()->SetRelativePos(Vec3(ParentPos));
}

void CMissileScript::tick()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	Vec3 vFront = CameraScript->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 EmptyPos = MissileEmpty->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();

	EmptyPos = vPos + vFront * 100;
	//EmptyPos.y -= vUp.y * 70;
	MissileEmpty->Transform()->SetRelativePos(EmptyPos);

	ShotTime += DT;

		//if (m_TargetObject != nullptr)
		//{
		//	Vec3 TargetPos = m_TargetObject->Transform()->GetRelativePos();
		//	Vec3 MissilePos = Transform()->GetRelativePos();

		//	Vec3 Dir = MissilePos - TargetPos;

		//	MissilePos += Dir * DT * 1000.f;
		//	Transform()->SetRelativePos(MissilePos);
		//}

	//if (m_TargetObject == nullptr)
	//{
		Vec3 BulletPos = Transform()->GetRelativePos();
		BulletPos += ShootDir * DT * 1000.f;
		Transform()->SetRelativePos(BulletPos);


		if (ShotTime > 5.0f)
		{
			ShotTime = 0.f;
			DestroyObject(GetOwner());
		}

}

void CMissileScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* pOtherObject = _Other->GetOwner();

	if (L"House" == _Other->GetOwner()->GetName())
	{
		DestroyObject(GetOwner());
	}

	if (L"Monster" == _Other->GetOwner()->GetName())
	{
		DestroyObject(GetOwner());
	}

	if (L"BossEmpty" == _Other->GetOwner()->GetName())
	{
		DestroyObject(MissileEmpty);
		DestroyObject(GetOwner());
	}
}
