#ifndef KMEANS_H
#define KMEANS_H
#include <map>
#include <vector>
#include <iostream>
#include <memory>
#include "../include/PointStealer.h"
#include "../include/EuclidianDistance.h"
#include "../include/RandomPoints.h"


template <typename PointsBaseType, typename EmptyClusterPolicy, typename IterationMethod, typename InitialCentroids>
class Kmeans
{
public:
    Kmeans(int clusters_number, int max_iterations, std::vector<std::vector<PointsBaseType>>& dataset, int points_move_thrsh = 10, PointsBaseType centroid_movement_thrsh = 15);
    ~Kmeans();
    void Cluster();

private:
    int clusters_number; // number of clusters;
    int max_iterations; // max number of iterations;
    typename std::vector<std::vector<PointsBaseType>>& dataset; // points dataset
    typename std::vector<std::vector<PointsBaseType>> centroids; // clusters' centroids
    std::map<int, std::vector<int>> assignments; // first - cluster, second - indexes of dataset points assigned to that cluster;
    IterationMethod iteration_method;
    EmptyClusterPolicy ecp;
    int points_move_thrsh; //points movement threshold
    PointsBaseType centroid_movement_thrsh; //centroid movement threshold

    template<typename U, typename W, typename V, typename Y>
    friend void IterationMethod::Iterate(Kmeans<U, W, V, Y>& km);

    template <typename U, typename W, typename V, typename Y>
    friend void InitialCentroids::Initialize(Kmeans<U, W, V, Y>& km);

    int points_number;
    int coordinates_number;
};


#endif // KMEANS_H
