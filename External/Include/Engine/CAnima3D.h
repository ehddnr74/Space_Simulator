#pragma once
#include "CEntity.h"

#include "ptr.h"
#include "CTexture.h"
#include "CMesh.h"


class CStructuredBuffer;
class CAnimator3D;

class CAnim3D :
    public CEntity
{
private:
    CAnimator3D* m_pOwner;

    int                 m_iCurFrm;
    float               m_fTime;

    bool                m_bFinish;

    Ptr<CMesh>				m_pMesh;

    const vector<tMTBone>* m_pVecBones;
    const vector<tMTAnimClip>* m_pVecClip;


    vector<tMTAnimClip> mClip;
    vector<tMTAnimClip> m_vecFrm;

    vector<float>				m_vecClipUpdateTime;
    vector<Matrix>				m_vecFinalBoneMat; // �ؽ��Ŀ� ������ ���� �������
    int							m_iFrameCount; // 30
    double						m_dCurTime;
    int							m_iCurClip; // Ŭ�� �ε���	

    int                         m_StartTime;
    int                         m_EndTime;

    int							m_iFrameIdx; // Ŭ���� ���� ������
    int							m_iNextFrameIdx; // Ŭ���� ���� ������
    float						m_fRatio;	// ������ ���� ����

    CStructuredBuffer* m_pBoneFinalMatBuffer;  // Ư�� �������� ���� ���
    bool						m_bFinalMatUpdate; // ������� ���� ���࿩��

public:
    void finaltick();
    void Create(const wstring& _strAnimName
        , double CurClipIndex, double mStartTime, double mFinalTime);

    void SetAnimClip(const vector<tMTAnimClip>* _vecAnimClip, vector<float> m_vecClipUpdateTime);
    const tMTAnimClip& GetCurFrame() { return m_vecFrm[m_iCurClip]; }

    bool IsFinish() { return m_bFinish; }
    void Reset()
    {
        m_dCurTime = 0.f;
        m_bFinish = false;
    }

    void SaveToLevelFile(FILE* _File);
    void LoadFromLevelFile(FILE* _File);


    CLONE(CAnim3D);
public:
    CAnim3D();
    ~CAnim3D();

    friend class CAnimator3D;
};
