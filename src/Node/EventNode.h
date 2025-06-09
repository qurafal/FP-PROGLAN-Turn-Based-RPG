#pragma once
#include "node.h"

class EventNode : public Node {
public:
    EventNode(nodeType type,const std::string& name, const std::string& description)
        : Node(type, name, description) {
        
        }
   
};