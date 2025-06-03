#pragma once
#include "../../include/base.h"
#include "../base.h"

class Skill {
public:
    std::string name;
    int apCost;
    ATTACK_TYPE attackType;

    Skill(const std::string& name, int apCost, ATTACK_TYPE attackType)
        : name(name), apCost(apCost), attackType(attackType) {}
};