#ifndef FPSCounter_H
#define FPSCounter_H

#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>

class FPSCounter {
private:
  double fps = 0.0f;
  int frameCount = 0;
  double lastFPSTime;
	double lastFrameTime;
	double targetFrameTime;

public:
  FPSCounter(double targetFPS);

  void Update();

  double GetFPS() const { return fps; }
};

#endif // FPSCounter_H