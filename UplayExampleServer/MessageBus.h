#pragma once

class MessageBus
{
public:
	static MessageBus&			instance();

	void						subscribe(Message, Function);

	void						post(Message);
private:
								MessageBus(void);
								~MessageBus(void);
};

