# Kmeans
Template class that implement Kmeans algorithm parametrised with:
PointsBaseType - type of input points;
InitialCentroids - initial partition policy type (RandomPoints class is supplied that performs centroids initialization with random points);
Iteration method - type which implements Cluster method that iterates the main body of algorithm using given distance metric (EuclidianDistance class is supplied to perform the clustering using Euclidian distance to evaluate points-clusters distance on each iteration)
EmptyClusterPolicy - type which implements HandleEmptyCluster method to wisely fulfill empty clusters on each iteration (if any). PointStealer type is provided that choses the furthest point in the cluster with max variance.
