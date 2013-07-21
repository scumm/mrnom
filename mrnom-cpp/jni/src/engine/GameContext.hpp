#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "EventLoop.hpp"

namespace engine {

class GameScreen;
class RenderView;
class ResourceFactory;

/**
 * Abstract game context class.
 */
class GameContext : public EventLoop {

public:

	GameContext();

	virtual ~GameContext();

	/**
	 * @param deltaTime The elapsed time, in seconds.
	 */
	virtual void onUpdate(float deltaTime);

	virtual void onStart();

	virtual void onResume();

	virtual void onPause();

	virtual void onStop();

	GameScreen* getScreen() const;

	void setScreen(GameScreen* screen);

	virtual GameScreen* getStartScreen() = 0;

	ResourceFactory* getResourceFactory() const;

private:

	GameScreen* mScreen;
	RenderView* mRenderView;
	ResourceFactory* mResourceFactory;
};

}

#endif
