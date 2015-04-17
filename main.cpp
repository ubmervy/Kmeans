#include "../include/Kmeans.h"
#include "../include/EuclidianDistance.h"
#include "../include/PointStealer.h"
#include "../include/RandomPoints.h"
#include <iostream>
#include <vector>


int main()
{
    std::vector<std::vector<float>> dataset;
    dataset.resize(10, std::vector<float>(2));
    Kmeans<float, EuclidianDistance, PointStealer, RandomPoints> km (4, dataset);
    km.Cluster();
    return 0;
}
