#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "d3dApp.h"
#include "Car.h"
#include "Camera.h"
#include "SkyRender.h"
#include <ctime>
#include <sstream>
#include "GameObject.h"

class GameApp : public D3DApp
{
public:
	enum class GameStatus {
		Preparing,	// ׼����
		Ready,		// ����
		Playing,	// ������
		Finished,	// �����
	};

public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();


private:

	// �����������������ɶ���������true
	bool PlayCameraAnimation(float dt);

	bool InitResource();

	void KeyInput(float dt);
	void MouseInput(float dt);

	std::wstring floating_to_wstring(float val, int precision);

private:
	ComPtr<ID2D1SolidColorBrush> mColorBrush;	// ��ɫ��ˢ
	ComPtr<IDWriteFont> mFont;					// ����
	ComPtr<IDWriteTextFormat> mTextFormat;		// �ı���ʽ

	Car mCar;									// ����
	GameObject mGround;							// ����
	GameObject mCylinder;						// Բ��
	
	std::unique_ptr<Camera> mCamera;			// �����
	CamType mCamType;							// ���������

	BasicEffect mBasicEffect;					// ������Ч������
	SkyEffect mSkyEffect;						// ��պ���Ч����
	std::unique_ptr<SkyRender> mDaylight;		// ��պ�(����)

	GameTimer mGameTimer;						// ��Ϸ��ʱ��
	GameStatus mGameStatus;						// ��Ϸ״̬
	bool mIsCompleted;							// �Ƿ����

	float mAnimationTime;						// ��������ʱ��

	//
	// ����������
	//
	
	int mClickPosX, mClickPosY;					// ���ε��ʱ���λ��
	float mSlideDelay;							// �϶��ӳ���Ӧʱ�� 
	float mCurrDelay;							// ��ǰ�ӳ�ʱ��
	bool mDirectionLocked;						// ������

	CarRotationRecord mCurrRotationRecord;	// ��ǰ��ת��¼
};


#endif