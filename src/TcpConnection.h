/*
 * TcpConnection.h
 *
 *  Created on: Mar 10, 2016
 *      Author: fred
 */

#ifndef TCPCONNECTION_H_
#define TCPCONNECTION_H_
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

namespace Quadcopter {

using boost::asio::ip::tcp;

class TcpConnection: public boost::enable_shared_from_this<TcpConnection> {
public:
	typedef boost::shared_ptr<TcpConnection> pointer;

	static pointer create(boost::asio::io_service& io_service) {
		return pointer(new TcpConnection(io_service));
	}

	tcp::socket& socket();

	void start();

private:
	TcpConnection(boost::asio::io_service& io_service) :
			socket_(io_service) {
	}

	void handle_write(const boost::system::error_code& /*error*/,
			size_t /*bytes_transferred*/) {
	}

	tcp::socket socket_;
	std::string message_;
};
} /* namespace Quadcopter */

#endif /* TCPCONNECTION_H_ */
