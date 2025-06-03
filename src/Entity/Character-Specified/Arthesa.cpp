#include "charEnem.h"

Arthesa::Arthesa() : Character("Arthesa", 100, 20, 10, 15, 5, MORTAL) {}

void Arthesa::baseAttack(Enemy &target, int globalAP)
{
    Action baseAttack = {"Skill",2, PHYSICAL}; // Define the base attack action
    if (target.isAlive() && globalAP >= 1)
    {
        int damage = atk - target.getDEF();
        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Arthesa::skill1(Enemy &target, int globalAP)
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

void Arthesa::skill2(Enemy &target, int globalAP) 
{
    Action baseAttack = {"Skill",2, PHYSICAL}; // Define the base attack action

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      // Deduct AP cost for the attack)
        int damage = atk - target.getDEF(); // Calculate damage considering target's defense

        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Arthesa::skill3(Entity &target, int globalAP) 
{
    Action baseAttack = {"Skill",5, PHYSICAL}; // Define the base attack action

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      // Deduct AP cost for the attack)
        int damage = atk - target.getDEF(); // Calculate damage considering target's defense

        target.takeDamage(damage, baseAttack.attackType);
    }
}
