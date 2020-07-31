//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonClass.h"
#include "LessonX.h"
#include "../VCProject2015/VCProject2015/Timer.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#undef min
#undef max
///////////////////////////////////////////////////////////////////////////////////////////
//
// ���������
//
//////////////////////////////////////////////////////////////////////////////////////////

bool			left_pressed; // �������Ƿ���
int map_id = 0;				 // ��ǰ��ͼ 0:welcome; 1:menu; 2:�ؿ�;
PvZSprite* selected_card; // ѡ�е�ֲ�￨
Plant* seed;
long double 	fTimeDelta;
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
	if (!CSystem::InitGameEngine(hInstance, lpCmdLine))
		return 0;

	// To do : �ڴ�ʹ��API���Ĵ��ڱ���
	CSystem::SetWindowTitle("PvZ");
	//CSystem::LoadMap("welcome.t2d");

	std::thread timer([&]() {
		while (true) {
			fTimeDelta += CSystem::GetTimeDelta();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		});
	timer.detach();

	// ������ѭ����������Ļͼ��ˢ�µȹ���
	while (CSystem::EngineMainLoop())
	{
		// ��ȡ���ε���֮���ʱ�����ݸ���Ϸ�߼�����
		// ִ����Ϸ��ѭ��
		g_GameMain.GameMainLoop(fTimeDelta);
	};

	// �ر���Ϸ����
	CSystem::ShutdownGameEngine();
	return 0;
}

//==========================================================================
//
// ���沶׽����ƶ���Ϣ�󣬽����õ�������
// �˵������ͼ ����ƶ� event handler
static void menu_map_OnMouseMove(const float fMouseX, const float fMouseY) {
	CAnimateSprite adcenture("AdventureGame"); // ð��ģʽ
	CAnimateSprite mini("MiniGame");		   // ������Ϸ
	CAnimateSprite edu("EduGame");			   // ����ģʽ
	if (adcenture.IsPointInSprite(fMouseX, fMouseY)) {
		adcenture.AnimateSpritePlayAnimation("AdventureModeAnimation", false);
	}
	if (mini.IsPointInSprite(fMouseX, fMouseY)) {
		mini.AnimateSpritePlayAnimation("MiniModeAnimation", false);
	}
	if (edu.IsPointInSprite(fMouseX, fMouseY)) {
		edu.AnimateSpritePlayAnimation("EduModeAnimation", false);
	}

}
void CSystem::OnMouseMove(const float fMouseX, const float fMouseY)
{
	// ��ͬ��ͼ�����¼��ֱ��װ������ȫ�ֵĵ�ͼid���ֲ�ͬ��ͼ���¼�
	switch (map_id)
	{
	case 0:
		break;
	case 1:
		menu_map_OnMouseMove(fMouseX, fMouseY);
	default:
		break;
	}

	// �����ڴ������Ϸ��Ҫ����Ӧ����
	if (left_pressed && selected_card && seed) {
		seed->SetSpritePosition(fMouseX, fMouseY);
	}
}
// �Բ�ͬ��ͼ����¼����з���, �Ա㱣֤��ͬ��ͼ��ͬ�������¼��Ĳ����ͻ
// ��ӭ�����ͼ ����� event handler
static void welcome_map_OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	CSprite startBtn("LoadBar");
	if (iMouseType == MOUSE_LEFT) {
		if (startBtn.IsPointInSprite(fMouseX, fMouseY)) {
			CSystem::LoadMap("menu.t2d");
			map_id = 1;
		}
	}
}
// �˵������ͼ ����� event handler
static void menu_map_OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	CSprite adcenture("AdventureGame");
	if (iMouseType == MOUSE_LEFT) {
		if (adcenture.IsPointInSprite(fMouseX, fMouseY)) {
			CSystem::LoadMap("level.t2d");
			map_id = 2;
		}
	}
}
//==========================================================================
//
// ���沶׽�������Ϣ�󣬽����õ�������
void CSystem::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY)
{
	// ��ͬ��ͼ�����¼��ֱ��װ������ȫ�ֵĵ�ͼid���ֲ�ͬ��ͼ���¼�
	switch (map_id)
	{
	case 0:
		welcome_map_OnMouseClick(iMouseType, fMouseX, fMouseY);
	case 1:
		menu_map_OnMouseClick(iMouseType, fMouseX, fMouseY);
	default:
		break;
	}

	// �����ڴ������Ϸ��Ҫ����Ӧ����
	if (iMouseType == MOUSE_LEFT) {

		left_pressed = true;
		selected_card = nullptr;
		seed = nullptr;
		// ��ֵ�ɹ� ִ��if
		selected_card = g_GameMain.get_sprite_by_position(fMouseX, fMouseY);
		std::cout << selected_card << std::endl;
		if (selected_card) {
			if (selected_card->get_type() == "Sun") {
				Sun* sun = reinterpret_cast<Sun*>(selected_card);
				sun->SpriteMoveTo(-43.275, -33.275, 100, true);
				sun->SetSpriteLifeTime(1);
				g_GameMain.add_sun(sun->get_num());
				sun->set_exist(false);

				left_pressed = false;
				selected_card = nullptr;
				seed = nullptr;

				return;
			}

			std::string type = selected_card->get_type();
			std::cout << type.substr(type.size() - 4, 4) << std::endl;
			// ����λCard��ʾ ֲ�￨
			if (type.substr(type.size() - 4, 4) == "Card") {
				// ��갴�� ѡ��ֲ�￨
				std::cout << selected_card->get_type() << std::endl;
				if (selected_card->get_type() == "PeaShooterCard") {
					seed = g_GameMain.create_pea_shooter(fMouseX, fMouseY);
				}
				else if (selected_card->get_type() == "SunflowerCard") {
					seed = g_GameMain.create_sunflower(fMouseX, fMouseY);
				}
				else if (selected_card->get_type() == "CherryBombCard") {
					seed = g_GameMain.create_cherry_bomb(fMouseX, fMouseY);
				}
				else if (selected_card->get_type() == "WallNutCard") {
					seed = g_GameMain.create_wall_nut(fMouseX, fMouseY);
				}
				seed->SetSpriteColorAlpha(100);
			}
		}
	}
}
//==========================================================================
//
// ���沶׽��굯����Ϣ�󣬽����õ�������
void CSystem::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY)
{
	float x_slot[10] = { -39, -28.5, -18, -7.5, 2, 12, 22, 32, 43, 55 };
	float y_slot[5] = { -17, -5, 9, 20, 32 };
	if (iMouseType == MOUSE_LEFT) {
		if (left_pressed && selected_card && seed) {
			seed->SetSpriteColorAlpha(255);

			// ȷ��λ��
			int x = 0, y = 0;
			for (int i = 1; i < 10; i++) {
				if (abs(fMouseX - x_slot[x]) > abs(fMouseX - x_slot[i])) {
					x = i;
				}
			}
			for (int i = 1; i < 5; i++) {
				if (abs(fMouseY - y_slot[y] + seed->GetSpriteHeight() / 2) > abs(fMouseY - y_slot[i] + seed->GetSpriteHeight() / 2)) {
					y = i;
				}
			}
			// ���������λ����ֲ��
			PvZSprite* sprite = g_GameMain.get_sprite_by_position(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
			if (sprite && sprite->is_exist()) {
				seed->DeleteSprite();
			}
			else {
				if (g_GameMain.planting(seed)) {
					seed->SetSpritePosition(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
					seed->set_exist(true);
				}
				else {
					seed->DeleteSprite();
				}
			}
		}
		left_pressed = false;
		selected_card = nullptr;
		seed = nullptr;
	}
}
//==========================================================================
//
// ���沶׽���̰�����Ϣ�󣬽����õ�������
// bAltPress bShiftPress bCtrlPress �ֱ�Ϊ�ж�Shift��Alt��Ctrl��ǰ�Ƿ�Ҳ���ڰ���״̬����������ж�Ctrl+E��ϼ�
void CSystem::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress)
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

}
//==========================================================================
//
// ���沶׽���̵�����Ϣ�󣬽����õ�������
void CSystem::OnKeyUp(const int iKey)
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����

}

//===========================================================================
//
// ���沶׽�������뾫����ײ֮�󣬵��ô˺���
void CSystem::OnSpriteColSprite(const char* szSrcName, const char* szTarName)
{
	PvZSprite* src = g_GameMain.get_sprite_by_name(szSrcName);
	PvZSprite* tar = g_GameMain.get_sprite_by_name(szTarName);


	if (src && tar) {
		// ��ʬ���빥����Χ
		if (src->get_type() == "Range" && tar->get_type() == "Zombie") {
			// ת�����丸�����ָ��
			PvZSprite* pvz = g_GameMain.get_sprite_by_name(src->GetSpriteMountedParent());
			Plant* p = reinterpret_cast<Plant*>(pvz);
			p->attack(fTimeDelta);
		}

		// ��ʬ��ֲ��
		if (src->get_type() == "Zombie" && tar->get_type() == "Plant") {
			Zombie* z = reinterpret_cast<Zombie*>(src);  // ָ��ǿת
			Plant* p = reinterpret_cast<Plant*>(tar);
			z->eat_plant(p, fTimeDelta);
		}

		// �ӵ���ʬ
		if (src->get_type() == "Arms" && tar->get_type() == "Zombie") {
			Arms* a = reinterpret_cast<Arms*>(src);  // ָ��ǿת
			Zombie* z = reinterpret_cast<Zombie*>(tar);
			z->attacked_by(a);
		}
	}
}

//===========================================================================
//
// ���沶׽������������߽���ײ֮�󣬵��ô˺���.
// iColSide : 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void CSystem::OnSpriteColWorldLimit(const char* szName, const int iColSide)
{

}

