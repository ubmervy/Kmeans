#ifndef EUCLIDIANDISTANCE_H
#define EUCLIDIANDISTANCE_H
#include "../include/Kmeans.h"
#include "../include/RandomPoints.h"
#include "../include/PointStealer.h"
#include <vector>
#include <map>

template <typename PointsBaseType, typename EmptyClusterPolicy, template<typename, typename> class IterationMethod, typename InitialCentroids>
class Kmeans;

template <typename PointsBaseType, typename EmptyClusterPolicy>
class EuclidianDistance
{

    public:
        EuclidianDistance();
        virtual ~EuclidianDistance();

        std::vector <std::vector <double>> distances;
        std::map<int, std::vector <std::vector<PointsBaseType>*>> new_assignments;
        int points_movements;

        template <template<typename, typename> class IterationMethod, typename InitialCentroids>
        void Iterate(Kmeans<PointsBaseType, EmptyClusterPolicy, IterationMethod, InitialCentroids>& km);

        template<typename U, typename V, template<typename, typename> class IterationMethod, typename InitialCentroids>
        friend void EmptyClusterPolicy::HandleEmptyClusters(EuclidianDistance<U, V> &iter_method,
                                                            Kmeans<U, V, IterationMethod, InitialCentroids>& km);
};

//#include "../src/EuclidianDistance.cpp"

#endif // EUCLIDIANDISTANCE_H
