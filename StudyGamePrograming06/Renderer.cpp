#include "Renderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <glew.h>
#include <algorithm>
#include "VertexInfo.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "Mesh.h"
#include "MeshComponent.h"


Renderer::Renderer(Game* game)
	: mGame(game)
	, mWindow(nullptr)
	, mSpriteShader(nullptr)
	, mMeshShader(nullptr)
	, mVertexInfo(nullptr)
{}

Renderer::~Renderer()
{}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	// Set OpenGL attributes
	// Use the core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Specify version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow(
		"Game Programming in C++",
		100, 
		100,
		static_cast<int>(mScreenWidth), 
		static_cast<int>(mScreenHeight), 
		SDL_WINDOW_OPENGL
	);

	if (!mWindow)
	{
		SDL_Log("window�̍쐬�Ɏ��s���܂���: %s", SDL_GetError());
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);

	// OpenGL�R���e�N�X�g�𐶐��i���ׂĂ�OpenGL�@�\�ɃA�N�Z�X����j
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEW��������
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("GLEW�̏������Ɏ��s���܂����B");
		return false;
	}
	glGetError();

	// �o�[�e�b�N�X�z��I�u�W�F�N�g�̐���
	CreateVertexInfo();

	// �V�F�[�_�[�̐���
	if (!LoadShaders())
	{
		SDL_Log("�V�F�[�_�[�̓ǂݍ��݂Ɏ��s���܂����B");
		return false;
	}

	// ��ʃN���A�̐F��ݒ�
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	return true;
}

void Renderer::UnloadData()
{
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();

	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	mMeshes.clear();
}

void Renderer::Shutdown()
{
	delete mVertexInfo;
	mSpriteShader->Unload();
	delete mSpriteShader;
	mMeshShader->Unload();
	delete mMeshShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

void Renderer::Draw()
{
	// ��ʂ��N���A & �[�x�o�b�t�@���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	// �܂��A�[�x�L�����ƃA���t�@�u�����f�B���O�𖳌������ĕ`�悷��B
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	// ���b�V���V�F�[�_�[�L����
	mMeshShader->SetActive();
	// �V�F�[�_�[�̃r���[�ϊ�&�ˉe�ϊ��s����X�V
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProj);
	// Update lighting uniforms
	SetLightUniforms(mMeshShader);
	// ���b�V���R���|�[�l���g��`��B
	for (auto mc : mMeshComps)
	{
		mc->Draw(mMeshShader);
	}

	// �[�x�������A�A���t�@�u�����f�B���O�L�������ĕ`��B�i��Ԏ�O�ɕ`�悷��j
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// �X�v���C�g�V�F�[�_�[�ƃo�[�e�b�N�X�z��I�u�W�F�N�g��L����
	mSpriteShader->SetActive();
	mVertexInfo->SetActive();
	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}

	// Swap the buffers
	SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Renderer::AddMeshComp(MeshComponent* mesh)
{
	mMeshComps.emplace_back(mesh);
}

void Renderer::RemoveMeshComp(MeshComponent* mesh)
{
	auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
	mMeshComps.erase(iter);
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			mTextures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

Mesh* Renderer::GetMesh(const std::string & fileName)
{
	Mesh* m = nullptr;
	auto iter = mMeshes.find(fileName);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	else
	{
		m = new Mesh();
		if (m->Load(fileName, this))
		{
			mMeshes.emplace(fileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

bool Renderer::LoadShaders()
{
	// �X�v���C�g�p�V�F�[�_�[�𐶐�
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// �X�v���C�g�̕`��ɂ́A���s�ˉe���s���B
	mView = Matrix4::Identity;
	// Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mProj = Matrix4::CreateOrtho(mScreenWidth, mScreenHeight, 0.01f, 5000.0f);
	mSpriteShader->SetMatrixUniform("uViewProj", mView * mProj);

	// ���b�V���p�V�F�[�_�[�𐶐�
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"))
	{
		return false;
	}

	mMeshShader->SetActive();
	// ���b�V���̕`��ɂ́A�����ˉe���s���B
	Vector3 cameraPos = Vector3::Zero;
	Vector3 cameraTarget = Vector3::UnitX;
	Vector3 cameraUp = Vector3::UnitZ;
	mView = Matrix4::CreateLookAt(cameraPos,cameraTarget,cameraUp);
	mProj = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),mScreenWidth, mScreenHeight, 0.01f, 10000.0f);
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProj);
	return true;
}

void Renderer::CreateVertexInfo()
{
	// ������W�n
	// ���_���W(vector3), �@���x�N�g��(Vector3), �e�N�X�`�����W(Vector2)
	float vertices[] = {
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,	 // top left
		 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,	 // top right
		 0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,	 // bottom right
		-0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f		 // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mVertexInfo = new VertexInfo(vertices, 4, indices, 6);
}

void Renderer::SetLightUniforms(Shader* shader)
{
	// �J�����̈ʒu�̓r���[�𔽓]���ċ��߂�
	Matrix4 invView = mView;
	invView.Invert();
	shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// ����
	shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	// ���s����
	shader->SetVectorUniform("uDirLight.mDirection", mDirLight.mDirection);
	shader->SetVectorUniform("uDirLight.mDiffuseColor",	mDirLight.mDiffuseColor);
	shader->SetVectorUniform("uDirLight.mSpecColor", mDirLight.mSpecColor);
}
