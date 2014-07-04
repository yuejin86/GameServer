#ifndef LOCKEDQUEUE_H
#define LOCKEDQUEUE_H
#include <deque>
#include <boost/thread/shared_lock_guard.hpp>

template <class T, class LockType, typename StorageType = std::deque<T> >
class LockedQueue
{
private:
	//! Lock access to the queue.
	LockType _lock;

	//! Storage backing the queue.
	StorageType _queue;

	//! Cancellation flag.
	/*volatile*/ bool _canceled;

public:

	//! Create a LockedQueue.
	LockedQueue()
		: _canceled(false)
	{
	}

	//! Destroy a LockedQueue.
	virtual ~LockedQueue()
	{
	}

	//! Adds an item to the queue.
	void add(const T& item)
	{
		shared_lock_guard<LockType> g(this->_lock);
		_queue.push_back(item);
	}

	//! Gets the next result in the queue, if any.
	bool next(T& result)
	{
		shared_lock_guard<LockType> g(this->_lock);

		if (_queue.empty())
			return false;

		result = _queue.front();
		_queue.pop_front();

		return true;
	}

	template<class Checker>
	bool next(T& result, Checker& check)
	{
		shared_lock_guard<LockType> g(this->_lock);

		if (_queue.empty())
			return false;

		result = _queue.front();
		if (!check.Process(result))
			return false;

		_queue.pop_front();
		return true;
	}

	//! Cancels the queue.
	void cancel()
	{
		shared_lock_guard<LockType> g(this->_lock);
		_canceled = true;
	}

	//! Checks if the queue is cancelled.
	bool cancelled()
	{
		shared_lock_guard<LockType> g(this->_lock);
		return _canceled;
	}

	///! Checks if we're empty or not with locks held
	bool empty()
	{
		shared_lock_guard<LockType> g(this->_lock);
		return _queue.empty();
	} 
};

#endif