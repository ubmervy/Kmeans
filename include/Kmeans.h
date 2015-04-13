#ifndef KMEANS_H
#define KMEANS_H
#include <vector>

template <typename PointsBaseType, typename MetricType, typename InitialAssignment>
class Kmeans
{
    public:
        Kmeans();
        ~Kmeans();
        void Cluster();

    private:
};

#include "/home/ubuntu14/Projects/Kmeans/src/Kmeans.cpp"
#endif // KMEANS_H
