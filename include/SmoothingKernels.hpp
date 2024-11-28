#ifndef SMOOTHING_KERNELS_HPP
#define SMOOTHING_KERNELS_HPP

#include <cmath>

inline float SpikyKernel(float r, float h) {
	if (r > h)
		return 0.0f;

	float norm = 15.0f / (M_PI * std::pow(h, 6));
	return std::pow(h - r, 3) * norm;
}

inline float SpikyKernelDeriv(float r, float h) {
	if (r > h)
		return 0.0f;

	float norm = -45.0f / (M_PI * std::pow(h, 6));
	return std::pow(h - r, 2) * norm;
}

#endif // SMOOTHING_KERNELS_HPP