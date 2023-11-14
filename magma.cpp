#pragma once
#include "tensor.cpp"

struct
{
  template <const unt64 n1, const unt64 n2>
  inline void T(const tensor<n1, n2> &mat, tensor<n2, n1> &result)
      const noexcept { for_n(n1, i) for_n(n2, j) result[j, i] = mat.at(i, j); }
  template <const unt64 n1, const unt64 n2>
  inline tensor<n2, n1> T(const tensor<n1, n2> &mat) const noexcept
  {
    tensor<n2, n1> result;
    this->T(mat, result);
    return result;
  }
  template <const unt64 n1, const unt64 n2, const unt64 n3>

  inline void matmul(const tensor<n1, n2> &mat1, const tensor<n2, n3> &mat2, tensor<n1, n3> &result) const noexcept
  {
    for_n(n1, i) for_n(n3, j)
    {
      result[i, j] = 0;
      for_n(n2, k) result[i, j] += mat1.at(i, k) * mat2.at(k, j);
    }
  }
  template <const unt64 n1, const unt64 n2, const unt64 n3>
  tensor<n1, n3> matmul(const tensor<n1, n2> &mat1, const tensor<n2, n3> &mat2) const noexcept
  {
    tensor<n1, n3> result;
    this->matmul(mat1, mat2, result);
    return result;
  }
} magma;
