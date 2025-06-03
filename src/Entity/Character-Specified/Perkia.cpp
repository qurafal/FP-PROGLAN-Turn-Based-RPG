#include "charEnem.h"


Perkia::Perkia() : Character("Perkia", 75, 5, 5, 30, 15, ETHEREAL){}

void Perkia::baseAttack(Enemy &target, int globalAP)
{
    Action baseAttack = {"Skill",2, PHYSICAL}; 
    if (target.isAlive() && globalAP >= 1)
    {
        int damage = atk - target.getDEF();
        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Perkia::skill1(Enemy &target, int globalAP)
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

void Perkia::skill2(Enemy &target, int globalAP) 
{
    Action baseAttack = {"Skill",2, PHYSICAL}; 

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      
        int damage = atk - target.getDEF(); 

        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Perkia::skill3(Entity &target, int globalAP) 
{
    Action baseAttack = {"Skill",5, PHYSICAL}; 

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      
        int damage = atk - target.getDEF(); 

        target.takeDamage(damage, baseAttack.attackType);
    }
}