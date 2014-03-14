#include <cfloat>
#include <cstdlib>
#include <cstring>

const float ZERO_TOLERANCE = 0.00001f;

inline Matrix2x2::Matrix2x2 (bool bZero)
{
    if (bZero)
    {
        MakeZero();
    }
    else
    {
        MakeIdentity();
    }
}
//----------------------------------------------------------------------------

inline Matrix2x2::Matrix2x2 (const Matrix2x2& rhs)
{
    m[0] = rhs.m[0];
    m[1] = rhs.m[1];
    m[2] = rhs.m[2];
    m[3] = rhs.m[3];
}
//----------------------------------------------------------------------------

inline Matrix2x2::Matrix2x2 (float fM00, float fM01, float fM10, float fM11)
{
    m[0] = fM00;
    m[1] = fM01;
    m[2] = fM10;
    m[3] = fM11;
}
//----------------------------------------------------------------------------

inline Matrix2x2::Matrix2x2 (const float afEntry[4], bool bRowMajor)
{
    if (bRowMajor)
    {
        m[0] = afEntry[0];
        m[1] = afEntry[1];
        m[2] = afEntry[2];
        m[3] = afEntry[3];
    }
    else
    {
        m[0] = afEntry[0];
        m[1] = afEntry[2];
        m[2] = afEntry[1];
        m[3] = afEntry[3];
    }
}
//----------------------------------------------------------------------------

inline Matrix2x2::Matrix2x2 (const Vector2& rkU, const Vector2& rkV,
    bool bColumns)
{
    if (bColumns)
    {
        m[0] = rkU[0];
        m[1] = rkV[0];
        m[2] = rkU[1];
        m[3] = rkV[1];
    }
    else
    {
        m[0] = rkU[0];
        m[1] = rkU[1];
        m[2] = rkV[0];
        m[3] = rkV[1];
    }
}
//----------------------------------------------------------------------------

inline Matrix2x2::Matrix2x2 (const Vector2* akV, bool bColumns)
{
    if (bColumns)
    {
        m[0] = akV[0][0];
        m[1] = akV[1][0];
        m[2] = akV[0][1];
        m[3] = akV[1][1];
    }
    else
    {
        m[0] = akV[0][0];
        m[1] = akV[0][1];
        m[2] = akV[1][0];
        m[3] = akV[1][1];
    }
}
//----------------------------------------------------------------------------

inline Matrix2x2::Matrix2x2 (float fM00, float fM11)
{
    MakeDiagonal(fM00,fM11);
}
//----------------------------------------------------------------------------

inline Matrix2x2::Matrix2x2 (float fAngle)
{
    FromAngle(fAngle);
}
//----------------------------------------------------------------------------

inline Matrix2x2::Matrix2x2 (const Vector2& rkU, const Vector2& rkV)
{
    MakeTensorProduct(rkU,rkV);
}
//----------------------------------------------------------------------------

inline Matrix2x2::operator const float* () const
{
    return m;
}
//----------------------------------------------------------------------------

inline Matrix2x2::operator float* ()
{
    return m;
}
//----------------------------------------------------------------------------

inline const float* Matrix2x2::operator[] (int iRow) const
{
    return &m[2*iRow];
}
//----------------------------------------------------------------------------

inline float* Matrix2x2::operator[] (int iRow)
{
    return &m[2*iRow];
}
//----------------------------------------------------------------------------

inline float Matrix2x2::operator() (int iRow, int iCol) const
{
    return m[iCol + 2*iRow];
}
//----------------------------------------------------------------------------

inline float& Matrix2x2::operator() (int iRow, int iCol)
{
    return m[iCol + 2*iRow];
}
//----------------------------------------------------------------------------

inline void Matrix2x2::MakeZero ()
{
    m[0] = (float)0.0;
    m[1] = (float)0.0;
    m[2] = (float)0.0;
    m[3] = (float)0.0;
}
//----------------------------------------------------------------------------

inline void Matrix2x2::MakeIdentity ()
{
    m[0] = (float)1.0;
    m[1] = (float)0.0;
    m[2] = (float)0.0;
    m[3] = (float)1.0;
}
//----------------------------------------------------------------------------

inline void Matrix2x2::MakeDiagonal (float fM00, float fM11)
{
    m[0] = fM00;
    m[1] = (float)0.0;
    m[2] = (float)0.0;
    m[3] = fM11;
}
//----------------------------------------------------------------------------

inline void Matrix2x2::FromAngle (float fAngle)
{
    m[0] = cosf(fAngle);
    m[2] = sinf(fAngle);
    m[1] = -m[2];
    m[3] =  m[0];
}
//----------------------------------------------------------------------------

inline void Matrix2x2::MakeTensorProduct (const Vector2& rkU,
    const Vector2& rkV)
{
    m[0] = rkU[0]*rkV[0];
    m[1] = rkU[0]*rkV[1];
    m[2] = rkU[1]*rkV[0];
    m[3] = rkU[1]*rkV[1];
}
//----------------------------------------------------------------------------

inline void Matrix2x2::SetRow (int iRow, const Vector2& rkV)
{
    int i0 = 2*iRow ,i1 = i0+1;
    m[i0] = rkV[0];
    m[i1] = rkV[1];
}
//----------------------------------------------------------------------------

inline Vector2 Matrix2x2::GetRow (int iRow) const
{
    int i0 = 2*iRow ,i1 = i0+1;
    return Vector2(m[i0],m[i1]);
}
//----------------------------------------------------------------------------

inline void Matrix2x2::SetColumn (int iCol, const Vector2& rkV)
{
    m[iCol] = rkV[0];
    m[iCol+2] = rkV[1];
}
//----------------------------------------------------------------------------

inline Vector2 Matrix2x2::GetColumn (int iCol) const
{
    return Vector2(m[iCol],m[iCol+2]);
}
//----------------------------------------------------------------------------

inline void Matrix2x2::GetColumnMajor (float* afCMajor) const
{
    afCMajor[0] = m[0];
    afCMajor[1] = m[2];
    afCMajor[2] = m[1];
    afCMajor[3] = m[3];
}
//----------------------------------------------------------------------------

inline Matrix2x2& Matrix2x2::operator= (const Matrix2x2& rhs)
{
    m[0] = rhs.m[0];
    m[1] = rhs.m[1];
    m[2] = rhs.m[2];
    m[3] = rhs.m[3];
    return *this;
}
//----------------------------------------------------------------------------

inline int Matrix2x2::CompareArrays (const Matrix2x2& rhs) const
{
    return memcmp(m,rhs.m,4*sizeof(float));
}
//----------------------------------------------------------------------------

inline bool Matrix2x2::operator== (const Matrix2x2& rhs) const
{
    return CompareArrays(rhs) == 0;
}
//----------------------------------------------------------------------------

inline bool Matrix2x2::operator!= (const Matrix2x2& rhs) const
{
    return CompareArrays(rhs) != 0;
}
//----------------------------------------------------------------------------

inline bool Matrix2x2::operator<  (const Matrix2x2& rhs) const
{
    return CompareArrays(rhs) < 0;
}
//----------------------------------------------------------------------------

inline bool Matrix2x2::operator<= (const Matrix2x2& rhs) const
{
    return CompareArrays(rhs) <= 0;
}
//----------------------------------------------------------------------------

inline bool Matrix2x2::operator>  (const Matrix2x2& rhs) const
{
    return CompareArrays(rhs) > 0;
}
//----------------------------------------------------------------------------

inline bool Matrix2x2::operator>= (const Matrix2x2& rhs) const
{
    return CompareArrays(rhs) >= 0;
}
//----------------------------------------------------------------------------

inline Matrix2x2 Matrix2x2::operator+ (const Matrix2x2& rhs) const
{
    return Matrix2x2(
        m[0] + rhs.m[0],
        m[1] + rhs.m[1],
        m[2] + rhs.m[2],
        m[3] + rhs.m[3]);
}
//----------------------------------------------------------------------------

inline Matrix2x2 Matrix2x2::operator- (const Matrix2x2& rhs) const
{
    return Matrix2x2(
        m[0] - rhs.m[0],
        m[1] - rhs.m[1],
        m[2] - rhs.m[2],
        m[3] - rhs.m[3]);
}
//----------------------------------------------------------------------------

inline Matrix2x2 Matrix2x2::operator* (const Matrix2x2& rhs) const
{
    return Matrix2x2(
        m[0]*rhs.m[0] + m[1]*rhs.m[2],
        m[0]*rhs.m[1] + m[1]*rhs.m[3],
        m[2]*rhs.m[0] + m[3]*rhs.m[2],
        m[2]*rhs.m[1] + m[3]*rhs.m[3]);
}
//----------------------------------------------------------------------------

inline Matrix2x2 Matrix2x2::operator* (float fScalar) const
{
    return Matrix2x2(
        fScalar*m[0],
        fScalar*m[1],
        fScalar*m[2],
        fScalar*m[3]);
}
//----------------------------------------------------------------------------

inline Matrix2x2 Matrix2x2::operator/ (float fScalar) const
{
    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        return Matrix2x2(
            fInvScalar*m[0],
            fInvScalar*m[1],
            fInvScalar*m[2],
            fInvScalar*m[3]);
    }

    return Matrix2x2(
        FLT_MAX,
        FLT_MAX,
        FLT_MAX,
        FLT_MAX);
}
//----------------------------------------------------------------------------

inline Matrix2x2 Matrix2x2::operator- () const
{
    return Matrix2x2(
        -m[0],
        -m[1],
        -m[2],
        -m[3]);
}
//----------------------------------------------------------------------------

inline Matrix2x2& Matrix2x2::operator+= (const Matrix2x2& rhs)
{
    m[0] += rhs.m[0];
    m[1] += rhs.m[1];
    m[2] += rhs.m[2];
    m[3] += rhs.m[3];
    return *this;
}
//----------------------------------------------------------------------------

inline Matrix2x2& Matrix2x2::operator-= (const Matrix2x2& rhs)
{
    m[0] -= rhs.m[0];
    m[1] -= rhs.m[1];
    m[2] -= rhs.m[2];
    m[3] -= rhs.m[3];
    return *this;
}
//----------------------------------------------------------------------------

inline Matrix2x2& Matrix2x2::operator*= (float fScalar)
{
    m[0] *= fScalar;
    m[1] *= fScalar;
    m[2] *= fScalar;
    m[3] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------

inline Matrix2x2& Matrix2x2::operator/= (float fScalar)
{
    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        m[0] *= fInvScalar;
        m[1] *= fInvScalar;
        m[2] *= fInvScalar;
        m[3] *= fInvScalar;
    }
    else
    {
        m[0] = FLT_MAX;
        m[1] = FLT_MAX;
        m[2] = FLT_MAX;
        m[3] = FLT_MAX;
    }

    return *this;
}
//----------------------------------------------------------------------------

inline Vector2 Matrix2x2::operator* (const Vector2& rkV) const
{
    return Vector2(
        m[0]*rkV[0] + m[1]*rkV[1],
        m[2]*rkV[0] + m[3]*rkV[1]);
}
//----------------------------------------------------------------------------

inline Matrix2x2 Matrix2x2::Transpose () const
{
    return Matrix2x2(
        m[0],
        m[2],
        m[1],
        m[3]);
}
//----------------------------------------------------------------------------

inline Matrix2x2 Matrix2x2::TransposeTimes (const Matrix2x2& rhs) const
{
    // P = A^T*B
    return Matrix2x2(
        m[0]*rhs.m[0] + m[2]*rhs.m[2],
        m[0]*rhs.m[1] + m[2]*rhs.m[3],
        m[1]*rhs.m[0] + m[3]*rhs.m[2],
        m[1]*rhs.m[1] + m[3]*rhs.m[3]);
}
//----------------------------------------------------------------------------

inline Matrix2x2 Matrix2x2::TimesTranspose (const Matrix2x2& rhs) const
{
    // P = A*B^T
    return Matrix2x2(
        m[0]*rhs.m[0] + m[1]*rhs.m[1],
        m[0]*rhs.m[2] + m[1]*rhs.m[3],
        m[2]*rhs.m[0] + m[3]*rhs.m[1],
        m[2]*rhs.m[2] + m[3]*rhs.m[3]);
}
//----------------------------------------------------------------------------

inline Matrix2x2 Matrix2x2::Inverse () const
{
    Matrix2x2 kInverse;

    float fDet = m[0]*m[3] - m[1]*m[2];
    if (fabs(fDet) > ZERO_TOLERANCE)
    {
        float fInvDet = ((float)1.0)/fDet;
        kInverse.m[0] =  m[3]*fInvDet;
        kInverse.m[1] = -m[1]*fInvDet;
        kInverse.m[2] = -m[2]*fInvDet;
        kInverse.m[3] =  m[0]*fInvDet;
    }
    else
    {
        kInverse.m[0] = (float)0.0;
        kInverse.m[1] = (float)0.0;
        kInverse.m[2] = (float)0.0;
        kInverse.m[3] = (float)0.0;
    }

    return kInverse;
}
//----------------------------------------------------------------------------

inline Matrix2x2 Matrix2x2::Adjoint () const
{
    return Matrix2x2(
        m[3],
        -m[1],
        -m[2],
        m[0]);
}
//----------------------------------------------------------------------------

inline float Matrix2x2::Determinant () const
{
    return m[0]*m[3] - m[1]*m[2];
}
//----------------------------------------------------------------------------

inline float Matrix2x2::QForm (const Vector2& rkU,
    const Vector2& rkV) const
{
    return Dot(rkU, (*this)*rkV);
}
//----------------------------------------------------------------------------

inline void Matrix2x2::ToAngle (float& rfAngle) const
{
    // assert:  matrix is a rotation
    rfAngle = atan2f(m[2],m[0]);
}
//----------------------------------------------------------------------------

inline void Matrix2x2::Orthonormalize ()
{
    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1], then orthonormal output matrix is Q = [q0|q1],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // compute q0
    float fInvLength = 1.0f / sqrtf(m[0]*m[0] +
        m[2]*m[2]);

    m[0] *= fInvLength;
    m[2] *= fInvLength;

    // compute q1
    float fDot0 = m[0]*m[1] + m[2]*m[3];
    m[1] -= fDot0*m[0];
    m[3] -= fDot0*m[2];

    fInvLength = 1.0f / sqrtf(m[1]*m[1] +
        m[3]*m[3]);

    m[1] *= fInvLength;
    m[3] *= fInvLength;
}
//----------------------------------------------------------------------------

inline void Matrix2x2::EigenDecomposition (Matrix2x2& rkRot, Matrix2x2& rkDiag) const
{
    float fTrace = m[0] + m[3];
    float fDiff = m[0] - m[3];
    float fDiscr = sqrtf(fDiff*fDiff +
        ((float)4.0)*m[1]*m[1]);
    float fEVal0 = ((float)0.5)*(fTrace-fDiscr);
    float fEVal1 = ((float)0.5)*(fTrace+fDiscr);
    rkDiag.MakeDiagonal(fEVal0,fEVal1);

    float fCos, fSin;
    if (fDiff >= (float)0.0)
    {
        fCos = m[1];
        fSin = fEVal0 - m[0];
    }
    else
    {
        fCos = fEVal0 - m[3];
        fSin = m[1];
    }
    float fTmp = 1.0f / sqrtf(fCos*fCos + fSin*fSin);
    fCos *= fTmp;
    fSin *= fTmp;

    rkRot.m[0] = fCos;
    rkRot.m[1] = -fSin;
    rkRot.m[2] = fSin;
    rkRot.m[3] = fCos;
}
//----------------------------------------------------------------------------

inline Matrix2x2 operator* (float fScalar, const Matrix2x2& rhs)
{
    return rhs*fScalar;
}
//----------------------------------------------------------------------------

inline Vector2 operator* (const Vector2& rkV,
    const Matrix2x2& rhs)
{
    return Vector2(
        rkV[0]*rhs[0][0] + rkV[1]*rhs[1][0],
        rkV[0]*rhs[0][1] + rkV[1]*rhs[1][1]);
}
//----------------------------------------------------------------------------
