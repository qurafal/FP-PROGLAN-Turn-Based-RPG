#include "charEnem.h"


Ahmed::Ahmed() : Character("Ahmed", 140, 15, 25, 10, 20, CONSTRUCT){}

void Ahmed::baseAttack(Enemy &target, int globalAP)
{
    Action baseAttack = {"Basic Attack",1, MAGICAL}; // Define the base attack action
    if (target.isAlive() && globalAP >= 1)
    {
        int damage = atk - target.getRES();
        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Ahmed::skill1(Enemy &target, int globalAP)
{
    Action baseAttack = {"Skill",2, PHYSICAL}; // Define the base attack action

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;
        int damage = atk;
        int breakAmount = 10;

        target.increaseBreakGauge(breakAmount); // Increase break gauge of the target
        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Ahmed::skill2(Enemy &target, int globalAP) 
{
    Action baseAttack = {"Skill",2, MAGICAL}; // Define the base attack action

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      // Deduct AP cost for the attack)
        int damage = mag*1.5;

        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Ahmed::skill3(Entity &target, int globalAP) 
{
    Action baseAttack = {"Skill",5, MAGICAL}; // Define the base attack action

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      // Deduct AP cost for the attack)
        int damage = atk - target.getRES(); // Calculate damage considering target's defense

        target.takeDamage(damage, baseAttack.attackType);
    }
}