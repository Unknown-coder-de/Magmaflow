#pragma once

typedef unsigned long long unt64;
typedef unsigned long unt32;
typedef unsigned unt16;
typedef unsigned short unt8;

typedef signed long long int64;
typedef signed long int32;
typedef signed int16;
typedef signed short int8;

#define for_fn(f, n, i) for (unt64 i = f; i < n; i++)
#define for_n(n, i) for_fn(0, n, i)
#define rfor_fn(f, n, i) for (unt64 i = n - 1; i >= f; i++)
#define rfor_n(n, i) rfor_fn(0, n, i)

#define arrlen(arr) (sizeof(arr) / sizeof((arr)[0]))
#define nalloc(tp, n) new tp[n]

struct
{
  template <typename tp>
  inline consteval tp product(const tp &a, const tp &b) const noexcept { return a * b; }
  template <typename tp, typename... args>
  inline consteval tp product(const tp &a, const args &..._args) const noexcept { return a * this->product(_args...); }

  template <typename tp>
  inline consteval tp E(const tp &a, const tp &b) const noexcept { return a + b; }
  template <typename tp, typename... args>
  inline consteval tp E(const tp &a, const args &..._args) const noexcept { return a + this->E(_args...); }

  template <typename tp>
  inline unt64 ptr_null_end(const tp *arr, const tp null = tp(0)) const noexcept
  {
    unt64 i = 0;
    while (*(arr + i) != null)
      i++;
    return i;
  }
  template <typename tp>
  inline unt8 ptr_null_short_end(const tp *arr, const tp null = tp(0)) const noexcept
  {
    unt64 i = 0;
    while (*(arr + i) != null)
      i++;
    return i;
  }
} _args;
