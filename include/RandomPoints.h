#ifndef RANDOMPOINTS_H
#define RANDOMPOINTS_H
#include "../include/Kmeans.h"
#include "../include/EuclidianDistance.h"
#include "../include/PointStealer.h"

template <typename PointsBaseType, typename EmptyClusterPolicy, template<class, class> class IterationMethod, typename InitialCentroids>
class Kmeans;

class RandomPoints
{
    public:
        RandomPoints();
        virtual ~RandomPoints();
        template <typename PointsBaseType, typename EmptyClusterPolicy, template<class, class> class IterationMethod, typename InitialCentroids>
        void Initialize(Kmeans<PointsBaseType, EmptyClusterPolicy, IterationMethod, InitialCentroids>& km);
};

#endif // RANDOMPOINTS_H
