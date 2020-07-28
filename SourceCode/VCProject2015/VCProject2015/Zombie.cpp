#include "Zombie.h"
#include "Plant.h"
const char* Zombie::type = "Zombie";

Zombie::Zombie(const char* sprite_name, int health, int move_speed, double power) :
    PvZSprite(sprite_name),
    health(health),
    move_speed(move_speed),
    power(power),
    next_attack(0),
    attack_interval(1),
    eating(false),
    eating_plant(nullptr)
{

}

const char* Zombie::get_type() {
    return type;
}
bool Zombie::is_eating() {
    return eating;
}

void Zombie::set_eating(bool eating) {
    this->eating = eating;
}

void Zombie::set_plant(Plant* plant) {
    eating_plant = plant;
}
Plant* Zombie::get_plant() {
    return eating_plant;
}

/////////////////////////

OrdinaryZombie::OrdinaryZombie(const char* zombie_name) : Zombie(zombie_name, 200, 4, 50)
{

}

/// <summary>
/// �ý�ʬ��ʼ�ƶ�
/// </summary>
void OrdinaryZombie::move() {
    this->eating = false;
    this->set_status();
    this->SetSpriteLinearVelocityX(-this->move_speed);
}

void OrdinaryZombie::stop() {
    this->set_status();
    this->SetSpriteLinearVelocityX(0);
}

void OrdinaryZombie::eat_plant(Plant* plant, long double delta_time) {
    if (delta_time - next_attack > attack_interval) {
        std::cout << "eating" << std::endl;
        plant->attacked_by(this);
        next_attack = delta_time;
    }
}



void OrdinaryZombie::attacked_by(Arms* arms) {
    this->health -= arms->get_power();
    arms->after_hit();
    if (this->health <= 0) {
        this->die();
    }
    else {
        this->set_status();
    }
}

/// <summary>
/// ��������
/// </summary>
void OrdinaryZombie::die() {
    this->SetSpriteLinearVelocityX(0);
    this->AnimateSpritePlayAnimation("ZombieDieAnimation", false);
    this->SetSpriteCollisionActive(false, false);
    this->SetSpriteWidth(20.625);
    this->SetSpriteHeight(10.625);
    // ������������
    this->SetSpriteLifeTime(1);
    exist = false;
}

double OrdinaryZombie::get_power() {
    return power;
}

OrdinaryZombie::~OrdinaryZombie() {
    std::cout << "~OrdinaryZombie()" << std::endl;
}

void OrdinaryZombie::set_status() {
    if (this->health > 100) {
        if (eating_plant && eating_plant->is_exist()) {
            this->AnimateSpritePlayAnimation("ZombieAttackAnimation", false);
        }
        else {
            this->AnimateSpritePlayAnimation("OrdinaryZombieAnimation", false);
        }
    }
    else if (this->health <= 100) {
        if (eating_plant && eating_plant->is_exist()) {
            this->AnimateSpritePlayAnimation("ZombieLoseHeadAttackAnimation", false);
            this->SetSpriteWidth(11.125);
            this->SetSpriteHeight(12.875);
        }
        else {
            this->AnimateSpritePlayAnimation("ZombieLoseHeadAnimation", false);
            this->SetSpriteWidth(10.000);
            this->SetSpriteHeight(11.875);
        }
    }
}