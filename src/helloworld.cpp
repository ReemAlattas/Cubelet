#include <algorithm>
#include <assert.h>
#include <iostream>
#include "../include/helloworld.h"
#include <gazebo/Global.hh>
#include <gazebo/XMLConfig.hh>
#include <gazebo/gazebo.h>
#include <gazebo/GazeboError.hh>
#include <gazebo/ControllerFactory.hh>

using namespace gazebo;

////////////////////////////////////////////////////////////////////////////////
// Constructor
helloGazebo::helloGazebo(Entity *parent) : Controller(parent)
{
}
////////////////////////////////////////////////////////////////////////////////
// Destructor
//helloGazebo::~helloGazebo()
//{
  //}
////////////////////////////////////////////////////////////////////////////////
// Load the controller
void helloGazebo::LoadChild(XMLConfigNode *node)
{
}
////////////////////////////////////////////////////////////////////////////////
// Initialize the controller
void helloGazebo::InitChild()
{
}
////////////////////////////////////////////////////////////////////////////////
// Update the controller
void helloGazebo::UpdateChild()
{
    /***************************************************************/
    /*                                                             */
    /*  this is called at every update simulation step             */
    /*                                                             */
    /***************************************************************/
  std::cout << "Hello World!" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
// Finalize the controller
void helloGazebo::FiniChild()
{
}

GZ_REGISTER_DYNAMIC_CONTROLLER("cubelet_helloworld", helloGazebo)


