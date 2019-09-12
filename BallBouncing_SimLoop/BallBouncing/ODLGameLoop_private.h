#ifndef ODLGAMELOOP_PRIVATE_H_
#define ODLGAMELOOP_PRIVATE_H_

typedef struct ODLGameLoopStateStruct {
	int desiredStateUpdatesPerSecond;
	double desiredStateUpdateDurationMs;

	double lastLoopTime;
	double timeAccumulatedMs;

	int upsCount;
	int fpsCount;
	double lastMeasurementTime;

} ODLGameLoopState;

extern ODLGameLoopState odlGameLoopState;

// void ODLGameLoop_initOpenGL();
// void ODLGameLoop_updateState();
// void ODLGameLoop_onOpenGLIdle();
// void ODLGameLoop_updateGraphics();
// void ODLGameLoop_onWindowReshape();
// void ODLGameLoop_onKeyboard(unsigned char key, int x, int y);
// void ODLGameLoop_updateMeasurements();


#endif /* ODLGAMELOOP_PRIVATE_H_ */
