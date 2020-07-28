/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../VCProject2015/VCProject2015/Zombie.h"
#include "../VCProject2015/VCProject2015/Plant.h"
#include "../VCProject2015/VCProject2015/Assist.h"

/////////////////////////////////////////////////////////////////////////////////
//
// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
	int				m_iGameState;				// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������
	long double		timer;						// ��Ϸ����ʱ��

	std::map<std::string, PvZSprite*>	name_to_sprite;
	// ��������
	int sun_count;
	CTextSprite* sun_num;
	// ��ͼ����
	CSprite* game_map;

	// ��������
	int ord_zombie_count;

	// ��������
	std::vector<OrdinaryZombie*>	vec_ord_zombie;
	std::vector<Pea*>				vec_pea;
	std::vector<PeaShooter*>		vec_pea_shooter;
	std::vector<Range*>				vec_range;
	std::vector<Sunflower*>			vec_sunflower;

	// ����ģ��
	OrdinaryZombie* t_ord_zombie;
	PeaShooter* t_pea_shooter;
	Pea* t_pea;
	Range* t_range;
	Sunflower* t_sunflower;

	// ֲ�￨
	PeaShooterCard* pea_shooter_card;
	SunflowerCard* sunflower_card;
public:
	CGameMain();            //���캯��
	~CGameMain();           //��������  

	// Get����
	int				GetGameState()											{ return m_iGameState; }

	// Set����
	void			SetGameState( const int iState )						{ m_iGameState = iState; }

	// ��Ϸ��ѭ����
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();
	PvZSprite* get_sprite_by_name(const std::string& sprite_name);
	PvZSprite* get_sprite_by_position(float x, float y);
	Zombie* create_ord_zombie(int y);
	Plant* create_pea_shooter(float x, float y);
	Plant* create_sunflower(float x, float y);
	bool planting(Plant* plant);
};

/////////////////////////////////////////////////////////////////////////////////
// 
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_