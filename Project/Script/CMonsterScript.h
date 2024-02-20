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

    double MoveTime;
    int HP;
    int RandomPos;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }

    CLONE(CMonsterScript);
public:
    CMonsterScript();
    ~CMonsterScript();
};


