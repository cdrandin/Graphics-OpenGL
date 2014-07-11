#include "Matrix3.h"

// Utility functions
//
void Swap( GLfloat& t1, GLfloat& t2 )
{
	GLfloat temp = t1;
	t1 = t2;
	t2 = temp;
}

void Matrix3::Identity ()
{
	this->_data[0] = static_cast<GLfloat>(1.0);
	this->_data[1] = static_cast<GLfloat>(0.0);
	this->_data[2] = static_cast<GLfloat>(0.0);
	this->_data[3] = static_cast<GLfloat>(0.0);
	this->_data[4] = static_cast<GLfloat>(1.0);
	this->_data[5] = static_cast<GLfloat>(0.0);
	this->_data[6] = static_cast<GLfloat>(0.0);
	this->_data[7] = static_cast<GLfloat>(0.0);
	this->_data[8] = static_cast<GLfloat>(1.0);
}

void Matrix3::Display ()
{
	for(int i=0;i<9;++i)
	{
		std::cout<<_data[i]<<' ';

		if((i+1)%3==0)
			std::cout<<std::endl;
	}
}
// End of Utility functions
//

// Constructors
//
Matrix3::Matrix3 ()
{
	this->_data[0] = static_cast<GLfloat>(0.0);
	this->_data[1] = static_cast<GLfloat>(0.0);
	this->_data[2] = static_cast<GLfloat>(0.0);
	this->_data[3] = static_cast<GLfloat>(0.0);
	this->_data[4] = static_cast<GLfloat>(0.0);
	this->_data[5] = static_cast<GLfloat>(0.0);
	this->_data[6] = static_cast<GLfloat>(0.0);
	this->_data[7] = static_cast<GLfloat>(0.0);
	this->_data[8] = static_cast<GLfloat>(0.0);
}

Matrix3::Matrix3 ( const Matrix3& myMatrix )
{
	this->_data[0] = myMatrix._data[0];
	this->_data[1] = myMatrix._data[1];
	this->_data[2] = myMatrix._data[2];
	this->_data[3] = myMatrix._data[3];
	this->_data[4] = myMatrix._data[4];
	this->_data[5] = myMatrix._data[5];
	this->_data[6] = myMatrix._data[6];
	this->_data[7] = myMatrix._data[7];
	this->_data[8] = myMatrix._data[8];
}

Matrix3::Matrix3 ( GLfloat x1,GLfloat y1,GLfloat z1,
			      GLfloat x2,GLfloat y2,GLfloat z2,
			      GLfloat x3,GLfloat y3,GLfloat z3 )
{
	this->_data[0] = x1;
	this->_data[1] = y1;
	this->_data[2] = z1;
	this->_data[3] = x2;
	this->_data[4] = y2;
	this->_data[5] = z2;
	this->_data[6] = x3;
	this->_data[7] = y3;
	this->_data[8] = z3;
}

Matrix3::Matrix3 ( const Vector3& v1, const Vector3& v2, const Vector3& v3 )
{
	this->_data[0] = static_cast<GLfloat>(v1.x());
	this->_data[1] = static_cast<GLfloat>(v1.y());
	this->_data[2] = static_cast<GLfloat>(v1.z());
	this->_data[3] = static_cast<GLfloat>(v2.x());
	this->_data[4] = static_cast<GLfloat>(v2.y());
	this->_data[5] = static_cast<GLfloat>(v2.z());
	this->_data[6] = static_cast<GLfloat>(v3.x());
	this->_data[7] = static_cast<GLfloat>(v3.y());
	this->_data[8] = static_cast<GLfloat>(v3.z());
}

Matrix3::Matrix3 ( GLfloat* myMatrix )
{
	this->_data[0] = *(myMatrix+0);
	this->_data[1] = *(myMatrix+1);
	this->_data[2] = *(myMatrix+2);
	this->_data[3] = *(myMatrix+3);
	this->_data[4] = *(myMatrix+4);
	this->_data[5] = *(myMatrix+5);
	this->_data[6] = *(myMatrix+6);
	this->_data[7] = *(myMatrix+7);
	this->_data[8] = *(myMatrix+8);
}

// End of Constructors
//

// Destructor
Matrix3::~Matrix3 (void)
{}

//End Destructor
//

/* 
 * Overloaded operators
 */
// Copy vector to new matrix
// If matrix is the same, return it back
Matrix3& Matrix3::operator= ( const Matrix3 &myMatrix )
{
	if (this == &myMatrix)
		return *this;

	for(int i=0;i<9;++i)
	{
		this->_data[i] = myMatrix._data[i];
	}

	return *this;
}

Matrix3& Matrix3::operator= ( const GLfloat* myValues )
{
	for(int i=0;i<9;++i)
	{
		this->_data[i] = *(myValues+i);
	}
	return *this;
}

// Check if the matrices are equal to each other
bool Matrix3::operator== ( const Matrix3 &myMatrix ) const
{
	for(int i=0;i<9;++i)
		if(this->_data[i] != myMatrix._data[i])
			return false;

	return true;
}

bool Matrix3::operator!= ( const Matrix3& myMatrix ) const
{
	for(int i=0;i<9;++i)
		if(this->_data[i] != myMatrix._data[i])
			return true;

	return false;
}


// Vector addition
Matrix3 Matrix3::operator+ ( const Matrix3& myMatrix ) const
{
	GLfloat temp[9];

	for(int i=0;i<9;++i)
	{
		temp[i] = this->_data[i] + myMatrix._data[i];
	}

	return Matrix3(temp);
}

Matrix3& Matrix3::operator+= ( const Matrix3& myMatrix )
{
	*this = *this + myMatrix;
	return *this;
}

// Value addition
Matrix3 Matrix3::operator+ ( const GLfloat& value ) const
{
	GLfloat temp[9];

	for(int i=0;i<9;++i)
	{
		temp[i] = this->_data[i] + value;
	}

	return Matrix3(temp);
}

Matrix3& Matrix3::operator+= ( const GLfloat& value )
{
	*this = *this + value;
	return *this;
}

// Vector subtraction
Matrix3 Matrix3::operator- ( const Matrix3& myMatrix ) const
{
	GLfloat temp[9];

	for(int i=0;i<9;++i)
	{
		temp[i] = this->_data[i] - myMatrix._data[i];
	}

	return Matrix3(temp);
}

Matrix3& Matrix3::operator-= ( const Matrix3& myMatrix )
{
	*this = *this - myMatrix;
	return *this;
}

// Value subtraction
Matrix3 Matrix3::operator- ( const GLfloat& value ) const
{
	GLfloat temp[9];

	for(int i=0;i<9;++i)
	{
		temp[i] = this->_data[i] - value;
	}

	return Matrix3(temp);
}

Matrix3& Matrix3::operator-= ( const GLfloat& value )
{
	*this = *this - value;
	return *this;
}

// Negate matrix
Matrix3& Matrix3::operator- ()
{
	for(int i=0;i<9;++i)
	{
		this->_data[i] *= -1;
	}

	return *this;
}

// Matrix multiplication
Matrix3 Matrix3::operator* ( const Matrix3& myMatrix ) const
{
	Matrix3 temp;

	temp._data[0] = this->_data[0] * myMatrix._data[0] + this->_data[1] * myMatrix._data[3] + this->_data[2] * myMatrix._data[6];
	temp._data[1] = this->_data[0] * myMatrix._data[1] + this->_data[1] * myMatrix._data[4] + this->_data[2] * myMatrix._data[7];
	temp._data[2] = this->_data[0] * myMatrix._data[2] + this->_data[1] * myMatrix._data[5] + this->_data[2] * myMatrix._data[8];

	temp._data[3] = this->_data[3] * myMatrix._data[0] + this->_data[4] * myMatrix._data[3] + this->_data[5] * myMatrix._data[6];
	temp._data[4] = this->_data[3] * myMatrix._data[1] + this->_data[4] * myMatrix._data[4] + this->_data[5] * myMatrix._data[7];
	temp._data[5] = this->_data[3] * myMatrix._data[2] + this->_data[4] * myMatrix._data[5] + this->_data[5] * myMatrix._data[8];
	
	temp._data[6] = this->_data[6] * myMatrix._data[0] + this->_data[7] * myMatrix._data[3] + this->_data[8] * myMatrix._data[6];
	temp._data[7] = this->_data[6] * myMatrix._data[1] + this->_data[7] * myMatrix._data[4] + this->_data[8] * myMatrix._data[7];
	temp._data[8] = this->_data[6] * myMatrix._data[2] + this->_data[7] * myMatrix._data[5] + this->_data[8] * myMatrix._data[8];

	return temp;
}

Matrix3& Matrix3::operator*= ( const Matrix3& myMatrix )
{
	*this = *this * myMatrix;
	return *this;
}

// Scalar multiplication
Matrix3 Matrix3::operator* ( const GLfloat& scalar ) const
{
	GLfloat temp[9];

	for(int i=0;i<9;++i)
	{
		temp[i] = this->_data[i] * scalar;
	}

	return Matrix3(temp);
}

Matrix3& Matrix3::operator*= ( const GLfloat& scalar )
{
	*this = *this * scalar;
	return *this;
}

Vector3 Matrix3::operator* ( const Vector3& myVector ) 
{
	GLfloat x,y,z;
	Matrix3 temp = *this;

	x = ( temp[1].x() * myVector.x()) + (temp[1].y() * myVector.y()) + (temp[1].z() * myVector.z() );
	y = ( temp[2].x() * myVector.x()) + (temp[2].y() * myVector.y()) + (temp[2].z() * myVector.z() );
	z = ( temp[3].x() * myVector.x()) + (temp[3].y() * myVector.y()) + (temp[3].z() * myVector.z() );

	return Vector3(x,y,z);
}

// DIVISION A/B = A * (1/B) = A * Inverse(B)
Matrix3 Matrix3::operator/ ( const Matrix3& myMatrix ) const
{
	Matrix3 temp = myMatrix;

	return( *this * temp.Inverse() );
}

Matrix3& Matrix3::operator/= ( const Matrix3& myMatrix ) 
{
	*this = *this / myMatrix;
	return *this;
}

Matrix3 Matrix3::operator/ ( const GLfloat& scalar ) const
{
	GLfloat temp[9];

	for(int i=0;i<9;++i)
	{
		temp[i] = this->_data[i] / scalar;
	}

	return Matrix3(temp);
}

Matrix3& Matrix3::operator/= ( const GLfloat& scalar ) 
{
	*this = *this / scalar;
	return *this;
}

// Row 1 to Row 3 for the 3x3 matrix
Vector3 Matrix3::operator[] ( const size_t& row_n ) const
{
	int elem = 0;

	switch(row_n)
	{
	case 1:
		elem = 0;
		break;
	case 2:
		elem = 3;
		break;
	case 3:
		elem = 6;
		break;
	default:
		std::cerr<<"Row out of bounds.\n";
		return Vector3(-9999,-9999,-9999);
		break;
	}

	return Vector3(this->_data[elem], this->_data[elem+1], this->_data[elem+2]);
}

/*
 * End of overloaded operators
 */

//Design idea. Transpose the real data or return a transpose verision
Matrix3 Matrix3::Transpose ()
{
	GLfloat temp[9];
	
	// copy the matrix into a temp array
	for(int i=0;i<9;++i)
		temp[i] = _data[i];

	// Swap spots for transpose
	Swap(temp[1], temp[3]);
	Swap(temp[2], temp[6]);
	Swap(temp[5], temp[7]);

	return Matrix3(temp);
}

Matrix3 Matrix3::Adjoint ()
{
	/* Find the Adjoint
	 * http://www.mathwords.com/a/adjoint.htm
	 */

	Matrix3 temp;

	// CoFactor(Mirror of minors)
	temp._data[0] = this->_data[4]*this->_data[8] - this->_data[5]*this->_data[7];
	temp._data[1] = this->_data[3]*this->_data[8] - this->_data[5]*this->_data[6];
	temp._data[2] = this->_data[3]*this->_data[7] - this->_data[4]*this->_data[6];

	temp._data[3] = this->_data[1]*this->_data[8] - this->_data[2]*this->_data[7];
	temp._data[4] = this->_data[0]*this->_data[8] - this->_data[2]*this->_data[6];
	temp._data[5] = this->_data[0]*this->_data[7] - this->_data[1]*this->_data[6];

	temp._data[6] = this->_data[1]*this->_data[5] - this->_data[2]*this->_data[4];
	temp._data[7] = this->_data[0]*this->_data[5] - this->_data[2]*this->_data[3];
	temp._data[8] = this->_data[0]*this->_data[4] - this->_data[1]*this->_data[3];

	// Matrix of cofactors
	// + - +
	// - + -
	// + - +
	for(int i=1;i<9;i+=2)
		temp._data[i] *= -1;

	// Finally the adjoint of A is the transpose of the cofactor matrix
	temp = temp.Transpose();

	return temp;
}

Matrix3 Matrix3::Inverse ()
{
	/* How to take the inverse of a matrix
	 * http://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
	 */

	if(this->Determinant() == 0.0)
	{
		std::cerr<<"No inverse for this matrix\n";
		return *this;
	}

	/* Inverse forumla for nxn matrix
	 * http://ncalculators.com/matrix/inverse-matrix.htm
	 */

	return ( this->Adjoint() * (1/this->Determinant()) );
}

GLfloat Matrix3::Determinant ()
{
	/* Finding the determinant
	 * http://www.mathsisfun.com/algebra/matrix-determinant.html
	 */
	return ( this->_data[0] * ((this->_data[4] * this->_data[8]) - (this->_data[5] * this->_data[7])) - 
			 this->_data[1] * ((this->_data[3] * this->_data[8]) - (this->_data[5] * this->_data[6])) +
			 this->_data[2] * ((this->_data[3] * this->_data[7]) - (this->_data[4] * this->_data[6])) );
}


// Read values
// Row and Col are between 1 and 3 inclusive
// 11 12 13
// 21 22 23
// 31 32 33
const GLfloat Matrix3::operator()( const size_t& row, const size_t& col ) const
{
	if( col > 3 || row > 3 || col < 0 || row < 0)
	{
		std::cerr << "Col or Row out of bounds, confine with in 3 deminsions\nValues accepted: 1,2,3 for rows and col\n";
	}

	/*
	 Approach as to how I got the formula to find the element given row and col

	int i = 0;
	switch(col)
	{
	case 1: // 0 1 2
		i += 0;
		break;
	case 2: // 3 4 5
		i += 3;
		break;
	case 3: / 6 7 8
		i += 6;
		break;
	}
	*/

	return _data[((row-1)*3)+col - 1];
}

// Write to values
// Row and Col are between 1 and 3 inclusive
// 11 12 13
// 21 22 23
// 31 32 33
GLfloat& Matrix3::operator ()( const size_t& row, const size_t& col )
{
	if( col > 3 || row > 3 || col < 0 || row < 0)
	{
		std::cerr << "Col or Row out of bounds, confine with in 3 deminsions\nValues accepted: 1,2,3 for rows and col\n";
	}

	/*
	 Approach as to how I got the formula to find the element given row and col

	int i = 0;
	switch(col)
	{
	case 1: // 0 1 2
		i += 0;
		break;
	case 2: // 3 4 5
		i += 3;
		break;
	case 3: / 6 7 8
		i += 6;
		break;
	}
	*/

	return _data[((row-1)*3)+col - 1];
}

void CopyMatrixToArray ( Matrix3& myMatrix, GLfloat a[9] )
{
	for(int i=0;i<9;++i)
		a[i] = myMatrix.getData(i);
}