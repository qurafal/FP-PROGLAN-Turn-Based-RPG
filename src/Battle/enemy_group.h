#pragma once

#include "../Entity/enemies.h"

class EnemyGroup {
private:
    std::vector<std::unique_ptr<Enemy>> enemies;

public:
    EnemyGroup() = default;

    // Add an enemy to the group
    void addEnemy(std::unique_ptr<Enemy> enemy) {
        enemies.push_back(std::move(enemy));
    }

    // Get a pointer to an enemy by index
    Enemy* getEnemy(size_t index) {
        if (index < enemies.size()) {
            return enemies[index].get();
        }
        return nullptr;
    }

    // Get the number of enemies
    size_t size() const {
        return enemies.size();
    }

    // Check if all enemies are defeated
    bool allDefeated() const {
        for (const auto& enemy : enemies) {
            if (enemy->isAlive()) return false;
        }
        return true;
    }

    // Get all alive enemies' indices
    std::vector<size_t> getAliveIndices() const {
        std::vector<size_t> indices;
        for (size_t i = 0; i < enemies.size(); ++i) {
            if (enemies[i]->isAlive()) {
                indices.push_back(i);
            }
        }
        return indices;
    }

    // Access to the underlying vector (const)
    const std::vector<std::unique_ptr<Enemy>>& getEnemies() const {
        return enemies;
    }
};