# OOP_Lab4

To run the project, first you have to generate all the necessary "make" files by using CMake. From the root directory of this project run:
```
cmake --clean-first -S . -B out/build/
```

Now go to out/build/:
```
cd out/build/
```
Inside this folder just run this command to compile the code:
```
make
```
Or
```
cmake --build .
```
Now you will find the program **oop_lab** inside the path (relative to the project root directory) : **/out/build/release**

INFO: This code has console feedback for creation and destruction of objects when build for debugging. From the project root directory, use the following commands to build for debugging:
```
cmake --clean-first -S . -B out/build/ - D CMAKE_BUILD_TYPE=Debug
cd out/build/
make
```
Now you will find the program **oop_lab** inside the path (relative to the project root directory) : **/out/build/debug**

WARNING: Make sure if you are using Ubuntu that you have the package "build-essential" installed, otherwise install it:
```
sudo apt-get install build-essential
```
