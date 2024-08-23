
#include "Matrices.h"
#include <cMath>
#include <cfloat>
#include <iostream>

bool operator==(const Mat2& l, const Mat2& r) {
	for (int i = 0; i < /* 2 * 2 = */4; ++i) {
		if (!CMP(l.asArray[i], r.asArray[i])) {
			return false;
		}
	}
	return true;
}

bool operator==(const Mat3& l, const Mat3& r) {
	for (int i = 0; i < /* 3 * 3 = */ 9; ++i) {
		if (!CMP(l.asArray[i], r.asArray[i])) {
			return false;
		}
	}
	return true;
}
bool operator==(const Mat4& l, const Mat4& r) {
	for (int i = 0; i < /* 4 * 4 = */ 16; ++i) {
		if (!CMP(l.asArray[i], r.asArray[i])) {
			return false;
		}
	}
	return true;
}

bool operator!=(const Mat2& l, const Mat2& r) {
	return !(l == r);
}

bool operator!=(const Mat3& l, const Mat3& r) {
	return !(l == r);
}

bool operator!=(const Mat4& l, const Mat4& r) {
	return !(l == r);
}

std::ostream& operator<<(std::ostream& os, const Mat2& m) {
	os << m._11 << ", " << m._12 << "\n";
	os << m._21 << ", " << m._22;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Mat3& m) {
	os << m._11 << ", " << m._12 << ", " << m._13 << "\n";
	os << m._21 << ", " << m._22 << ", " << m._23 << "\n";
	os << m._31 << ", " << m._32 << ", " << m._33;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Mat4& m) {
	os << m._11 << ", " << m._12 << ", " << m._13 << ", " << m._14 << "\n";
	os << m._21 << ", " << m._22 << ", " << m._23 << ", " << m._24 << "\n";
	os << m._31 << ", " << m._32 << ", " << m._33 << ", " << m._34 << "\n";
	os << m._41 << ", " << m._42 << ", " << m._43 << ", " << m._44;
	return os;
}

Mat3 FastInverse(const Mat3& Mat) {
	return Transpose(Mat);
}

Mat4 FastInverse(const Mat4& Mat) {

	Mat4 inverse = Transpose(Mat);
	inverse._41 = inverse._14 = 0.0f;
	inverse._42 = inverse._24 = 0.0f;
	inverse._43 = inverse._34 = 0.0f;

	Vec3 right = Vec3(Mat._11, Mat._12, Mat._13);
	Vec3 up = Vec3(Mat._21, Mat._22, Mat._23);
	Vec3 forward = Vec3(Mat._31, Mat._32, Mat._33);
	Vec3 position = Vec3(Mat._41, Mat._42, Mat._43);

	inverse._41 = -right.dot(position);
	inverse._42 = -up.dot(position);
	inverse._43 = -forward.dot(position);

	return inverse;
}

void Transpose(const float* srcMat, float* dstMat, int srcRows, int srcCols) {
	for (int i = 0; i < srcRows * srcCols; i++) {
		int row = i / srcRows;
		int col = i % srcRows;
		dstMat[i] = srcMat[srcCols * col + row];
	}
}

Mat2 Transpose(const Mat2& Matrix) {
	Mat2 result;
	Transpose(Matrix.asArray, result.asArray, 2, 2);
	return result;
}

Mat3 Transpose(const Mat3& Matrix) {
	Mat3 result;
	Transpose(Matrix.asArray, result.asArray, 3, 3);
	return result;
}

Mat4 Transpose(const Mat4& Matrix) {
	Mat4 result;
	Transpose(Matrix.asArray, result.asArray, 4, 4);
	return result;
}

Mat2 operator*(const Mat2& Matrix, float scalar) {
	Mat2 result;
	for (int i = 0; i < 4; ++i) {
		result.asArray[i] = Matrix.asArray[i] * scalar;
	}
	return result;
}

Mat3 operator*(const Mat3& Matrix, float scalar) {
	Mat3 result;
	for (int i = 0; i < 9; ++i) {
		result.asArray[i] = Matrix.asArray[i] * scalar;
	}
	return result;
}

Mat4 operator*(const Mat4& Matrix, float scalar) {
	Mat4 result;
	for (int i = 0; i < 16; ++i) {
		result.asArray[i] = Matrix.asArray[i] * scalar;
	}
	return result;
}

bool Multiply(float* out, const float* MatA, int aRows, int aCols, const float* MatB, int bRows, int bCols) {
	if (aCols != bRows) {
		return false;
	}

	for (int i = 0; i < aRows; ++i) {
		for (int j = 0; j < bCols; ++j) {
			out[bCols * i + j] = 0.0f;
			for (int k = 0; k < bRows; ++k) {
				out[bCols * i + j] += MatA[aCols * i + k] * MatB[bCols * k + j];
			}
		}
	}

	return true;
}

Mat2 operator*(const Mat2& MatrixA, const Mat2& MatrixB) {
	Mat2 result;
	Multiply(result.asArray, MatrixA.asArray, 2, 2, MatrixB.asArray, 2, 2);
	return result;
}

Mat3 operator*(const Mat3& MatrixA, const Mat3& MatrixB) {
	Mat3 result;
	Multiply(result.asArray, MatrixA.asArray, 3, 3, MatrixB.asArray, 3, 3);
	return result;
}

Mat4 operator*(const Mat4& MatrixA, const Mat4& MatrixB) {
	Mat4 result;
	Multiply(result.asArray, MatrixA.asArray, 4, 4, MatrixB.asArray, 4, 4);
	return result;
}

float Determinant(const Mat2& Matrix) {
	return Matrix._11 * Matrix._22 - Matrix._12 * Matrix._21;
}

Mat2 Cut(const Mat3& Mat, int row, int col) {
	Mat2 result;
	int index = 0;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == row || j == col) {
				continue;
			}
			result.asArray[index++] = Mat.asArray[3 * i + j];
		}
	}

	return result;
}

Mat3 Cut(const Mat4& Mat, int row, int col) {
	Mat3 result;
	int index = 0;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == row || j == col) {
				continue;
			}
			result.asArray[index++] = Mat.asArray[4 * i + j];
		}
	}

	return result;
}

Mat3 Minor(const Mat3& Mat) {
	Mat3 result;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result[i][j] = Determinant(Cut(Mat, i, j));
		}
	}

	return result;
}

Mat2 Minor(const Mat2& Mat) {
	return Mat2(
		Mat._22, Mat._21,
		Mat._12, Mat._11
	);
}

void Cofactor(float* out, const float* minor, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			out[cols * j + i] = minor[cols * j + i] * powf(-1.0f, i + j);
		}
	}
}

Mat2 Cofactor(const Mat2& Mat) {
	Mat2 result;
	Cofactor(result.asArray, Minor(Mat).asArray, 2, 2);
	return result;
}

Mat3 Cofactor(const Mat3& Mat) {
	Mat3 result;
	Cofactor(result.asArray, Minor(Mat).asArray, 3, 3);
	return result;
}

float Determinant(const Mat3& Mat) {
	float result = 0.0f;

	/*float A = Mat.asArray[3 * 0 + 0] * Determinant(Cut(Mat, 0, 0));
	float B = Mat.asArray[3 * 0 + 1] * Determinant(Cut(Mat, 0, 1));
	float C = Mat.asArray[3 * 0 + 2] * Determinant(Cut(Mat, 0, 2));
	result = A - B + C;*/

	/*for (int j = 0; j < 3; ++j) {
		result += Mat.asArray[3 * 0 + j] * Determinant(Cut(Mat, 0, j)) * powf(-1, 0 + j);
	}*/

	Mat3 cofactor = Cofactor(Mat);
	for (int j = 0; j < 3; ++j) {
		result += Mat.asArray[3 * 0 + j] * cofactor[0][j];
	}

	return result;
}

Mat4 Minor(const Mat4& Mat) {
	Mat4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result[i][j] = Determinant(Cut(Mat, i, j));
		}
	}

	return result;
}

Mat4 Cofactor(const Mat4& Mat) {
	Mat4 result;
	Cofactor(result.asArray, Minor(Mat).asArray, 4, 4);
	return result;
}

float Determinant(const Mat4& Mat) {
	float result = 0.0f;

	Mat4 cofactor = Cofactor(Mat);
	for (int j = 0; j < 4; ++j) {
		result += Mat.asArray[4 * 0 + j] * cofactor[0][j];
	}

	return result;
}

Mat2 Adjugate(const Mat2& Mat) {
	return Transpose(Cofactor(Mat));
}

Mat3 Adjugate(const Mat3& Mat) {
	return Transpose(Cofactor(Mat));
}

Mat4 Adjugate(const Mat4& Mat) {
	return Transpose(Cofactor(Mat));
}

Mat2 Inverse(const Mat2& Mat) {
	float det = Determinant(Mat);
	if (CMP(det, 0.0f)) { return Mat2(); }
	return Adjugate(Mat) * (1.0f / det);

	/*float det = Mat._11 * Mat._22 - Mat._12 * Mat._21;
	if (CMP(det, 0.0f)) {
		return Mat2();
	}
	float i_det = 1.0f / det;
	Mat2 result;
	result._11 =  Mat._22 * i_det;
	result._12 = -Mat._12 * i_det;
	result._21 = -Mat._21 * i_det;
	result._22 =  Mat._11 * i_det;
	return result;*/
}

Mat3 Inverse(const Mat3& Mat) {
	float det = Determinant(Mat);
	if (CMP(det, 0.0f)) { return Mat3(); }
	return Adjugate(Mat) * (1.0f / det);
}

Mat4 Inverse(const Mat4& m) {
	/*float det = Determinant(m);
	if (CMP(det, 0.0f)) { return Mat4(); }
	return Adjugate(m) * (1.0f / det);*/

	// The code below is the expanded form of the above equation.
	// This optimization avoids loops and function calls

	float det
		= m._11 * m._22 * m._33 * m._44 + m._11 * m._23 * m._34 * m._42 + m._11 * m._24 * m._32 * m._43
		+ m._12 * m._21 * m._34 * m._43 + m._12 * m._23 * m._31 * m._44 + m._12 * m._24 * m._33 * m._41
		+ m._13 * m._21 * m._32 * m._44 + m._13 * m._22 * m._34 * m._41 + m._13 * m._24 * m._31 * m._42
		+ m._14 * m._21 * m._33 * m._42 + m._14 * m._22 * m._31 * m._43 + m._14 * m._23 * m._32 * m._41
		- m._11 * m._22 * m._34 * m._43 - m._11 * m._23 * m._32 * m._44 - m._11 * m._24 * m._33 * m._42
		- m._12 * m._21 * m._33 * m._44 - m._12 * m._23 * m._34 * m._41 - m._12 * m._24 * m._31 * m._43
		- m._13 * m._21 * m._34 * m._42 - m._13 * m._22 * m._31 * m._44 - m._13 * m._24 * m._32 * m._41
		- m._14 * m._21 * m._32 * m._43 - m._14 * m._22 * m._33 * m._41 - m._14 * m._23 * m._31 * m._42;

	if (CMP(det, 0.0f)) {
		return Mat4();
	}
	float i_det = 1.0f / det;

	Mat4 result;
	result._11 = (m._22 * m._33 * m._44 + m._23 * m._34 * m._42 + m._24 * m._32 * m._43 - m._22 * m._34 * m._43 - m._23 * m._32 * m._44 - m._24 * m._33 * m._42) * i_det;
	result._12 = (m._12 * m._34 * m._43 + m._13 * m._32 * m._44 + m._14 * m._33 * m._42 - m._12 * m._33 * m._44 - m._13 * m._34 * m._42 - m._14 * m._32 * m._43) * i_det;
	result._13 = (m._12 * m._23 * m._44 + m._13 * m._24 * m._42 + m._14 * m._22 * m._43 - m._12 * m._24 * m._43 - m._13 * m._22 * m._44 - m._14 * m._23 * m._42) * i_det;
	result._14 = (m._12 * m._24 * m._33 + m._13 * m._22 * m._34 + m._14 * m._23 * m._32 - m._12 * m._23 * m._34 - m._13 * m._24 * m._32 - m._14 * m._22 * m._33) * i_det;
	result._21 = (m._21 * m._34 * m._43 + m._23 * m._31 * m._44 + m._24 * m._33 * m._41 - m._21 * m._33 * m._44 - m._23 * m._34 * m._41 - m._24 * m._31 * m._43) * i_det;
	result._22 = (m._11 * m._33 * m._44 + m._13 * m._34 * m._41 + m._14 * m._31 * m._43 - m._11 * m._34 * m._43 - m._13 * m._31 * m._44 - m._14 * m._33 * m._41) * i_det;
	result._23 = (m._11 * m._24 * m._43 + m._13 * m._21 * m._44 + m._14 * m._23 * m._41 - m._11 * m._23 * m._44 - m._13 * m._24 * m._41 - m._14 * m._21 * m._43) * i_det;
	result._24 = (m._11 * m._23 * m._34 + m._13 * m._24 * m._31 + m._14 * m._21 * m._33 - m._11 * m._24 * m._33 - m._13 * m._21 * m._34 - m._14 * m._23 * m._31) * i_det;
	result._31 = (m._21 * m._32 * m._44 + m._22 * m._34 * m._41 + m._24 * m._31 * m._42 - m._21 * m._34 * m._42 - m._22 * m._31 * m._44 - m._24 * m._32 * m._41) * i_det;
	result._32 = (m._11 * m._34 * m._42 + m._12 * m._31 * m._44 + m._14 * m._32 * m._41 - m._11 * m._32 * m._44 - m._12 * m._34 * m._41 - m._14 * m._31 * m._42) * i_det;
	result._33 = (m._11 * m._22 * m._44 + m._12 * m._24 * m._41 + m._14 * m._21 * m._42 - m._11 * m._24 * m._42 - m._12 * m._21 * m._44 - m._14 * m._22 * m._41) * i_det;
	result._34 = (m._11 * m._24 * m._32 + m._12 * m._21 * m._34 + m._14 * m._22 * m._31 - m._11 * m._22 * m._34 - m._12 * m._24 * m._31 - m._14 * m._21 * m._32) * i_det;
	result._41 = (m._21 * m._33 * m._42 + m._22 * m._31 * m._43 + m._23 * m._32 * m._41 - m._21 * m._32 * m._43 - m._22 * m._33 * m._41 - m._23 * m._31 * m._42) * i_det;
	result._42 = (m._11 * m._32 * m._43 + m._12 * m._33 * m._41 + m._13 * m._31 * m._42 - m._11 * m._33 * m._42 - m._12 * m._31 * m._43 - m._13 * m._32 * m._41) * i_det;
	result._43 = (m._11 * m._23 * m._42 + m._12 * m._21 * m._43 + m._13 * m._22 * m._41 - m._11 * m._22 * m._43 - m._12 * m._23 * m._41 - m._13 * m._21 * m._42) * i_det;
	result._44 = (m._11 * m._22 * m._33 + m._12 * m._23 * m._31 + m._13 * m._21 * m._32 - m._11 * m._23 * m._32 - m._12 * m._21 * m._33 - m._13 * m._22 * m._31) * i_det;

	/*if (result * m != Mat4()) {
		std::cout << "ERROR! Expecting Matrix x inverse to equal identity!\n";
	}*/

	return result;
}

Mat4 ToColumnMajor(const Mat4& Mat) {
	return Transpose(Mat);
}

Mat3 ToColumnMajor(const Mat3& Mat) {
	return Transpose(Mat);
}

Mat4 FromColumnMajor(const Mat4& Mat) {
	return Transpose(Mat);
}

Mat3 FromColumnMajor(const Mat3& Mat) {
	return Transpose(Mat);
}

Mat4 FromColumnMajor(const float* Mat) {
	return Transpose(Mat4(
		Mat[0], Mat[1], Mat[2], Mat[3],
		Mat[4], Mat[5], Mat[6], Mat[7],
		Mat[8], Mat[9], Mat[10], Mat[11],
		Mat[12], Mat[13], Mat[14], Mat[15]
	));
}

Mat4 Translation(float x, float y, float z) {
	return Mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f
	);
}
Mat4 Translation(const Vec3& pos) {
	return Mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		pos.x, pos.y, pos.z, 1.0f
	);
}

Mat4 Translate(float x, float y, float z) {
	return Mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f
	);
}

Mat4 Translate(const Vec3& pos) {
	return Mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		pos.x, pos.y, pos.z, 1.0f
	);
}

Mat4 FromMat3(const Mat3& Mat) {
	Mat4 result;

	result._11 = Mat._11;
	result._12 = Mat._12;
	result._13 = Mat._13;

	result._21 = Mat._21;
	result._22 = Mat._22;
	result._23 = Mat._23;

	result._31 = Mat._31;
	result._32 = Mat._32;
	result._33 = Mat._33;

	return result;
}

Vec3 GetTranslation(const Mat4& Mat) {
	return Vec3(Mat._41, Mat._42, Mat._43);
}

Mat4 Scale(float x, float y, float z) {
	return Mat4(
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Mat4 Scale(const Vec3& Vec) {
	return Mat4(
		Vec.x, 0.0f, 0.0f, 0.0f,
		0.0f, Vec.y, 0.0f, 0.0f,
		0.0f, 0.0f, Vec.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Vec3 GetScale(const Mat4& Mat) {
	return Vec3(Mat._11, Mat._22, Mat._33);
}

Mat4 Rotation(float pitch, float yaw, float roll) {
	return  ZRotation(roll) * XRotation(pitch) * YRotation(yaw);
}

Mat3 Rotation3x3(float pitch, float yaw, float roll) {
	return ZRotation3x3(roll) * XRotation3x3(pitch) * YRotation3x3(yaw);
}

Mat2 Rotation2x2(float angle) {
	return Mat2(
		cosf(angle), sinf(angle),
		-sinf(angle), cosf(angle)
	);
}

Mat4 YawPitchRoll(float yaw, float pitch, float roll) {
	yaw = DEG2RAD(yaw);
	pitch = DEG2RAD(pitch);
	roll = DEG2RAD(roll);

	Mat4 out; // z * x * y
	out._11 = (cosf(roll) * cosf(yaw)) + (sinf(roll) * sinf(pitch) * sinf(yaw));
	out._12 = (sinf(roll) * cosf(pitch));
	out._13 = (cosf(roll) * -sinf(yaw)) + (sinf(roll) * sinf(pitch) * cosf(yaw));
	out._21 = (-sinf(roll) * cosf(yaw)) + (cosf(roll) * sinf(pitch) * sinf(yaw));
	out._22 = (cosf(roll) * cosf(pitch));
	out._23 = (sinf(roll) * sinf(yaw)) + (cosf(roll) * sinf(pitch) * cosf(yaw));
	out._31 = (cosf(pitch) * sinf(yaw));
	out._32 = -sinf(pitch);
	out._33 = (cosf(pitch) * cosf(yaw));
	out._44 = 1;
	return out;
}

Mat4 XRotation(float angle) {
	angle = DEG2RAD(angle);
	return Mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosf(angle), sinf(angle), 0.0f,
		0.0f, -sinf(angle), cosf(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Mat3 XRotation3x3(float angle) {
	angle = DEG2RAD(angle);
	return Mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, cosf(angle), sinf(angle),
		0.0f, -sinf(angle), cosf(angle)
	);
}

Mat4 YRotation(float angle) {
	angle = DEG2RAD(angle);
	return Mat4(
		cosf(angle), 0.0f, -sinf(angle), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sinf(angle), 0.0f, cosf(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Mat3 YRotation3x3(float angle) {
	angle = DEG2RAD(angle);
	return Mat3(
		cosf(angle), 0.0f, -sinf(angle),
		0.0f, 1.0f, 0.0f,
		sinf(angle), 0.0f, cosf(angle)
	);
}

Mat4 ZRotation(float angle) {
	angle = DEG2RAD(angle);
	return Mat4(
		cosf(angle), sinf(angle), 0.0f, 0.0f,
		-sinf(angle), cosf(angle), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Mat3 ZRotation3x3(float angle) {
	angle = DEG2RAD(angle);
	return Mat3(
		cosf(angle), sinf(angle), 0.0f,
		-sinf(angle), cosf(angle), 0.0f,
		0.0f, 0.0f, 1.0f
	);
}

Mat4 Orthogonalize(const Mat4& Mat) {
	Vec3 xAxis(Mat._11, Mat._12, Mat._13);
	Vec3 yAxis(Mat._21, Mat._22, Mat._23);
	Vec3 zAxis = xAxis.cross(yAxis);

	xAxis = yAxis.cross(zAxis);
	yAxis = zAxis.cross(xAxis);
	zAxis = xAxis.cross(yAxis);

	return Mat4(
		xAxis.x, xAxis.y, xAxis.z, Mat._14,
		yAxis.x, yAxis.y, yAxis.z, Mat._24,
		zAxis.x, zAxis.y, zAxis.z, Mat._34,
		Mat._41, Mat._42, Mat._43, Mat._44
	);
}

Mat3 Orthogonalize(const Mat3& Mat) {
	Vec3 xAxis(Mat._11, Mat._12, Mat._13);
	Vec3 yAxis(Mat._21, Mat._22, Mat._23);
	Vec3 zAxis = xAxis.cross(yAxis);

	xAxis = yAxis.cross(zAxis);
	yAxis = zAxis.cross(xAxis);
	zAxis = xAxis.cross(yAxis);

	return Mat3(
		xAxis.x, xAxis.y, xAxis.z,
		yAxis.x, yAxis.y, yAxis.z,
		zAxis.x, zAxis.y, zAxis.z
	);
}

Mat4 AxisAngle(Vec3& axis, float angle) {
	angle = DEG2RAD(angle);
	float c = cosf(angle);
	float s = sinf(angle);
	float t = 1.0f - cosf(angle);

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	if (!CMP(axis.magnitudeSq(), 1.0f)) {
		float inv_len = 1.0f / axis.magnitude();
		x *= inv_len;
		y *= inv_len;
		z *= inv_len;
	}

	return Mat4(
		t * (x * x) + c, t * x * y + s * z, t * x * z - s * y, 0.0f,
		t * x * y - s * z, t * (y * y) + c, t * y * z + s * x, 0.0f,
		t * x * z + s * y, t * y * z - s * x, t * (z * z) + c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Mat3 AxisAngle3x3(Vec3& axis, float angle) {
	angle = DEG2RAD(angle);
	float c = cosf(angle);
	float s = sinf(angle);
	float t = 1.0f - cosf(angle);

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	if (!CMP(axis.magnitudeSq(), 1.0f)) {
		float inv_len = 1.0f / axis.magnitude();
		x *= inv_len;
		y *= inv_len;
		z *= inv_len;
	}

	return Mat3(
		t * (x * x) + c, t * x * y + s * z, t * x * z - s * y,
		t * x * y - s * z, t * (y * y) + c, t * y * z + s * x,
		t * x * z + s * y, t * y * z - s * x, t * (z * z) + c
	);
}

Vec3 MultiplyPoint(const Vec3& Vec, const Mat4& Mat) {
	Vec3 result;
	result.x = Vec.x * Mat._11 + Vec.y * Mat._21 + Vec.z * Mat._31 + 1.0f * Mat._41;
	result.y = Vec.x * Mat._12 + Vec.y * Mat._22 + Vec.z * Mat._32 + 1.0f * Mat._42;
	result.z = Vec.x * Mat._13 + Vec.y * Mat._23 + Vec.z * Mat._33 + 1.0f * Mat._43;
	return result;
}

Vec3 MultiplyVector(const Vec3& Vec, const Mat4& Mat) {
	Vec3 result;
	result.x = Vec.x * Mat._11 + Vec.y * Mat._21 + Vec.z * Mat._31 + 0.0f * Mat._41;
	result.y = Vec.x * Mat._12 + Vec.y * Mat._22 + Vec.z * Mat._32 + 0.0f * Mat._42;
	result.z = Vec.x * Mat._13 + Vec.y * Mat._23 + Vec.z * Mat._33 + 0.0f * Mat._43;
	return result;
}

Vec3 MultiplyVector(Vec3& Vec, const Mat3& Mat) {
	Vec3 result;
	result.x = Vec.dot(Vec3{ Mat._11, Mat._21, Mat._31 });
	result.y = Vec.dot(Vec3{ Mat._12, Mat._22, Mat._32 });
	result.z = Vec.dot(Vec3{ Mat._13, Mat._23, Mat._33 });
	return result;
}

Mat4 Transform(const Vec3& scale, const Vec3& eulerRotation, const Vec3& translate) {
	return Scale(scale) *
		Rotation(eulerRotation.x, eulerRotation.y, eulerRotation.z) *
		Translation(translate);
}

Mat4 Transform(const Vec3& scale, Vec3& rotationAxis, float rotationAngle, const Vec3& translate) {
	return Scale(scale) *
		AxisAngle(rotationAxis, rotationAngle) *
		Translation(translate);
}

Mat4 LookAt(Vec3& position, Vec3& target, Vec3& up) {
	Vec3 forward = (target - position).getNormal();
	Vec3 right = up.cross(forward).getNormal();
	Vec3 newUp = forward.cross(right);

	return Mat4(
		right.x, newUp.x, forward.x, 0.0f,
		right.y, newUp.y, forward.y, 0.0f,
		right.z, newUp.z, forward.z, 0.0f,
		-right.dot(position), -newUp.dot(position), -forward.dot(position), 1.0f
	);
}

Mat4 Projection(float fov, float aspect, float zNear, float zFar) {
	float tanHalfFov = tanf(DEG2RAD((fov * 0.5f)));
	float fovY = 1.0f / tanHalfFov; // cot(fov/2)
	float fovX = fovY / aspect; // cot(fov/2) / aspect

	Mat4 result;

	result._11 = fovX;
	result._22 = fovY;
	result._33 = zFar / (zFar - zNear); // far / range
	result._34 = 1.0f;
	result._43 = -zNear * result._33; // - near * (far / range)
	result._44 = 0.0f;

	return result;
}

Mat4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
	float _11 = 2.0f / (right - left);
	float _22 = 2.0f / (top - bottom);
	float _33 = 1.0f / (zFar - zNear);
	float _41 = (left + right) / (left - right);
	float _42 = (top + bottom) / (bottom - top);
	float _43 = (zNear) / (zNear - zFar);

	return Mat4(
		_11, 0.0f, 0.0f, 0.0f,
		0.0f, _22, 0.0f, 0.0f,
		0.0f, 0.0f, _33, 0.0f,
		_41, _42, _43, 1.0f
	);
}

Vec3 Decompose(const Mat3& rot1) {
	Mat3 rot = Transpose(rot1);

	float sy = sqrt(rot._11 * rot._11 + rot._21 * rot._21);

	bool singular = sy < 1e-6;

	float x, y, z;
	if (!singular) {
		x = atan2(rot._32, rot._33);
		y = atan2(-rot._31, sy);
		z = atan2(rot._21, rot._11);
	}
	else {
		x = atan2(-rot._23, rot._22);
		y = atan2(-rot._31, sy);
		z = 0;
	}

	return Vec3(x, y, z);
}
