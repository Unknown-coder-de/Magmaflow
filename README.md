# Magmaflow - A development ready OUTLINE project
# Overview
Hello everyone! I'm Yash Raj Singh Rawat. I had coded this tensor's library. This repository contains C++ code for a simple tensor library, including a tensor class (tensor.cpp), basic operations on tensors, and a printing utility (print.cpp). The code is structured into three main files: torch.cpp, tensor.cpp, and print.cpp.

# File Descriptions
# torch.cpp
This file defines basic types (unt64, unt32, unt16, unt8, int64, int32, int16, int8) and some convenient macros (for_fn, for_n, rfor_fn, rfor_n, arrlen, nalloc). It also includes a template struct with constexpr functions for product and element-wise addition.

# tensor.cpp
This file defines a template struct for a tensor, leveraging the types and macros from torch.cpp. It includes functions for element-wise operations such as addition, subtraction, multiplication, and division. The tensor class supports operations with both other tensors and scalar values.

# print.cpp
This file provides a utility for printing tensors. It includes functions for printing basic types (unt64, unt32, unt16, unt8, int64, int32, int16, int8, float, double, long double, char, and strings) and a recursive printing function for tensors.

# How to Use
Include the necessary header files in your project.
```
#include "torch.cpp"
#include "tensor.cpp"
#include "print.cpp"
```

Create tensors using the tensor struct.
```
tensor<3, 4, 2> a;
```

Perform operations on tensors.
```
a += 1.5;
```

Print tensors using the provided print functions.
```
print(a);
```

Example:
```
#include "torch.cpp"
#include "tensor.cpp"
#include "print.cpp"

int main() {
    tensor<3, 4, 2> a, b;

    // Perform operations
    a += 1.5;
    b += 2.0;

    // Print tensors
    print("Tensor a:", a);
    print("Tensor b:", b);

    return 0;
}
```
