#ifndef EUCLIDIANDISTANCE_H
#define EUCLIDIANDISTANCE_H
#include "../include/Kmeans.h"
#include "../include/RandomPoints.h"
#include "../include/PointStealer.h"

template <typename PointsBaseType, typename IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
class Kmeans;

class EuclidianDistance
{

    public:
        EuclidianDistance();
        virtual ~EuclidianDistance();

        std::vector < std::vector <double> > distances;

        template <typename PointsBaseType, typename IterationMethod, typename EmptyClusterPolicy, typename InitialCentroids>
        void Iterate(Kmeans<PointsBaseType, IterationMethod, EmptyClusterPolicy, InitialCentroids>& km);

};

//#include "../src/EuclidianDistance.cpp"

#endif // EUCLIDIANDISTANCE_H
