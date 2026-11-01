#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Core.h>
#include <DX3D/Core/base.h>
#include "GraphicsResource.h"
#include "VertexBuffer.h"


namespace dx3d {
	class GraphicsDevice final : public Base, public std::enable_shared_from_this<GraphicsDevice>
	{
	public:
		explicit GraphicsDevice(const GraphicsDeviceDesc& desc);
		virtual ~GraphicsDevice() override;

		SwapChainPtr createSwapChain(const SwapChainDesc& desc);
		DeviceContextPtr createDeviceContext();
		ShaderBinaryPtr compileShader(const ShaderCompileDesc& desc) const;
		GraphicsPipelineStatePtr createGraphicsPipelineState(const GraphicsPipelineStateDesc& desc);
		VertexBufferPtr createVertexBuffer(const VertexBufferDesc& desc);
		VertexShaderSignaturePtr createVertexShaderSignature(const VertexShaderSignatureDesc& desc);
		IndexBufferPtr createIndexBuffer(const IndexBufferDesc& desc);
		ConstantBufferPtr createConstantBuffer(const ConstantBufferDesc& desc);

		void executeCommandList(DeviceContext& context);
	private:
		GraphicsResourceDesc getGraphicsResourceDesc() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext{};
		Microsoft::WRL::ComPtr<IDXGIDevice> m_dxgiDevice{};
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_dxgiAdapter{};
		Microsoft::WRL::ComPtr<IDXGIFactory> m_dxgiFactory{};
	};
}
