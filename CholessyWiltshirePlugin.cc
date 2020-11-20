#include <functional>

#include <ignition/math/Vector3.hh>

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include "gazebo/transport/transport.hh"
#include "CholessyWiltshirePlugin.hh"

using namespace gazebo;


namespace gazebo
{
/////////////////////////////////////////////////
CholessyWiltshirePlugin::CholessyWiltshirePlugin()
{
}

/////////////////////////////////////////////////
CholessyWiltshirePlugin::~CholessyWiltshirePlugin()
{
}

/////////////////////////////////////////////////
void CholessyWiltshirePlugin::OnCholessyWiltshire(ConstCholessyWiltshirePtr &_msg)
{
  std::lock_guard<std::mutex> lock(this->msgMutex);
  this->cholessyWiltshireMsgPtr = _msg;
}

/////////////////////////////////////////////////
void CholessyWiltshirePlugin::Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
{
  // Get the world name.
  this->model = _parent;
  this->world = this->model->GetWorld();

  // Subscribe to Hydra updates by registering OnHydra() callback.
  this->node = transport::NodePtr(new transport::Node());
  this->node->Init(this->world->Name());
  this->CholessyWiltshireSub = this->node->Subscribe("~/cholessy_wiltshire",
                                                    &CholessyWiltshirePlugin::OnCholessyWiltshire, this);

  // Listen to the update event. This event is broadcast every
  // simulation iteration.
  this->updateConnection = event::Events::ConnectWorldUpdateBegin(
      std::bind(&CholessyWiltshirePlugin::Update, this));
}

/////////////////////////////////////////////////
void CholessyWiltshirePlugin::Update()
{
  std::lock_guard<std::mutex> lock(this->msgMutex);

  // Move the model.
  this->model->SetLinearVel(
                              ignition::math::Vector3d( 0.2, 0.2, 0));


  // Remove the message that has been processed.
  this->cholessyWiltshireMsgPtr.reset();
}

GZ_REGISTER_MODEL_PLUGIN(CholessyWiltshirePlugin)
}
