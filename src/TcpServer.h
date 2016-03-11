/*
 * TcpServer.h
 *
 *  Created on: Mar 10, 2016
 *      Author: fred
 */

#ifndef SRC_TCPSERVER_H_
#define SRC_TCPSERVER_H_

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "TcpConnection.h"
using namespace std;

namespace Quadcopter {
using boost::asio::ip::tcp;

class TcpServer {
public:
	TcpServer(boost::asio::io_service& io_service);
	virtual ~TcpServer();

private:
	void start_accept();
	void handle_accept(TcpConnection::pointer new_connection,
			const boost::system::error_code& error);
	tcp::acceptor acceptor_;
};

} /* namespace Quadcopter */

#endif /* SRC_TCPSERVER_H_ */
