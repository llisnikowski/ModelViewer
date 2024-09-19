#pragma once
#include "Loader.hpp"


struct Border;

class LoaderPostprocess : public Loader::Postprocess
{
public:
    using Index       = unsigned int;
    using Indices     = std::vector<Index>;
    using Vertices    = std::vector<Vertex>;
    using Position    = glm::vec3;
    using VerticesOpt = std::vector<Position>;
    using Line        = std::pair<Index, Index>;
    using Lines       = std::vector<Line>;

    Mesh convert(Vertices &vertices, Indices &indices) override;

private:
    std::pair<VerticesOpt, Indices> getOptimalize(
    Vertices &vertices, Indices &indices);
    Border calcBorder(VerticesOpt vertices);
};
