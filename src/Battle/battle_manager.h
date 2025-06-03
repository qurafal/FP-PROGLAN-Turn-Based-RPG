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

    
    void resetAP() {
        globalAP = maxAP;
    }

    
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

    
    bool isBattleOver() const {
        return party.allDefeated() || enemyGroup.allDefeated();
    }

    
    bool isPlayerVictory() const {
        return enemyGroup.allDefeated() && !party.allDefeated();
    }

    
    bool isPlayerDefeat() const {
        return party.allDefeated();
    }

    
};