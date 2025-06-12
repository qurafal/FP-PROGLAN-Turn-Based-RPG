#pragma once
#include "enemies.h"
#include "character.h"


// Factory functions for each enemy type
inline std::unique_ptr<Enemy> makeGoblin() {
    return std::make_unique<Enemy>(
        "Goblin", 50, 15, 5, 0, 0, ETHEREAL, 100,
        [](Character& target) {
            int damage = 15; // Let takeDamage handle DEF
            target.takeDamage(damage, PHYSICAL);
        },
        [](Character& target) {
            int damage = 10 + 15;
            target.takeDamage(damage, PHYSICAL);
        }
    );
}

inline std::unique_ptr<Enemy> makeSkeleton() {
    return std::make_unique<Enemy>(
        "Skeleton", 60, 18, 8, 0, 0, ETHEREAL, 120,
        [](Character& target) {
            int damage = 18;
            target.takeDamage(damage, PHYSICAL);
        },
        [](Character& target) {
            int damage = 5 + 18;
            target.takeDamage(damage, PHYSICAL);
        }
    );
}

inline std::unique_ptr<Enemy> makeWitch() {
    return std::make_unique<Enemy>(
        "Witch", 40, 8, 4, 20, 10, ETHEREAL, 80,
        [](Character& target) {
            int damage = 20;
            target.takeDamage(damage, MAGICAL);
        },
        [](Character& target) {
            int damage = 10 + 20;
            target.takeDamage(damage, MAGICAL);
        }
    );
}

inline std::unique_ptr<Enemy> makeWizard() {
    return std::make_unique<Enemy>(
        "Wizard", 45, 10, 6, 22, 12, ETHEREAL, 90,
        [](Character& target) {
            int damage = 22;
            target.takeDamage(damage, MAGICAL);
        },
        [](Character& target) {
            int damage = 8 + 22;
            target.takeDamage(damage, MAGICAL);
        }
    );
}

inline std::unique_ptr<Enemy> makeFireWorm() {
    return std::make_unique<Enemy>(
        "Fire Worm", 80, 25, 12, 15, 8, ETHEREAL, 150,
        [](Character& target) {
            int damage = 25;
            target.takeDamage(damage, PHYSICAL);
        },
        [](Character& target) {
            int damage = 15 + 15;
            target.takeDamage(damage, MAGICAL);
        }
    );
}

inline std::unique_ptr<Enemy> makeSlime() {
    return std::make_unique<Enemy>(
        "Slime", 30, 8, 2, 0, 0, ETHEREAL, 50,
        [](Character& target) {
            int damage = 8;
            target.takeDamage(damage, PHYSICAL);
        },
        [](Character& target) {
            int damage = 3 + 8;
            target.takeDamage(damage, PHYSICAL);
        }
    );
}