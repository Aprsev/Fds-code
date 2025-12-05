# Build Instructions

```bash
# Configure the project
cmake .

# Build the project
cmake --build .
```

If you don't want to build in current directory, you could:

```bash
# Create and navigate to a build directory
mkdir build
cd build

# Configure from parent directory
cmake ..

# Build the project
cmake --build .
```