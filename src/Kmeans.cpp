#include "../include/Kmeans.h"
#include "../include/EuclidianDistance.h"
#include "../include/PointStealer.h"
#include "../include/RandomPoints.h"
#include <iostream>

//ctor
template <typename PointsBaseType, typename IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>::Kmeans(int clusters_number,
                                                                                       std::vector<std::vector<PointsBaseType>>& dataset):
                                                        clusters_number(clusters_number),
                                                        dataset(dataset),
                                                        points_number(dataset.size()),
                                                        coordinates_number(dataset[0].size())

{
    if (clusters_number >= dataset.size())
    {
        std::cerr << "The number of clusters must be less than the number of samples in dataset." << std::endl;
        exit(1);
    }

    InitialCentroids ic = InitialCentroids();
    ic.Initialize(*this);
}

//dtor
template <typename PointsBaseType, typename IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>::~Kmeans()
{

}

//Cluster
template <typename PointsBaseType, typename IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
void Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>::Cluster()
{
    iteration_method.Iterate(*this);
}

template class Kmeans<float, EuclidianDistance, PointStealer, RandomPoints>;




