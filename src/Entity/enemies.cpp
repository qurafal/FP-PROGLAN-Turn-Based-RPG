#include "enemies.h"
#include "character.h"

// Implementasi Goblin
Goblin::Goblin() : Enemy("Goblin", 50, 15, 5, 0, 0, ETHEREAL, 100) {}

void Goblin::attack1(Character &target) {
    ATTACK_TYPE attackType = PHYSICAL;
    if (target.isAlive()) {
        int damage = atk - target.getDEF();
        target.takeDamage(damage, attackType);
    }
}

void Goblin::attack2(Character &target) {
    ATTACK_TYPE attackType = PHYSICAL;
    if (target.isAlive()) {
        int damage = 10 + atk - target.getDEF();
        target.takeDamage(damage, attackType);
    }
}