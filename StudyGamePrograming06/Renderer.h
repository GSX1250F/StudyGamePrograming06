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
	Vector3 mDirection;		// 光の方向
	Vector3 mDiffuseColor;	// 拡散反射色
	Vector3 mSpecColor;		// 鏡面反射色
};

struct PointLight
{
	float mAttenuation;		// 距離減衰係数
	Vector3 mPosition;		// 点光源の位置
	Vector3 mDiffuseColor;	// 拡散反射色
	Vector3 mSpecColor;		// 鏡面反射色
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
	std::unordered_map<class Shader*, std::string> mShaders;	//シェーダーとシェーダー名の連想配列
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

	// 環境光と光源
	Vector3 mAmbientLight;
	//DirectionalLight mDirLight;
	std::vector<DirectionalLight> mDirLights;
	std::vector<PointLight> mPointLights;
};