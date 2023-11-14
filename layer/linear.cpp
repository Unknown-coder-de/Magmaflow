#pragma once

#include "../magma.cpp"
#include "../random.cpp"

namespace layer
{
  template <const unt64 input_n, const unt64 output_n>
  struct linear
  {
    tensor<input_n, output_n> weight = random.randn<input_n, output_n>();
    float bias = 0, lnr = 0.01;

    template <const unt64 n>
    inline tensor<n, output_n> forward(const tensor<n, input_n> &inputs)
        const noexcept { return magma.matmul(inputs, this->weight) += bias; }
    template <const unt64 n>
    tensor<n, input_n> backward(
        const tensor<n, input_n> &inputs, const tensor<n, output_n> &output_d) noexcept
    {
      this->weight -= magma.matmul(magma.T(inputs), output_d) * lnr,
          this->bias -= output_d.E() * lnr;
      return magma.matmul(this->weight, magma.T(output_d));
    }
    template <const unt64 n>
    tensor<n, output_n> gradients(const tensor<n, input_n> &inputs, const tensor<n, output_n> &targets)
        const noexcept { return (this->forward(inputs) -= targets) /= (float(2) / float(output_n)); }
  };
}