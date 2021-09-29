#pragma once

#include <map>
#include "StaticModel.h"
#include "StaticModelLoader.h"

class StaticModelCache {

private:
    static std::map<std::string, StaticModel*> cache;
    static StaticModelLoader loader;

public:
    static StaticModel * get(const std::string & path);

};