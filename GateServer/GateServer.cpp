﻿#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "CServer.h"
#include "ConfigMgr.h"

int main()
{
    ConfigMgr gCfgMgr;
    std::string gate_port_str = gCfgMgr["GateServer"]["Port"];
    unsigned short gate_port = atoi(gate_port_str.c_str());


    try {

        unsigned short port = static_cast<unsigned short>(8080);
        net::io_context ioc;
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);

        signals.async_wait(
            [&ioc](const boost::system::error_code& ec, int signal_number) {
                if (ec) {
                    return;
                }
                else {
                    ioc.stop();
                }
            }
        );

        std::make_shared<CServer>(ioc, port)->Start();
        ioc.run();

    }
    catch (std::exception& e) {
        std::cerr << "Error is : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}