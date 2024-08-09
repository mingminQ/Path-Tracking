#include <cmath>
#include <vector>

struct Pose2D
{
  double x, y, yaw;
};

struct cmd_vel
{
  double v, w;
};

class controller_purepursuit
{
  public:

  // initialize controller
  void init_controller()
  {
  
  }

  // calculate distance between two points
  double get_distance( Pose2D point1, Pose2D point2 )
  {
    return sqrt( pow(point2.x - point1.x, 2) + pow(point2.y - point1.y) );
  }

  // calculate rear vehicle position
  Pose2D get_vehicle_position_rear( Pose2D vehiclePose )
  {
    Pose2D vehiclePose_raer;
    vehiclePose_raer.x   = vehiclePose.x - ( wheelBase / 2.0 ) * cos( vehiclePose.yaw );
    vehiclePose_raer.x   = vehiclePose.y - ( wheelBase / 2.0 ) * sin( vehiclePose.yaw );
    vehiclePose_rear.yaw = vehiclePose.yaw;
  }

  // calculate target waypoint
  Pose2D get_target_point( Pose2D vehiclePose )
  {
      Pose2D targetPoint;
    
      if( currentIdx == waypoints.size() )
      {
        targetPoint.x = waypoints[ waypoints.size() - 1 ].x;
        targetPoint.y = waypoints[ waypoints.size() - 1 ].y;
        return targetPoint;
      }

    Pose2D vehiclePose_raer = get_vehicle_position_rear( vehiclePose );


    for(size_t idx = currentIdx; idx < waypoints.size(); idx++)
    {
      double distance = get_distance( vehiclePose_raer, waypoints[idx] );
      
      if( LookAheadDistance <= distance )
      {
        targetPoint.x = waypoints[idx].x;
        targetPoint.y = waypoints[idx].y;
        currentIdx = idx;
        return targetPoint;
      }
    }
  }

  // calculate steering angle
  Pose2D get_steering_angle( Pose2D vehiclePose )
  {
    Pose2D targetPoint = get_target_point(vehiclePose);
    
  }

  // return linear velocity and steering angle
  cme_vel control( Pose2D vehiclePose)
  {
    cmd_vel control_input;
    control_input.w = get_steering_angle( vehiclePose );
    
    // add linear velocity controller
    // control_input.v = 
    
    return control_input;
  }
};
