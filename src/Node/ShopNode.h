#pragma once
#include "node.h"

class ShopNode : public Node {
public:
    ShopNode(nodeType type,const std::string& name, const std::string& description)
        : Node(type, name, description) {
        
        }
   
};