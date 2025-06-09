#pragma once
#include "../Entity/character.h"

class Party
{
private:
    std::vector<std::unique_ptr<Character>> members;

public:
    Party() = default;

    void addMember(std::unique_ptr<Character> character)
    {
        members.push_back(std::move(character));
    }

    int findMemberByName(const std::string &name) const
    {
        for (size_t i = 0; i < members.size(); ++i)
        {
            if (members[i]->getName() == name)
                return static_cast<int>(i);
        }
        return -1;
    }

    void removeMemberByName(const std::string &name)
    {
        int idx = findMemberByName(name);
        if (idx != -1)
        {
            members.erase(members.begin() + idx);
        }
    }

    Character *getMember(size_t index)
    {
        if (index < members.size())
        {
            return members[index].get();
        }
        return nullptr;
    }

    size_t size() const
    {
        return members.size();
    }

    bool allDefeated() const
    {
        for (const auto &member : members)
        {
            if (member->isAlive())
                return false;
        }
        return true;
    }

    std::vector<size_t> getAliveIndices() const
    {
        std::vector<size_t> indices;
        for (size_t i = 0; i < members.size(); ++i)
        {
            if (members[i]->isAlive())
            {
                indices.push_back(i);
            }
        }
        return indices;
    }

    std::vector<std::unique_ptr<Character>> &getMembers()
    {
        return members;
    }
};