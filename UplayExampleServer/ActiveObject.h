#pragma once
class ActiveObject
{
public:
	ActiveObject(void);
	~ActiveObject(void);

	void run();

private:
	void subscribe();
};

