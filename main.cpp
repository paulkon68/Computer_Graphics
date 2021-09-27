#include<GL/glut.h>

int *leftIntersec=(int *)malloc(500*sizeof(int)); 
int *rightIntersec=(int *)malloc(500*sizeof(int)); 

void findIntersectionPoints(GLint x1,GLint y1,GLint x2,GLint y2);
void Draw(void);
void Init(void);
void Menu(int id);

int shape = 0;

int main(int argC,char *argV[])
{
	
    glutInit(&argC,argV);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    
    glutCreateWindow("Scanline Fill Algorithm");
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    Init();
    glutDisplayFunc(Draw);
    
    glutMainLoop();
    
    free(rightIntersec);
    free(leftIntersec);
    
    return 0;
}

void Init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);

    glutCreateMenu(Menu);
    
    glutAddMenuEntry("Parallelogram", 1);
    glutAddMenuEntry("Rhombus", 2);
    glutAddMenuEntry("Square", 3);
    glutAddMenuEntry("Triangle", 4);
    glutAddMenuEntry("Hourglass", 5);
    glutAddMenuEntry("Trapezoid Polygon -1-", 6);
    glutAddMenuEntry("Trapezoid Polygon -2-", 7);
    glutAddMenuEntry("Trapezoid Polygon -3-", 8);
    glutAddMenuEntry("Exit", 9);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Menu(int id)
{
    if(id == 1)
        shape = 1;
    else if(id == 2)
        shape = 2;
    else if(id == 3)
    	shape = 3;
    else if(id == 4)
        shape = 4;
    else if(id == 5)
    	shape = 5;
    else if(id == 6)
        shape = 6;
    else if(id == 7)
    	shape = 7;
    else if(id == 8)
        shape = 8;
	else if(id == 9) 
		shape = 9;
	
    glutPostRedisplay();
}


void findIntersectionPoints(GLint x1,GLint y1,GLint x2,GLint y2)
{
    float x,M;
    int tmp,y;
    
    if(y1>y2)
    {
        tmp = x1;
        x1 = x2;
        x2 = tmp;

        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
	
	// check if the denominator is zero (if slope = 0)
    if(!(y2-y1))
        M = x2-x1;
    else
        M = (x2-x1)/(y2-y1);

    x = x1;
    
    // scan from bottom to top
    for(y=y1;y<=y2;y++)
    {
        if(x<leftIntersec[y])
            leftIntersec[y]=x;
        if(x>rightIntersec[y])
            rightIntersec[y]=x;

        x = x + M;
    }
}

void Draw(void)
{
    int x,y,i;
    
    
    glClear(GL_COLOR_BUFFER_BIT);

    for(i=0;i<500;i++)
    {
        leftIntersec[i] = 500;
        rightIntersec[i] = 0;
    }
	
	if (shape == 1){
		
		// parallelogram
     	GLint P1[2] = {250, 250}, P2[2] = {150, 250}, P3[2] = {250, 350}, P4[2] = {350, 350};

	    glBegin(GL_LINE_LOOP);
	        glVertex2iv(P1);
	        glVertex2iv(P2);
	        glVertex2iv(P3);
	        glVertex2iv(P4);
	    glEnd();
    
	    findIntersectionPoints(P1[0],P1[1],P2[0],P2[1]);
	    findIntersectionPoints(P2[0],P2[1],P3[0],P3[1]);
	    findIntersectionPoints(P3[0],P3[1],P4[0],P4[1]);
	    findIntersectionPoints(P4[0],P4[1],P1[0],P1[1]);
    
	} 
	
	else if(shape == 2){
	
		// Rhombus:
	    GLint P1[2] = {125, 250}, P2[2] = {250, 125}, P3[2] = {375, 250}, P4[2] = {250, 375};	
	     
	    glBegin(GL_LINE_LOOP);
		    glVertex2iv(P1);
		    glVertex2iv(P2);
		    glVertex2iv(P3);
	        glVertex2iv(P4);
		glEnd();
	    
		    findIntersectionPoints(P1[0],P1[1],P2[0],P2[1]);
		    findIntersectionPoints(P2[0],P2[1],P3[0],P3[1]);
		    findIntersectionPoints(P3[0],P3[1],P4[0],P4[1]);
		    findIntersectionPoints(P4[0],P4[1],P1[0],P1[1]);
		    
	} 
	 
	 else if(shape == 3){
	 	
	 	// square:
        GLint P1[2] = {250, 250}, P2[2] = {350, 250}, P3[2] = {350, 350}, P4[2] = {250, 350};
        
        glBegin(GL_LINE_LOOP);
		    glVertex2iv(P1);
		    glVertex2iv(P2);
		    glVertex2iv(P3);
	        glVertex2iv(P4);
		glEnd();
	    
		findIntersectionPoints(P1[0],P1[1],P2[0],P2[1]);
	    findIntersectionPoints(P2[0],P2[1],P3[0],P3[1]);
	    findIntersectionPoints(P3[0],P3[1],P4[0],P4[1]);
		findIntersectionPoints(P4[0],P4[1],P1[0],P1[1]);
		
	}
	 
	else if(shape == 4){
		
		// triangle:
        GLint P1[2] = {250, 250}, P2[2] = {350, 250}, P3[2] = {350, 350};
        
        glBegin(GL_LINE_LOOP);
		    glVertex2iv(P1);
		    glVertex2iv(P2);
		    glVertex2iv(P3);
		glEnd();
	    
		findIntersectionPoints(P1[0],P1[1],P2[0],P2[1]);
	    findIntersectionPoints(P2[0],P2[1],P3[0],P3[1]);
	    findIntersectionPoints(P3[0],P3[1],P1[0],P1[1]);
	    
	}
    
    else if(shape == 5){
    	
    	// hourglass:
    	GLint P1[2] = {250, 250}, P2[2] = {350, 250}, P3[2] = {250, 350}, P4[2] = {350, 350};
    	
    	 glBegin(GL_LINE_LOOP);
		    glVertex2iv(P1);
		    glVertex2iv(P2);
		    glVertex2iv(P3);
	        glVertex2iv(P4);
		glEnd();
	    
		findIntersectionPoints(P1[0],P1[1],P2[0],P2[1]);
	    findIntersectionPoints(P2[0],P2[1],P3[0],P3[1]);
	    findIntersectionPoints(P3[0],P3[1],P4[0],P4[1]);
		findIntersectionPoints(P4[0],P4[1],P1[0],P1[1]);
    	
	}
	
	else if(shape == 6){
		
		// trapezoid Polygon(1): 
       GLint P1[2] = {250, 250}, P2[2] = {350, 250}, P3[2] = {350, 350}, P4[2] = {250, 400};
       
       glBegin(GL_LINE_LOOP);
		    glVertex2iv(P1);
		    glVertex2iv(P2);
		    glVertex2iv(P3);
	        glVertex2iv(P4);
		glEnd();
	    
		findIntersectionPoints(P1[0],P1[1],P2[0],P2[1]);
	    findIntersectionPoints(P2[0],P2[1],P3[0],P3[1]);
	    findIntersectionPoints(P3[0],P3[1],P4[0],P4[1]);
		findIntersectionPoints(P4[0],P4[1],P1[0],P1[1]);
		
	}
	
	else if(shape == 7){
		
		// trapezoid Polygon (2):
        GLint P1[2] = {250, 250}, P2[2] = {150, 250}, P3[2] = {150, 350}, P4[2] = {350, 350};
     
     	glBegin(GL_LINE_LOOP);
		    glVertex2iv(P1);
		    glVertex2iv(P2);
		    glVertex2iv(P3);
	        glVertex2iv(P4);
		glEnd();
	    
		findIntersectionPoints(P1[0],P1[1],P2[0],P2[1]);
	    findIntersectionPoints(P2[0],P2[1],P3[0],P3[1]);
	    findIntersectionPoints(P3[0],P3[1],P4[0],P4[1]);
		findIntersectionPoints(P4[0],P4[1],P1[0],P1[1]);
		
	}
    
    else if(shape == 8){
		
		// trapezoid Polygon (3):
        GLint P1[2] = {250, 250}, P2[2] = {150, 250}, P3[2] = {50, 350}, P4[2] = {350, 350};
     
     	glBegin(GL_LINE_LOOP);
		    glVertex2iv(P1);
		    glVertex2iv(P2);
		    glVertex2iv(P3);
	        glVertex2iv(P4);
		glEnd();
	    
		findIntersectionPoints(P1[0],P1[1],P2[0],P2[1]);
	    findIntersectionPoints(P2[0],P2[1],P3[0],P3[1]);
	    findIntersectionPoints(P3[0],P3[1],P4[0],P4[1]);
		findIntersectionPoints(P4[0],P4[1],P1[0],P1[1]);
		
	}
	
	else if(shape == 9) exit(0);
	
    for(y=0;y<500;y++)
    {
        for(x=leftIntersec[y];x<rightIntersec[y];x++)
        {
        	glColor3f(0.5, 0.5, 0.5);
            glBegin(GL_POINTS);
            	glVertex2i(x,y);
            glEnd();
            glFlush();
        }
    }
    
    
}

