#pragma once
#include "../include/base.h"


#include <random>
#include "../Node/node.h"
#include "../Node/BattleNode.h"
#include "../Node/ShopNode.h"
#include "../Node/EventNode.h"
#include "../Node/BossNode.h"

class Floor {
private:
    std::vector<std::vector<std::unique_ptr<Node>>> steps;
    
    std::unique_ptr<Node> generateRandomNodes(std::mt19937& gen, bool& shopExists);

public:
    Floor(int currentFloor);
    void generateFloor(int currentFloor);

    //steps[step][branch] itu node
    //steps[step] itu branch kalo ada
    Node* getNode(size_t step, size_t branch = 0) const {
        if (step < steps.size() && branch < steps[step].size())
            return steps[step][branch].get();
        return nullptr;
    }

     const std::vector<std::vector<std::unique_ptr<Node>>>& getSteps() const { return steps; }  
     
};