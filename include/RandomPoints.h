#ifndef RANDOMPOINTS_H
#define RANDOMPOINTS_H
#include "../include/Kmeans.h"
#include "../include/EuclidianDistance.h"
#include "../include/PointStealer.h"

template <typename PointsBaseType, template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
class Kmeans;

class RandomPoints
{
    public:
        RandomPoints();
        virtual ~RandomPoints();
        template <typename PointsBaseType, template<typename> class IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
        void Initialize(Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>& km);
};

#endif // RANDOMPOINTS_H
