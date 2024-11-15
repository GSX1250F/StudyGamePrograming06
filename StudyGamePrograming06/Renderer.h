#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"
#include "Texture.h"
#include "VertexInfo.h"

struct DirectionalLight
{
	Vector3 mDirection;		// ���̕���
	Vector3 mDiffuseColor;	// �g�U���ːF
	Vector3 mSpecColor;		// ���ʔ��ːF
};

struct PointLight
{
	float mAttenuation;		// ���������W��
	Vector3 mPosition;		// �_�����̈ʒu
	Vector3 mDiffuseColor;	// �g�U���ːF
	Vector3 mSpecColor;		// ���ʔ��ːF
};

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();

	bool Initialize(float screenWidth, float screenHeight);
	void UnloadData();
	void Shutdown();

	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);

	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);
	class VertexInfo* GetVertexInfo() { return mVertexInfo; }

	void SetViewMatrix(const Matrix4& matrix) { mView = matrix; }
	void SetProjMatrix(const Matrix4& matrix) { mProj = matrix; }

	Vector3& GetAmbientLight() { return mAmbientLight; }
	void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
	//DirectionalLight& GetDirectionalLight() { return mDirLight; }
	std::vector<DirectionalLight> GetDirectionalLight() { return mDirLights; }
	//void SetDirectionalLight(const DirectionalLight& dir) { mDirLight = dir; }
	void SetDirectionalLight(const DirectionalLight& dir) { mDirLights.emplace_back(dir); }
	std::vector<PointLight> GetPointLight() { return mPointLights; }
	void SetPointLight(const PointLight& pt) { mPointLights.emplace_back(pt); }


	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

private:
	void CreateVertexInfo();
	bool LoadShaders();
	void SetLightUniforms(class Shader* shader);

	std::unordered_map<std::string, class Texture*> mTextures;
	std::unordered_map<std::string, class Mesh*> mMeshes;
	std::unordered_map<class Shader*, std::string> mShaders;	//�V�F�[�_�[�ƃV�F�[�_�[���̘A�z�z��
	std::vector<class SpriteComponent*> mSprites;	
	std::vector<class MeshComponent*> mMeshComps;
	
	class Game* mGame;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_GLContext mContext;
	
	float mScreenWidth;
	float mScreenHeight;

	class VertexInfo* mVertexInfo;
	class Shader* mSpriteShader;
	//class Shader* mMeshShader;
	

	Matrix4 mView;
	Matrix4 mProj;

	// �����ƌ���
	Vector3 mAmbientLight;
	//DirectionalLight mDirLight;
	std::vector<DirectionalLight> mDirLights;
	std::vector<PointLight> mPointLights;
};