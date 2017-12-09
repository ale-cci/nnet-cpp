#include <cassert>
#include <algorithm>
#include "NetInput.hpp"
#include "utils"

NetInput::NetInput(int input_size, int nof_attributes) {
  assert(input_size > 0 && nof_attributes > 0);
  _size = input_size;
  _attrs = nof_attributes;

  // allocating inputs
  _net_in = new float[_size * _attrs];
}

int NetInput::get_size() const {
  return _size;
}

int NetInput::get_attributes() const {
  return _attrs;
}

float* NetInput::parse(int* input) {
  allzero(); // reset previous input

  ffor(i, _size)
    if (input[i] != 0){
      assert(input[i] <= _attrs && input[i] > 0);
      _net_in[i*_attrs + input[i] -1] = 1;
    }
  return _net_in;
}

float* NetInput::allzero() {
  std::fill_n(_net_in, _size*_attrs, 0);
  return _net_in;
}

float* NetInput::random() {
  std::generate_n(_net_in, _size*_attrs, [](){return randTo(0, 1);});
  return _net_in;
}

float* NetInput::last_input() {
  return _net_in;
}

int NetInput::input_size() const {
  return _size * _attrs;
}
