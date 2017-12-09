#include <cstdlib>
#include <algorithm>
#include "utils"
#include "QModel.hpp"

void QModel::set_data(unsigned int status_size, unsigned int nof_actions) {
  uint16_t hlayer_neurons = (status_size + nof_actions);
  allocate(status_size, nof_actions, 1, hlayer_neurons, hlayer_neurons);
}

int QModel::max_arg(float* inputs) {
  feed_forward(inputs);
  int max_index = 0;

  for(int i=1; i < _outputs; ++i)
    if(output[i] > output[max_index])
      max_index = i;

  printf("%.6f  %.6f  %.6f  %.6f\n", output[0], output[1], output[2], output[3]);
  last_action = max_index;
  return max_index;
}

void QModel::give_reward(float* inputs, float reward) {
  ffor(i, _outputs)
    error[i] = (i==last_action)?(-reward):0;
  backpropagate(inputs, error);
}
