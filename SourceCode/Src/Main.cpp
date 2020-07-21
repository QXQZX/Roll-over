//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonClass.h"
#include "LessonX.h"
#include <iostream>
///////////////////////////////////////////////////////////////////////////////////////////
//
// ���������
//
//////////////////////////////////////////////////////////////////////////////////////////
int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
	//��������̨�����������Ϣ���
	FILE* stream;
	AllocConsole();
	freopen_s(&stream, "CONOUT$", "a+", stdout);

	// ��ʼ����Ϸ����
	if( !CSystem::InitGameEngine( hInstance, lpCmdLine ) )
		return 0;

	// To do : �ڴ�ʹ��API���Ĵ��ڱ���
	CSystem::SetWindowTitle("PvZ");

	// ������ѭ����������Ļͼ��ˢ�µȹ���
	while( CSystem::EngineMainLoop() )
	{
		// ��ȡ���ε���֮���ʱ�����ݸ���Ϸ�߼�����
		float	fTimeDelta	=	CSystem::GetTimeDelta();

		// ִ����Ϸ��ѭ��
		g_GameMain.GameMainLoop( fTimeDelta );
	};

	// �ر���Ϸ����
	CSystem::ShutdownGameEngine();
	return 0;
}

//==========================================================================
//
// ���沶׽����ƶ���Ϣ�󣬽����õ�������
void CSystem::OnMouseMove( const float fMouseX, const float fMouseY )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

}
//==========================================================================
//
// ���沶׽�������Ϣ�󣬽����õ�������
void CSystem::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

}
//==========================================================================
//
// ���沶׽��굯����Ϣ�󣬽����õ�������
void CSystem::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

}
//==========================================================================
//
// ���沶׽���̰�����Ϣ�󣬽����õ�������
// bAltPress bShiftPress bCtrlPress �ֱ�Ϊ�ж�Shift��Alt��Ctrl��ǰ�Ƿ�Ҳ���ڰ���״̬����������ж�Ctrl+E��ϼ�
void CSystem::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	
}
//==========================================================================
//
// ���沶׽���̵�����Ϣ�󣬽����õ�������
void CSystem::OnKeyUp( const int iKey )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

}

//===========================================================================
//
// ���沶׽�������뾫����ײ֮�󣬵��ô˺���
void CSystem::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	PvZSprite* src = g_GameMain.get_sprite_by_name(szSrcName);
	PvZSprite* tar = g_GameMain.get_sprite_by_name(szTarName);
	std::cout << szSrcName << " " << szTarName << std::endl;
	if (src->get_type() == "Zombie" && tar->get_type() == "Plant") {
		src->AnimateSpritePlayAnimation("BoomDieAnimation", false);
		src->SetSpriteLinearVelocityX(0);
	}

	if (src->get_type() == "Zombie" && tar->get_type() == "Plant") {
		src->AnimateSpritePlayAnimation("BoomDieAnimation", false);
		reinterpret_cast<Zombie*>(src)->die(); // ָ��ǿת
	}
}

//===========================================================================
//
// ���沶׽������������߽���ײ֮�󣬵��ô˺���.
// iColSide : 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void CSystem::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	
}

