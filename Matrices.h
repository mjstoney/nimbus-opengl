#ifndef _H_MatH_MatRICES_
#define _H_MatH_MatRICES_
#include <ostream>


/*
Row Major!

These Matrices are row major, with a linear memory layout.
This means, a 4x4 transform Matrix breaks down into the
following components:

Xx, Xy, Xz, 0
Yx, Yy, Yz, 0
Zx, Zy, Zz, 0
Tx, Ty, Tz, 1

Where the rotation about the X axis is defined by the Vector:
(Xx, Xy, Xy). The scale of the Matrix is found in it's main
diagonal: (Xx, Yy, Zz).

The Matrix is laid out by rows in memory as well. This gives
us a nice linear memory map. This is what the above Matrix
looks like in memory:

{ Xx, Xy, Xz, 0, Yx, Yy, Yz, 0, Zx, Zy, Zz, 0, Tx, Ty, Tz, 1 };
*/

/*
Pre Multiplication!
Matrices are concatenated left to right. This means a MVP
Matrix could be built like so
Mat4 MVP = model * view * projection
Or the world transform: SRT
scale first, rotate second, translate last
world = scale * rotate * translate
This makes reading Matrix multiplication quiet intuitive.
The parent child relation-ship looks like this
child.absolute = child.relative * parent.absolute
world = local * parent.world
*/

/*
Row Vectors
Vectors are treated as 1x3 (or 1x4) row Vectors. This means in the
multiplication chain they MUST be put in front of Matrices! Like so
Vec3 final = pointVecTOR * model * view * projection
This is because we can only multiply Matrices if their inner
dimensions Match. This makes our multiplication be 1x4 * 4x4.
*/

/*
Left Handed!
The Projection and Orthographic projection functions product left
handed Matrices. That is, +Z goes INTO the screen.
*/


#include "Vectors.h"

typedef struct Mat2 {
	union {
		struct {
			float	_11, _12,
				_21, _22;
		};
		float asArray[4];
	};

	inline Mat2() {
		_11 = _22 = 1.0f;
		_12 = _21 = 0.0f;
	}

	inline Mat2(float f11, float f12,
		float f21, float f22) {
		_11 = f11; _12 = f12;
		_21 = f21; _22 = f22;
	}

	inline float* operator[](int i) {
		return &(asArray[i * 2]);
	}
} Mat2;

typedef struct Mat3 {
	union {
		struct {
			float	_11, _12, _13,
				_21, _22, _23,
				_31, _32, _33;
		};
		float asArray[9];
	};

	inline Mat3() {
		_11 = _22 = _33 = 1.0f;
		_12 = _13 = _21 = 0.0f;
		_23 = _31 = _32 = 0.0f;
	}

	inline Mat3(float f11, float f12, float f13,
		float f21, float f22, float f23,
		float f31, float f32, float f33) {
		_11 = f11; _12 = f12; _13 = f13;
		_21 = f21; _22 = f22; _23 = f23;
		_31 = f31; _32 = f32; _33 = f33;
	}

	inline float* operator[](int i) {
		return &(asArray[i * 3]);
	}
} Mat3;

typedef struct Mat4 {
	union {
		struct {
			float	_11, _12, _13, _14,
				_21, _22, _23, _24,
				_31, _32, _33, _34,
				_41, _42, _43, _44;
		};
		float asArray[16];
	};

	inline Mat4() {
		_11 = _22 = _33 = _44 = 1.0f;
		_12 = _13 = _14 = _21 = 0.0f;
		_23 = _24 = _31 = _32 = 0.0f;
		_34 = _41 = _42 = _43 = 0.0f;
	}

	inline Mat4(float f11, float f12, float f13, float f14,
		float f21, float f22, float f23, float f24,
		float f31, float f32, float f33, float f34,
		float f41, float f42, float f43, float f44) {
		_11 = f11; _12 = f12; _13 = f13; _14 = f14;
		_21 = f21; _22 = f22; _23 = f23; _24 = f24;
		_31 = f31; _32 = f32; _33 = f33; _34 = f34;
		_41 = f41; _42 = f42; _43 = f43; _44 = f44;
	}

	inline float* operator[](int i) {
		return &(asArray[i * 4]);
	}
} Mat4;

bool operator==(const Mat2& l, const Mat2& r);
bool operator==(const Mat3& l, const Mat3& r);
bool operator==(const Mat4& l, const Mat4& r);

bool operator!=(const Mat2& l, const Mat2& r);
bool operator!=(const Mat3& l, const Mat3& r);
bool operator!=(const Mat4& l, const Mat4& r);

std::ostream& operator<<(std::ostream& os, const Mat2& m);
std::ostream& operator<<(std::ostream& os, const Mat3& m);
std::ostream& operator<<(std::ostream& os, const Mat4& m);

void Transpose(const float* srcMat, float* dstMat, int srcRows, int srcCols);
Mat2 Transpose(const Mat2& Matrix);
Mat3 Transpose(const Mat3& Matrix);
Mat4 Transpose(const Mat4& Matrix);

Mat2 operator*(const Mat2& Matrix, float scalar);
Mat3 operator*(const Mat3& Matrix, float scalar);
Mat4 operator*(const Mat4& Matrix, float scalar);

bool Multiply(float* out, const float* MatA, int aRows, int aCols, const float* MatB, int bRows, int bCols);
Mat2 operator*(const Mat2& MatrixA, const Mat2& MatrixB);
Mat3 operator*(const Mat3& MatrixA, const Mat3& MatrixB);
Mat4 operator*(const Mat4& MatrixA, const Mat4& MatrixB);

Mat3 Cut(const Mat4& Mat, int row, int col);
Mat2 Cut(const Mat3& Mat, int row, int col);
void Cofactor(float* out, const float* minor, int rows, int cols);

Mat2 Minor(const Mat2& Mat);
Mat2 Cofactor(const Mat2& Mat);
float Determinant(const Mat2& Matrix);
Mat2 Adjugate(const Mat2& Mat);
Mat2 Inverse(const Mat2& Mat);

Mat3 Minor(const Mat3& Mat);
Mat3 Cofactor(const Mat3& Mat);
float Determinant(const Mat3& Mat);
Mat3 Adjugate(const Mat3& Mat);
Mat3 Inverse(const Mat3& Mat);

Mat4 Minor(const Mat4& Mat);
Mat4 Cofactor(const Mat4& Mat);
float Determinant(const Mat4& Mat);
Mat4 Adjugate(const Mat4& Mat);
Mat4 Inverse(const Mat4& Mat);

Mat4 ToColumnMajor(const Mat4& Mat);
Mat3 ToColumnMajor(const Mat3& Mat);
Mat4 FromColumnMajor(const Mat4& Mat);
Mat3 FromColumnMajor(const Mat3& Mat);
Mat4 FromColumnMajor(const float* Mat);

Mat4 Translation(float x, float y, float z);
Mat4 Translation(const Vec3& pos);
Vec3 GetTranslation(const Mat4& Mat);

Mat4 Translate(float x, float y, float z);
Mat4 Translate(const Vec3& pos);
Mat4 FromMat3(const Mat3& Mat);

Mat4 Scale(float x, float y, float z);
Mat4 Scale(const Vec3& Vec);
Vec3 GetScale(const Mat4& Mat);

Mat4 Rotation(float pitch, float yaw, float roll); // X, Y, Z
Mat3 Rotation3x3(float pitch, float yaw, float roll); // X, Y, Z
Mat2 Rotation2x2(float angle);
Mat4 YawPitchRoll(float yaw, float pitch, float roll); // Y, X, Z

Mat4 XRotation(float angle);
Mat3 XRotation3x3(float angle);

Mat4 YRotation(float angle);
Mat3 YRotation3x3(float angle);

Mat4 ZRotation(float angle);
Mat3 ZRotation3x3(float angle);

Mat4 Orthogonalize(const Mat4& Mat);
Mat3 Orthogonalize(const Mat3& Mat);

Mat4 AxisAngle(Vec3& axis, float angle);
Mat3 AxisAngle3x3(Vec3& axis, float angle);

Vec3 MultiplyPoint(const Vec3& Vec, const Mat4& Mat);
Vec3 MultiplyVector(const Vec3& Vec, const Mat4& Mat);
Vec3 MultiplyVector(const Vec3& Vec, const Mat3& Mat);

Mat4 Transform(const Vec3& scale, const Vec3& eulerRotation, const Vec3& translate);
Mat4 Transform(const Vec3& scale, const Vec3& rotationAxis, float rotationAngle, const Vec3& translate);

Mat4 LookAt(const Vec3& position, const Vec3& target, const Vec3& up);
Mat4 Projection(float fov, float aspect, float zNear, float zFar);
Mat4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);

Vec3 Decompose(const Mat3& rot);

Mat3 FastInverse(const Mat3& Mat);
Mat4 FastInverse(const Mat4& Mat);

#endif