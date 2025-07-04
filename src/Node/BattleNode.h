#pragma once
#include "node.h"

#include "../Battle/enemy_group.h" 
#include "../Entity/enemies.h" 

class BattleNode : public Node {
    private:
    EnemyGroup enemies; 
public:
    BattleNode(nodeType type,const std::string& name, const std::string& description, EnemyGroup&& enemies)
        : Node(type, name, description), enemies(std::move(enemies)) {}
        
        

        EnemyGroup& getEnemies() {
            return enemies;
        }
        void setEnemies(EnemyGroup&& newEnemies) {
            enemies = std::move(newEnemies);
        }
        void addEnemy(std::unique_ptr<Enemy> enemy) {
            enemies.addEnemy(std::move(enemy));
        }
   
};