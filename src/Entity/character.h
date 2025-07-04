#pragma once
#include "base.h"
#include "enemies.h"

class Enemy; // Forward declaration


class Character : public Entity
{

public:
    Character(const std::string &name, int hp, int atk, int def, int mag, int res, ENTITY_TYPE ent_type)
        : Entity(name, hp, atk, def, mag, res, ent_type) {}

    virtual int baseAttack(Enemy &target, int globalAP) = 0;
    virtual int skill1(Enemy &target, int globalAP) = 0;
    virtual int skill2(Enemy &target, int globalAP) = 0;
    virtual int skill3(Entity &target, int globalAP) = 0;

    float getBreakMuktiplier(ENTITY_TYPE enemyType) const{
    if(ent_type == enemyType){
        return 1.0f; 
    }else if(isDominant(enemyType)){
        return 0.7f; 
    }else{
        return 1.4f; 
    }
}
};

class Arthesa : public Character
{
public:
    Arthesa();

    int baseAttack(Enemy &target, int globalAP) override;
    int skill1(Enemy &target, int globalAP) override;
    int skill2(Enemy &target, int globalAP) override;
    int skill3(Entity &target, int globalAP) override;

    int getAPCost(int actionIndex) const {
        switch (actionIndex) {
            case 0: return 1; // Base Attack
            case 1: return 2; // Skill 1
            case 2: return 2; // Skill 2
            case 3: return 5; // Skill 3
            default: return 0;
        }
    }
};
class Perkia : public Character
{
public:
    Perkia();

    int baseAttack(Enemy &target, int globalAP) override;
    int skill1(Enemy &target, int globalAP) override;
    int skill2(Enemy &target, int globalAP) override;
    int skill3(Entity &target, int globalAP) override;

    int getAPCost(int actionIndex) const {
        switch (actionIndex) {
            case 0: return 1; // Base Attack
            case 1: return 2; // Skill 1
            case 2: return 2; // Skill 2
            case 3: return 5; // Skill 3
            default: return 0; 
        }
    }
};
class Ahmed : public Character
{
public:
    Ahmed();

    int baseAttack(Enemy &target, int globalAP) override;
    int skill1(Enemy &target, int globalAP) override;
    int skill2(Enemy &target, int globalAP) override;
    int skill3(Entity &target, int globalAP) override;
    
    int getAPCost(int actionIndex) const {
        switch (actionIndex) {
            case 0: return 1; // Base Attack
            case 1: return 2; // Skill 1
            case 2: return 2; // Skill 2
            case 3: return 5; // Skill 3
            default: return 0; 
        }
    }
};
class Hamilla : public Character
{
public:
    Hamilla();

    int baseAttack(Enemy &target, int globalAP) override;
    int skill1(Enemy &target, int globalAP) override;
    int skill2(Enemy &target, int globalAP) override;
    int skill3(Entity &target, int globalAP) override;

    int getAPCost(int actionIndex) const {
        switch (actionIndex) {
            case 0: return 1; // Base Attack
            case 1: return 2; // Skill 1
            case 2: return 2; // Skill 2
            case 3: return 5; // Skill 3
            default: return 0; 
        }
    }
};