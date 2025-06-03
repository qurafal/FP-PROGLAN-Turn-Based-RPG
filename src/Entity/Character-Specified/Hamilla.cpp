#include "charEnem.h"



Hamilla::Hamilla() : Character("Hamilla", 80, 35, 25, 15, 5, CONSTRUCT){}

void Hamilla::baseAttack(Enemy &target, int globalAP)
{
    Action baseAttack = {"Skill",2, PHYSICAL}; 
    if (target.isAlive() && globalAP >= 1)
    {
        int damage = atk - target.getDEF();
        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Hamilla::skill1(Enemy &target, int globalAP)
{
    Action baseAttack = {"Skill",2, PHYSICAL}; 

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      
        int damage = atk - target.getDEF(); 
        int breakAmount = 10;

        target.increaseBreakGauge(breakAmount); 
        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Hamilla::skill2(Enemy &target, int globalAP) 
{
    Action baseAttack = {"Skill",2, PHYSICAL}; 

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      
        int damage = atk - target.getDEF(); 

        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Hamilla::skill3(Entity &target, int globalAP) 
{
    Action baseAttack = {"Skill",5, PHYSICAL}; 

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      
        int damage = atk - target.getDEF(); 

        target.takeDamage(damage, baseAttack.attackType);
    }
}