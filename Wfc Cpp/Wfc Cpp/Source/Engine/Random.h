#pragma once

#include <random>

namespace Satellite
{
	class Random
	{
		private:
			std::mt19937 mt;

		public:
			Random(unsigned int seed);

			/// Generate a random integer between [low, high].
			int GenerateRandomInteger(int low, int high);

			/// Generate a random float between [low, high].
			float GenerateRandomFloat(float low, float high);
	};
}