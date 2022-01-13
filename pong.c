
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <GL/glfw.h>

#define PADDLE_HEIGHT 100
#define PADDLE_WIDTH 20

#define PADDLE_LEFT_UP_KEY 81 //ASCII code for Q
#define PADDLE_LEFT_DOWN_KEY 65 //ASCII code for A

#define PADDLE_RIGHT_UP_KEY 79 //ASCII code for O
#define PADDLE_RIGHT_DOWN_KEY 76 //ASCII code for L

#define BALL_RADIUS 10

#define FIELD_WIDTH 640
#define FIELD_HEIGHT 480

#define LEFT_SIDE 0
#define RIGHT_SIDE 1

#define LOSE_SERVE_TIME 60

#define PADDLE_SPEED 10.0
// initial max and min speeds of the the ball
#define BALL_SPEED_V_MINI 0.0
#define BALL_SPEED_V_MAXI 12.0
#define BALL_SPEED_H_MINI 3.0
#define BALL_SPEED_H_MAXI 12.0
#define PI 3.14159265f

int p1w, p2w = 0;// No. of player wins
// Sets ball speeds to their initial values
double BALL_SPEED_V_MAX = BALL_SPEED_V_MAXI;
double BALL_SPEED_H_MAX = BALL_SPEED_H_MAXI;
double BALL_SPEED_H_MIN = BALL_SPEED_H_MINI;
double BALL_SPEED_V_MIN = BALL_SPEED_V_MINI;
// Player names
char p1 [10];
char p2 [10];
FILE *fp;// File pointer
typedef struct {
	float x;
	float y;
	int width;
	int height;
	float velX;
	float velY;
} Entity; // Structure to define object to be animated

Entity leftPaddle;
Entity rightPaddle;
Entity ball;

int loseTimer;

void rectangle(double x0, double y0, double x1, double y1)// Function to draw rectangles
{
  glBegin(GL_QUADS);
  glVertex2d(x0,y0);
  glVertex2d(x0,y1);
  glVertex2d(x1,y1);
  glVertex2d(x1,y0);
  glEnd();
}
void updateSpeed() {// updates spped to increase Difficulty (EX 8)
	BALL_SPEED_H_MAX += 0.707;
	BALL_SPEED_V_MAX += 0.707;
	BALL_SPEED_H_MIN += 0.707;
	BALL_SPEED_V_MIN += 0.707;
}
void initSpeed() {//Initializes ball speed to orginal speed after game reset
	BALL_SPEED_H_MAX = BALL_SPEED_H_MAXI;
	BALL_SPEED_V_MAX = BALL_SPEED_V_MAXI;
	BALL_SPEED_H_MIN = BALL_SPEED_H_MINI;
	BALL_SPEED_V_MIN = BALL_SPEED_V_MINI;
}
void circle(double x, double y, double r)// Draws cicle for ball
{
	glBegin(GL_TRIANGLE_FAN);// draws circle using the triangle fan technique
		glVertex2f(ball.x, ball.y);
		int numSegments = 100;
		GLfloat angle;
		for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
	         angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
	         glVertex2f(ball.x+cos(angle) * BALL_RADIUS,ball.y+ sin(angle) * BALL_RADIUS);
	      }
	   glEnd();

}
double randfrac(void) {// Function to generate random values for ugly colours
    double res = (rand() % RAND_MAX) / (double)RAND_MAX;
    return res;
}

void renderFrame(void) {// renders objects in the game
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	rectangle(leftPaddle.x, leftPaddle.y, leftPaddle.x + leftPaddle.width, leftPaddle.y + leftPaddle.height);
	glColor3d(0.0, 1.0, 0.0);
	rectangle(rightPaddle.x, rightPaddle.y, rightPaddle.x + rightPaddle.width, rightPaddle.y + rightPaddle.height);
	glColor3d(randfrac(), randfrac(), randfrac());
	circle(ball.x, ball.y, BALL_RADIUS);
	glfwSwapBuffers();

}

void initPaddles() {// Initializes the structures
	leftPaddle.x = 0;
	leftPaddle.y = (FIELD_HEIGHT / 2) - (PADDLE_HEIGHT / 2);
	leftPaddle.width = PADDLE_WIDTH;
	leftPaddle.height = PADDLE_HEIGHT;

	rightPaddle.x = FIELD_WIDTH - PADDLE_WIDTH;
	rightPaddle.y = (FIELD_HEIGHT / 2) - (PADDLE_HEIGHT / 2);
	rightPaddle.width = PADDLE_WIDTH;
	rightPaddle.height = PADDLE_HEIGHT;

	ball.x = (FIELD_WIDTH / 2) - (BALL_RADIUS / 2);
	ball.y = (FIELD_HEIGHT / 2) - (BALL_RADIUS / 2);
	ball.velX = (BALL_SPEED_H_MAX-BALL_SPEED_H_MIN)/2.0;
	ball.velY = (BALL_SPEED_V_MAX-BALL_SPEED_V_MIN)/2.0;
	ball.width = BALL_RADIUS;
	ball.height = BALL_RADIUS;
}

void GLFWCALL keyboardHandler(int  keyChar, int action) {// Keyboard eventlistner

	if(action == GLFW_PRESS){
		switch (keyChar) {
			case PADDLE_LEFT_UP_KEY:
				leftPaddle.velY = PADDLE_SPEED;
				//if (leftPaddle.y == FIELD_HEIGHT)
				//leftPaddle.velY = 0;
				break;
			case PADDLE_LEFT_DOWN_KEY:
				leftPaddle.velY = -PADDLE_SPEED;
				//if (leftPaddle.y == 0)
				//leftPaddle.velY = 0;
				break;
			case PADDLE_RIGHT_UP_KEY:
				rightPaddle.velY = PADDLE_SPEED;
				//if (rightPaddle.y == FIELD_HEIGHT)
				//rightPaddle.velY = 0;
				break;
			case PADDLE_RIGHT_DOWN_KEY:
				rightPaddle.velY = -PADDLE_SPEED;
				//if (rightPaddle.y == 0)
				//rightPaddle.velY = 0;
				break;
			default:
				break;
		}
	}else if (action == GLFW_RELEASE){
		switch (keyChar) {
			case PADDLE_LEFT_UP_KEY:
			case PADDLE_LEFT_DOWN_KEY:
				leftPaddle.velY = 0;
				break;
			case PADDLE_RIGHT_UP_KEY:
			case PADDLE_RIGHT_DOWN_KEY:
				rightPaddle.velY = 0;
				break;
			case GLFW_KEY_ESC://exercise 3
				glfwCloseWindow();
			default:
				break;
		}
	}
}

void handleLose(int side) {
	loseTimer = LOSE_SERVE_TIME;
	initPaddles();
	if (side == RIGHT_SIDE) {
		ball.velX *= -1;
	}
}

float getVertBallSpeedRebound(float yOffset, float minValue, float maxValue) {// calculates vertical rebound
	return yOffset*(maxValue-minValue);
}

float getHorizBallSpeedRebound(float yOffset, float minValue, float maxValue) {//calculates horizontal rebound
	float a = maxValue-minValue;
	return (-1*a*yOffset*yOffset + maxValue);
}

float calculateNormalizedOffset(float origin, float distance, float max){// calculates offset for rebound calculations
	return (distance - origin)/max;
}

void runPhysics() { //Runs pysics of the game -calculates velocity , position etc
	if (loseTimer > 0) {
		loseTimer --;
		return;
	}
	ball.x += ball.velX;
	ball.y += ball.velY;

	if (ball.x <= leftPaddle.x + leftPaddle.width) {
		float ballCentre = ball.y + (ball.width / 2);
		if (ballCentre > leftPaddle.y && ballCentre <= leftPaddle.y + leftPaddle.height) {// ball strikes left paddle
			float yOffset = calculateNormalizedOffset(leftPaddle.y + leftPaddle.height/2, ballCentre, leftPaddle.height/2);
			ball.velX = getHorizBallSpeedRebound(yOffset, BALL_SPEED_H_MIN, BALL_SPEED_H_MAX);
			ball.velY = getVertBallSpeedRebound(yOffset, BALL_SPEED_V_MIN, BALL_SPEED_V_MAX);
			ball.x = leftPaddle.x + leftPaddle.width + 1;
			updateSpeed();// speed is updated evry time the left player touches the ball so that it updates once every two turns
		}
		if (ball.x <= 0) {
			printf("Left loses\n");
			p2w++;// increments wins for Player 2
			fprintf(fp,"lose      win\n");// records results in file
			initSpeed();// Initializes the speeds
			handleLose(LEFT_SIDE);
		}
	}

	if (ball.x + ball.width >= rightPaddle.x) {
		float ballCentre = ball.y + (ball.width / 2);
		if (ballCentre > rightPaddle.y && ballCentre <= rightPaddle.y + rightPaddle.height) {// ball striked right paddle
			float yOffset = calculateNormalizedOffset(rightPaddle.y + rightPaddle.height/2, ballCentre, rightPaddle.height/2);
			ball.velX = -1 * getHorizBallSpeedRebound(yOffset, BALL_SPEED_H_MIN, BALL_SPEED_H_MAX);
			ball.velY = getVertBallSpeedRebound(yOffset, BALL_SPEED_V_MIN, BALL_SPEED_V_MAX);
			ball.x = rightPaddle.x - 1 - ball.width;
		}
		if (ball.x + ball.width >= FIELD_WIDTH) {
			printf("Right loses\n");
			p1w++;// increments wins for Player 1
			fprintf(fp,"win      lose\n");// records results in file
			initSpeed();// Initializes the speeds
			handleLose(RIGHT_SIDE);
		}
	}
	//if (ball.y==FIELD_HEIGHT||ball.y==0)
	//ball.velY*=-1;
	leftPaddle.y = leftPaddle.y + leftPaddle.velY;
	rightPaddle.y = rightPaddle.y + rightPaddle.velY;
}
void checkbounds()// MAkes sure that ball and paddles don't leave the bounds.
{
	if (leftPaddle.y < 0||leftPaddle.y > FIELD_HEIGHT-PADDLE_HEIGHT)
		leftPaddle.velY =0;
	if (rightPaddle.y < 0||rightPaddle.y > FIELD_HEIGHT-PADDLE_HEIGHT)
		rightPaddle.velY =0;
	if (ball.y < BALL_RADIUS || ball.y > FIELD_HEIGHT-BALL_RADIUS)
		ball.velY = ball.velY*-1;
}

int main(int argc, char** argv) {
	initPaddles();
	glfwInit();
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(FIELD_WIDTH, FIELD_HEIGHT, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,FIELD_WIDTH,0,FIELD_HEIGHT,-1.0,1.0);
	glfwSetKeyCallback(&keyboardHandler);
	printf("Enter name of player 1\n");
	scanf("%s",p1);
	printf("Enter name pf player 2\n");
	scanf("%s",p2 );
	fp =fopen("results.txt","w");
	fprintf(fp,"%7s%7s\n",p1,p2);
	for(;;){
		glClearColor(0.0f,0.0f,0.0f,0.0f);
	    glClear(GL_COLOR_BUFFER_BIT);
		if (!glfwGetWindowParam(GLFW_OPENED))
			break;
		renderFrame();
		checkbounds();
		runPhysics();
		usleep(30*1000);
	}
	printf("No. of wins for Player1: %d\n",p1w);
	printf("No. of wins for Player2: %d\n",p2w);
	glfwTerminate();
	return 0;
}
