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
	sun_count(20000),
	sun_num(new CTextSprite("SunCount")),
	game_map(new CSprite("background")),
	ord_zombie_count(5),

	// ģ���ʼ��
	t_ord_zombie(new OrdinaryZombie("OrdinaryZombie")),
	t_pea_shooter(new PeaShooter("PeaShooter", nullptr)),
	t_pea(new Pea("Pea")),
	t_range(new Range("AttackRange")),
	t_sun(new Sun("Sun", 25)),
	t_sunflower(new Sunflower("Sunflower", nullptr)),
	t_boom(new Boom("Boom")),
	t_cherry_bomb(new CherryBomb("CherryBomb", nullptr)),

	// ����ʼ��
	pea_shooter_card(new PeaShooterCard("PeaShooterCard")), // ���ֶ�����map
	sunflower_card(new SunflowerCard("SunflowerCard")),
	cherry_bomb_card(new CherryBombCard("CherryBombCard"))
{
	name_to_sprite[pea_shooter_card->GetName()] = pea_shooter_card;
	name_to_sprite[sunflower_card->GetName()] = sunflower_card;
	name_to_sprite[cherry_bomb_card->GetName()] = cherry_bomb_card;
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
	// welcome.t2d
	CSprite title("Title");
	title.SpriteMoveTo(-0.909, -27.080, 18, true);

	CSprite load("load");
	load.SetSpriteAngularVelocity(80);
	load.SpriteMoveTo(0.75 + 41.5 / 2 - 6, 30.875 - 11.75 / 2 + 2.7, 10, true);
	load.SetSpriteLifeTime(4);

	//create_pea_shooter(-39, -5 + -17)->set_exist(true);
	//create_pea_shooter(-39, -5 + -5)->set_exist(true);
	//create_pea_shooter(-39, -5 + 9)->set_exist(true);
	//create_pea_shooter(-39, -5 + 20)->set_exist(true);
	//create_pea_shooter(-39, -5 + 32)->set_exist(true);
	sun_num->SetTextValue(sun_count);
}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun(float fDeltaTime)
{
	// menu.t2d
	//CSprite welcome("welcome");
	//welcome.SpriteMoveTo(-28.883, -23.750, 18, true);

	if (fDeltaTime - timer > 6) {
		create_ord_zombie(CSystem::RandomRange(0, 4));
		timer = fDeltaTime;
		output_sun();
	}

	for (Sunflower* sunflower : vec_sunflower) {
		sunflower->attack(fDeltaTime);
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

Zombie* CGameMain::create_ord_zombie(int y) {
	float y_slot[5] = { -17, -5, 9, 20, 32 };
	OrdinaryZombie* zombie = new OrdinaryZombie(CSystem::MakeSpriteName(t_ord_zombie->GetName(), vec_ord_zombie.size()));
	vec_ord_zombie.push_back(zombie);
	name_to_sprite[zombie->GetName()] = zombie;
	zombie->CloneSprite(t_ord_zombie->GetName());
	zombie->set_exist(true);
	zombie->SetSpritePosition(CSystem::GetScreenRight(), y_slot[y] - zombie->GetSpriteHeight() / 2);
	zombie->move();

	return zombie;
}

Plant* CGameMain::create_pea_shooter(float x, float y) {
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
	pshtr->SetSpriteImmovable(true);
	rect->SpriteMountToSprite(pshtr->GetName(), 11, -0.5);
	pshtr->set_exist(false);
	return pshtr;
}

Plant* CGameMain::create_sunflower(float x, float y) {
	Sun* sun = new Sun(CSystem::MakeSpriteName(t_sun->GetName(), vec_sun.size()), 25);
	vec_sun.push_back(sun);
	name_to_sprite[sun->GetName()] = sun;
	sun->CloneSprite(t_sun->GetName());
	sun->set_exist(false);

	Sunflower* sf = new Sunflower(CSystem::MakeSpriteName(t_sunflower->GetName(), vec_sunflower.size()), sun);
	vec_sunflower.push_back(sf);
	name_to_sprite[sf->GetName()] = sf;

	sf->CloneSprite(t_sunflower->GetName());
	sf->SetSpritePosition(x, y);
	sf->SetSpriteImmovable(true);
	sf->set_exist(false);
	return sf;
}

Plant* CGameMain::create_cherry_bomb(float x, float y) {
	// ����ӣ��ը���� ������Χ
	Range* rect = new Range(CSystem::MakeSpriteName(t_range->GetName(), vec_range.size()));
	vec_range.push_back(rect);
	name_to_sprite[rect->GetName()] = rect;
	rect->CloneSprite(t_range->GetName());
	rect->set_exist(true);
	rect->SetSpriteWidth(30);
	rect->SetSpriteHeight(35);

	// ����ӣ��ը���� ��ը
	Boom* boom = new Boom(CSystem::MakeSpriteName("Boom", vec_boom.size()));
	vec_boom.push_back(boom);
	name_to_sprite[boom->GetName()] = boom;
	boom->set_exist(false);

	CherryBomb* cb = new CherryBomb(CSystem::MakeSpriteName(t_cherry_bomb->GetName(), vec_cherry_bomb.size()), boom);
	std::cout << cb->get_type();
	vec_cherry_bomb.push_back(cb);
	name_to_sprite[cb->GetName()] = cb;

	cb->CloneSprite(t_cherry_bomb->GetName());
	cb->SetSpritePosition(x, y);
	cb->SetSpriteImmovable(true);
	rect->SpriteMountToSprite(cb->GetName(), 0, 0);
	cb->set_exist(false);
	return cb;
}


PvZSprite* CGameMain::get_sprite_by_position(float x, float y) {
	std::cout << "CLICK:" << x << " " << y << std::endl;
	for (std::pair<std::string, PvZSprite*> sprite : name_to_sprite) {
		if (sprite.second->IsPointInSprite(x, y)) {
			return sprite.second;
		}
	}
	return nullptr;
}

bool CGameMain::planting(Plant* plant) {
	if (sun_count >= plant->get_cost()) {
		std::cout << "plant" << std::endl;
		sun_count -= plant->get_cost();
		sun_num->SetTextValue(sun_count);
		return true;
	}
	return false;
}

void CGameMain::output_sun(int num) {
	Sun* sun = new Sun(CSystem::MakeSpriteName(t_sun->GetName(), vec_sun.size()), num);
	vec_sun.push_back(sun);
	name_to_sprite[sun->GetName()] = sun;
	sun->CloneSprite(t_sun->GetName());
	

	int pos_x = CSystem::RandomRange(CSystem::GetScreenLeft() + 5, CSystem::GetScreenRight() - 5);
	int pos_y = CSystem::RandomRange(CSystem::GetScreenTop() + 10, CSystem::GetScreenBottom() - 5);

	sun->SetSpritePosition(pos_x, CSystem::GetScreenTop() + 10);
	sun->SpriteMoveTo(pos_x, pos_y, 15, true);


	sun->set_exist(true);
	sun->SetSpriteLifeTime(10);
}

void CGameMain::add_sun(int num) {
	sun_count += num;
	sun_num->SetTextValue(sun_count);
}