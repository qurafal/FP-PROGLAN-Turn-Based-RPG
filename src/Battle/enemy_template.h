// enemy_templates.h
#pragma once
#include "../Entity/enemies.h"
#include <vector>
#include <functional>
#include <memory>

std::unique_ptr<Enemy> makeGoblin();
std::unique_ptr<Enemy> makeSkeleton();
std::unique_ptr<Enemy> makeWitch();
std::unique_ptr<Enemy> makeWizard();
std::unique_ptr<Enemy> makeFireWorm();
std::unique_ptr<Enemy> makeSlime();

extern const std::vector<std::function<std::unique_ptr<Enemy>()>> ENEMY_TEMPLATES;