#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <chrono>
#include <random>

class RandomNumberGenerator
{
public:
    RandomNumberGenerator();

public:
    static int randInt(const int from, const int toNotIncluding);
    static int randDir();
    static float randFloat(const float from, const float toNotIncluding);
    static bool randBool(const double trueProb = 0.5);

private:
    static std::mt19937 rng;
};

inline RandomNumberGenerator::RandomNumberGenerator()
{
    static bool initialized = false;
    if(!initialized) {
        uint32_t seed;
        std::random_device device;
        if(device.entropy() == 0) {
            auto duration = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::time_point::min();
            seed = duration.count();
        } else {
            std::uniform_int_distribution<uint32_t> dist(std::numeric_limits<uint32_t>::min(),
                                                         std::numeric_limits<uint32_t>::max());
            seed = dist(device);
        }
        rng.seed(seed);
        initialized = true;
    }
}

inline int RandomNumberGenerator::randInt(const int from, const int toNotIncluding)
{
    std::uniform_int_distribution<int> dist(from, toNotIncluding - 1);
    return dist(rng);
}

inline int RandomNumberGenerator::randDir()
{
    return randInt(0, 6);
}

inline float RandomNumberGenerator::randFloat(const float from, const float toNotIncluding)
{
    std::uniform_real_distribution<float> dist(from, toNotIncluding);
    return dist(rng);
}

inline bool RandomNumberGenerator::randBool(const double trueProb)
{
    return (randFloat(0, 1) < trueProb);
}

#endif // RANDOMNUMBERGENERATOR_H
