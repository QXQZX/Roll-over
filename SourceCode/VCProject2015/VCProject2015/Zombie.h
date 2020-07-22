#pragma once
#include "PvZSprite.h"
#include "Arms.h"

class Zombie : public PvZSprite {
public:
    Zombie(const char* sprite_name, int health, int speed, int power);
    const char* get_type() override;

    virtual void move() = 0;
    virtual void stop() = 0;
    virtual void eat_plant() = 0;
    virtual void die() = 0;
    virtual void attacked_by(Arms* arm) = 0;
    virtual int  get_power() = 0;

protected:
    int health;
    int move_speed;
    int power;

    float next_attack;                // �����´ι���ʱ��
    const float attack_interval;      // �������
    static const char* type;
};

class OrdinaryZombie : public Zombie {
public:
    OrdinaryZombie(const char* zombie_name);
    ~OrdinaryZombie();
    void move() override;
    void stop() override;
    void eat_plant() override;
    void die() override;
    void attacked_by(Arms* arm) override;
    int  get_power() override;
};
