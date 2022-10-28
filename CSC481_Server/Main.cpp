#include <zmq.hpp>
#include <string>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Timeline.h"
#include "MovingPlatform.h"
#include "EventManager.h"
#include "Event.h"
#include "EventHandler.h"
#include<vector>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#endif
int numClients = 0;
int client1 = 0;
int client2 = 0;
int client3 = 0;
sf::Vector2f p1;
sf::Vector2f p2;
sf::Vector2f p3;
sf::Vector2f m;
sf::Vector2f m2;
bool first = false;
float last_time;
float elapsed;
EventManager manager;
EventHandler conh("connection");
Event ce("connection");
Event ce2("connection");
Event ce3("connection");

// from ZMQ Zhelper
int s_send(void* socket, const char* string, int flags = 0) {
    int rc;
    zmq_msg_t message;
    zmq_msg_init_size(&message, strlen(string));
    memcpy(zmq_msg_data(&message), string, strlen(string));
    rc = zmq_msg_send(&message, socket, flags);
    assert(-1 != rc);
    zmq_msg_close(&message);
    return (rc);
}

int main() {
    manager.evenh(&conh);
    //  Prepare our context and socket
    zmq::context_t context(1);
    //   zmq::context_t context2(2);
    zmq::socket_t publisher(context, ZMQ_PUB);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");
    publisher.bind("tcp://*:5556");
    zmq::socket_t pub(context, ZMQ_PUB);
    pub.bind("tcp://*:5557");

    int sndhwm = 0;
    pub.setsockopt(ZMQ_SNDHWM, &sndhwm, sizeof(sndhwm));
    //  Socket to receive signals
    zmq::socket_t syncservice(context, ZMQ_REP);
    syncservice.bind("tcp://*:5562");

    // Set up a time for the moving platform
    sf::Clock c1;
    sf::Clock c2;
    // Create the original timeline, since we are using seconds, set tic to 1 to operate in second
    Timeline origin(NULL, 1, true, &c1);
    // Create the timeline for main game loop
    Timeline tline(&origin, 1, false, &c2);
    MovingPlatform mp;
    mp.setPosition(0, 400);

    MovingPlatform mp2;
    mp2.setPosition(300, 500);


    while (true) {
        std::vector<float> array;
        std::vector<float> array2;
        std::vector<float> array3;
        
        float time = tline.getTime();
        elapsed = time - last_time;
        last_time = time;
        mp.updateTime(elapsed);
        mp.leftRight();
        mp2.updateTime(elapsed);
        mp2.upDown();
        m = mp.getShape().getPosition();
        m2 = mp2.getShape().getPosition();
        zmq::message_t request;
        std::stringstream mes;
        //  Wait for next request from client
        socket.recv(&request);
        std::string rpl = std::string(static_cast<char*>(request.data()), request.size());
        std::string join = "Join";

        // Put the result on standard out
       // std::copy(array.begin(), array.end(), std::ostream_iterator<float>(std::cout, " "));

  //       std::cout  << rpl << std::endl;
        if (rpl.compare(join) == 0) { // new client join
            first == true;
            numClients++;
            int newID = numClients;
            

            std::cout << "Received join from client " << newID << std::endl;
            //  Send the client id
            ce.cid = newID;
            ce.setSocket(&socket);
            ce.setPriority(1);
            manager.raise(&ce);
            manager.handleEvents(1);
            zmq::message_t request;
            socket.recv(&request);
            std::string rpl = std::string(static_cast<char*>(request.data()), request.size());
            std::istringstream iss(rpl);
            std::copy(std::istream_iterator<float>(iss), std::istream_iterator<float>(), std::back_inserter(array));
            p1.x = array.at(1);
            p1.y = array.at(2);
            s_send(socket, "receive");
            //              std::cout << p1.x << p1.y << std::endl;


            if (numClients == 2) {
                zmq::message_t request;
                socket.recv(&request);
                std::string rpl = std::string(static_cast<char*>(request.data()), request.size());
                std::istringstream iss(rpl);
                std::copy(std::istream_iterator<float>(iss), std::istream_iterator<float>(), std::back_inserter(array2));
                p2.x = p1.x;
                p2.x = p1.x;
                p1.x = array2.at(1);
                p1.y = array2.at(2);
                s_send(socket, "receive");
            }
            else if (numClients == 3) {
                p3.x = p1.x;
                p3.x = p1.x;

                zmq::message_t request;
                socket.recv(&request);
                std::string rpl = std::string(static_cast<char*>(request.data()), request.size());
                std::istringstream iss(rpl);
                std::copy(std::istream_iterator<float>(iss), std::istream_iterator<float>(), std::back_inserter(array2));
                p1.x = array2.at(1);
                p1.y = array2.at(2);
                s_send(socket, "receive");

                zmq::message_t request2;
                socket.recv(&request2);
                std::string rpl2 = std::string(static_cast<char*>(request2.data()), request2.size());
                std::istringstream isss(rpl2);
                std::copy(std::istream_iterator<float>(isss), std::istream_iterator<float>(), std::back_inserter(array3));
                p2.x = array3.at(1);
                p2.y = array3.at(2);
                s_send(socket, "receive");

                if (array2.at(0) == 2) {
                    p1.x = array3.at(1);
                    p1.y = array3.at(2);
                    p2.x = array2.at(1);
                    p2.y = array2.at(2);
                }
            }




        }
        else {
            std::string rpl = std::string(static_cast<char*>(request.data()), request.size());
            std::istringstream iss(rpl);
            std::copy(std::istream_iterator<float>(iss), std::istream_iterator<float>(), std::back_inserter(array));
            p1.x = array.at(1);
            p1.y = array.at(2);
            s_send(socket, "receive");
            if (numClients == 2) {
                zmq::message_t request;
                socket.recv(&request);
                std::string rpl = std::string(static_cast<char*>(request.data()), request.size());
                std::istringstream isss(rpl);
                std::copy(std::istream_iterator<float>(isss), std::istream_iterator<float>(), std::back_inserter(array2));
                p2.x = array2.at(1);
                p2.y = array2.at(2);
                s_send(socket, "receive");
                if (array2.at(0) == 1) {
                    p1.x = array2.at(1);
                    p1.y = array2.at(2);
                    p2.x = array.at(1);
                    p2.y = array.at(2);
                }
            }
            else if (numClients == 3) {
                zmq::message_t request;
                socket.recv(&request);
                std::string rpl = std::string(static_cast<char*>(request.data()), request.size());
                std::istringstream iss(rpl);
                std::copy(std::istream_iterator<float>(iss), std::istream_iterator<float>(), std::back_inserter(array2));
                p2.x = array2.at(1);
                p2.y = array2.at(2);
                s_send(socket, "receive");

                zmq::message_t request2;
                socket.recv(&request2);
                std::string rpl2 = std::string(static_cast<char*>(request2.data()), request2.size());
                std::istringstream isss(rpl2);
                std::copy(std::istream_iterator<float>(isss), std::istream_iterator<float>(), std::back_inserter(array3));
                p3.x = array3.at(1);
                p3.y = array3.at(2);
                s_send(socket, "receive");

                if (array2.at(0) == 1) {
                    p1.x = array2.at(1);
                    p1.y = array2.at(2);
                }
                if (array3.at(0) == 1) {
                    p1.x = array3.at(1);
                    p1.y = array3.at(2);
                }


                if (array.at(0) == 2) {
                    p2.x = array.at(1);
                    p2.y = array.at(2);
                }
                if (array3.at(0) == 2) {
                    p2.x = array3.at(1);
                    p2.y = array3.at(2);
                }

                if (array.at(0) == 3) {
                    p3.x = array.at(1);
                    p3.y = array.at(2);
                }
                if (array2.at(0) == 3) {
                    p3.x = array2.at(1);
                    p3.y = array2.at(2);
                }
            }

        }
       
        // 1 : p, 2 : u, 3 : 1x, 4 : 2x, 5: 0.5x
        
        int size1 = array.size();
        int size2 = array2.size();
        int size3 = array3.size();
  //      std::cout << size1 << std::endl;
        if (size1 > 3 ) {
            int action = array.at(3);
            if (action == 1) {
                tline.paused();
            }
            else if (action == 2) {
                tline.unpaused();
            }
            else if (action == 3) {
                tline.changeTic(1);
                mp.updateTic(true);
                mp2.updateTic(true);
            }
            else if (action == 4) {
                tline.changeTic(2);
                mp.updateTic(true);
                mp2.updateTic(true);
            }
            else if (action == 5) {
                tline.changeTic(0.5);
                mp.updateTic(true);
                mp2.updateTic(true);
            }
        }

        if (size2 > 3) {
            int action = array2.at(3);
            if (action == 1) {
                tline.paused();
            }
            else if (action == 2) {
                tline.unpaused();
            }
            else if (action == 3) {
                tline.changeTic(1);
                mp.updateTic(true);
                mp2.updateTic(true);
            }
            else if (action == 4) {
                tline.changeTic(2);
                mp.updateTic(true);
                mp2.updateTic(true);
            }
            else if (action == 5) {
                tline.changeTic(0.5);
                mp.updateTic(true);
                mp2.updateTic(true);
            }
        }

        if (size3 > 3) {
            int action = array3.at(3);
            if (action == 1) {
                tline.paused();
            }
            else if (action == 2) {
                tline.unpaused();
            }
            else if (action == 3) {
                tline.changeTic(1);
                mp.updateTic(true);
                mp2.updateTic(true);
            }
            else if (action == 4) {
                tline.changeTic(2);
                mp.updateTic(true);
                mp2.updateTic(true);
            }
            else if (action == 5) {
                tline.changeTic(0.5);
                mp.updateTic(true);
                mp2.updateTic(true);
            }
        }





        // the string to send the position of each character
        std::stringstream Pstr;

        // Update the iteration number
        if (numClients == 0) {
            // do nothing
        }
        else if (numClients == 1) {
            mes << "Client 1:Iteration " << client1;
            Pstr << 1 << " " << mp.getLR() << " " << mp2.getUD() << " " << elapsed << " " << m.x << " " << m.y << " " << m2.x << " " << m2.y << " " << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << " " << p3.x << " " << p3.y;
            client1++;
        }
        else if (numClients == 2) {
            mes << "Client 1:Iteration " << client1 << " Client 2:Iteration " << client2;
            Pstr << 2 << " " << mp.getLR() << " " << mp2.getUD() << " " << elapsed << " " << m.x << " " << m.y << " " << m2.x << " " << m2.y << " " << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << " " << p3.x << " " << p3.y;
            client1++;
            client2++;
        }
        else if (numClients == 3) {
            mes << "Client 1:Iteration " << client1 << " Client 2:Iteration " << client2 << " Client 3:Iteration " << client3;
            Pstr << 3 << " " << mp.getLR() << " " << mp2.getUD() << " " << elapsed << " " << m.x << " " << m.y << " " << m2.x << " " << m2.y << " " << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << " " << p3.x << " " << p3.y;
            client1++;
            client2++;
            client3++;
        }
        //  Send the message to all subscriber
         //zmq::message_t pub((void*)mes.str().c_str(), mes.str().size() + 1, NULL);
        zmq::message_t reply2(mes.str().size());
        memcpy(reply2.data(), mes.str().c_str(), mes.str().size());
        publisher.send(reply2);
        //std::cout << Pstr.str() << std::endl;
        // send each position of character and the position of moving platform
        // 3,mx,my,p1x,p1y,p2x,p2y,p3x,p3y here 3 stand for the number of client
        // 2,mx,my,p1x,p1y,p2x,p2y here 3 stand for the number of client
        // 1,mx,my,p1x,p1y here 3 stand for the number of client

        int subscribers = 0;
        while (subscribers < numClients) {

            //  - wait for synchronization request
            zmq::message_t yes(1);
            syncservice.recv(yes);

            //  - send synchronization reply
            s_send(syncservice, "");

            subscribers++;
        }
        zmq::message_t reply3(Pstr.str().size());
        memcpy(reply3.data(), Pstr.str().c_str(), Pstr.str().size());
        pub.send(reply3);

    }
    return 0;
}