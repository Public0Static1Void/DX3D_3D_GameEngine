#pragma once
#include <iostream>
#include <DX3D/Core/Core.h>
#include <DX3D/Math/Vector3.h>
#include <DX3D/Math/Vector4.h>

namespace dx3d {
	inline constexpr f32 Pi = 3.14159265358979323846f;
	inline constexpr f32 ToRadians(f32 degrees) { return degrees * (Pi / 180.0f); }

	class Matrix4x4 {
	public:
		Matrix4x4() {
			rows[0][0] = rows[1][1] = rows[2][2] = rows[3][3] = 1.0f;
		}

		Matrix4x4 operator*(const Matrix4x4& rhs) const {
			Matrix4x4 result;
			for (ui32 row = 0; row < 4; ++row) {
				for (ui32 col = 0; col < 4; ++col) {
					f32 sum = 0.0f;
					for (ui32 k = 0; k < 4; ++k) {
						sum += rows[row][k] * rhs.rows[k][col];
					}
					result.rows[row][col] = sum;
				}
			}
			return result;
		}

		friend Vector4 operator*(const Vector4& v, const Matrix4x4& matrix) {
			Vector4 result;
			for (ui32 col = 0; col < 4; ++col) {
				f32 sum = 0.0f;
				for (ui32 k = 0; k < 4; ++k)
					sum += v[k] * matrix.rows[k][col];
				result[col] = sum;
			}
			return result;
		}

		static Matrix4x4 RotationY(f32 angle) {
			const f32 c = std::cos(angle), s = std::sin(angle);
			Matrix4x4 r;
			r.rows[0][0] = c; r.rows[0][2] = -s;
			r.rows[2][0] = s; r.rows[2][2] = c;
			return r;
		}

		static Matrix4x4 RotationX(f32 angle) {
			const f32 c = std::cos(angle), s = std::sin(angle);
			Matrix4x4 r;
			r.rows[1][1] = c; r.rows[1][2] = s;
			r.rows[2][1] = -s; r.rows[2][2] = c;
			return r;
		}

		static Matrix4x4 LookAtLH(const Vector3& eye, const Vector3& target, const Vector3& up) {
			const Vector3 zAxis = (target - eye).Normalized();
			const Vector3 xAxis = Vector3::Cross(up, zAxis);
			const Vector3 yAxis = Vector3::Cross(zAxis, xAxis);

			Matrix4x4 r;
			r.rows[0][0] = xAxis.x; r.rows[0][1] = yAxis.x; r.rows[0][2] = zAxis.x;
			r.rows[1][0] = xAxis.y; r.rows[1][1] = yAxis.y; r.rows[1][2] = zAxis.y;
			r.rows[2][0] = xAxis.z; r.rows[2][1] = yAxis.z; r.rows[2][2] = zAxis.z;
			r.rows[3][0] = -Vector3::Dot(xAxis, eye);
			r.rows[3][1] = -Vector3::Dot(yAxis, eye);
			r.rows[3][2] = -Vector3::Dot(zAxis, eye);
			return r;
		}

		static Matrix4x4 PerspectiveFovLH(f32 fovY, f32 aspectRatio, f32 nearZ, f32 farZ) {
			const f32 h = 1.0f / std::tan(fovY * 0.5f);
			const f32 w = h / aspectRatio;
			const f32 range = farZ / (farZ - nearZ);

			Matrix4x4 r;
			r.rows[0][0] = w;
			r.rows[1][1] = h;
			r.rows[2][2] = range;
			r.rows[2][3] = 1.0f;
			r.rows[3][2] = -range * nearZ;
			r.rows[3][3] = 0.0f;
			return r;
		}

		Vector4 rows[4]{};
	};
}