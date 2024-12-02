#ifndef SMOOTHING_KERNELS_HPP
#define SMOOTHING_KERNELS_HPP

#include <cmath>

inline float Poly6Kernel(float r, float h) {
	if (r > h)
		return 0.0f;

	float norm = 315.0f / (64.0f * M_PI * std::pow(h, 9));
	return std::pow(h * h - r * r, 3) * norm;
}

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

inline float ViscosityKernel(float r, float h) {
	if (r > h)
		return 0.0f;

	float norm = 15.0f / (2.0f * M_PI * std::pow(h, 3));
	float term1 = - std::pow(r, 3) / (2.0f * std::pow(h, 3));
	float term2 = std::pow(r, 2) / std::pow(h, 2);
	float term3 = h / (2.0f * r);

	return norm * (term1 + term2 + term3 - 1.0f);
}

inline float ViscosityKernelLaplacian(float r, float h) {
	if (r > h)
		return 0.0f;

	float norm = 45.0f / (M_PI * std::pow(h, 6));
	return (h - r) * norm;
}

#endif // SMOOTHING_KERNELS_HPP