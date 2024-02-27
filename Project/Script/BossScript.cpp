#include "pch.h"
#include "BossScript.h"
#include "BossBulletScript.h"
#include "time.h"
#include "BossShiled.h"
#include "CPlanet_Lotating.h"
#include "BossPlanets.h"

BossScript::BossScript()
	: CScript((UINT)SCRIPT_TYPE::BOSSSCRIPT)
	, HP(100)
	, MoveTime(0.f)
	, Bulletbool(false)
	, ShotTime(3.0f)
	, RoomEffectCheck(false)

{
}

BossScript::~BossScript()
{
}

void BossScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	Vec3 BossPos = CameraPos;
	Vec3 CameraFront = CameraScript->GetvFront();
	BossPos += CameraFront * 8000.f;
	Transform()->SetRelativeScale(Vec3(250.f, 250.f, 250.f));
	Transform()->SetRelativeRot(Vec3(XM_PI / 3.7f, XM_PI / 1.33f, XM_PI / 36.f));
	Transform()->SetRelativePos(Vec3(BossPos));

	{	//Sirius
		CGameObject* Sirius = new CGameObject;
		Sirius->SetName(L"Sirius");
		Sirius->AddComponent(new CTransform);
		Sirius->AddComponent(new CMeshRender);
		Sirius->AddComponent(new CPlanet_Lotating);
		Sirius->AddComponent(new BossPlanets);

		BossPlanets* SBP = Sirius->GetScript<BossPlanets>();
		SBP->SetCameraScript(CameraScript);
		SBP->SetSirius(Sirius);
		SBP->SetBossScript(this);

		Sirius->Transform()->SetRelativeScale(Vec3(10000.f, 10000.f, 10000.f));
		Sirius->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		Sirius->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, -0.1f, 0.f));

		Sirius->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		Sirius->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SiriusMtrl"), 0);
		Sirius->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Sirius.jpg"));
		SpawnGameObject(Sirius, Vec3(0.f, 0.f, 30000000.f), L"Sirius");
	}

	{	//Volcanic
		CGameObject* Volcanic = new CGameObject;
		Volcanic->SetName(L"Volcanic");
		Volcanic->AddComponent(new CTransform);
		Volcanic->AddComponent(new CMeshRender);
		Volcanic->AddComponent(new CPlanet_Lotating);
		Volcanic->AddComponent(new BossPlanets);

		BossPlanets* VBP = Volcanic->GetScript<BossPlanets>();
		VBP->SetCameraScript(CameraScript);
		VBP->SetVolcanic(Volcanic);
		VBP->SetBossScript(this);
		

		Volcanic->Transform()->SetRelativeScale(Vec3(10000.f, 10000.f, 10000.f));
		Volcanic->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		Volcanic->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

		Volcanic->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		Volcanic->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"VolcanicMtrl"), 0);
		Volcanic->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Volcanic_01.png"));

		SpawnGameObject(Volcanic, Vec3(50000.f, 0.f, 30500000.f), L"Volcanic");
	}

	//{	//Volcanic_Lava
	//	CGameObject* Volcanic_Lava = new CGameObject;
	//	Volcanic_Lava->SetName(L"Volcanic_Lava");
	//	Volcanic_Lava->AddComponent(new CTransform);
	//	Volcanic_Lava->AddComponent(new CMeshRender);
	//	Volcanic_Lava->AddComponent(new CPlanet_Lotating);

	//	Volcanic_Lava->Transform()->SetRelativeScale(Vec3(20050.f, 20050.f, 20050.f));
	//	Volcanic_Lava->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

	//	Volcanic_Lava->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

	//	Volcanic_Lava->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//	Volcanic_Lava->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Volcanic_LavaMtrl"), 0);
	//	Volcanic_Lava->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Volcanic\\Volcanic_Lava.png"));

	//	SpawnGameObject(Volcanic_Lava, Vec3(50000.f, 0.f, 30500000.f), L"Volcanic_Lava");
	//}

	//{	//Nar_Shaddaa
	//	CGameObject* Nar_Shaddaa = new CGameObject;
	//	Nar_Shaddaa->SetName(L"Nar_Shaddaa");
	//	Nar_Shaddaa->AddComponent(new CTransform);
	//	Nar_Shaddaa->AddComponent(new CMeshRender);
	//	Nar_Shaddaa->AddComponent(new CPlanet_Lotating);
	//	Nar_Shaddaa->AddComponent(new BossPlanets);

	//	BossPlanets* NBP = Nar_Shaddaa->GetScript<BossPlanets>();
	//	NBP->SetCameraScript(CameraScript);
	//	NBP->SetNarShaddaa(Nar_Shaddaa);
	//	NBP->SetBossScript(this);

	//	Nar_Shaddaa->Transform()->SetRelativeScale(Vec3(20000.f, 20000.f, 20000.f));
	//	Nar_Shaddaa->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

	//	Nar_Shaddaa->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));



	//	Nar_Shaddaa->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//	Nar_Shaddaa->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Nar_ShaddaaDMtrl"), 0);
	//	Nar_Shaddaa->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Nar_Shaddaa01.png"));

	//	SpawnGameObject(Nar_Shaddaa, Vec3(50000.f, 400.000f, 30450000.f), L"Nar_Shaddaa");
	//}
}

void BossScript::tick()
{
	// 보스의 프레임마다 위치 조정 
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	Vec3 CameraRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();
	Vec3 BossPos = Transform()->GetRelativePos();
	Vec3 CameraFront = CameraScript->GetvFront();

	if (BossPos.z - CameraPos.z >= 12000.f)
	{
		return;
	}
	else
	{
		BossPos.z += CameraFront.z * DT * 1200.f;
	}
	Transform()->SetRelativePos(BossPos);

	if (RoomEffectCheck == false)
	{
		RoomEffectCheck = true;
		CreateRoomEffect();
	}

	//if (HP <= 0)
	//{
	//	DestroyObject(GetOwner());
	//}

	//ShotTime += DT;

	//if (ShotTime >= 5.0f && Bulletbool == false)
	//{
	//	ShotTime = 0.f;
	//	Bulletbool = true;
	//	//CreateBossBullet();
	//	//CreateBossMissile();
	//	//CreateBossRazer();
	//}

	switch (eBossState)
	{
	case BossScript::BossState::Razer:
		razer();
		break;
	case BossScript::BossState::Missile:
		missile();
		break;
	case BossScript::BossState::MonsterSpawn:
		monsterspawn();
		break;
	case BossScript::BossState::TelePort:
		teleport();
		break;
	case BossScript::BossState::ForceShield:
		forceshield();
		break;
	case BossScript::BossState::Die:
		die();
		break;
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
	SpawnGameObject(Bullet, BossPos, L"Monster");
}

void BossScript::CreateBossMissile()
{
	Ptr<CMeshData> pMeshData = nullptr;
	Missile = nullptr;

	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\boss_missile.fbx");
	Missile = pMeshData->Instantiate();

	Missile->AddComponent(new CCollider2D);
	Missile->AddComponent(new BossBulletScript);

	Missile->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));

	BossBulletScript* BBS = Missile->GetScript<BossBulletScript>();
	BBS->SetPlayerScript(PlayerScript);
	BBS->SetBossScript(this);

	Missile->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	Missile->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));

	Missile->SetName(L"Missile");
	Vec3 BossPos = Transform()->GetRelativePos();
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	SpawnGameObject(Missile, BossPos, L"Monster");
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

	SpawnGameObject(Razer, BossPos, L"Monster");
}

void BossScript::CreateRoomEffect()
{
	CGameObject* RoomEffect = new CGameObject;
	RoomEffect->SetName(L"RoomEffect");
	
	RoomEffect->AddComponent(new CTransform);
	RoomEffect->AddComponent(new CMeshRender);
	RoomEffect->AddComponent(new BossShiled);
	BossShiled* BS = RoomEffect->GetScript<BossShiled>();
	BS->SetCameraScript(CameraScript);


	RoomEffect->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	RoomEffect->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ShiledMtrl"), 0);
	RoomEffect->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Shield\\Shiled3.jpg"));

	RoomEffect->Transform()->SetRelativeScale(Vec3(10000.f, 10000.f, 10000.f));

	Vec3 BossPos = Transform()->GetRelativePos();
	BossPos.y += 500.f;

	SpawnGameObject(RoomEffect, BossPos, 0);
}



void BossScript::razer()
{
}

void BossScript::missile()
{
}

void BossScript::monsterspawn()
{
}

void BossScript::teleport()
{
}

void BossScript::forceshield()
{
}

void BossScript::die()
{
}