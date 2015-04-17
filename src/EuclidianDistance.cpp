#include "../include/EuclidianDistance.h"
#include "../include/Kmeans.h"
#include <vector>
#include <math.h>
#include <iterator>

template <typename PointsBaseType, typename IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
class Kmeans;

EuclidianDistance::EuclidianDistance()
{

}

EuclidianDistance::~EuclidianDistance()
{
    //dtor
}

template <typename PointsBaseType, typename IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
void EuclidianDistance::Iterate (Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>& km)
{
    distances.resize(km.clusters_number, std::vector<double>(km.dataset.size()));
    //calculate points-centroids distance
    for (int i = 0; i < km.clusters_number; ++i)
    {
        for (int j = 0; j < km.dataset.size(); ++j)
        {
            double temp = 0.0;
            for (int k = 0; k < km.dataset[i].size(); k++)
            {
                temp += pow((km.dataset[j][k] - km.centroids[i][k]), 2);
            }
            distances[i][j] = sqrt(temp);
        }
    }

    //assign points to clusters
    int min_distance_index;
    for (int i = 0; i < km.points_number; ++i)
    {
        min_distance_index = 0;
        for (int j = 0; j < km.clusters_number; ++j)
        {
            if (distances[j][i] < distances[min_distance_index][i])
                min_distance_index = j;
        }

        for (int k = 0; k < km.dataset[i].size(); ++k)
        {

            typename std::vector<PointsBaseType>::iterator it = km.dataset[i].begin();
            std::advance(it, k);
            std::cout << *it;
            km.assignments[min_distance_index].resize(km.clusters_number);
            km.assignments[min_distance_index][i].push_back(&(*it));
            //std::cout << "Cluster: " << min_distance_index << " Point [" << i << "][" << k << "]" << std::endl;
        }
        //std::cout << std::endl;
    }

    //re-calculate clusters means
    std::vector < std::vector < PointsBaseType > > cluster_count;
    cluster_count.resize(km.clusters_number, std::vector < PointsBaseType > (km.coordinates_number));
    for (int i = 0; i < km.clusters_number; ++i)
    {

        for (int j = 0; j < km.assignments.size(); ++j)
        {
            for (int k = 0; k < km.assignments.size(); ++k)
            {
                //cluster_count[i] = *(km.assignments[i][j]);
                //std::cout << (km.assignments[i][j])->[k] << std::endl;
            }

            for (int k = 0; k < km.coordinates_number; ++k)
            {
                km.centroids[i][k] = cluster_count[i][k]/cluster_count[i].size();
            }
        }
    }

    if (km.assignments.size() < km.clusters_number)
    {
        //km.empty_cluster_handler.HandleEmptyClusters();
    }
}

template void EuclidianDistance::Iterate (Kmeans<float, EuclidianDistance, PointStealer, RandomPoints>& km);

