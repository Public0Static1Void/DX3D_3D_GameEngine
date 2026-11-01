#include "ConstantBuffer.h"

dx3d::ConstantBuffer::ConstantBuffer(const ConstantBufferDesc& desc, const GraphicsResourceDesc& gDesc)
	: GraphicsResource(gDesc), m_dataSize(desc.dataSize)
{
	if (!desc.dataSize) DX3DLogThrowInvalidArg("No constant buffer size passed as an argument");
	if (desc.dataSize % 16 != 0) DX3DLogThrowInvalidArg("Constant buffer size must be a multiple of 16 bytes");

	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = desc.dataSize;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; // The CPU owns the memory
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = desc.initialData;

	DX3DGraphicsLogThrowOnFail(
		m_device.CreateBuffer(&bufferDesc, desc.initialData ? &initData : nullptr, &m_buffer),
		"CreateVuffer (constant buffer) failed"
	);
}

dx3d::ui32 dx3d::ConstantBuffer::getDataSize() const noexcept {
	return m_dataSize;
}