#include "TcpConnection.h"

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include "TcpServer.h"

int TcpConnection::myPrevId = 0;

namespace ip = boost::asio::ip;

TcpConnection::Pointer 
TcpConnection::create(
	boost::asio::io_service&	io_service, 
	TcpServer&					aParentServer)
{
	return TcpConnection::Pointer(new TcpConnection(io_service, aParentServer));
}

ip::tcp::socket& 
TcpConnection::socket()
{
	return mySocket;
}

int
TcpConnection::getId()
{
	return myId;
}

void
TcpConnection::start()
{
	mySocket.async_read_some(boost::asio::buffer(myBuf),
							boost::bind(&TcpConnection::handleRead, 
										shared_from_this(),
										boost::asio::placeholders::error,
										boost::asio::placeholders::bytes_transferred));
}

void
TcpConnection::handleRead(
	const boost::system::error_code&		e, 
	std::size_t								bytesTransferred)
{
	if (!e)
	{
		std::string message(myBuf.data(), myBuf.data() + bytesTransferred);
		std::cout << message << std::endl;
		//boost::array<char, 16> buf;
		mySocket.write_some(boost::asio::buffer(boost::lexical_cast<std::string>(message.length())));
		if (message == "disconnect")
		{
			std::cout << "Disconnecting" << std::endl;
			myParentServer.closeConnection(shared_from_this());
				
			return;
		}
		else
		{
			start();
		}
	}
	else
	{
		std::cout << "Error: " << e.message() << std::endl;
		myParentServer.closeConnection(shared_from_this());
	}
}

TcpConnection::TcpConnection(
	boost::asio::io_service&		io_service,
	TcpServer&						aParentServer)
	: mySocket(io_service)
	, myId(myPrevId)
	, myParentServer(aParentServer)
{
	myPrevId++;
}
