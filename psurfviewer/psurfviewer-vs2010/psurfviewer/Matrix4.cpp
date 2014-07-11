#include "Matrix4.h"

// Utility functions
//
void Matrix4::Swap( GLfloat& t1, GLfloat& t2 )
{
	GLfloat temp = t1;
	t1 = t2;
	t2 = temp;
}

void Matrix4::Identity ()
{
	this->_data[0] = static_cast<GLfloat>(1.0);
	this->_data[1] = static_cast<GLfloat>(0.0);
	this->_data[2] = static_cast<GLfloat>(0.0);
	this->_data[3] = static_cast<GLfloat>(0.0);
	this->_data[4] = static_cast<GLfloat>(0.0);
	this->_data[5] = static_cast<GLfloat>(1.0);
	this->_data[6] = static_cast<GLfloat>(0.0);
	this->_data[7] = static_cast<GLfloat>(0.0);
	this->_data[8] = static_cast<GLfloat>(0.0);
	this->_data[9] = static_cast<GLfloat>(0.0);
	this->_data[10] = static_cast<GLfloat>(1.0);
	this->_data[11] = static_cast<GLfloat>(0.0);
	this->_data[12] = static_cast<GLfloat>(0.0);
	this->_data[13] = static_cast<GLfloat>(0.0);
	this->_data[14] = static_cast<GLfloat>(0.0);
	this->_data[15] = static_cast<GLfloat>(1.0);

}

void Matrix4::Display ()
{
	GLfloat* temp = this->ReturnArrayGL();

	for(int i=0;i<16;++i)
	{
		std::cout<<*(temp+i)<<" ";

		if((i+1)%4==0)
			std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

void Matrix4::DisplayGL ()
{
	for(int i=0;i<16;++i)
	{
		std::cout<<_data[i]<<" ";

		if((i+1)%4==0)
			std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

// End of Utility functions
//

// Constructors
//
Matrix4::Matrix4(void)
{
	for(int i=0;i<16;++i)
		_data[i] = static_cast<GLfloat>(0.0);
}

Matrix4::Matrix4( GLfloat x1, GLfloat y1, GLfloat z1, GLfloat w1,
				  GLfloat x2, GLfloat y2, GLfloat z2, GLfloat w2,
				  GLfloat x3, GLfloat y3, GLfloat z3, GLfloat w3,
				  GLfloat x4, GLfloat y4, GLfloat z4, GLfloat w4 )
{
	_data[0]  = x1;
	_data[1]  = y1;
	_data[2]  = z1;
	_data[3]  = w1;

	_data[4]  = x2;
	_data[5]  = y2;
	_data[6]  = z2;
	_data[7]  = w2;

	_data[8]  = x3;
	_data[16]  = y3;
	_data[10] = z3;
	_data[11] = w3;

	_data[12] = x4;
	_data[13] = y4;
	_data[14] = z4;
	_data[15] = w4;
}

Matrix4::Matrix4( GLfloat* myMatrix )
{
	for(int i=0;i<16;++i)
		_data[i] = *(myMatrix+i);
}

Matrix4::Matrix4( GLfloat inc_data [4][4] )
{
	int index = 0;

	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			_data[index] = inc_data[i][j];
			++index;
		}
	}
}

Matrix4::Matrix4( Matrix3 myMatrix )
{
	this->data[0] = myMatrix.data[0];
	this->data[1] = myMatrix.data[1];
	this->data[2] = myMatrix.data[2];
	this->data[3] = static_cast<GLfloat>(0.0);

	this->data[4] = myMatrix.data[3];
	this->data[5] = myMatrix.data[4];
	this->data[6] = myMatrix.data[5];
	this->data[7] = static_cast<GLfloat>(0.0);

	this->data[8] = myMatrix.data[6];
	this->data[9] = myMatrix.data[7];
	this->data[10] = myMatrix.data[8];
	this->data[11] = static_cast<GLfloat>(0.0);
	
	this->data[12] = static_cast<GLfloat>(0.0);
	this->data[13] = static_cast<GLfloat>(0.0);
	this->data[14] = static_cast<GLfloat>(0.0);
	this->data[15] = static_cast<GLfloat>(1.0);
}
// End of Constructors
//
// Check if the matrices are equal to each other
bool Matrix4::operator== ( const Matrix4 &myMatrix )
{
	for(int i=0;i<16;++i)
		if(_data[i] != myMatrix._data[i])
			return false;

	return true;
}

// Copy vector to new matrix
// If matrix is the same, return it back
Matrix4 Matrix4::operator= ( const Matrix4 &myMatrix )
{
	if (this == &myMatrix)
		return *this;

	for(int i = 0; i<16;++i)
	{
		this->_data[i] = myMatrix._data[i];
	}

	return *this;
}

// Vector addition
Matrix4 Matrix4::operator+ ( const Matrix4& myMatrix )
{
	GLfloat temp[16];

	for(int i=0;i<16;++i)
	{
		temp[i] = this->_data[i] + myMatrix._data[i];
	}

	return Matrix4(temp);
}

void Matrix4::operator+= ( const Matrix4& myMatrix )
{
	*this = *this + myMatrix;
}

// Value addition
Matrix4 Matrix4::operator+ ( const GLfloat& value )
{
	GLfloat temp[16];

	for(int i=0;i<16;++i)
	{
		temp[i] = this->_data[i] + value;
	}

	return Matrix4(temp);
}

void Matrix4::operator+= ( const GLfloat& value )
{
	*this = *this + value;
}

// Vector subtraction
Matrix4 Matrix4::operator- ( const Matrix4& myMatrix )
{
	GLfloat temp[16];

	for(int i=0;i<16;++i)
	{
		temp[i] = this->_data[i] - myMatrix._data[i];
	}

	return Matrix4(temp);
}

void Matrix4::operator-= ( const Matrix4& myMatrix )
{
	*this = *this - myMatrix;
}

// Value subtraction
Matrix4 Matrix4::operator- ( const GLfloat& value )
{
	GLfloat temp[16];

	for(int i=0;i<16;++i)
	{
		temp[i] = this->_data[i] - value;
	}

	return Matrix4(temp);
}

void Matrix4::operator-= ( const GLfloat& value )
{
	*this = *this - value;
}	

// Negate matrix
Matrix4 Matrix4::operator- ()
{
	GLfloat temp[16];

	for(int i=0;i<16;++i)
	{
		temp[i] = this->_data[i] * -1;
	}

	return Matrix4(temp);
}

// Matrix multiplication
Matrix4 Matrix4::operator* ( const Matrix4& myMatrix )
{
	Matrix4 temp;

	//Used http://www.calcul.com/show/calculator/matrix-multiplication_;4;4;4;4?m_m1=[[0,1,2,3],[4,5,6,7],[8,9,10,11],[12,13,14,15]]&m_m2=[[A,B,C,D],[E,F,G,H],[I,J,K,L],[M,N,O,P]] 
	// TO help keep track of formula

	// Row by Row
	temp._data[0] = this->_data[0] * myMatrix[0] + this->_data[1] * myMatrix._data[4] + this->_data[2] * myMatrix._data[8] + this->_data[3] * myMatrix._data[12];
	temp._data[1] = this->_data[0] * myMatrix[1] + this->_data[1] * myMatrix._data[5] + this->_data[2] * myMatrix._data[9] + this->_data[3] * myMatrix._data[13];
	temp._data[2] = this->_data[0] * myMatrix[2] + this->_data[1] * myMatrix._data[6] + this->_data[2] * myMatrix._data[10] + this->_data[3] * myMatrix._data[14];
	temp._data[3] = this->_data[0] * myMatrix[3] + this->_data[1] * myMatrix._data[7] + this->_data[2] * myMatrix._data[11] + this->_data[3] * myMatrix._data[15];

	temp._data[4] = this->_data[4] * myMatrix[0] + this->_data[5] * myMatrix._data[4] + this->_data[6] * myMatrix._data[8] + this->_data[7] * myMatrix._data[12];
	temp._data[5] = this->_data[4] * myMatrix[1] + this->_data[5] * myMatrix._data[5] + this->_data[6] * myMatrix._data[9] + this->_data[7] * myMatrix._data[13];
	temp._data[6] = this->_data[4] * myMatrix[2] + this->_data[5] * myMatrix._data[6] + this->_data[6] * myMatrix._data[10] + this->_data[7] * myMatrix._data[14];
	temp._data[7] = this->_data[4] * myMatrix[3] + this->_data[5] * myMatrix._data[7] + this->_data[6] * myMatrix._data[11] + this->_data[7] * myMatrix._data[15];

	temp._data[8] = this->_data[8] * myMatrix[0] + this->_data[9] * myMatrix._data[4] + this->_data[10] * myMatrix._data[8] + this->_data[11] * myMatrix._data[12];
	temp._data[9] = this->_data[8] * myMatrix[1] + this->_data[9] * myMatrix._data[5] + this->_data[10] * myMatrix._data[9] + this->_data[11] * myMatrix._data[13];
	temp._data[10] = this->_data[8] * myMatrix[2] + this->_data[9] * myMatrix._data[6] + this->_data[10] * myMatrix._data[10] + this->_data[11] * myMatrix._data[14];
	temp._data[11] = this->_data[8] * myMatrix[3] + this->_data[9] * myMatrix._data[7] + this->_data[10] * myMatrix._data[11] + this->_data[11] * myMatrix._data[15];

	temp._data[12] = this->_data[12] * myMatrix[0] + this->_data[13] * myMatrix._data[4] + this->_data[14] * myMatrix._data[8] + this->_data[15] * myMatrix._data[12];
	temp._data[13] = this->_data[12] * myMatrix[1] + this->_data[13] * myMatrix._data[5] + this->_data[14] * myMatrix._data[9] + this->_data[15] * myMatrix._data[13];
	temp._data[14] = this->_data[12] * myMatrix[2] + this->_data[13] * myMatrix._data[6] + this->_data[14] * myMatrix._data[10] + this->_data[15] * myMatrix._data[14];
	temp._data[15] = this->_data[12] * myMatrix[3] + this->_data[13] * myMatrix._data[7] + this->_data[14] * myMatrix._data[11] + this->_data[15] * myMatrix._data[15];

	return (temp);
}

void Matrix4::operator*= ( const Matrix4& myMatrix )
{
	*this = *this * myMatrix;
}

// Scalar multiplication
Matrix4 Matrix4::operator* ( const GLfloat& scalar )
{
	GLfloat temp[16];

	for(int i=0;i<16;++i)
	{
		temp[i] = this->_data[i] * scalar;
	}

	return Matrix4(temp);
}

void Matrix4::operator*= ( const GLfloat& scalar )
{
	*this = *this * scalar;
}

Matrix4 Matrix4::operator/ ( const Matrix4& myMatrix )
{
	Matrix4 temp = myMatrix;

	return( *this * temp.Inverse() );
}

/*
 * End of overloaded operators
 */

// Copy values into array, swap values at key points for valid transpose for a 4x4
Matrix4 Matrix4::Transpose ()
{
	GLfloat temp[16];
	
	// copy the matrix into a temp array
	for(int i=0;i<16;++i)
		temp[i] = _data[i];

	//    1  2  3
	// 4     6  7
	// 8  9     11
	// 12 13 14   
	// Swap spots for transpose
	Swap(temp[1], temp[4]);
	Swap(temp[2], temp[8]);
	Swap(temp[3], temp[12]);
	Swap(temp[6], temp[9]);
	Swap(temp[7], temp[13]);
	Swap(temp[11], temp[14]);

	return Matrix4(temp);
}

// Given an location within 
// 0  1  2  3
// 4  5  6  7 
// 8  9  10 11
// 12 13 14 15 indicies
//
// Return a 3x3 matrix to be be used for the inverse by return part of a cofactor matrix
// When index is selected ignore that row and column
Matrix3 Matrix4::FindCofactorMatrix3x3 ( const size_t& index )
{
	int rowC, colC;
	// These are the rows and columns to be ignored
	// Resulting values are within 0,1,2,3
	// first row  is 0, last row 3
	// first col is 0, last col is 3
	rowC = index/4; // 4 is the number of dimensions being used
	colC = index%4;
	
	int counter = 0; // Keep track of transfering 4x4 matrix into a simple 2D array, for organization

	GLfloat temp[4][4];

	for(int row=0;row<4;++row)
		for(int col=0;col<4;++col)
			temp[row][col] = this->_data[counter++];

	GLfloat cofactor[9];

	counter = 0;
	for(int row=0;row<4;++row)
		for(int col=0;col<4;++col)
		{
			if(rowC == row || colC == col)
			{ // Skip that row and column
			}
			else
			{
				// Value is included for our cofactor
				cofactor[counter++] = temp[row][col];
			}
		}

	return Matrix3(cofactor);
}

Matrix4 Matrix4::Adjoint ()
{
	/* Find the Adjoint
	 * http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
	 */

	GLfloat detOfCofactors[16];

	// Find cofactor for each element then take the determinant to then place it in a 4x4 matrix
	for(int i=0;i<16;++i)
	{
		detOfCofactors[i] = this->FindCofactorMatrix3x3(i).Determinant();
	}

	// Place our cofactor determinant values into 4x4 matrix class, to continue with operations
	Matrix4 temp(detOfCofactors);

	// Matrix of cofactors
	// + - + -
	// - + - +
	// + - + -
	// - + - +
	temp._data[1] *= -1;
	temp._data[3] *= -1;
	temp._data[4] *= -1;
	temp._data[6] *= -1;
	temp._data[9] *= -1;
	temp._data[11] *= -1;
	temp._data[12] *= -1;
	temp._data[14] *= -1;
	
	return temp.Transpose();
}

Matrix4 Matrix4::Inverse ()
{
	/* How to take the inverse of a matrix
	 * http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
	 * http://www.youtube.com/watch?feature=player_detailpage&v=nNOz6Ez8Fn4#t=139s
	 */
	float det = this->Determinant();
	if(det == 0.0)
	{
		std::cerr<<"No inverse for this matrix\n";
		return *this;
	}

	/* Inverse forumla for nxn matrix
	 * http://ncalculators.com/matrix/inverse-matrix.htm
	 */

	return ( this->Adjoint() * (1/det) );
}

GLfloat Matrix4::Determinant ()
{
	/* Finding the determinant
	 * http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
	 */
	return ( ( this->_data[0] * this->_data[5] * this->_data[10] * this->_data[15] ) + ( this->_data[0] * this->_data[6] * this->_data[11] * this->_data[13] ) + ( this->_data[0] * this->_data[7] * this->_data[9] * this->_data[14] )
		   + ( this->_data[1] * this->_data[4] * this->_data[11] * this->_data[14] ) + ( this->_data[1] * this->_data[6] * this->_data[8]  * this->_data[15] ) + ( this->_data[1] * this->_data[7] * this->_data[10] * this->_data[12] ) 
		   + ( this->_data[2] * this->_data[4] * this->_data[9]  * this->_data[15] ) + ( this->_data[2] * this->_data[5] * this->_data[11] * this->_data[12] ) + ( this->_data[2] * this->_data[7] * this->_data[8] * this->_data[13] ) 
		   + ( this->_data[3] * this->_data[4] * this->_data[10] * this->_data[13] ) + ( this->_data[3] * this->_data[5] * this->_data[8] * this->_data[14] )  + ( this->_data[3] * this->_data[6] * this->_data[9] * this->_data[12] )

		   - ( this->_data[0] * this->_data[5] * this->_data[11] * this->_data[14] ) - ( this->_data[0] * this->_data[6] * this->_data[9] * this->_data[15] )  - ( this->_data[0] * this->_data[7] * this->_data[10] * this->_data[13] ) 
		   - ( this->_data[1] * this->_data[4] * this->_data[10] * this->_data[15] ) - ( this->_data[1] * this->_data[6] * this->_data[11] * this->_data[12] ) - ( this->_data[1] * this->_data[7] * this->_data[8] * this->_data[14] )
		   - ( this->_data[2] * this->_data[4] * this->_data[11] * this->_data[13] ) - ( this->_data[2] * this->_data[5] * this->_data[8] * this->_data[15] )  - ( this->_data[2] * this->_data[7] * this->_data[9] * this->_data[12] )
		   - ( this->_data[3] * this->_data[4] * this->_data[9] * this->_data[14] )  - ( this->_data[3] * this->_data[5] * this->_data[10] * this->_data[12] ) - ( this->_data[3] * this->_data[6] * this->_data[8] * this->_data[13] ) );
}

// Row and Col are between 1 and 3 inclusive
// 11 12 13 14
// 21 22 23 24
// 31 32 33 34
// 41 42 43 44
const GLfloat Matrix4::operator()( const size_t& col, const size_t& row ) const
{
	if( col > 4 || row > 4 || col < 0 || row < 0)
	{
		std::cerr << "Col or Row out of bounds, confine with in 3 deminsions\nValues accepted: 1,2,3 for rows and col\n";
	}

	/*
	 Approach as to how I got the formula to find the element given row and col

	int i = 0;
	switch(col)
	{
	case 1: // 0 1 2 3
		i += 0;
		break;
	case 2: // 4 5 6 7
		i += 4;
		break;
	case 3: // 8 9 10 11
		i += 4;
		break;
	case 4: // 12 13 14 15
		i += 4;
		break;
	}
	*/

	return _data[((col-1)*4)+row - 1];
}

GLfloat& Matrix4::operator ()( const size_t& row, const size_t& col )
{
	if( col > 4 || row > 4 || col < 0 || row < 0)
	{
		std::cerr << "Col or Row out of bounds, confine with in 3 deminsions\nValues accepted: 1,2,3 for rows and col\n";
	}

	/*
	 Approach as to how I got the formula to find the element given row and col

	int i = 0;
	switch(col)
	{
	case 1: // 0 1 2 3
		i += 0;
		break;
	case 2: // 4 5 6 7
		i += 4;
		break;
	case 3: // 8 9 10 11
		i += 4;
		break;
	case 4: // 12 13 14 15
		i += 4;
		break;
	}
	*/

	return _data[((col-1)*4)+row - 1];
}

GLfloat* Matrix4::ReturnArray ()
{
	GLfloat* temp = new GLfloat[16];
	for(int i=0;i<16;++i)
		temp[i] = this->data[i];

	return temp;
}

GLfloat* Matrix4::ReturnArrayGL ()
{
	Matrix4 t = *this;
	GLfloat* temp = new GLfloat[16];

	*(temp+0)  = t(1,1);
	*(temp+1)  = t(1,2);
	*(temp+2)  = t(1,3);
	*(temp+3)  = t(1,4);
	*(temp+4)  = t(2,1);
	*(temp+5)  = t(2,2);
	*(temp+6)  = t(2,3);
	*(temp+7)  = t(2,4);
	*(temp+8)  = t(3,1);
	*(temp+9)  = t(3,2);
	*(temp+10) = t(3,3);
	*(temp+11) = t(3,4);
	*(temp+12) = t(4,1);
	*(temp+13) = t(4,2);
	*(temp+14) = t(4,3);
	*(temp+15) = t(4,4);
	

	return temp;
}

// Rortation about some degree angle. x,y,z are strength in the rotation for that axis.
// For now only used 0 or 1 to determine which axis to rotate about.
Matrix4 Rotate ( const GLfloat angleInDegrees, const GLfloat x, const GLfloat y, const GLfloat z )
{
	Matrix4 rotate;
	rotate.Identity();

	if ( x==1.0 && y==0.0 && z==0.0 )
	{
		rotate(2,2) = cos(DEG2RAD(angleInDegrees));
		rotate(2,3) = -sin(DEG2RAD(angleInDegrees));
		rotate(3,2) = sin(DEG2RAD(angleInDegrees));
		rotate(3,3) = cos(DEG2RAD(angleInDegrees));
		rotate(4,4) = 1.0;
	}
	else if ( x==0.0 && y==1.0 && z==0.0)
	{
		rotate(1,1) = cos(DEG2RAD(angleInDegrees));
		rotate(1,3) = sin(DEG2RAD(angleInDegrees));
		rotate(3,1) = -sin(DEG2RAD(angleInDegrees));
		rotate(3,3) = cos(DEG2RAD(angleInDegrees));
		rotate(4,4) = 1.0;
	}
	else if ( x==0.0 && y==0.0 && z==1.0)
	{
		rotate(1,1) = cos(DEG2RAD(angleInDegrees));
		rotate(1,2) = -sin(DEG2RAD(angleInDegrees));
		rotate(2,1) = sin(DEG2RAD(angleInDegrees));
		rotate(2,2) = cos(DEG2RAD(angleInDegrees));
		rotate(4,4) = 1.0;
	}

	return rotate;
}

Matrix4 Translate ( GLfloat x, GLfloat y, GLfloat z )
{
	Matrix4 translate;
	translate.Identity();

	translate(4,1) = x;
	translate(4,2) = y;
	translate(4,3) = z;

	return translate;
}

Matrix4 UniformScale ( GLfloat s )
{
	Matrix4 uniformScale;
	uniformScale.Identity();
	uniformScale(1,1) = s;
	uniformScale(2,2) = s;
	uniformScale(3,3) = s;
	uniformScale(4,4) = 1.0;

	return uniformScale;
}

Matrix4 Scale ( GLfloat a, GLfloat b, GLfloat c )
{
	Matrix4 scale;
	scale.Identity();
	scale(1,1) = a;
	scale(2,2) = b;
	scale(3,3) = c;
	scale(4,4) = 1.0;

	return scale;
}