/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;

//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
CGameMain::CGameMain() :
	m_iGameState(1),
	timer(0),
	sun_count(2000),
	game_map(new CSprite("background")),
	ord_zombie_count(5),
	t_ord_zombie(new OrdinaryZombie("OrdinaryZombie")),
	t_pea_shooter(new PeaShooter("PeaShooter", nullptr)),
	t_pea(new Pea("Pea")),
	t_range(new Range("PeaShooterAttackRange")),
	t_sunflower(new Sunflower("Sunflower")),
	pea_shooter_card(new PeaShooterCard("PeaShooterCard")), // ���ֶ�����map
	sunflower_card(new SunflowerCard("SunflowerCard"))
{
	name_to_sprite[pea_shooter_card->GetName()] = pea_shooter_card;
	name_to_sprite[sunflower_card->GetName()] = sunflower_card;
}
//==============================================================================
//
// ��������
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬. 
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop(float	fDeltaTime)
{
	switch (GetGameState())
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
	{
		GameInit();
		SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
	}
	break;

	// ��Ϸ�����У����������Ϸ�߼�
	case 2:
	{
		// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
		if (true)
		{
			GameRun(fDeltaTime);
		}
		else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
		{
			SetGameState(0);
			GameEnd();
		}
	}
	break;

	// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit()
{
	create_pea_shooter(-39, -5 + -17)->set_exist(true);
	create_pea_shooter(-39, -5 + -5)->set_exist(true);
	create_pea_shooter(-39, -5 + 9)->set_exist(true);
	create_pea_shooter(-39, -5 + 20)->set_exist(true);
	create_pea_shooter(-39, -5 + 32)->set_exist(true);
}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{
	if (fDeltaTime - timer > 3) {
		create_ord_zombie(CSystem::RandomRange(0, 4));
		timer = fDeltaTime;
	}
}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
}

// �þ�������ӳ�侫�����
PvZSprite* CGameMain::get_sprite_by_name(const std::string& sprite_name) {
	if (name_to_sprite.count(sprite_name)) {
		return name_to_sprite.at(sprite_name);
	}
	return nullptr;
}

PvZSprite* CGameMain::create_ord_zombie(int y) {
	float y_slot[5] = { -17, -5, 9, 20, 32 };
	OrdinaryZombie* zombie = new OrdinaryZombie(CSystem::MakeSpriteName(t_ord_zombie->GetName() , vec_ord_zombie.size()));
	vec_ord_zombie.push_back(zombie);
	name_to_sprite[zombie->GetName()] = zombie;
	zombie->CloneSprite(t_ord_zombie->GetName());
	zombie->set_exist(true);
	zombie->SetSpritePosition(CSystem::GetScreenRight(), y_slot[y] - zombie->GetSpriteHeight() / 2);
	zombie->move();

	return zombie;
}

PvZSprite* CGameMain::create_pea_shooter(float x, float y) {
	// �����㶹���ֵ� ������Χ
	Range* rect = new Range(CSystem::MakeSpriteName(t_range->GetName(), vec_range.size()));
	vec_range.push_back(rect);
	name_to_sprite[rect->GetName()] = rect;
	rect->CloneSprite(t_range->GetName());
	rect->set_exist(true);

	// �����㶹���ֵ� �㶹
	Pea* pea = new Pea(CSystem::MakeSpriteName("Pea", vec_pea.size()));
	vec_pea.push_back(pea);
	name_to_sprite[pea->GetName()] = pea;
	pea->set_exist(false);

	// �����㶹����
	PeaShooter* pshtr = new PeaShooter(CSystem::MakeSpriteName(t_pea_shooter->GetName(), vec_pea_shooter.size()), pea);
	vec_pea_shooter.push_back(pshtr);
	name_to_sprite[pshtr->GetName()] = pshtr;

	pshtr->CloneSprite(t_pea_shooter->GetName());
	pshtr->SetSpritePosition(x, y);
	pshtr->SetSpriteImmovable(false);
	rect->SpriteMountToSprite(pshtr->GetName(), 11, -0.5);
	pshtr->set_exist(false);
	return pshtr;
}

PvZSprite* CGameMain::create_sunflower(float x, float y) {

	Sunflower* sf = new Sunflower(CSystem::MakeSpriteName(t_sunflower->GetName(), vec_sunflower.size()));
	std::cout << sf->get_type();
	vec_sunflower.push_back(sf);
	name_to_sprite[sf->GetName()] = sf;
	std::cout << t_sunflower->GetName() << std::endl;

	sf->CloneSprite(t_sunflower->GetName());
	sf->SetSpritePosition(x, y);
	sf->SetSpriteImmovable(false);
	sf->set_exist(false);
	return sf;
}

PvZSprite* CGameMain::get_sprite_by_position(float x, float y) {
	for (std::pair<std::string, PvZSprite*> sprite : name_to_sprite) {
		if (sprite.second->IsPointInSprite(x, y)) {
			return sprite.second;
		}
	}
	return nullptr;
}