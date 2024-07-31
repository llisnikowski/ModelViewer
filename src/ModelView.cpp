#include "ModelView.hpp"


ModelView::ModelView(std::string group, std::string name)
: group{group}
, name{name}
{}

ModelView::ModelView(std::vector<std::string> group, std::string name)
: group{group}
, name{name}
{}
