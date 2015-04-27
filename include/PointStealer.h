#ifndef POINTSTEALER_H
#define POINTSTEALER_H
#include <utility>

class EuclidianDistance;

class PointStealer
{
    public:
        PointStealer();
        virtual ~PointStealer();
        std::pair<int, int>  HandleEmptyClusters(EuclidianDistance &iter_method, int empty_cluster);
    protected:
    private:
};

#endif // POINTSTEALER_H
