#ifndef __tensor__
#define __tensor__

#include "torch.cpp"

#define talloc(tp, ...) new tp[_args.product(__VA_ARGS__)]

struct
{
  template <const unt64 size, const unt64 shape_i>
  inline unt64 _index_(const unt64 &indic) const noexcept
  {
    return indic;
  }
  template <const unt64 size, const unt64 shape_f, const unt64... shape_, typename... args>
  inline unt64 _index_(const unt64 &indic, const args &...indices) const noexcept
  {
    constexpr unt64 size_ = size / shape_f;
    return size_ * indic + _index_<size_, shape_...>(indices...);
  }
  template <const unt64... shape_, typename... args>
  inline unt64 index(const args &...indices) const noexcept
  {
    return _index_<_args.product(shape_...), shape_...>(indices...);
  }

  template <typename... args>
  inline consteval unt64 shape(const args &..._indices) noexcept { return _args.product(_indices...); }
} compute;

template <typename tp, const unt64 n>
struct array
{
  tp *data = nalloc(tp, n);
  const unt64 len = n;
};

template <const unt64... n>
struct tensor
{
  array<float, compute.shape(n...)> arr;

  void assign(const float *data, const unt64 len) noexcept { for_n(len, i) arr.data[i] = data[i]; }

  template <typename... args>
  const float &at(const args &...indices)
      const noexcept { return arr.data[compute.index<n...>(indices...)]; }

  float E() const noexcept
  {
    float sum = 0;
    for_n(arr.len, i) sum += arr.data[i];
    return sum;
  }
  inline float mean() const noexcept { return this->E() / arr.len; }
  float max() const noexcept
  {
    float _max_ = arr.data[0];
    for_fn(1, arr.len, i) if (_max_ < arr.data[i]) _max_ = arr.data[i];
    return _max_;
  }
  float min() const noexcept
  {
    float _min_ = arr.data[0];
    for_fn(1, arr.len, i) if (_min_ > arr.data[i]) _min_ = arr.data[i];
    return _min_;
  }

  template <typename... args>
  float &operator[](const args &...indices) noexcept { return arr.data[compute.index<n...>(indices...)]; }

  tensor<n...> &operator=(const tensor<n...> &other) noexcept
  {
    for_n(arr.len, i) arr.data[i] = other.arr.data[i];
    return *this;
  }

  tensor<n...> &operator+=(const tensor<n...> &other) noexcept
  {
    for_n(arr.len, i) arr.data[i] += other.arr.data[i];
    return *this;
  }
  tensor<n...> &operator-=(const tensor<n...> &other) noexcept
  {
    for_n(arr.len, i) arr.data[i] -= other.arr.data[i];
    return *this;
  }
  tensor<n...> &operator*=(const tensor<n...> &other) noexcept
  {
    for_n(arr.len, i) arr.data[i] *= other.arr.data[i];
    return *this;
  }
  tensor<n...> &operator/=(const tensor<n...> &other) noexcept
  {
    for_n(arr.len, i) arr.data[i] /= other.arr.data[i];
    return *this;
  }

  tensor<n...> operator+(const tensor<n...> &other)
      const noexcept { return tensor<n...>(*this) += other; }
  tensor<n...> operator-(const tensor<n...> &other)
      const noexcept { return tensor<n...>(*this) -= other; }
  tensor<n...> operator*(const tensor<n...> &other)
      const noexcept { return tensor<n...>(*this) *= other; }
  tensor<n...> operator/(const tensor<n...> &other)
      const noexcept { return tensor<n...>(*this) /= other; }

  tensor<n...> &operator+=(const float &value) noexcept
  {
    for_n(arr.len, i) arr.data[i] += value;
    return *this;
  }
  tensor<n...> &operator-=(const float &value) noexcept
  {
    for_n(arr.len, i) arr.data[i] -= value;
    return *this;
  }
  tensor<n...> &operator*=(const float &value) noexcept
  {
    for_n(arr.len, i) arr.data[i] *= value;
    return *this;
  }
  tensor<n...> &operator/=(const float &value) noexcept
  {
    for_n(arr.len, i) arr.data[i] /= value;
    return *this;
  }

  tensor<n...> operator+(const float &value)
      const noexcept { return tensor<n...>(*this) += value; }
  tensor<n...> operator-(const float &value)
      const noexcept { return tensor<n...>(*this) -= value; }
  tensor<n...> operator*(const float &value)
      const noexcept { return tensor<n...>(*this) *= value; }
  tensor<n...> operator/(const float &value)
      const noexcept { return tensor<n...>(*this) /= value; }
};

#endif // __tensor__