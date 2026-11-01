#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Math/Vector3.h>
#include <fstream>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc) : Base(desc.base)
{
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{ m_Logger });

	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();


	constexpr char shaderFilePath[] = "DX3D/Assets/Shaders/Basic.hlsl";
	std::ifstream shaderStream(shaderFilePath);
	if (!shaderStream) DX3DLogThrowError("Failed to open the shader file");
	std::string shaderFileData{
		std::istreambuf_iterator<char>(shaderStream),
		std::istreambuf_iterator<char>()
	};

	auto shaderSourceCode = shaderFileData.c_str();
	auto shaderSourceCodeSize = shaderFileData.length();

	auto vs = device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize,
		"VSMain", ShaderType::VertexShader});
	auto ps = device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize,
		"PSMain", ShaderType::PixelShader});
	auto vsSig = device.createVertexShaderSignature({ vs });

	m_pipeline = device.createGraphicsPipelineState({ *vsSig, *ps });

	const Vertex vertexList[] = {
		{ {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f} }, // 0 red
		{ {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} }, // 1 green
		{ { 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f} }, // 2 blue
		{ { 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} }, // 3 yellow
		{ {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} }, // 4 magenta
		{ {-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f, 1.0f} }, // 5 cyan
		{ { 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} }, // 6 white
		{ { 0.5f, -0.5f,  0.5f}, {1.0f, 0.5f, 0.0f, 1.0f} }  // 7 orange
	};
	// size -> list size
	// sizeof -> Class bits size
	m_vb = device.createVertexBuffer({ vertexList, std::size(vertexList), sizeof(Vertex) });

	const ui32 indexList[] = {
		0, 1, 2,  0, 2, 3, // Front  (-Z)
		7, 6, 5,  7, 5, 4, // Back   (+Z)
		4, 5, 1,  4, 1, 0, // Left   (-X)
		3, 2, 6,  3, 6, 7, // Right  (+X)
		1, 5, 6,  1, 6, 2, // Top    (+Y)
		0, 3, 7,  0, 7, 4  // Bottom (-Y)
	};
	m_ib = device.createIndexBuffer({ indexList, std::size(indexList) });

	const Matrix4x4 identity{};
	m_transformCB = device.createConstantBuffer({ &identity, sizeof(Matrix4x4) });
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
	return *m_graphicsDevice;
}

void dx3d::GraphicsEngine::update(f32 deltaTime)
{
	m_elapsedTime += deltaTime;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain)
{
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.27f, 0.27f, 0.27f });
	context.setGraphicsPipelineState(*m_pipeline);

	const auto size = swapChain.getSize();
	context.setViewportSize(size);

	const f32 aspectRatio = static_cast<f32>(size.width) / static_cast<f32>(size.heigth > 0 ? size.heigth : 1);
	const auto world = Matrix4x4::RotationX(m_elapsedTime * 0.6f) * Matrix4x4::RotationY(m_elapsedTime * 0.9f);
	const auto view = Matrix4x4::LookAtLH({ 0.0f, 0.0f, -2.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
	const auto projection = Matrix4x4::PerspectiveFovLH(ToRadians(60.0f), aspectRatio, 0.1f, 100.0f);
	const auto worldViewProj = world * view * projection;

	context.updateConstantBuffer(*m_transformCB, &worldViewProj);
	context.setVertexShaderConstantBuffer(*m_transformCB);

	context.setVertexBuffer(*m_vb);
	context.setIndexBuffer(*m_ib);
	context.drawIndexedTriangleList(m_ib->getIndexListSize(), 0u, 0);

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present(true);
}
