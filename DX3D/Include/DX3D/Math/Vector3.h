#pragma once
#include <iostream>
#include <DX3D/Core/Core.h>

namespace dx3d {
	class Vector3 {
	public:
		Vector3() = default;
		Vector3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}

		Vector3 operator-(const Vector3& other) const { return { x - other.x, y - other.y, z - other.z }; }

		static f32 Dot(const Vector3& a, const Vector3& b) {
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		static Vector3 Cross(const Vector3& a, const Vector3& b) {
			return {
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.z * b.y - a.y * b.x
			};
		}

		Vector3 Normalized() const {
			const f32 length = std::sqrt(Dot(*this, *this));
			return length > 0.0f ? Vector3{ x / length, y / length, z / length } : *this;
		}
	public:
		f32 x{}, y{}, z{};
	};
}
