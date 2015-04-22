#include "../include/PointStealer.h"
#include "../include/EuclidianDistance.h"
#include <iostream>
#include <set>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

template <typename PointsBaseType, typename EmptyClusterPolicy>
class EuclidianDistance;

PointStealer::PointStealer()
{
    //ctor
}

PointStealer::~PointStealer()
{
    //dtor
}

template<typename PointsBaseType, typename EmptyClusterPolicy, template<typename, typename> class IterationMethod, typename InitialCentroids>
void PointStealer::HandleEmptyClusters(EuclidianDistance<PointsBaseType, EmptyClusterPolicy> &iter_method,
                                       Kmeans<PointsBaseType, EmptyClusterPolicy, IterationMethod, InitialCentroids>& km)
{
    //find empty clusters indexes
    std::vector<int> empty_clusters_indexes;
    for (int i = 0; i < iter_method.distances.size(); ++i)
    {
        if (iter_method.new_assignments.find(i)==iter_method.new_assignments.end())
        {
            empty_clusters_indexes.emplace_back(i);
        }
    }

    //move closest points to empty clusters
    while(!empty_clusters_indexes.empty())
    {
        //find clostest point
        int empty_cluster = empty_clusters_indexes.back();
        int min_distance_point = std::numeric_limits<float>::max();
        int min_point_index;

        for (int i = 0; i < iter_method.distances[empty_cluster].size(); ++i)
        {
            if(iter_method.distances[empty_cluster][i]<min_distance_point)
            {
                min_distance_point = iter_method.distances[empty_cluster][i];
                min_point_index = i;
            }
        }

        //move closest point from its closest cluster and add to new_assignments
        for (int j = 0; j < iter_method.distances.size(); ++j)
        {
            if(iter_method.new_assignments[j].find(min_point_index)!=iter_method.new_assignments[j].end())
            {
                iter_method.new_assignments[empty_cluster].emplace_back(*(iter_method.new_assignments[j].find(min_point_index)));
                iter_method.new_assignments[j].erase(iter_method.new_assignments[j].find(min_point_index));
            }
        }
    empty_clusters_indexes.pop_back();
    }
}

template void PointStealer::HandleEmptyClusters(EuclidianDistance<float, PointStealer> &iter_method,
        Kmeans<float, PointStealer, EuclidianDistance, RandomPoints>& km);
