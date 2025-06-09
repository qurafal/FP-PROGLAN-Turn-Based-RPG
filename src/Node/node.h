#pragma once
#include "../include/base.h"

typedef enum nodeType{
    BATTLE,
    EVENT,
    SHOP,
    BOSS
}nodeType;

class Node {
private:
    std::string name;
    std::string description;
    Node* parent = nullptr;
    bool visited = false;
    nodeType type;

public:
    Node(nodeType type, const std::string& name, const std::string& description)
        :  name(name), description(description), type(type) {};


    //Simple func
    std::string getName() {return name;}
    void setName(const std::string& newName) {name = newName;}

    std::string getDescription() {return description;}
    void setDescription(const std::string& newDescription) {description = newDescription;}

    nodeType getType() {return type;}
    void setType(nodeType newType) {type = newType;}

    bool isVisited() const { return visited; }
    void setVisited(bool visitedStatus) {
        visited = visitedStatus;
    }

};