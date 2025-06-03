#pragma once
#include <cstdint>
#include "base.h"

///STILL UNUSED

class hp{
    private:
        uint16_t currentHp;
        uint16_t maxHp;

    public:
        hp(uint16_t max) : maxHp(max), currentHp(max) {} 
        void setMaxHp(uint16_t max) {
            maxHp = max;
            currentHp = max; 
        }
        void setCurrentHp(uint16_t current) {
            currentHp = current;
            if (currentHp > maxHp) {
                currentHp = maxHp;
            }
        }
        uint16_t getCurrentHp() const {
            return currentHp;
        }
        uint16_t getMaxHp() const {
            return maxHp;
        }
        
        
        bool isAlive() const {
            return currentHp > 0; 
        }
        void reset() {
            currentHp = maxHp; 
        }
};
