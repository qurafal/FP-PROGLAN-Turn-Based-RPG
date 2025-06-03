#include "charEnem.h"


Perkia::Perkia() : Character("Perkia", 75, 5, 5, 30, 15, ETHEREAL){}

void Perkia::baseAttack(Enemy &target, int globalAP)
{
    Action baseAttack = {"Skill",2, PHYSICAL}; // Define the base attack action
    if (target.isAlive() && globalAP >= 1)
    {
        int damage = atk - target.getDEF();
        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Perkia::skill1(Enemy &target, int globalAP)
{
    Action baseAttack = {"Skill",2, PHYSICAL}; // Define the base attack action

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      // Deduct AP cost for the attack)
        int damage = atk - target.getDEF(); // Calculate damage considering target's defense
        int breakAmount = 10;

        target.increaseBreakGauge(breakAmount); // Increase break gauge of the target
        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Perkia::skill2(Enemy &target, int globalAP) 
{
    Action baseAttack = {"Skill",2, PHYSICAL}; // Define the base attack action

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      // Deduct AP cost for the attack)
        int damage = atk - target.getDEF(); // Calculate damage considering target's defense

        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Perkia::skill3(Entity &target, int globalAP) 
{
    Action baseAttack = {"Skill",5, PHYSICAL}; // Define the base attack action

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      // Deduct AP cost for the attack)
        int damage = atk - target.getDEF(); // Calculate damage considering target's defense

        target.takeDamage(damage, baseAttack.attackType);
    }
}