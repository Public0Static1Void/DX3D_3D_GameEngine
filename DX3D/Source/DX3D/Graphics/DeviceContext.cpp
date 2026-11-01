#include "DeviceContext.h"
#include "SwapChain.h"
#include "GraphicsPipelineState.h"
#include "VertexBuffer.h"

dx3d::DeviceContext::DeviceContext(const GraphicsResourceDesc& gDesc) : GraphicsResource(gDesc)
{
	DX3DGraphicsLogThrowOnFail(
		m_device.CreateDeferredContext(0, &m_context),
		"CreateDefferredContext "
	);
}

void dx3d::DeviceContext::clearAndSetBackBuffer(const SwapChain& swapChain, const Vector4& color)
{
	f32 fColor[] = { color.x, color.y, color.z, color.w };
	auto rtv = swapChain.m_rtv.Get();
	auto dsv = swapChain.m_dsv.Get();
	m_context->ClearRenderTargetView(swapChain.m_rtv.Get(), fColor);
	m_context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_context->OMSetRenderTargets(1, &rtv, dsv);
}

void dx3d::DeviceContext::setGraphicsPipelineState(const GraphicsPipelineState& pipeline)
{
	m_context->IASetInputLayout(pipeline.m_layout.Get());
	m_context->VSSetShader(pipeline.m_vs.Get(), nullptr, 0);
	m_context->PSSetShader(pipeline.m_ps.Get(), nullptr, 0);
}

void dx3d::DeviceContext::setVertexBuffer(const VertexBuffer& buffer)
{
	auto stride = buffer.m_vertexSize;
	auto buf = buffer.m_buffer.Get();
	auto offset = 0u;
	m_context->IASetVertexBuffers(0, 1, &buf, &stride, &offset);
}

void dx3d::DeviceContext::setViewportSize(const Rect& size)
{
	D3D11_VIEWPORT vp{};
	vp.Width = static_cast<f32>(size.width);
	vp.Height = static_cast<f32>(size.heigth);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_context->RSSetViewports(1, &vp);
}

void dx3d::DeviceContext::drawTriangleList(ui32 vertexCount, ui32 startVertexLocation)
{
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_context->Draw(vertexCount, startVertexLocation);
}

void dx3d::DeviceContext::setIndexBuffer(const IndexBuffer& buffer)
{
	m_context->IASetIndexBuffer(buffer.m_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void dx3d::DeviceContext::updateConstantBuffer(const ConstantBuffer& buffer, const void* data)
{
	m_context->UpdateSubresource(buffer.m_buffer.Get(), 0, nullptr, data, 0, 0);
}

void dx3d::DeviceContext::setVertexShaderConstantBuffer(const ConstantBuffer& buffer, ui32 slot)
{
	auto buf = buffer.m_buffer.Get();
	m_context->VSSetConstantBuffers(slot, 1, &buf);
}

void dx3d::DeviceContext::drawIndexedTriangleList(ui32 indexCount, ui32 startIndexLocation, i32 baseVertexLocation)
{
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_context->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}