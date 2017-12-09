#ifndef __QLEARN__
#define __QLEARN__
#include <cstdint>
#include "nnet.hpp" // Neural Network class

// Q learning model
class QModel : private NeuralNetwork{
private:
  unsigned int last_action = 0;
public:
  void set_data(unsigned int status_size, unsigned int nof_actions);
  int max_arg(float* inputs);
  void give_reward(float* inputs, float reward);
};

#endif // __QLEARN__
