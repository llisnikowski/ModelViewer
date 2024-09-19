#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"


std::ostream& operator<<(std::ostream& os, const glm::vec4& vec);
std::ostream& operator<<(std::ostream& os, const glm::vec3& vec);
std::ostream& operator<<(std::ostream& os, const glm::vec2& vec);
std::ostream& operator<<(std::ostream& os, const glm::quat& quat);
std::ostream& operator<<(std::ostream& os, const glm::mat4& quat);
std::ostream& operator<<(std::ostream& os, glm::mat4&& quat);
