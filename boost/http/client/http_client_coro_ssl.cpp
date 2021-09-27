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
// Example: HTTP SSL client, coroutine
//
//------------------------------------------------------------------------------

#include "example/common/root_certificates.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/spawn.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// 报告失败
void fail(beast::error_code ec, char const *what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// 执行 HTTP GET 并打印响应
void do_session(
    std::string const &host,
    std::string const &port,
    std::string const &target,
    int version,
    net::io_context &ioc,
    ssl::context &ctx,
    net::yield_context yield)
{
    beast::error_code ec;

    // 这些对象执行我们的 I/O
    tcp::resolver resolver(ioc);
    beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

    // 设置 SNI 主机名（许多主机需要这个才能成功握手）
    if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
    {
        ec.assign(static_cast<int>(::ERR_get_error()), net::error::get_ssl_category());
        std::cerr << ec.message() << "\n";
        return;
    }

    // 查域名
    auto const results = resolver.async_resolve(host, port, yield[ec]);
    if (ec)
        return fail(ec, "resolve");

    // 设置超时。
    beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(30));

    // 在我们从查找中获得的 IP 地址建立连接
    get_lowest_layer(stream).async_connect(results, yield[ec]);
    if (ec)
        return fail(ec, "connect");

    // 设置超时。
    beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(30));

    // 执行 SSL 握手
    stream.async_handshake(ssl::stream_base::client, yield[ec]);
    if (ec)
        return fail(ec, "handshake");

    // 设置 HTTP GET 请求消息
    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // 设置超时。
    beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(30));

    // 向远程主机发送 HTTP 请求
    http::async_write(stream, req, yield[ec]);
    if (ec)
        return fail(ec, "write");

    // 此缓冲区用于读取，必须持久化
    beast::flat_buffer b;

    // 声明一个容器来保存响应
    http::response<http::dynamic_body> res;

    // 接收 HTTP 响应
    http::async_read(stream, b, res, yield[ec]);
    if (ec)
        return fail(ec, "read");

    // 将消息写入标准输出
    std::cout << res << std::endl;

    // 设置超时。
    beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(30));

    // 优雅地关闭流
    stream.async_shutdown(yield[ec]);
    if (ec == net::error::eof)
    {
        // 理由：
        // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
        ec = {};
    }
    if (ec)
        return fail(ec, "shutdown");

    // 如果我们到达这里，则连接将正常关闭
}

//------------------------------------------------------------------------------

int main(int argc, char **argv)
{
    // 检查命令行参数
    if (argc != 4 && argc != 5)
    {
        std::cerr << "Usage: http-client-coro-ssl <host> <port> <target> [<HTTP version: 1.0 or 1.1(default)>]\n"
                  << "Example:\n"
                  << "    http-client-coro-ssl www.example.com 443 /\n"
                  << "    http-client-coro-ssl www.example.com 443 / 1.0\n";
        return EXIT_FAILURE;
    }
    auto const host = argv[1];
    auto const port = argv[2];
    auto const target = argv[3];
    int version = argc == 5 && !std::strcmp("1.0", argv[4]) ? 10 : 11;

    // 所有 I/O 都需要 io_context 上下文
    net::io_context ioc;

    // SSL 上下文是必需的，并持有证书, tls版本
    ssl::context ctx{ssl::context::tlsv12_client};

    // 验证本地服务器根证书
    load_root_certificates(ctx);

    // 验证远程服务器的证书
    ctx.set_verify_mode(ssl::verify_peer);

    // 启动异步操作
    boost::asio::spawn(ioc, std::bind(
                                &do_session,
                                std::string(host),
                                std::string(port),
                                std::string(target),
                                version,
                                std::ref(ioc),
                                std::ref(ctx),
                                std::placeholders::_1));

    // 运行 I/O 服务。 调用返回
    // 获取操作完成。
    ioc.run();

    return EXIT_SUCCESS;
}
