#include <DX3D/Game/Game.h>
#include <DX3D/Window/Win32/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>

dx3d::Game::Game(const GameDesc& desc) :
		Base({ *std::make_unique<Logger>(desc.logLevel).release()}),
		m_loggerPtr(&m_Logger)
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{ m_Logger });
	m_display = std::make_unique<Display>(DisplayDesc{ {m_Logger, desc.windowSize}, m_graphicsEngine->getGraphicsDevice() });

	m_previousTime = std::chrono::steady_clock::now();

	DX3DLogInfo("Game initialized");
}

dx3d::Game::~Game()
{
	DX3DLogInfo("Game is shutting down...");
}

void dx3d::Game::onInternalUpdate()
{
	const auto now = std::chrono::steady_clock::now();
	const f32 deltaTime = std::chrono::duration<f32>(now - m_previousTime).count();
	m_previousTime = now;

	m_graphicsEngine->update(deltaTime);
	m_graphicsEngine->render(m_display->getSwapChain());
}