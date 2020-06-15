#include "Server.h"

Server::Server():TCP(),PathPlanner(mp(0,0),
    800, 3, 2, 1, 1, 0.25, ObstacleVector),
    BehaviorPlanner(){
    

}
// Master function that takes the work of a server
void Server::Communicate(){
    setupConnection();
    readMessage();
    CreateObstacleVector();
    getDestination(Data);
    PathPlanner = DijkstraPRM(destination,numSamples,
        zmax,xmax,cellwidth,cellheight,radius,ObstacleVector);
    // Behavioral Planner will run here and decide on destination
    // After that Path Planner will give Path.
    // Then we will fit velocity along the path.
    PathPlanner.PrintPathDetails();
}

void Server::setupConnection(){
    Acceptor->listen(BACKLOG_SIZE);
    SOCK = std::make_shared<SOCKET>(*IO);
    Acceptor->accept(*SOCK);
    
}

void Server::readMessage(){
    // get header
    size_t header;
    boost::asio::read(*SOCK,
        boost::asio::buffer( &header, sizeof(header)));
    
    // get body
    boost::asio::streambuf buf;
    boost::asio::read(*SOCK,buf.prepare(header));
    buf.commit(header);

    // deSerialize
    deSerialize(buf);
}

void Server::deSerialize(boost::asio::streambuf &buf){
    std::istream is(&buf);
    boost::archive::text_iarchive ar( is );
    ar & Data;
}

void Server::CreateObstacleVector(){
    ObstacleVector = Data.Obstacles;
    ObstacleVector.insert(ObstacleVector.end(),
        Data.LaneLeft.begin(),Data.LaneLeft.end());
    ObstacleVector.insert(ObstacleVector.end(),
        Data.LaneRight.begin(),Data.LaneRight.end());
}