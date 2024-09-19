#include "LoaderPostprocess.hpp"

Mesh LoaderPostprocess::convert(Vertices &vertices, Indices &indices)
{
    auto [vertOpt, indOpt] = getOptimalize(vertices, indices);
    Border border          = calcBorder(vertOpt);
    return Mesh(vertices, indices, vertOpt, indOpt, border);
}


auto LoaderPostprocess::getOptimalize(
Vertices &vertices, Indices &indices) -> std::pair<VerticesOpt, Indices>
{
    VerticesOpt verticesOpt;
    Indices indicesOpt;
    for(Index index: indices) {
        Position pos = vertices[index].Position;
        auto itPos   = std::find(verticesOpt.begin(), verticesOpt.end(), pos);
        if(itPos == verticesOpt.end()) {
            verticesOpt.push_back(pos);
            indicesOpt.push_back(index);
            continue;
        }
        indicesOpt.push_back(itPos - verticesOpt.begin());
    }
    return {verticesOpt, indicesOpt};
}

Border LoaderPostprocess::calcBorder(VerticesOpt vertices)
{
    Border border;
    if(vertices.size() > 0) {
        border.setFirstPoint(vertices[0]);
    }

    for(Position &pos: vertices) {
        border.addPoint(pos);
    }
    return border;
}
