#include<bits/stdc++.h>
#include<GL/glut.h> //OpenGL

using namespace std;

int ww = 900, wh = 600;
int xi=450, yi=200, xf=500, yf=400;

void setPixel(int x, int y);
void linea();
void circunferencia();
void CirclePoints(int x, int y);
void poligono();
void setup();

int main(int argc, char **argv)
{

	///Primer paso inicializar OpenGL
    glutInit(&argc, argv);
    ///Mostrar en modo simple y colores RGB.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    ///Brindar tamaño de ventana.
    glutInitWindowSize(ww, wh);
    ///Brindar coordenadas para la posicion de la ventana.
    glutInitWindowPosition(400, 300);
    ///Crear ventana con un nombre determinado.
    glutCreateWindow("Grafica");
    ///Setear color del primer plano.
    glClearColor(1,1,1, 1.0);
    ///Limpiar la pantalla al color de fondo.
    glColor3f(1,1,1);
    ///Limpiar los objetos y renderizarlos.
    glClear(GL_COLOR_BUFFER_BIT);
    ///Registrar La visualizacion.
    glutDisplayFunc(linea);
    glutDisplayFunc(circunferencia);
    glutDisplayFunc(poligono);

    glFlush();

    setup();

    glutMainLoop(); ///terminar el bucle

    return 0;

}

void linea()
{
    //un solo sentido de dibujo de líneas
    if (xf<xi && yf<yi){ 
        swap(xi,xf);
        swap(yi,yf);
    }
    else{
        if(xf>xi && yf<yi){
            swap(xi,xf);
            swap(yi,yf);
        }
    }
 
    int yi_, xi_, xf_;
    xi_ = xi;
    yi_ = yi;
    xf_ = xf;

    //Setear al punto de origen 0,0
    xf = xf-xi;
    yf = yf-yi;
    xi=0;	//setear a 0
    yi=0;	//setear a 0

    //Buscar la simetria en la linea
    if (xf<xi){
        if (yf-abs(xf) > 0){       
            xf=-xf;
            swap(xf,yf);
        }
        else{
            xf=-xf;
        }
    }
    else{
        if (yf-xf > 0){
            swap(xf,yf);
        }
    }

    int dx, dy, incremento_E, incremento_NE, d, x, y;
    dx = xf - xi;
    dy = yf - yi;
    d = 2 * dy - dx; ///Setear el valor inicial de D.
    incremento_E = 2 * dy;
    incremento_NE = 2 * (dy - dx);
    x = xi;
    y = yi;
    setPixel(xi_, yi_);

    while (x < xf){
        if (d <= 0){ ///Setear el valor de E
            d = d + incremento_E;
            x = x + 1;
        }else{ ///Setear ek valor de NE
            d = d + incremento_NE;
            x = x + 1;
            y = y + 1;
        }
        if (xf_<xi_){ ///Reconstruccion
            if (yf-abs(xf) > 0){          
                setPixel(xi_-y,x+yi_);
            }
            else{
                setPixel(xi_-x,y+yi_);
            }
        }
        else{
            if (yf-abs(xf) > 0){                
                setPixel(y+xi_, x+yi_);
            }
            else{
                setPixel(x+xi_, y+yi_);
            }
        }
    }
    
}

void circunferencia()
{
    glClearColor(1,1,1, 1.0); ///Setear color del primer plano.
    glColor3f(1,1,1); ///Limpiar la pantalla al color de fondo.
    glClear(GL_COLOR_BUFFER_BIT); ///Limpiar los objetos y renderizarlos.


    ///Seteamos los valores iniciales
    int r=150;
    int x, y, d;
    x = 0;
    y = r;
    d = 1 - r;
    CirclePoints(x+300, y+300);
    while (y > x){
        if (d < 0){
            d = d + 2 * x + 3;
            x++;
        }else{
            d = d + 2 * (x - y) + 5;
            x++;
            y--;
        }
        CirclePoints(x+300, y+300);
    }
    
    glFlush();
}

void CirclePoints(int x, int y) ///Setear coordenadas de la circunferencia
{
    setPixel( x, y);
    setPixel( x, -y);
    setPixel(-x, y);
    setPixel(-x, -y);
    setPixel( y, x);
    setPixel( y, -x);
    setPixel(-y, x);
    setPixel(-y, -x);
}


void poligono()
{
	///Setear coordenada para los puntos que formaran el poligono
    int xi=120, yi=200, xf=300, yf=280, x3=400, y3=200;

    glClearColor(1,1,1, 1.0); ///Setear color del primer plano.
    glColor3f(1,1,1); ///Limpiar la pantalla al color de fondo.
    glClear(GL_COLOR_BUFFER_BIT); ///Limpiar los objetos y renderizarlos.

    ///Poligono de tres lados (formados por 3 lineas).
    linea(xi,yi,xf,yf);
    linea(xf,yf,x3,y3);
    linea(x3,y3,xi,yi);
    
    glFlush();
}


void setPixel(int x, int y)
{
    glColor3f(0.0, 0.0, 1.0); ///Setear pixel a negro.
    glBegin(GL_POINTS);
    glVertex2i(x, y); ///Setear las coordenadas de los pixeles.
    glEnd();
}

void setup()
{
    glViewport(0, 0, ww, wh); ///Setear para que se visualize en toda la pantalla de OpenGL.
    glMatrixMode(GL_PROJECTION); ///Setear modo matriz para la proyeccion.
    glLoadIdentity(); ///Limpiar la proyeccion actual para la identidad.
    gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh); /// Especificar el tipo de proyeccion.
    glMatrixMode(GL_MODELVIEW); ///Setear modo matriz a modo de vista.