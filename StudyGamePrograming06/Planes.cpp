#include "Planes.h"
#include "Plane.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"

Planes::Planes(Game* game) :Actor(game)
{
	const float start = -1250.0f;
	const float size = 250.0f;
	// 10���c���ɕ��ׂ�
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Plane* a = new Plane(game);
			a->SetPosition(Vector3(start + i * size, start + j * size, -100.0f));
			a->SetScale(10.0f);
			
		}
	}

	// ���E�ǂ��쐬
	Quaternion q = Quaternion(Vector3::UnitX, 0.5f * Math::Pi);	//x�����S��90����
	for (int i = 0; i < 10; i++)
	{
		Plane* a = new Plane(game);
		a->SetPosition(Vector3(start + i * size, start - size, 0.0f));
		a->SetScale(10.0f);
		a->SetRotation(q);
		
		a = new Plane(game);
		a->SetPosition(Vector3(start + i * size, -start + size, 0.0f));
		a->SetScale(10.0f);
		a->SetRotation(q);		
	}

	// �O��ǂ��쐬
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, 0.5f * Math::Pi));	//�����z�����S��90����
	for (int i = 0; i < 10; i++)
	{
		Plane* a = new Plane(game);
		a->SetPosition(Vector3(start - size, start + i * size, 0.0f));
		a->SetScale(10.0f);
		a->SetRotation(q);
		
		a = new Plane(game);
		a->SetPosition(Vector3(-start + size, start + i * size, 0.0f));
		a->SetScale(10.0f);
		a->SetRotation(q);		
	}

}
