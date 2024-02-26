#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"

class HyperLoopScript : public CScript
{
private:
    CCameraScript* CameraScript;
    CPlayerScript* PlayerScript;
    CGameObject* m_TargetObject;
    CGameObject* Camera;

    bool collision = false;
    double mTime;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }

    CLONE(HyperLoopScript);
public:
    HyperLoopScript();
    ~HyperLoopScript();
};

