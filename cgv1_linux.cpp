//#include<GL/gl.h>
#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
//#include <windows.h>
//#include <direct.h>
//#include <process.h>
#include<string.h>
 // Linux
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#define GL_PI 3.14
#define MAX 25
#define INF 999

int n,i=1,a[25],b[25],cost[25][25],cost1[25][25],tree[25][25],l[2];
int src,mincost=0;
int visited[25];
char s[20],*s1;
int ch=1;
void *currentfont;


typedef struct {
   int u, v, w;
} Edge;

//const int NODES = 5 ;   /* the number of nodes */
int EDGES=0;            /* the number of edges */
Edge edges[32];         /* large enough for n <= 2^NODES=32 */																	//	edges is an array of structures


//FUNCTION TO SELECT BITMAP FONT
void setFont(void *font)
{
    currentfont=font;
}



//FUNCTION TO DRAW sentence string at (x,y)
void drawstring(GLfloat x,GLfloat y,char *c)
{
  glRasterPos2f(x,y);

 	//This loop ensures that the whole sentence is drawn out
	while(*c!='\0')
	{
	    glutBitmapCharacter(currentfont,*c);
		*c++;
	}
}



//FUNCTION TO DELAY- This simply gives the animations a fluid like feel
void delay()
{
    for(int i=0;i<25000;i++)
       for(int j=0;j<250000;j++);
}


//DISPLAY FUNCTION FOR TITLE PAGE
void title()
{
    glLineWidth(5);								//This line loop is just to make a border within the window for asthetics
    glColor3f(1,1,0);							//Yellow border
    glBegin(GL_LINE_LOOP);
          glVertex2f(10,10);
          glVertex2f(10,490);
          glVertex2f(490,490);
          glVertex2f(490,10);
    glEnd();

    setFont(GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0,1.0,1.0);
    drawstring(100,440,"Topic: Prim's Algorithm");
    glColor3f(1.0,1.0,1.0);
    drawstring(100,400,"Submitted by");
    glColor3f(1.0,0.0,0.0);
    drawstring(100,360,"Akanksha Mishra\t 1CR16CS012");
    glColor3f(1.0,0.0,0.0);
    drawstring(100,320,"Kumar Shaurya\t 1CR16CS073");
    glColor3f(1.0,0.0,0.0);
    drawstring(100,280,"CSE 6th Semester");
    glColor3f(1.0,1.0,1.0);
    drawstring(100,100,"Right click in My Window for options");

	glFlush();
}


//DISPLAY FUNCTION FOR INITIALIZING (DRAWING) THE  INPUT AND OUTPUT AREAS
void initialDraw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    setFont(GLUT_BITMAP_HELVETICA_18);

    glColor3f(0.0,0.0,0.0);
    drawstring(20,230,"Input Area");
    drawstring(20,470,"Output Area");

    glColor3f(0.0,0.0,0.0);					// Color Black
    glLineWidth(2.5);
    glBegin(GL_LINE_LOOP);					// These Line loops are to border the input and output boxes in the My Window
          glVertex2f(10,10);
          glVertex2f(490,10);
		  glVertex2f(490,250);
          glVertex2f(10,250);
    glEnd();

	glBegin(GL_LINE_LOOP);
          glVertex2f(10,255);
          glVertex2f(490,255);
		  glVertex2f(490,490);
          glVertex2f(10,490);

    glEnd();

    glFlush();
}

//BLANK DISPLAY FUNCTION
void display (void)
{

    glFlush();

}

//DRAW A BITMAP NUMBER i at (x,y)
void raster(int x,int y,int i)
{
    char z=i+'0';
    glRasterPos2f(x-5,y-5);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,z);
}




//DRAW THE NODES (SQUARES)
void drawSquare(int x, int y)
{

    if(i<=n)									// This ensures that one cannot place more than assigned nodes onto the screen
    {
        y = 500-y;                              //Convert from screen coordinates
        glPointSize(35);						// This sets a single point size to be that big

        if(i==src)
			glColor3f(0.7f, 0.4f, 0.0f);
        else
			glColor3f(0.5f, 0.5f, 0.8f);

        glBegin(GL_POINTS);
			glVertex2f(x , y);
        glEnd();

        a[i]=x;
        b[i]=y;

        glColor3f(0.0f, 1.0f, 0.0f);
        int i1=sprintf(s,"%d",ch);			// Prints the name of the node
        s1=s;
        drawstring(x-5,y-5,s1);


        glFlush();
   }

   ch++;									// Increments the letter to name the node
   i++;										// Increment as the num of nodes formed increasess
}





//READ DATA: |V|,COST MATRIX
void read()
{
    printf("Enter the number of vertices:\n");
    scanf("%d",&n);
    printf("Enter the cost adjacency matrix:\n");
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&cost[i][j]);
            if(cost[i][j]==0)				// Means if node is unreachable via that path
                 cost[i][j]=999;

            else
            {
                edges[EDGES].u=i;
                edges[EDGES].v=j;
                edges[EDGES].w=cost[i][j];
                EDGES++;
            }
        }

      for(int i=1;i<=n;i++)
      {
          for(int j=1;j<=n;j++)
          {
             cost1[i][j]=cost[i][j];
               if(cost1[i][j]==0)				// Means if node is unreachable via that path
                  cost1[i][j]=999;
          }
      }
     printf("\nGO TO MY WINDOW, PLACE THE NODES IN INPUT AREA AND THEN CLICK RIGHT BUTTON FOR NEXT OPTION\n");
     initialDraw(); //Draw the initial screen
}


// TILL HERE EASILY UNDERSTOOD AND MODIFIED------------------------------------------------------------------------------------------

//DRAW THE EDGES THAT CONNECTING THE NODES
void drawlineCN()
{
  int j,k,x1,x2,y1,y2;
  for(j=1;j<=n;j++)
  	for(k=1;k<=n;k++)
	{
		if(cost[j][k]!=999 && j<k)
		{
			 x1=a[j];
			 y1=b[j];
			 x2=a[k];
			 y2=b[k];


			 glColor3f(0.0,0.5,0.0);

			 glLineWidth(3);
			 glBegin(GL_LINES);
					  glVertex2i(x1-6,y1+10);
					  glVertex2i(x2-6,y2+10);
			 glEnd();
			 int i2=sprintf(s,"%d",cost[j][k]);							// Prints the weight onto the Edge
			 s1=s;
			 drawstring((x1+x2-16)/2,(y1+y2+22)/2,s1);
			 glFlush();
		}

		if(cost[j][k]!=cost[k][j] && cost[j][k]!=999 && j>k)			// This checks if the same path weight A-->B and B-->A is there... If so, then dont draw
		{
			 x1=a[j];
			 y1=b[j];
			 x2=a[k];
			 y2=b[k];

			 glColor3f(1.0,0.5,0.0);
			 glBegin(GL_LINES);
				               glVertex2i(x1+10,y1+18);
				               glVertex2i(x2+10,y2+18);
			 glEnd();
			 int i3=sprintf(s,"%d",cost[j][k]);						// Prints the weight onto the Edge
			 s1=s;
			 drawstring((x1+x2+20)/2,(y1+y2+36)/2,s1);
			 glFlush();
		}
   	}
}


void shortestpath(int src)
{
   int p,q,x,y,x1,x2,y1,y2,j;
   int k=1,u=0,v=0,min;
   int l=0;

                while(k<n)
		{

			for(i=1,min=999;i<=n;i++)
			{
				for(j=1;j<=n;j++)
				{
						if(cost[i][j]<min)
					       {
						    if(visited[i]==1)
						    {
							  u=i;
							  v=j;
							  min=cost[i][j];
						    }
						}
				 }
			}

                        //Setting the end vertices of an edge to tree array
                        tree[l][1]=u;
                        tree[l++][2]=v;
                        printf("%d-->%d=%d\n",u,v,min);


			k++;
                        mincost=mincost+min;
                        visited[v]=1;
                        cost[u][v]=cost[v][u]=999;

		}
               printf("The minimum cost is: %d\n",mincost);



   //DRAW THE SPANNING TREE
   int cch=1;									// In the output section while naming the spanning tree
   for(int r=1;r<=n;r++)
   {

             x=a[r];
             y=b[r];

             glPointSize(35);
             if(r==src)
                   glColor3f(0.7f, 0.4f, 0.0f);
             else
                   glColor3f(0.5f, 0.5f, 0.8f);

             glBegin(GL_POINTS);
                   glVertex2f(x+5,y+254);					// It was set up such that the letter appears mid of node
             glEnd();

             glColor3f(0.0,1.0,0.0);
             int i4=sprintf(s,"%d",cch);					// Prints the name of the node
             s1=s;
             drawstring(x,y+250,s1);

             glFlush();

			 cch++;											// So that next node has next letter
      }


     for(int x=0;x<l;x++)
     {
             p=tree[x][1];
             q=tree[x][2];
             if(p==0||q==0) continue;

             x1=a[p];
             y1=b[p];
             x2=a[q];
             y2=b[q];

             if(p<q)
             {
                glColor3f(0.0,0.5,0.0);
                glBegin(GL_LINES);
                                  glVertex2i(x1,y1+250);
                                  glVertex2i(x2,y2+250);
                glEnd();
                int i5=sprintf(s,"%d",cost1[p][q]);					// Prints the weight onto the Edge

                s1=s;

                drawstring((x1+x2)/2,(y1+y2+500)/2,s1);


             }

             else
        	 {
                glColor3f(1.0,0.5,0.0);
                glBegin(GL_LINES);
                                  glVertex2i(x1,y1+250);
                                  glVertex2i(x2,y2+250);
                glEnd();
                int i6=sprintf(s,"%d",cost1[p][q]);					// Prints the weight onto the Edge

                s1=s;

                drawstring((x1+x2)/2,(y1+y2+500)/2,s1);

             }
       }

             glFlush();


}


void mouse(int button, int state , int x , int y) 				// This takes in inputs when the mouse is interacted with... The x & y are the coordinates of wherw the button is clicked
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		drawSquare(x,y);

}

void top_menu(int option)					// This is the right mouse button click options
{
	int x,y;
	switch(option)
	{
      case 1:
           read();							// Reads the nodes and cost matrix
           glutPostRedisplay();
           break;

      case 2:
           drawlineCN();
           glutPostRedisplay();
           break;

      case 3:

			{
                                for(i=1;i<=n;i++)
                                  visited[i]=0;

                                printf("Enter the source vertex:");
			        scanf("%d",&src);
			        visited[src]=1;

				glClear(GL_COLOR_BUFFER_BIT);					// Clears screen
				initialDraw();
				int cch=1;
				for(int r=1;r<=n;r++)
				{
					x=a[r];
					y=b[r];

					glPointSize(35);

					if(r==src)
						glColor3f(0.7f, 0.4f, 0.0f);
					else
						glColor3f(0.5f, 0.5f, 0.8f);

					glBegin(GL_POINTS);
						glVertex2f(x,y);
					glEnd();


// THE REASON WE RE draw even the inputs is coz we do clear color each iteration... For the Prims part, we wont need this section at all
					glColor3f(0.0,1.0,0.0);
					int i6=sprintf(s,"%d",cch);
					s1=s;
					drawstring(x-5,y-5,s1);
					setFont(GLUT_BITMAP_HELVETICA_18);
					glColor3f(0.0,0.0,0.0);
					drawstring(130,470,"For source");
					glFlush();

					cch++;
				}

				drawlineCN();
				int i6=sprintf(s,"%d",src);														// This line is the OP line for 1,2,3,....
				s1=s;
				setFont(GLUT_BITMAP_HELVETICA_18);
				glColor3f(0.0,0.0,0.0);
				drawstring(225,470,s1);
				glutPostRedisplay();
				shortestpath(src);

			}
				break;

          case 4:
               exit(0);
   	 }
}


void init (void)
{
		glClearColor (1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport( 0,0, 500, 500 );
		glMatrixMode( GL_PROJECTION );
		glOrtho( 0.0, 500.0, 0.0, 500.0, 1.0, -1.0 );
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glFlush();
}
void myInit1()
{
	  glClearColor(0.0,0.0,0.0,0.0);
	  glColor3f(0.0f,0.0f,0.0f);
	  glPointSize(5.0);
	  gluOrtho2D(0.0,500.0,0.0,500.0);
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  setFont(GLUT_BITMAP_HELVETICA_18);
}


void display1(void)
{
	  glClear(GL_COLOR_BUFFER_BIT);
	  title();

}
int main (int argc,char** argv)
{
	   glutInit(&argc,argv);


	   glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	   glutInitWindowPosition(0,0);						// x,y where 0,0 is top left corner and y increases downward
	   glutInitWindowSize(500,500);						// Hz x Vert
	   glutCreateWindow("CG Mini Project");
	   glutDisplayFunc(display1);						// displays the contents on Title Sheet
	   myInit1();

	   glutInitDisplayMode( GLUT_SINGLE|GLUT_RGB );
	   glutInitWindowPosition(550,0);							// 0,0 is the origion which is the top left most corner of the monitor screen- From there the size of the window is drawn
	   glutInitWindowSize(500,500);								// Breadth(Horizontal) x Length(Vertical) of the window- Only works for 500x500
	   glutCreateWindow("My Window");
	   glutDisplayFunc(display);
	   glutMouseFunc(mouse);

	   glutCreateMenu(top_menu);								// This creates the options menu to open once RMB is clicked
		   glutAddMenuEntry("Read Cost Matrix",1);
		   glutAddMenuEntry("Display Weighted Graph",2);
		   glutAddMenuEntry("Display Minimum Spanning tree",3);
		   glutAddMenuEntry("Exit",4);
		   glutAttachMenu(GLUT_RIGHT_BUTTON);

	   printf("\nGO TO MY WINDOW AND CLICK RIGHT BUTTON FOR NEXT OPTION\n");		// Displayed in terminal
	   init();

	   glutMainLoop();
}
