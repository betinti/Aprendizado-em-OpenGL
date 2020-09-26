#include <windows.h>		// for MS Windows
#include <GL\freeglut.h>	// GLUT, include glu.h and gl.h
#include <iostream>         // para o "cout"
#include <fstream>		    // File library
using namespace std;

GLfloat angleV, fAspect; // varivaies referentes a angulção
//int DisplayFile[6] = { 1,2,3,4,5,6 };  // seis elementos no display

// variaveis referentes a possicao de cada objeto
GLfloat dx1 = 0; GLfloat dx2 = 0; GLfloat dx3 = 0;
GLfloat dy1 = 0; GLfloat dy2 = 0; GLfloat dy3 = 0;
GLfloat dz1 = 0; GLfloat dz2 = 0; GLfloat dz3 = 0;
GLfloat dx4 = 0; GLfloat dx5 = 0; GLfloat dx6 = 0;
GLfloat dy4 = 0; GLfloat dy5 = 0; GLfloat dy6 = 0;
GLfloat dz4 = 0; GLfloat dz5 = 0; GLfloat dz6 = 0;

//GLfloat dx = 0; GLfloat dy = 0;

// varivaies referetes a posicao da camera
GLfloat cx = 0; GLfloat cy = 0; GLfloat cz = 0;

// variaveis referentes ao rgb
GLfloat rk = 0; GLfloat gk = 0; GLfloat bk = 0;
GLfloat r1 = 0; GLfloat g1 = 0; GLfloat b1 = 0;
GLfloat r2 = 0; GLfloat g2 = 0; GLfloat b2 = 0;
GLfloat r3 = 0; GLfloat g3 = 0; GLfloat b3 = 0;
GLfloat r4 = 0; GLfloat g4 = 0; GLfloat b4 = 0;
GLfloat r5 = 0; GLfloat g5 = 0; GLfloat b5 = 0;
GLfloat r6 = 0; GLfloat g6 = 0; GLfloat b6 = 0;

// Variaveis referente ao tamanho de cada objeto
GLfloat t1 = 0; GLfloat t2 = 0; GLfloat t3 = 0;
GLfloat t4 = 0; GLfloat t5 = 0; GLfloat t6 = 0;

// Variaveis referentes a rotacao de cada objeto selecionado
GLfloat angle = 0.0f;
GLfloat angle1 = 0.0f; GLfloat angle2 = 0.0f; GLfloat angle3 = 0.0f;
GLfloat angle4 = 0.0f; GLfloat angle5 = 0.0f; GLfloat angle6 = 0.0f;


// Variaveis referentes a Alteração de sua visibilidade (ligada e desligada) de cada objeto em cena
bool show01 = true;
bool show02 = true;
bool show03 = true;
bool show04 = true;
bool show05 = true;
bool show06 = true;

// Variaveis referentes ao modo de visão (ortogonal e perspectiva)
bool vision = true;

// Variaveis referentes as luzes
bool light01 = true;
bool light02 = true;

int numObjects;				// numero de objetos
int ObjectList[6];         // Lista de Objetos, 10 é o número máximo
int x[6], y[6], z[6];		// coordenadas dos objetos
float r[6], g[6], b[6];  // cores dos objetos

int selected = 0;
char title[] = "OpenGL-PUCPR: Bernardo Guimarães Tinti";
GLfloat nRange = 200;

// Função printanto o MENU no prompt
void menu() {
	cout << "|------ MENU ------|------ MENU ------|------ MENU ------|------ MENU ------|" << endl;
	cout << "SELECAO DOS OBJETOS:" << endl;
	cout << "	F1 F2 F3 F4 F5 F6 Seleciona cada um dos objetos;" << endl;
	cout << "	END seleciona nenhum objeto;" << endl;
	cout << "INTERACAO COM CADA OBJETO:" << endl;
	cout << "	1 2 3 4 5 6 apaga e mostra cada objeto;" << endl;
	cout << "	F7 F8 diminui e aumenta o tamanho do objeto selecionado;" << endl;
	cout << "	Setas para mover o objeto selecionado;" << endl;
	cout << "	PageUp e PageDown para rotacionar o objeto selecionado ou a cena inteira caso nada esteja selecionado;" << endl;
	cout << "	U, I e O aumentam a escada do R, G e B, respectivamente, de cada objeto selecionado;" << endl;
	cout << "	J, K e L diminuem a escada do R, G e B, respectivamente, de cada objeto selecionado;" << endl;
	cout << "	A, S, D, W , Q e E altera a posicao da camera, sendo:" << endl;
	cout << "		A e D dedicados ao eixo X;" << endl;
	cout << "		W e S dedicados ao eixo Y;" << endl;
	cout << "		Q e E dedicados ao eixo Z;" << endl;
	cout << "INTERACAO COM A CENA:" << endl;
	cout << "	Botao esquerdo e direito do mouse para dar zoom IN e OUT da cena respectivamente;" << endl;
	cout << "	Z para ativar a visao perspectiva;" << endl;
	cout << "	X para ativar a visao ortogonal;" << endl;
	cout << "ILUMINACAO:" << endl;
	cout << "	7 liga a luz 1 e apaga a luz 2;" << endl;
	cout << "	8 liga a luz 2 e apaga a luz 1;" << endl;
	cout << "	9 liga as luzes 1 e 2;" << endl;
	cout << "	0 desliga todas as luzes;" << endl;
	cout << "MENU:" << endl;
	cout << "	Botao do meio do mouse para reexibir o menu;" << endl;
}

// A habilitação da iluminação, e todas as inicializações necessárias
void SetupRC() 
	{ 
	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_CULL_FACE); 
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f); 
	}

// Calculo da Normal
void ReduceToUnit(float vector[3])
{
	float length;

	// Calculate the length of the vector		
	length = (float)sqrt((vector[0] * vector[0]) +
		(vector[1] * vector[1]) +
		(vector[2] * vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if (length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}
void calcNormal(float v[3][3], float out[3])
{
	float v1[3], v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];
	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];
	out[x] = v1[y] * v2[z] - v1[z] * v2[y];
	out[y] = v1[z] * v2[x] - v1[x] * v2[z];
	out[z] = v1[x] * v2[y] - v1[y] * v2[x];
	ReduceToUnit(out); // vetor unitário 
}

// Função usada para especificar o volume de visualização
void setVisParam(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();
	// Especifica a projeção perspectiva
	gluPerspective(angleV, fAspect, 0.1, 500);
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Especifica posição do observador e do alvo
	gluLookAt(0 + cx, 80 + cy, 200 + cz, 0 + cx, 0 + cy, 0 + cz, 0, 1, 0);
	glutPostRedisplay(); //redraw
}

// Função do cubo a partir de triangulos
void cubo(float a) {
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(-a / 2, a / 2, a / 2);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glVertex3f(a / 2, a / 2, a / 2);
	glVertex3f(a / 2, -a / 2, a / 2);
	glVertex3f(a / 2, a / 2, -a / 2);
	glVertex3f(a / 2, -a / 2, -a / 2);
	glVertex3f(-a / 2, a / 2, -a / 2);
	glVertex3f(-a / 2, -a / 2, -a / 2);
	glVertex3f(-a / 2, a / 2, a / 2);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0, 1.0, 1.0);
	glVertex3f(-a / 2, a / 2, -a / 2);
	glVertex3f(-a / 2, a / 2, a / 2);
	glVertex3f(a / 2, a / 2, -a / 2);
	glVertex3f(a / 2, a / 2, a / 2);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0, 1.0, 0.0);
	glVertex3f(a / 2, -a / 2, -a / 2);
	glVertex3f(a / 2, -a / 2, a / 2);
	glVertex3f(-a / 2, -a / 2, -a / 2);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glEnd();
}

// Função para leitura do arquivo de cena
void DisplayFileRead(const char* fileName) // na versão 2015 (char * fileName)
{
	fstream inStream;
	inStream.open(fileName, ios::in); // abre o arquivo
	if (inStream.fail()) return;      //falha na abertura do arquivo
	cout << "Abertura do arquivo com sucesso ..." << endl;
	inStream >> numObjects;			  // lê primeira linha do arquivo, número de objetos 
	cout << numObjects << " Objetos na cena ..." << endl;
	for (int i = 1; i <= numObjects; i++) { // leitura das demais linhas, ID dos objetos, posição e cor
		inStream >> ObjectList[i] >> x[i] >> y[i] >> z[i] >> r[i] >> g[i] >> b[i];
	}
	inStream.close();				// fecha o arquivo
}

// Função callback chamada para fazer o desenho
void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // limpa a tela e o buffer de profundidade
	glPushMatrix(); //Empurra uma nova pilha de matriz
	glRotatef(angle, 1.0f, 1.0f, 1.0f); // rotação de toda a cena
	
	for (int i = 0; i < numObjects+1; i++) {  // percorre todo o display-file
		switch (ObjectList[i]) {
		case 1: // cubo
			if (show01) {
				glPushMatrix();
				glColor3f(r[i] + r1, g[i] + g1, b[i] + b1);
				glTranslatef(x[i] + dx1, y[i] + dy1, z[i] + dz1);
				glRotatef(angle1, 1.0f, 1.0f, 1.0f);
				glutSolidCube(20 + t1);
				glPopMatrix();
			}	break;
		case 2: // esfera
			if (show02){
				glPushMatrix();
				glColor3f(r[i] + r2, g[i] + g2, b[i] + b2);
				glTranslatef(x[i] + dx2, y[i] + dy2, z[i] + dz2);
				glRotatef(angle2, 1.0f, 1.0f, 1.0f);
				glutSolidSphere(20 + t2, 24 + t2, 24 + t2);
				glPopMatrix();
			}	break;
		case 3: // cone
			if (show03){
				glPushMatrix();
				glColor3f(r[i] + r3, g[i] + g3, b[i] + b3);
				glTranslatef(x[i] + dx3, y[i] + dy3, z[i] + dz3);
				glRotatef(angle3, 1.0f, 1.0f, 1.0f);
				glutSolidCone(20 + t3, 20 + t3, 24 + t3, 24 + t3);
				glPopMatrix();
			}	break;
		case 4: // chaleira	
			if (show04) {
				glPushMatrix();
				glColor3f(r[i] + r4, g[i] + g4, b[i] + b4);
				glTranslatef(x[i] + dx4, y[i] + dy4, z[i] + dz4);
				glRotatef(angle4, 1.0f, 1.0f, 1.0f);
				glutSolidTeapot(10 + t4);
				glPopMatrix();
			}	break;
		case 5: // torus
			if (show05){
				glPushMatrix();
				glColor3f(r[i] + r5, g[i] + g5, b[i] + b5);
				glTranslatef(x[i] + dx5, y[i] + dy5, z[i] + dz5);
				glRotatef(angle5, 1.0f, 1.0f, 1.0f);
				glutSolidTorus(5 + t5, 5 + t5, 5, 5);
				glPopMatrix();
			}	break;
		case 6: // cubo
			if (show06){
				glPushMatrix(); //salva
				glColor3f(0.0 + r6, 0.0 + g6, 1.0 + b6);
				glTranslatef(x[i] + dx6, y[i] + dy6, z[i] + dz6);
				glRotatef(angle6, 1.0f, 1.0f, 1.0f);
				cubo(10 + t6);
				glutSolidDodecahedron();
				glPopMatrix(); //traz de volta, restaura
			}	break;
		}	
	}

	glPopMatrix();
	glutSwapBuffers();

}
	
// Inicializa parâmetros de rendering e iluminação
void initGL(void)
	{
		angleV = 45;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
		glClearDepth(1.0f);                   // Set background depth to farthest
		glEnable(GL_DEPTH_TEST);			// Enable depth testing for z-culling
		glDepthFunc(GL_LEQUAL);				// Set the type of depth-test
		glShadeModel(GL_FLAT);   // Enable smooth shading
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

		// Define os parametros referentes a luz 0
		GLfloat luzAmbiente0[4] = { 0.2,0.2,0.2,1.0 };	//luz ambiente
		GLfloat luzDifusa0[4] = { 0.5,0.5,0.5,0.5 };	   // "cor" 
		GLfloat luzEspecular0[4] = { 2.0, 2.0, 2.0, 2.0 };// "brilho" 
		GLfloat posicaoLuz0[4] = { 0.0, 50.0, 50.0, 1.0 }; //posicionamento 
		// Define os parametros referentes a luz 1
		GLfloat luzAmbiente1[4] = { 0.2,0.2,0.2,1.0 }; //luz ambiente
		GLfloat luzDifusa1[4] = { 1,1,1,1.0 };			// "cor" 
		GLfloat luzEspecular1[4] = { 1.0, 1.0, 1.0, 1.0 };// "brilho" 
		GLfloat posicaoLuz1[4] = { 500.0, -50.0, 1.0, 50.0 }; //posicionamento

		// Capacidade de brilho do material
		GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
		GLint especMaterial = 60;
		// Especifica que a cor de fundo da janela será preta
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Habilita o modelo de colorização de Gouraud
		glShadeModel(GL_SMOOTH);
		// Define a refletância do material 
		glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
		// Define a concentração do brilho
		glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
		// Ativa o uso da luz ambiente 
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente0);
		
		// Define os parâmetros da luz de número 0
		glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular0);
		glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz0);
		// Define os parâmetros da luz de número 1
		glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular1);
		glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);

		// Habilita a definição da cor do material a partir da cor corrente
		glEnable(GL_COLOR_MATERIAL);
		//Habilita o uso de iluminação
		glEnable(GL_LIGHTING);

		if (light01) { glEnable(GL_LIGHT0); } //deixa a luz 1 acessa por padrão
		if (light02) { glEnable(GL_LIGHT1); } //deixa a luz 2 acessa por padrão
	}

// Função callback chamada quando o tamanho da janela é alterado 
void reshape(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if (h == 0) h = 1;
	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;
	setVisParam(); //define como padrão a visão inicial como perspectiva
	glutPostRedisplay(); //redraw
}

// Função callback chamada para gerenciar eventos do mouse
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (angleV >= 10) angleV -= 3/2;
		cout << "Zoom IN - aperte Z para vizualizar a mudanca" << endl;
		break;
	case GLUT_RIGHT_BUTTON:
		if (angleV <= 130) angleV += 3/2;
		cout << "Zoom OUT - aperte Z para vizualizar a mudanca" << endl;
		break;	
	}
	if (button == GLUT_MIDDLE_BUTTON) if (state == GLUT_DOWN) { menu(); };
	glutPostRedisplay();  // redraw
}

// Função callback chamada para gerenciar eventos das teclas especiais do teclado
void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_PAGE_UP:
		if (selected == 0) angle++;
		if (selected == 1) angle1++;
		if (selected == 2) angle2++;
		if (selected == 3) angle3++;
		if (selected == 4) angle4++;
		if (selected == 5) angle5++;
		if (selected == 6) angle6++;
		cout << "Rotacionando" << endl;
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (selected == 0) angle--;
		if (selected == 1) angle1--;
		if (selected == 2) angle2--;
		if (selected == 3) angle3--;
		if (selected == 4) angle4--;
		if (selected == 5) angle5--;
		if (selected == 6) angle6--;
		cout << "Rotacionando" << endl;
		break;
	case GLUT_KEY_LEFT:
		if (selected == 0) cout << "*Nenhum objeto selecionado*" << endl;
		if (selected == 1) dx1--;
		if (selected == 2) dx2--;
		if (selected == 3) dx3--;
		if (selected == 4) dx4--;
		if (selected == 5) dx5--;
		if (selected == 6) dx6--;
		cout << "Movimentacao do objeto selecionado no eixo X negativo" << endl;
		break;
	case GLUT_KEY_RIGHT:
		if (selected == 0) cout << "*Nenhum objeto selecionado*" << endl;
		if (selected == 1) dx1++;
		if (selected == 2) dx2++;
		if (selected == 3) dx3++;
		if (selected == 4) dx4++;
		if (selected == 5) dx5++;
		if (selected == 6) dx6++;
		cout << "Movimentacao do objeto selecionado no eixo X positivo" << endl;
		break;
	case GLUT_KEY_UP:
		if (selected == 0) cout << "*Nenhum objeto selecionado*" << endl;
		if (selected == 1) dy1++;
		if (selected == 2) dy2++;
		if (selected == 3) dy3++;
		if (selected == 4) dy4++;
		if (selected == 5) dy5++;
		if (selected == 6) dy6++;
		cout << "Movimentacao do objeto selecionado no eixo Y positivo" << endl;
		break;
	case GLUT_KEY_DOWN:
		if (selected == 0) cout << "*Nenhum objeto selecionado*" << endl;
		if (selected == 1) dy1--;
		if (selected == 2) dy2--;
		if (selected == 3) dy3--;
		if (selected == 4) dy4--;
		if (selected == 5) dy5--;
		if (selected == 6) dy6--;
		cout << "Movimentacao do objeto selecionado no eixo Y negativo" << endl;
		break;
	case GLUT_KEY_F1:
		selected = 1;
		cout << "CUBO selecionado" << endl;
		break;
	case GLUT_KEY_F2:
		selected = 2;
		cout << "ESFERA selecionada" << endl;
		break;
	case GLUT_KEY_F3:
		selected = 3;
		cout << "CONE selecionado" << endl;
		break;
	case GLUT_KEY_F4:
		selected = 4;
		cout << "CHALEIRA selecionada" << endl;
		break;
	case GLUT_KEY_F5:
		selected = 5;
		cout << "TORUS selecionado" << endl;
		break;
	case GLUT_KEY_F6:
		selected = 6;
		cout << "CUBO DE TRIANGULOS selecionado" << endl;
		break;
	case GLUT_KEY_F7:
		if (selected == 1) t1--;
		if (selected == 2) t2--;
		if (selected == 3) t3--;
		if (selected == 4) t4--;
		if (selected == 5) t5--;
		if (selected == 6) t6--;
		cout << "Diminuindo objeto" << endl;
		break;
	case GLUT_KEY_F8:
		if (selected == 1) t1++;
		if (selected == 2) t2++;
		if (selected == 3) t3++;
		if (selected == 4) t4++;
		if (selected == 5) t5++;
		if (selected == 6) t6++;
		cout << "Aumentando objeto" << endl;
		break;
	case GLUT_KEY_END:
		selected = 0;
		cout << "Nenhum objeto selecionado" << endl;
		break;
	}
	glutPostRedisplay();   // redraw
}

// Função callback chamada para gerenciar eventos das teclas normais do teclado
void NormalKeyHandler(unsigned char key, int x, int y){
	switch (key) {
	case 'z': // Perspectiva
		setVisParam();
		cout << "Visao perspectiva" << endl;
		glutPostRedisplay(); //redraw
		break;
	case 'x': // Ortogonal
		glOrtho(0.5, 3, 0.5, 3, 0, 1.8);
		cout << "Visao ortogonal" << endl;
		glutPostRedisplay(); //redraw
		break;
	case 'w': //up
		cy = cy + 5;
		glutPostRedisplay(); //redraw
		cout << "Movimentacao de camera no eixo Y positivo - aperte Z para vizualizar a mudanca" << endl;
		break;
	case 's': //down
		cy = cy - 5;
		glutPostRedisplay(); //redraw
		cout << "Movimentacao de camera no eixo Y negativo - aperte Z para vizualizar a mudanca" << endl;
		break;
	case 'a': //Left
		cx = cx - 5;
		glutPostRedisplay(); //redraw
		cout << "Movimentacao de camera no eixo X negativo - aperte Z para vizualizar a mudanca" << endl;
		break;
	case 'd': //Right
		cx = cx + 5;
		glutPostRedisplay(); //redraw
		cout << "Movimentacao de camera no eixo X positivo - aperte Z para vizualizar a mudanca" << endl;
		break;
	case 'q': //Z+
		cz = cz + 5;
		glutPostRedisplay(); //redraw
		cout << "Movimentacao de camera no eixo Z positivo - aperte Z para vizualizar a mudanca" << endl;
		break;
	case 'e': //Z+
		cz = cz - 5;
		glutPostRedisplay(); //redraw
		cout << "Movimentacao de camera no eixo Z negativo - aperte Z para vizualizar a mudanca" << endl;
		break;
	case 'u': // r up
		if (selected == 1) r1 = r1 + 0.02;
		if (selected == 2) r2 = r2 + 0.02;
		if (selected == 3) r3 = r3 + 0.02;
		if (selected == 4) r4 = r4 + 0.02;
		if (selected == 5) r5 = r5 + 0.02;
		if (selected == 6) r6 = r6 + 0.02;
		cout << "R up" << endl;
		break;
	case 'i': //g up
		if (selected == 1) g1 = g1 + 0.02;
		if (selected == 2) g2 = g2 + 0.02;
		if (selected == 3) g3 = g3 + 0.02;
		if (selected == 4) g4 = g4 + 0.02;
		if (selected == 5) g5 = g5 + 0.02;
		if (selected == 6) g6 = g6 + 0.02;
		cout << "G up" << endl;
		break;
	case 'o': //b up
		if (selected == 1) b1 = b1 + 0.02;
		if (selected == 2) b2 = b2 + 0.02;
		if (selected == 3) b3 = b3 + 0.02;
		if (selected == 4) b4 = b4 + 0.02;
		if (selected == 5) b5 = b5 + 0.02;
		if (selected == 6) b6 = b6 + 0.02;
		cout << "B up" << endl;
		break;
	case 'j': //r down
		if (selected == 1) r1 = r1 - 0.02;
		if (selected == 2) r2 = r2 - 0.02;
		if (selected == 3) r3 = r3 - 0.02;
		if (selected == 4) r4 = r4 - 0.02;
		if (selected == 5) r5 = r5 - 0.02;
		if (selected == 6) r6 = r6 - 0.02;
		cout << "R down" << endl;
		break;
	case 'k': //g down
		if (selected == 1) g1 = g1 - 0.02;
		if (selected == 2) g2 = g2 - 0.02;
		if (selected == 3) g3 = g3 - 0.02;
		if (selected == 4) g4 = g4 - 0.02;
		if (selected == 5) g5 = g5 - 0.02;
		if (selected == 6) g6 = g6 - 0.02;
		cout << "G down" << endl;
		break;
	case 'l': //b down
		if (selected == 1) b1 = b1 - 0.02;
		if (selected == 2) b2 = b2 - 0.02;
		if (selected == 3) b3 = b3 - 0.02;
		if (selected == 4) b4 = b4 - 0.02;
		if (selected == 5) b5 = b5 - 0.02;
		if (selected == 6) b6 = b6 - 0.02;
		cout << "B down" << endl;
		break;
	case '1': // cubo
		if (show01){ show01 = FALSE; 
		cout << "CUBO desligado" << endl;}	
		else {show01 = TRUE;
		cout << "CUBO ligado" << endl;}
		break;
	case '2': // esfera
		if (show02) {show02 = FALSE;
			cout << "ESFERA desligada" << endl;}
		else{ show02 = TRUE; cout << "ESFERA ligada" << endl; }
		break;
	case '3': //cone
		if (show03) {
			show03 = FALSE;
			cout << "CONE desligado" << endl;
		}
		else { show03 = TRUE; cout << "CONE ligado" << endl; }
		break;
	case '4': // chaleira
		if (show04) {
			show04 = FALSE;
			cout << "CHALEIRA desligada" << endl;
		}
		else { show04 = TRUE; cout << "CHALEIRA ligada" << endl; }
		break;
	case '5': // torus
		if (show05) {
			show05 = FALSE;
			cout << "TORUS desligado" << endl;
		}
		else { show05 = TRUE; cout << "TORUS ligado" << endl; }
		break;
	case '6': // cubo de triangulos
		if (show06) {
			show06 = FALSE;
			cout << "CUBO DE TRIANGULOS desligado" << endl;
		}
		else { show06 = TRUE; cout << "CUBO DE TRIANGULOS ligado" << endl; }
		break;
	case '7':
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		cout << "Luz 1 - ON" << endl;
		cout << "Luz 2 - OFF" << endl;
		break;
	case '8':
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		cout << "Luz 1 - OFF" << endl;
		cout << "Luz 2 - ON" << endl;
		break;
	case '9':
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		cout << "Luz 1 - ON" << endl;
		cout << "Luz 2 - ON" << endl;
		break;
	case '0':
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		cout << "Luz 1 - OFF" << endl;
		cout << "Luz 2 - OFF" << endl;
		break;
	}
	glutPostRedisplay(); //redraw
}

// Programa Principal -- Main
int main(int argc, char** argv) {
	DisplayFileRead("df.txt");              // se estiver aqui, lê somente uma vez
	cout << "MODO DE VISAO INICIAL: perspectiva" << endl;
	menu();									// mostra a interface de comandos do prompt
	glutInit(&argc, argv);					// Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE);		// Enable double buffered mode
	glutInitWindowSize(640, 480);			// Set the window's initial width & height
	glutInitWindowPosition(50, 50);			// Position the window's initial top-left corner
	glutCreateWindow(title);				// Create window with the given title
	glutDisplayFunc(render);				// Regster callback for render function
	glutSpecialFunc(processSpecialKeys);	// Register callback handler for special keys (keyborad)
	glutKeyboardFunc(NormalKeyHandler);		// Register callback handler for normal keys (keyborad)
	glutReshapeFunc(reshape);				// Register callback for window resize event
	glutMouseFunc(mouse);					// Register callback for mouse event
	glutIdleFunc(render);					// no animation
	initGL();								// Initialization function
	glutMainLoop();							// event loop
	return 0;
}