#include "charEnem.h"



Hamilla::Hamilla() : Character("Hamilla", 80, 35, 25, 15, 5, CONSTRUCT){}

int Hamilla::baseAttack(Enemy &target, int globalAP)
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

int Hamilla::skill1(Enemy &target, int globalAP)
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

int Hamilla::skill2(Enemy &target, int globalAP) 
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

int Hamilla::skill3(Entity &target, int globalAP) 
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