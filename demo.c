#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
const int numVertices=5;
const int numEdges=6;
const float vertices[7][7]={{0.0,0.0},{-300.0,-300.0},{300.0,-300.0},{-300.0,-350.0},{300.0,-350.0}};
const int edges[7][7]={{0,1},{1,2},{2,0},{1,3},{2,4},{3,4}};
const float r=225.0;
float theta=0.0;
const float A[3]={225.0,0.0};
float centres1[5][5]={{225.0,0.0},{159.1,-159.1},{0.0,-225.0},{-159.1,-159.1}};
float centres2[5][5]={{-225.0,0.0},{-159.1,159.1},{0.0,225.0},{159.1,159.1}};

float vert[10][5][5];

const int sqedge[5][5]={{0,1},{1,2},{2,3},{3,0}};
void timer(int);

void reshape(int w, int h){
glViewport(0,0,(GLsizei)w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-780,780,-420,420);
glMatrixMode(GL_MODELVIEW);
}
void compute_sq_centres(){

for(int i=0;i<4;i++){
if(i==0){
centres1[i][0]=r * cos(-theta);
centres1[i][1]=r * sin(-theta);}
if(i==1){
centres1[i][0]=r * cos((pi/4.0)+theta);
centres1[i][1]=(r* sin((pi/4.0)+theta))*(-1);
}
if(i==2){
centres1[i][0]=r*cos((pi/2.0)+theta);
centres1[i][1]=(r*sin((pi/2.0)+theta))*(-1);
}
if(i==3){
centres1[i][0]=r*cos(((3*pi)/4.0)+theta);
centres1[i][1]=(r*sin(((3*pi)/4.0)+theta))*(-1);
}
}
for (int i=0;i<4;i++)
{
if(i==0){
centres2[i][0]=r * cos(pi-theta);
centres2[i][1]=r * sin(pi-theta);}
if(i==1){
centres2[i][0]=r * cos(((3.0*pi)/4.0)-theta);
centres2[i][1]=r* sin(((3.0*pi)/4.0)-theta);
}
if(i==2){
centres2[i][0]=r*cos((pi/2.0)-theta);
centres2[i][1]=r*sin((pi/2.0)-theta);
}
if(i==3){
centres2[i][0]=r*cos(((pi)/4.0)-theta);
centres2[i][1]=r*sin(((pi)/4.0)-theta);
}
}
}


void compute_vertices(){
int i,j,k,x,y;
for(i=0;i<8;i++)
{
	if(i<4)
	{
	  x=centres1[i][0];
	  y=centres1[i][1];
	}else{
	  x=centres2[i-4][0];
	  y=centres2[i-4][1];
	}
	for(j=0;j<4;j++)
	{
		if(j%4==0){
			vert[i][j][0]=x+30;
			vert[i][j][1]=y+30;}
		else if(j%4==1){
			vert[i][j][0]=x+30;
			vert[i][j][1]=y-30;}
		else if(j%4==2){
			vert[i][j][0]=x-30;
			vert[i][j][1]=y-30;}
		else{
			vert[i][j][0]=x-30;
			vert[i][j][1]=y+30;}
	}

}

}
void myInit(void)
{
glClearColor(0.0,0.0,0.0,1.0);
glColor3f(1.0,1.0,1.0);
glPointSize(5.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-780,780,-420,420);
}

void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_POINTS);
float x,y,i;
for(i=0;i<(2*pi); i+=0.001)
{
x=225 * cos(i);
y=225 * sin(i);
glVertex2i(x,y);
}
glEnd();

glBegin(GL_POINTS);
float x1,y1,j;
for(j=0;j<(2*pi); j+=0.001)
{
x1=60 * cos(j);
y1=60 * sin(j);
glVertex2i(x1,y1);
}
glEnd();

glBegin(GL_POINTS);
float x2,y2,l;
for(l=0;l<(2*pi); l+=0.001)
{
x2=6 * cos(l);
y2=6 * sin(l);
glVertex2i(x2,y2);
}
glEnd();

glBegin(GL_LINES);
for(int i=0; i<numEdges;i++)
{
glVertex2fv(vertices[edges[i][0]]);
glVertex2fv(vertices[edges[i][1]]);
}

glEnd();

glBegin(GL_QUADS);
for(int sq=0;sq<8;sq++){
for(int i=0;i<4;i++){
glVertex2fv(vert[sq][sqedge[i][0]]);
glVertex2fv(vert[sq][sqedge[i][1]]);

}
}

glEnd();

glBegin(GL_LINES);
for(int i=0; i<4;i++)
{
glVertex2fv(centres1[i]);
glVertex2fv(centres2[i]);
}
glEnd();
glutSwapBuffers();

}

int main(int argc, char ** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE  | GLUT_RGB);

glutInitWindowSize(1336,968);
glutInitWindowPosition(0,0);



glutCreateWindow("Carnival");
myInit();
compute_vertices();

glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutTimerFunc(0,timer,0);
myInit();
glutMainLoop();
}

void timer (int k){
theta=theta+(pi/64.0);
printf("%f\n",theta);
compute_sq_centres();
compute_vertices(); 
 glutPostRedisplay();
if(theta<15.0)
 glutTimerFunc(1000/5,timer,0);
}
