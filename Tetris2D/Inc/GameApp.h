#pragma once

#include "IApp.h"

class Camera2D;

class GameApp : public IApp 
{
public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;
	virtual void Run() override;

private:
	Camera2D* mainCamera_ = nullptr;
};