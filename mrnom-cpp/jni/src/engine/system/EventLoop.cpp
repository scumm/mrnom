#include "EventLoop.hpp"

#define INTERVAL_30FPS 0.0333333333333f
#define INTERVAL_60FPS 0.0166666666667f

using namespace engine;

EventLoop::EventLoop() :
	_application(0),
	_active(false) {
	LOG_D("### EventLoop::EventLoop()");
}

EventLoop::~EventLoop() {
	LOG_D("$$$ EventLoop::~EventLoop()");
}

android_app* EventLoop::getApplication() const {
	return _application;
}

void EventLoop::init(android_app* application)
{
	int result, events;
	android_poll_source* source;

	_application = application;

	// register our system event call-backs
	application->onAppCmd = systemStateCallback;
	application->onInputEvent = systemInputCallback;
	application->userData = this;

	app_dummy();

	LOG_D("--- ENTERING EVENT LOOP");

	while (true) {

		// Consume system events awaiting in the queue.
		// Timeout type: 0: non-blocking, -1: blocking.

		while ((result = ALooper_pollAll((_active ? 0 : -1), NULL, &events, (void**) &source)) >= 0) {
			if (source != NULL) source->process(application, source);

			if (application->destroyRequested) {
				LOG_D("--- EXITING EVENT LOOP");
				assert(!_active);
				return;
			}
		}

		if (_active) {
			// get time delta since last cycle
			float deltaTime = _timer.elapsed(true);

			onUpdate(deltaTime);

			// get time delta since this cycle
			float frameTime = _timer.elapsed(false);

			if (frameTime < INTERVAL_30FPS) {
				// running faster than fps limit
				// put thread to sleep to save energy
				float sleepTime = INTERVAL_30FPS - frameTime;
				// LOG_D("frameTime: %f sleepTime: %f", frameTime, sleepTime);
				usleep(sleepTime * 1000000.0); // seconds to microseconds
			}
		}
	}
}

void EventLoop::resumeRender() {
	_active = true;
	_timer.update();
}

void EventLoop::pauseRender() {
	_active = false;
}

/*
 * For each system command we invoke an equivalent call-back method.
 * We also toggle the active state on resume / pause system commands.
 */
void EventLoop::systemStateCallback(android_app* app, int32_t cmd)
{
	EventLoop* eventLoop = (EventLoop*) app->userData;

	switch (cmd) {
	case APP_CMD_START:
		LOG_D("--- APP_CMD_START");
		eventLoop->onStart();
		break;
	case APP_CMD_RESUME:
		LOG_D("--- APP_CMD_RESUME");
		// eventLoop->onResume();
		break;
	case APP_CMD_INIT_WINDOW:
		LOG_D("--- APP_CMD_INIT_WINDOW");
		eventLoop->onResume();
		break;
	case APP_CMD_PAUSE:
		LOG_D("--- APP_CMD_PAUSE");
		eventLoop->onPause();
		break;
	case APP_CMD_TERM_WINDOW:
		LOG_D("--- APP_CMD_TERM_WINDOW");
		// eventLoop->onPause();
		break;
	case APP_CMD_STOP:
		LOG_D("--- APP_CMD_STOP");
		eventLoop->onStop();
		break;
	case APP_CMD_DESTROY:
		LOG_D("--- APP_CMD_DESTROY");
		eventLoop->onDestroy();
		break;
	}
}

int32_t EventLoop::systemInputCallback(android_app* app, AInputEvent* event)
{
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		return 1;
	}

	return 0;
}
