#include "log.hpp"


std::ostream& operator<<(std::ostream& os, const glm::vec4& vec)
{
    return os << "vec4[" << vec.x << "; " << vec.y << "; " << vec.z << "; "
              << vec.w << "]";
}

std::ostream& operator<<(std::ostream& os, const glm::vec3& vec)
{
    return os << "vec3[" << vec.x << "; " << vec.y << "; " << vec.z << "]";
}

std::ostream& operator<<(std::ostream& os, const glm::vec2& vec)
{
    return os << "vec2[" << vec.x << "; " << vec.y << "]";
}

std::ostream& operator<<(std::ostream& os, const glm::quat& quat)
{
    return os << "quat[" << quat.x << "; " << quat.y << "; " << quat.z << "; "
              << quat.w << "]";
}

std::ostream& operator<<(std::ostream& os, const glm::mat4& mat)
{
    return os << "mat4[[" << mat[0][0] << "; " << mat[0][1] << "; " << mat[0][2]
              << "; " << mat[0][3] << "]; [" << mat[1][0] << "; " << mat[1][1]
              << "; " << mat[1][2] << "; " << mat[1][3] << "]; [" << mat[2][0]
              << "; " << mat[2][1] << "; " << mat[2][2] << "; " << mat[2][3]
              << "]; [" << mat[3][0] << "; " << mat[3][1] << "; " << mat[3][2]
              << "; " << mat[3][3] << "]";
}

std::ostream& operator<<(std::ostream& os, glm::mat4&& mat)
{
    return os << "mat4[[" << mat[0][0] << "; " << mat[0][1] << "; " << mat[0][2]
              << "; " << mat[0][3] << "]; [" << mat[1][0] << "; " << mat[1][1]
              << "; " << mat[1][2] << "; " << mat[1][3] << "]; [" << mat[2][0]
              << "; " << mat[2][1] << "; " << mat[2][2] << "; " << mat[2][3]
              << "]; [" << mat[3][0] << "; " << mat[3][1] << "; " << mat[3][2]
              << "; " << mat[3][3] << "]";
}
