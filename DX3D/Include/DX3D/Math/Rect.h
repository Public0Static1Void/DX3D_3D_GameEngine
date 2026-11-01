#pragma once
#include "Core.h"

namespace dx3d {
	class Rect {
	public:
		Rect() = default;
		Rect(i32 width, i32 heigth) : left(0), top(0), width(width), heigth(heigth) {}
		Rect(i32 left, i32 top, i32 width, i32 heigth) : left(left), top(top), width(width), heigth(heigth) {}
	public:
		i32 left{}, top{}, width{}, heigth{};
	};
}
