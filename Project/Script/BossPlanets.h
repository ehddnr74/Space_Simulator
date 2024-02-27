#pragma once
#include <Engine\CScript.h>
#include "CCameraScript.h"
#include "BossScript.h"

class BossPlanets : public CScript
{
public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(BossPlanets);

public:
    BossPlanets();
    ~BossPlanets();

    void SetSirius(CGameObject* sirius) { Sirius = sirius; }
    void SetVolcanic(CGameObject* volcanic) { Volcanic = volcanic; }
    void SetNarShaddaa(CGameObject* narshaddaa) { NarShaddaa = narshaddaa; }

    void SetCameraScript(CCameraScript* CS) { CameraScript = CS; }
    void SetBossScript(BossScript* BS) { BossScript = BS; }
private:
    CGameObject* Sirius;
    CGameObject* Volcanic;
    CGameObject* NarShaddaa;

    CCameraScript* CameraScript;
    BossScript* BossScript;

};