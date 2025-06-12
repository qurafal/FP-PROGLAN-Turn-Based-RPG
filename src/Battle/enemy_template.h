// enemy_templates.h
#pragma once
#include "../Entity/enemies.h"
#include <vector>
#include <functional>
#include <memory>

inline const std::vector<std::function<std::unique_ptr<Enemy>()>> ENEMY_TEMPLATES = {
    makeGoblin,
    makeSkeleton,
    makeWitch,
    makeWizard,
    makeFireWorm,
    makeSlime
};