#include "../include/Kmeans.h"
#include "../include/EuclidianDistance.h"
#include "../include/PointStealer.h"
#include "../include/RandomPoints.h"
#include <iostream>

template <typename PointsBaseType>
class EuclidianDistance;

//ctor
template <typename PointsBaseType, template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>::Kmeans(int clusters_number,
        int max_iterations,
        std::vector<std::vector<PointsBaseType>>& dataset):
    clusters_number(clusters_number),
    max_iterations(max_iterations),
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
template <typename PointsBaseType, template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>::~Kmeans()
{

}

//Cluster
template <typename PointsBaseType, template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
void Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>::Cluster()
{
    int iterations = max_iterations;
    while (iterations)
    {
        iteration_method.Iterate(*this);
        --iterations;
    };
}

template class Kmeans<float, EuclidianDistance, PointStealer, RandomPoints>;




