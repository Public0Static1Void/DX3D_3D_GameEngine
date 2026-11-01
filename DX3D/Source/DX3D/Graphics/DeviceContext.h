#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Graphics/IndexBuffer.h>
#include <DX3D/Graphics/ConstantBuffer.h>
#include <DX3D/Math/Vector4.h>

namespace dx3d {
	class DeviceContext final : public GraphicsResource
	{
	public:
		explicit DeviceContext(const GraphicsResourceDesc& gDesc);
		void clearAndSetBackBuffer(const SwapChain& swapChain, const Vector4& color);
		void setGraphicsPipelineState(const GraphicsPipelineState& pipeline);
		void setVertexBuffer(const VertexBuffer& buffer);
		void setViewportSize(const Rect& size);
		void drawTriangleList(ui32 vertexCount, ui32 startVertexLocation);

		void setIndexBuffer(const IndexBuffer& buffer);
		void updateConstantBuffer(const ConstantBuffer& buffer, const void* data);
		void setVertexShaderConstantBuffer(const ConstantBuffer& buffer, ui32 slot = 0u);
		void drawIndexedTriangleList(ui32 indexCount, ui32 startIndexLocation, i32 baseVertexLocation);
	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context{};

		friend class GraphicsDevice;
	};
}