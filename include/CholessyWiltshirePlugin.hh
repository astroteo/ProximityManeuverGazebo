#ifndef GAZEBO_PLUGINS_HYDRADEMOPLUGIN_HH_
#define GAZEBO_PLUGINS_HYDRADEMOPLUGIN_HH_

#include <mutex>
#include <ignition/transport/Node.hh>
#include "gazebo/physics/physics.hh"
#include "gazebo/msgs/msgs.hh"
#include "gazebo/transport/TransportTypes.hh"
#include "gazebo/common/Plugin.hh"
#include "gazebo/common/Events.hh"
#include "cholessy_wiltshire_physics_msgs_creator.pb.h"
namespace gazebo
{
  class GZ_PLUGIN_VISIBLE CholessyWiltshirePlugin : public ModelPlugin
  {
    /// \brief Constructor
    public: CholessyWiltshirePlugin();

    /// \brief Destructor
    public: virtual ~CholessyWiltshirePlugin();

    // Documentation Inherited.
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);

    /// \brief Update the controller
    private: void Update();

    /// \brief Callback executed every time a new hydra message is received.
    /// \param[in] _msg The hydra message.
    private: void OnCholessyWiltshire(ConstCholessyWiltshirePtr &_msg);

    /// \brief World pointer
    private: physics::WorldPtr world;

    /// \brief Model pointer
    private: physics::ModelPtr model;

    /// \brief Node used for using Gazebo communications.
    private: transport::NodePtr node;

    /// \brief Subscribe pointer.
    private: transport::SubscriberPtr CholessyWiltshireSub;

    /// \brief Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;

    /// \brief Mutex to protect hydraMsgPtr.
    private: std::mutex msgMutex;

    /// \brief Store the last message from hydra.
    private: boost::shared_ptr<const gazebo::msgs::CholessyWiltshire> cholessyWiltshireMsgPtr;

    // Place ignition::transport objects at the end of this file to
    // guarantee they are destructed first.

    /// \brief Ignition node used for communication.
    private: ignition::transport::Node nodeIgn;
  };
}
#endif
