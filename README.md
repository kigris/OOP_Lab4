# OOP_Lab4

To run the project, first you have to generate all the necessary "make" files by using CMake. From the root directory of this project run:
```
cmake --clean-first -S ../../ -B .
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
WARNING: Make sure if you are using Ubuntu that you have the package "build-essential" installed, otherwise install it:
```
sudo apt-get install build-essential
```
