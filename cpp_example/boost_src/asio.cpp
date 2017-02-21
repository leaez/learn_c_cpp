#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <thread>

using namespace boost::asio;



void test_steady_timer()
{
  io_service ioservice;

  steady_timer timer1{ioservice, std::chrono::seconds{3}};
  timer1.async_wait([](const boost::system::error_code &ec)
    { std::cout << "3 sec\n"; });

  steady_timer timer2{ioservice, std::chrono::seconds{4}};
  timer2.async_wait([](const boost::system::error_code &ec)
    { std::cout << "4 sec\n"; });

  ioservice.run();
}

//https://theboostcpplibraries.com/boost.asio-network-programming
/** tcp  */ 
#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <ctime>
#include <array>
#include <iostream>


using namespace boost::asio;
using namespace boost::asio::ip;

io_service ioservice;
tcp::endpoint tcp_endpoint{tcp::v4(), 2014};
tcp::acceptor tcp_acceptor{ioservice, tcp_endpoint};
tcp::socket tcp_socket{ioservice};
std::string data;

void write_handler(const boost::system::error_code &ec,
  std::size_t bytes_transferred)
{
  if (!ec)
    tcp_socket.shutdown(tcp::socket::shutdown_send);
  std::cout << "+++++++ser one send+++++++\n";
}

void accept_handler(const boost::system::error_code &ec)
{
  if (!ec)
  {
    std::time_t now = std::time(nullptr);
    //data = std::ctime(&now);
    data = "===========";
    for(int i= 0;i<=1; i++){
        sleep(1);
    async_write(tcp_socket, buffer(data), write_handler);}
    std::cout << "+++++++ser accept ++++++\n";
  }
}

/** client */ 
using namespace boost::asio;
using namespace boost::asio::ip;

tcp::resolver resolv{ioservice};
std::array<char, 4096> bytes;

void read_handler(const boost::system::error_code &ec,
  std::size_t bytes_transferred)
{
  if (!ec)
  {
    //  for(int i=0;i <= 5; i++){
    std::cout.write(bytes.data(), bytes_transferred);
    tcp_socket.async_read_some(buffer(bytes), read_handler);
    //std::cout << "+++++++cli read ++++++\n";
    //sleep(1);
      }
  }
}

void connect_handler(const boost::system::error_code &ec)
{
  if (!ec)
  {
    std::string r = 
      "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
    write(tcp_socket, buffer(r));
    tcp_socket.async_read_some(buffer(bytes), read_handler);
    std::cout << "+++++++cli con read ++++++\n";
  }
}

void resolve_handler(const boost::system::error_code &ec,
  tcp::resolver::iterator it)
{
  if (!ec)
    tcp_socket.async_connect(*it, connect_handler);
}


    /** client */ 
int client(){
    tcp::resolver::query q{"theboostcpplibraries.com", "80"};
    resolv.async_resolve(q, resolve_handler);
    ioservice.run();
}
    /** server  */ 
int server(){ 
    tcp_acceptor.listen();
    tcp_acceptor.async_accept(tcp_socket, accept_handler);
    ioservice.run();
}
int main()
{
    
    test_steady_timer();
    printf("-----------\n");

    std::thread t1{client};
    //std::thread t2{server};
    t1.join();
    //t2.join();


    return 0;
}

