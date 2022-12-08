//
// Created by qiwentao on 22-12-5.
//

//#include "server.h"
#include <iostream>
#include <string>
#include <memory>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;

class HttpConnection : public std::enable_shared_from_this<HttpConnection> {
public:
    explicit HttpConnection(asio::io_context &io) : socket_(io) {}

    void Start() {
        auto p = shared_from_this();
        asio::async_read_until(socket_, asio::dynamic_buffer(request_), "\r\n\r\n",
                               [p, this](const error_code &err, size_t len) {
                                   if (err) {
                                       cout << "recv err:" << err.message() << "\n";
                                       return;
                                   }
                                   string first_line = request_.substr(0, request_.find(
                                           "\r\n")); // should be like: GET / HTTP/1.0
                                   cout << first_line << "\n";// process with request
                                   // ...

                                   char str[] = "HTTP/1.0 200 OK\r\n\r\n<html>hello from http server</html>";
                                   asio::async_write(socket_, asio::buffer(str),
                                                     [p, this](const error_code &err, size_t len) {
                                                         socket_.close();
                                                     });
                               });
    }

    asio::ip::tcp::socket &Socket() { return socket_; }

private:
    asio::ip::tcp::socket socket_;
    string request_;
};

class HttpServer {
public:
    HttpServer(asio::io_context &io, const asio::ip::tcp::endpoint& ep) : io_(io), acceptor_(io, ep) {}

    void Start() {
        auto p = std::make_shared<HttpConnection>(io_);
        acceptor_.async_accept(p->Socket(), [p, this](const error_code &err) {
            if (err) {
                cout << "accept err:" << err.message() << "\n";
                return;
            }
            p->Start();
            Start();
        });
    }

private:
    asio::io_context &io_;
    asio::ip::tcp::acceptor acceptor_;
};

int main() {
    string ip_address = "172.16.32.86";
    int port = 8000;

    asio::io_context io;
    asio::ip::tcp::endpoint ep(asio::ip::make_address(ip_address), port);

    HttpServer hs(io, ep);
    hs.Start();
    io.run();

    return 0;
}
