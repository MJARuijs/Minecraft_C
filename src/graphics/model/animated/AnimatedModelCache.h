#pragma once

#include <map>
#include "../static/StaticModelLoader.h"
#include "AnimatedModel.h"
#include "AnimatedModelLoader.h"

class AnimatedModelCache {

private:
    static std::map<std::string, AnimatedModel*> cache;
    static AnimatedModelLoader loader;

public:
    static AnimatedModel * get(const std::string & path);

};