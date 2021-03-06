#ifndef LOADINGSCREEN_HPP
#define LOADINGSCREEN_HPP

#include "../engine.h"

using namespace engine;

class LoadingScreen : public GameScreen {

public:

	LoadingScreen(GameContext* context);

	virtual ~LoadingScreen();

	// override
	virtual void resume();

	// override
	virtual void update(float deltaTime);

	// override
	virtual void render(float deltaTime);

	// override
	virtual void pause();

	// override
	virtual void dispose();

private:

	Texture* _backgroundTexture;
	Texture* _logoTexture;
};

#endif
