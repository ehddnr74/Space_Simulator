#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"

class BossScript : public CScript
{

public:
    enum class BossState
    {
        Razer,
        Missile,
        MonsterSpawn,
      //VolcanicAbsorb,
      //SiriusAbsorb,
        TelePort,
        ForceShield,
        Die,
    };

private:
    double InitTime;
    BossState eBossState;
    CPlayerScript* PlayerScript;
    CCameraScript* CameraScript;
    CGameObject* Bullet;
    CGameObject* Missile;

    int HP;
    double MoveTime;
    double ShotTime;
    bool Bulletbool;
    bool RoomEffectCheck;

    bool Once = false;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }

    void CreateBossBullet();
    void CreateBossMissile();
    void CreateBossRazer();
    void CreateRoomEffect();


    void SetBulletBool(bool b) { Bulletbool = b; }

    CLONE(BossScript);
public:
    BossScript();
    ~BossScript();

private:
    void razer();
    void missile();
    void monsterspawn();
    void teleport();
    void forceshield();
    void die();

};

