#pragma once

#include "base.h"
#include "character.h"

class Character; // Forward declaration

// Enemy class
class Enemy : public Entity
{
protected:
    int breakGauge, breakGaugeMax;
    bool isBroken;

public:
    Enemy(const std::string &name, int hp, int atk, int def, int mag, int res, ENTITY_TYPE ent_type, int breakGaugeMax)
        : Entity(name, hp, atk, def, mag, res, ent_type) , breakGauge(0), breakGaugeMax(breakGaugeMax), isBroken(false) {}


 void takeDamage(int dmg, ATTACK_TYPE attackType) override {
        
        if (breakGauge >= breakGaugeMax) {
            
            dmg *= 2;
        }
        
        Entity::takeDamage(dmg, attackType);
    }
    void increaseBreakGauge(int amount) {
        breakGauge += amount;
        if (breakGauge > breakGaugeMax) {
            breakGauge = breakGaugeMax; 
        }
    }
    void resetBreakGauge() {
        breakGauge = 0; 
    }
    int getBreakGauge() const {
        return breakGauge; 
    }

    virtual void attack1(Character &target) = 0; 
    virtual void attack2(Character &target) = 0; 


    bool getIsBroken() const { return isBroken; }
    void resetBreak() { isBroken = false; }
};

class Goblin : public Enemy
{
public:
    Goblin();

    void attack1(Character &target) override;
    void attack2(Character &target) override;
};
class Skeleton : public Enemy
{
public:
    Skeleton();

    void attack1(Character &target) override;
    void attack2(Character &target) override;
};
//Witch
//Wizard
//Fire Worm
//Slime