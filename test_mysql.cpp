//
// Created by qiwentao on 22-11-30.
//
#include <mysql/jdbc.h>
#include <boost/json.hpp>
#include <memory>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include <boost/lexical_cast.hpp>

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
                                   // should be like: GET / HTTP/1.0
                                   string first_line = request_.substr(0, request_.find("\r\n"));
                                   cout << request_ << "\n";// process with request
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
    HttpServer(asio::io_context &io, const asio::ip::tcp::endpoint &ep) : io_(io), acceptor_(io, ep) {}

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

void build_http_server(){
    string ip_address = "172.16.32.86";
    int port = 8000;

    asio::io_context io;///io
    asio::ip::tcp::endpoint ep(asio::ip::make_address(ip_address), port);///ip:port

    HttpServer hs(io, ep);
    hs.Start();
    io.run();
}

int main() {
    build_http_server();
    return 0;
}


void mysql_conn(){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "123456789");

    stmt = con->createStatement();
    stmt->execute("USE test");
//    bool b = stmt->execute("select * from test_table");
    stmt->execute("DROP TABLE IF EXISTS test1");
    stmt->execute("CREATE TABLE test1(id INT, label CHAR(1))");
    stmt->execute("INSERT INTO test1(id, label) VALUES (1, 'a')");

    delete stmt;
    delete con;
}

std::string gedit_json(){
    std::vector<std::pair<std::string,std::string >>info;
    info.emplace_back("李四","哈囖");
    info.emplace_back("张三", "hello");

    boost::json::array info_ary;

    for (const auto &item: info){
        boost::json::object obj;
        obj["name"]=item.first;
        obj["msg"]=item.second;
        info_ary.push_back(obj);
    }

    boost::json::object info_json;
    info_json.emplace("info", info_ary);

    std::string ss = boost::json::serialize(info_json);
//    std::cout<<ss<<std::endl;
    return ss;
}

std::string build_response(){
    namespace http = boost::beast::http;
    http::response<http::string_body> resp;
    resp.set(boost::beast::http::field::server,"tiny-server");///处理请求时间
    resp.set(boost::beast::http::field::access_control_allow_origin,"*");///允许跨域访问
    resp.set(boost::beast::http::field::content_type,"application/json;charset=utf-8");///允许跨域访问

    resp.body()=gedit_json();///body内容

    resp.prepare_payload();///根据body长度，调整content-length
    resp.result(http::status::ok);///响应值200

    ///response转换成string
    const std::string &s_header = boost::lexical_cast<std::string>(resp.base());
    std::string s_body= resp.body();

//    std::cout<<s_header<<s_body<<std::endl;

//    std::cout<<resp.result();
    return s_header+s_body;
}

void build_socket(){
    int PORT=8000;
    int sockFd,newSockFd,valRead;
    int opt=1;
    char buffer[1024]={0};
    struct sockaddr_in addr;

    sockFd=socket(AF_INET,SOCK_STREAM,0);
    setsockopt(sockFd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr=INADDR_ANY;//    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    addr.sin_port= htons(PORT);
    int addrlen = sizeof(addr);

    bind(sockFd,(struct sockaddr*)&addr,addrlen);
    listen(sockFd,3);

    newSockFd=accept(sockFd,(struct sockaddr*)&addr,(socklen_t*)&addrlen);


    read(newSockFd,buffer,1024);
    std::cout<<buffer<<std::endl;

    std::string resp = build_response();
    send(newSockFd,resp.c_str(),resp.size(),0);


    std::cout<<"over over over over over!"<<std::endl;
}

void build_server(){
    using boost::asio::ip::tcp;
    std::cout << "server start==================>"<<std::endl;
    boost::asio::io_context io;
    tcp::acceptor acceptor(io,tcp::endpoint(tcp::v4(),8000));

    tcp::socket sock(io);

    acceptor.accept(sock);
    std::cout<<"client: "<<sock.remote_endpoint().address()<<std::endl;
    try {
        while (true){
            char buf[0xFF];
            sock.receive(boost::asio::buffer(buf));

            sock.send(boost::asio::buffer(buf));
        }
    }catch (std::exception & e) {
        std::cout<<e.what() << std::endl;
    }
    sock.close();
    ::system("pause");
}