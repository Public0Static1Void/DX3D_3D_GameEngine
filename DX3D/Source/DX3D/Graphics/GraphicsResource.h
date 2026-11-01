#pragma once
#include <d3d11.h>
#include <wrl.h>

#include <DX3D/Core/base.h>
#include <DX3D/Core/Common.h>
#include "GraphicsLogsUtils.h"

namespace dx3d {
	struct GraphicsResourceDesc {
		BaseDesc base;
		std::shared_ptr<const GraphicsDevice> graphicsDevice;
		ID3D11Device& device;
		IDXGIFactory& factory;
	};

	class GraphicsResource : public Base {
	public:
		explicit GraphicsResource(const GraphicsResourceDesc& desc) : 
			Base(desc.base),
			m_graphicsDevice(desc.graphicsDevice),
			m_device(desc.device),
			m_factory(desc.factory)
		{}

	protected:
		std::shared_ptr<const GraphicsDevice> m_graphicsDevice;
		ID3D11Device& m_device;
		IDXGIFactory& m_factory;
	};
}
