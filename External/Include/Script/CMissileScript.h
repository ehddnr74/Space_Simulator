#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"
#include "BossScript.h"

class CMissileScript :
    public CScript
{
private:
    CCameraScript* CameraScript;
    CPlayerScript* PlayerScript;
    CGameObject* MissileEmpty;
    CGameObject* m_TargetObject;
    CGameObject* Camera;

    Vector3 OffsetX;
    Vector3 ShootDir;
    //Vector3 ShootUpDir;
    //Vector3 ShootDownDir;
    //Vector3 ShootRightDir;
    //Vector3 ShootLeftDir;
    double ShotTime;

public:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetTargetObject(CGameObject* m_TO) { m_TargetObject = m_TO; }

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }

   // void SetBossScript(BossScript* BS) { Boss_Script = BS; }

    CLONE(CMissileScript);
public:
    CMissileScript();
    ~CMissileScript();
};

