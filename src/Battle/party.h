#pragma once
#include "../Entity/character.h"



class Party {
private:
    std::vector<std::unique_ptr<Character>> members;

public:
    Party() = default;

    // Add a character to the party
    void addMember(std::unique_ptr<Character> character) {
        members.push_back(std::move(character));
    }

    // Get a pointer to a character by index
    Character* getMember(size_t index) {
        if (index < members.size()) {
            return members[index].get();
        }
        return nullptr;
    }

    // Get the number of party members
    size_t size() const {
        return members.size();
    }

    // Check if all party members are defeated
    bool allDefeated() const {
        for (const auto& member : members) {
            if (member->isAlive()) return false;
        }
        return true;
    }

    // Get all alive members' indices
    std::vector<size_t> getAliveIndices() const {
        std::vector<size_t> indices;
        for (size_t i = 0; i < members.size(); ++i) {
            if (members[i]->isAlive()) {
                indices.push_back(i);
            }
        }
        return indices;
    }

    // Access to the underlying vector (const)
    const std::vector<std::unique_ptr<Character>>& getMembers() const {
        return members;
    }
};