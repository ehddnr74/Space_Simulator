#include "pch.h"
#include "BossScript.h"
#include "BossBulletScript.h"
#include "time.h"

BossScript::BossScript()
	: CScript((UINT)SCRIPT_TYPE::BOSSSCRIPT)
	, HP(100)
	, RandomPos(1)
	, MoveTime(0.f)
	, Bulletbool(false)
	, ShotTime(3.0f)
	, ContactTime(0.f)
	, ContackFinish(false)
	, Bossnear(false)
	, BossnearTime(0.f)
{
}

BossScript::~BossScript()
{
}

void BossScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
}

void BossScript::tick()
{
	Vec3 CameraPos = CameraScript->Transform()->GetRelativePos();
	// 카메라와 보스 거리 계산
	float Distance = Transform()->GetRelativePos().z - CameraScript->Transform()->GetRelativePos().z;

	if (ContackFinish == false)
	{
		ContactTime += DT;
	}
	//if (ContackFinish == false && 0.f <= ContactTime && ContactTime <= 2.25f)
	//{
	//	Vec3 CameraRot = CameraScript->Transform()->GetRelativeRot();
	//	if (CameraRot.y >= -(XM_PI / 2.4))
	//	{
	//		CameraRot.y -= DT * 0.5f;
	//			CameraScript->Transform()->SetRelativeRot(CameraRot);
	//	}
	//	
	//}
	//if (ContackFinish == false && 2.25f <= ContactTime && ContactTime <= 4.0f)
	//{
	//	Vec3 CameraRot = CameraScript->Transform()->GetRelativeRot();
	//	CameraRot.y -= DT * 0.5f;
	//	CameraScript->Transform()->SetRelativeRot(CameraRot);
	//}
	if (Bossnear == false && ContackFinish == false && ContactTime >= 1.5f && CameraPos.z <= 998000.f)
	{
		if(CameraPos.z >=997900.f)
			Bossnear = true;

		Vec3 CameraFront = CameraScript->GetOwner()->Transform()->GetRelativeDir(DIR_TYPE::FRONT);

		CameraPos += CameraFront * DT * 2000.f;
		CameraScript->Transform()->SetRelativePos(CameraPos);

		//ContactBoss();
	}

	if (ContackFinish == false && Bossnear)
	{
		BossnearTime += DT;
		if (BossnearTime >= 8.0f)
		{
			ContackFinish = true;
			CameraScript->Transform()->SetRelativePos(Vec3(23797.109f, -2210.932f, 990286.562f));
			PlayerScript->Transform()->SetRelativeScale(0.3f, 0.3f, 0.3f);
		}
	}
	
	

	//if (ContackFinish == false && ContactTime > 8.5f)
	//{
	//	CameraScript->Transform()->SetRelativePos(Vec3(23797.109f, -2210.932f, 990286.562f));
	//	ContackFinish = true;
	//	ContactTime = 0.0f;
	//}
	
	//Vec3 Rot = Transform()->GetRelativeRot();
	//Rot.z += DT * 1.0f;
	//
	//Transform()->SetRelativeRot(Rot);

	ShotTime += DT;

	if (HP <= 0)
	{
		DestroyObject(GetOwner());
	}

	if (ShotTime >= 5.0f && Bulletbool == false)
	{
		ShotTime = 0.f;
		Bulletbool = true;
		//CreateBossBullet();
		//CreateBossMissile();
		CreateBossRazer();
	}
}

void BossScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Bullet" == _Other->GetOwner()->GetName())
	{
		HP -= 10;
	}
}

void BossScript::CreateBossBullet()
{
	Ptr<CMeshData> BulletMeshData = nullptr;
	Bullet = nullptr;

	BulletMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\08_Uranus.mdat");
	Bullet = BulletMeshData->Instantiate();

	Bullet->AddComponent(new CCollider2D);
	Bullet->AddComponent(new BossBulletScript);

	Bullet->Transform()->SetRelativeScale(Vec3(0.1f, 0.1f, 0.1f));

	BossBulletScript* BBS = Bullet->GetScript<BossBulletScript>();
	BBS->SetPlayerScript(PlayerScript);
	BBS->SetBossScript(this);

	Bullet->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	Bullet->Collider2D()->SetOffsetScale(Vec3(10.f, 10.f, 10.f));
	Bullet->SetName(L"BossBullet");

	Vec3 BossPos = Transform()->GetRelativePos();
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	SpawnGameObject(Bullet, BossPos, L"Boss");
}

void BossScript::CreateBossMissile()
{
	Ptr<CMeshData> pMeshData = nullptr;
	Missile = nullptr;

	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\boss_missile.fbx");
	Missile = pMeshData->Instantiate();

	Missile->AddComponent(new CCollider2D);
	Missile->AddComponent(new BossBulletScript);

	Missile->Transform()->SetRelativeScale(Vec3(1000.f, 1000.f, 1000.f));

	BossBulletScript* BBS = Missile->GetScript<BossBulletScript>();
	BBS->SetPlayerScript(PlayerScript);
	BBS->SetBossScript(this);

	Missile->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	Missile->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));

	Missile->SetName(L"Missile");
	Vec3 BossPos = Transform()->GetRelativePos();
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	SpawnGameObject(Missile, BossPos, L"Boss");
}

void BossScript::CreateBossRazer()
{
	CGameObject* Razer = new CGameObject;
	Razer->SetName(L"Razer");

	Razer->AddComponent(new CTransform);
	Razer->AddComponent(new CMeshRender);
	Razer->AddComponent(new CCollider2D);
	Razer->AddComponent(new BossBulletScript);

	Razer->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	Razer->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"RazerMtrl"), 0);

	Razer->Transform()->SetRelativeScale(Vec3(500.f, 10.f, 10.f));

	BossBulletScript* BBS = Razer->GetScript<BossBulletScript>();
	BBS->SetPlayerScript(PlayerScript);
	BBS->SetBossScript(this);

	Razer->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	//Razer->Collider2D()->SetOffsetScale(Vec3(20.f, 20.f, 500.f));

	Vec3 BossPos = Transform()->GetRelativePos();
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

	SpawnGameObject(Razer, BossPos, L"Boss");
}

void BossScript::ContactBoss()
{
	Vec3 CameraPos = CameraScript->Transform()->GetRelativePos();
	Vec3 CameraFront = CameraScript->GetvFront();
	Vec3 BossPos = Transform()->GetRelativePos();

	//if (CameraPos.y - BossPos.y < 1500.f)
	//{
	//	CameraPos.x += DT * 200.f;
	//	CameraScript->Transform()->SetRelativePos(CameraPos);
	//}

	Vec3 CameraToBossDir = (BossPos - CameraPos).Normalize();
	CameraPos -= -CameraToBossDir * DT * 400.f;

	CameraScript->Transform()->SetRelativePos(CameraPos);
	
}
