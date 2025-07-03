#include "charEnem.h"


Perkia::Perkia() : Character("Perkia", 75, 5, 5, 30, 15, ETHEREAL){}

int Perkia::baseAttack(Enemy &target, int globalAP)
{
    Action action = {"Skill",2, PHYSICAL}; 
    if (target.isAlive() && globalAP >= 1)
    {
        int damage = atk - target.getDEF();
        target.takeDamage(damage, action.attackType);
        return action.APCost;
    }
    return 0;

}

int Perkia::skill1(Enemy &target, int globalAP)
{
    Action action = {"Skill",2, PHYSICAL}; 

    if (target.isAlive()&& globalAP >= action.APCost)
    {
        globalAP -= action.APCost;      
        int damage = atk - target.getDEF(); 
        int breakAmount = 10;

        target.increaseBreakGauge(breakAmount); 
        target.takeDamage(damage, action.attackType);
        return action.APCost;
    }
    return 0;

}

int Perkia::skill2(Enemy &target, int globalAP) 
{
    Action action = {"Skill",2, PHYSICAL}; 

    if (target.isAlive()&& globalAP >= action.APCost)
    {
        globalAP -= action.APCost;      
        int damage = atk - target.getDEF(); 

        target.takeDamage(damage, action.attackType);
        return action.APCost;
    }
    return 0;

}

int Perkia::skill3(Entity &target, int globalAP) 
{
    Action action = {"Skill",5, PHYSICAL}; 

    if (target.isAlive()&& globalAP >= action.APCost)
    {
        globalAP -= action.APCost;      
        int damage = atk - target.getDEF(); 

        target.takeDamage(damage, action.attackType);
        return action.APCost;
    }
    return 0;

}