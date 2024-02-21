#include "pch.h"
#include "TestLevel.h"

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CCollisionMgr.h>

#include <Script\CPlayerScript.h>
#include <Script\CMonsterScript.h>
#include <Script\CCameraScript.h>
#include <Script\CPlanet_Lotating.h>
#include <Script\MeteoScript.h>
#include <Script\BlackholeScript.h>

#include "CLevelSaveLoad.h"


#include <Engine/CSetColorShader.h>

//a

void CreateTestLevel()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	// Layer 이름설정
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"Tile");
	pCurLevel->GetLayer(2)->SetName(L"Player");
	pCurLevel->GetLayer(3)->SetName(L"Monster");
	pCurLevel->GetLayer(4)->SetName(L"PlayerProjectile");
	pCurLevel->GetLayer(5)->SetName(L"MonsterProjectile");
	pCurLevel->GetLayer(6)->SetName(L"sun");
	pCurLevel->GetLayer(7)->SetName(L"blackhole");
	pCurLevel->GetLayer(8)->SetName(L"Volcanic");
	pCurLevel->GetLayer(9)->SetName(L"Nar_Shaddaa");
	pCurLevel->GetLayer(31)->SetName(L"ViewPort UI");


	// Main Camera Object 생성
	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName(L"MainCamera");

	pMainCam->AddComponent(new CTransform);
	pMainCam->AddComponent(new CCamera);
	pMainCam->AddComponent(new CCameraScript);

	pMainCam->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	pMainCam->Camera()->SetCameraIndex(0);		// MainCamera 로 설정
	pMainCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
	pMainCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.

	//pMainCam->Transform()->SetRelativeRot(-XM_PI * 1.6, XM_PI * 3, 0.f);

	SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), 0);
	pMainCam->Transform()->SetMainCamera(pMainCam);

	//// UI cameara
	////CGameObject* pUICam = new CGameObject;
	////pUICam->SetName(L"UICamera");

	////pUICam->AddComponent(new CTransform);
	////pUICam->AddComponent(new CCamera);

	////pUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	////pUICam->Camera()->SetCameraIndex(1);		// Sub 카메라로 지정
	////pUICam->Camera()->SetLayerMask(31, true);	// 31번 레이어만 체크

	////SpawnGameObject(pUICam, Vec3(0.f, 0.f, 0.f), 0);


	// SkyBox 추가
	CGameObject* pSkyBox = new CGameObject;
	pSkyBox->SetName(L"SkyBox");

	pSkyBox->AddComponent(new CTransform);
	pSkyBox->AddComponent(new CSkyBox);

	pSkyBox->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
	pSkyBox->SkyBox()->SetSkyBoxType(SKYBOX_TYPE::SPHERE);
	pSkyBox->SkyBox()->SetSkyBoxTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\Space.png"));

	SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), L"Player");

	// 광원 추가
	CGameObject* pLightObj = new CGameObject;
	pLightObj->SetName(L"Point Light");

	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight3D);

	pLightObj->Transform()->SetRelativeRot(Vec3(XM_PI/* / 4.f*/, XM_PI /*/ 4.f*/, XM_PI));//0.f));
	//pLightObj->Light3D()->SetLightType(LIGHT_TYPE::POINT);
	pLightObj->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightObj->Light3D()->SetRadius(100000.f);
	pLightObj->Light3D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLightObj->Light3D()->SetLightAmbient(Vec3(0.f, 0.f, 0.f));

	SpawnGameObject(pLightObj, Vec3(/*-10000.*/0.f, 0.f, 0.f), 0);

	//CGameObject* pObj = new CGameObject;
	//pObj->SetName(L"Directional Light");
	//
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//
	//pObj->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);


	//SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);

	// ============
	// FBX Loading
	// ============	




	Ptr<CMeshData> pMeshData = nullptr;
	CGameObject* Plane = nullptr;

	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\untitled.fbx");
	pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\untitled.mdat");
	Plane = pMeshData->Instantiate();
	Plane->Transform()->SetRelativeScale(Vec3(0.3f, 0.3f, 0.3f));
	//pObj->Animator3D()->CreateAnimation(L"Walk", 0, 2, 7);
	//pObj->Animator3D()->Play(L"Walk", true);
	Plane->Transform()->SetRelativeRot(Vec3(XM_PI / 2.2f, XM_PI * 1.05, XM_PI / 90.f));
	//Plane->Transform()->SetRelativeRot(Vec3(0.f,0.f,0.f));
	Plane->AddComponent(new CPlayerScript);



	CCameraScript* CCS = pMainCam->GetScript<CCameraScript>();
	CCS->SetTarget(Plane);


	//Plane->AddComponent(new CCollider2D);
	//Plane->Collider2D()->SetOffsetPos(Vec3(0.f, -300.f, 0.f));
	//Plane->Collider2D()->SetOffsetScale(Vec3(1000.f,1000.f, 1000.f));
	Plane->SetName(L"SpaceShip");
	SpawnGameObject(Plane, Vec3(53.f, -170.f, 500.f), L"Player");

	//Plane->AddChild(pMainCam);


	//CGameObject* Muzzle = new CGameObject;
	//Muzzle->SetName(L"Muzzle");
	//Muzzle->AddComponent(new CTransform);
	//Muzzle->AddComponent(new CMeshRender);

	//Muzzle->Transform()->SetRelativeScale(Vec3(0.1f, 0.1f, 0.1f));
	//Muzzle->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));
	//Muzzle->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//Muzzle->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);

	//Muzzle->AddComponent(new CCollider2D);
	//Muzzle->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	//Muzzle->Collider2D()->SetOffsetScale(Vec3(1000.f,1000.f, 1000.f));

	//SpawnGameObject(Muzzle, Vec3(-1.f,-909.f,-233.f), 0);

	//Plane->AddChild(Muzzle);
	pMainCam->AddChild(Plane);

	{
		Ptr<CMeshData> MonsterMeshData = nullptr;
		CGameObject* Monster = nullptr;

		MonsterMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Enemy.fbx");
		//HouseMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\test78678678.mdat");
		Monster = MonsterMeshData->Instantiate();
		Monster->AddComponent(new CMonsterScript);
		CMonsterScript* MS = Monster->GetScript<CMonsterScript>();
		CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();
		MS->SetPlayerScript(CPS);
		//CPlayerScript* PS = Plane->GetScript<CPlayerScript>();
		//PS->SetEnemy(pHouse);
		Monster->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 50.f));
		Monster->Transform()->SetRelativeRot(Vec3(50.f, 0.f, 0.f));
		Monster->AddComponent(new CCollider2D);
		Monster->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		Monster->Collider2D()->SetOffsetScale(Vec3(8.f, 8.f, 8.f));
		Monster->SetName(L"Monster");
		SpawnGameObject(Monster, Vec3(0.f, 0.f, 3000.f), L"Monster");
		MS->begin();

	}

		//Ptr<CMeshData> Meteo1MeshData = nullptr;
		//CGameObject* pMeteo1 = nullptr;
		//Meteo1MeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\04_meteo.fbx");

		////for (int i = 0; i < 10; ++i)
		////{
		////MeteoMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\01_meteo.mdat");
		//	pMeteo1 = Meteo1MeshData->Instantiate();
		//	pMeteo1->AddComponent(new MeteoScript);
		////MeteoScript * MS = pMeteo->GetScript<MeteoScript>();
		////MS->begin();
		////Vec3 MeteoPosition = MS->GetSpawnPosition();
		//	pMeteo1->Transform()->SetRelativeScale(Vec3(100.0f, 100.0f, 100.0f));
		////pMeteo->AddComponent(new CCollider2D);
		////pMeteo->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		////pMeteo->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
		//	pMeteo1->SetName(L"Meteo");
		////SpawnGameObject(pMeteo, Vec3(MeteoPosition), L"Monster");
		//SpawnGameObject(pMeteo1, Vec3(400, 600, 1200), L"Monster");
		////}


		//Ptr<CMeshData> Meteo2MeshData = nullptr;
		//CGameObject* pMeteo2 = nullptr;
		//Meteo2MeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\04_meteo.fbx");
		////for (int i = 0; i < 10; ++i)
		////{
		//	//MeteoMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\01_meteo.mdat");
		//	pMeteo2 = Meteo2MeshData->Instantiate();
		//	pMeteo2->AddComponent(new MeteoScript);
		//	//MeteoScript * MS = pMeteo->GetScript<MeteoScript>();
		//	//MS->begin();
		//	//Vec3 MeteoPosition = MS->GetSpawnPosition();
		//	pMeteo2->Transform()->SetRelativeScale(Vec3(100.0f, 100.0f, 100.0f));
		//	//pMeteo->AddComponent(new CCollider2D);
		//	//pMeteo->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		//	//pMeteo->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
		//	pMeteo2->SetName(L"Meteo");
		//	//SpawnGameObject(pMeteo, Vec3(MeteoPosition), L"Monster");
		//	SpawnGameObject(pMeteo2, Vec3(-400, 600, 1200), L"Monster");
		////}





	//{

	//	Ptr<CMeshData> HouseMeshData2 = nullptr;
	//	CGameObject* pHouse2 = nullptr;

	//	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\SpaceShuttle.fbx");
	//	HouseMeshData2 = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\House.mdat");
	//	pHouse2 = HouseMeshData2->Instantiate();
	//	pHouse2->Transform()->SetRelativeScale(Vec3(0.5f, 0.5f, 0.5f));
	//	pHouse2->AddComponent(new CCollider2D);
	//	pHouse2->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	//	pHouse2->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
	//	pHouse2->SetName(L"House2");
	//	SpawnGameObject(pHouse2, Vec3(1500.f, 2500.f, 3000.f), L"Monster");
	//}


		//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\Monster.mdat");		
		//for (int i = 0; i < 10; ++i)
		//{
		//	pObj = pMeshData->Instantiate();
		//	pObj->Animator3D()->CreateAnimation(L"Walk", 0, 2, 7);
		//	pObj->Animator3D()->Play(L"Walk", true);
		//	pObj->SetName(L"Monster");
		//	SpawnGameObject(pObj, Vec3((i + 1) * 50.f, 200.f, 500.f), 0);
		//}


	//// LandScape Object
	//CGameObject* pLandScape = new CGameObject;
	//pLandScape->SetName(L"LandScape");

	//pLandScape->AddComponent(new CTransform);
	//pLandScape->AddComponent(new CLandScape);

	//pLandScape->Transform()->SetRelativeScale(Vec3(500.f, 3000.f, 500.f));

	//pLandScape->LandScape()->SetFace(64, 64);
	//pLandScape->LandScape()->SetFrustumCheck(false);
	////pLandScape->LandScape()->SetHeightMap(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HeightMap_01.jpg"));

	//SpawnGameObject(pLandScape, Vec3(0.f, 0.f, 0.f), 0);
	
	// ============
	// SolarSystem Loading
	// ============	
	{
		// 인스턴싱 테스트
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;

		{	//태양
			CGameObject* Sun = new CGameObject;
			Sun->SetName(L"sun");
			Sun->AddComponent(new CTransform);
			Sun->AddComponent(new CMeshRender);
			Sun->AddComponent(new CPlanet_Lotating);

			Sun->Transform()->SetRelativeScale(Vec3(2000.f, 2000.f, 2000.f));
			Sun->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

			Sun->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			Sun->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			Sun->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3DMtrl"), 0);
			Sun->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solarsystem\\sun.jpg"));

			SpawnGameObject(Sun, Vec3(0.f, 0.f, 0.f), L"sun");
		}

		{	//수성
			CGameObject* Mercury = new CGameObject;
			Mercury->SetName(L"02_Mercury");
			Mercury->AddComponent(new CTransform);

			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\02_Mercury.fbx");
			pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\02_Mercury.mdat");
			Mercury = pMeshData->Instantiate();

			Mercury->AddComponent(new CPlanet_Lotating);
			Mercury->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 1.0f, 0.f));
			Mercury->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));
			SpawnGameObject(Mercury, Vec3(0.f, 0.f, 5000.f), L"Default");
		}

		{	//금성
			CGameObject* Venus = new CGameObject;
			Venus->SetName(L"03_Venus");
			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\03_Venus.fbx");
			pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\03_Venus.mdat");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\03_Venus.mdat", L"meshdata\\03_Venus.mdat");
			Venus = pMeshData->Instantiate();
			Venus->Transform()->SetRelativeScale(Vec3(20.f, 20.f, 20.f));

			Venus->AddComponent(new CPlanet_Lotating);
			Venus->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Venus, Vec3(0.f, 0.f, 7000.f), L"Default");
		}

		{	//지구
			CGameObject* Earth = new CGameObject;
			Earth->SetName(L"04_Earth");
			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\04_Earth.fbx");
			pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\04_Earth.mdat");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\04_Earth.mdat", L"meshdata\\04_Earth.mdat");
			Earth = pMeshData->Instantiate();

			Earth->AddComponent(new CPlanet_Lotating);
			Earth->Transform()->SetRelativeScale(Vec3(0.8f, 0.8f, 0.8f));
			Earth->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Earth, Vec3(0.f, 0.f, 9000.f), L"Default");
		}

		{	//달
			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\04_Moon.fbx");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\04_Moon.mdat", L"meshdata\\04_Moon.mdat");
			//pObj = pMeshData->Instantiate();
			//pObj->SetName(L"04_Moon");
			//pObj->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));
			//SpawnGameObject(pObj, Vec3(3000.f, 0.f, 0.f), L"Default");
		}

		{	//화성
			CGameObject* Mars = new CGameObject;
			Mars->SetName(L"05_Mars");
			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\05_Mars.fbx");
			pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\05_Mars.mdat");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\05_Mars.mdat", L"meshdata\\05_Mars.mdat");
			Mars = pMeshData->Instantiate();

			Mars->AddComponent(new CPlanet_Lotating);
			Mars->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 50.f));
			Mars->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Mars, Vec3(0.f, 0.f, 11000.f), L"Default");
		}

		{	//목성
			CGameObject* Jupiter = new CGameObject;
			Jupiter->SetName(L"06_Jupiter");
			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\06_Jupiter.fbx");
			pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\06_Jupiter.mdat");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\06_Jupiter.mdat", L"meshdata\\06_Jupiter.mdat");
			Jupiter = pMeshData->Instantiate();

			Jupiter->AddComponent(new CPlanet_Lotating);
			Jupiter->Transform()->SetRelativeScale(Vec3(5.f, 5.f, 5.f));
			Jupiter->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Jupiter, Vec3(0.f, 0.f, 20000.f), L"Default");
		}

		{	//토성
			CGameObject* Saturn = new CGameObject;
			Saturn->SetName(L"07_Saturn");
			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\07_Saturn.fbx");
			pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\07_Saturn.mdat");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\07_Saturn.mdat", L"meshdata\\07_Saturn.mdat");
			Saturn = pMeshData->Instantiate();

			Saturn->AddComponent(new CPlanet_Lotating);
			Saturn->Transform()->SetRelativeScale(Vec3(0.01f, 0.01f, 0.01f));
			Saturn->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Saturn, Vec3(0.f, 0.f, 30000.f), L"Default");
		}

		{	//토성 고리
			CGameObject* SaturnRing = new CGameObject;
			SaturnRing->SetName(L"07_SaturnRing");
			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\07_SaturnRing.fbx");
			pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\07_SaturnRing.mdat");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\07_SaturnRing.mdat", L"meshdata\\07_SaturnRing.mdat");
			SaturnRing = pMeshData->Instantiate();

			SaturnRing->AddComponent(new CPlanet_Lotating);
			SaturnRing->Transform()->SetRelativeScale(Vec3(0.01f, 0.01f, 0.01f));
			SaturnRing->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(SaturnRing, Vec3(0.f, 0.f, 30000.f), L"Default");
		}

		{	//천왕성
			CGameObject* Uranus = new CGameObject;
			Uranus->SetName(L"08_Uranus");
			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\08_Uranus.fbx");
			pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\08_Uranus.mdat");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\08_Uranus.mdat", L"meshdata\\08_Uranus.mdat");
			Uranus = pMeshData->Instantiate();

			Uranus->AddComponent(new CPlanet_Lotating);
			Uranus->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
			Uranus->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Uranus, Vec3(0.f, 0.f, 40000.f), L"Default");
		}

		{	//천왕성 고리
			CGameObject* UranusRing = new CGameObject;
			UranusRing->SetName(L"08_UranusRing");
			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\08_UranusRing.fbx");
			pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\08_UranusRing.mdat");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\08_UranusRing.mdat", L"meshdata\\08_UranusRing.mdat");
			UranusRing = pMeshData->Instantiate();

			UranusRing->AddComponent(new CPlanet_Lotating);
			UranusRing->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
			UranusRing->Transform()->SetRelativeRot(Vec3(-1.0f, 0.f, 0.f));
			UranusRing->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(UranusRing, Vec3(0.f, 0.f, 40000.f), L"Default");
		}

		{	//해왕성
			CGameObject* Neptune = new CGameObject;
			Neptune->SetName(L"09_Neptune");
			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\09_Neptune.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\09_Neptune.mdat", L"meshdata\\09_Neptune.mdat");
			Neptune = pMeshData->Instantiate();

			Neptune->AddComponent(new CPlanet_Lotating);
			Neptune->Transform()->SetRelativeScale(Vec3(30.f, 30.f, 30.f));
			Neptune->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Neptune, Vec3(0.f, 0.f, 48000.f), L"Default");
		}
	}
	// ============
	// BlackHole
	// ============	
	{
		Ptr<CMeshData> BlackHoleMeshData = nullptr;

		{	//blackhole
			CGameObject* BlackHole = new CGameObject;
			BlackHole->SetName(L"blackhole");
			BlackHole->AddComponent(new CTransform);
			BlackHole->AddComponent(new CMeshRender);
			BlackHole->AddComponent(new CCollider2D);

			BlackHole->AddComponent(new CPlanet_Lotating);
			BlackHole->AddComponent(new BlackholeScript);

			//블랙홀 스크립트 안에 플레이어 스크립트 정보를 넣어준다.
			BlackholeScript* BS = BlackHole->GetScript<BlackholeScript>();
			CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();
			BS->SetPlayerScript(CPS);

			BlackHole->Transform()->SetRelativeScale(Vec3(1000.f, 1000.f, 1000.f));
			BlackHole->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));
			BlackHole->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
			BlackHole->Collider2D()->SetOffsetScale(Vec3(5.f, 5.f, 5.f));

			BlackHole->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			BlackHole->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			BlackHole->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BlackholeMtrl"), 0);
			SpawnGameObject(BlackHole, Vec3(0.f, 0.f, 55000.f), L"blackhole");
		}

		//blackhole ring
		{
			CGameObject* pBlackhole_Ring = nullptr;

			BlackHoleMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\blackholerring.fbx");
			//BlackHoleMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\House.mdat");
			pBlackhole_Ring = BlackHoleMeshData->Instantiate();
			pBlackhole_Ring->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));
			pBlackhole_Ring->Transform()->SetRelativeRot(Vec3(50.f, 0.f, 0.f));
			pBlackhole_Ring->SetName(L"BlackHole_Ring");
			SpawnGameObject(pBlackhole_Ring, Vec3(0.f, 0.f, 55000.f), L"Default");
		}
	}

	// ============
	// BossStage_Map
	// ============	
	{
		Ptr<CMeshData> BossStageMeshData = nullptr;

		{	//Volcanic
			CGameObject* Volcanic = new CGameObject;
			Volcanic->SetName(L"Volcanic");
			Volcanic->AddComponent(new CTransform);
			Volcanic->AddComponent(new CMeshRender);
			Volcanic->AddComponent(new CPlanet_Lotating);

			Volcanic->Transform()->SetRelativeScale(Vec3(2000.f, 2000.f, 2000.f));
			Volcanic->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

			Volcanic->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			Volcanic->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			Volcanic->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"VolcanicMtrl"), 0);
			Volcanic->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Volcanic_01.png"));
			SpawnGameObject(Volcanic, Vec3(-2000.f, 277.f, 1010000.f), L"Volcanic");
		}

		{	//Volcanic
			CGameObject* Nar_Shaddaa = new CGameObject;
			Nar_Shaddaa->SetName(L"Nar_Shaddaa");
			Nar_Shaddaa->AddComponent(new CTransform);
			Nar_Shaddaa->AddComponent(new CMeshRender);
			Nar_Shaddaa->AddComponent(new CPlanet_Lotating);

			Nar_Shaddaa->Transform()->SetRelativeScale(Vec3(2000.f, 2000.f, 2000.f));
			Nar_Shaddaa->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

			Nar_Shaddaa->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			Nar_Shaddaa->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			Nar_Shaddaa->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Nar_ShaddaaDMtrl"), 0);
			Nar_Shaddaa->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Nar_Shaddaa01.png"));
			SpawnGameObject(Nar_Shaddaa, Vec3(5000.f, 0.f, 1005000.f), L"Nar_Shaddaa");
		}

		//Boss
		{
			CGameObject* Boss = nullptr;

			BossStageMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\boss_test1.fbx");
			//BossStageMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\House.mdat");
			Boss = BossStageMeshData->Instantiate();
			Boss->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 50.f));
			Boss->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));
			//Boss->AddComponent(new CCollider2D);
			//Boss->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
			//Boss->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
			Boss->SetName(L"BlackHole_Ring");
			SpawnGameObject(Boss, Vec3(0.f, 1000.f, 1003000), L"Default");
		}

		//CGameObject* Empty = new CGameObject;
		//Empty->SetName(L"Empty");
		//Empty->AddComponent(new CTransform);
		//Empty->AddComponent(new CMeshRender);
		//Empty->Transform()->SetRelativeScale(Vec3(0.001f, 0.001f, 0.001f));
		////Empty->Transform()->SetRelativePos()
		//Empty->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		//Empty->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);

		//Empty->AddComponent(new CCollider2D);
		//Empty->Collider2D()->SetOffsetPos(Vec3(15000.f, -80000.f, 180000.f));
		//Empty->Collider2D()->SetOffsetScale(Vec3(400000.f, 400000.f, 400000.f));

		//SpawnGameObject(Empty, Vec3(0.f, 0.f, 300.f), L"Player");
	}

	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"blackhole");
}
