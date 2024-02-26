#include "pch.h"
#include "Fading.h"
#include "CCameraScript.h"
#include <Engine\CMeshRender.h>

Fading::Fading()
	: CScript((UINT)SCRIPT_TYPE::FADING)
	, ratio(1.f)
	, init(false)
{
}

Fading::~Fading()
{
}

void Fading::begin()
{
	//eFadingState = FadingState::FadeIn;
}

void Fading::tick()
{
	switch (eFadingState)
	{
	case Fading::FadingState::FadeIn:
		FadeIn();
		break;
	case Fading::FadingState::FadeOut:
		FadeOut();
		break;
	}
}
void Fading::FadeIn()
{
	ratio -= DT * 0.15f;

	GetOwner()->MeshRender()->SetRatio(ratio);

	if (ratio <= 0.f)
	{
		DestroyObject(GetOwner());
		ratio = 0.f;
	}
}

void Fading::FadeOut()
{
	if (init == false)
	{
		ratio = 0.f;
		init = true;
	}

	ratio += DT * 0.15f;

	GetOwner()->MeshRender()->SetRatio(ratio);

	if (ratio >= 1.f)
	{
		DestroyObject(GetOwner());
		ratio = 0.f;
		init = true;
	}
}




