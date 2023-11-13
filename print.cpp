#pragma once

#include <stdio.h>
#include "tensor.cpp"

inline void print(const unt64 &a) noexcept { printf("%lld", a); }
inline void print(const unt32 &a) noexcept { printf("%ld", a); }
inline void print(const unt16 a) noexcept { printf("%d", a); }
inline void print(const unt8 a) noexcept { printf("%d", a); }

inline void print(const int64 &a) noexcept { printf("%lld", a); }
inline void print(const int32 &a) noexcept { printf("%ld", a); }
inline void print(const int16 a) noexcept { printf("%d", a); }
inline void print(const int8 a) noexcept { printf("%d", a); }

inline void print(const float &a) noexcept { printf("%.1f", a); }
inline void print(const double &a) noexcept { printf("%.2f", a); }
inline void print(const long double &a) noexcept { printf("%.3f", a); }

inline void print(const char a) noexcept { printf("%c", a); }
inline void print(const char *str) noexcept { printf(str); }

#include <string.h>

char *strmul(const char *str, const unt64 n) noexcept
{
  char *new_str = nalloc(char, strlen(str) * n);
  strcpy(new_str, str);
  for_n(n - 1, i) strcat(new_str, str);
  return new_str;
}

template <typename tp>
void print_ptr(tp *arr, const unt64 *shape, const unt64 &size,
               const unt8 shift, const unt8 ndim) noexcept
{
  printf("{");
  if (ndim == 1)
  {
    print(*arr);
    if (*shape > 5)
    {
      for_fn(1, 5, i) printf(", "), print(arr[i]);
      printf(", ... %lld+", *shape - 5);
    }
    else
      for_fn(1, *shape, i) printf(", "), print(arr[i]);
  }
  else
  {
    const unt64 new_size = size / *shape, new_ndim = ndim - 1, new_shift = shift + 1;
    print_ptr(&*arr, &shape[1], new_size, new_shift, new_ndim);
    if (*shape > 5)
    {
      for_fn(1, 5, i) printf(",\n%s", strmul(" ", shift)),
          print_ptr(&arr[i * size], &shape[1], new_size, new_shift, new_ndim);
      printf(", ... %lld+", *shape - 5);
    }
    else
      for_fn(1, *shape, i) printf(",\n%s", strmul(" ", shift)),
          print_ptr(&arr[i * size], &shape[1], new_size, new_shift, new_ndim);
  }
  printf("}");
}

template <const unt64... n>
inline void print(const tensor<n...> &a) noexcept { print_ptr(
    a.arr.data, nalloc(unt64, ){n...}, a.arr.len / *nalloc(unt64, ){n...},
    1, _args.ptr_null_short_end(nalloc(unt64, ){n..., 0})); }

inline void prints() noexcept {}
template <typename tp, typename... args>
inline void prints(const tp &a, const args &..._args) noexcept { print(a), prints(_args...); }