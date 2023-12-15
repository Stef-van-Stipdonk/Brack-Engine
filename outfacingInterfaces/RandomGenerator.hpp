//
// Created by Olaf van den Berg on 14/12/2023.
//

#ifndef BRACKOCALYPSE_RANDOMGENERATOR_HPP
#define BRACKOCALYPSE_RANDOMGENERATOR_HPP

#include <random>

class RandomGenerator {
public:
    static int randomInt(int min, int max) {
        std::random_device rd;
        std::mt19937 generator(rd());

        std::uniform_int_distribution<int> distribution(min, max);
        int randomInt = distribution(generator);
        return randomInt;
    }

    static float randomFloat(float min, float max) {
        std::random_device rd;
        std::mt19937 generator(rd());

        std::uniform_real_distribution<float> distribution(min, max);
        float randomFloat = distribution(generator);
        return randomFloat;
    }
};


#endif //BRACKOCALYPSE_RANDOMGENERATOR_HPP
