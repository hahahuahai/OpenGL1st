#include <GL/glew.h>
#include <GL/glfw3.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

GLint width, height;
GLfloat ratio = 1.f;
GLfloat rquad = 0.0f;




void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)return;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case  GLFW_KEY_D:
	{
						GLdouble modelMatrix[16];
						glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
						GLdouble projMatrix[16];
						glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
						GLint viewport[4];
						glGetIntegerv(GL_VIEWPORT, viewport);

						float depth;
						GLdouble winx, winy, winz;
						winx = viewport[2] / 2;
						winy = viewport[3] / 2;

						glReadPixels(winx, winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
						std::cout << "屏幕坐标为：(" << winx << "," << winy << ")" << "的点，深度值为：" << depth << std::endl;

						GLdouble x, y, z;
						gluUnProject(winx, winy, depth, modelMatrix, projMatrix, viewport, &x, &y, &z);
						gluProject(x, y, z, modelMatrix, projMatrix, viewport, &winx, &winy, &winz);

						assert(fabs(winz - depth) < 0.001);
	}
		break;
	default:
		break;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	if (height == 0){
		height = 1;
	}
	if (h > 0)
	{
		ratio = (float)w / (float)h;
	}
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init_opengl(void)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void draw_scene(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glLoadIdentity();
	glTranslatef(-0.5f, -0.5f, -3.0f);
	glRotatef(rquad, 1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);/* f1: front */
	glColor3f(1.0f, 0.0f, 0.5f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f2: bottom */
	glColor3f(1.0f, 0.5f, 0.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f3:back */
	glColor3f(0.0f, 0.5f, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f4: top */
	glColor3f(0.5f, 0.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f5: left */
	glColor3f(0.0f, 1.0f, 0.5f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glBegin(GL_POLYGON);/* f6: right */
	glColor3f(0.5f, 1.0f, 0.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glEnd();
	rquad += 0.8f;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1200, 675, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwGetFramebufferSize(window, &width, &height);
	framebuffer_size_callback(window, width, height);
	glewExperimental = true; // Needed for core propbmpfile
	if (glewInit() != GLEW_OK){
		return -1;
	}

	init_opengl();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		draw_scene(window);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}