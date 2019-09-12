#include "gameLoopConstants.h"
#include "ODLGameLoop_private.h"


ODLGameLoopState odlGameLoopState;

/* This function calucaltes and displays performance information such as ups (updates per second) and fps (frames per second)
 */
void ODLGameLoop_updateMeasurements() {
  double now = glutGet(GLUT_ELAPSED_TIME);
  //printf("now:%d last:%d \n", (int) now, (int) odlGameLoopState.lastMeasurementTime);
  double timeElapsedMs = ((now-odlGameLoopState.lastMeasurementTime)*1000000)/(CLOCKS_PER_SEC);
  //printf("timeElapsed:%d \n", (int) timeElapsedMs);
  if(timeElapsedMs>=500) {

    double ups = (odlGameLoopState.upsCount*1000)/timeElapsedMs;
    double fps = (odlGameLoopState.fpsCount*1000)/timeElapsedMs;
    char title[100];
    printf("On Demand Game Loop. FPS:%d UPS:%d \n", (int) fps, (int)ups);
    odlGameLoopState.upsCount = 0;
    odlGameLoopState.fpsCount = 0;
    odlGameLoopState.lastMeasurementTime = now;
  }
}

/* This function initializes variables defining the state of the game loop
 */
void ODLGameLoop_initGameLoopState() {

  odlGameLoopState.lastLoopTime = glutGet(GLUT_ELAPSED_TIME);
  odlGameLoopState.lastMeasurementTime = glutGet(GLUT_ELAPSED_TIME);

  odlGameLoopState.desiredStateUpdatesPerSecond = DESIRED_STATE_UPDATES_PER_SECOND;
  odlGameLoopState.desiredStateUpdateDurationMs = DESIRED_STATE_UPDATE_DURATION_MS;

  odlGameLoopState.upsCount = 0;
  odlGameLoopState.fpsCount = 0;

  odlGameLoopState.timeAccumulatedMs = glutGet(GLUT_ELAPSED_TIME);

  //printf("lastLoop:%d lastMeasure:%d time timeAccumulated:%d \n", (int) odlGameLoopState.lastLoopTime, (int) odlGameLoopState.lastMeasurementTime, (int) odlGameLoopState.timeAccumulatedMs);
}

/* This function handles refreshing the display window
 */
void ODLGameLoop_onOpenGLDisplay() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen
  double now = glutGet(GLUT_ELAPSED_TIME);
  double dt = now - odlGameLoopState.lastLoopTime;
  //printf("lastLoop:%f now:%f dt:%f \n", odlGameLoopState.lastLoopTime, now, dt);
  Component::updateAll(dt);
  odlGameLoopState.fpsCount++;
  glutSwapBuffers();
}

/* This function controls the speed of fixedUpdates and ensures they run at a fixed interval.
 */
void ODLGameLoop_onOpenGLIdle() {

  double now = glutGet(GLUT_ELAPSED_TIME);
  double timeElapsedMs = ((now-odlGameLoopState.lastLoopTime)*1000000)/(CLOCKS_PER_SEC);


  odlGameLoopState.timeAccumulatedMs += timeElapsedMs;

  while(odlGameLoopState.timeAccumulatedMs >= DESIRED_STATE_UPDATE_DURATION_MS) { //
  	  //printf("dt:%f \n", odlGameLoopState.timeAccumulatedMs);


      Component::fixedUpdateAll( (float) odlGameLoopState.timeAccumulatedMs);
      //ODLGameLoop_updateState();
      odlGameLoopState.timeAccumulatedMs -= DESIRED_STATE_UPDATE_DURATION_MS;

      odlGameLoopState.upsCount++;
      ODLGameLoop_updateMeasurements();

      glutPostRedisplay();

  }

  odlGameLoopState.lastLoopTime = now;
}


/* This function initializes glut and begins the game loop
 */
void ODLGameLoop_initOpenGL() {
    char title[] = "Test Window";  // Windowed mode's title
    int windowWidth  = VIEW_WIDTH;     // Windowed mode's width
    int windowHeight = VIEW_HEIGHT;     // Windowed mode's height
    int windowPosX   = WINDOW_POS_X;      // Windowed mode's top-left corner x
    int windowPosY   = WINDOW_POS_Y;      // Windowed mode's top-left corner y

    char *my_argv[] = { (char*) "dummyArgs", NULL };
    int   my_argc = 1;
    glutInit(&my_argc, my_argv);

    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
    glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
    glutCreateWindow(title);      // Create window with given title

    glShadeModel(GL_SMOOTH);              // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);       // Black Background
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0f);                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);              // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);               // The Type Of Depth Testing To Do
    glEnable(GL_COLOR_MATERIAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutDisplayFunc(ODLGameLoop_onOpenGLDisplay); //set function that displays things
    glutIdleFunc(ODLGameLoop_onOpenGLIdle); //set function to update state

    ODLGameLoop_initGameLoopState();

    glutMainLoop();
}
