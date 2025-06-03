#pragma once
#include "base.h"
#include "enemies.h"

class Enemy; // Forward declaration


class Character : public Entity
{

public:
    Character(const std::string &name, int hp, int atk, int def, int mag, int res, ENTITY_TYPE ent_type)
        : Entity(name, hp, atk, def, mag, res, ent_type) {}

    virtual void baseAttack(Enemy &target, int globalAP) = 0;
    virtual void skill1(Enemy &target, int globalAP) = 0;
    virtual void skill2(Enemy &target, int globalAP) = 0;
    virtual void skill3(Entity &target, int globalAP) = 0;

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

    void baseAttack(Enemy &target, int globalAP) override;
    void skill1(Enemy &target, int globalAP) override;
    void skill2(Enemy &target, int globalAP) override;
    void skill3(Entity &target, int globalAP) override;
};
class Perkia : public Character
{
public:
    Perkia();

    void baseAttack(Enemy &target, int globalAP) override;
    void skill1(Enemy &target, int globalAP) override;
    void skill2(Enemy &target, int globalAP) override;
    void skill3(Entity &target, int globalAP) override;
};
class Ahmed : public Character
{
public:
    Ahmed();

    void baseAttack(Enemy &target, int globalAP) override;
    void skill1(Enemy &target, int globalAP) override;
    void skill2(Enemy &target, int globalAP) override;
    void skill3(Entity &target, int globalAP) override;
};
class Hamilla : public Character
{
public:
    Hamilla();

    void baseAttack(Enemy &target, int globalAP) override;
    void skill1(Enemy &target, int globalAP) override;
    void skill2(Enemy &target, int globalAP) override;
    void skill3(Entity &target, int globalAP) override;
};