#include "pch.h"
#include "BlackholeScript.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"
#include "BossScript.h"

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
		//CameraPos = Vec3(23797.109f, -2210.932f, 990286.562f);
		PlayerScript->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
		CameraPos = Vec3(0.f, 0.f, 30500000.f);
		//CameraRot = Vec3(1.47715068f, 3.29867244f, 0.0349065848f);
		CameraScript->GetOwner()->Transform()->SetRelativePos(CameraPos);
		//CameraScript->GetOwner()->Transform()->SetRelativeRot(Vec3(XM_PI / 180.f, (XM_PI / 180.f), 0.f));
		//CameraScript->GetOwner()->Transform()->SetRelativeRot(CameraRot);

		Tele_in = false;
	}
}

void BlackholeScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Empty" == _Other->GetOwner()->GetName())
	{
		Tele_in = true;
		////Boss
		//{
		//	Ptr<CMeshData> BossStageMeshData = nullptr;
		//	CGameObject* Boss = nullptr;
		//
		//	BossStageMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\boss.fbx");
		//	//BossStageMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\House.mdat");
		//	Boss = BossStageMeshData->Instantiate();
		//
		//	Boss->AddComponent(new CCollider2D);
		//	Boss->AddComponent(new BossScript);
		//
		//	BossScript* BS = Boss->GetScript<BossScript>();
		//	BS->SetPlayerScript(PlayerScript);
		//
		//	Boss->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 50.f));
		//
		//	Boss->Transform()->SetRelativeRot(Vec3(144.2f, 51.559f, 43.7f));
		//
		//	//CameraScript->Transform()->SetRelativeRot(Vec3(0.f, -10.f, 0.f));
		//
		//	//Boss->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		//	//Boss->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
		//
		//	Boss->SetName(L"Boss");
		//	SpawnGameObject(Boss, Vec3(0.f, 0.f, 1000000.000f), L"Boss");
		//	//SpawnGameObject(Boss, Vec3(0.0f, 0.0f, 5000.f), L"Boss");
		//}
	}
}
