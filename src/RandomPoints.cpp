#include "../include/RandomPoints.h"
#include "../include/Kmeans.h"
#include "../include/DataManipulation.h"
#include "../include/EuclidianDistance.h"
#include "../include/PointStealer.h"
#include <unordered_set>

DataManipulation dm;

template <typename PointsBaseType, template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
class Kmeans;

RandomPoints::RandomPoints()
{
    //ctor
}

RandomPoints::~RandomPoints()
{
    //dtor
}

template <typename PointsBaseType, template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
void RandomPoints::Initialize(Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>& km)
{
    km.centroids.resize(km.clusters_number, std::vector <PointsBaseType>(km.coordinates_number));
    std::unordered_set<int> random_points; //a set of unique points (dataset indexes)
    std::unordered_set<int>::iterator it;

    //centroid initialization
    std::cout << "Initialization.." << std::endl;

    //get random points indexes
    int random_index;

    /*while(random_points.size()!=km.clusters_number)
    {
        random_index = dm.get_random_number<int>(0, km.dataset.size()-1);
        random_points.insert(random_index);
    }*/

    for (int i = km.clusters_number-1; i >= 0; --i)
        random_points.insert(i);

    //initialize centroids by random dataset points
    for (it = random_points.begin(); it != random_points.end(); ++it)
        for (int k = 0; k < 2; ++k)
        {
            {
                km.centroids[*it][k] = km.dataset[*it][k];
            }
        }

    for (int p = 0; p < km.clusters_number; ++p)
    {
        for (int k = 0; k < 2; ++k)
        {
            std::cout << "Centroids [" << p << "] = " << km.centroids[p][k] << '\t';
        }
        std::cout<< std::endl;
    }
}

template void RandomPoints::Initialize (Kmeans<float, EuclidianDistance, PointStealer, RandomPoints>& km);
