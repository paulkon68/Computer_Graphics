#include <GL/glut.h>
#include <GL/glu.h>

void Draw(void);
void Cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[]);
void cubeFace(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[] );
void keyStroke(unsigned char button, int x, int y);

GLfloat cameraX = 0, cameraY = 0, cameraZ = 4;
char *keyboardCharacter = (char *)malloc(8*sizeof(char));

int main(int argC, char *argV[]){
	
	glutInit(&argC, argV);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 150);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Perspective View of a Cube");

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 2, 10);
	glMatrixMode(GL_MODELVIEW);
	
	keyboardCharacter[0] = 'x';
	keyboardCharacter[1] = 'X';
	keyboardCharacter[2] = 'y';
	keyboardCharacter[3] = 'Y';
	keyboardCharacter[4] = 'z';
	keyboardCharacter[5] = 'Z';
	keyboardCharacter[6] = 'q';
	
	glutDisplayFunc(Draw);
	glutKeyboardFunc(keyStroke);
	glutMainLoop();
	
	free(keyboardCharacter);
	
	return 0;
}

void Draw(void){
	
	GLfloat V[8][3] = {
						{-0.5, 0.5, 0.5},
						{0.5, 0.5, 0.5},
						{0.5,-0.5, 0.5},
						{-0.5,-0.5, 0.5},
						{-0.5, 0.5, -0.5},
						{0.5, 0.5, -0.5},
						{0.5,-0.5, -0.5},
						{-0.5,-0.5, -0.5}
					  };
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
	Cube(V[0], V[1], V[2], V[3],V[4],V[5],V[6],V[7]);
	
	glutSwapBuffers();
	
}

void Cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[]){
	
	glColor3f(1, 0, 0);
	cubeFace(V0, V1, V2, V3);
	
	glColor3f(0, 1, 0);
	cubeFace(V4, V5, V6, V7);
	
	glColor3f(0, 0, 1);
	cubeFace(V0, V4, V7, V3);
	
	glColor3f(1, 1, 0);
	cubeFace(V1, V5, V6, V2);
	
	glColor3f(0, 1, 1);
	cubeFace(V3, V2, V6, V7);
	
	glColor3f(1, 0, 1);
	cubeFace(V0, V1, V5, V4);	
		
}

void cubeFace(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[] ){
	
	glBegin(GL_POLYGON);
		glVertex3fv(A);
		glVertex3fv(B);
		glVertex3fv(C);
		glVertex3fv(D);
	glEnd();
	
}

void keyStroke(unsigned char button, int x, int y){
	
	if (button == keyboardCharacter[0]) cameraX -= 0.5;
	else if (button == keyboardCharacter[1]) cameraX += 0.5;
	else if (button == keyboardCharacter[2]) cameraY -= 0.5;
	else if (button == keyboardCharacter[3]) cameraY += 0.5;
	else if (button == keyboardCharacter[4]) cameraZ -= 0.5;
	else if (button == keyboardCharacter[5]) cameraZ += 0.5;
	else if (button == keyboardCharacter[6]) exit(0);
	
	glutPostRedisplay();
}
