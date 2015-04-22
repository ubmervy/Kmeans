#ifndef POINTSTEALER_H
#define POINTSTEALER_H
#include "../include/EuclidianDistance.h"
#include "../include/Kmeans.h"

template <typename PointsBaseType, typename EmptyClusterPolicy, template<class, class> class IterationMethod, typename InitialCentroids>
class Kmeans;

template <typename PointsBaseType, typename EmptyClusterPolicy>
class EuclidianDistance;

class PointStealer
{
    public:
        PointStealer();
        virtual ~PointStealer();
        template<typename PointsBaseType, typename EmptyClusterPolicy, template<typename, typename> class IterationMethod, typename InitialCentroids>
        void HandleEmptyClusters(EuclidianDistance<PointsBaseType, EmptyClusterPolicy> &iter_method,
                                                                   Kmeans<PointsBaseType, EmptyClusterPolicy, IterationMethod, InitialCentroids>& km);
    protected:
    private:
};

#endif // POINTSTEALER_H
