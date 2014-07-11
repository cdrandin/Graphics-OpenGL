#include "Vector3.h"
#include "Matrix3.h"

#ifndef MATRIX4_H
#define MATRIX4_H

class Matrix4
{
private:
	GLfloat _data[16];
	
	Matrix3 FindCofactorMatrix3x3( const size_t& );
public:
	GLfloat getData( int i )
	{
		return _data[i];
	}

	void putData( int i , GLfloat j)
	{
		_data[i]=j;
	}
	__declspec(property(get=getData, put=putData)) GLfloat data[16];

	Matrix4(void);
	Matrix4( GLfloat,GLfloat,GLfloat,GLfloat,
			 GLfloat,GLfloat,GLfloat,GLfloat,
			 GLfloat,GLfloat,GLfloat,GLfloat,
			 GLfloat,GLfloat,GLfloat,GLfloat );

	Matrix4( GLfloat* );
	Matrix4( GLfloat [4][4] );
	Matrix4( Matrix3 );

	~Matrix4(void) {};

	bool     operator==( const Matrix4& );
	Matrix4  operator= ( const Matrix4& );

/*    ADDITION    */
	Matrix4  operator+ ( const Matrix4& );
	void     operator+=( const Matrix4& );
	Matrix4  operator+ ( const GLfloat& );
	void     operator+=( const GLfloat&  );

	/*    SUBTRACTION    */
	Matrix4  operator- ( const Matrix4& );
	void     operator-=( const Matrix4& );
	Matrix4  operator- ( const GLfloat&  );
	void     operator-=( const GLfloat&  );

	/*    NEGATE    */
	Matrix4  operator- ();

	/*    MULTIPLICATION    */
	Matrix4  operator* ( const Matrix4& );
	void     operator*=( const Matrix4& );
	Matrix4  operator* ( const GLfloat&  );
	void     operator*=( const GLfloat&  );

	/*    DIVISION A/B = A * (1/B) = A * Inverse(B)    */
	Matrix4 operator/ ( const Matrix4& );

	inline GLfloat  operator[]( const int x ) const {	return _data[x];   }

	// Get
	const GLfloat operator ()          ( const size_t&, const size_t& ) const;
	// Set
	GLfloat& operator ()               ( const size_t&, const size_t& );

	/*    MATRIX PROPERTIES    */
	Matrix4 Transpose ();
	Matrix4 Adjoint   ();
	Matrix4 Inverse   ();
	void Identity  ();
	// If determinant is < 0 it is a mirror object
	GLfloat Determinant();

	//GLfloat operator()( const size_t& col, const size_t& row );

	void Display ();
	void DisplayGL ();
	void Swap ( GLfloat&, GLfloat& );
	GLfloat* ReturnArray ();
	GLfloat* ReturnArrayGL ();
};

Matrix4 Rotate ( const GLfloat angleInDegrees, const GLfloat x, const GLfloat y, const GLfloat z );
Matrix4 Translate                      ( GLfloat, GLfloat, GLfloat );
Matrix4 UniformScale                   ( GLfloat );
Matrix4 Scale                          ( GLfloat, GLfloat, GLfloat );

#endif
