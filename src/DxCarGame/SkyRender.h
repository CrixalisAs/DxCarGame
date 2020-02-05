#ifndef SKYRENDER_H
#define SKYRENDER_H

#include <vector>
#include <string>
#include "Effects.h"
#include "Camera.h"

class SkyRender
{
public:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;


	// 需要提供完整的天空盒贴图 或者 已经创建好的天空盒纹理.dds文件
	SkyRender(ID3D11Device * device, 
		ID3D11DeviceContext * deviceContext, 
		const std::wstring& cubemapFilename, 
		float skySphereRadius,		// 天空球半径
		bool generateMips = false);	// 默认不为静态天空盒生成mipmaps


	// 需要提供天空盒的六张正方形贴图
	SkyRender(ID3D11Device * device, 
		ID3D11DeviceContext * deviceContext, 
		const std::vector<std::wstring>& cubemapFilenames, 
		float skySphereRadius,		// 天空球半径
		bool generateMips = false);	// 默认不为静态天空盒生成mipmaps


	ID3D11ShaderResourceView * GetTextureCube();

	void Draw(ComPtr<ID3D11DeviceContext> deviceContext, SkyEffect& skyEffect, const Camera& camera);

	// 设置调试对象名
	void SetDebugObjectName(const std::string& name);

private:
	void InitResource(ID3D11Device * device, float skySphereRadius);

private:
	ComPtr<ID3D11Buffer> m_pVertexBuffer;
	ComPtr<ID3D11Buffer> m_pIndexBuffer;

	UINT m_IndexCount;

	ComPtr<ID3D11ShaderResourceView> m_pTextureCubeSRV;
};

#endif