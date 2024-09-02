#include "Helper.hpp"


std::vector<std::unique_ptr<HelpLine>> Helper::lines{};

void Helper::init(int count)
{
    for(int i = 0; i < count; i++) {
        lines.push_back(std::make_unique<HelpLine>());
    }
}
