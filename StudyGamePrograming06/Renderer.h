#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

struct DirectionalLight
{
	// Direction of light
	Vector3 mDirection;
	// Diffuse color
	Vector3 mDiffuseColor;
	// Specular color
	Vector3 mSpecColor;
};

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();

	bool Initialize(float screenWidth, float screenHeight);
	void Shutdown();
	void UnloadData();

	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);

	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);
	class VertexInfo* GetVertexInfo() { return mVertexInfo; }

	void SetViewMatrix(const Matrix4& view) { mView = view; }
	void SetProjMatrix(const Matrix4& matrix) { mProj = matrix; }

	void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

private:
	void CreateVertexInfo();
	bool LoadShaders();	
	void SetLightUniforms(class Shader* shader);

	std::unordered_map<std::string, class Texture*> mTextures;
	std::unordered_map<std::string, class Mesh*> mMeshes;
	std::vector<class SpriteComponent*> mSprites;
	std::vector<class MeshComponent*> mMeshComps;

	class Game* mGame;
	SDL_Window* mWindow;
	SDL_GLContext mContext;

	class Shader* mSpriteShader;
	class Shader* mMeshShader;
	class VertexInfo* mVertexInfo;
	
	// ÉrÉÖÅ[ïœä∑Ç∆éÀâeïœä∑çsóÒ
	Matrix4 mView;
	Matrix4 mProj;
	
	// Width/height of screen
	float mScreenWidth;
	float mScreenHeight;

	// Lighting data
	Vector3 mAmbientLight;
	DirectionalLight mDirLight;

	
};