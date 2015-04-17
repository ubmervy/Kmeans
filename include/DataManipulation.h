#ifndef DATAMANIPULATION_H
#define DATAMANIPULATION_H
#include "boost/random.hpp"
 #include <time.h>

class DataManipulation
{
    public:
        DataManipulation();
        virtual ~DataManipulation();

        template<class T> T get_random_number(T rangeMin, T rangeMax);

    protected:
    private:
};

//get random number
template<class T>
T DataManipulation::get_random_number(T rangeMin, T rangeMax)
{
    typedef boost::uniform_real<> NumberDistribution;
    typedef boost::mt19937 RandomNumberGenerator;
    typedef boost::variate_generator<RandomNumberGenerator&,
            NumberDistribution> Generator;

    RandomNumberGenerator generator;
    static unsigned int seed = 0;
    generator.seed((++seed) + time(NULL)); // seed with the current time
    NumberDistribution distribution(rangeMin, rangeMax);
    Generator numberGenerator(generator, distribution);
    return numberGenerator();
}

//#include "../src/DataManipulation.cpp"

#endif // DATAMANIPULATION_H
