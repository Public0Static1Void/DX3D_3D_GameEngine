#pragma once
#include <DX3D/Core/base.h>
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Common.h>
#include <DX3D/Math/Vector3.h>
#include <DX3D/Math/Vector4.h>
#include <DX3D/Math/Matrix4x4.h>

namespace dx3d {
	class GraphicsEngine final : public Base // Final prevents the class to be further edited
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		GraphicsDevice& getGraphicsDevice() noexcept;

		void update(f32 deltaTime);
		void render(SwapChain& swapChain);

	private:
		struct Vertex {
			Vector3 position;
			Vector4 color;
		};
	private:
		std::shared_ptr<GraphicsDevice> m_graphicsDevice{};
		DeviceContextPtr m_deviceContext{};
		GraphicsPipelineStatePtr m_pipeline{};
		VertexBufferPtr m_vb{};
		IndexBufferPtr m_ib{};
		ConstantBufferPtr m_transformCB{};
		f32 m_elapsedTime{};
	};
}
