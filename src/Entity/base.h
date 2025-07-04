#pragma once

#include "../include/base.h"

#include <memory>

extern int globalAP;
void resetGlobalAP();

typedef enum ENTITY_TYPE
{
    MORTAL = 0,
    ETHEREAL,
    CONSTRUCT
} ENTITY_TYPE;

typedef enum ATTACK_TYPE
{
    PHYSICAL = 0,
    MAGICAL
} ATTACK_TYPE;

typedef struct
{
    std::string name;
    int APCost;
    ATTACK_TYPE attackType;
} Action;

class Entity
{

protected:
    std::string name;
    int hp, maxHp;
    int atk, def, mag, res;
    ENTITY_TYPE ent_type;

public:
    Entity(const std::string &name, int hp, int atk, int def, int mag, int res, ENTITY_TYPE ent_type)
        : name(name), hp(hp), maxHp(hp), atk(atk), def(def), mag(mag), res(res), ent_type(ent_type) {}

    virtual ~Entity() = default;

    virtual void takeDamage(int dmg, ATTACK_TYPE attackType)
    {
        switch (attackType)
        {
        case PHYSICAL:
            dmg -= def; // MASIH PERLU PENGECEKAN KARENA KALO DEF > ATK, Dmg bisa negatif DAN MALAH NGEHEAL, // Update udah di bawah tpai jadi kebal bukan ngurangin dikit
            break;
        case MAGICAL:
            dmg -= res;
            break;
        }
        if (dmg < 0)
            dmg = 0; // Prevent healing
        hp -= dmg;
        if (hp < 0)
            hp = 0;
    }
    void heal(int amount)
    {
        hp += amount;
        if (hp > maxHp)
            hp = maxHp; // Cap HP at max HP
    }

    bool isAlive() const { return hp > 0; }
    bool isDominant(ENTITY_TYPE otherType) const
    {
        if (ent_type == MORTAL && otherType == ETHEREAL)
            return true;
        if (ent_type == ETHEREAL && otherType == CONSTRUCT)
            return true;
        if (ent_type == CONSTRUCT && otherType == MORTAL)
            return true;
        return false;
    }

    const std::string &getName() const { return name; }
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHp; }
    int getATK() const { return atk; }
    int getDEF() const { return def; }
    int getINT() const { return mag; }
    int getRES() const { return res; }
    
    ENTITY_TYPE getType() const { return ent_type; }

    void setHP(int value) { hp = value; }
    void setMaxHP(int value) { 
        int currentHP = getHP(); 
        int currentMaxHP = getMaxHP();
        setHP(currentHP + (value - currentMaxHP)); 
        maxHp = value; }
    void setATK(int value) { atk = value; }
    void setDEF(int value) { def = value; }
    void setINT(int value) { mag = value; }
    void setRES(int value) { res = value; }
    
};
