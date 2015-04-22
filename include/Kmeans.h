#ifndef KMEANS_H
#define KMEANS_H
#include <map>
#include <vector>
#include <iostream>
#include <memory>
#include "../include/PointStealer.h"
#include "../include/EuclidianDistance.h"
#include "../include/RandomPoints.h"


template <typename PointsBaseType, typename EmptyClusterPolicy, template<class, class> class IterationMethod, typename InitialCentroids>
class Kmeans
{
public:
    Kmeans(int clusters_number, int max_iterations, std::vector<std::vector<PointsBaseType>>& dataset, int points_move_thrsh = 2, PointsBaseType centroid_movement_thrsh = 10);
    ~Kmeans();
    void Cluster();

private:
    int clusters_number; // number of clusters;
    int max_iterations; // max number of iterations;
    typename std::vector<std::vector<PointsBaseType>>& dataset; // points dataset
    typename std::vector<std::vector<PointsBaseType>> centroids; // clusters' centroids
    typename std::map<int, std::vector<std::vector<PointsBaseType>*>> assignments; // first - cluster, second - vector of pointers to dataset points assigned to that cluster;
    IterationMethod<PointsBaseType, EmptyClusterPolicy> iteration_method;
    EmptyClusterPolicy ecp;
    int points_move_thrsh; //points movement threshold
    PointsBaseType centroid_movement_thrsh; //centroid movement threshold

    template<template<typename, typename> class W, typename V>
    friend void IterationMethod<PointsBaseType, EmptyClusterPolicy>::Iterate(Kmeans<PointsBaseType, EmptyClusterPolicy, W, V>& km);

    template <typename U, typename W, template<typename, typename> class V, typename Y>
    friend void InitialCentroids::Initialize(Kmeans<U, W, V, Y>& km);

    template<typename U, typename V, template<typename, typename> class W, typename Y>
    friend void EmptyClusterPolicy::HandleEmptyClusters(IterationMethod<U, V> &iter_method,
                                                        Kmeans<U, V, W, Y>& km);

    int points_number;
    int coordinates_number;
};


#endif // KMEANS_H
