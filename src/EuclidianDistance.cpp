#include "../include/EuclidianDistance.h"
#include "../include/PointStealer.h"
#include "../include/Kmeans.h"
#include <vector>
#include <math.h>
#include <iterator>
#include <limits>
#include <algorithm>

template <typename PointsBaseType, typename EmptyClusterPolicy, template<typename, typename> class IterationMethod, typename InitialCentroids>
class Kmeans;

template<typename PointsBaseType, typename EmptyClusterPolicy>
EuclidianDistance<PointsBaseType, EmptyClusterPolicy>::EuclidianDistance()
{

}

template<typename PointsBaseType, typename EmptyClusterPolicy>
EuclidianDistance<PointsBaseType, EmptyClusterPolicy>::~EuclidianDistance()
{
    //dtor
}

template<typename PointsBaseType, typename EmptyClusterPolicy>
template <template<typename, typename> class IterationMethod, typename InitialCentroids>
void EuclidianDistance<PointsBaseType, EmptyClusterPolicy>::Iterate (Kmeans<PointsBaseType, EmptyClusterPolicy, IterationMethod, InitialCentroids>& km)
{
    int iterations = km.max_iterations;
    //iterate till max_iterations or exit criteria is reached
    while (iterations)
    {
        int min_distance_cluster;
        double min_distance;
        points_movements = km.points_number;
        bool centroid_moved = false;
        std::vector<double> centroid_movements;
        centroid_movements.resize(km.centroids[0].size());
        distances.resize(km.clusters_number, std::vector<double>(km.points_number));
        std::cout << "iteration " << km.max_iterations-iterations << std::endl;
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

                distances[j][i] = sqrt(distances[j][i]);//actually this is unnecessary for comparing distances but is expected following the class name

                if (distances[j][i] < min_distance)
                {
                    min_distance_cluster = j;
                    min_distance = distances[j][i];
                }
            }

            //if there have been assignments (not the first iteration) the number of moved points can be found
            if(!km.assignments[min_distance_cluster].empty())
            {
                points_movements = 0;
                //if point is not in closetst cluster increment points_movement counter
                if(std::find(km.assignments[min_distance_cluster].begin(), km.assignments[min_distance_cluster].end(), &(km.dataset[i])) == km.assignments[min_distance_cluster].end())
                {
                    points_movements++;
                }
            }
            new_assignments[min_distance_cluster].push_back(&(km.dataset[i]));
            std::cout << "point " << i << " - cluster" << min_distance_cluster << std::endl;
        }

//check for empty clusters
        if (new_assignments.size() < km.clusters_number)
        {
            km.ecp.HandleEmptyClusters(*this, km);
        }

//apply new point assignments to km.assignment map
        km.assignments.swap(new_assignments);

        std::cout << "points_movements: " << points_movements << std::endl;

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
                for (int i = 0; i < new_assignments[j].size(); ++i)
                {
                    new_centroids[j][k] += new_assignments[j][i]->at(k);
                }
                //std::cout << km.assignments[j][k]->at(k) << std::endl;

                new_centroids[j][k] /= new_assignments[j].size();
            }

            if(!centroid_moved)
            {
                for (int k = 0; k < km.coordinates_number; ++k)
                {
                    centroid_movements[j] += pow((new_centroids[j][k]-km.centroids[j][k]), 2);
                }
                //maximum centroid movement distance can be found to compare with given threshold
                if(sqrt(centroid_movements[j])>km.centroid_movement_thrsh)
                {
                    centroid_moved = true;
                }
                std::cout << "centroid_movement [" << j << "]: " << sqrt(centroid_movements[j]) << std::endl;
            }

            std::cout << "centroid " << j << ": " << new_centroids[j][0] << '\t' << new_centroids[j][1];
            std::cout << std::endl;
        }

//check if exit criteria is reached
        if((points_movements <= km.points_move_thrsh) || (!centroid_moved))
        {
            return;
        }

        iterations--;
    }
}

template void EuclidianDistance<float, PointStealer>::Iterate (Kmeans<float, PointStealer, EuclidianDistance, RandomPoints>& km);
template class EuclidianDistance<float, PointStealer>;

