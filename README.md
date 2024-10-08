# OxyFEM

```
 ██████╗ ██╗  ██╗██╗   ██╗     ███████╗███╗   ███╗
██╔═══██╗╚██╗██╔╝╚██╗ ██╔╝     ██╔════╝████╗ ████║
██║   ██║ ╚███╔╝  ╚████╔╝█████╗█████╗  ██╔████╔██║
██║   ██║ ██╔██╗   ╚██╔╝ ╚════╝██╔══╝  ██║╚██╔╝██║
╚██████╔╝██╔╝ ██╗   ██║        ██║     ██║ ╚═╝ ██║
 ╚═════╝ ╚═╝  ╚═╝   ╚═╝        ╚═╝     ╚═╝     ╚═╝
```

Copyright (C) 2024 by Matthieu PETIT

## Description

Finite element method code for 2D problem. 

Allows to resolve the variational formulation : 

Find $u\in W$ such that $u = u_D$ on $\Gamma_D$ and $a(u,v) = f(v)$ 

with 

$$a(u,v) = \int_{\Omega} \Big( \sum_{\alpha,\beta=1}^{2} a_{\alpha,\beta}(x) \frac{\partial u}{\partial x_\alpha} (x) \frac{\partial v }{\partial x_\beta}(x)  + a_{00}(x) u(x) v(x) \Big) dx  + \int_{\Gamma_N} b_N (\gamma) y(\gamma) v(\gamma) d\gamma$$

and 

$$f(v) = \int_\Omega f_\Omega (x) v(x) dx + \int_{\Gamma_N} g_N(\gamma) v(\gamma) d\gamma$$


## How to build the project

1. Clone the repo 
2. Get the submodule Eigen with :
    ```
    git submodule update --init --recursive
    ```
3. Compile the project :
   1. With standard `cmake` 
        ``` 
        cd build 
        cmake ..
        make -jN
        ```
    2. With ninja
        ```
        cd build 
        cmake -G Ninja ..
        ninja
        ```

## How to run 

1. Rename the file `parameters.txt.example` to `parameters.txt`
2. Launch the executable : 
    ```
    ./build/exeFEM
    ```
3. The tests are located in the folder `build/tests/`, to launch the executables :
    ```
    ./build/tests/oxyTest
    ./build/tests/oxyTestDiffusion
    ./build/tests/oxyTestCircle
    ./build/tests/oxyTestSinSin
    ```
