
#include <iostream>
#include <GL/glut.h>

using namespace std;

//initializing
float _angle = 0.0f;
static float car1_t = 0.0, car2_t = 0.0, speed1 = 0.0, speed2 = 0.0, speed = 0.0, cloud_t = 0.0, car3_t = 0.0, car4_t = 0.0, sunT = 0.0;

static float  speed3 = 0.0, speed4 = 0.0, speed5 = 0.0, speed6 = 0.0, speed7 = 0.0;

bool start1 = false, start2 = false, start3 = false, start4 = false, start5 = false, start6 = false, start7 = false;
bool start8 = false, start9 = false;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1': start1 = true; speed1 = 0.90; break; //translatn start car 1 blue
	case '!': start1 = false;  break; //translatn stop car 1

	case '2': start2 = true; speed2 = .9; break; //start car 2
	case '@': start2 = false;  break; //stop  car 2

	case '3': start3 = true; speed4 = 0.90; break; // start car 3
	case '#': start3 = false; break; //stop car 3

	case '4': start4 = true; speed5 = 0.90; break; // start car 4
	case '$': start4 = false; break; // stop car 4

	case '5': start5 = true; speed6 = 0.01; break;//speed sun
	case '%': start5 = false; glEnable(GL_LIGHT0);

	case '0':exit(0);
	break;
	}
}

//Initializes 3D rendering
void initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.329412, 0.329412, 0.329412, 1);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable lighting
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH); //Enable smooth shading
}

//Called when the window is resized
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawCircle(float x1, float y1, float z, double radius)
{
	float x2, y2;
	float angle;

	glBegin(GL_POLYGON);

	for (angle = .1f; angle<361.0f; angle += 1.0f)
	{
		x2 = x1 + sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex3f(x2, y2, z);
	}

	glEnd();
}

void ground()		//footpath
{
	glBegin(GL_QUADS);

	float line_w = -4.8;
	glColor3f(0.648824, 0.658824, 0.658824);
	for (int line = 0; line<1; line++)
	{
		glVertex3f(line_w, -2.1, -5.0);
		glVertex3f(line_w, -1.3, -5.0);
		glVertex3f(line_w + 3.40, -1.3, -5.0);
		glVertex3f(line_w + 3.70, -2.1, -5.0);

	}

	float line_w1 = .99;
	glColor3f(0.648824, 0.658824, 0.658824);
	for (int line = 0; line<1; line++)
	{
		glVertex3f(line_w1 + .4, -2.1, -5.0);
		glVertex3f(line_w1, -1.3, -5.0);
		glVertex3f(line_w1 + 4.10, -1.3, -5.0);
		glVertex3f(line_w1 + 4.10, -2.1, -5.0);
	}

	glEnd();
}

void bground() // footpath
{
	glBegin(GL_QUADS);
	glColor3f(0.449412, 0.469412, 0.3829412);//Road

	glVertex3f(-1.25, -2.8, -6.0);
	glColor3f(0.698824, 0.658824, 0.658824);//Road
	glVertex3f(-1.68, -1.5798, -6.0);
	glColor3f(0.449412, 0.469412, 0.3829412);//Road
	glVertex3f(-1.45, -1.725, -6.0);
	glColor3f(0.449412, 0.469412, 0.3829412);
	glVertex3f(-1.09, -2.8, -6.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.658824, 0.658824, 0.658824);
	glVertex3f(.95, -1.5, -5.0);//upper top
	glColor3f(0.449412, 0.469412, 0.3829412);
	glVertex3f(1.0, -1.3, -5.0);//top right
	glColor3f(0.459412, 0.329412, 0.3829412);
	glVertex3f(1.6, -2.1, -5.0);
	glColor3f(0.449412, 0.469412, 0.3829412);
	glVertex3f(1.3, -2.1, -5.0);//bottom left

	glEnd();
}

void background()
{
	glBegin(GL_TRIANGLE_STRIP);

	glColor3f(0.707255, 0.556863, 0.137255);    //grass
	glVertex3f(-4.8, 1.3, -5.0);
	glColor3f(0.137255, 0.556863, 0.137255);
	glVertex3f(-4.8, 0.8, -5.0);
	glColor3f(0.087255, 0.556863, 0.137255);
	glVertex3f(4.8, 0.8, -5.0);
	
	glColor3f(0.607255, 0.556863, 0.137255);
	glVertex3f(4.8, 1.3, -5.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.52, 0.69, 0.87);  //sky

	glVertex3f(-5, 1.0, -5.3);
	glColor3f(0.92, 0.69, 0.87);
	glVertex3f(-5, 2.3, -5.3);
	glVertex3f(5, 2.3, -5.3);
	glColor3f(0.22, 0.69, 0.87);
	glVertex3f(5, 1.0, -5.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.658824, 0.658824, 0.658824); //Roadline
	for (int line = 0; line<1; line++)
	{
		glVertex3f(-4.9, 1.2, -5.0);
		glVertex3f(-4.9, .75, -5.0);
		glVertex3f(6, .75, -5.0);
		glVertex3f(6, 1.2, -5.0);
	}
	glEnd();
}

void roaddivider()
{
	glBegin(GL_QUADS);

	glColor3f(0.117255, 0.506863, 0.137255); //green divider uper left
	float line_x1 = -6.5;
	glBegin(GL_QUADS);
	for (int line = 0; line<2; line++)
	{
		glVertex3f(line_x1, -.18, -8.);
		glVertex3f(line_x1, -.38, -8.0);
		glVertex3f(line_x1 + 3., -.38, -8.0);
		glVertex3f(line_x1 + 3., -.18, -8.0);
		line_x1 += 2.0;
	}

	glColor3f(0.5229412, 0.4029412, 0.329412);//divider lower left
	float line_x11 = -6.5;
	glBegin(GL_QUADS);
	for (int line = 0; line<1; line++)
	{
		glVertex3f(line_x11, -.19, -7.);
		glVertex3f(line_x11, -.34, -7.);
		glVertex3f(line_x11 + 5.158, -.34, -7.0);
		glVertex3f(line_x11 + 5.178, -.19, -7.0);
		line_x11 += 2.0;
	}

	glColor3f(0.117255, 0.506863, 0.137255);//green divider upper right
	float line_x2 = .5;
	glBegin(GL_QUADS);
	for (int line = 0; line<3; line++)
	{
		glVertex3f(line_x2, -.16, -8.);
		glVertex3f(line_x2, -.33, -8.);
		glVertex3f(line_x2 + 3.5, -.33, -8.0);
		glVertex3f(line_x2 + 3.5, -.16, -8.0);
		line_x2 += 2.0;

	}

	glColor3f(0.5229412, 0.4029412, 0.329412); //divider lower right
	float line_x3 = .45;
	glBegin(GL_QUADS);
	for (int line = 0; line<3; line++)
	{
		glVertex3f(line_x3 + .01, -.18, -7.);
		glVertex3f(line_x3 + .03, -.32, -7.);
		glVertex3f(line_x3 + 3.5, -.32, -7.0);
		glVertex3f(line_x3 + 3.5, -.18, -7.0);
		line_x3 += 2.0;
	}

	glEnd();

	glColor3f(0.529412, 0.499412, 0.529412); // BOTTOM CROSSING
	float line_xxxx = -2.5;
	glBegin(GL_QUADS);
	for (int line = 0; line<3; line++)
	{
		glVertex3f(line_xxxx, -02.750, -8.);
		glVertex3f(line_xxxx, -3.0, -8.0);
		glVertex3f(line_xxxx + 3.5, -3.0, -8.0);
		glVertex3f(line_xxxx + 3.5, -2.750, -8.0);
		line_xxxx += 2.0;
	}
	glEnd();

	glColor3f(04.97, 01.58, .98);
	float line_xxxx4 = -2.5;
	glBegin(GL_QUADS);
	for (int line = 0; line<3; line++)
	{
		glVertex3f(line_xxxx4, -02.470, -7.);
		glVertex3f(line_xxxx4, -2.55, -7.);
		glVertex3f(line_xxxx4 + 3.5, -2.55, -7.0);
		glVertex3f(line_xxxx4 + 3.5, -2.470, -7.0);
		line_xxxx4 += 2.0;
	}
	glEnd();

	glFlush();
}

void roadline()
{
	float line_x = -5.0;
	glBegin(GL_QUADS);
	glColor3f(0.4229412, 0.4029412, 0.329412); //small road strip  

	for (int line = 0; line<10; line++)
	{
		glVertex3f(line_x, -1.10, -6.0);
		glVertex3f(line_x, -1.20, -6.0);
		glVertex3f(line_x + .50, -1.20, -6.0);
		glVertex3f(line_x + .50, -1.10, -6.0);
		line_x += 1.9;
	}

	line_x = -5.0;
	for (int line = 0; line<18; line++)
	{
		glVertex3f(line_x, 0.25, -6.0);
		glVertex3f(line_x, 0.15, -6.0);
		glVertex3f(line_x + .50, 0.15, -6.0);
		glVertex3f(line_x + .50, 0.25, -6.0);
		line_x += 1.9;
	}
	glEnd();
}

void car1()
{
	glBegin(GL_QUADS);
	glColor3f(1, 0.498039, 0);
	//top||frontview
	glVertex3f(1.64, -0.6, -5.0);
	glVertex3f(1.66, -0.6, -5.0);
	glVertex3f(1.66, -0.4, -5.04);
	glVertex3f(1.64, -0.4, -5.04);

	//top||backtview
	glColor3f(0.87, 0.58, 0.98);
	glVertex3f(1.64, -0.6, -5.3);
	glVertex3f(1.66, -0.6, -5.3);
	glVertex3f(1.66, -0.4, -5.26);
	glVertex3f(1.64, -0.4, -5.26);
	glEnd();

	glColor3f(0., .0, .0);
	//wheel
	drawCircle(1.2, -0.88, -5.0, 0.12);
	drawCircle(1.2, -0.88, -5.3, 0.12);
	drawCircle(2.0, -0.88, -5.3, 0.12);
	drawCircle(2.0, -0.88, -5.0, 0.12);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.558824, 0.658824, 0.658824);
	//top-frontview-front glass
	glVertex3f(1.32, -0.6, -5.0);
	glVertex3f(1.98, -0.6, -5.0);
	glVertex3f(1.88, -0.42, -5.04);
	glVertex3f(1.47, -0.42, -5.04);
	//top-back glass-backview
	glColor3f(0.658824, 0.658824, 0.658824);
	glVertex3f(1.32, -0.6, -5.3);
	glVertex3f(1.98, -0.6, -5.3);
	glVertex3f(1.88, -0.42, -5.26);
	glVertex3f(1.47, -0.42, -5.26);
	//top-rightview right glass
	glColor3f(0.658824, 0.658824, 0.658824);
	glVertex3f(1.98, -0.58, -5.0);
	glVertex3f(1.98, -0.58, -5.3);
	glVertex3f(1.88, -0.42, -5.26);
	glVertex3f(1.88, -0.42, -5.04);
	//top-leftglass
	glVertex3f(1.3, -0.59, -5.0);
	glVertex3f(1.3, -0.59, -5.3);
	glVertex3f(1.43, -0.41, -5.26);
	glVertex3f(1.43, -0.41, -5.04);
	glEnd;
	glColor3f(255, 255, 255);
	//body-frontview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(2.0, -0.9, -5.0);
	glVertex3f(1.3, -0.9, -5.0);
	//body-backview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(2.0, -0.9, -5.3);
	glVertex3f(1.3, -0.9, -5.3);
	//body-bottomview
	glVertex3f(0.9, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.0);
	glVertex3f(0.9, -0.9, -5.0);

	//front-frontview
	glColor3f(255, 255, 255);
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(1.0, -0.7, -5.0);
	glVertex3f(1.0, -0.9, -5.0);
	glVertex3f(1.3, -0.9, -5.0);
	glVertex3f(1.0, -0.7, -5.0);

	glColor3f(255, 255, 255);// color
	glVertex3f(0.9, -0.75, -5.0);
	glVertex3f(0.9, -0.9, -5.0);
	glVertex3f(1.0, -0.9, -5.0);
	//front-backview	
	glColor3f(1, 0, 0);
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(1.0, -0.9, -5.3);
	glVertex3f(1.3, -0.9, -5.3);

	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(0.9, -0.75, -5.3);
	glVertex3f(0.9, -0.9, -5.3);
	glVertex3f(1.0, -0.9, -5.3);
	//front-topview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(1.0, -0.7, -5.0);
	glVertex3f(1.3, -0.6, -5.0);

	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(0.9, -0.75, -5.3);
	glVertex3f(0.9, -0.75, -5.0);
	glVertex3f(1.0, -0.7, -5.0);

	//front bumper-frontview
	glVertex3f(0.9, -0.87, -5.0);
	glVertex3f(0.9, -0.8, -5.0);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.87, -5.0);

	//front bumper-backview
	glVertex3f(0.9, -0.87, -5.3);
	glVertex3f(0.9, -0.8, -5.3);
	glVertex3f(0.87, -0.8, -5.3);
	glVertex3f(0.87, -0.87, -5.3);
	//front bumper-bottomview
	glVertex3f(0.9, -0.87, -5.3);
	glVertex3f(0.9, -0.87, -5.0);
	glVertex3f(0.87, -0.87, -5.0);
	glVertex3f(0.87, -0.87, -5.3);
	//front bumper-leftview
	//glColor3f(.2, .1, .16);
	glVertex3f(0.87, -0.87, -5.3);
	glVertex3f(0.87, -0.8, -5.3);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.87, -5.0);
	//front bumper-topkview
	glVertex3f(0.9, -0.8, -5.3);
	glVertex3f(0.9, -0.8, -5.0);
	glColor3f(255, 255, 255);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.8, -5.3);

	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.2, -0.9, -5.0);
	glVertex3f(2.0, -0.9, -5.0);
	glColor3f(255, 255, 255);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.2, -0.9, -5.0);
	glColor3f(1, 0, 0);
	glVertex3f(2.3, -0.9, -5.0);
	glVertex3f(2.3, -0.73, -5.0);
	//back-backview

	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(2.2, -0.68, -5.3);

	glVertex3f(2.2, -0.9, -5.3);
	glVertex3f(2.0, -0.9, -5.3);

	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.3);
	glVertex3f(2.3, -0.73, -5.3);
	//back-topview

	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.0, -0.6, -5.0);

	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.3, -0.73, -5.0);
	glVertex3f(2.3, -0.73, -5.3);
	//back bumper-frontview
	glVertex3f(2.35, -0.87, -5.0);
	glVertex3f(2.3, -0.87, -5.0);
	glVertex3f(2.3, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.0);
	//back bumper-backview
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.3);
	glVertex3f(2.3, -0.77, -5.3);
	glVertex3f(2.35, -0.77, -5.3);
	//back bumper-rightview
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.35, -0.87, -5.0);
	glVertex3f(2.35, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.3);
	//back bumper-bottomview
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.0);
	glVertex3f(2.35, -0.87, -5.0);
	//back bumper-topview
	glVertex3f(2.35, -0.77, -5.3);
	glVertex3f(2.3, -0.77, -5.3);
	glVertex3f(2.3, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.0);
	//top-backview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.25);
	//top-frontview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(1.9, -0.4, -5.05);
	glVertex3f(1.45, -0.4, -5.05);
	//top-topview
	glVertex3f(1.9, -0.4, -5.05);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.05);
	//top-leftview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(1.45, -0.4, -5.05);
	glVertex3f(1.45, -0.4, -5.25);
	glVertex3f(1.3, -0.6, -5.3);
	glColor3f(0, 0, 0);
	//top-rightview
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.9, -0.4, -5.05);

	glEnd();
}

void car()
{
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	//top||frontview
	glVertex3f(1.64, -0.6, -5.0);
	glVertex3f(1.66, -0.6, -5.0);
	glVertex3f(1.66, -0.4, -5.04);
	glVertex3f(1.64, -0.4, -5.04);
	//top||backtview
	glColor3f(0, 0, 0);
	glVertex3f(1.64, -0.6, -5.3);
	glVertex3f(1.66, -0.6, -5.3);
	glVertex3f(1.66, -0.4, -5.26);
	glVertex3f(1.64, -0.4, -5.26);
	glEnd();

	glColor3f(0, 0, 0.0);
	//wheel
	drawCircle(1.2, -0.88, -5.0, 0.12);
	drawCircle(1.2, -0.88, -5.3, 0.12);
	drawCircle(2.0, -0.88, -5.3, 0.12);
	drawCircle(2.0, -0.88, -5.0, 0.12);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0.0);
	//top-frontview-front glass
	glVertex3f(1.32, -0.6, -5.0);
	glVertex3f(1.98, -0.6, -5.0);
	glVertex3f(1.88, -0.42, -5.04);
	glVertex3f(1.47, -0.42, -5.04);
	//top-back glass-backview
	glVertex3f(1.32, -0.6, -5.3);
	glVertex3f(1.98, -0.6, -5.3);
	glVertex3f(1.88, -0.42, -5.26);
	glVertex3f(1.47, -0.42, -5.26);
	//top-rightview right glass
	glVertex3f(1.98, -0.58, -5.0);
	glVertex3f(1.98, -0.58, -5.3);
	glVertex3f(1.88, -0.42, -5.26);
	glVertex3f(1.88, -0.42, -5.04);
	//top-leftglass
	glVertex3f(1.3, -0.59, -5.0);
	glVertex3f(1.3, -0.59, -5.3);
	glVertex3f(1.43, -0.41, -5.26);
	glVertex3f(1.43, -0.41, -5.04);

	glColor3f(1, 0, 0);
	//body-frontview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.0);

	glColor3f(0.2, .65, .26);
	glVertex3f(2.0, -0.9, -5.0);
	glVertex3f(1.3, -0.9, -5.0);
	//body-backview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(2.0, -0.9, -5.3);
	glVertex3f(1.3, -0.9, -5.3);
	//body-bottomview
	glVertex3f(0.9, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.0);
	glVertex3f(0.9, -0.9, -5.0);

	//front-frontview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(1.0, -0.7, -5.0);

	glVertex3f(1.0, -0.9, -5.0);
	glVertex3f(1.3, -0.9, -5.0);
	glVertex3f(1.0, -0.7, -5.0);
	glVertex3f(0.9, -0.75, -5.0);
	glVertex3f(0.9, -0.9, -5.0);
	glVertex3f(1.0, -0.9, -5.0);
	//front-backview

	glVertex3f(1.3, -0.6, -5.3);

	glVertex3f(1.0, -0.7, -5.3);

	glVertex3f(1.0, -0.9, -5.3);
	glVertex3f(1.3, -0.9, -5.3);

	glVertex3f(1.0, -0.7, -5.3);


	glVertex3f(0.9, -0.75, -5.3);
	glVertex3f(0.9, -0.9, -5.3);
	glVertex3f(1.0, -0.9, -5.3);
	//front-topview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(1.0, -0.7, -5.0);
	glVertex3f(1.3, -0.6, -5.0);

	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(0.9, -0.75, -5.3);
	glVertex3f(0.9, -0.75, -5.0);
	glVertex3f(1.0, -0.7, -5.0);

	//front bumper-frontview
	glVertex3f(0.9, -0.87, -5.0);
	glVertex3f(0.9, -0.8, -5.0);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.87, -5.0);
	//front bumper-backview
	glVertex3f(0.9, -0.87, -5.3);
	glVertex3f(0.9, -0.8, -5.3);
	glVertex3f(0.87, -0.8, -5.3);
	glVertex3f(0.87, -0.87, -5.3);

	//front bumper-bottomview
	glVertex3f(0.9, -0.87, -5.3);
	glVertex3f(0.9, -0.87, -5.0);
	glVertex3f(0.87, -0.87, -5.0);
	glVertex3f(0.87, -0.87, -5.3);
	//front bumper-leftview
	glVertex3f(0.87, -0.87, -5.3);
	glVertex3f(0.87, -0.8, -5.3);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.87, -5.0);
	//front bumper-topkview
	glVertex3f(0.9, -0.8, -5.3);
	glVertex3f(0.9, -0.8, -5.0);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.8, -5.3);

	//back-frontview
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.2, -0.9, -5.0);
	glVertex3f(2.0, -0.9, -5.0);

	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.2, -0.9, -5.0);
	glVertex3f(2.3, -0.9, -5.0);
	glVertex3f(2.3, -0.73, -5.0);

	//back-backview
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.9, -5.3);
	glVertex3f(2.0, -0.9, -5.3);

	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.3);
	glVertex3f(2.3, -0.73, -5.3);
	//back-topview
	glColor3f(1, 0, 0);
	glColor3f(0.71, .65, .26);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.0, -0.6, -5.0);

	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.3, -0.73, -5.0);
	glVertex3f(2.3, -0.73, -5.3);

	//back bumper-frontview
	glVertex3f(2.35, -0.87, -5.0);
	glVertex3f(2.3, -0.87, -5.0);
	glVertex3f(2.3, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.0);

	//back bumper-backview
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.3);
	glVertex3f(2.3, -0.77, -5.3);
	glVertex3f(2.35, -0.77, -5.3);
	//back bumper-rightview
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.35, -0.87, -5.0);
	glVertex3f(2.35, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.3);
	//back bumper-bottomview
	//glColor3f(0.71, .65, .26);
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.0);
	glVertex3f(2.35, -0.87, -5.0);
	//back bumper-topview

	glVertex3f(2.35, -0.77, -5.3);
	glVertex3f(2.3, -0.77, -5.3);
	glVertex3f(2.3, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.0);

	//top-backview


	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.25);
	//top-frontview

	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(1.9, -0.4, -5.05);
	glVertex3f(1.45, -0.4, -5.05);
	//top-topview

	glColor3f(1, 0, 0);
	glVertex3f(1.9, -0.4, -5.05);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.05);
	//top-leftview

	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(1.45, -0.4, -5.05);
	glVertex3f(1.45, -0.4, -5.25);
	glVertex3f(1.3, -0.6, -5.3);
	glColor3f(0, 0, 0);
	//top-rightview
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.9, -0.4, -5.05);

	glEnd();
}

void car3_3()
{
	glBegin(GL_QUADS);

	//top||frontview
	glVertex3f(1.64, -0.6, -5.0);
	glVertex3f(1.66, -0.6, -5.0);
	glVertex3f(1.66, -0.4, -5.04);
	glVertex3f(1.64, -0.4, -5.04);
	//top||backview
	glVertex3f(1.64, -0.6, -5.3);
	glVertex3f(1.66, -0.6, -5.3);
	glVertex3f(1.66, -0.4, -5.26);
	glVertex3f(1.64, -0.4, -5.26);
	glEnd();

	glColor3f(0., .0, .0);
	//wheel
	drawCircle(1.2, -0.88, -5.0, 0.12);
	drawCircle(1.2, -0.88, -5.3, 0.12);
	drawCircle(2.0, -0.88, -5.3, 0.12);
	drawCircle(2.0, -0.88, -5.0, 0.12);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0.0);
	//top-frontview-front glass
	glVertex3f(1.32, -0.6, -5.0);
	glVertex3f(1.98, -0.6, -5.0);
	glVertex3f(1.88, -0.42, -5.04);
	glVertex3f(1.47, -0.42, -5.04);
	//top-back glass-backview
	glVertex3f(1.32, -0.6, -5.3);
	glVertex3f(1.98, -0.6, -5.3);
	glVertex3f(1.88, -0.42, -5.26);
	glVertex3f(1.47, -0.42, -5.26);
	//top-rightview right glass
	glVertex3f(1.98, -0.58, -5.0);
	glVertex3f(1.98, -0.58, -5.3);
	glVertex3f(1.88, -0.42, -5.26);
	glVertex3f(1.88, -0.42, -5.04);
	//top-leftglass
	glVertex3f(1.3, -0.59, -5.0);
	glVertex3f(1.3, -0.59, -5.3);
	glVertex3f(1.43, -0.41, -5.26);
	glVertex3f(1.43, -0.41, -5.04);
	glEnd;
	
	glColor3f(0, 0, 0.98);
	//body-frontview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.0);
	glColor3f(0.0, 0.0, 1.2);
	glVertex3f(2.0, -0.9, -5.0);
	glVertex3f(1.3, -0.9, -5.0);
	//body-backview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(2.0, -0.6, -5.3);
	glColor3f(0.35, 0.35, 0.67);
	glVertex3f(2.0, -0.9, -5.3);
	glVertex3f(1.3, -0.9, -5.3);
	//body-bottomview
	glColor3f(0,0,1);
	glVertex3f(0.9, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.0);
	glVertex3f(0.9, -0.9, -5.0);

	//front-frontview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(1.0, -0.7, -5.0);
	glVertex3f(1.0, -0.9, -5.0);
	glVertex3f(1.3, -0.9, -5.0);
	glVertex3f(1.0, -0.7, -5.0);
	glVertex3f(0.9, -0.75, -5.0);
	glColor3f(0,0,0.8);
	glVertex3f(0.9, -0.9, -5.0);
	glVertex3f(1.0, -0.9, -5.0);
	//front-backview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(1.0, -0.9, -5.3);
	glVertex3f(1.3, -0.9, -5.3);

	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(0.9, -0.75, -5.3);
	glVertex3f(0.9, -0.9, -5.3);
	glVertex3f(1.0, -0.9, -5.3);
	//front-topview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(1.0, -0.7, -5.0);
	glVertex3f(1.3, -0.6, -5.0);

	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(0.9, -0.75, -5.3);
	glVertex3f(0.9, -0.75, -5.0);
	glVertex3f(1.0, -0.7, -5.0);

	//front bumper-frontview
	glVertex3f(0.9, -0.87, -5.0);
	glVertex3f(0.9, -0.8, -5.0);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.87, -5.0);
	//front bumper-backview
	glVertex3f(0.9, -0.87, -5.3);
	glVertex3f(0.9, -0.8, -5.3);
	glVertex3f(0.87, -0.8, -5.3);
	glVertex3f(0.87, -0.87, -5.3);
	//front bumper-bottomview
	glVertex3f(0.9, -0.87, -5.3);
	glVertex3f(0.9, -0.87, -5.0);
	glVertex3f(0.87, -0.87, -5.0);
	glVertex3f(0.87, -0.87, -5.3);
	//front bumper-leftview
	glVertex3f(0.87, -0.87, -5.3);
	glVertex3f(0.87, -0.8, -5.3);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.87, -5.0);
	//front bumper-topkview
	glVertex3f(0.9, -0.8, -5.3);
	glVertex3f(0.9, -0.8, -5.0);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.8, -5.3);

	//back-frontview
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.2, -0.9, -5.0);
	glVertex3f(2.0, -0.9, -5.0);

	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.2, -0.9, -5.0);
	glVertex3f(2.3, -0.9, -5.0);
	glVertex3f(2.3, -0.73, -5.0);
	//back-backview
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.9, -5.3);
	glVertex3f(2.0, -0.9, -5.3);

	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.3);
	glVertex3f(2.3, -0.73, -5.3);
	//back-topview
	glColor3f(1, 0, 0);
	glColor3f(0.71, .65, .26);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.3, -0.73, -5.0);
	glVertex3f(2.3, -0.73, -5.3);

	//back bumper-frontview
	glVertex3f(2.35, -0.87, -5.0);
	glVertex3f(2.3, -0.87, -5.0);
	glVertex3f(2.3, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.0);
	//back bumper-backview
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.3);
	glVertex3f(2.3, -0.77, -5.3);
	glVertex3f(2.35, -0.77, -5.3);
	//back bumper-rightview
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.35, -0.87, -5.0);
	glVertex3f(2.35, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.3);
	//back bumper-bottomview
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.0);
	glVertex3f(2.35, -0.87, -5.0);
	//back bumper-topview
	glVertex3f(2.35, -0.77, -5.3);
	glVertex3f(2.3, -0.77, -5.3);
	glVertex3f(2.3, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.0);
	//top-backview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.25);
	//top-frontview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(1.9, -0.4, -5.05);
	glVertex3f(1.45, -0.4, -5.05);
	//top-topview
	glColor3f(1, 0, 0);
	glVertex3f(1.9, -0.4, -5.05);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.05);
	//top-leftview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(1.45, -0.4, -5.05);
	glVertex3f(1.45, -0.4, -5.25);
	glVertex3f(1.3, -0.6, -5.3);
	glColor3f(0, 0, 0);
	//top-rightview
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.9, -0.4, -5.05);

	glEnd();
}

void car4_4()
{
	glBegin(GL_QUADS);
	glColor3f(1, 1, 0);
	//top||frontview
	glVertex3f(1.64, -0.6, -5.0);
	glVertex3f(1.66, -0.6, -5.0);
	glVertex3f(1.66, -0.4, -5.04);
	glVertex3f(1.64, -0.4, -5.04);
	//top||backtview
	glColor3f(0, 0, 0);
	glVertex3f(1.64, -0.6, -5.3);
	glVertex3f(1.66, -0.6, -5.3);
	glVertex3f(1.66, -0.4, -5.26);
	glVertex3f(1.64, -0.4, -5.26);
	glEnd();

	glColor3f(0, 0, 0.0);
	//wheel
	drawCircle(1.2, -0.88, -5.0, 0.12);
	drawCircle(1.2, -0.88, -5.3, 0.12);
	drawCircle(2.0, -0.88, -5.3, 0.12);
	drawCircle(2.0, -0.88, -5.0, 0.12);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0.0);
	//top-frontview-front glass
	glVertex3f(1.32, -0.6, -5.0);
	glVertex3f(1.98, -0.6, -5.0);
	glVertex3f(1.88, -0.42, -5.04);
	glVertex3f(1.47, -0.42, -5.04);
	//top-back glass-backview
	glVertex3f(1.32, -0.6, -5.3);
	glVertex3f(1.98, -0.6, -5.3);
	glVertex3f(1.88, -0.42, -5.26);
	glVertex3f(1.47, -0.42, -5.26);
	//top-rightview right glass
	glVertex3f(1.98, -0.58, -5.0);
	glVertex3f(1.98, -0.58, -5.3);
	glVertex3f(1.88, -0.42, -5.26);
	glVertex3f(1.88, -0.42, -5.04);
	//top-leftglass
	glVertex3f(1.3, -0.59, -5.0);
	glVertex3f(1.3, -0.59, -5.3);
	glVertex3f(1.43, -0.41, -5.26);
	glVertex3f(1.43, -0.41, -5.04);

	glColor3f(1, 0, 0);
	//body-frontview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.0);
	glColor3f(0.9, .69, .29);
	glVertex3f(2.0, -0.9, -5.0);
	glVertex3f(1.3, -0.9, -5.0);
	//body-backview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(2.0, -0.6, -5.3);
	glColor3f(0.4, .64, .24);
	glVertex3f(2.0, -0.9, -5.3);
	glVertex3f(1.3, -0.9, -5.3);
	//body-bottomview
	glVertex3f(0.9, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.0);
	glVertex3f(0.9, -0.9, -5.0);
	//front-frontview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(1.0, -0.7, -5.0);
	glVertex3f(1.0, -0.9, -5.0);
	glVertex3f(1.3, -0.9, -5.0);
	glVertex3f(1.0, -0.7, -5.0);
	glVertex3f(0.9, -0.75, -5.0);
	glVertex3f(0.9, -0.9, -5.0);
	glVertex3f(1.0, -0.9, -5.0);
	//front-backview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(1.0, -0.9, -5.3);
	glVertex3f(1.3, -0.9, -5.3);
	glVertex3f(1.0, -0.7, -5.3);


	glVertex3f(0.9, -0.75, -5.3);
	glVertex3f(0.9, -0.9, -5.3);
	glVertex3f(1.0, -0.9, -5.3);
	//front-topview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(1.0, -0.7, -5.0);
	glVertex3f(1.3, -0.6, -5.0);

	glVertex3f(1.0, -0.7, -5.3);
	glVertex3f(0.9, -0.75, -5.3);
	glVertex3f(0.9, -0.75, -5.0);
	glVertex3f(1.0, -0.7, -5.0);
	//front bumper-frontview
	glVertex3f(0.9, -0.87, -5.0);
	glVertex3f(0.9, -0.8, -5.0);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.87, -5.0);
	//front bumper-backview
	glVertex3f(0.9, -0.87, -5.3);
	glVertex3f(0.9, -0.8, -5.3);
	glVertex3f(0.87, -0.8, -5.3);
	glVertex3f(0.87, -0.87, -5.3);
	//front bumper-bottomview
	glVertex3f(0.9, -0.87, -5.3);
	glVertex3f(0.9, -0.87, -5.0);
	glVertex3f(0.87, -0.87, -5.0);
	glVertex3f(0.87, -0.87, -5.3);
	//front bumper-leftview
	glVertex3f(0.87, -0.87, -5.3);
	glVertex3f(0.87, -0.8, -5.3);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.87, -5.0);
	//front bumper-topkview
	glVertex3f(0.9, -0.8, -5.3);
	glVertex3f(0.9, -0.8, -5.0);
	glVertex3f(0.87, -0.8, -5.0);
	glVertex3f(0.87, -0.8, -5.3);
	//back-frontview
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.2, -0.9, -5.0);
	glVertex3f(2.0, -0.9, -5.0);

	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.2, -0.9, -5.0);
	glVertex3f(2.3, -0.9, -5.0);
	glVertex3f(2.3, -0.73, -5.0);
	//back-backview
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.9, -5.3);
	glVertex3f(2.0, -0.9, -5.3);

	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.9, -5.3);
	glVertex3f(2.3, -0.9, -5.3);
	glVertex3f(2.3, -0.73, -5.3);
	//back-topview
	glColor3f(1, 0, 0);
	glColor3f(0.71, .65, .26);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.0, -0.6, -5.0);

	glVertex3f(2.2, -0.68, -5.3);
	glVertex3f(2.2, -0.68, -5.0);
	glVertex3f(2.3, -0.73, -5.0);
	glVertex3f(2.3, -0.73, -5.3);
	//back bumper-frontview
	glVertex3f(2.35, -0.87, -5.0);
	glVertex3f(2.3, -0.87, -5.0);
	glVertex3f(2.3, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.0);
	//back bumper-backview
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.3);
	glVertex3f(2.3, -0.77, -5.3);
	glVertex3f(2.35, -0.77, -5.3);
	//back bumper-rightview
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.35, -0.87, -5.0);
	glVertex3f(2.35, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.3);
	//back bumper-bottomview
//	glColor3f(0.71, .65, .26);
	glVertex3f(2.35, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.3);
	glVertex3f(2.3, -0.87, -5.0);
	glVertex3f(2.35, -0.87, -5.0);
	//back bumper-topview
	glVertex3f(2.35, -0.77, -5.3);
	glVertex3f(2.3, -0.77, -5.3);
	glVertex3f(2.3, -0.77, -5.0);
	glVertex3f(2.35, -0.77, -5.0);

	//top-backview
	glVertex3f(1.3, -0.6, -5.3);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.25);
	//top-frontview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(1.9, -0.4, -5.05);
	glVertex3f(1.45, -0.4, -5.05);
	//top-topview
	glColor3f(1, 0, 0);
	glVertex3f(1.9, -0.4, -5.05);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.25);
	glVertex3f(1.45, -0.4, -5.05);
	//top-leftview
	glVertex3f(1.3, -0.6, -5.0);
	glVertex3f(1.45, -0.4, -5.05);
	glVertex3f(1.45, -0.4, -5.25);
	glVertex3f(1.3, -0.6, -5.3);
	glColor3f(0, 0, 0);
	//top-rightview
	glVertex3f(2.0, -0.6, -5.0);
	glVertex3f(2.0, -0.6, -5.3);
	glVertex3f(1.9, -0.4, -5.25);
	glVertex3f(1.9, -0.4, -5.05);

	glEnd();
}

void car3()
{
	glPushMatrix();
	glTranslatef(-6, 1.12, -11);
	glRotatef(180, 0, 1, 0);
	car3_3();
	glPopMatrix();
}

void car4()
{
	glPushMatrix();
	glTranslatef(-11, 1.12, -11);
	glRotatef(180, 0, 1.0, 0);
	car4_4();
	glPopMatrix();
}

void hill()
{
	glColor3f(0.60296875, 0.49019607843, 0.41960784313);
	glBegin(GL_TRIANGLE_STRIP);	//1st hill
	glVertex3f(-2, 1.13, -5);
	glVertex3f(-1.65, 1.130, -5);
	glColor3f(0.70296875, 0.49019607843, 0.41960784313);
	glVertex3f(-1., 1.1, -5);
	glColor3f(0.60296875, 0.49019607843, 0.41960784313);
	glVertex3f(-1.25, 1.4, -5);

	glVertex3f(-1.31, 1.03, -5.0);   //2nd hill
	glColor3f(0.70296875, 0.49019607843, 0.41960784313);
	glVertex3f(-0.8, 1.5, -5);
	glVertex3f(-0.5, 1.0, -5);
	glColor3f(0.60296875, 0.49019607843, 0.41960784313);
	glVertex3f(-0.28, 1.3, -5);
	glVertex3f(-0.6, 1.28, -5);
	glVertex3f(-0.3, 1.0, -5);
	glColor3f(0.54296875, 0.49019607843, 0.41960784313);
	glVertex3f(-0.45, 1.4, -5);
	glVertex3f(-0.49, 1.2, -5);
	glColor3f(0.65296875, 0.49019607843, 0.41960784313);
	glVertex3f(-.1, 1.5, -5);

	glVertex3f(0.0, 1.03, -5);	//3rd hill
	glColor3f(0.65296875, 0.49019607843, 0.41960784313);
	glVertex3f(0.2, 1.03, -5);
	glColor3f(0.67296875, 0.49019607843, 0.41960784313);
	glVertex3f(.6, 1.6, -5);
	glColor3f(0.54296875, 0.49019607843, 0.41960784313);
	glVertex3f(.7, 1.7, -5);
	glColor3f(0.67296875, 0.49019607843, 0.41960784313);
	
	glVertex3f(1.3, 1.01, -5);    //4th hill
	glColor3f(0.62296875, 0.49019607843, 0.41960784313);
	glVertex3f(-0.6, 1.03, -5);
	glVertex3f(.0, 1.2, -5);
	glVertex3f(.6, 1.01, -5);
	glVertex3f(0.6, 1.03, -5);
	glVertex3f(1.0, 1.4, -5);
	glVertex3f(1.4, 1.01, -5);  

	glEnd();
}

void dustbin()
{
	glColor3f(0.94117647058, 0.94117647058, 0.94117647058);
	glBegin(GL_QUADS);//1st white
	glVertex3f(-3.4, -2.0, -5);
	glVertex3f(-3.3, -2.0, -5);
	glVertex3f(-3.3, -1.55, -5);
	glVertex3f(-3.4, -1.55, -5);

	glBegin(GL_QUADS);//2nd white
	glVertex3f(-3.2, -2.0, -5);
	glVertex3f(-3.1, -2.0, -5);
	glVertex3f(-3.1, -1.55, -5);
	glVertex3f(-3.2, -1.55, -5);

	glColor3f(0.42156862745, 0.42156862745, 0.42156862745);
	glBegin(GL_QUADS);//body
	glVertex3f(-3.5, -2.1, -5);
	glVertex3f(-3.0, -2.1, -5);
	glVertex3f(-3.0, -1.5, -5);
	glVertex3f(-3.5, -1.5, -5);

	glBegin(GL_QUADS);//cover
	glVertex3f(-3.55, -1.48, -5);
	glVertex3f(-2.94, -1.48, -5);
	glVertex3f(-2.94, -1.38, -5);
	glVertex3f(-3.55, -1.38, -5);
	glEnd();
}

void sun()
{
	glColor3f(0.88296875, 0.43019607843, 0.41960784313);
	drawCircle(0.0, 1.85, -5.1, 0.26);
}

void cloud()
{
	glColor3f(0.62, 0.69, 0.87);
	drawCircle(-3.5, 1.55, -5.2, 0.2);

	drawCircle(-2.8, 1.55, -5.2, 0.2);
	drawCircle(-3.27, 1.75, -5.2, 0.18);
	drawCircle(-3.28, 1.45, -5.2, 0.21);
	drawCircle(-3.0, 1.75, -5.2, 0.18);
	drawCircle(-3.0, 1.45, -5.2, 0.23);

	drawCircle(-1.50, 1.55, -5.2, 0.2);
	drawCircle(-0.83, 1.55, -5.2, 0.2);
	drawCircle(-01.27, 1.75, -5.2, 0.18);
	drawCircle(-01.29, 1.45, -5.2, 0.21);
	drawCircle(-1., 1.75, -5.2, 0.18);
	drawCircle(-1., 1.45, -5.2, 0.23);

	glPopMatrix();

	if (cloud_t>5.3)
		cloud_t = -3.3;
	else
		cloud_t += 0.001;

}

void cloud2()
{
	glPushMatrix();

	glTranslatef(cloud_t -2.6, 0.17, 0);
	cloud();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cloud_t - .5, 0.13, 0);
	cloud();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cloud_t - 4.6, 0.22, 0);
	cloud();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cloud_t - 2.5, 0.19, 0);
	cloud();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cloud_t - 2.69, 0.19, 0);
	cloud();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cloud_t + 4.9, 0.18, 0);
	cloud();
	glPopMatrix();
}

//Draws the 3D scene
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (start1 == true)  // car one starting from right
	{
		car1_t -= +speed1;

		if (car1_t<-12){
			car1_t = +1.9;
		}
	}

	if (start2 == true)  // car 2 starting from right
	{
		car2_t -= +speed2;

		if (car2_t<-12){
			car2_t =+ 3.3;
		}
	}

	if (start3 == true)  // car 3 starting from left
	{
		car3_t += speed4;

		if (car3_t>17){
			car3_t = +3.5;
		}
	}

	if (start4 == true) // car 4 starting from left
	{
		car4_t += speed5;

		if (car4_t>17){
			car4_t = .3;
		}
	}

	if (start5 == true)  // sun 
	{
		sunT -= +speed6;
		if (sunT<-.57){
			sunT += 7;

			glDisable(GL_LIGHT0);
		}
	}

	// car 1
	glPushMatrix();
	glTranslatef(car1_t + 5, -.25, -0.01);
	car1();
	glPopMatrix();

	// car 2
	glPushMatrix();
	glTranslatef(car2_t + 5, .11, -0.6);
	car();
	glPopMatrix();

	//car 3
	glPushMatrix();
	glTranslatef(car3_t - 3.71, .2, -.8);
	car3();
	glPopMatrix();

	//car 4
	glPushMatrix();
	glTranslatef(car4_t + 1, -.1, 0);
	car4();
	glPopMatrix();

	//sun
	glPushMatrix();
	glTranslatef(0, sunT, 0);
	sun();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(cloud_t, -.2, 0);
	cloud();
	cloud2();
	glPopMatrix();

	glPushMatrix();
	dustbin();
	roadline();
	ground();
	bground();
	background();
	hill();
	cloud2();
	roaddivider();

	glutSwapBuffers();
}

void update(int value)
{
	_angle += 1.5f;

	if (_angle > 360)
	{
		_angle -= 360;
	}

	glutPostRedisplay();

	glutTimerFunc(100, update, 0);
}

int main(int argc, char** argv)
{
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1380, 700);

	//Create the window
	glutCreateWindow("MOVING CAR");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutTimerFunc(10, update, 0); //Add a timer

	glutMainLoop();

	return 0;
}
