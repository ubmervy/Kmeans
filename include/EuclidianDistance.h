#ifndef EUCLIDIANDISTANCE_H
#define EUCLIDIANDISTANCE_H
#include "../include/PointStealer.h"
#include <vector>
#include <map>
#include <utility>

template <typename PointsBaseType, typename EmptyClusterPolicy, typename IterationMethod, typename InitialCentroids>
class Kmeans;

class EuclidianDistance
{
    public:
        EuclidianDistance();
        virtual ~EuclidianDistance();

        std::vector <std::vector <double>> distances;
        std::map<int, std::vector<int>> new_assignments;
        std::vector<int> empty_clusters_indexes;

        template <typename PointsBaseType, typename EmptyClusterPolicy, typename IterationMethod, typename InitialCentroids>
        void Iterate(Kmeans<PointsBaseType, EmptyClusterPolicy, IterationMethod, InitialCentroids>& km);

        friend std::pair<int, int> PointStealer::HandleEmptyClusters(EuclidianDistance &iter_method, int empty_cluster);
};

#endif // EUCLIDIANDISTANCE_H
