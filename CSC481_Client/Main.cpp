#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Char.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "Timeline.h"
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <zmq.hpp>
#include <string>
#include "DeathZone.h"
#include"Sideboundary.h"
#include"EventManager.h"
#include"Event.h"
#include"EventHandler.h"
#include "ScriptManager.h"
#include "dukglue/dukglue.h"
std::condition_variable  _condition_variable;
std::condition_variable  _condition_variable1;
std::mutex _mutex;
bool focus = true;
bool lrflag;
bool upflag;
// the client id
int id = 0;
zmq::context_t context(1);
zmq::socket_t socket(context, ZMQ_REQ);
zmq::socket_t so(context, ZMQ_REQ);
zmq::socket_t subscriber(context, ZMQ_SUB);
zmq::socket_t sub(context, ZMQ_SUB);
sf::Vector2f mv;
sf::Vector2f mv2;
sf::Vector2f ch1;
sf::Vector2f ch2;
sf::Vector2f ch3;
sf::Vector2f spawn(10,500);
MovingPlatform mp;
MovingPlatform mp2;
float mpd;
float mpd2;
DeathZone dz;
Platform pf;
Platform pf2;
Platform pf3;
Sideboundary sb;
Sideboundary sb2;
Char c;
Char c2;
Char c3;
float elapsed;
bool sec = false;
bool thir = false;
EventManager manager;
EventHandler chah("char");
ScriptManager scripter = ScriptManager();


class MPThread
{
    Char* ch;
    sf::Clock* clock;
    Timeline* timeline;

public:
    MPThread( Char* ch)
    {
        this->ch = ch;
    }


    void run()
    {
        while (true) {
            try
            {

                {
                    std::unique_lock<std::mutex> lock(_mutex);
                    _condition_variable.wait(lock);
                    mp.setPosition(mv.x, mv.y);
                    mp2.setPosition(mv2.x, mv2.y);
                    mp.updateShape(-mpd, 0);
                    mp2.updateShape(-mpd2, 0);
                   // std::cout << "mp" << mp->getShape().getPosition().x << " " << mp->getShape().getPosition().y << std::endl;
                   // std::cout << "mp2" << mp2->getShape().getPosition().x << " " << mp2->getShape().getPosition().y << std::endl;
                    _condition_variable1.notify_all();
                    lock.unlock();

                }
            }
            catch (...)
            {
                std::cerr << "Thread caught exception." << std::endl;
            }
        }

    }
};

class CharThread
{
    Char* ch;
    sf::Clock* clock;
    Timeline* timeline;

public:
    CharThread( Char* ch, sf::Clock* clock)
    {
        this->ch = ch;
        this->clock = clock;
    }

    void run()
    {

        while (true) {
            try
            {
                std::unique_lock<std::mutex> lock(_mutex);
                _condition_variable1.wait(lock);
                // implement the landing on moving platform
                float time = clock->restart().asSeconds();
                //ch->focus = focus;
                ch->updateFocus(focus);
                //ch->inter = false;
                ch->updateInter(false);
                if (ch->detectCollision(&pf)) {
                    ch->updateInter(true);
                    ch->setPosition(ch->getShape().getPosition().x, ch->getShape().getPosition().y);
                    ch->setPre(sf::Vector2f(ch->getPre().x, ch->getPre().y));
                }
                Event e("MovingPlatformcollisionLR");
                if (ch->detectCollision(&mp)) {
                    e.setGo(&mp);
                    e.setPriority(1);
                    e.setTime(elapsed);
                    e.setLR(lrflag);
                    //std::cout << e.getType() << std::endl;
                    manager.regist("MovingPlatformcollisionLR", &chah);
                    manager.raise(&e);
                }
                Event e1("MovingPlatformcollisionUD");
                if (ch->detectCollision(&mp2)) {
                    e1.setGo(&mp2);
                    e1.setPriority(2);
                    e1.setUD(upflag);
                    e1.setTime(elapsed);
                    manager.regist("MovingPlatformcollisionUD", &chah);
                    manager.raise(&e1);


                }
                Event e2("Platformcollision");
                if (ch->detectCollision(&pf2)) {
                    e2.setGo(&pf);
                    e2.setPriority(3);
                    e2.setTime(elapsed);
                    manager.regist("Platformcollision", &chah);
                    manager.raise(&e2);
                }
                Event e3("Platformcollision");
                if (ch->detectCollision(&pf3)) {
                    e3.setGo(&pf3);
                    e3.setPriority(4);
                    e3.setTime(elapsed);
                    manager.regist("Platformcollision", &chah);
                    manager.raise(&e3);

                }
                Event e4("death");
                Event e5("spawn");
                if (ch->detectCollision(&dz)) {
                    e4.setTime(elapsed);
                    e4.setPriority(5);
                    manager.regist("death", &chah);
                    //manager.raise(&e4);
                    // run the script
                    // load the script
                    scripter.runRaiseScript("raiseEvent", 1, "death");
                    // handle the event
                     scripter.runHandleScript("handleE", 1, &chah);
                    e5.setTime(elapsed);
                    e5.setPriority(5);
                    manager.regist("spawn", &chah);
                    manager.raise(&e5);
                }
                
                float previous = ch->getShape().getPosition().x;
                //ch->moving(elapsed);
                //ch->updateMove(elapsed);
                Event ee("input");
                ee.setTime(elapsed);
                ee.setPriority(6);
                manager.regist("input", &chah);
                manager.raise(&ee);
                //scripter.runRaiseScript("handleE", 1, &manager);
                manager.handleEvents();
                float now = ch->getShape().getPosition().x;
                float delta = now - previous;
                if (ch->detectCollision(&sb) || ch->detectCollision(&sb2)) {
                    mpd += delta;
                    mpd2 += delta;
                    pf.updateShape(-delta, 0);
                    pf2.updateShape(-delta,0);
                    pf3.updateShape(-delta, 0);
                   // std::cout << pf2.getShape().getPosition().x << " " << pf2.getShape().getPosition().y << std::endl;
                    ch->setPosition(previous, ch->getShape().getPosition().y);

                }

                lock.unlock();
            }
            catch (...)
            {
                std::cerr << "Thread caught exception." << std::endl;
            }

        }
    }
};


void run_wrapper1(MPThread* fe)
{
    fe->run();
}

void run_wrapper2(CharThread* fe)
{
    fe->run();
}

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

int main()
{


    sf::RenderWindow window(sf::VideoMode(800, 800), "My window", sf::Style::Close);
    // setup heart
    sf::Texture texture;

    if (!texture.loadFromFile("heart.png"))
    {
        std::cout << "ERROR MESSAGE" << std::endl;
    }
    c.updateTexture(&texture);
    c.setPre(c.getShape().getPosition());
    c2.updateTexture(&texture);
    c3.updateTexture(&texture);
    // setup ground
    pf.setSize(10000, 300);
    pf.setPosition(-5000, 600);
    pf.updateColor(143, 188,143);
    // another two platform
    pf2.setSize(150, 20);
    pf2.setPosition(100, 400);
    pf2.updateColor(255, 255, 224);
    pf3.setSize(150, 20);
    pf3.setPosition(600, 400);
    pf3.updateColor(30, 144, 255);

    sb.setPosition(790,0);
    sb2.setPosition(0, 0);
    // setup ufo
    sf::Texture texture2;

    if (!texture2.loadFromFile("ufo.png"))
    {
        std::cout << "ERROR MESSAGE" << std::endl;
    }
    mp.updateTexture(&texture2);
    mp2.updateTexture(&texture2);
    // setup ufo
    sf::Texture texture3;


    sf::Clock cl1;
    sf::Clock cl2;
    // Create the original timeline, since we are using seconds, set tic to 1 to operate in second
    Timeline origin(NULL, 1, true, &cl1);
    // Create the timeline for main game loop
    Timeline tline(&origin, 1, false, &cl2);
    // the time for character jumping
    sf::Clock clock;
    float time = 0.0f;

    std::mutex m;
    std::condition_variable cv;
    MPThread t1( &c);
    CharThread t2( &c, &clock);
    std::thread first(run_wrapper1, &t1);
    std::thread second(run_wrapper2, &t2);

    // variables
    bool paused = false;
    bool unpaused = false;
    bool two = false;
    bool one = false;
    bool pointfive = false;
    // setup the client
    socket.connect("tcp://127.0.0.1:5555");
    subscriber.connect("tcp://127.0.0.1:5556");
    sub.connect("tcp://127.0.0.1:5557");
    so.connect("tcp://127.0.0.1:5558");
    const char* filter = "";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
    sub.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
    // sub.setsockopt(ZMQ_CONFLATE,1);

         //  Second, synchronize with publisher
    zmq::socket_t syncclient(context, ZMQ_REQ);
    syncclient.connect("tcp://127.0.0.1:5562");


    // Implement the client
    // the client has not conenct to the server
    // Raise the connect event in the client, and handle in the server
    Event ce("Join");
    ce.setPriority(1);

    zmq::message_t request(4);
    memcpy(request.data(), ce.getType().c_str(), 4);
    std::cout << "Sending join " << std::endl;
    socket.send(request);
    int idd;
    //  Get the reply about the client id, setup the client id
    zmq::message_t reply;
    socket.recv(&reply);
    std::istringstream iss(static_cast<char*>(reply.data()));
    iss >> idd;
    id = idd;
    std::cout << idd << std::endl;

    // Script
    dukglue_register_method(scripter.getContext(), &Platform::trans, "transform");
    //dukglue_register_method(scripter.getContext(), &EventHandler::onEvent, "onEvent");
    dukglue_register_constructor<Event,std::string>(scripter.getContext(), "Event");


    // manager
    chah.setCh(&c);
    manager.evenh(&chah);
    // run the program as long as the window is open
    while (window.isOpen())
    {
        int action = 0;
        // check window's event that were triggered since the last iteration of the loop 
        sf::Event event;
        while (window.pollEvent(event))
        {
            //close the window
            if (event.type == sf::Event::Closed) {
                //zmq_disconnect(socket, "tcp://127.0.0.1:5555");
                //zmq_disconnect(subscriber, "tcp://127.0.0.1:5556");
                //zmq_disconnect(sub, "tcp://127.0.0.1:5557");
                //zmq_disconnect(so, "tcp://127.0.0.1:5558");
                //zmq_disconnect(syncclient, "tcp://127.0.0.1:5562");
                window.close();
            }
            if (event.type == sf::Event::GainedFocus) focus = true;
            if (event.type == sf::Event::LostFocus) focus = false;
            //           std::cout << focus << std::endl;
        }
           
        // clear the window with black color
        window.clear(sf::Color::Black);
        // load the script
        scripter.loadScript("script.js");
        if (focus) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                two = true;
            }

            if (two == true && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                tline.changeTic(0.5);
                //mp.Ticchanged = true;
                
                two = false;
                action = 5;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                pointfive = true;
            }

            if (pointfive == true && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                tline.changeTic(2);
               // mp.Ticchanged = true;
                pointfive = false;
                action = 4;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                one = true;
            }

            if (one == true && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                tline.changeTic(1);
                //mp.Ticchanged = true;
                one = false;
                action = 3;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                paused = true;
            }
            if (paused == true && !sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                paused = false;
                tline.paused();
                action = 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
                unpaused = true;
            }
            if (unpaused == true && !sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
                unpaused = false;
                tline.unpaused();
                action = 2;
            }
        }

        // 1 : p, 2 : u, 3 : 1x, 4 : 2x, 5: 0.5x
        // sending the character position to the server
        std::stringstream connect;

        if (action != 0) {
            connect << id << " " << c.getPre().x << " " << c.getPre().y << " " << action;
        }
        else {
            connect << id << " " << c.getPre().x << " " << c.getPre().y;
        }

        zmq::message_t request(connect.str().size());

        memcpy(request.data(), connect.str().c_str(), connect.str().size());
        socket.send(request);

        //  Get the reply about the reply
        zmq::message_t reply;
        socket.recv(&reply);
        //           std::cout << "get " << std::endl;



               // Get the subscribe message
        zmq::message_t update;
        subscriber.recv(&update);
        std::string up = std::string(static_cast<char*>(update.data()), update.size());
     //   std::cout << up << std::endl;
        // Get the Position message from publisher 
                //  - send a synchronization request
        s_send(syncclient, "");

        //  - wait for synchronization reply
        zmq::message_t yes(1);
        syncclient.recv(yes);

        zmq::message_t update2;
        sub.recv(&update2);
        //       std::cout << "get haha" << std::endl;
        std::string up2 = std::string(static_cast<char*>(update2.data()), update2.size());
        std::vector<float> array;
        std::istringstream iss(up2);
        std::copy(std::istream_iterator<float>(iss),
            std::istream_iterator<float>(),
            std::back_inserter(array));
        //      std::cout << up2.size() << std::endl;
        //            Pstr << 1 << " " << mp.getLR() << " " << mp2.getUD() << " " << elapsed << " " << m.x << " " << m.y << " " << m2.x << " " << m2.y << " " << p1.x << " " << p1.y;
        mv.x = array.at(4);
        mv.y = array.at(5);
        mv2.x = array.at(6);
        mv2.y = array.at(7);
        ch1.x = array.at(8);
        ch1.y = array.at(9);
        elapsed = array.at(3);
        lrflag = array.at(1);
        upflag = array.at(2);

        // display the other character 
             // display the other character 
        if (array.at(0) == 2) {
            // two character 
            if (id == 1) {
                // two character
                c2.setPosition(array.at(10), array.at(11));
            }
            else if (id == 2) {
                c2.setPosition(array.at(8), array.at(9));
            }

        }
        if (array.at(0) == 3) {
            if (id == 1) {
                c2.setPosition(array.at(10), array.at(11));

                c3.setPosition(array.at(12), array.at(13));
            }
            else if (id == 2) {
                c2.setPosition(array.at(8), array.at(9));
                c3.setPosition(array.at(12), array.at(13));
                //              std::cout << array.at(9) << " " << array.at(10);
            }
            else if (id == 3) {
                c2.setPosition(array.at(8), array.at(9));

                c3.setPosition(array.at(10), array.at(11));
            }
        }

        _condition_variable.notify_all();
        float dl = c.getShape().getPosition().x - c.getPre().x;
        c2.updateShape(dl, 0);
        c3.updateShape(dl, 0);
        // display the other character 
        if (array.at(0) == 2) {
                window.draw(c2.getShape());

        }else if (array.at(0) == 3) {
                window.draw(c2.getShape());
                window.draw(c3.getShape());
        }
        // run the script
        scripter.runScript("trans", 1, &pf2);

        window.draw(c.getShape());
        window.draw(pf.getShape());
        window.draw(pf2.getShape());
        window.draw(pf3.getShape());
        window.draw(mp.getShape());
        window.draw(mp2.getShape());



        window.display();



    }
    while (true) {
        std::stringstream connect;
        connect << id << " " << c.getPre().x << " " << c.getPre().y;
        zmq::message_t request(connect.str().size());

        memcpy(request.data(), connect.str().c_str(), connect.str().size());
        socket.send(request);

        //  Get the reply about the reply
        zmq::message_t reply;
        socket.recv(&reply);

        // Get the subscribe message
        zmq::message_t update;
        subscriber.recv(&update);
        std::string up = std::string(static_cast<char*>(update.data()), update.size());
        //   std::cout << up << std::endl;
           // Get the Position message from publisher 
                   //  - send a synchronization request
        s_send(syncclient, "");

        //  - wait for synchronization reply
        zmq::message_t yes(1);
        syncclient.recv(yes);

        zmq::message_t update2;
        sub.recv(&update2);


    }
    first.join();
    second.join();
    return 0;
}

