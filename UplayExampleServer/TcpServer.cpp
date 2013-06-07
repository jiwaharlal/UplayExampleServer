#include "TcpServer.h"

#include <boost/bind.hpp>
#include <boost/asio.hpp>

namespace ip = boost::asio::ip;

TcpServer::TcpServer(boost::asio::io_service& io_service)
	: myAcceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), 13))
{
	startAccept();
}

void TcpServer::closeConnection(TcpConnection::Pointer aConnection)
{
	std::cout << "Closing connection" << std::endl;
	for (auto it = myConnections.begin(); it != myConnections.end(); ++it)
	{
		if (*it == aConnection)
		{
			myConnections.erase(it);
			break;
		}
	}
}

void TcpServer::startAccept()
{
	TcpConnection::Pointer newConnection =
		TcpConnection::create(myAcceptor.get_io_service(), *this);

	myAcceptor.async_accept(newConnection->socket(),
		boost::bind(&TcpServer::handleAccept, this, newConnection,
		boost::asio::placeholders::error));
}

void TcpServer::handleAccept(TcpConnection::Pointer aNewConnection,
	const boost::system::error_code& aError)
{
	if (!aError)
	{
		aNewConnection->start();
		myConnections.push_back(aNewConnection);
	}

	startAccept();
}
