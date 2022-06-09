//
// Created by 蒋希文 on 2022/5/27.
//

#ifndef GRIDMAP_TYPES_H
#define GRIDMAP_TYPES_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <memory>

using InstanceIdType = unsigned int;
using FeatureType = std::string;
using LocationType = std::pair<double, double>;

struct InstanceType {
    FeatureType feature;
    InstanceIdType id;
    LocationType location;
    bool operator < (const InstanceType &rhs) const {
        return feature == rhs.feature ? id < rhs.id : feature < rhs.feature;
    }
    bool operator == (const InstanceType &rhs) const {
        return feature == rhs.feature && id == rhs.id;
    }
};

using InstanceNameType = std::pair<FeatureType, InstanceIdType>;

#endif //GRIDMAP_TYPES_H
