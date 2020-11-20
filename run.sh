export GAZEBO_MODEL_PATH=$PWD/models:$GAZEBO_MODEL_PATH
export GAZEBO_PLUGIN_PATH=$PWD/build:$GAZEBO_PLUGIN_PATH

#gazebo cholessy_wiltshire.world
gzserver -u InternationalSpaceStationWorld.world &
gzclient
