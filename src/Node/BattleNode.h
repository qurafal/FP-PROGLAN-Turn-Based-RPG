#pragma once
#include "node.h"

class BattleNode : public Node {
public:
    BattleNode(nodeType type,const std::string& name, const std::string& description)
        : Node(type, name, description) {
        
        }
   
};