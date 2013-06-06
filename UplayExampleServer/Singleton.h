#pragma once

//Inherit from Singleton this class to get a thread safe singleton GetInstance() method.

template<typename T>
void Delete(T* aInstance)
{
	aInstance->_DestroyInstance();
}

template <typename C>
class Singleton
{
public:
	static C&	GetInstance()
	{
		static volatile uint32 control = 0;

		for(;;) 
		{
			uint32 prev = AtomicCompareSwap(control, 1, 0);
			if (2 == prev) 
			{
				//Do nothing, the static pointers have been initialized
				break;
			}
			else if (0 == prev) 
			{			
				mySingletonInstance = new C();
				//					ourSingletonDeleter.RegisterSingletonToDelete(mySingletonInstance);
				control = 2;

				break;
			}
			else 
			{
				// Another thread is initializing the singleton:
				// must wait.
				MG_ASSERT(1 == prev, "State error.");
				SleepMS(1); // sleep 1 millisecond
			}
		}

		return *mySingletonInstance;
	}

	//NOT THREAD SAFE
	static void	_DestroyInstance()
	{
		//Not thread safe, this function is for debugging only
		C* instance = mySingletonInstance;
		mySingletonInstance = 0;
		delete instance;
	}

private:
	static C* mySingletonInstance;
};

template <typename C>
C* Singleton<C>::mySingletonInstance;

