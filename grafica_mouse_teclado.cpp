#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

using namespace std;

//Variables para almacenar coordenadas antes y despues del movimiento del mouse

double anteriorMouseX, anteriorMouseY; //almacena posicion anterior
double actualMouseX, actualMouseY; //almacena posicion actual en caso de movimiento
double MovX=0, MovY=0; //Movimiento en X y Y
bool mouse_click = false; //estado del mouse en casi hay movimiento true sino false


//Variables para almacenar coordenadas y movimiento generado por las teclas
//coordonadas iniciales
double x = 0;
double y = 0;
//cantidad de movimiento realizada
double Cantidad_mov_H = 0;
double Cantidad_mov_V = 0;
//booleano para determinar el movimiento del objeto
bool Mover_obj = false;

//se agrega el movimiento que sera proporcionado por las tecles arriba, abajo , izq y der
void control_teclas(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if(action == GLFW_PRESS){
		
		if(key == GLFW_KEY_RIGHT){
			Cantidad_mov_H = 0.2;
			Mover_obj = true;
		}
		else if(key == GLFW_KEY_LEFT){
			Cantidad_mov_H = -0.2;
			Mover_obj = true;
		}
		else if(key == GLFW_KEY_UP){
			Cantidad_mov_V = 0.2;
			Mover_obj = true;
		}
		else if(key == GLFW_KEY_DOWN){
			Cantidad_mov_V = -0.2;
			Mover_obj = true;
		}
	}

	else if(action == GLFW_RELEASE){
		if(key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN){
			Cantidad_mov_H = 0;
			Mover_obj = false;
		}

//movimiento del mouse
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mouse_click = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
		mouse_click = false;
	}
}

//dibujar el cubo
void Dibujar_cubo() {

	GLfloat vertices[] = {
    // frente
    -1.0, -1.0,  1.0,
     1.0, -1.0,  1.0,
     1.0,  1.0,  1.0,
    -1.0,  1.0,  1.0,
    // atras
    -1.0, -1.0, -1.0,
     1.0, -1.0, -1.0,
     1.0,  1.0, -1.0,
    -1.0,  1.0, -1.0
  	};


  	GLfloat colors[] = {
    // frente
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 1.0, 1.0,
    // atras
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 1.0, 1.0
  	};

	static float alpha = 0;
	glRotatef(alpha, 0.5, 1, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glDrawArrays(GL_QUADS, 0, 8);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	alpha += 1;
}


void Mostrar( GLFWwindow* window ) {

	GLint windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluPerspective( 60, (double)windowWidth / (double)windowHeight, 0.2, 100 );

	if(Mover_obj){ //en caso de haber movimiento del objeto por medio las teclas
		x = x+Cantidad_mov_H;
		y = y+Cantidad_mov_V;
	}

	else if(mouse_click){	// en caso de haber movimiento por medio del mouse
		glfwGetCursorPos(window, &actualMouseX, &actualMouseY);
		double x = anteriorMouseX-actualMouseX;
		double y = anteriorMouseY-actualMouseY;
		double D_vector = sqrt(pow(x, 2)+pow(y,2));
		if(D_vector != 0){
			MovX -= (x/D_vector)*0.1;
			MovY -= (y/D_vector)*0.1;
		}
		cout<<MovX<<"\t"<<MovY<<endl;
		gluLookAt(0, 0, -5, MovX, MovY, 0, 0, 1, 0);
		glfwGetCursorPos(window, &anteriorMouseX, &anteriorMouseY);
	}else{
		glfwGetCursorPos(window, &anteriorMouseX, &anteriorMouseY);
		gluLookAt(0, 0, -5, MovX, MovY, 0, 0, 1, 0);
	}

	Dibujar_cubo();	//finalmente se grafica el cubo despues de haber o no movimiento
	glfwSwapBuffers(window);
	glfwPollEvents();
	}
}


int main(int argc, char** argv) {
	
	GLFWwindow* window = glfwCreateWindow(900, 600, "Grafica_mouse_teclado", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, control_teclas);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	Mostrar( window );
	glfwDestroyWindow(window);
	glfwTerminate();
}