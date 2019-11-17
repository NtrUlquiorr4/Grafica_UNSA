#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <math.h>
#include <iostream>

using namespace std;

//trabajando con valores para la perspectiva inicial de la camara
glm::vec3 Camara_Pos   = glm::vec3(1.0, 1.0, 0.0);
glm::vec3 Camara_Front = glm::vec3(-1.0, 0.0, -1.0);
glm::vec3 Camara_Up    = glm::vec3(0.0, 1.0, -1.0);
//variable para determinar si se realizo el cambio de perspectiva
bool Perspectiva = true;
//se habilita el cambio de perspectiva.
void Cambio_Perspectiva(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(action == GLFW_PRESS){
		if(key == GLFW_KEY_P){
			perspectiva = !perspectiva;
		}
	}
}

void Mostrar( GLFWwindow* window ) {

	GLint windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(perspectiva){ //haciendo el cambio ortogonal a perspectiva con los valores ingresados
		gluPerspective(60, (double)windowWidth / (double)windowHeight, 0.1, 100 );
		gluLookAt(Camara_Pos[0], Camara_Pos[1], Camara_Pos[2], 
		Camara_Pos[0] + Camara_Front[0], Camara_Pos[1] + Camara_Front[1], Camara_Pos[2] + Camara_Front[2], 
		Camara_Up[0], Camara_Up[1], Camara_Up[2]);
	} else {
		double dist = sqrt(1 / 3.0);
		gluLookAt(dist, dist, dist,
					0.0,  0.0,  0.0,
					0.0,  1.0,  0.0);
	}

	glMatrixMode(GL_MODELVIEW);

	glBegin(GL_LINES);//perspectiva

	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(1.0, 0.0, 0.0);
	glVertex3d(1.0, 0.0, 0.0);

	glColor3d(0.0, 1.0, 0.0);
	glVertex3d(0.0, 1.0, 0.0);
	glVertex3d(0.0, 1.0, 0.0);

	glColor3d(0.0, 0.0, 1.0);
	glVertex3d(0.0, 0.0, 1.0);
	glVertex3d(0.0, 0.0, 1.0);

	glEnd();
	glFlush();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

int main(int argc, char** argv) {
	
	GLFWwindow* window = glfwCreateWindow(900, 600, "Grafica_perspectiva", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, Cambio_Perspectiva);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	Mostrar( window );
	glfwDestroyWindow(window);
	glfwTerminate();
}