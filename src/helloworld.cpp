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
		physics::LinkPtr link_i,link_j;
		math::Pose relativePose, stuckPose;
		math::Vector3 stuckPosition;
		
	    //add force to cublet 
		//world->GetModel(1)->GetLink("body")->SetForce(math::Vector3(0,0,2));
		
		//itterate over each model
		for( i=0; i < modelCount ; i++)
		{
			//If model[i] is cublet
			if (world->GetModel(i)->GetName().find("cubelet") != std::string::npos)
			{
				
				//itterate over lower number models
				for( j=0; j < i ; j++)
				{
					//If [j] is cublet
					if (world->GetModel(j)->GetName().find("cubelet") != std::string::npos )
					{
						//Get links
						link_i = world->GetModel(i)->GetLink("body");
						link_j = world->GetModel(j)->GetLink("body");

						
						if(isStuck[i][j])
						{
							//print relative positions each second
							if ( lastTime.sec < world->GetRealTime().sec )
							{
								std::cout <<"\n ["<<i<<"]to["<<j<<"] Position="<<link_i->GetWorldPose().pos - link_j->GetWorldPose().pos;
							}
							//TO DO:test forces and torque to see if connection joint breaks
						
						}
						else//not stuck
						{
							//find is in contact
							if( world->GetPhysicsEngine()->AreTouching(link_i,link_j))
							{
								//not already stuck
								if(!isStuckToAny[i])
								{
									// stick i to j
									isStuck[i][j]=1;
									isStuckToAny[i]=1;

									//Snap into position
									relativePose = link_i->GetWorldPose() - link_j->GetWorldPose();
								    stuckPosition = GetStuckPosition(relativePose.pos) * 0.042;
									stuckPose = math::Pose( stuckPosition , math::Quaternion(0,0,0) );
									link_i->SetWorldPose(stuckPose + link_j->GetWorldPose() );
									
									//Change Joint to connect to new link
									world->GetModel(i)->GetJoint("cube_joint")->Attach(link_j,link_i);
									std::cout << "\n****\nStuck ["<<i<<"] to ["<<j<<"]";
									std::cout << "\nrelative postion = " << relativePose.pos ;
									std::cout << "\npose = " << link_i->GetWorldPose();
								}
							}
						}
					}
				}
			}
		}
		
      
      this->lastTime = world->GetRealTime();
      
    }
  private: math::Vector3 GetStuckPosition(math::Vector3 position)
	{
		int i, s;
		double maxDotProd = 0, dotProd, x,y,z,sign;
		math::Vector3 unitVector, maxVector;
		//Itterate over 6 on-axis vectors
		for (i = 0; i < 3; i++)
		{
			for(s = 0; s < 2; s++)
			{
				//Set up directtion vector
				x = (i==0), y = (i==1), z = (i==2);
				sign = s==1 ? 1 : -1;
				unitVector.Set(sign * x ,sign * y , sign * z);
				dotProd = position.GetDotProd(unitVector);
				if (dotProd > maxDotProd)
				{
					maxDotProd = dotProd;
					maxVector = unitVector;
				}
			}
		}
		return maxVector;
	}
  private: physics::WorldPtr world;
  private: event::ConnectionPtr updateConnection;
  private: common::Time lastTime;
  private: double modelCount;
  private: bool isStuck[5][5];
  private: bool isStuckToAny[5];
  };
  GZ_REGISTER_WORLD_PLUGIN(cubelet_HelloWorld)
}



