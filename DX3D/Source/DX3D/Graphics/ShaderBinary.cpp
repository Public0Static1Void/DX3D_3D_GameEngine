#include "ShaderBinary.h"
#include "GraphicsUtils.h"
#include <d3dcompiler.h>

dx3d::ShaderBinary::ShaderBinary(const ShaderCompileDesc& desc, const GraphicsResourceDesc& gDesc) :
	GraphicsResource(gDesc), m_type(desc.shaderType)
{
	if (!desc.shaderSourceName) DX3DLogThrowInvalidArg("No shader name passed as an argument");
	if (!desc.shaderSourceCode) DX3DLogThrowInvalidArg("No shader source code passed as an argument");
	if (!desc.shaderSourceCodeSize) DX3DLogThrowInvalidArg("No shader source code size passed as an argument");
	if (!desc.shaderEntryPoint) DX3DLogThrowInvalidArg("No shader entry point passed as an argument");

	UINT compileFlags{};

#ifdef _DEBUG
	compileFlags |= D3DCOMPILE_DEBUG;
#endif

	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob{}; // Stores the errors messages
	DX3DGraphicsCheckShaderCompile(
		D3DCompile(
			desc.shaderSourceCode,
			desc.shaderSourceCodeSize,
			desc.shaderSourceName,
			nullptr, // Used for macros
			nullptr,
			desc.shaderEntryPoint,
			dx3d::GraphicsUtils::GetShaderModelTarget(desc.shaderType),
			compileFlags,
			0,
			&m_blob,
			&errorBlob
		),
		errorBlob.Get()
	);
	
}

dx3d::BinaryData dx3d::ShaderBinary::getData() const noexcept
{
	return {
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize()
	};
}

dx3d::ShaderType dx3d::ShaderBinary::getType() const noexcept
{
	return m_type;
}
