//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: HTTP client, synchronous
//
//------------------------------------------------------------------------------

//[example_http_client

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

using namespace std;

class MyHttpConn
{
private: // 私有
    /* data */
public: // 公开
    MyHttpConn(int argc, char **argv);
    ~MyHttpConn();
};

// 类初始化
MyHttpConn ::MyHttpConn(int argc, char **argv)
{
    cout << "argv[0]         : " << argv[0] << endl;
    cout << "host    argv[1] : " << argv[1] << endl;
    cout << "port    argv[2] : " << argv[2] << endl;
    cout << "target  argv[3] : " << argv[3] << endl;
    cout << "version argv[4] : " << argv[4] << endl;
    cout << endl;

    int version = argc == 5 && !std::strcmp("1.0", argv[4]) ? 10 : 11;
    cout << "version:   :" << version << endl;
    cout << "传 参 数 量: " << argc << endl;
    cout << endl;
}
// 析构函数
MyHttpConn ::~MyHttpConn()
{
}

// 执行 HTTP GET 并打印响应
// ./http_sync_class_call 10.10.10.100 80 / 1.1
int main(int argc, char **argv)
{
    try
    {
        // 检查命令行参数。
        if (argc != 4 && argc != 5)
        {
            std::cerr << "Usage: http-client-sync <host> <port> <target> [<HTTP version: 1.0 or 1.1(default)>]\n"
                      << "Example:\n"
                      << "    http-client-sync www.example.com 80 /\n"
                      << "    http-client-sync www.example.com 80 / 1.0\n";
            return EXIT_FAILURE;
        }
        MyHttpConn myhttpconn(argc, argv);
        auto const host = argv[1];
        auto const port = argv[2];
        auto const target = argv[3];
        int version = argc == 5 && !std::strcmp("1.0", argv[4]) ? 10 : 11;

        // 所有 I/O 都需要 io_context
        net::io_context ioc;

        // 这些对象执行我们的 I/O
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        // 查域名
        auto const results = resolver.resolve(host, port);

        // 在我们从查找中获得的 IP 地址建立连接
        stream.connect(results);

        // 设置 HTTP GET 请求消息
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // 向远程主机发送 HTTP 请求
        http::write(stream, req);

        // 此缓冲区用于读取，必须持久化
        beast::flat_buffer buffer;

        // 声明一个容器来保存响应
        http::response<http::dynamic_body> res;

        // 接收 HTTP 响应
        http::read(stream, buffer, res);

        // 将消息写入标准输出
        std::cout << res << std::endl;

        // 优雅地关闭套接字
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected 有时会发生
        // 所以不要打扰报告它。
        //
        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};

        // 如果我们到达这里，则连接将正常关闭
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
