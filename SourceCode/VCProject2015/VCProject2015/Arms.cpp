#include "Arms.h"

const char* Arms::type = "Arms";
Arms::Arms(const char* sprite_name, int power) :
    PvZSprite(sprite_name),
    power(power)
{

}

int Arms::get_power() {
    return power;
}

const char* Arms::get_type() {
    return type;
}


///////////////////////////////////////

Pea::Pea(const char* arms_name) :
    Arms(arms_name, 40)
{

}

/// <summary>
/// ����֮�����Ч
/// </summary>
void Pea::after_hit() {
    this->AnimateSpritePlayAnimation("BoomAnimation", false);
    this->SetSpriteCollisionActive(false, false);
    this->SetSpriteLinearVelocityX(0);
    this->SetSpriteLifeTime(0.5);
}