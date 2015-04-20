#include "../include/EuclidianDistance.h"
#include "../include/Kmeans.h"
#include <vector>
#include <math.h>
#include <iterator>
#include <limits>
#include <algorithm>

template <typename PointsBaseType, template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
class Kmeans;

template<typename PointsBaseType>
EuclidianDistance<PointsBaseType>::EuclidianDistance()
{

}

template<typename PointsBaseType>
EuclidianDistance<PointsBaseType>::~EuclidianDistance()
{
    //dtor
}

template<typename PointsBaseType>
template <template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
void EuclidianDistance<PointsBaseType>::Iterate (Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>& km)
{
    distances.resize(km.clusters_number, std::vector<double>(km.points_number));
    int min_distance_cluster;
    double min_distance;
    int centroid_movement = 0;

    //calculate points-centroids distance
    for (int i = 0; i < km.points_number; ++i)
    {
        min_distance_cluster = 0;
        min_distance = std::numeric_limits<float>::max();
        for (int j = 0; j < km.clusters_number; ++j)
        {
            for (int k = 0; k < km.coordinates_number; k++)
            {
                distances[j][i] += pow((km.dataset[i][k] - km.centroids[j][k]), 2);
            }
            // std::cout << "dataset [" << j << "][" << k << "] = " << km.dataset[j][k] << std::endl;
            // std::cout << "centroids [" << i << "][" << k << "] = " << km.centroids[i][k] << std::endl;
            if (distances[j][i] < min_distance)
            {
                min_distance_cluster = j;
                min_distance = distances[j][i];
            }
        }

        //
        int points_movements = 0;
        if(!km.assignments[min_distance_cluster].empty())
        {

            //std::cout << "DDD" << &(km.dataset[i]) << std::endl;
            //std::cout << "AAA" << km.assignments[min_distance_cluster][0]->data() << std::endl;
            //std::cout << "AAA" << *(km.assignments[min_distance_cluster].begin()) << std::endl;
            if(std::find(km.assignments[min_distance_cluster].begin(), km.assignments[min_distance_cluster].end(), &(km.dataset[i])) == km.assignments[min_distance_cluster].end())
            {
                points_movements++;
            }
        }
        std::cout << "points_movements: " << points_movements << std::endl;

        km.assignments[min_distance_cluster].push_back(&(km.dataset[i]));
        std::cout << "point " << i << " - cluster" << min_distance_cluster << std::endl;

        if (km.assignments.size() < km.clusters_number)
        {
            //km.empty_cluster_handler.HandleEmptyClusters();
        }
    }

//re-calculate clusters means

//make new_centroids filled with zeros before new iteration begin
    typename std::vector <std::vector<PointsBaseType>> new_centroids;
    new_centroids.resize(km.centroids.size(), std::vector<PointsBaseType>(km.centroids[0].size()));
    for (int i = 0; i < km.centroids.size(); ++i)
    {
        std::fill(new_centroids[i].begin(), new_centroids[i].end(), 0.00);
    }

//calculate new centroid means
    for (int j = 0; j < km.clusters_number; ++j)
    {
        for (int k = 0; k < km.coordinates_number; ++k)
        {
            for (int i = 0; i < km.assignments[j].size(); ++i)
            {
                new_centroids[j][k] += km.assignments[j][i]->at(k);
            }
            //std::cout << km.assignments[j][k]->at(k) << std::endl;

            new_centroids[j][k] /= km.assignments[j].size();
        }
        std::cout << "centroid " << j << ": " << new_centroids[j][0] << '\t' << new_centroids[j][1];
        std::cout << std::endl;
    }
}

template void EuclidianDistance<float>::Iterate (Kmeans<float, EuclidianDistance, PointStealer, RandomPoints>& km);
template class EuclidianDistance<float>;

