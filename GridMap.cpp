//
// Created by jiang on 2022/5/27.
//

#include <algorithm>
#include <cmath>

#include "GridMap.h"
#include "Utils.h"

GridMap::GridMap(double gridSize) : _gridSize(gridSize) {

}

GridMap::GridMap(double gridSize, const std::vector<InstanceType> &instances) : _gridSize(gridSize) {
    for(auto &instance : instances) {
        _addInstance(instance);
    }
}

void GridMap::_addInstance(const InstanceType &instance) {
    auto &location = instance.location;
    GridIdType gridId = {std::floor(location.first / _gridSize), std::floor(location.second / _gridSize)};

    if(!doubleEqual(gridId.first * _gridSize, location.first) && !doubleEqual(gridId.second * _gridSize, location.second)) {
        _gridInstances[gridId].push_back(instance);
    } else {
        if (doubleEqual(gridId.first * _gridSize, location.first)) {
            _instancesOnVerticalEdge[gridId].push_back(instance);
        }
        if (doubleEqual(gridId.second * _gridSize, location.second)) {
            _instancesOnHorizontalEdge[gridId].push_back(instance);
        }
    }
}

std::vector<InstanceType> GridMap::_getGridInstances(const GridMap::GridIdType &gridId) {
    auto &instancesInGrid = _gridInstances[gridId];
    auto &instancesOnVerticalEdges = _instancesOnVerticalEdge[gridId];
    auto &instancesOnHorizontalEdges = _instancesOnHorizontalEdge[gridId];

    auto gridInstances = instancesInGrid;
    gridInstances.insert(gridInstances.end(), instancesOnVerticalEdges.begin(), instancesOnVerticalEdges.end());
    gridInstances.insert(gridInstances.end(), instancesOnHorizontalEdges.begin(), instancesOnHorizontalEdges.end());

    //std::sort(std::begin(gridInstances), std::end(gridInstances));
    //gridInstances.erase(std::unique(std::begin(gridInstances), std::end(gridInstances)), gridInstances.end());

    return gridInstances;
}

std::vector<InstanceType> GridMap::getSurroundInstances(const InstanceType &instance) {
    auto &location = instance.location;
    GridIdType gridId = {std::floor(location.first / _gridSize), std::floor(location.second / _gridSize)};
    if(_surroundInstances.count(gridId)) return _surroundInstances[gridId];

    auto surroundInstances = _getGridInstances(gridId);

    const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const int dy[] = {1, 0, -1, -1, -1, 0, 1, 1};
    for(int i = 0; i < 9; ++i) {
        GridIdType newGridId = gridId;
        newGridId.first = gridId.first + dx[i];
        newGridId.second = gridId.second + dy[i];

        auto gridInstances = _getGridInstances(newGridId);
        surroundInstances.insert(surroundInstances.end(), gridInstances.begin(), gridInstances.end());
    }

    std::sort(std::begin(surroundInstances), std::end(surroundInstances));
    surroundInstances.erase(std::unique(std::begin(surroundInstances), std::end(surroundInstances)), surroundInstances.end());

    return _surroundInstances[gridId] = std::move(surroundInstances);
}
