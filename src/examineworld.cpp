#include <algorithm>
#include <assert.h>
#include <iostream>
#include "/home/andymcevoy/ros/Cubelet/include/examineworld.h"
#include <gazebo/Global.hh>
#include <gazebo/XMLConfig.hh>
#include <gazebo/gazebo.h>
#include <gazebo/GazeboError.hh>
#include <gazebo/ControllerFactory.hh>

using namespace gazebo;

////////////////////////////////////////////////////////////////////////////////
// Constructor
examineWorld::examineWorld(Entity *parent) : Controller(parent)
{
  myParent=parent;
}
////////////////////////////////////////////////////////////////////////////////
// Destructor
//examineWorld::~examineWorld()
//{
  //}
////////////////////////////////////////////////////////////////////////////////
// Load the controller
void examineWorld::LoadChild(XMLConfigNode *node)
{
}
////////////////////////////////////////////////////////////////////////////////
// Initialize the controller
void examineWorld::InitChild()
{
}
////////////////////////////////////////////////////////////////////////////////
// Update the controller
void examineWorld::UpdateChild()
{
    /***************************************************************/
    /*                                                             */
    /*  this is called at every update simulation step             */
    /*                                                             */
    /***************************************************************/
  Pose3d newPose = myParent->GetWorldPose();
  std::cout << "Hello World!" << std::endl;
  std::cout << "    " << myParent->GetWorldPose()<< std::endl;
}
////////////////////////////////////////////////////////////////////////////////
// Finalize the controller
void examineWorld::FiniChild()
{
}

GZ_REGISTER_DYNAMIC_CONTROLLER("cubelet_examineworld", examineWorld)


