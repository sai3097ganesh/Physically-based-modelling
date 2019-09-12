/*-------------------------------------------------------

Implements all of the components used program.

---------------------------------------------------------*/

#include "components.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <GL/gl.h>     // The GL Header File
#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
#include <unistd.h>

#define PI 3.14159265f

using namespace std;

/*Begin GameObject-------------------------------------------------------*/

/* The constructor for a GameObject. 
 *
 * @param (double x) starting x position of object
 * @param (double y) starting y position of object
 */
GameObject::GameObject( double x, double y ) : x( x ), y( y ) {}

/* This function returns a list of all components that have the input string as their type
 *
 * @param (string type) the desired "type" of component
 */
list<Component*> GameObject::getComponent( string type ) {
  list<Component*> res;
  for(Component* elem: componentList) {
    if ((elem->type).compare( type ) == 0) res.push_back( elem );
  }
  return res;
}

/**
 * This function adds a component to the GameObject's component list.
 * 
 * @param (Component* c) the component to add to the Gameobject's list
 */
void GameObject::addComponent( Component* c) {
  componentList.push_back( c );
}

/*End GameObject---------------------------------------------------------*/

/*Begin Component-------------------------------------------------------*/

/* This function is a constructor for a general Component. 
 *  
 * @param (GameObject* parent) the parent of the new Component
 * @param (string type) the type of the new component
 */

Component::Component( GameObject* parent, string type ) : parent ( parent ), type ( type ) {
  Component::components.push_back( this ); 
  parent->addComponent( this );
};


/* This function is intended to be run at a variable interval (useful for things like rendering)
 * The defualt implementation does nothing
 *
 * @param (float dt) time since the last fixedUpdate in milliseconds
 */
void Component::update( float dt ) {}

/* This function is intended to be run at a set interval (useful for things like physics)
 * The defualt implementation does nothing.
 *
 * @param (float dt) time since the last fixedUpdate in milliseconds
 */

void Component::fixedUpdate( float dt ) {}

/* This function takes in a float (dt) representing the time since the last fixedUpdate
 * This function is intended to be run at a variable interval (useful for things like rendering)
 * It runs the update(float dt) funtion for every component
 */

/* This function runs update() on every component
 *
 * @param (float dt) time since the last fixedUpdate in milliseconds
 */
void Component::updateAll( float dt ){
  //printf("floatingUpdateDt:%f \n", (float) dt);
  for(Component* elem: Component::components){
    elem->update( dt );
  }
};

/* This function runs fixedUpdate() on every component
 *
 * @param (float dt) time since the last fixedUpdate in milliseconds
 */
void Component::fixedUpdateAll( float dt ){
  //printf("fixedUpdateDt:%f \n", (float) dt);
  for(Component* elem: Component::components){
    elem->fixedUpdate( dt );
  }
};

/*End Component-------------------------------------------------------*/


/*Begin Collider (extends Component)-------------------------------------------------------*/

list<Collider*> Collider::allColliders;

/* The constructor for a Collider. 
 *
 * @param (GameObject* parent) the parent of the new Component
 * @param (double radius) the collision radius of the object
 */
Collider::Collider( GameObject* parent, double radius ) :
  radius( radius ), Component ( parent, "Collider"){
  Collider::allColliders.push_back( this );
  list<triggerFunc> triggers; //this list is all colliders
};

/* This function adds a trigger function (fuction called when there is a collision) to the collider.
 *
 * @param (triggerFunc trigger) a trigger function to be called when the collider detects a collision.
 */
void Collider::addTrigger(triggerFunc trigger) {
  triggers.push_back(trigger);
}

/* This function calulates the disatnce between 2 GameObjects 

 * @param (GameObject* obj1)
 * @param (GameObject* obj2)
 */
float calculateDistance(GameObject* obj1, GameObject* obj2) {
  return sqrt( pow((obj1->x - obj2->x), 2) + pow((obj1->y - obj2->y), 2) );
}

/**
 * This function detects if this collider is colliding with any other colliders 
 * that are not attached to the same parent object. If it detects a collision, 
 * it will invoke any collision resolution functions attached to the current collider.
 *
 * @param (float dt) The elapsed time since the last fixedUpdate in milliseconds
 */

void Collider::fixedUpdate(float dt) {
  // Retrieve a list of all colliders attached to the parent
  list <Component*> parentList =  parent->getComponent("Collider");

  Collider* parentCollider;
  for(Collider* otherCollider: Collider::allColliders) {
    for(Component* elem: parentList) {
      // Skip this loop iteration if the other collider in consideration is
      // attached to the same object as the current collider
      parentCollider = (Collider*) elem;
      if (otherCollider == parentCollider) continue;

      // If there is no collision, skip this loop iteration
      float distance = calculateDistance(otherCollider->parent, parent);
      if (distance > this->radius + otherCollider->radius) continue;

      // Otherwise, execute any registered collision resolution functions
      for (triggerFunc trigger: triggers) trigger(this, otherCollider, dt);
    }
  }
}

/*End Coliider-------------------------------------------------------*/


/*Begin CircleRender-------------------------------------------------------*/

/* The constructor for a CircleRender. 
 *
 * @param (GameObject* parent) the parent of the new Component
 * @param (double radius) the collision radius of the object
 */
CircleRender::CircleRender( GameObject* parent, double radius ) :
radius ( radius ), Component(parent, string("CircleRender")) {
  setColor(0, 0, 1);
}

/* This function sets the color the circle should render as.  
 *
 * @param (float R) The value of red (0-255)
 * @param (float G) The value of greem (0-255)
 * @param (float B) The value of blue (0-255)
 */
void CircleRender::setColor(float R, float G, float B) {
  color.R = R;
  color.G = G;
  color.B = B;
}

/**
 * This function detects if this collider is colliding with any other colliders 
 *
 * @param (float dt) The elapsed time since the last fixedUpdate in milliseconds
 */
void CircleRender::update( float dt ) {
  //printf("floatingUpdatedt:%f \n", dt);
  GLfloat ballRadius = (GLfloat) radius;   // Radius of the bouncing ball
  GLfloat ballX = (GLfloat) parent->x;         // Ball's center (x, y) position
  GLfloat ballY = (GLfloat) parent->y;

  glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
  glLoadIdentity();              // Reset model-view matrix

  glTranslatef(ballX, ballY, 0.0f);  // Translate to (xPos, yPos)
  // Use triangular segments to form a circle
  glBegin(GL_TRIANGLE_FAN);
     glColor3f(color.R, color.G, color.B);
     glVertex2f(0.0f, 0.0f);       // Center of circle
     int numSegments = 100;
     GLfloat angle;
     for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
        angle = (i * 2.0f * PI) / numSegments;  // 360 deg for all segments
        glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
     }
  glEnd();
}
/*End CircleRenderer-------------------------------------------------------*/

/*Begin Physics-------------------------------------------------------*/

/* The constructor for a Physics. 
 *
 * @param (GameObject* parent) the parent of the new Component
 * @param (double dx) the speed in the x direction
 * @param (double dy) the speed in the y direction
 * @param (double mass) the mass of the object
 */
Physics::Physics ( GameObject* parent, double dx, double dy, double mass) :
mass ( mass ), dx ( dx ), dy ( dy ), Component (parent, string("Physics")) {};

/**
 * This function changes the state of the object at a fixed rate
 *
 * @param (float dt) The elapsed time since the last fixedUpdate in milliseconds
 */
void Physics::fixedUpdate( float dt ) {
  parent->x += dx * dt;
  parent->y += dy * dt;
};

/*End Physics------------------------------------------------------*/

/*Begin WalBounceScript-------------------------------------------------------*/

/* This function is a constructor for a WallBounceScript. 
 * It takes in a GameObject (parent) and a double (radius). It saves radius as an object variable.
 * It then runs the parent constructor for Component (to complete setup).
 */

/* The constructor for a WallBounceScript. 
 *
 * @param (GameObject* parent) the parent of the new Component
 * @param (double radius) the radius of the ball
 */
WallBounceScript::WallBounceScript( GameObject* parent, double radius ) :
radius ( radius ), Component (parent, string( "WallBounceScript" )) {};

/* This function takes in a float (dt) representing the time since the last fixedUpdate
 * This function updates the x and y speeds in the Physics component of the GameObject to make objects bounce off walls.
 */

/**
 * This function snsures that GameObjects don't leave the screen
 *
 * @param (float dt) The elapsed time since the last fixedUpdate in milliseconds
 */
void WallBounceScript::fixedUpdate( float dt ) {
  double x = parent->x;
  double y = parent->y;
  Physics* physComp = dynamic_cast<Physics*> (parent->getComponent(string("Physics")).front());
  double dx = physComp->dx;
  double dy = physComp->dy;

  if (x+radius >= 1) {
    dx = -1 * fabs(dx);
  }
  if (x-radius <= -1) {
    dx = fabs(dx);
  }
  if (y+radius >= 1) {
    dy = -1 * fabs(dy);
  }
  if (y-radius <= -1) {
    dy = fabs(dy);
  }

  physComp->dx = dx;
  physComp->dy = dy;
}
/*End WalBounceScript-------------------------------------------------------*/
