#include "../include/EuclidianDistance.h"
#include "../include/PointStealer.h"
#include "../include/RandomPoints.h"
#include "../include/Kmeans.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <iterator>
#include <limits>
#include <algorithm>

template <typename PointsBaseType, typename EmptyClusterPolicy, typename IterationMethod, typename InitialCentroids>
class Kmeans;

EuclidianDistance::EuclidianDistance()
{
    //ctor
}

EuclidianDistance::~EuclidianDistance()
{
    //dtor
}

template <typename PointsBaseType, typename EmptyClusterPolicy, typename IterationMethod, typename InitialCentroids>
void EuclidianDistance::Iterate (Kmeans<PointsBaseType, EmptyClusterPolicy, IterationMethod, InitialCentroids>& km)
{
    int min_distance_cluster;
    double min_distance;
    int points_movements = km.points_number;
    bool centroid_moved = false; // flag that helps to avoid overcalculation of centroid movements
    std::vector<double> centroid_movements; //distances between centroids of current and previous iteration

    std::pair<int, int> solved_empty_cluster; //result of HandleEmptyCluster function, which returns index of furthest point (first int) of cluster with max variance (second int)

    int iterations = km.max_iterations;
    //iterate till max_iterations or other exit criteria is reached
    while (iterations)
    {
        std::cout << "iteration " << km.max_iterations-iterations << std::endl;
        //calculate points-centroids distance

        distances.resize(km.clusters_number, std::vector<double>(km.points_number));
        for (int i = 0; i < km.points_number; ++i)
        {
            points_movements = 0;
            min_distance_cluster = 0;
            min_distance = std::numeric_limits<double>::max();
            for (int j = 0; j < km.clusters_number; ++j)
            {
                for (int k = 0; k < km.coordinates_number; k++)
                {
                    distances[j][i] += pow((km.dataset[i][k] - km.centroids[j][k]), 2);
                }

                distances[j][i] = sqrt(distances[j][i]);

                if (distances[j][i] < min_distance)
                {
                    min_distance_cluster = j;
                    min_distance = distances[j][i];
                }
            }

            new_assignments[min_distance_cluster].push_back(i);
            //std::cout << "point " << i << " - cluster" << min_distance_cluster << std::endl;

            //if point is not in closetst cluster increment points_movement counter
            if(std::find(km.assignments[min_distance_cluster].begin(), km.assignments[min_distance_cluster].end(), i) == km.assignments[min_distance_cluster].end())
            {
                points_movements++;
            }
        }

        //check for empty clusters
        if (new_assignments.size() != km.clusters_number)
        {
            //find empty clusters indexes
            for (int j = 0; j < km.clusters_number; ++j)
            {
                if (new_assignments[j].empty())
                {
                    empty_clusters_indexes.emplace_back(j);
                }
            }

            for(unsigned int e = 0; e < empty_clusters_indexes.size(); ++e)
            {
                //get a point to fill the empty cluster and donor's cluster index
                solved_empty_cluster = km.ecp.HandleEmptyClusters(*this, e);

                //update iteration assignments
                new_assignments[solved_empty_cluster.second].push_back(solved_empty_cluster.first);
                std::vector<int>::iterator it = new_assignments[solved_empty_cluster.second].begin();
                std::advance(it, e);
                new_assignments[solved_empty_cluster.second].erase(it);

                //update points_movements counter
                if(std::find(km.assignments[solved_empty_cluster.second].begin(), km.assignments[solved_empty_cluster.second].end(), solved_empty_cluster.first) != km.assignments[solved_empty_cluster.second].end())
                {
                    points_movements++;
                }
                else if (std::find(km.assignments[e].begin(), km.assignments[e].end(), solved_empty_cluster.first) != km.assignments[e].end())
                {
                    points_movements--;
                }

                //update distances
                for (int k = 0; k < km.coordinates_number; k++)
                {
                    distances[e][solved_empty_cluster.first] += pow((km.dataset[solved_empty_cluster.first][k] - km.centroids[e][k]), 2);
                    distances[solved_empty_cluster.second][solved_empty_cluster.first] += pow((km.dataset[solved_empty_cluster.first][k] - km.centroids[solved_empty_cluster.second][k]), 2);
                }
                distances[e][solved_empty_cluster.first] = sqrt(distances[solved_empty_cluster.second][solved_empty_cluster.first]);
                distances[solved_empty_cluster.second][solved_empty_cluster.first] = sqrt(distances[solved_empty_cluster.second][solved_empty_cluster.first]);
            }

            empty_clusters_indexes.clear();
        }

        std::cout << "points_movements: " << points_movements << std::endl;

//re-calculate clusters means

//make new_centroids filled with zeros before new iteration begin
    typename std::vector <std::vector<PointsBaseType>> new_centroids;
    new_centroids.resize(km.centroids.size(), std::vector<PointsBaseType>(km.centroids[0].size()));
    for (int i = 0; i < km.centroids.size(); ++i)
    {
        std::fill(new_centroids[i].begin(), new_centroids[i].end(), 0.00);
    }

    centroid_movements.resize(km.clusters_number);
//calculate new centroid means
    for (int j = 0; j < km.clusters_number; ++j)
    {
        for (int k = 0; k < km.coordinates_number; ++k)
        {
            for (int i = 0; i < new_assignments[j].size(); ++i)
            {
                new_centroids[j][k] += km.dataset[new_assignments[j][i]][k];
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

//apply new centroids means to km.centroids
    km.centroids.swap(new_centroids);
    km.assignments.swap(new_assignments);
    distances.clear();
    centroid_movements.clear();

//check if exit criteria is reached
    if((points_movements > km.points_move_thrsh) || (centroid_moved))
    {
        //apply new point assignments to km.assignment map
        std::cout << "threshold" << std::endl;
        return;
    }
    iterations--;
}
}

template void EuclidianDistance::Iterate (Kmeans<float, PointStealer, EuclidianDistance, RandomPoints>& km);

