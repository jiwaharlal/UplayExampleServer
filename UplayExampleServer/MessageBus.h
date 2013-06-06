#pragma once

#include <boost/function.hpp>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

class MessageBase0
{
public:
    std::string getName()
    {
        return typeid(*this).name();
    }
};

template <class ConcreteMessage>
class MessageBase: public MessageBase0
{
};

class DispatcherBase
{
public:
	virtual void call(MessageBase0&) = 0;
};

template <class MessageClass>
class Dispatcher: public DispatcherBase
{
public:
	Dispatcher(boost::function<void(MessageClass&)> aFunction)
		: myFunction(aFunction)
	{
	}

	virtual void call(MessageBase0& aMessage)
	{
		myFunction(dynamic_cast<MessageClass&>(aMessage));
	}
};

class MessageBus
{
private:
	typedef std::vector<boost::shared_ptr<DispatcherBase> > DispatcherStorage;
	typedef std::map<std::string, DispatcherStorage> SubscriberMap;
public:
	static MessageBus&			instance();

	template <class MessageClass>
	void subscribe(MessageClass& aMessage, boost::function<void(MessageClass&)> aFunction)
	{
		boost::shared_ptr<DispatcherBase> dispatcher = new Dispatcher<MessageClass>(aFunction);
		std::string name = aMessage.getName();
		mySubscriberMap[name].push_back(dispatcher);
	}

	void post(MessageBase0& aMessage)
	{
		std::string name = aMessage.getName();
		auto it = mySubscriberMap.find(name);
		if ( it == mySubscriberMap.end() )
		{
			return;
		}
		DispatcherStorage& dispatchers = it->second;
		for (auto it = dispatchers.begin(); it != dispatchers.end(); ++it)
		{
			(*it)->call(aMessage);
		}
	}
private:
								MessageBus(void);
								~MessageBus(void);

	SubscriberMap mySubscriberMap;
};

