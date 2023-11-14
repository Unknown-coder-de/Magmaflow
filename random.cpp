#pragma once

#include <stdlib.h>
#include "tensor.cpp"

// To generate random integers
#define randint(min, max) (min + rand() % (max - min))
// To generate random floating points
#define randf(min, max) (min + (max - min) * static_cast<float>(rand()) / RAND_MAX)

struct
{
  template <typename tp>
  tp choice(const tp *arr, const unt64 n)
      const noexcept { return *(arr + randint(0, n)); }
  template <const unt64... n>
  tensor<n...> randn(const float min = -1, const float max = 1) const noexcept
  {
    tensor<n...> result;
    for_n(result.arr.len, i) result.arr.data[i] = randf(min, max);
    return result;
  }
} random;