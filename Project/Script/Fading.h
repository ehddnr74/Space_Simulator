#pragma once
#include <Engine\CScript.h>
#include "CCameraScript.h"

class Fading : public CScript
{
public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(Fading);

    enum class FadingState
    {
        FadeIn,
        FadeOut,
    };

    void SetFadingState(FadingState FS) { eFadingState = FS; }

private:
    double ratio;
    FadingState eFadingState;

public:
    Fading();
    ~Fading();

private:
    void FadeIn();
    void FadeOut();

    bool init;

};


