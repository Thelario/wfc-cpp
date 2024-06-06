#include "Random.h"

namespace Satellite
{
	Random::Random(unsigned int seed) : mt(std::mt19937(seed))
	{ }

	int Random::GenerateRandomInteger(int low, int high)
	{
		std::uniform_int_distribution<int> dist(low, high);
		return dist(mt);
	}

	float Random::GenerateRandomFloat(float low, float high)
	{
		std::uniform_real_distribution<float> dist(low, high);
		return dist(mt);
	}
}