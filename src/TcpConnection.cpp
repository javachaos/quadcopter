/*
 * TcpConnection.cpp
 *
 *  Created on: Mar 10, 2016
 *      Author: fred
 */

#include "TcpConnection.h"

namespace Quadcopter {

void TcpConnection::start() {
	boost::asio::async_write(socket_, boost::asio::buffer(message_),
	                boost::bind(&TcpConnection::handle_write, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
}

tcp::socket& TcpConnection::socket() {
	return socket_;
}

} /* namespace Quadcopter */
