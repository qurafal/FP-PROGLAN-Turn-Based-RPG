#include "enemy_template.h"

// Factory function definitions
std::unique_ptr<Enemy> makeGoblin() {
    return std::make_unique<Enemy>(
        "Goblin", 50, 15, 5, 0, 0, ETHEREAL, 100,
        [](Character& target) { target.takeDamage(15, PHYSICAL); },
        [](Character& target) { target.takeDamage(25, PHYSICAL); }
    );
}

std::unique_ptr<Enemy> makeSkeleton() {
    return std::make_unique<Enemy>(
        "Skeleton", 60, 18, 8, 0, 0, ETHEREAL, 120,
        [](Character& target) { target.takeDamage(18, PHYSICAL); },
        [](Character& target) { target.takeDamage(23, PHYSICAL); }
    );
}

std::unique_ptr<Enemy> makeWitch() {
    return std::make_unique<Enemy>(
        "Witch", 40, 8, 4, 20, 10, ETHEREAL, 80,
        [](Character& target) { target.takeDamage(20, MAGICAL); },
        [](Character& target) { target.takeDamage(30, MAGICAL); }
    );
}

std::unique_ptr<Enemy> makeWizard() {
    return std::make_unique<Enemy>(
        "Wizard", 45, 10, 6, 22, 12, ETHEREAL, 90,
        [](Character& target) { target.takeDamage(22, MAGICAL); },
        [](Character& target) { target.takeDamage(30, MAGICAL); }
    );
}

std::unique_ptr<Enemy> makeFireWorm() {
    return std::make_unique<Enemy>(
        "Fire Worm", 80, 25, 12, 15, 8, ETHEREAL, 150,
        [](Character& target) { target.takeDamage(25, PHYSICAL); },
        [](Character& target) { target.takeDamage(30, MAGICAL); }
    );
}

std::unique_ptr<Enemy> makeSlime() {
    return std::make_unique<Enemy>(
        "Slime", 30, 8, 2, 0, 0, ETHEREAL, 50,
        [](Character& target) { target.takeDamage(8, PHYSICAL); },
        [](Character& target) { target.takeDamage(11, PHYSICAL); }
    );
}

const std::vector<std::function<std::unique_ptr<Enemy>()>> ENEMY_TEMPLATES = {
    makeGoblin,
    makeSkeleton,
    makeWitch,
    makeWizard,
    makeFireWorm,
    makeSlime
};