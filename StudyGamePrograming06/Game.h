#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	class Renderer* GetRenderer() { return mRenderer; }

	void SetRunning(bool isrunning) { mIsRunning = isrunning; }

	//ゲームウィンドウの大きさ
	int mWindowWidth;
	int mWindowHeight;

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// すべてのアクター
	std::vector<class Actor*> mActors;
	// すべての待ちアクター
	std::vector<class Actor*> mPendingActors;

	class Renderer* mRenderer;

	Uint32 mTicksCount;
	bool mIsRunning;
	// アクターが更新中か
	bool mUpdatingActors;

	// Game-specific
	class CameraActor* mCameraActor;
};