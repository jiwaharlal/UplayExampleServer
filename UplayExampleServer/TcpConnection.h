#pragma once

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

class TcpServer;

class TcpConnection
	: public boost::enable_shared_from_this<TcpConnection>
{
public:
	typedef boost::shared_ptr<TcpConnection> Pointer;

	static Pointer						create(
											boost::asio::io_service&			io_service,
											TcpServer&							aParentServer);
	boost::asio::ip::tcp::socket&		socket();
	int									getId();
	void								start();
	void								handleRead(
											const boost::system::error_code&	e, 
											std::size_t							bytesTransferred);
private:
										TcpConnection(
											boost::asio::io_service&			io_service, 
											TcpServer&							aParentServer);
	void								handleWrite(
											const boost::system::error_code&, 
											size_t bytes_transferred);

	boost::asio::ip::tcp::socket		mySocket;
	std::string							message_;
	int									myId;
	static int							myPrevId;
	boost::array<char, 128>				myBuf;
	TcpServer&							myParentServer;
};

