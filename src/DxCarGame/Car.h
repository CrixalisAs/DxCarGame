#ifndef CAR_H
#define CAR_H

#include <wrl/client.h>
#include "Effects.h"
#include "Collision.h"
#include <vector>
#include <stack>
#include "Geometry.h"
#include "LightHelper.h"

enum CarFaceColor {
	CarFaceColor_Black,		// ��ɫ
	CarFaceColor_Orange,		// ��ɫ
	CarFaceColor_Red,			// ��ɫ
	CarFaceColor_Green,		// ��ɫ
	CarFaceColor_Blue,		// ��ɫ
	CarFaceColor_Yellow,		// ��ɫ
	CarFaceColor_White,		// ��ɫ
	Tire0,					//����
	Tire1,					//̥��
};

enum CarFace {
	CarFace_PosX,		// +X��
	CarFace_NegX,		// -X��
	CarFace_PosY,		// +Y��
	CarFace_NegY,		// -Y��
	CarFace_PosZ,		// +Z��
	CarFace_NegZ,		// -Z��
};

enum CarRotationAxis {
	CarRotationAxis_X,	// ��X����ת
	CarRotationAxis_Y,	// ��Y����ת
	CarRotationAxis_Z,	// ��Z����ת
};

struct CarRotationRecord
{
	CarRotationAxis axis;	// ��ǰ��ת��
	int pos;				// ��ǰ��ת�������
	float dTheta;			// ��ǰ��ת�Ļ���
};

struct Cube
{
	DirectX::XMMATRIX GetWorldMatrix() const;

	CarFaceColor faceColors[6];	// ���������ɫ������0-5�ֱ��Ӧ+X, -X, +Y, -Y, +Z, -Z��
	DirectX::XMFLOAT3 pos;			// ��ת��������������λ��
	DirectX::XMFLOAT3 rotation;		// ��������ڵ�����ת����¼��ǰ�ֱ���x��, y��, z����ת�Ļ���

};

struct Cylinder
{
	DirectX::XMMATRIX GetWorldMatrix() const;

	CarFaceColor faceColors[2];	
	DirectX::XMFLOAT3 pos;			// ��ת��������������λ��
	DirectX::XMFLOAT3 rotation;		// ��������ڵ�����ת����¼��ǰ�ֱ���x��, y��, z����ת�Ļ���

};


class Car
{
public:

	struct PSConstantBuffer
	{
		DirectionalLight dirLight[10];
		PointLight pointLight[10];
		SpotLight spotLight[10];
		Material material;
		int numDirLight;
		int numPointLight;
		int numSpotLight;
		float pad;		// �����֤16�ֽڶ���
		DirectX::XMFLOAT4 eyePos;
	};
	
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	Car();

	// ��ʼ����Դ
	void InitResources(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	// ������Ҫ��Ⱦ��ģ��
	template<class VertexType>
	void SetMesh(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext, const Geometry::MeshData<VertexType>& meshData);
	// ������ԭħ��
	void Reset();
	// ����ħ��״̬
	void Update(float dt);
	// ����ħ��
	void Draw(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext, BasicEffect& effect);

	const DirectX::XMFLOAT3 & GetPosition();
	const float & GetRotateAngle();
	const DirectX::XMFLOAT3 & GetForwardTarget();

	void Move(DirectX::XMFLOAT2 move);

	// ��ǰ����ʰȡ���ĸ�������(ֻ���ǿɼ�������)�Ķ�Ӧ������δ�ҵ��򷵻�(-1, -1, -1)
	DirectX::XMINT3 HitCube(Ray ray, float * pDist = nullptr) const;
	

	// ������ת�ٶ�(rad/s)
	void SetMoveSpeed(float speed);

	// ��ȡ��������
	ComPtr<ID3D11ShaderResourceView> GetTexArray() const;

private:
	// ���ڴ��д�������
	ComPtr<ID3D11ShaderResourceView> CreateCarCubeTextureArrayFromMemory(ComPtr<ID3D11Device> device,
		ComPtr<ID3D11DeviceContext> deviceContext);

private:
	Material mMaterial;
	// ���� [X][Y][Z]
	Cube mCubes[6][6][6];
	Cylinder mCylinder[4];
	
	// ��ǰ�Զ���ת���ٶ�
	float mSpeed;
	float mRotateAngle;

	// ���㻺����
	ComPtr<ID3D11Buffer> mVertexBuffer;	

	// ��������������6������
	ComPtr<ID3D11Buffer> mIndexBuffer;
	
	// ʵ����������

	// �������飬����7������
	ComPtr<ID3D11ShaderResourceView> mTexArray;

	DirectX::XMFLOAT3 mPosition;
	DirectX::XMFLOAT3 mForwardTarget;
};




#endif