#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define PI		 3.14159

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define ORANGE   1.0, 0.5, 0.1, 1.0
#define CYAN     0.0, 1.0, 1.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.3, 0.3, 0.3, 1.0


GLfloat pos[] = { 0., 0., 0. };
GLfloat posicao_carro[4][4];

GLfloat theta = 0.;
GLfloat vel = 1.;
//================================================================================
//------------------------------------------------------------ Sistema Coordenadas 
GLint		wScreen = 1920, hScreen = 1080;		//.. janela - pixeis
GLfloat		SIZE = 10.0;	//.. Mundo  SIZE=coordenadas x=y=z


//========================================================= Animacao objeto Mesa
float	  centrox = 0;
float	  rotacao = 0;
float	  rotacao_parabrisas = 0;
float	  anguloRotacaoParaBrisas = 1;
float     translacaovidro = 0;
GLint     sempreRodar = 0;
GLint     sempreRodarParaBrisas = 0;
GLfloat   altura = 0;
GLfloat   incALT = 0.1;
GLint     faceVisivel = 0;

//============================================================= Observador
GLfloat  rVisao = 8, aVisao = -0.5 * PI, incVisao = 1;
GLfloat  obsP[] = { rVisao * cos(aVisao), 2.0, rVisao * sin(aVisao) };
float	 anguloZ = 35;


//===========================================================Variaveis e constantes
GLint     msec = 50;


//==================================================================== VERTEX ARAY
//------------------------------------------- coordenadas + normais + cores
GLfloat tam = 0.5;
static GLfloat vertices[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
		-tam,  -tam,  tam,	// 0 
		-tam,   tam,  tam,	// 1 
		-tam,   tam, -tam,	// 2 
		-tam,  -tam, -tam,	// 3 
		//……………………………………………………  x=tam Direita
		tam,  -tam,  tam,	// 4 
		tam,   tam,  tam,	// 5 
		tam,   tam, -tam,	// 6 
		tam,  -tam, -tam,	// 7 
		//……………………………………………………… (y=tam Cima
		-tam,  tam,  tam,	// 8 
		-tam,  tam, -tam,	// 9 
		tam,  tam, -tam,	// 10 
		tam,  tam,  tam,	// 11 
		//........................frente
		tam,  tam,  tam,	// 12 
		tam,   -tam,  tam,	// 13 
		-tam,   -tam, tam,	// 14 
		-tam,  tam, tam,	// 15 
		//…………………………………………………… tras
		tam,  tam,  -tam,	// 16 
		tam,   -tam,  -tam,	// 17 
		-tam,   -tam, -tam,	// 18 
		-tam,  tam, -tam,	// 19 
		//……………………………………………………… (baixo
		-tam,  -tam,  tam,	// 20 
		-tam,  -tam, -tam,	// 21 
		tam,  -tam, -tam,	// 22 
		tam,  -tam,  tam,	// 23 
};
static GLfloat normais[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  //…………………………………………………………………………………………………… x=tam (Direita)
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  //…………………………………………………………………………………………………… y=tam (Cima)
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,

	   //…………………………………………………………………………………………………… y=tam (frente)
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   //…………………………………………………………………………………………………… y=tam (tras)
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
	   //…………………………………………………………………………………………………… y=tam (baixo)
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,

};



static GLuint cima[] = { 8, 11, 10, 9 };
static GLuint esquerda[] = { 0, 1, 2, 3 };
static GLuint direita[] = { 4, 7, 6, 5 };
static GLuint frente[] = { 12,13,14,15 };
static GLuint tras[] = { 16,17,18,19 };
static GLuint baixo[] = { 20,21,22,23 };



//================================================================================
//=========================================================================== INIT
void initialize(void)
{
	glClearColor(WHITE);		//………………………………………………………………………………Apagar
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	

	glEnable(GL_CULL_FACE);		//………………………………………………………………………………Faces visiveis
	glCullFace(GL_BACK);		//………………………………………………………………………………Mostrar so as da frente

	glVertexPointer(3, GL_FLOAT, 0, vertices);	//………………………………………Posicoes
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);		//………………………………………Normais
	glEnableClientState(GL_NORMAL_ARRAY);
}



void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo
	glColor4f(ORANGE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5 * SIZE, 0, 0);
	glEnd();
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5 * SIZE, 0);
	glEnd();
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.5 * SIZE);
	glEnd();

}
void desenhaCubo() {
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
}

//======================================
void drawScene() {

	if (sempreRodar) {
		rotacao = rotacao + 1;
		altura = altura + incALT;
		if (altura > 3) incALT = -incALT;
		if (altura < -1) incALT = -incALT;
	}
	if (sempreRodarParaBrisas) {
		rotacao_parabrisas += anguloRotacaoParaBrisas;
		if (rotacao_parabrisas >= 90) {
			anguloRotacaoParaBrisas = -anguloRotacaoParaBrisas;
		}
		if (rotacao_parabrisas <= 0) {
			anguloRotacaoParaBrisas = -anguloRotacaoParaBrisas;
		}
	}
	//desenha estrutura carro
	glTranslatef(pos[0]+centrox, pos[1]+altura, pos[2]);
	glRotatef(rotacao, 0.0, 1.0, 0.0);
	glScalef(2.5, 2.0, 2.5);
	glPushMatrix();
	glPushMatrix();
	glScalef(2, 1, 1);
	desenhaCubo();
	glPopMatrix();
	glPushMatrix();
	glColor4f(BLUE);
	glTranslated(-1 * tam, 2 * tam, 0);
	desenhaCubo();
	glGetFloatv(GL_MODELVIEW_MATRIX, &posicao_carro[0][0]);
	glPopMatrix();
	//desenha farois frente
	glPushMatrix();
	glColor4f(ORANGE);
	glTranslatef(2 * tam, 0.6 * tam, 0.6 * tam);
	glScaled(0.05, 0.2, 0.2);
	desenhaCubo();
	glPopMatrix();
	glPushMatrix();
	glColor4f(ORANGE);
	glTranslatef(2 * tam, 0.6 * tam, -0.6 * tam);
	glScaled(0.05, 0.2, 0.2);
	desenhaCubo();
	glPopMatrix();
	//desenha chapa matricula frente
	glPushMatrix();
	glColor4f(WHITE);
	glTranslatef(2 * tam, -0.3 * tam, 0);
	glScaled(0.05, 0.2, 0.6);
	desenhaCubo();
	glPopMatrix();
	//desenha chapa matricula tras
	glPushMatrix();
	glColor4f(WHITE);
	glTranslatef(-2 * tam, -0.3 * tam, 0);
	glScaled(0.05, 0.2, 0.6);
	desenhaCubo();
	glPopMatrix();
	//desenha farois tras
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(-2 * tam, 0.6 * tam, 0.6 * tam);
	glScaled(0.05, 0.4, 0.2);
	desenhaCubo();
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(-2 * tam, 0.6 * tam, -0.6 * tam);
	glScaled(0.05, 0.4, 0.2);
	desenhaCubo();
	glPopMatrix();
	//desenha janela tras
	glPushMatrix();
	glColor3f(0.000, 1.000, 1.000);
	glTranslatef(-2 * tam, 2 * tam, 0);
	glScalef(tam / 100, 0.80, 0.80);
	desenhaCubo();
	glPopMatrix();
	//desenha janela frente
	glPushMatrix();
	glColor3f(0.000, 1.000, 1.000);
	glTranslated(0, 2 * tam, 0);
	glScalef(tam / 100, 0.80, 0.80);
	desenhaCubo();
	glPopMatrix();
	//desenha janela lado condutor
	glPushMatrix();
	glColor3f(0.000, 1.000, 1.000);
	glTranslated(-tam, (2 * tam) - (tam * translacaovidro), -tam);
	glScalef(0.80, 0.80, tam / 100);
	desenhaCubo();
	glPopMatrix();
	//desenha porta lado condutor
	glPushMatrix();
	glColor4f(BLUE);
	glTranslated(-tam, tam - 0.6 * tam, -tam-tam/100);
	glScalef(1, 0.8, tam / 99);
	desenhaCubo();
	glPopMatrix();
	//desenha puxador porta lado condutor
	glPushMatrix();
	glColor4f(BLACK);
	glTranslated(-1.40 * tam, tam - 0.6 * tam, -tam);
	glScalef(0.25, 0.1, 0.1);
	desenhaCubo();
	glPopMatrix();
	//desenha janela lado passageiro
	glPushMatrix();
	glColor3f(0.000, 1.000, 1.000);
	glTranslated(-tam, (2 * tam) - (tam * translacaovidro), +tam);
	glScalef(0.80, 0.80, tam / 100);
	desenhaCubo();
	glPopMatrix();
	//desenha porta lado passageiro
	glPushMatrix();
	glColor4f(BLUE);
	glTranslated(-tam, tam - 0.6 * tam, tam+tam/100);
	glScalef(1, 0.8, tam / 99);
	desenhaCubo();
	glPopMatrix();
	//desenha puxador porta lado passageiro
	glPushMatrix();
	glColor4f(BLACK);
	glTranslated(-1.40 * tam, tam - 0.6 * tam, tam);
	glScalef(0.25, 0.1, 0.1);
	desenhaCubo();
	glPopMatrix();
	//desenha limpa-vidros
	glPushMatrix();
	glTranslatef(-tam, tam + 0.30 * tam, 0.8 * tam);
	glRotatef(-rotacao_parabrisas, 1, 0, 0);
	glTranslatef(tam, tam - 0.30 * tam, tam - 1.05 * tam);
	glScalef(0.05 * tam, 0.7, 0.05 * tam);
	glColor4f(BLACK);
	desenhaCubo();
	glPopMatrix();
	//Desenha Rodas
	glColor4f(BLACK);
	glTranslated(tam, -tam, 0);
	glScalef(0.5, 0.5, 1.2);
	desenhaCubo();
	glPopMatrix();
	glPopMatrix();
	glColor4f(BLACK);
	glTranslated(-tam, -tam, 0);
	glScalef(0.5, 0.5, 1.2);
	desenhaCubo();
	glPopMatrix();
	glPopMatrix();
}




//====================================================== 
//====================================================== 
void display(void) {

	//================================================================= APaga 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//================================================================= Viewport 2
	glViewport(0.25 * wScreen, 0, 0.75 * wScreen, 0.75 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, (float)wScreen / hScreen, 0.1, 9999);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	//======================================================
	//gluLookAt(3, 3, 5, 0, 0, 0, 0, 1, 0);

	//…………………………………………………………………………………………………………………………………………………………Objectos
	drawEixos();
	drawScene();

	glViewport(0, 0, 0.25 * wScreen, 0.25 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 30, 0, 0, 0, 0, 0, 0, -1);
	drawEixos();
	drawScene();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}


void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {

	case '+':
		sempreRodarParaBrisas = !sempreRodarParaBrisas;
		glutPostRedisplay();
		break;
	case '1':
		if (translacaovidro < 1.6)translacaovidro += 0.1;
		glutPostRedisplay();
		break;

	case '2':
		if (translacaovidro > 0.1)translacaovidro -= 0.1;
		glutPostRedisplay();
		break;

	case '3':
		altura = altura + incALT;
		if (altura > 3) incALT = -incALT;
		if (altura < -1) incALT = -incALT;
		glutPostRedisplay();
		break;

	case '4':
		altura = altura - incALT;
		if (altura > 3) incALT = -incALT;
		if (altura < -1) incALT = -incALT;
		glutPostRedisplay();
		break;


	case 'R': case 'r':
		sempreRodar = !sempreRodar;
		glutPostRedisplay();
		break;
	case 'A': case 'a':
		centrox = centrox + 0.5;
		glutPostRedisplay();
		break;
	case 'S': case 's':
		centrox = centrox - 0.5;
		glutPostRedisplay();
		break;
		//------------------------------ rotacao	
	case 'E': case 'e':
		rotacao = rotacao + 2.5;
		glutPostRedisplay();
		break;
	case 'D': case 'd':
		rotacao = rotacao - 2.5;
		glutPostRedisplay();
		break;

		//------------------------------ translacao



		//------------------------------ Cull Face
	case 'C': case 'c':
		//======================================
		//  <><><><><><> Alternar Face Visivel  ???
		//  <><><><><><> Ativa / Inativa  
		//======================================
		faceVisivel++;
		glEnable(GL_CULL_FACE);
		switch ((faceVisivel % 4)) {
		case 0:
			glCullFace(GL_BACK);
			break;

		case 1:
			glCullFace(GL_FRONT);
			break;

		case 2:
			glCullFace(GL_FRONT_AND_BACK);
			break;

		case 3:
			glDisable(GL_CULL_FACE);
			break;
		}
		glutPostRedisplay();
		break;


	case 27:
		exit(0);
		break;
	}

}



void teclasNotAscii(int key, int x, int y) {

	//=========================================================
	//  <><><><><><>  Movimento do observador  ???
	//=========================================================
	if (key == GLUT_KEY_UP) {
		pos[0] = pos[0] + vel * cos(rotacao * PI / 180.);
		pos[2] = pos[2] - vel * sin(rotacao * PI / 180.);
	}
	if (key == GLUT_KEY_DOWN) {
		pos[0] = pos[0] - vel * cos(rotacao * PI / 180.);
		pos[2] = pos[2] + vel * sin(rotacao * PI / 180.);
	}
	if (key == GLUT_KEY_LEFT)
		rotacao += 3.;
	if (key == GLUT_KEY_RIGHT)
		rotacao -= 3.;
	glutPostRedisplay();

}


//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Ganda Carro - Projeto CG 2022/2023");

	initialize();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}