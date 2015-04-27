#include "../include/PointStealer.h"
#include "../include/EuclidianDistance.h"
#include <iostream>
#include <set>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <utility>

class EuclidianDistance;

PointStealer::PointStealer()
{
    //ctor
}

PointStealer::~PointStealer()
{
    //dtor
}

std::pair<int, int> PointStealer::HandleEmptyClusters(EuclidianDistance &iter_method, int empty_cluster)
{
    std::vector<double> cluster_variances;
    cluster_variances.resize(iter_method.distances.size());
    for (unsigned int j = 0; j < iter_method.distances.size(); ++j)
    {
        //find cluster variance
        for (unsigned int i = 0; i < iter_method.new_assignments[j].size(); ++i)
        {
            cluster_variances[j] += iter_method.distances[j][i];
        }
    }


    //weight sums of distances with cluster's points number or with infinity in case cluster contains one point only to exclude cluster from donor candidates;
    int maxVarianceCluster = 0;
    for (unsigned int j = 0; j < iter_method.distances.size(); ++j)
    {
        cluster_variances[j] /= cluster_variances[j]/ ((iter_method.new_assignments[j].size() == 1) ? std::numeric_limits<int>::max() : iter_method.new_assignments[j].size());
        if (cluster_variances[j] > maxVarianceCluster)
        {
            maxVarianceCluster = j;
        }
    }

    //find the furthest point of cluster with max variance
    double maxDistance = std::numeric_limits<double>::max();
    int furthest_point;
    for (unsigned int i = 0; i < iter_method.distances.size(); ++i)
    {
        for (unsigned int j = 0; j < iter_method.distances[maxVarianceCluster].size(); ++j)
        {
            if (cluster_variances[j] > maxVarianceCluster)
            {
                maxDistance = iter_method.distances[j][i];
                furthest_point = i;
            }
        }
    }

    return std::make_pair(furthest_point, maxVarianceCluster);
   /* //move closest points to empty clusters
    for(int e = 0; e < iter_method.empty_clusters_indexes.size(); ++e)
    {
        //find clostest point
        int empty_cluster = iter_method.empty_clusters_indexes.at(e);
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
        for (int j = 0; j < iter_method.new_assignments.size(); ++j)
        {
        //if the point is in current cluster push it to empty cluster and erase from the really closest one
            std::vector<int>::iterator it = std::find(iter_method.new_assignments[j].begin(), iter_method.new_assignments[j].end(), min_point_index);
            if(it!=iter_method.new_assignments[j].end())
            {
                iter_method.new_assignments[empty_cluster].emplace_back(min_point_index);
                iter_method.new_assignments[j].erase(it);
                break;
            }
        }
    }*/
}
