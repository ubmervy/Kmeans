#ifndef EUCLIDIANDISTANCE_H
#define EUCLIDIANDISTANCE_H
#include "../include/Kmeans.h"
#include "../include/RandomPoints.h"
#include "../include/PointStealer.h"
#include <vector>
#include <map>

template <typename PointsBaseType, template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
class Kmeans;

template <typename PointsBaseType>
class EuclidianDistance
{

    public:
        EuclidianDistance();
        virtual ~EuclidianDistance();

        std::vector <std::vector <double>> distances;
        std::map<int, std::vector <std::vector<PointsBaseType>*>> new_assignments;
       /* template <U>
        structure new_assignments
        {
            typename std::map<int, std::vector <std::vector<U>*>> new_assignments;
        }*/

        template <template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
        void Iterate(Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>& km);

};

//#include "../src/EuclidianDistance.cpp"

#endif // EUCLIDIANDISTANCE_H
