#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include<utility>
#include <boost/archive/text_oarchive.hpp>
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

class message{
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &A, const unsigned int version){
      A & Obstacles;
      A & LaneLeft;
      A & LaneRight;
      A & stop_sign;
  }
public:
  vector<pair<float,float>> Obstacles;
  vector<pair<float,float>> LaneLeft;
  vector<pair<float,float>> LaneRight;
  int stop_sign;  // if 0, no stop sign.
  message(){}

  message(vector<floatpair> &Obs, vector<floatpair> &laneleft,
       vector<floatpair> &laneright):Obstacles(Obs),LaneLeft(laneleft)
       , LaneRight(laneright),stop_sign(0){}

  void printVector(){
      std::cout<<"\n OBSTACLES:      "<<std::endl;
      for(auto x:Obstacles){
          cout<<"\n"<<x.first<<"\t"<<x.second;
      }
      cout<<std::endl;

      std::cout<<"\n LEFTLANE:      "<<std::endl;
      for(auto x:LaneLeft){
          cout<<"\n"<<x.first<<"\t"<<x.second;
      }
      cout<<std::endl;

      std::cout<<"\n LANERIGHT:      "<<std::endl;
      for(auto x:LaneRight){
          cout<<"\n"<<x.first<<"\t"<<x.second;
      }
      cout<<std::endl;
  }

  // Non Constructor function to create the message.
  void setParams(vector<floatpair> &Obs, vector<floatpair> &laneleft,
       vector<floatpair> &laneright){
         Obstacles = Obs;
         LaneLeft = laneleft;
         LaneRight = laneright;

       }
};