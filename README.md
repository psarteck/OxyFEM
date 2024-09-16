# OxyFEM

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
