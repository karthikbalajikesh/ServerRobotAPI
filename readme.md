# Server API for Autonomous Wheeled Robot

A vector of Obstacles and Lane points are sent to the Server via TCP protocol from a remote Client on an Arm 64 based Linux Platform. The hardware used here is NVIDIA Jetson Nano. 

## Functions Performed 
* Receive the Message Object from Client
* Deserialize the Message
* Behavioral Planner identifies the destination (Currently only Lane Following)
* Path Planner generates waypoints
* Plan Velocity and Orientation (To be Added)
* Send the Path object back to the client (To be Added)
