#include <math.hpp>

double getPi(){
	return 2 * std::acos(0.0); // or alternatively use 2 * std::asin(1.0f) or directly return 3.141593;
}

double getTau(){
	return 4 * std::acos(0.0); // or alternatively use 4 * std::asin(1.0f) or directly return 2 * 3.141593;
}

inline int rng_int(int min, int max){
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

inline float rng_real(float min, float max){
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}