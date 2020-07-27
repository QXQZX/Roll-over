#pragma once
#include "PvZSprite.h"
#include "Zombie.h"
#include "Arms.h"
// ֲ�����
class Plant : public PvZSprite 
{
public:
    Plant(const char* sprite_name, double health, int attack_interval);
    virtual void attack(float delta_time) = 0;
    virtual bool attacked_by(Zombie* zombie);
    
    const char* get_type() override;

protected:
    double health;                      // Ѫ��
    long double next_attack;            // �����´ι���ʱ��
    const float attack_interval;        // �������
    static const char* type;            // ����
};

// �㶹���� �̳���ֲ�����
class PeaShooter : public Plant {

public:
    PeaShooter(const char* plant_name, Pea* pea);
    void attack(float delta_time) override;
private:
    Pea* pea;
};


// ���տ� �̳���ֲ�����
class Sunflower : public Plant {

public:
    Sunflower(const char* plant_name);
    void attack(float delta_time) override;
private:
    int light_num;
    int light_v;
};

