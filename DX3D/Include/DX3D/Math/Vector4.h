#pragma once
#include <DX3D/Core/Core.h>

namespace dx3d {
	class Vector4 {
	public:
		Vector4() = default;
		Vector4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}

		// Lets you write v[0], v[1]...
		f32& operator[](ui32 i) { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; };
		const f32& operator[](ui32 i) const { return i == 0 ? x : i == 1 ? y : i == 2 ? z : w; };
	public:
		f32 x{}, y{}, z{}, w{};
	};
}
