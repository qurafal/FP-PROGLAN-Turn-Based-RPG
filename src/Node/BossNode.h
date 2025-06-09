#pragma once
#include "node.h"

class BossNode : public Node {
public:
    BossNode(nodeType type,const std::string& name, const std::string& description)
        : Node(type, name, description) {
        
        }
   
};