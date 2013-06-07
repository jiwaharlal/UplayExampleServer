#pragma once

#include <boost/asio.hpp>
#include <list>

#include "TcpConnection.h"

class TcpServer
{
public:
				TcpServer(
					boost::asio::io_service&			io_service);

	void		closeConnection(
					TcpConnection::Pointer				aConnection);
private:
	void		startAccept();
	void		handleAccept(
					TcpConnection::Pointer				aNewConnection,
					const boost::system::error_code&	aError);

	boost::asio::ip::tcp::acceptor			myAcceptor;
	std::list<TcpConnection::Pointer>		myConnections;
};

