#ifndef __NET_INPUT__
#define __NET_INPUT__
#include <iostream>
#include <cstdint>
#include "nnet.hpp"

/** parses the input to a vector**/
class NetInput {
private:
  int _size;
  int _attrs;
  float* _net_in;

public:
  NetInput(int input_size, int nof_attributes);

  int get_size() const;
  int get_attributes() const;
  int input_size() const;

  float* parse(int* inputs);
  float* allzero();
  float* random();
  float* last_input();
};

#endif
