#pragma once

#include "stdincludes.h"

#include "Vector2.h"



class Matrix2x2
{
public:
    // If bZero is true, create the zero matrix.  Otherwise, create the
    // identity matrix.
    explicit Matrix2x2 (bool bZero = true);

    // copy constructor
    Matrix2x2 (const Matrix2x2& rhs);

    // input Mrc is in row r, column c.
    Matrix2x2 (float fM00, float fM01, float fM10, float fM11);

    // Create a matrix from an array of numbers.  The input array is
    // interpreted based on the Boolean input as
    //   true:  entry[0..3] = {m00,m01,m10,m11}  [row major]
    //   false: entry[0..3] = {m00,m10,m01,m11}  [column major]
    Matrix2x2 (const float afEntry[4], bool bRowMajor);

    // Create matrices based on vector input.  The Boolean is interpreted as
    //   true: vectors are columns of the matrix
    //   false: vectors are rows of the matrix
    Matrix2x2 (const Vector2& rkU, const Vector2& rkV,
        bool bColumns);
    Matrix2x2 (const Vector2* akV, bool bColumns);

    // create a diagonal matrix
    Matrix2x2 (float fM00, float fM11);

    // create a rotation matrix (positive angle - counterclockwise)
    explicit Matrix2x2 (float fAngle);

    // create a tensor product U*V^T
    Matrix2x2 (const Vector2& rkU, const Vector2& rkV);

    // create various matrices
    void MakeZero ();
    void MakeIdentity ();
    void MakeDiagonal (float fM00, float fM11);
    void FromAngle (float fAngle);
    void MakeTensorProduct (const Vector2& rkU,
        const Vector2& rkV);

    // member access
    inline operator const float* () const;
    inline operator float* ();
    inline const float* operator[] (int iRow) const;
    inline float* operator[] (int iRow);
    inline float operator() (int iRow, int iCol) const;
    inline float& operator() (int iRow, int iCol);
    void SetRow (int iRow, const Vector2& rkV);
    Vector2 GetRow (int iRow) const;
    void SetColumn (int iCol, const Vector2& rkV);
    Vector2 GetColumn (int iCol) const;
    void GetColumnMajor (float* afCMajor) const;

    // assignment
    inline Matrix2x2& operator= (const Matrix2x2& rhs);

    // comparison
    bool operator== (const Matrix2x2& rhs) const;
    bool operator!= (const Matrix2x2& rhs) const;
    bool operator<  (const Matrix2x2& rhs) const;
    bool operator<= (const Matrix2x2& rhs) const;
    bool operator>  (const Matrix2x2& rhs) const;
    bool operator>= (const Matrix2x2& rhs) const;

    // arithmetic operations
    inline Matrix2x2 operator+ (const Matrix2x2& rhs) const;
    inline Matrix2x2 operator- (const Matrix2x2& rhs) const;
    inline Matrix2x2 operator* (const Matrix2x2& rhs) const;
    inline Matrix2x2 operator* (float fScalar) const;
    inline Matrix2x2 operator/ (float fScalar) const;
    inline Matrix2x2 operator- () const;

    // arithmetic updates
    inline Matrix2x2& operator+= (const Matrix2x2& rhs);
    inline Matrix2x2& operator-= (const Matrix2x2& rhs);
    inline Matrix2x2& operator*= (float fScalar);
    inline Matrix2x2& operator/= (float fScalar);

    // matrix times vector
    inline Vector2 operator* (const Vector2& rkV) const;  // M * v

    // other operations
    Matrix2x2 Transpose () const;  // M^T
    Matrix2x2 TransposeTimes (const Matrix2x2& rhs) const;  // this^T * M
    Matrix2x2 TimesTranspose (const Matrix2x2& rhs) const;  // this * M^T
    Matrix2x2 Inverse () const;
    Matrix2x2 Adjoint () const;
    float Determinant () const;
    float QForm (const Vector2& rkU,
        const Vector2& rkV) const;  // u^T*M*v

    // The matrix must be a rotation for these functions to be valid.  The
    // last function uses Gram-Schmidt orthonormalization applied to the
    // columns of the rotation matrix.  The angle must be in radians, not
    // degrees.
    void ToAngle (float& rfAngle) const;
    void Orthonormalize ();

    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1] is a rotation matrix with columns u0 and u1 and
    // D = diag(d0,d1) is a diagonal matrix whose diagonal entries are d0 and
    // d1.  The eigenvector u[i] corresponds to eigenvector d[i].  The
    // eigenvalues are ordered as d0 <= d1.
    void EigenDecomposition (Matrix2x2& rkRot, Matrix2x2& rkDiag) const;

    static const Matrix2x2 ZERO;
    static const Matrix2x2 IDENTITY;

private:
    // support for comparisons
    int CompareArrays (const Matrix2x2& rhs) const;

    // matrix stored in row-major order
    float m[4];
};

// c * M

inline Matrix2x2 operator* (float fScalar, const Matrix2x2& rhs);

// v^T * M
inline Vector2 operator* (const Vector2& rkV,
    const Matrix2x2& rhs);

#include "Matrix2x2.inl"