#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <thread>
#include <zmq.hpp>
#include <unistd.h>
int main(int argc, char *argv[]) {
  // "You should create and use exactly one context in your process."
  zmq::context_t context(3);

  // the main thread runs the publisher and sends messages periodically
  zmq::socket_t publisher(context, ZMQ_PUB);
  // for the inproc transport, we MUST bind on the publisher before we can
  // connect any subscribers
  std::string transport("inproc://mytransport");
  //std::string transport("tcp://*:5555");
  //publisher.bind("tcp://192.168.1.5:8888");
 // publisher.bind("tcp://127.0.0.1:9002");
  publisher.bind(transport);
  //subscriber.connect(transport);
  //publisher.connect(transport);
  //publisher.bind("inproc://mytransport");
usleep(1);
#if 1
  // in a seperate thread, poll the socket until a message is ready. when a
  // message is ready, receive it, and print it out. then, start over.
  //
  // 1. create the subscriber socket
  zmq::socket_t subscriber(context, ZMQ_SUB);
  // 2. we need to connect to the transport
  subscriber.connect(transport);
  //subscriber.bind(transport);
  // 3. set the socket options such that we receive all messages. we can set
  // filters here. this "filter" ("" and 0) subscribes to all messages.
  subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

  size_t nmsg = 10;
  size_t nrx = 0;
  // to use zmq_poll correctly, we construct this vector of pollitems
  std::vector<zmq::pollitem_t> p = {{ static_cast<void*>(subscriber), 0, ZMQ_POLLIN, 0}};
  //{ static_cast<void*>(receiver), 0, ZMQ_POLLIN, 0 },
  // the subscriber thread runs until it received all of the messages
  std::thread subs_thread([&subscriber, &p, &nrx, &nmsg]() {
    while (true) {
      zmq::message_t rx_msg;
      // when timeout (the third argument here) is -1,
      // then block until ready to receive
      zmq::poll(p.data(), 1, -1);
      if (p[0].revents & ZMQ_POLLIN) {
        // received something on the first (only) socket
        subscriber.recv(&rx_msg);
        std::string rx_str;
        rx_str.assign(static_cast<char *>(rx_msg.data()), rx_msg.size());
        std::cout << "Received: " << rx_str << std::endl; 
        if (++nrx == nmsg)
          break;
      }
    }
  });

  // let's publish a few "Hello" messages
  for (size_t i = 0; i < nmsg; ++i) {
    // create a message
    std::stringstream s;
    s << "Hello " << i;
    auto msg = s.str();
    zmq::message_t message(msg.length());
    memcpy(message.data(), msg.c_str(), msg.length());
    publisher.send(message);
  }
  subs_thread.join();
#endif
  return 0;
}
