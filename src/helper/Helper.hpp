#pragma once
#include <memory>
#include <vector>
#include "HelpLine.hpp"

class Helper
{
public:
    static void init(int count);

    static std::vector<std::unique_ptr<HelpLine>> lines;
};
