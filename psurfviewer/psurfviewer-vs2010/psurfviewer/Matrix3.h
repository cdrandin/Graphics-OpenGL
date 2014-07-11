//#include <iostream>
//#include <cmath>
//#include <gl/glut.h>

#ifndef MATRIX3_H
#define MATRIX3_H

#include "Vector3.h"

#ifndef MSGFX_FP
#define MSGFX_FP

#define FP_EPSILON 1e-9
#define ALMOST_ZERO FP_EPSILON

#define FP_EQUAL(a, b, delta) ( ((a) == (b)) || \
                                ( (a)-(delta) < (b) && \
                                  (a)+(delta) > (b)) )

#define FP_LT(a, b, delta)  (fabs((a) - (b)) < (delta))

#define FP_GT(a, b, delta)  (fabs((a) - (b)) > (delta))

#define IOS_FP_PRECISION 5
#endif

/*
* OPENGL IS COLUMN MAJOR
* C IS ROW MAJOR
*
* This class is row major
*/

class Matrix3
{
	GLfloat _data[9];

public:
	GLfloat getData(int i )
	{
		return _data[i];
	}

	void putData( int i , GLfloat j)
	{
		_data[i]=j;
	}
	__declspec(property(get=getData, put=putData)) GLfloat data[9];

	Matrix3                            ( void );
	Matrix3                            ( const Matrix3& );
	Matrix3                            ( GLfloat, GLfloat, GLfloat,
										 GLfloat, GLfloat, GLfloat,
										 GLfloat, GLfloat, GLfloat );
	Matrix3                            ( const Vector3&,
										 const Vector3&,
										 const Vector3& );
	explicit Matrix3                   ( GLfloat* );
	~Matrix3                           ( void );

	// Set equal to
	Matrix3& operator=                 ( const Matrix3& );
	Matrix3& operator=                 ( const GLfloat* );

	bool operator==                    ( const Matrix3& ) const;
	bool operator!=                    ( const Matrix3& ) const;

	/*    ADDITION    */
	Matrix3 operator+                  ( const Matrix3& ) const;
	Matrix3& operator+=                ( const Matrix3& );
	Matrix3 operator+                  ( const GLfloat& ) const;
	Matrix3& operator+=                ( const GLfloat& );

	/*    SUBTRACTION    */
	Matrix3 operator-                  ( const Matrix3& ) const;
	Matrix3& operator-=                ( const Matrix3& );
	Matrix3 operator-                  ( const GLfloat& )const;
	Matrix3& operator-=                ( const GLfloat& );

	/*    NEGATE    */
	Matrix3& operator-                 ();

	/*    MULTIPLICATION    */
	Matrix3 operator*                  ( const Matrix3& ) const;
	Matrix3& operator*=                ( const Matrix3& );
	Matrix3 operator*                  ( const GLfloat& ) const;
	Matrix3& operator*=                ( const GLfloat& );
	Vector3 operator *                 ( const Vector3 & );

	/*    DIVISION A/B = A * (1/B) = A * Inverse(B)    */
	Matrix3 operator/                  ( const Matrix3& ) const;
	Matrix3& operator/=                ( const Matrix3& );
	Matrix3 operator/                  ( const GLfloat& ) const;
	Matrix3& operator/=                ( const GLfloat& );

	Vector3 operator[]                 ( const size_t& ) const;
	// Get
	const GLfloat operator ()          ( const size_t&, const size_t& ) const;
	// Set
	GLfloat& operator ()               ( const size_t&, const size_t& );

	/*    MATRIX PROPERTIES    */
	Matrix3 Transpose                  ();
	Matrix3 Adjoint                    ();
	Matrix3 Inverse                    ();
	void Identity                      ();
	// If determinant is < 0 it is a mirror object
	GLfloat Determinant                ();

	//Vector3 Column                   ( const size_t& columnIndex );
	//Vector3 Row                      ( const size_t& rowIndex );

	void Display                       ();
};

void CopyMatrixToArray                 ( Matrix3&, GLfloat [9] );
void Swap                              ( GLfloat&, GLfloat& );
#endif