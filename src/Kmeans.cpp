#include "../include/Kmeans.h"
#include "../include/EuclidianDistance.h"
#include "../include/PointStealer.h"
#include "../include/RandomPoints.h"
#include <iostream>

template <typename PointsBaseType, typename EmptyClusterPolicy>
class EuclidianDistance;

//ctor
template <typename PointsBaseType, typename EmptyClusterPolicy, template<typename, typename> class IterationMethod, typename InitialCentroids>
Kmeans<PointsBaseType, EmptyClusterPolicy, IterationMethod, InitialCentroids>::Kmeans(  int clusters_number,
                                                                                        int max_iterations,
                                                                                        std::vector<std::vector<PointsBaseType>>& dataset,
                                                                                        int points_move_thrsh,
                                                                                        PointsBaseType centroid_movement_thrsh):
    clusters_number(clusters_number),
    max_iterations(max_iterations),
    dataset(dataset),
    points_move_thrsh(points_move_thrsh),
    centroid_movement_thrsh(centroid_movement_thrsh),
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
template <typename PointsBaseType, typename EmptyClusterPolicy, template<typename, typename> class IterationMethod, typename InitialCentroids>
Kmeans<PointsBaseType, EmptyClusterPolicy, IterationMethod, InitialCentroids>::~Kmeans()
{

}

//Cluster
template <typename PointsBaseType, typename EmptyClusterPolicy, template<typename, typename> class IterationMethod, typename InitialCentroids>
void Kmeans<PointsBaseType, EmptyClusterPolicy, IterationMethod, InitialCentroids>::Cluster()
{
        iteration_method.Iterate(*this);
}

template class Kmeans<float, PointStealer, EuclidianDistance, RandomPoints>;




