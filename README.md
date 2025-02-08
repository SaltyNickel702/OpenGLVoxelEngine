# Creating a Voxel Engine from scratch using OpenGL and C++
### Project Specifications
- Using CMake for project management
- Currently using Ninja compiler on windows machine


Currently able to open a window using GLFW and handle user keyboard input
Engine is built in the Game namespace

### Documentation
All under Game namepace
- `window`
  - contains the GLFW window
- `createWindow(int w, int h)`
  - creates window of `w` width and `h` height and assigns to `window` variable
- `keyDown(int GLFWkey)`
  - bool value of if a key is down
- `addCallbackToKeyDown(int GLFWkey, std::function<void()>& func)`
  - executes func() everytime the specified key is pushed down
