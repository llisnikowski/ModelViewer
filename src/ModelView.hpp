#pragma once
#include <string>
#include <vector>


struct ModelView
{
    ModelView(std::string group, std::string name);
    ModelView(std::vector<std::string> group, std::string name);

    std::vector<std::string> group;
    std::string name;
    bool show{true};
};
