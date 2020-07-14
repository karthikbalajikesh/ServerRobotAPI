#include<iostream>
#include<fstream>
#include<vector>
#include <boost/archive/text_oarchive.hpp>
#include<utility>
#include <boost/archive/text_iarchive.hpp>
#include<boost/serialization/serialization.hpp>
#include<boost/serialization/access.hpp>
#include<boost/serialization/vector.hpp>
#include<boost/serialization/utility.hpp>

using std::vector;
using std::cout;
using std::pair;
using std::endl;
#define mp std::make_pair

typedef std::pair<float,float> floatpair;
// Class that contains the response sent from Server
// This is the path that needs to be followed by the
// robot
class Path{
private:
    friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &A, const unsigned int version){
      A & WaypointsPos;
      A & WaypointsVel;
  }
public:
  vector<floatpair> WaypointsPos;
  vector<float>WaypointsVel;

  Path(){}
  Path(vector<floatpair>& pos, vector<float> vel){
      WaypointsPos = pos;
      WaypointsVel = vel;
  }

  void setParams(vector<floatpair> &Cood){
      WaypointsPos = Cood;
  }

  void printDetails(){
    printPosition();
    printVelocity();


  }

  void printPosition(){
    std::cout<<" Position : "<<std::endl;
    for (auto node:WaypointsPos){
      std::cout<<"( "<<node.first<<" , "<<
                  node.second<<" ) "<<std::endl;
    }
  }

  void printVelocity(){
    std::cout<<" Velocity : "<<std::endl;
    for (auto v:WaypointsVel){
      std::cout<<v<< "  m/s"<<std::endl;
    }
  }

};
