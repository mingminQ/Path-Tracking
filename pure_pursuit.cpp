#include <cmath>
#include <vector>

class controller_purepursuit
{
  private: // menber variables for pure pursuit controller
  std::vector<float32> waypoints;
  double LookAheadDistance;
  double maxSteering;
  double wheelBase;
  int currentIdx;

  double target_x;
  double target_y;

  double current_x;
  double current_y;
  double current_yaw;

  double targetDistance; 

  int x   = 0;
  int y   = 1;
  int yaw = 2;

  public:
  void init_controller()
  {
  
  }

  void find_target_point(std::vector<float32> vehiclePose)
  {
    // set current vehicle position to rear wheel
    current_x   = vehiclePose[x] - wheelBase * cos(vehiclePose[yaw]);
    current_y   = vehiclePose[y] - wheelBase * sin(vehiclePose[yaw]);
    current_yaw = vehiclePose[yaw];

    // find target point satisfying condition
    for(size_t idx = currentIdx; idx < waypoints.size(); idx++)
    {
      targetDistance = sqrt( pow(waypoint[idx][x] - current_x, 2) + pow(waypoint[idx][y] - current_y, 2));

      if(LookAheadDistance < targetDistance)
      {
        target_x = waypoint[idx][x];
        target_y = waypoint[idx][y];
        currentIdx = idx;
        return;
      }
    }

    // faild to find target point satisfying condition
    if(currentIdx == waypoint.size())
    {
      target_x = waypoint.end()[x];
      target_y = waypoint.end()[y];
    }
  }

  double calculate_steering()
  {
  
  }

  std::vector<float32> control(std::vector<float32> vehiclePose)
  {
    find_target_point(vehiclePose);
    
    double steering = calculate_steering(vehiclePose);
    steering = maxSteering < steering ? maxSteering : ( steering < -maxSteering ? -maxSteering : steering);

    std::vector<float> cmd_vel = {linearVelocity, steering};
    return cmd_vel;
  }
};
