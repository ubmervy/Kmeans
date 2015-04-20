#ifndef KMEANS_H
#define KMEANS_H
#include <map>
#include <vector>
#include <iostream>
#include <memory>
#include "../include/PointStealer.h"
#include "../include/EuclidianDistance.h"
#include "../include/RandomPoints.h"

template <typename PointsBaseType, template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
class Kmeans
{
public:
    Kmeans(int, int, std::vector<std::vector<PointsBaseType>>& dataset);
    ~Kmeans();
    void Cluster();

private:
    int clusters_number; // number of clusters;
    int max_iterations; // max number of iterations;
    typename std::vector<std::vector<PointsBaseType>>& dataset; // points dataset
    typename std::vector<std::vector<PointsBaseType>> centroids; // clusters' centroids
    typename std::map<int, std::vector<std::vector<PointsBaseType>*>> assignments; // first - cluster, second - vector of pointers to dataset points assigned to that cluster;
    PointStealer empty_cluster_handler;
    IterationMethod<PointsBaseType> iteration_method;

    //template <typename U>
    template<template<typename> class W, typename V, typename Y>
    friend void IterationMethod<PointsBaseType>::Iterate(Kmeans<PointsBaseType, W, V, Y>& km);

    template <typename U, template<typename> class W, typename V, typename Y>
    friend void InitialCentroids::Initialize(Kmeans<U, W, V, Y>& km);

    int points_number;
    int coordinates_number;
};


#endif // KMEANS_H
