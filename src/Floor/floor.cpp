#include "floor.h"
#include "../Battle/enemy_template.h"
#include "../Battle/enemy_group.h"

Floor::Floor(int currentFloor)
{
    generateFloor(currentFloor);
}

std::unique_ptr<Node> Floor::generateRandomNodes(std::mt19937 &gen, bool& shopExists)
{
    std::uniform_int_distribution<> dist(0, 2);
    int type = dist(gen);

    if (shopExists) {
        // Only allow BATTLE or EVENT
        type = (dist(gen) % 2 == 0) ? BATTLE : EVENT;
    }

    switch(type)
    {
    case BATTLE: {
        EnemyGroup group;
        std::uniform_int_distribution<> enemyCountDist(2, 3); // 2 or 3 enemies
        int numEnemies = enemyCountDist(gen);
        std::uniform_int_distribution<> templateDist(0, ENEMY_TEMPLATES.size() - 1);
        for (int i = 0; i < numEnemies; ++i) {
            int idx = templateDist(gen);
            group.addEnemy(ENEMY_TEMPLATES[idx]());
        }
        return std::make_unique<BattleNode>(BATTLE, "Battle", "A fierce battle awaits!", std::move(group));
    }
    case SHOP: {
        shopExists = true;
        return std::make_unique<ShopNode>(SHOP, "Shop", "A place to buy items.");
    }
    case EVENT: {
        return std::make_unique<EventNode>(EVENT, "Event", "A mysterious event occurs.");
    }
    }
    return nullptr;
}

void Floor::generateFloor(int currentFloor)
{
    bool shopExists = false;

    steps.clear();
    std::random_device rd;
    std::mt19937 gen(rd());

    // Step 1: single node
    std::vector<std::unique_ptr<Node>> step1;
    step1.push_back(generateRandomNodes(gen, shopExists));
    steps.push_back(std::move(step1));

    // Step 2: branch (2 nodes)
    std::vector<std::unique_ptr<Node>> step2;
    step2.push_back(generateRandomNodes(gen, shopExists));
    step2.push_back(generateRandomNodes(gen, shopExists));
    steps.push_back(std::move(step2));

    // Step 3: single node
    std::vector<std::unique_ptr<Node>> step3;
    step3.push_back(generateRandomNodes(gen, shopExists));
    steps.push_back(std::move(step3));

    // Step 4: branch (2 nodes)
    std::vector<std::unique_ptr<Node>> step4;
    step4.push_back(generateRandomNodes(gen, shopExists));
    step4.push_back(generateRandomNodes(gen, shopExists));
    steps.push_back(std::move(step4));

    // Step 5: single node
    std::vector<std::unique_ptr<Node>> step5;
    step5.push_back(std::make_unique<BossNode>(BOSS, "Boss", "The final boss of this floor!"));
    steps.push_back(std::move(step5));
}