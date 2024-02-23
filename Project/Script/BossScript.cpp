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
