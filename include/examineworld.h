#ifndef GAZEBO_EXAMINEWORLD_H
#define GAZEBO_EXAMINEWORLD_H
#include <gazebo/Controller.hh>
#include <gazebo/Body.hh>
#include <gazebo/World.hh>

namespace gazebo
{
  class examineWorld : public Controller
  {
    /// \brief Constructor
    /// \param parent The parent entity, must be a Model or a Sensor
  public: examineWorld(Entity *parent);

    /// \brief Destructor
    //public: virtual ~helloGazebo();

    /// \brief Load the controller
    /// \param node XML config node
  protected: virtual void LoadChild(XMLConfigNode *node);

    /// \brief Init the controller
  protected: virtual void InitChild();

    /// \brief Update the controller
  protected: virtual void UpdateChild();

    /// \brief Finalize the controller
  protected: virtual void FiniChild();
    
  private:
    Entity *myParent;
  };
}
#endif

