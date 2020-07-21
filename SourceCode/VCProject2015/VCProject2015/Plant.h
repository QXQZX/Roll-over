#pragma once
#include "PvZSprite.h"
#include "Arms.h"
// ֲ�����
class Plant : public PvZSprite 
{
public:
    Plant(const char* sprite_name, int health, int attack_interval);
    virtual void attack(float delta_time) = 0;
    const char* get_type() override;
protected:
    int health;                     // Ѫ��
    int next_attack;                // �����´ι���ʱ��
    const int attack_interval;      // �������
    static const char* type;        // ����
};

// �㶹���� �̳���ֲ�����
class PeaShooter : public Plant {

public:
    PeaShooter(const char* plant_name, Pea* pea);
    void attack(float delta_time) override;
private:
    Pea* pea;
};

