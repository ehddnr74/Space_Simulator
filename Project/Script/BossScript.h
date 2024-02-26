#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"

class BossScript : public CScript
{
private:
    CPlayerScript* PlayerScript;
    CCameraScript* CameraScript;
    CGameObject* Bullet;
    CGameObject* Missile;

    int HP;
    int RandomPos;
    double MoveTime;
    double ShotTime;
    bool Bulletbool;
    bool Bossnear;

    double BossnearTime;

    double ContactTime;
    bool ContackFinish;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }

    void CreateBossBullet();
    void CreateBossMissile();
    void CreateBossRazer();

    void ContactBoss();

    void SetBulletBool(bool b) { Bulletbool = b; }

    CLONE(BossScript);
public:
    BossScript();
    ~BossScript();
};

