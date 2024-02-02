#pragma once

#include "pkb/templates/TemplateMapSet.h"

class FollowsStore {
private:
    TemplateMapSet<int, int> followsMap;
    TemplateMapSet<int, int> followedByMap;
};
