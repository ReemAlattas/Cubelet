#include <iostream>
#include <boost/bind.hpp>
#include <string>
#include "gazebo.h"
#include "physics/physics.h"
//#include "Pose.hh"

namespace gazebo
{
  class cubelet_HelloWorld : public WorldPlugin
  {
  public: cubelet_HelloWorld() : WorldPlugin()
    {
      std::cout << "*****\n\n HELLO CUBELETS!\n\n*****";
    }
  public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
    {
      this->world = _world;
      this->updateConnection = event::Events::ConnectWorldUpdateStart(boost::bind(&cubelet_HelloWorld::OnUpdate, this));
      this->lastTime = world->GetRealTime();
      this->modelCount = _world->GetModelCount();
	  
	  // get Models
      std::cout << "*****\n\n MODEL COUNT = "<< modelCount <<"\n\n*****";
	  int i,j;
	  for( i=0; i<modelCount;i++)
	  {
		  std::cout << "\nModel[ "<< i <<" ] = "<< world->GetModel(i)->GetName()<<"\n";
		  this->isStuckToAny[i]=0;
		  
		  for( j=0; j<modelCount; j++)
			  this->isStuck[i][j]=0;
	  }
    }
 public: void OnUpdate()
    {
		int i, j;
		double dist;
		physics::LinkPtr link_i,link_j;

	    //add force to cublet 1
		world->GetModel(1)->GetLink("body")->SetForce(math::Vector3(-2,2,0));
						
		for( i=0; i < modelCount ; i++)
		{
			//If [i] is cublet
			if (world->GetModel(i)->GetName().find("cubelet") != std::string::npos)
			{
				for( j=0; j < i ; j++)
				{
					//If [j] is cublet
					if (world->GetModel(j)->GetName().find("cubelet") != std::string::npos )
					{
						//Get links
						link_i = world->GetModel(i)->GetLink("body");
						link_j = world->GetModel(j)->GetLink("body");
						 
						dist = (link_j->GetWorldPose() - link_i->GetWorldPose()).pos.GetLength();

						if(isStuck[i][j])
						{
							link_i->SetWorldPose(link_j->GetWorldPose());// + poseRel[i][j]);
							link_i->SetLinearAccel(math::Vector3(0,0,0));
							link_i->SetLinearVel(math::Vector3(0,0,0));
						
							//only once a second print
							if (lastTime.sec < world->GetRealTime().sec)
							{
								//Print Distance from i to j
								std::cout << "*****\n Time = "<< world->GetRealTime() <<"\n";
								std::cout << " Distance = "<< dist <<"\n";
								std::cout << " "<<world->GetModel(i)->GetName()<<" connected to \n";
								std::cout << " "<<world->GetModel(j)->GetName()<<"\n";
							}
						}
						else//not stuck
						{
							//find relative position
							poseRel[i][j] = link_j->GetWorldPose() - link_i->GetWorldPose();
							if( world->GetPhysicsEngine()->AreTouching(link_i,link_j))
							{
								//not already stuck
								if(!isStuckToAny[i])
								{
									// should be stuck
									isStuck[i][j]=1;
									isStuckToAny[i]=1;
									std::cout << "\n****\nStuck ["<<i<<"] to ["<<j<<"].\nPose = "<<poseRel[i][j];
								}
							}
						}
					}
				}
			}
		}
		
      
      this->lastTime = world->GetRealTime();
      
    }
  private: physics::WorldPtr world;
  private: event::ConnectionPtr updateConnection;
  private: common::Time lastTime;
  private: double modelCount;
  private: math::Pose poseRel[5][5];
  private: bool isStuck[5][5];
  private: bool isStuckToAny[5];
  };
  GZ_REGISTER_WORLD_PLUGIN(cubelet_HelloWorld)
}



