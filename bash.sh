#!/bin/bash


if [ $# -eq 0 ]; then
    repo="."
else
    repo=$1
fi
# rm -r $repo/build
# rm $repo/cmake_install.cmake
# rm $repo/CMakeCache.txt
# rm $repo/Makefile
# rm -r $repo/CMakeFiles
# mkdir $repo/build



# # Vérifiez si le répertoire existe
# if [ -d "$repo" ]; then
#     echo "Le répertoire existe."
# else
#     echo "Le répertoire n'existe pas."
# fi


# cmake $repo/ -DCMAKE_BUILD_TYPE=Debug -G Ninja

cmake $repo/ -DCMAKE_BUILD_TYPE=Debug 

# ninja 
make -j10