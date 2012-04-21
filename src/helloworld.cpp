#include "gazebo.h"
#include <iostream>

namespace gazebo
{
  class cubelet_HelloWorld : public WorldPlugin
  {
  public: cubelet_HelloWorld() : public WorldPlugin()
    {
      printf("Hello Cubelets!\n");
    }
  public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
    {
    }
  public: void OnUpdate()
    {
      std::cout << "on update function\n";
    }
  };
  GZ_REGISTER_WORLD_PLUGIN(cubelet_HelloWorld)
}



