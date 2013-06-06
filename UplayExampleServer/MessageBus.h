#pragma once

class MessageBus
{
public:
	static MessageBus&			instance();

	void						subscribe(Message, Function);

	void						dispatch(Message);
private:
								MessageBus(void);
								~MessageBus(void);

	typedef boost::function<void(MessageBase&)>
	std::map<std::vector<boost::function<void(MessageBase)> > > myRecieversMap;
};

