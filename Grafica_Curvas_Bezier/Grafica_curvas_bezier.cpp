#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
double ratonX, ratonY; //declarar posicion de los puntos que seran fijados por el raton
bool liberar_raton = false; //movimiento del raton

static void llamada_error(int error, const char* descripcion){ //correccion de errores
	fputs(descripcion, stderr);
}
static void llamada_llave(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) //cerrar ventana
		glfwSetWindowShouldClose(window, GL_TRUE);
}
void llamada_boton_raton(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){ //captura de puntos por medio del raton
		liberar_raton = true;}
}
class Punto2D{ //clase punto
public:
	float x,y;
	Punto2D(float x, float y) : x(x),y(y){}
	~Punto2D(){}
	void draw(float size = 1){
		glPointSize(size);glBegin(GL_POINTS);glColor3f(1, 1, 1);glVertex3f(x, y, 1);glEnd();}

};

void dibujar_punto(vector<Punto2D> puntos, float t){ //dibujar puntos iniciales por medio de la entrada del raton
	if(puntos.size() == 1){
		puntos[0].draw();}
	else{
		vector<Punto2D> aux = puntos;
		aux.pop_back();
		for(int i=0; i<aux.size(); i++){
			float x = (1-t)*puntos[i].x + t*puntos[i+1].x;float y = (1-t)*puntos[i].y + t*puntos[i+1].y;aux[i] = Punto2D(x,y);}
		dibujar_punto(aux, t);}
}

void dibujar_curva(vector<Punto2D> puntos, int steps){ //dibujar la curva respecto a los puntos ingresados
	if(puntos.size() < 3) return;
	for(int i=0; i<steps; i++){
		float t = float(i)/(steps-1);
		dibujar_punto(puntos, t);}
}

void dibujar_puntos(vector<Punto2D>& puntos){ //dibujar los puntos entre la entrada de puntos simulando la curva
	for(int i=0; i<puntos.size(); i++){
		puntos[i].draw(5);}
}

int main(void) {
	GLFWwindow* window;
	glfwSetErrorCallback(llamada_error);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(900, 600, "Curvas de Bezier", NULL, NULL); //crear ventana
	if (!window){
		glfwTerminate();
		exit(EXIT_FAILURE);}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, llamada_llave);
	glfwSetMouseButtonCallback(window, llamada_boton_raton);
	vector<Punto2D> puntos;
	do{ glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glOrtho(0, 900, 600, 0, 1, -1);
		if(liberar_raton){
			glfwGetCursorPos(window, &ratonX, &ratonY);
			Punto2D p = Punto2D(ratonX, ratonY);
			puntos.push_back(p);
			liberar_raton = false;}
		dibujar_puntos(puntos);
		dibujar_curva(puntos, 100);
		glfwSwapBuffers(window);
		glfwPollEvents();}
	while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
    	glfwWindowShouldClose(window) == 0);
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
}