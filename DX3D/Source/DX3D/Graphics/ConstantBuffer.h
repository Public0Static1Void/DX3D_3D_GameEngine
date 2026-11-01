#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d {
	class ConstantBuffer final : public GraphicsResource
	{
	public:
		ConstantBuffer(const ConstantBufferDesc& desc, const GraphicsResourceDesc& gDesc);
		ui32 getDataSize() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};
		ui32 m_dataSize{};
		friend class DeviceContext;
	};
}