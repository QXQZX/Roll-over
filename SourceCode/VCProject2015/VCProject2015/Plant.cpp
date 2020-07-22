#include "Plant.h"

const char* Plant::type = "Plant";

Plant::Plant(const char* sprite_name, int health, int attack_interval) :
    PvZSprite(sprite_name),
    health(health), 
    next_attack(0),
    attack_interval(attack_interval) {

}

const char* Plant::get_type() {
    return type;
}

/* --------------------------------------------------- */
PeaShooter::PeaShooter(const char* plant_name, Pea* pea) :
    Plant(plant_name, 200, 500),
    pea(pea)
{
    
}

/// <summary>
/// ʱ�������۵���һ���̶Ⱥ� ��ʼ����
/// </summary>
/// <param name="delta_time">ÿ��ʱ����</param>
void PeaShooter::attack(float delta_time) {
    if ((next_attack -= delta_time) <= 0) {
        pea->CloneSprite("Pea");
        // ΢��λ��һ�� ���첿����
        pea->SetSpritePosition(this->GetSpritePositionX() + 1, this->GetSpritePositionY() - 2);
        pea->SetSpriteLinearVelocityX(30);
        next_attack = attack_interval;
    }
}

/// <summary>
/// ֲ�ﱻ��ʬ��
/// </summary>
/// <param name="zombie">��ֻ��ʬ</param>
/// <returns>true:��ҧ���� false����û��ҧ��</returns>
bool PeaShooter::attacked_by(Zombie* zombie) {
    this->health -= zombie->get_power();
    if (this->health <= 0) {
        return true;
    }
    else {
        return false;
    }
}