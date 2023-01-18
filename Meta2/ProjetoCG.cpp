#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>#include <windows.h>
#include "RgbImage.h"


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

void initMaterials(int material);
char Materiais[18][30] = {
	"Esmerald",  "Jade",  "obsidian",    "Pearl",        "Ruby",
	"Turquoise", "Brass", "Bronze",      "Chrome",       "Copper",
	"Gold",      "Silver","blackPlastic","cyankPlastic", "greenPlastic",
	"redPlastic", "whitePlastic","yellowPlastic" };


GLUquadricObj* esfera = gluNewQuadric();
GLfloat pos[] = { 0., 0., 0. };
GLfloat posicao_carro[4][4];

GLfloat theta = 0.;
GLfloat vel = 1.;

//material que vai ser mudado com a letra V
GLint material = 4;


GLint		wScreen = 1920, hScreen = 1080;	
GLfloat		SIZE = 10.0;



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
GLfloat  rVisao = 8, aVisao = -0.5 * PI, incVisao = 1, aVisaoCopia = -0.5;
GLfloat  obsP[] = { rVisao * sin(aVisao) + pos[0], 2.0, rVisao * cos(aVisao)+pos[2]};
float	 anguloZ = 35;


int malhaPol = 1;


GLint     msec = 50;

GLfloat tam = 0.5;




GLint   Dia = 0;
GLfloat intensidadeDia = 1.0;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia,intensidadeDia, 1.0 };


// Luz teto
GLint teto = 1;
GLfloat intensidadeTeto = 0;
GLint luzR = 1;
GLint luzG = 1;
GLint luzB = 1;
GLfloat posicaoLuz[] = { 0.0, 10, 0.0, 0.0 };
GLfloat localCorAmbiente[4] = { luzR* intensidadeTeto, luzG* intensidadeTeto, luzB* intensidadeTeto, 1.0 };
GLfloat localCorDifusa[4] = { luzR * intensidadeTeto, luzG * intensidadeTeto, luzB * intensidadeTeto, 1.0 };
GLfloat localCorEspecular[4] = { luzR * intensidadeTeto, luzG * intensidadeTeto, luzB * intensidadeTeto, 1.0 };

//foco1
int contador=0;
GLfloat R=1, G=0., B=0.;
GLfloat intensidadeFoco = 0;
GLfloat posicaoFoco[4] = { 0,10,0,1 };
GLfloat corFoco1[4] = { R * intensidadeFoco, G * intensidadeFoco, B * intensidadeFoco, 1.0 };
GLfloat direcaoFoco1[] = { 0, -1.0, 0.0,0.0};
GLfloat anguloFoco = 40.0;

//foco2
GLfloat posicaoFoco1[4] = { 10,10,40,1 };

//foco3
GLfloat posicaoFoco2[4] = { 10,10,80,1 };

//foco4
GLfloat posicaoFoco3[4] = { 10,10,120,1 };

//foco5
GLfloat posicaoFoco4[4] = { 10,10,160,1 };

//teto
GLfloat posicaolampada[4] = { 0.1,14,0.1,1 };
GLfloat intensidadeP = 2;
GLfloat cor_amb[4] = { 0.8 * intensidadeP,0.8 * intensidadeP,0 * intensidadeP,1.0 };
GLfloat cor[4] = { 0.8 * intensidadeP,0.8 * intensidadeP,0 * intensidadeP,1.0 };
GLfloat cor_spec[4] = { 0.8 * intensidadeP,0.8 * intensidadeP,0 * intensidadeP,1.0 };


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

RgbImage imag;

static GLuint cima[] = { 8, 11, 10, 9 };
static GLuint esquerda[] = { 0, 1, 2, 3 };
static GLuint direita[] = { 4, 7, 6, 5 };
static GLuint frente[] = { 12,13,14,15 };
static GLuint tras[] = { 16,17,18,19 };
static GLuint baixo[] = { 20,21,22,23 };

GLuint   texture[5];



static GLfloat vertices1[] = {
-0.50, 0.00, -0.96,
 0.50, 0.00, -0.96,
 0.50, 0.00, -0.00,
-0.50, 0.00, -0.00,
-0.50, 0.00, -0.96,
 0.50, 0.00, -0.96,
 0.50, 0.16, -0.96,
-0.50, 0.16, -0.96,
-0.50, 0.16, -1.28,
 0.50, 0.16, -1.28,
 0.50, 0.16, -0.96,
-0.50, 0.16, -0.96 };
static GLfloat normais1[] = {
0.0, 0.0, 1.0,
0.0, 0.0, 1.0,
0.0, 0.0, 1.0,
0.0, 0.0, 1.0,
0.0, 1.0, 0.0,
0.0, 1.0, 0.0,
0.0, 1.0, 0.0,
0.0, 1.0, 0.0,
0.0, 0.0, 1.0,
0.0, 0.0, 1.0,
0.0, 0.0, 1.0,
0.0, 0.0, 1.0 };
static GLfloat cores1[] = {
0.0, 1.0, 0.0,
0.0, 1.0, 0.0,
0.0, 1.0, 0.0,
0.0, 1.0, 0.0,
1.0, 0.0, 0.0,
1.0, 0.0, 0.0,
1.0, 0.0, 0.0,
1.0, 0.0, 0.0,
1.0, 0.0, 1.0,
1.0, 0.0, 1.0,
1.0, 0.0, 1.0,
1.0, 0.0, 1.0 };
static GLfloat texturas[] = {
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1 };



int alteraPostes = 0;

void desenhaPostes(float x, int control) {
	int a = 15;
	int b = 16;
	int c = 7;
	if (control == 1) {
		a = -a;
		b = -b;
		c = -c;
	}
	glPushMatrix();
	initMaterials(2);
	glTranslatef(c, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(a, -3, x - 1);
	glVertex3f(a, -3, x);
	glVertex3f(a, 10, x);
	glVertex3f(a, 10, x - 1);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(a, -3, x - 1);
	glVertex3f(a, -3, x);
	glVertex3f(a, 10, x);
	glVertex3f(a, 10, x - 1);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(b, -3, x);
	glVertex3f(a, -3, x);
	glVertex3f(a, 10, x);
	glVertex3f(b, 10, x);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(b, -3, x - 1);
	glVertex3f(a, -3, x - 1);
	glVertex3f(a, 10, x - 1);
	glVertex3f(b, 10, x - 1);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(b, 10, x - 1);
	glVertex3f(c, 10, x - 1);
	glVertex3f(c, 11, x - 1);
	glVertex3f(b, 11, x - 1);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(b, 10, x);
	glVertex3f(c, 10, x);
	glVertex3f(c, 11, x);
	glVertex3f(b, 11, x);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(b, 10, x);
	glVertex3f(c, 10, x);
	glVertex3f(c, 10, x - 1);
	glVertex3f(b, 10, x - 1);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(b, 11, x);
	glVertex3f(c, 11, x);
	glVertex3f(c, 11, x-1);
	glVertex3f(b, 11, x - 1);
	glEnd();
	glPopMatrix();

}


void desenhaGaragem() {
		glNormal3f(1, 0, 0);
		initMaterials(material);
		glPushMatrix();
		glTranslatef(3, -1.2, 0);
		glBegin(GL_QUADS);
		// parede 1
		glVertex3f(-15, -1.5f, -15);
		glVertex3f(-15, -1.5f, 15);
		glVertex3f(-15, 15, 15);
		glVertex3f(-15, 15, -15);
		glEnd();
		// parede 2
		glNormal3f(-1, 0, 0);
		glBegin(GL_QUADS);
		glVertex3f(15, -1.5f, 15);
		glVertex3f(15, -1.5f, -15);
		glVertex3f(15, 15, -15);
		glVertex3f(15, 15, 15);
		glEnd();
		// parede 3
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glVertex3f(15, -1.5f, -15);
		glVertex3f(-15, -1.5f, -15);
		glVertex3f(-15, 15, -15);
		glVertex3f(15, 15, -15);
		glEnd();
		//teto
		glNormal3f(0, 1, 0);
		glBegin(GL_QUADS);
		glVertex3f(15, 15, 15);
		glVertex3f(-15, 15, 15);
		glVertex3f(-15, 15, -15);
		glVertex3f(15, 15, -15);
		glEnd();
		glPopMatrix();
}

void initLights(void) {
	// Ambiente

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);

	//direcional
	GLfloat Foco_ak = 1.0;
	GLfloat Foco_al = 0.05f;
	GLfloat Foco_aq = 0.0f;
	GLfloat Foco_Expon = 2.0;


	//glPushMatrix();
	//glTranslatef(20, 0, 0);
	//glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEspecular);
	GLfloat dir[] = { 0,-1,-1,0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);



	
	// luz pontual teto 1
	/*GLfloat intensidadeP = 2;
	GLfloat cor[] = { 0.8*intensidadeP,0.8 * intensidadeP,0.0 * intensidadeP,1.0 };
	float atenConst = 5;
	//GLfloat posicaolampada[] = { 0,15,0,1 };
	glLightfv(GL_LIGHT2, GL_POSITION, posicaolampada);
	//glLightfv(GL_LIGHT2, GL_AMBIENT, cor);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, cor);
	glLightfv(GL_LIGHT2, GL_SPECULAR, cor);
	//glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, atenConst);
	//glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
	//glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.1);
	*/

	// luz teto
	
	glLightfv(GL_LIGHT1, GL_POSITION, posicaolampada);
	glLightfv(GL_LIGHT1, GL_AMBIENT, cor_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, cor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, cor_spec);


	// luz foco 1
	glLightfv(GL_LIGHT3, GL_POSITION, posicaoFoco1);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, corFoco1);
	glLightfv(GL_LIGHT3, GL_AMBIENT, corFoco1);
	glLightfv(GL_LIGHT3, GL_SPECULAR, corFoco1);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, Foco_Expon);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, anguloFoco);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direcaoFoco1);

	// luz foco 2
	glLightfv(GL_LIGHT4, GL_POSITION, posicaoFoco2);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, corFoco1);
	glLightfv(GL_LIGHT4, GL_AMBIENT, corFoco1);
	glLightfv(GL_LIGHT4, GL_SPECULAR, corFoco1);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, Foco_Expon);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, anguloFoco);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direcaoFoco1);

	// luz foco 3
	glLightfv(GL_LIGHT5, GL_POSITION, posicaoFoco3);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, corFoco1);
	glLightfv(GL_LIGHT5, GL_AMBIENT, corFoco1);
	glLightfv(GL_LIGHT5, GL_SPECULAR, corFoco1);
	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, Foco_Expon);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, anguloFoco);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, direcaoFoco1);

	// luz foco 4
	glLightfv(GL_LIGHT6, GL_POSITION, posicaoFoco4);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, corFoco1);
	glLightfv(GL_LIGHT6, GL_AMBIENT, corFoco1);
	glLightfv(GL_LIGHT6, GL_SPECULAR, corFoco1);
	glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, Foco_Expon);
	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, anguloFoco);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, direcaoFoco1);

	//glPopMatrix();

}




void initTexturas()
{
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("road.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());


	//----------------------------------------- Esfera - skybox envolvente
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("sky.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}





//================================================================================
//=========================================================================== INIT
void initialize(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	
	glEnable(GL_NORMALIZE);
	initTexturas();
	
	
	
	
	//glEnable(GL_CULL_FACE);		//………………………………………………………………………………Faces visiveis
	//glCullFace(GL_BACK);		//………………………………………………………………………………Mostrar so as da frente

	glVertexPointer(3, GL_FLOAT, 0, vertices);	//………………………………………Posicoes
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);		//………………………………………Normais
	glEnableClientState(GL_NORMAL_ARRAY);


	//glNormalPointer(GL_FLOAT, 0, normais1);
	//glEnableClientState(GL_NORMAL_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas);   // coordenadas textura
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//……………………………………………………………………………………………………………………………Luzes
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);

	//initMaterials(17);
}




void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5 * SIZE, 0, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5 * SIZE, 0);
	glEnd();
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


void drawEsfera()
{
	//------------------------- Esfera
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	initMaterials(2);
	//glTranslatef(2, 4, 2);
	glRotatef(-90, 1, 0, 0);
	gluQuadricDrawStyle(esfera, GLU_FILL);
	gluQuadricNormals(esfera, GLU_SMOOTH);
	gluQuadricTexture(esfera, GL_TRUE);
	gluSphere(esfera, 240.0, 100, 100);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

/*void drawChao() {
	float L = 1;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	for (int i = -230; i <= 240; i += 30) {
		glPushMatrix();
		glTranslatef(0, -3, i);
		glNormal3f(0, 1, 0);
		initMaterials(2);
		glBegin(GL_QUADS);
		for(int p = -40; p<40;p++){
			for(int f = -40; f< 40;f++){
			glTexCoord2f(0.0f, 1.0f);    glVertex3i((f - 1), 0.1,  (p-1)); //A 
			glTexCoord2f(1.0f, 0.0f); 	 glVertex3i((f-1), 0.1, p);  //B
			glTexCoord2f(1.0f, 1.0f);    glVertex3i(f, 0.1, p); //C
			glTexCoord2f(0.0f, 0.0f);  	 glVertex3i(f, 0.1, (p -1)); //D
			}
			}
		glEnd();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
}
*/


void drawChao() {
	float L = 1;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	int				i, j;
	int dim = 150;
	float			med_dim = (float)dim / 2;
	for (int p = -80; p <= 240; p +=80) {
		glPushMatrix();
		glTranslatef(-40, -3, p);
		glScalef(40, 1, 40);
		glNormal3f(0, 1, 0);
		initMaterials(2);
		glBegin(GL_QUADS);
		for (i = 0; i < dim; i++)
			for (j = 0; j < dim; j++) {
				glTexCoord2f((float)j / dim, (float)i / dim);
				glVertex3d((float)j / med_dim, 0, (float)i / med_dim);
				glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
				glVertex3d((float)(j + 1) / med_dim, 0, (float)i / med_dim);
				glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
				glVertex3d((float)(j + 1) / med_dim, 0,(float)(i + 1) / med_dim);
				glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
				glVertex3d((float)j / med_dim, 0, (float)(i + 1) / med_dim);
			}
		glEnd();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
}






void drawChaoNoMalha(void) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	for (int i = -80; i <= 240; i += 80) {
		glPushMatrix();
		glTranslatef(0, -3, i);
		glNormal3f(0, 1, 0);
		initMaterials(2);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);    glVertex3i(-40, 0.1, 40); //A 
		glTexCoord2f(0.0f, 0.0f); 	 glVertex3i(-40, 0.1, -40);  //B
		glTexCoord2f(1.0f, 0.0f);    glVertex3i(40, 0.1, -40); //C
		glTexCoord2f(1.0f, 1.0f);  	 glVertex3i(40, 0.1, 40); //D
		glEnd();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
}

void desenhaJanelas(int x) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	initMaterials(5);
	if(x==1){
		//desenha janela lado condutor
		glPushMatrix();
		initMaterials(5);
		glTranslated(-tam, (2 * tam) - (tam * translacaovidro), -tam);
		glScalef(0.80, 0.80, tam / 100);
		desenhaCubo();
		glPopMatrix();
	}
	if (x == 2) {
		//desenha janela lado passageiro
		glPushMatrix();
		initMaterials(5);
		glTranslated(-tam, (2 * tam) - (tam * translacaovidro), +tam);
		glScalef(0.80, 0.80, tam / 100);
		desenhaCubo();
		glPopMatrix();
	}
	glDisable(GL_BLEND);
}

void desenhaCabine(void) {

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	//lado passageiro
	glPushMatrix();
	glTranslatef(0.45, 0, 0);
	glScalef(0.1, 1, 1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.45, 0, 0);
	glScalef(0.1, 1, 1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.45, 0);
	glScalef(1, 0.1, 1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glPopMatrix();

	//lado condutor
	glPushMatrix();
	glTranslatef(0.45, 0, 0);
	glScalef(0.1, 1, 1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.45, 0, 0);
	glScalef(0.1, 1, 1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.45, 0);
	glScalef(1, 0.1, 1);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();


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
	glTranslatef(pos[0]+centrox, pos[1]+altura-1.2, pos[2]);
	glRotatef(rotacao, 0.0, 1.0, 0.0);
	glScalef(2.5, 2.0, 2.5);
	glPushMatrix();
	initMaterials(7);
	glPushMatrix();
	glScalef(2, 1, 1);
	desenhaCubo();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-1 * tam, 2 * tam, 0);
	//cabine
	desenhaCabine();
	//desenhaCubo();
	//glGetFloatv(GL_MODELVIEW_MATRIX, &posicao_carro[0][0]);
	glPopMatrix();
	//desenha farois frente
	glPushMatrix();
	initMaterials(16);
	glTranslatef(2 * tam, 0.6 * tam, 0.6 * tam);
	glScaled(0.05, 0.2, 0.2);
	desenhaCubo();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2 * tam, 0.6 * tam, -0.6 * tam);
	glScaled(0.05, 0.2, 0.2);
	desenhaCubo();
	glPopMatrix();
	//desenha chapa matricula frente
	glPushMatrix();
	initMaterials(16);
	glTranslatef(2 * tam, -0.3 * tam, 0);
	glScaled(0.05, 0.2, 0.6);
	desenhaCubo();
	glPopMatrix();
	//desenha chapa matricula tras
	glPushMatrix();
	initMaterials(16);
	glTranslatef(-2 * tam, -0.3 * tam, 0);
	glScaled(0.05, 0.2, 0.6);
	desenhaCubo();
	glPopMatrix();
	//desenha farois tras
	glPushMatrix();
	initMaterials(15);
	glTranslatef(-2 * tam, 0.6 * tam, 0.6 * tam);
	glScaled(0.05, 0.4, 0.2);
	desenhaCubo();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2 * tam, 0.6 * tam, -0.6 * tam);
	glScaled(0.05, 0.4, 0.2);
	desenhaCubo();
	glPopMatrix();
	//desenha janela tras
	glPushMatrix();
	initMaterials(5);
	glTranslatef(-2 * tam, 2 * tam, 0);
	glScalef(tam / 100, 0.80, 0.80);
	desenhaCubo();
	glPopMatrix();
	//desenha janela frente
	glPushMatrix();
	initMaterials(5);
	glTranslated(0, 2 * tam, 0);
	glScalef(tam / 100, 0.80, 0.80);
	desenhaCubo();
	glPopMatrix();
	//desenha janela lado condutor
	desenhaJanelas(1);
	//desenha porta lado condutor
	glPushMatrix();
	initMaterials(7);
	glTranslated(-tam, tam - 0.6 * tam, -tam-tam/100);
	glScalef(1, 0.8, tam / 99);
	desenhaCubo();
	glPopMatrix();
	//desenha puxador porta lado condutor
	glPushMatrix();
	initMaterials(8);
	glTranslated(-1.40 * tam, tam - 0.6 * tam, -tam);
	glScalef(0.25, 0.1, 0.1);
	desenhaCubo();
	glPopMatrix();
	//desenha janela lado passageiro
	desenhaJanelas(2);
	//desenha porta lado passageiro
	glPushMatrix();
	initMaterials(7);
	glTranslated(-tam, tam - 0.6 * tam, tam+tam/100);
	glScalef(1, 0.8, tam / 99);
	desenhaCubo();
	glPopMatrix();
	//desenha puxador porta lado passageiro
	glPushMatrix();
	initMaterials(8);
	glTranslated(-1.40 * tam, tam - 0.6 * tam, tam);
	glScalef(0.25, 0.1, 0.1);
	desenhaCubo();
	glPopMatrix();
	//desenha limpa-vidros
	glPushMatrix();
	initMaterials(2);
	glTranslatef(-tam, tam + 0.30 * tam, 0.8 * tam);
	glRotatef(-rotacao_parabrisas, 1, 0, 0);
	glTranslatef(tam, tam - 0.30 * tam, tam - 1.05 * tam);
	glScalef(0.05 * tam, 0.7, 0.05 * tam);
	desenhaCubo();
	glPopMatrix();
	//Desenha Rodas
	glTranslated(tam, -tam, 0);
	glScalef(0.5, 0.5, 1.2);
	desenhaCubo();
	glPopMatrix();
	initMaterials(2);
	glPopMatrix();
	glTranslated(-tam, -tam, 0);
	glScalef(0.5, 0.5, 1.2);
	desenhaCubo();
	glPopMatrix();
	glPopMatrix();
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

	

	gluLookAt(obsP[0], obsP[1], obsP[2], pos[0], pos[1], pos[2], 0, 1, 0);
	
	
	initLights();
	//glDisable(GL_LIGHT1);

	/*
	glColor3f(1., 1., 1.);
	glPushMatrix();
	glTranslatef(0.1, 14, 0.1);
	glScaled(3., 3., 3.);
	glutSolidSphere(1., 8, 8);
	glPopMatrix();
	*/

	if (malhaPol == 1)drawChao();
	else drawChaoNoMalha();
	desenhaGaragem();
	if (alteraPostes == 1) {
		desenhaPostes(40,1);
		desenhaPostes(80,1);
		desenhaPostes(120,1);
		desenhaPostes(160,1);
	}
	else {
		desenhaPostes(40, 0);
		desenhaPostes(80, 0);
		desenhaPostes(120, 0);
		desenhaPostes(160, 0);
	}

	drawEixos();
	drawEsfera();
	drawScene();



	glViewport(0, 0, 0.25 * wScreen, 0.25 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 30, 0, 0, 0, 0, 0, 0, -1);
	initLights();
	if (malhaPol == 1)drawChao();
	else drawChaoNoMalha();
	if (alteraPostes == 1) {
		desenhaPostes(40, 1);
		desenhaPostes(80, 1);
		desenhaPostes(120, 1);
		desenhaPostes(160, 1);
	}
	else {
		desenhaPostes(40, 0);
		desenhaPostes(80, 0);
		desenhaPostes(120, 0);
		desenhaPostes(160, 0);
	}
	drawEixos();
	drawScene();


	glutSwapBuffers();
}

void updateLuz() {
	corFoco1[0] = R * intensidadeFoco;
	corFoco1[1] = G * intensidadeFoco;
	corFoco1[2] = B * intensidadeFoco;
	glLightfv(GL_LIGHT6, GL_DIFFUSE, corFoco1);
	glLightfv(GL_LIGHT6, GL_AMBIENT, corFoco1);
	glLightfv(GL_LIGHT6, GL_SPECULAR, corFoco1);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, corFoco1);
	glLightfv(GL_LIGHT5, GL_AMBIENT, corFoco1);
	glLightfv(GL_LIGHT5, GL_SPECULAR, corFoco1);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, corFoco1);
	glLightfv(GL_LIGHT4, GL_AMBIENT, corFoco1);
	glLightfv(GL_LIGHT4, GL_SPECULAR, corFoco1);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, corFoco1);
	glLightfv(GL_LIGHT3, GL_AMBIENT, corFoco1);
	glLightfv(GL_LIGHT3, GL_SPECULAR, corFoco1);
}


void updateFocos() {
	posicaoFoco1[0] = -posicaoFoco1[0];
	posicaoFoco2[0] = -posicaoFoco2[0];
	posicaoFoco3[0] = -posicaoFoco3[0];
	posicaoFoco4[0] = -posicaoFoco4[0];
	glLightfv(GL_LIGHT3, GL_POSITION, posicaoFoco1);
	glLightfv(GL_LIGHT4, GL_POSITION, posicaoFoco2);
	glLightfv(GL_LIGHT5, GL_POSITION, posicaoFoco3);
	glLightfv(GL_LIGHT6, GL_POSITION, posicaoFoco4);

}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {

	switch (key) {


	case 'X': case 'x':
		if (alteraPostes == 0)alteraPostes = 1;
		else alteraPostes = 0;
		updateFocos();
		glutPostRedisplay();
		break;

	case 'i':
	case 'I':
		intensidadeFoco = intensidadeFoco + 0.2;
		if (intensidadeFoco > 10) intensidadeFoco = 0;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'G': case 'g':
		contador++;
		if (contador > 2)contador = 0;
		if (contador == 0) {
			R = 1;
			G = 0;
			B = 0;
		}
		if (contador == 1) {
			R = 0;
			G = 1;
			B = 0;
		}
		if (contador == 2) {
			R = 0;
			G = 0;
			B = 1;
		}
		updateLuz();
		glutPostRedisplay();
		break;

	case 'V': case 'v':
		material++;
		if (material > 7) material = 4;
		glutPostRedisplay();
		break;

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

	case 'W': case 'w':
		obsP[1] += 1;
		glutPostRedisplay();
		break;

	case 'S': case 's':
		obsP[1] -= 1;
		glutPostRedisplay();
		break;

	case 'A': case 'a':
		aVisao -= 0.1;
		obsP[0] = rVisao * sin(aVisao + (rotacao * PI / 180.)) + pos[0];
		obsP[2] = rVisao * cos(aVisao + (rotacao * PI / 180.)) + pos[2];
		glutPostRedisplay();
		break;
	case 'D': case 'd':
		aVisao += 0.1;
		obsP[0] = rVisao * sin(aVisao + (rotacao * PI / 180.)) + pos[0];
		obsP[2] = rVisao * cos(aVisao + (rotacao * PI / 180.)) + pos[2];
		glutPostRedisplay();
		break;
	case 'Z': case 'z':
		aVisao = aVisaoCopia;
		obsP[0] = rVisao * sin(aVisao - (rotacao * PI / 180.));
		obsP[2] = rVisao * cos(aVisao - (rotacao * PI / 180.));
		glutPostRedisplay();
		break;

	/*case 'A': case 'a':
		centrox = centrox + 0.5;
		glutPostRedisplay();
		break;
	case 'S': case 's':
		centrox = centrox - 0.5;
		glutPostRedisplay();
		break;*/
		//------------------------------ rotacao	
	case 'E': case 'e':
		rotacao = rotacao + 2.5;
		obsP[0] = rVisao * sin(aVisao + (rotacao * PI / 180.)) + pos[0];
		obsP[2] = rVisao * cos(aVisao + (rotacao * PI / 180.)) + pos[2];
		glutPostRedisplay();
		break;
	case 'F': case 'f':
		rotacao = rotacao - 2.5;
		obsP[0] = rVisao * sin(aVisao + (rotacao * PI / 180.)) + pos[0];
		obsP[2] = rVisao * cos(aVisao + (rotacao * PI / 180.)) + pos[2];
		glutPostRedisplay();
		break;

	case 'M': case 'm':
		if (malhaPol == 1) malhaPol = 0;
		else malhaPol = 1;
		glutPostRedisplay();
		break;


	case 'C': case 'c':
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
	//GLfloat  obsP[] = { rVisao * sin(aVisao) + cos(rotacao * PI / 180.), 2.0, rVisao * cos(aVisao) + sin(rotacao * PI / 180.)};
	if (key == GLUT_KEY_UP) {
		pos[0] = pos[0] + vel * cos(rotacao * PI / 180.);
		pos[2] = pos[2] - vel * sin(rotacao * PI / 180.);
		obsP[0] = rVisao * sin(aVisao + (rotacao * PI / 180.)) + pos[0];
		obsP[2] = rVisao * cos(aVisao + (rotacao * PI / 180.)) + pos[2];
	}
	if (key == GLUT_KEY_DOWN) {
		pos[0] = pos[0] - vel * cos(rotacao * PI / 180.);
		pos[2] = pos[2] + vel * sin(rotacao * PI / 180.);
		obsP[0] = rVisao * sin(aVisao + (rotacao * PI / 180.)) + pos[0];
		obsP[2] = rVisao * cos(aVisao + (rotacao * PI / 180.)) + pos[2];
	}
	if (key == GLUT_KEY_LEFT){
		rotacao += 3.;
		obsP[0] = rVisao * sin(aVisao + (rotacao * PI / 180.)) + pos[0];
		obsP[2] = rVisao * cos(aVisao + (rotacao * PI / 180.)) + pos[2];
	}
	if (key == GLUT_KEY_RIGHT){
		rotacao -= 3.;
		obsP[0] = rVisao * sin(aVisao + (rotacao * PI / 180.)) + pos[0];
		obsP[2] = rVisao * cos(aVisao + (rotacao * PI / 180.)) + pos[2];
	}
	glutPostRedisplay();

}


//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Ganda Carro - Projeto CG 2022/2023 (M-malha; G-cores_luz; V-muda_materiais; X-pos_luzes;+-rotacao_parabrisas;1/2-sobe/desce_vidros;I-intensidade)");
	initialize();
	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}