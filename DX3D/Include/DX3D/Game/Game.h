#pragma once
#include <chrono>
#include <DX3D/Core/base.h>
#include <DX3D/Core/Core.h>

namespace dx3d {
	class Game: public Base
	{
	public:
		explicit Game(const GameDesc& desc);
		virtual ~Game() override;

		virtual void Run() final; // Final prevents further inheritance or modifications

	private:
		void onInternalUpdate(); // Where all the code that executes in one frame is
	private:
		std::unique_ptr<Logger> m_loggerPtr{};
		std::unique_ptr<GraphicsEngine> m_graphicsEngine{};
		std::unique_ptr<Display> m_display{};
		std::chrono::steady_clock::time_point m_previousTime{};
		bool m_isRunning{ true };
	};
}
