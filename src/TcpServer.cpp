/*
 * TcpServer.cpp
 *
 *  Created on: Mar 10, 2016
 *      Author: fred
 */

#include "Constants.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>
#include <boost/serialization/vector.hpp>
#include "TcpConnection.cpp"
#include "Blackboard.h"
#include "Device.h"
#include "Log.h"

using namespace std;
namespace Quadcopter {
/// Serves system information to any client that connects to it.
class TcpServer: Device {
public:
	/// Constructor opens the acceptor and starts waiting for the first incoming
	/// connection.
	TcpServer(boost::asio::io_service& io_service, unsigned short port) :
                  Device(ID_TCPCLIENT, "TcpServer"), acceptor_(io_service,
                  boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
            try {
                io_service.run();
            } catch (exception& e) {
                clog << kLogNotice << e.what() << endl;
                cerr << e.what() << endl;
            }
	}

	void init(Blackboard *bb) {
		// Create the data to be sent to each client.
		bb->addMessage(ID_TCPCLIENT, ID_COMM, "started");
		Blackboard::BBMessage m = bb->checkForMessage(ID_TCPCLIENT);
		msgs_.push_back(m);
		// Start an accept operation for a new connection.
		connection_ptr new_conn(new TcpConnection(acceptor_.get_io_service()));
		acceptor_.async_accept(new_conn->socket(),
				boost::bind(&TcpServer::handle_accept, this,
						boost::asio::placeholders::error, new_conn));
	}
	void update(Blackboard* bb) {
		Blackboard::BBMessage m = bb->checkForMessage(ID_TCPCLIENT);
		msgs_.push_back(m);
	}

	/// Handle completion of a accept operation.
	void handle_accept(const boost::system::error_code& e,
			connection_ptr conn) {
		if (!e) {
			// Successfully accepted a new connection. Send the list of msgs to the
			// client. The connection::async_write() function will automatically
			// serialize the data structure for us.
			conn->async_write(msgs_,
					boost::bind(&TcpServer::handle_write, this,
							boost::asio::placeholders::error, conn));
		}

		// Start an accept operation for a new connection.
		connection_ptr new_conn(new TcpConnection(acceptor_.get_io_service()));
		acceptor_.async_accept(new_conn->socket(),
				boost::bind(&TcpServer::handle_accept, this,
						boost::asio::placeholders::error, new_conn));
	}

	/// Handle completion of a write operation.
	void handle_write(const boost::system::error_code& e, connection_ptr conn) {
		// Nothing to do. The socket will be closed automatically when the last
		// reference to the connection object goes away.
	}

private:
	/// The acceptor object used to accept incoming socket connections.
	boost::asio::ip::tcp::acceptor acceptor_;

	/// The data to be sent to each client.
	std::vector<Blackboard::BBMessage> msgs_;
};

}
