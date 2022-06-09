//
// Created by jiang on 2022/5/27.
//

#ifndef GRIDMAP_GRIDMAP_H
#define GRIDMAP_GRIDMAP_H

#include <vector>
#include <map>
#include <unordered_map>

#include "Types.h"

class GridMap {
private:
    using TickIdType = int;
    using GridIdType = std::pair<TickIdType, TickIdType>;

    double _gridSize;

    // Grid id is a pair which specifies the discrete position of the grid's left-down corner.
    // i.e. <floor(X / Grid_Size), floor(Y / Grid_Size)>.

    // The map stores instances within the grid.
    std::map<GridIdType, std::vector<InstanceType>> _gridInstances;
    // The variable maps to the instances on which the specific horizontal edge. The edge is named by its left point.
    std::map<GridIdType, std::vector<InstanceType>> _instancesOnHorizontalEdge;
    // The variable maps to the instances on which the specific vertical edge. The edge is named by its bottom point.
    std::map<GridIdType, std::vector<InstanceType>> _instancesOnVerticalEdge;

    std::map<GridIdType, std::vector<InstanceType>> _surroundInstances;
private:
    void _addInstance(const InstanceType &instance);

    std::vector<InstanceType> _getGridInstances(const GridIdType &gridId);

public:
    GridMap(double gridSize);
    GridMap(double gridSize, const std::vector<InstanceType> &instances);

    std::vector<InstanceType> getSurroundInstances(const InstanceType &instance);
};


#endif //GRIDMAP_GRIDMAP_H
