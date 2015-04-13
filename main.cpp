#include <iostream>
#include "Kmeans.h"

using namespace std;

int main()
{
    Kmeans<float, float, float> km;
    km.Cluster();
    return 0;
}
