#pragma once

#include "base.h"
#include "character.h"
#include <functional>

class Character; // Forward declaration

// Enemy class
class Enemy : public Entity
{
protected:
    int breakGauge, breakGaugeMax;
    bool isBroken;

    std::function<void(Character&)> attack1Func;
    std::function<void(Character&)> attack2Func;

public:
     Enemy(const std::string &name, int hp, int atk, int def, int mag, int res, ENTITY_TYPE ent_type, int breakGaugeMax,
          std::function<void(Character&)> attack1Func,
          std::function<void(Character&)> attack2Func)
        : Entity(name, hp, atk, def, mag, res, ent_type),
          breakGauge(0), breakGaugeMax(breakGaugeMax), isBroken(false),
          attack1Func(attack1Func), attack2Func(attack2Func) {}

    virtual ~Enemy() override = default;

 void takeDamage(int dmg, ATTACK_TYPE attackType) override {
        
        if (breakGauge >= breakGaugeMax) {
            
            dmg *= 2;
        }
        
        Entity::takeDamage(dmg, attackType);
    }

    //SISTEM BREAK kayaknya gak kepake karena musuh keburu mati sebelum bisa break, dan belum sempet
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

    void attack1(Character &target) { attack1Func(target); }
    void attack2(Character &target) { attack2Func(target); }


    bool getIsBroken() const { return isBroken; }
    void resetBreak() { isBroken = false; }
};
