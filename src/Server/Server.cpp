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
    // Behavioral Planner will run here and decide on destination
    getDestination(Data);
    // Get the Path
    PlanPath();
    // Then we will fit velocity along the path.
    getTrajectory();
    // Next will be to create a Path object, serialize and send
    sendMessage();
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
    Data.printVector();
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

void Server::PlanPath(){
    int index = 0;
    while(1){
        // After that Path Planner will give Path.
        PathPlanner = DijkstraPRM(destination,numSamples,
        zmax,xmax,cellwidth,cellheight,radius,ObstacleVector);
        //PathPlanner.PrintPathDetails();
        Pathway = PathPlanner.GetPathVector();
        //std::cout<<"\n\n"<<Pathway.size();
        if (Pathway.size()>=7){
            // Only break when there are enough points
            
            break;
        }
        index++;
        if (index>=3){
            std::cout<<"Error No path"<<std::endl;
            Pathway = vector<floatpair>();
            break;
        }
    }
}

void Server::getTrajectory(){
    Velocity = vector<float>(Pathway.size(),0.5);
    // Currently no stop sign is being considered.
    Waypoints = Path(Pathway,Velocity);
    //Waypoints.printDetails();
}

void Server::sendMessage(){
    
    boost::asio::streambuf buf;
    std::ostream OutputStream(&buf);
    boost::archive::text_oarchive OutputArchive(OutputStream);
    // Perform Serialization
    OutputArchive & Waypoints;
 
    // Scatter Send
    const size_t header = buf.size();
    vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::const_buffer(&header, 
                        sizeof(header)));
    buffers.push_back(buf.data());
    boost::asio::write(*SOCK,buffers);

    SOCK->shutdown(boost::asio::socket_base::shutdown_send);
}
