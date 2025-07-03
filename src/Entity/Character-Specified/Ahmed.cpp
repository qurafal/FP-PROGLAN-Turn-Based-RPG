#include "charEnem.h"


Ahmed::Ahmed() : Character("Ahmed", 140, 15, 25, 10, 20, CONSTRUCT){}

int Ahmed::baseAttack(Enemy &target, int globalAP)
{
    Action action = {"Basic Attack",1, MAGICAL}; 
    if (target.isAlive() && globalAP >= 1)
    {
        int damage = atk - target.getRES();
        target.takeDamage(damage, action.attackType);
        return action.APCost; 
    }
    return 0;
}

int Ahmed::skill1(Enemy &target, int globalAP)
{
    Action action = {"Skill",2, PHYSICAL}; 

    if (target.isAlive()&& globalAP >= action.APCost)
    {
      
        int damage = atk;
        int breakAmount = 10;

        target.increaseBreakGauge(breakAmount); 
        target.takeDamage(damage, action.attackType);
        return action.APCost; 
    }
    return 0;
}

int Ahmed::skill2(Enemy &target, int globalAP) 
{
    Action action = {"Skill",2, MAGICAL}; 

    if (target.isAlive()&& globalAP >= action.APCost)
    {
        globalAP -= action.APCost;
        int damage = mag*1.5;

        target.takeDamage(damage, action.attackType);
        return action.APCost; 
    }
    return 0;
}

int Ahmed::skill3(Entity &target, int globalAP) 
{
    Action action = {"Skill",5, MAGICAL}; 

    if (target.isAlive()&& globalAP >= action.APCost)
    {
        globalAP -= action.APCost;      
        int damage = atk - target.getRES(); 

        target.takeDamage(damage, action.attackType);
        return action.APCost; 
    }
    return 0;
}