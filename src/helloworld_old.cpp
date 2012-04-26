#include <iostream>
#include <boost/bind.hpp>
#include "gazebo.h"
#include "physics/physics.h"
//#include "Pose.hh"

namespace gazebo
{
  class cubelet_HelloWorld : public ModelPlugin
  {
  public: cubelet_HelloWorld() : ModelPlugin()
    {
      std::cout << "*****\n\n HELLO CUBELETS!\n\n*****";
    }
  public: void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
    {
      this->model = _parent;
      this->updateConnection = event::Events::ConnectWorldUpdateStart(boost::bind(&cubelet_HelloWorld::OnUpdate, this));
    }
  public: void OnUpdate()
    {
      //std::cout << "Joint Count = " << model->GetWorldPose() << std::endl;
      pose=model->GetWorldPose();
      //newPosition.x=0.0;
      //newPosition.y=0.0;
      //newPosition.z=1.0;
      if (pose.pos.z<0.1) 
	{
	  std::cout << "    Reset position\n";
	  pose.pos.z=1.0;
	  model->SetWorldPose(pose);
	  std::cout << "        New joint position = " << model->GetWorldPose() << std::endl;
	}
    }
  private: physics::ModelPtr model;
  private: math::Pose pose;
  private: math::Vector3 newPosition;
  private: event::ConnectionPtr updateConnection;
  };
  GZ_REGISTER_MODEL_PLUGIN(cubelet_HelloWorld)
}



