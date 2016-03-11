/*
 * TcpServer.cpp
 *
 *  Created on: Mar 10, 2016
 *      Author: fred
 */

#include "TcpServer.h"
#include "Constants.h"
namespace Quadcopter {

TcpServer::TcpServer(boost::asio::io_service& io_service)  :
    acceptor_(io_service, tcp::endpoint(tcp::v4(), TCP_SERVER_PORT)) {
    start_accept();
}

TcpServer::~TcpServer() {
}

void TcpServer::start_accept()  {
	TcpConnection::pointer new_connection = TcpConnection::create(
			acceptor_.get_io_service());
	acceptor_.async_accept(new_connection->socket(),
			boost::bind(&TcpServer::handle_accept, this, new_connection,
					boost::asio::placeholders::error));
}

void TcpServer::handle_accept(TcpConnection::pointer new_connection,
		const boost::system::error_code& error)  {
	if (!error) {
		new_connection->start();
	}
	start_accept();
}

}
