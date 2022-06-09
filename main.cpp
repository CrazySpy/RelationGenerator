#include <iostream>
#include <string>
#include <fstream>

#include "GridMap.h"
#include "CSVReader/CSVReader.h"
#include "Utils.h"
using namespace std;

int main(int argc, char **argv) {
    if(argc != 3) {
        cout << "Argument number must be 3" << endl;
        cout << argv[0] << " <distance_threshold> <dataset_path>" << endl;
        return 0;
    }
    double distanceThreshold = stod(argv[1]);
    string dataset = argv[2];

    std::vector<InstanceType> instances;

    CSVReader csvReader(dataset);
    while(csvReader.hasNext()) {
        auto line = csvReader.getNextRecord();
        auto feature = line[0];
        auto id = stoul(line[1]);
        auto x = stod(line[2]), y = stod(line[3]);

        instances.push_back({feature, id, {x, y}});
    }
    cout << instances.size() << endl;

    GridMap gridMap(distanceThreshold, instances);

    ofstream ofs("relations_" + string(argv[1]) + ".csv");
    ofs << "Feature1,Id1,Feature2,Id2" << endl;
    for(int i = 0; i < instances.size(); ++i) {
        if(i % 1000 == 0) cout << i << endl;
        auto &instance1 = instances[i];
        auto candidateNeighbors = gridMap.getSurroundInstances(instance1);
        for(auto &candidateNeighbor : candidateNeighbors) {
            if(instance1.feature >= candidateNeighbor.feature) continue;

            double distance = euclidDistance(instance1.location, candidateNeighbor.location);
            if(distance <= distanceThreshold) {
                ofs << instance1.feature << "," << instance1.id << ","
                    << candidateNeighbor.feature << "," << candidateNeighbor.id
                    << endl;
            }
        }
    }

    return 0;
}
