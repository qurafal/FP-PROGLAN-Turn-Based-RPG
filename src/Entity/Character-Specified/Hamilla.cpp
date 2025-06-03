#include "charEnem.h"



Hamilla::Hamilla() : Character("Hamilla", 80, 35, 25, 15, 5, CONSTRUCT){}

void Hamilla::baseAttack(Enemy &target, int globalAP)
{
    Action baseAttack = {"Skill",2, PHYSICAL}; // Define the base attack action
    if (target.isAlive() && globalAP >= 1)
    {
        int damage = atk - target.getDEF();
        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Hamilla::skill1(Enemy &target, int globalAP)
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

void Hamilla::skill2(Enemy &target, int globalAP) 
{
    Action baseAttack = {"Skill",2, PHYSICAL}; // Define the base attack action

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      // Deduct AP cost for the attack)
        int damage = atk - target.getDEF(); // Calculate damage considering target's defense

        target.takeDamage(damage, baseAttack.attackType);
    }
}

void Hamilla::skill3(Entity &target, int globalAP) 
{
    Action baseAttack = {"Skill",5, PHYSICAL}; // Define the base attack action

    if (target.isAlive(), globalAP >= baseAttack.APCost)
    {
        globalAP -= baseAttack.APCost;      // Deduct AP cost for the attack)
        int damage = atk - target.getDEF(); // Calculate damage considering target's defense

        target.takeDamage(damage, baseAttack.attackType);
    }
}