#ifndef VEHICLE_H
#define VEHICLE_H

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

#define timestep 0.02 //corresponds to 1 timestep
//#define timestep 1 //corresponds to 50 timesteps

class Vehicle {
public:
    // Constructors
    Vehicle();
    Vehicle(int lane, float s, float v, float a, string state="CS", float d = -1, int id = -1);
    
    // Destructor
    virtual ~Vehicle();
    
    // Vehicle functions
    vector<Vehicle> choose_next_state(map<int, vector<Vehicle>> &predictions);
    
    vector<string> successor_states();
    
    vector<Vehicle> generate_trajectory(string state,
    map<int, vector<Vehicle>> &predictions);
    
    float get_kinematics(map<int, vector<Vehicle>> &predictions, int lane);
    
    vector<Vehicle> keep_lane_trajectory(map<int, vector<Vehicle>> &predictions);
    
    vector<Vehicle> lane_change_trajectory(string state,
    map<int, vector<Vehicle>> &predictions);
    
    void set_lane(double d);
    
    void increment(int dt, int prev_size);
    
    float position_at(int t, int prev_size);
    
    bool get_vehicle_behind(map<int, vector<Vehicle>> &predictions, int lane,
    Vehicle &rVehicle);
    
    bool get_vehicle_ahead(map<int, vector<Vehicle>> &predictions, int lane,
    Vehicle &rVehicle);
    
    vector<Vehicle> generate_predictions(int horizon, int prev_size);
   
    
    // public Vehicle variables
    struct collider{
        bool collision; // is there a collision?
        int  time; // time collision happens
    };
    
    map<string, int> lane_direction = {{"PLCL", -1}, {"LCL", -1},
    {"LCR", 1}, {"PLCR", 1}};
    
    int L = 1;
    
    int preferred_buffer = 6; // impacts "keep lane" behavior.
    
    int lane, goal_lane, lanes_available, id;
    double yaw, x, y, s, goal_s;
    
    float d, v, target_speed, a, max_acceleration, ref_v;

    string state;
};

#endif  // VEHICLE_H
