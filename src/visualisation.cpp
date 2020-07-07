
#include "visualisation.h"

void visualise::initialise()
{
	
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return ;
	}
	// Open a window and create its OpenGL context
	window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Display", NULL, NULL);
	if( !window){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(window);
	
	glViewport(0 ,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int argc;
	char** argv;
	glutInit(&argc,argv);
}
void visualise::Draw_lines()
{
	glColor3ub(0,255,0);
	glBegin(GL_LINES);
	glPointSize(100);
	for(int i=0;i<grid_y + 1;i++)
	{
		glVertex2f(x1,y1+ i*border);
		glVertex2f(x2,y1+ i*border);
	}
	for(int i=0;i<grid_x + 1;i++)
	{
		glVertex2f(x1+ i*border,y1);
		glVertex2f(x1 + i*border,y2);
	}
	
	glEnd();
}
void visualise::Draw_obstacles()
{
	float y_obst_start = y1 + (1.5 * scaling_factor) + border/2;
	float y_obst_end = y1 + 2.5 * scaling_factor + border/2;
	float x_interm1 = x1 + 2* scaling_factor + border/2;
	float x_interm2 = x1 + 2.8* scaling_factor + border/2;
	GLfloat polygonVertices1[] =
	{
		x1,y_obst_start,0,
		x_interm1,y_obst_start,0,
		x_interm1,y_obst_end,0,
		x1,y_obst_end,0
	};
	GLfloat polygonVertices2[] =
	{
		x2,y_obst_start,0,
		x_interm2,y_obst_start,0,
		x_interm2,y_obst_end,0,
		x2,y_obst_end,0
	};
	glColor3ub(0,255,255);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,polygonVertices1);
	glDrawArrays(GL_POLYGON,0,4);
	glVertexPointer(3,GL_FLOAT,0,polygonVertices2);
	glDrawArrays(GL_POLYGON,0,4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void visualise::Draw_path(std::vector<point>& path,point& start, point& goal)
{
	
	
        glColor3ub(0,0,255);
		glBegin(GL_LINE_STRIP);
		glPointSize(100);
		for(int i=0;i<path.size();i++)
		{
			float x = x1 + border/2+( path[i].x * scaling_factor);
			float y = y1 + border/2+( path[i].y * scaling_factor);
			glVertex2f(x,y);
		}    
		glEnd();
        writeText(start.x,start.y,"start");
        writeText(goal.x,goal.y,"goal");
       
}
void visualise::writeText(int x, int y, char *string)
{
	glColor3f( 0, 0, 0 );
	
	glRasterPos2f(x1+ (x*scaling_factor), y1+(y*scaling_factor));
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
	}
}

void visualise::Draw_environment() 
{
	GLfloat polygonVertices[] =
	{
		x1,y1,0,
		x2,y1,0,
		x2,y2,0,
		x1,y2,0
	};
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3ub(255,255,255);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,polygonVertices);
	glDrawArrays(GL_POLYGON,0,4);
	glDisableClientState(GL_VERTEX_ARRAY);
	Draw_lines();
	Draw_obstacles();
	
}

