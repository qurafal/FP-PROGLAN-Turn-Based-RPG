#include "charEnem.h"

Arthesa::Arthesa() : Character("Arthesa", 100, 20, 10, 15, 5, MORTAL) {}

int Arthesa::baseAttack(Enemy &target, int globalAP)
{
    Action action = {"Skill",2, PHYSICAL};  
    if (target.isAlive() && globalAP >= 1)
    {
        globalAP -= action.APCost;
        int damage = atk;
        target.takeDamage(damage, action.attackType);
        return action.APCost; 
    }
    return 0; 
}

int Arthesa::skill1(Enemy &target, int globalAP)
{
    Action action = {"Skill",2, PHYSICAL}; 

    if (target.isAlive()&& globalAP >= action.APCost)
    {
        globalAP -= action.APCost;      
        int damage = atk;
        int breakAmount = 10;

        target.increaseBreakGauge(breakAmount); 
        target.takeDamage(damage, action.attackType);
        return action.APCost; 
    }
    return 0;
}

int Arthesa::skill2(Enemy &target, int globalAP) 
{
    Action action = {"Skill",2, PHYSICAL}; 

    if (target.isAlive()&& globalAP >= action.APCost)
    {
        globalAP -= action.APCost;      
        int damage = atk;

        target.takeDamage(damage, action.attackType);
        return action.APCost; 
    }
    return 0;
}

int Arthesa::skill3(Entity &target, int globalAP) 
{
    Action action = {"Skill",5, PHYSICAL}; 

    if (target.isAlive()&& globalAP >= action.APCost)
    {
        globalAP -= action.APCost;      
        int damage = atk;

        target.takeDamage(damage, action.attackType);
        return action.APCost; 
    }
    return 0;
}
