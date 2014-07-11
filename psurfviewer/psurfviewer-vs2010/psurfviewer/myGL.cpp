#include "myGL.h"
#include <stack>

/* Do not edit these variables. */
bool myMatrixModeOn;
bool myTranslateOn;
bool myRotateOn;
bool myScaleOn;
bool myLookAtOn;
bool myFrustumOn;
bool myPerspectiveOn;
bool myOrthoOn;
std::stack<Matrix4>* myProjectionStack;
std::stack<Matrix4>* myModelingStack; 

int _myMatrixMode;


float* GetCurrentMatrixf ( )
{
	if(_myMatrixMode == GL_MODELVIEW)
	{
		// your code here
		return myModelingStack->top().ReturnArrayGL();
	}
	else if(_myMatrixMode == GL_PROJECTION)
	{
		// your code here
		return myProjectionStack->top().ReturnArrayGL();
	}
}

void print( GLfloat* v )
{
	std::cout<<std::endl;

	for(int i=0;i<16;++i)
	{
		std::cout<<*(v+i)<<" ";
	}
	std::cout<<std::endl;

}

void popPrint ()
{
	Matrix4 top = myModelingStack->top();
	top.DisplayGL();
	std::cout<<std::endl;
	print(top.ReturnArrayGL());
	std::cout<<std::endl;
}

void myMultMatrix ( Matrix4 myMatrix )
{
	// Get top of current stack, multiply by incoming matrix, 
	//   then push product back
	if(_myMatrixMode == GL_MODELVIEW)
	{
		// your code here
		myModelingStack->top() *= myMatrix;
	}
	else if(_myMatrixMode == GL_PROJECTION)
	{
		// your code here
		myProjectionStack->top() *= myMatrix;
	}
}

/* To toggle something on or off, change from false to true. */
void myGLInit( ){
  myMatrixModeOn  = true;
  myTranslateOn   = true;
  myRotateOn      = true;
  myScaleOn       = true;
  myLookAtOn      = true;
  myFrustumOn     = false;
  myPerspectiveOn = true;
  myOrthoOn       = true;

  if( myMatrixModeOn )
  {
	myProjectionStack = new std::stack<Matrix4>();
	myModelingStack   = new std::stack<Matrix4>();

    glGetIntegerv(GL_MATRIX_MODE, &_myMatrixMode);
  }	
}

void myMatrixMode( GLenum mode )
{
  if( myMatrixModeOn )
  {
    _myMatrixMode = mode;
	glMatrixMode(mode);
  }
  else
  {
    glMatrixMode(mode);
	toggleMyMatrixMode();
  }
}

void myPushMatrix( )
{
  if( myMatrixModeOn )
  {
	// pushes the current matrix stack down by one, 
	// duplicating the current matrix.
	if(_myMatrixMode == GL_MODELVIEW)
	{
		// your code here
		myModelingStack->push(myModelingStack->top());
	}
	else if(_myMatrixMode == GL_PROJECTION)
	{
		// your code here
		myProjectionStack->push(myProjectionStack->top());
	}
	else
	{
		glPushMatrix( );
	}
  }
}

void myPopMatrix( )
{
  if( myMatrixModeOn )
  {
    if(_myMatrixMode == GL_MODELVIEW)
	{
      // your code here
	  myModelingStack->pop();
    }
	else if(_myMatrixMode == GL_PROJECTION)
	{
      // your code here
	  myProjectionStack->pop();
    }
  }
  else
  {
    glPopMatrix( );
  }
}

void myLoadIdentity( )
{
  if( myMatrixModeOn )
  {
	glLoadIdentity();
	Matrix4 id;
	id.Identity();

    if(_myMatrixMode == GL_MODELVIEW)
	{
      // your code here
	  myModelingStack->push(id);
    }
	else if(_myMatrixMode == GL_PROJECTION)
	{
      // your code here
	  myProjectionStack->push(id);
    }
  }
  else
  {
    glLoadIdentity( );
  }
}

void myTranslatef( float x, float y, float z )
{
  if( myTranslateOn )
  {
	  // your code here
	  Matrix4 translate = Translate(x,y,z);

	  //glMultMatrixf(translate.ReturnArrayGL());
	  myMultMatrix(translate);
  }
  else
  {
    glTranslatef( x, y, z );
	toggleMyTranslate();
  }
}

void myRotatef( float angle, float x, float y, float z){
  if( myRotateOn )
  {
    // your code here
	  Matrix4 rotation = Rotate(angle,x,y,z);

	  //glMultMatrixf(rotation.ReturnArrayGL());
	  myMultMatrix(rotation);
  }
  else
  {
    glRotatef(angle, x, y, z);
	toggleMyRotate();
  }
}

void myScalef(float x, float y, float z ){
  if(myScaleOn)
  {
	Matrix4 scale = UniformScale(x);

	//glMultMatrixf(scale.ReturnArrayGL());
	myMultMatrix(scale);
  }
  else
  {
    glScalef(x, y, z);
	toggleMyScale();
  }
}

//gluLookAt creates a viewing matrix derived from an eye point, a reference point indicating the center of the scene, and an UP vector.
//
//The matrix maps the reference point to the negative z axis and the eye point to the origin. When a typical projection matrix is used, 
//the center of the scene therefore maps to the center of the viewport. Similarly, the direction described by the UP vector projected 
//onto the viewing plane is mapped to the positive y axis so that it points upward in the viewport. The UP vector must not be parallel 
//to the line of sight from the eye point to the reference point.
void myLookAt( double eyeX, double eyeY, double eyeZ, 
	           double centerX, double centerY, double centerZ, 
			   double upX, double upY, double upZ)
{
  if( myLookAtOn )
  {
    // your code here
	  Vector3 F( static_cast<float>(centerX) - static_cast<float>(eyeX),
		         static_cast<float>(centerY) - static_cast<float>(eyeY), 
				 static_cast<float>(centerZ) - static_cast<float>(eyeZ) );

	  Vector3 up( static_cast<float>(upX),
				  static_cast<float>(upY),
				  static_cast<float>(upZ) );

	  F.Normalize();
	  up.Normalize();

	  Vector3 s = CrossProduct(F,up);
	  Vector3 u = CrossProduct(s,F);

	  GLfloat myLookAt[16] = { s[X] , s[Y], s[Y], 0,
						       u[X] , u[Y], u[Z], 0,
						      -F[X] ,-F[Y],-F[Z], 0,
						         0  ,   0 ,   0 , 1 };

	  Matrix4 m(myLookAt);
	  //glMultMatrixf(m.ReturnArrayGL());
	  myMultMatrix(m);

	  myTranslatef(static_cast<float>(-eyeX), static_cast<float>(-eyeY), static_cast<float>(-eyeZ));
  }
  else
  {
    gluLookAt( eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	toggleMyLookAt();
  }
}

// Typically, the matrix mode is GL_PROJECTION
void myFrustum(double left, double right, double bottom, double top, double zNear, double zFar){
  if( myFrustumOn )
  {
    // your code here
	  float A, B, C, D;
	  A = static_cast<float>((right + left)/(right - left));
	  B = static_cast<float>((top + bottom)/(top - bottom));
	  C = static_cast<float>((-zFar + zNear)/(zFar - zNear));
	  D = static_cast<float>((-2*zFar *zNear)/(zFar - zNear));

	  
	  GLfloat matrix[16] = { (2*zNear)/(right-left), 0, A, 0,
					         0, (2*zNear)/(top-bottom), B, 0,
					                              0, 0, C, D,
												  0, 0, -1, 0 };
					   
	  Matrix4 frustum(matrix);
	  //glMultMatrixf(frustum.ReturnArrayGL());
	  myMultMatrix(frustum);
  }
  else
  {
    glFrustum(left, right, bottom, top, zNear, zFar);
  }
}

void myPerspective(double fovy, double aspect, double zNear, double zFar){
  if( myPerspectiveOn )
  {
    // your code here
	double f = 1/tan(DEG2RAD(fovy/2.0));

	GLfloat matrix[16] = {f/aspect, 0.0f, 0.0f, 0.0f,
						  0.0f, f, 0.0f, 0.0f,
						  0.0f, 0.0f, (zFar+zNear)/(zNear-zFar), (2*zFar*zNear)/(zNear-zFar),
						  0.0f, 0.0f, -1.0f, 0.0f };

	Matrix4 perspective( matrix ); 
	//glMultMatrixf(perspective.ReturnArrayGL());
	myMultMatrix(perspective);
  }
  else
  {
    gluPerspective(fovy, aspect, zNear, zFar);
	toggleMyPerspective();
  }
}

// Typically, the matrix mode is GL_PROJECTION
void myOrtho(double left, double right, double bottom, double top, double zNear, double zFar ){
  if( myOrthoOn )
  {
    // your code here
	  float t[3];
	  t[X] = (-right + left)/(right - left);
	  t[Y] = (-top + bottom)/(top - bottom);
	  t[Z] = (-zFar + zNear)/(zFar - zNear);

	  GLfloat matrix[16] = {  (2.0/(right-left)), 0, 0, t[X],
					          0, (2.0/(top-bottom)), 0, t[Y],
					          0, 0, (-2.0/(zFar-zNear)), t[Z],
							  0, 0, 0, 1 };
	  Matrix4 ortho(matrix);

	  ortho.DisplayGL();

	  //glMultMatrixf(ortho.ReturnArrayGL());
	  myMultMatrix(ortho);
  }
  else
  {
    glOrtho(left, right, bottom, top, zNear, zFar);
	toggleMyOrtho();
  }
}

/*    TOGGLES    */
void toggleMyMatrixMode( ){
  printf("MyMatrixMode not implemented\n");
}

void toggleMyTranslate( ){
  printf("MyTranslate not implemented\n");
}

void toggleMyRotate( ){
  printf("MyRotate not implemented\n");
}

void toggleMyScale( ){
  printf("MyScale not implemented\n");
}

void toggleMyLookAt( ){
  printf("MyLookAt not implemented\n");
}

void toggleMyFrustum( ){
  printf("MyFrustum not implemented\n");
}

void toggleMyPerspective( ){
  printf("MyPerspective not implemented\n");
}

void toggleMyOrtho( ){
  printf("MyOrtho not implemented\n");
}
/*    END TOGGLES    */