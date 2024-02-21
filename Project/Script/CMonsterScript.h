#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"

class CMonsterScript :
    public CScript
{
private:
    CPlayerScript* PlayerScript;
    CCameraScript* CameraScript;
    CGameObject* Bullet;

    double MoveTime;
    double ShotTime;
    int HP;
    int RandomPos;
    bool Bulletbool;



public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }

    void CreateMonsterBullet();

    void SetBulletBool(bool b) { Bulletbool = b; }

    CLONE(CMonsterScript);
public:
    CMonsterScript();
    ~CMonsterScript();
};


