#ifndef KMEANS_H
#define KMEANS_H
#include <map>
#include <vector>
#include <iostream>
#include <memory>
#include "../include/PointStealer.h"
#include "../include/EuclidianDistance.h"
#include "../include/RandomPoints.h"


template <typename PointsBaseType, typename IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
class Kmeans
{
public:
    Kmeans(int, std::vector<std::vector<PointsBaseType>>& dataset);
    ~Kmeans();
    void Cluster();

private:
    int clusters_number; // number of clusters;
    typename std::vector<std::vector<PointsBaseType>>& dataset; // points dataset
    typename std::vector<std::vector<PointsBaseType>> centroids; // clusters' centroids
    typename std::map<int, std::vector<std::vector<PointsBaseType*>>> assignments; // first - cluster, second - vector of pointers to dataset points assigned to that cluster;
    PointStealer empty_cluster_handler;
    IterationMethod iteration_method;

    template <typename U, typename W, typename V, typename Y>
    friend void IterationMethod::Iterate(Kmeans<U, W, V, Y>& km);

    template <typename U, typename W, typename V, typename Y>
    friend void InitialCentroids::Initialize(Kmeans<U, W, V, Y>& km);

    int points_number;
    int coordinates_number;
};


#endif // KMEANS_H
