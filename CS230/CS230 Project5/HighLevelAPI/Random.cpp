#include "stdafx.h"
#include "Random.h"

float Random::RandomRange(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}
