#pragma once
#include "../include/base.h"

#pragma once
#include "party.h"
#include "enemy_group.h"

class BattleManager {
private:
    Party party;
    EnemyGroup enemyGroup;
    int maxAP;

public:
    BattleManager(Party&& party, EnemyGroup&& enemyGroup)
        : party(std::move(party)), enemyGroup(std::move(enemyGroup)) {
        maxAP = this->party.size() * 3;
        globalAP = maxAP;
    }

    // Reset AP at the start of each turn
    void resetAP() {
        globalAP = maxAP;
    }

    // Try to use AP, return true if successful
    bool useAP(int amount) {
        if (globalAP >= amount) {
            globalAP -= amount;
            return true;
        }
        return false;
    }

    int getAP() const { return globalAP; }
    int getMaxAP() const { return maxAP; }

    Party& getParty() { return party; }
    EnemyGroup& getEnemyGroup() { return enemyGroup; }

    // Check if battle is over (win/lose)
    bool isBattleOver() const {
        return party.allDefeated() || enemyGroup.allDefeated();
    }

    // Returns true if player won
    bool isPlayerVictory() const {
        return enemyGroup.allDefeated() && !party.allDefeated();
    }

    // Returns true if player lost
    bool isPlayerDefeat() const {
        return party.allDefeated();
    }

    // Add more methods for turn management, action queue, etc. as needed
};