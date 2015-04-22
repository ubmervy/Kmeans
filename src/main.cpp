#include "../include/Kmeans.h"
#include "../include/EuclidianDistance.h"
#include "../include/PointStealer.h"
#include "../include/RandomPoints.h"
#include "../include/DataManipulation.h"
#include <iostream>
#include <vector>

const float rangeMin = -sqrt(std::numeric_limits<float>::max())/2;
const float rangeMax = sqrt(std::numeric_limits<float>::max())/2;

int main()
{
    //int points_number = 10;
    //int dimention = 2;
    std::vector<std::vector<float>> dataset;
    dataset = {
    {15.00, 26.00},
    {14.00, 25.00},
    {14.00, 24.00},
    {15.00, 24.00},
    {15.00, 25.00},
    {14.00, 23.00},
    {33.00, 2.00},
    {34.00, 5.00},
    {38.00, 24.00},
    {15.00, 1.00},
    {35.00, 3.00},
    {34.00, 2.00},
    };
    //dataset.resize(points_number, std::vector<float>(dimention));
    DataManipulation dm;
/*
    std::cout << "Generate dataset" << std::endl;
    for (int i = 0; i < points_number; ++i)
    {
        for (int j = 0; j < dimention; ++j)
        {
            dataset[i][j] = dm.get_random_number<float>(rangeMin, rangeMax);
            std::cout << "[" << i << "][" << j << "] = " << dataset[i][j] << '\t';
        }
        std::cout << std::endl;
    }*/

    Kmeans<float, PointStealer, EuclidianDistance, RandomPoints> km (3, 4, dataset);
    km.Cluster();
    return 0;
}
