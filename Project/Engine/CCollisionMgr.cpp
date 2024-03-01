#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CCollider2D.h"

CCollisionMgr::CCollisionMgr()
    : m_matrix{}
{

}


CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::tick()
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurLevel();

	for (UINT iRow = 0; iRow < MAX_LAYER; ++iRow)
	{
		for (UINT iCol = iRow; iCol < MAX_LAYER; ++iCol)
		{
			if (!(m_matrix[iRow] & (1 << iCol)))
				continue;

			// iRow ���̾�� iCol ���̾�� ���� �浹�˻縦 �����Ѵ�.
			CollisionBtwLayer(pLevel->GetLayer(iRow), pLevel->GetLayer(iCol));
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(CLayer* _Left, CLayer* _Right)
{
	const vector<CGameObject*>& vecLeft = _Left->GetObjects();
	const vector<CGameObject*>& vecRight = _Right->GetObjects();

	if (_Left == _Right)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = i + 1; j < vecRight.size(); ++j)
			{
				CollisionBtwObject(vecLeft[i], vecRight[j]);				
			}
		}
	}
	else
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				CollisionBtwObject(vecLeft[i], vecRight[j]);				
			}
		}
	}
}

void CCollisionMgr::CollisionBtwObject(CGameObject* _LeftObject, CGameObject* _RightObject)
{
	if (!(_LeftObject->Collider2D() && _RightObject->Collider2D()))
		return;

	// �浹ü ID ����
	CollisionID id = {};
	id.LeftID = _LeftObject->Collider2D()->GetID();
	id.RightID = _RightObject->Collider2D()->GetID();
	
	// ID �˻�
	map<UINT_PTR, bool>::iterator iter = m_mapColID.find(id.id);
	if (iter == m_mapColID.end())
	{
		m_mapColID.insert(make_pair(id.id, false));
		iter = m_mapColID.find(id.id);
	}

	// �� �� �ϳ��� ���� ���� ���¶��(Dead ����)
	bool bDead = false;
	if (_LeftObject->IsDead() || _RightObject->IsDead())
	{
		bDead = true;
	}
	
	// �� �浹ü�� ���� �浹 ������ Ȯ��
	if (CollisionBtwCollider(_LeftObject->Collider2D(), _RightObject->Collider2D()))
	{
		// ������ �浹�� ���� �ְ�, ���� �ϳ� �̻��� ���� �����̶��
		if (bDead && iter->second)
		{
			_LeftObject->Collider2D()->EndOverlap(_RightObject->Collider2D());
			_RightObject->Collider2D()->EndOverlap(_LeftObject->Collider2D());
		}
		else if (iter->second)
		{
			// ��� �浹 ��
			_LeftObject->Collider2D()->OnOverlap(_RightObject->Collider2D());
			_RightObject->Collider2D()->OnOverlap(_LeftObject->Collider2D());
		}
		else
		{
			// �̹� �����ӿ� �浹
			if (!bDead) // ���� �ϳ��� Dead ���¸� �浹�� �����Ѵ�.
			{
				_LeftObject->Collider2D()->BeginOverlap(_RightObject->Collider2D());
				_RightObject->Collider2D()->BeginOverlap(_LeftObject->Collider2D());
				iter->second = true;
			}			
		}
	}

	else
	{
		// �浹 ����
		if (iter->second)
		{
			_LeftObject->Collider2D()->EndOverlap(_RightObject->Collider2D());
			_RightObject->Collider2D()->EndOverlap(_LeftObject->Collider2D());
			iter->second = false;
		}
	}


}

// �� �浹ü�� �浹 �˻� ����
bool CCollisionMgr::CollisionBtwCollider(CCollider2D* _pLeft, CCollider2D* _pRight)
{
	Vec3 LocalRadiusX = Vec3(0.5f, 0.f, 0.f);
	Vec3 LocalRadiusY = Vec3(0.f, 0.5f, 0.f);
	Vec3 LocalRadiusZ = Vec3(0.f, 0.f, 0.5f);

	Vec3 LeftWorldPos = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pLeft->GetColliderWorldMat());
	Vec3 RightWorldPos = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pRight->GetColliderWorldMat());

	Vec3 LeftRadiusX = XMVector3TransformCoord(LocalRadiusX, _pLeft->GetColliderWorldMat());
	LeftRadiusX -= LeftWorldPos;
	Vec3 RightRadiusX = XMVector3TransformCoord(LocalRadiusX, _pRight->GetColliderWorldMat());
	RightRadiusX -= RightWorldPos;

	Vec3 LeftRadiusY = XMVector3TransformCoord(LocalRadiusY, _pLeft->GetColliderWorldMat());
	LeftRadiusY -= LeftWorldPos;
	Vec3 RightRadiusY = XMVector3TransformCoord(LocalRadiusY, _pRight->GetColliderWorldMat());
	RightRadiusY -= RightWorldPos;

	Vec3 LeftRadiusZ = XMVector3TransformCoord(LocalRadiusZ, _pLeft->GetColliderWorldMat());
	LeftRadiusZ -= LeftWorldPos;
	Vec3 RightRadiusZ = XMVector3TransformCoord(LocalRadiusZ, _pRight->GetColliderWorldMat());
	RightRadiusZ -= RightWorldPos;

	float L_RadiusX = sqrt((LeftRadiusX.x * LeftRadiusX.x) + (LeftRadiusX.y + LeftRadiusX.y) + (LeftRadiusX.z + LeftRadiusX.z));
	float R_RadiusX = sqrt((RightRadiusX.x * RightRadiusX.x) + (RightRadiusX.y + RightRadiusX.y) + (RightRadiusX.z + RightRadiusX.z));

	float L_RadiusY = sqrt((LeftRadiusY.x * LeftRadiusY.x) + (LeftRadiusY.y + LeftRadiusY.y) + (LeftRadiusY.z + LeftRadiusY.z));
	float R_RadiusY = sqrt((RightRadiusY.x * RightRadiusY.x) + (RightRadiusY.y + RightRadiusY.y) + (RightRadiusY.z + RightRadiusY.z));

	float L_RadiusZ = sqrt((LeftRadiusZ.x * LeftRadiusZ.x) + (LeftRadiusZ.y + LeftRadiusZ.y) + (LeftRadiusZ.z + LeftRadiusZ.z));
	float R_RadiusZ = sqrt((RightRadiusZ.x * RightRadiusZ.x) + (RightRadiusZ.y + RightRadiusZ.y) + (RightRadiusZ.z + RightRadiusZ.z));

	Vec3 Center = RightWorldPos - LeftWorldPos;
	float fDistance = sqrt((Center.x * Center.x) + (Center.y + Center.y) + (Center.z + Center.z));

	//if (abs(Center.x + 20) < (LeftRadiusX.x + RightRadiusX.x) && abs(Center.y + 20) < (LeftRadiusY.y + RightRadiusY.y)
		//&& abs(Center.z + 20) < (LeftRadiusZ.z + RightRadiusZ.z))
	//return true;

	if (fDistance <= (L_RadiusX + R_RadiusX) && fDistance <= (L_RadiusY + R_RadiusY) && fDistance <= (L_RadiusZ + R_RadiusZ))
		return true;

	if (pow(Center.x, 2) + pow(Center.y, 2) + pow(Center.z, 2) < pow(LeftRadiusX.x + RightRadiusX.x, 2))
		return true;

	return false;


	//// 0 -- 1
	//// |    |
	//// 3 -- 2
	//Vec3 arrLocal[4] =
	//{
	//	Vec3(-0.5f, 0.5f, 0.f),
	//	Vec3(0.5f, 0.5f, 0.f),
	//	Vec3(0.5f, -0.5f, 0.f),
	//	Vec3(-0.5f, -0.5f, 0.f),
	//};

	//// �� �浹ü�� �� ǥ�� ���� 2���� ����
	//Vec3 arrProj[4] = {};

	//arrProj[0] = XMVector3TransformCoord(arrLocal[1], _pLeft->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pLeft->GetColliderWorldMat());
	//arrProj[1] = XMVector3TransformCoord(arrLocal[3], _pLeft->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pLeft->GetColliderWorldMat());
	//
	//arrProj[2] = XMVector3TransformCoord(arrLocal[1], _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pRight->GetColliderWorldMat());
	//arrProj[3] = XMVector3TransformCoord(arrLocal[3], _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pRight->GetColliderWorldMat());
	//
	//// �� �浹ü�� �߽����� ����
	//Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pLeft->GetColliderWorldMat());
	//

	//// �и��� �׽�Ʈ
	//for (int i = 0; i < 4; ++i)
	//{
	//	Vec3 vProj = arrProj[i];
	//	vProj.Normalize();

	//	// 4���� ǥ����͸� ������ ���������� ������Ų �Ÿ��� ���� / 2
	//	float fProjDist = 0.f;
	//	for (int j = 0; j < 4; ++j)
	//	{
	//		fProjDist += fabsf(arrProj[j].Dot(vProj));
	//	}
	//	fProjDist /= 2.f;

	//	float fCenter = fabsf(vCenter.Dot(vProj));

	//	if (fProjDist < fCenter)
	//		return false;
	//}


 //   return true;
}



void CCollisionMgr::LayerCheck(UINT _left, UINT _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;

	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}

	m_matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::LayerCheck(const wstring& _strLeftLayer, const wstring& _strRightLayer)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	CLayer* pLeft = pCurLevel->FindLayerByName(_strLeftLayer);
	CLayer* pRight = pCurLevel->FindLayerByName(_strRightLayer);

	LayerCheck(pLeft->GetLayerIndex(), pRight->GetLayerIndex());
}
