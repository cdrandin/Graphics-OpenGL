
#ifdef __APPLE__
/* Apple's weird location of their OpenGL & GLUT implementation */
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>
#endif

#include <cstdlib>
#include <cstdio>
#include <string>

/* Thanks to Apple's Sample Code... */
#include "SurfaceGeometry.h"

#include "GLSLShader.h"
#include "SGFaceList.h"
#include "getopt.h"

#include "myGL.h"

SGFaceList *gModel[kSurfaces];
unsigned int gCurrentModel;
unsigned int gGLSLOff;

float gTranslation[3], gRotationAngle[3], gScaleFactor[3];
float scaleValue = 0.01f;
float rotationValue = 5;

bool perspectiveOn = true;

int gMouseButtonState;
int gMouseButton;

int WIDTH, HEIGHT;

const char * program_usage = 
"Press the follow buttons to do a functionality\n\
1: glsl active/deactive states\n\
p:perspective/ortho views (default perspective)\n\
+: increment uniform scale\n\
-: decrement uniform scale\n\
(space): switch between models\n\
(esc): terminate program\n";

struct LookAt
{
	Vector3 position;
	Vector3 gaze;
	Vector3 up;

	LookAt( GLfloat eyeX,
		 	GLfloat eyeY,
		    GLfloat eyeZ,
		    GLfloat centerX,
		    GLfloat centerY,
		    GLfloat centerZ,
		    GLfloat upX,
		    GLfloat upY,
		    GLfloat upZ)
	{
		position[X] = eyeX;
		position[Y] = eyeY;
		position[Z] = eyeZ;

		gaze[X]     = centerX;
		gaze[Y]     = centerY;
		gaze[Z]     = centerZ;

		up[X]       = upX;
		up[Y]       = upY;
		up[Z]       = upZ;
	}
	~LookAt()
	{};

};

LookAt camera ( 0.0f, 0.0f, -15.0f,
	            0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f );

LookAt light ( 1.25f, 1.25f, 0.5f,
	           0.0f, 0.0f, 0.0f,
			   0.0f, 0.0f, 0.0f );

float* mouseDownLoc = new float[2];

GLSLProgram *gRender;

void printVector(float v[3]){
  printf( "(%g, %g, %g)\n", v[0], v[1], v[2] );
}

void usage( std::string msg ){
  std::cerr << msg << std::endl;
  std::cerr << "usage: psurfviewer [-v -h]" << std::endl;
  std::cerr << "                 or" << std::endl;
  std::cerr << "       psurfviewer [--verbose --help]" << std::endl;
}

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init( void ) 
{
	Vector3 v(1.0f,1.0f,1.0f);
	v.Display();

	// prompt instructions
	std::cout << program_usage << std::endl;

   glClearColor( 0.0, 0.0, 0.0, 0.0 );
   glDisable( GL_LIGHTING );
   glEnable( GL_DEPTH_TEST );
   glFrontFace( GL_CCW );

   for( int i = 0; i < kSurfaces; i++ ){
     gModel[i] = BuildGeometry( i, 4, 8, 3 );
	 //gModel[i] = BuildGeometry( i, 4, 64, 24 );
   }
   gCurrentModel = 0;
   for( int i = 0; i < 3; i++ ){
     gRotationAngle[i] = 0.0f;
     gTranslation[i] = 0.0f;
     gScaleFactor[i] = 1.0f;
   }

   #ifdef WIN32
      glewInit( );
   #endif

   /*
   // simple
   //const char* vs_file = "simple.vs";
   //const char* fs_file = "simple.fs";
   // Simple Shader (like asgt. 2)

   const char* vs_file = "simpleShader_vs.txt";
   const char* fs_file = "simpleShader_fs.txt";
   
   VertexShader vertexShader(vs_file);
   FragmentShader fragmentShader(fs_file);
   gRender = new GLSLProgram( );
   assert(gRender->attach(vertexShader));
   assert(gRender->attach(fragmentShader));
   gRender->link( );
   gGLSLOff = 1;
   */
}

void SimpleShader ( Vector3& L, Vector3& N, Vector3& V, Vector3& color )
{
	Vector3 R(((2*N)*(N.DotProduct(L))) - L);

	float cosTheta = R.DotProduct(V);
	Vector3 W(1.0f,1.0f,1.0f);
	Vector3 P(1.0f,2.0f,20.0f);
	
	float red   = W[X] * pow( (cosTheta + 1)/2.0f, P[X] );
	float green = W[Y] * pow( (cosTheta + 1)/2.0f, P[Y] );
	float blue  = W[Z] * pow( (cosTheta + 1)/2.0f, P[Z] );

	color = Vector3(red,green,blue);
}

void drawSurface( SGFaceList *f ){
  int i = 0;
  int j = 0;
  int index;
  if( f->surface == kCube ){
    glEnable( GL_POLYGON_OFFSET_FILL );
    glBegin( GL_TRIANGLES );
    for( i = 0; i < f->fc; i++ ){
      for( j = 0; j < 3; j++ ){
        glColor3fv( f->colors[ f->faces[i][j] ] );
        glVertex3fv( f->vertices[ f->faces[i][j] ] );
      }
    }
    glEnd( );
    glColor3f( 0.0, 0.0, 0.0 );
    for( i = 0; i < (f->fc); i++ ){
      glBegin( GL_LINE_LOOP );
      for( j = 0; j < 3; j++ ){
        glVertex3fv( f->vertices[ f->faces[i][j] ] );
      }
      glEnd( );
    }
    glDisable( GL_POLYGON_OFFSET_LINE );
  }else{
    for( i = 0; i < (f->maxI); i++ ){
      glBegin( GL_TRIANGLE_STRIP );
      for( j = 0; j <= (f->maxJ); j++ ){
        index = (i % (f->maxI)) * (f->maxJ) + (j % (f->maxJ));

		//*
		// 
		// Shading stuff
		// Get vector between camera position and object for each vertex
		Vector3 V( static_cast<GLfloat>( camera.position[X] - f->vertices[index][X] ),
			       static_cast<GLfloat>( camera.position[Y] - f->vertices[index][Y] ),
				   static_cast<GLfloat>( camera.position[Z] - f->vertices[index][Z] ) );
		V.Normalize();

		// Get vector between light position and object for each vertex
		Vector3 L( static_cast<GLfloat>( light.position[X] - f->vertices[index][X] ),
			       static_cast<GLfloat>( light.position[Y] - f->vertices[index][Y] ),
				   static_cast<GLfloat>( light.position[Z] - f->vertices[index][Z] ) );
		L.Normalize();

		// Get vector normal for each vertex
		Vector3 N( f->v_normals[index][X], f->v_normals[index][Y], f->v_normals[index][Z] ); 
		N.Normalize();

		Vector3 color;

		SimpleShader(L, N, V, color);

		glColor3f( color[X], color[Y], color[Z] );

		//
		// End of shading stuff
		//*/

        //glColor3fv( f->colors[index] ); // comment out for shading
        glNormal3fv( f->v_normals[index] );
        glVertex3fv( f->vertices[index] );
        
        index = ((i + 1) % f->maxI) * f->maxJ + (j % f->maxJ);

		//*
		//
		// Do the shading stuff
		V = Vector3( static_cast<GLfloat>( camera.position[X] - f->vertices[index][X] ),
			         static_cast<GLfloat>( camera.position[Y] - f->vertices[index][Y] ),
				     static_cast<GLfloat>( camera.position[Z] - f->vertices[index][Z] ) );
		V.Normalize();

		L = Vector3( static_cast<GLfloat>( light.position[X] - f->vertices[index][X] ),
			         static_cast<GLfloat>( light.position[Y] - f->vertices[index][Y] ),
				     static_cast<GLfloat>( light.position[Z] - f->vertices[index][Z] ) );
		L.Normalize();

		N = Vector3( f->v_normals[index][X], f->v_normals[index][Y], f->v_normals[index][Z] ); 
		N.Normalize();

		SimpleShader(L, N, V, color);

		glColor3f( color[X], color[Y], color[Z] );

		//
		// End of shading stuff
		//*/

        //glColor3fv( f->colors[index] ); // comment out for shading
        glNormal3fv( f->v_normals[index] );
        glVertex3fv( f->vertices[index] );
      }
      glEnd( );
    }
  }
}

void display( void ){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //glClear (/*GL_COLOR_BUFFER_BIT |*/ GL_DEPTH_BUFFER_BIT);
   //glClear (GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
   myLoadIdentity( );
   myLookAt( camera.position[X], camera.position[Y], camera.position[Z], //	GLdouble  	eyeX   , GLdouble  	eyeY   , GLdouble  	eyeZ,
			  camera.gaze[X],      camera.gaze[Y], camera.gaze[Z],       //	GLdouble  	centerX, GLdouble  	centerY, GLdouble  	centerZ,
			  camera.up[X],          camera.up[Y], camera.up[Z] );    //	GLdouble  	upX    , GLdouble  	up    Y, GLdouble  	upZ

   myRotatef( gRotationAngle[X], 1.0, 0.0, 0.0 );
   myRotatef( gRotationAngle[Y], 0.0, 1.0, 0.0 );
   myRotatef( gRotationAngle[Z], 0.0, 0.0, 1.0 );
   myScalef ( gScaleFactor[X], gScaleFactor[Y], gScaleFactor[Z] );
   myTranslatef( gTranslation[X], gTranslation[Y], gTranslation[Z] );
   //glutSolidTorus (0.5, 1.0, 32, 60);

   glMultMatrixf(GetCurrentMatrixf());

   drawSurface( gModel[gCurrentModel] ); //draw
   glFlush ();
   glutSwapBuffers();
}

void reshape( int w, int h ){
	WIDTH = w;
	HEIGHT = h;

   glViewport( 0, 0, (GLsizei) WIDTH, (GLsizei) HEIGHT );
   myMatrixMode( GL_PROJECTION );
   myLoadIdentity( );

   myPerspective( 40.0, (GLfloat) WIDTH/(GLfloat) HEIGHT, 1.0, 20.0 );

   glMultMatrixf(GetCurrentMatrixf());

   myMatrixMode( GL_MODELVIEW );
   myLoadIdentity( );
}

void mouse( int button, int state, int x, int y ) 
{
  gMouseButtonState = state;
  gMouseButton      = button;

  if(state == GLUT_DOWN)
  {
	  mouseDownLoc[X] = x;
	  mouseDownLoc[Y] = y;
  }

  if( glutGetModifiers( ) == GLUT_ACTIVE_SHIFT ){
	   switch (button) {
       case GLUT_LEFT_BUTTON:
       case GLUT_MIDDLE_BUTTON:
         // Fall through
       case GLUT_RIGHT_BUTTON:
		 break;
       default:
         // You have more than three buttons on your mouse?
         break;
    }
	}else if( glutGetModifiers( ) == GLUT_ACTIVE_CTRL ){
     switch (button) {
       case GLUT_LEFT_BUTTON:
         break;
       case GLUT_MIDDLE_BUTTON:
         // Fall through
       case GLUT_RIGHT_BUTTON:
         break;
       default:
         // You have more than three buttons on your mouse?
         break;
    }
  }else{
    switch (button) {
      case GLUT_LEFT_BUTTON:

      case GLUT_MIDDLE_BUTTON:
        // Fall through
      case GLUT_RIGHT_BUTTON:
      default:
        // You have more than three buttons on your mouse?
        break;
   }
 }
 glutPostRedisplay( );
}

void mouseMotion(int x, int y)
{
	static int lastX = mouseDownLoc[X], lastY = mouseDownLoc[Y];

	// Offset
	float d_x = (x - lastX)/100.0f;
	float d_y = (y - lastY)/100.0f;

	lastX = x; 
	lastY = y;

	// Button is down and left button clicked
	if( gMouseButtonState == GLUT_DOWN && gMouseButton == GLUT_LEFT_BUTTON )
	{
		// If shift pressed move along XZ plane
		if( glutGetModifiers() == GLUT_ACTIVE_SHIFT )
		{
			gTranslation[X] -= d_x;
			gTranslation[Z] -= d_y;
		}
		// If ctrl pressed translate the camera towards/away from the origin
		else if( glutGetModifiers() == GLUT_ACTIVE_CTRL )
		{
			camera.position[X] += d_x;
			camera.position[Z] += d_y;
		}
		// Else move along XY plane
		else
		{
			gTranslation[X] -= d_x;
			gTranslation[Y] -= d_y;
		}
	}

  glutPostRedisplay( );
}

// Options: Rotation
void special( int key, int px, int py ){
	if( glutGetModifiers( ) == GLUT_ACTIVE_SHIFT ){
		switch( key ){
			// Rotate about the Z axis
		case GLUT_KEY_UP:
			gRotationAngle[Z] += rotationValue;
			break;
		case GLUT_KEY_DOWN:
			gRotationAngle[Z] -= rotationValue;
			break;
	  }
	}else{
	  switch( key ){
		  // Rotate about the X axis
		case GLUT_KEY_UP:
			gRotationAngle[X] += rotationValue;
			break;
		case GLUT_KEY_DOWN:
			gRotationAngle[X] -= rotationValue;
			break;
		// Rotate about the Y axis
		case GLUT_KEY_LEFT:
			gRotationAngle[Y] -= rotationValue;
			break;
		case GLUT_KEY_RIGHT:
			gRotationAngle[Y] += rotationValue;
			break;
	  }
	}
  glutPostRedisplay( );
}

// Options: uniform scale, toggle between models, camera zoom
void keyboard( unsigned char key, int x, int y ){
  switch( key ){
    case 27:
      // The esc key
      exit( 0 );
    break;
	case '1':
		gGLSLOff = !gGLSLOff;
		if( gGLSLOff ){
		  gRender->deactivate( );
		  puts("GLSL deactivated");
		}else{
		  puts("GLSL actived");
		  gRender->activate( );
		}
		break;
	// Change the views when you press P, between ortho an dperspective
	case 'p':
		perspectiveOn = !perspectiveOn;

		myMatrixMode( GL_PROJECTION );
		myLoadIdentity( );

		if(perspectiveOn)
		{
			myPerspective( 40.0, (GLfloat) WIDTH/(GLfloat) HEIGHT, 1.0, 20.0 );
		}
		else
		{
			glOrtho(-15, 15, -15, 15, -10, 30);
		}

		glMultMatrixf(GetCurrentMatrixf());

		myMatrixMode( GL_MODELVIEW );
		myLoadIdentity( );

		break;
    case '+':
    // uniform scale up
		gScaleFactor[X] += scaleValue;
		gScaleFactor[Y] += scaleValue;
		gScaleFactor[Z] += scaleValue;
    break;
    case '-':
    // uniform scale down
		gScaleFactor[X] -= scaleValue;
		gScaleFactor[Y] -= scaleValue;
		gScaleFactor[Z] -= scaleValue;
    break;
    case ' ':
		// toggle between different models
        gCurrentModel = (gCurrentModel + 1) % kSurfaces;
    break;
	case '[':
		break;
	case ']':
		break;
    default:
      std::cerr << "Unknown key press \'" << key << "\'" << std::endl;
    break;
  }
  glutPostRedisplay( );
}

int main(int argc, char** argv){
  int ch;
  struct option longopts[] = {
    { "verbose", required_argument, NULL, 'v' },
    { "help", required_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 }
  };
  
  // Let GLUT process the command line first
  glutInit(&argc, argv);
  
  // myGL init
  myGLInit();

  // Let's figure out what the command line options are
  while( (ch = getopt_long(argc, argv, "vh", longopts, NULL)) != -1 ){
    switch( ch ){
      case 'v':
        // Turn on debugging
      break;
      case 'h':
        usage( std::string( "Hope this helps..." ) );
      break;
      default:
        /* do nothing */
        fprintf( stderr, "Ignoring unknown option: %c\n", ch );
      break;
    } 
  }

  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  WIDTH = (int)800;
  HEIGHT = (int)800;
  glutInitWindowSize( WIDTH, HEIGHT ); 
  glutInitWindowPosition( 780, 0 );
  glutCreateWindow( argv[0] );

  // Initialize our OpenGL environment
  init( );

 /*
   * Set up our call back functions to handle events
   */
  // Handle window size changes
  glutReshapeFunc( reshape );
  // Handle keyboard events
  glutKeyboardFunc( keyboard );
  glutSpecialFunc( special );
  // display gets called every time we want to refresh the screen
  glutDisplayFunc( display );
  // handle user input via the mouse
  glutMouseFunc( mouse );
  glutMotionFunc( mouseMotion );

  // The program doesn't return from the next call.
  glutMainLoop( );

  return( 0 );
}
