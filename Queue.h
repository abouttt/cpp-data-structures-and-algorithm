#pragma once

#include <deque>

template<typename T, typename Container = std::deque<T>>
class Queue
{
public:

	// constructor

	explicit Queue()
		: mContainer()
	{}

	Queue(const Queue& other)
		: mContainer(other.mContainer)
	{}

	Queue(Queue&& other)
		: mContainer(std::move(other.mContainer))
	{}

	//

	// destructor

	~Queue() {}

	//

	// operator =

	Queue& operator=(const Queue& other)
	{
		mContainer = other.mContainer;
		return *this;
	}

	Queue& operator=(Queue&& other)
	{
		mContainer = std::move(other.mContainer);
		return *this;
	}

	//

	// Element access

	inline T& front()
	{
		return mContainer.front();
	}

	inline const T& front() const
	{
		return mContainer.front();
	}

	inline T& back()
	{
		return mContainer.back();
	}

	inline const T& back() const
	{
		return mContainer.back();
	}

	//

	// Capacity

	inline bool empty() const
	{
		return mContainer.empty();
	}

	inline size_t size() const
	{
		return mContainer.size();
	}

	//

	// Modifiers

	inline void push(const T& value)
	{
		mContainer.push_back(value);
	}

	inline void push(T&& value)
	{
		mContainer.push_back(std::move(value));
	}

	inline void pop()
	{
		mContainer.pop_front();
	}

	inline void swap(Queue& other) noexcept
	{
		mContainer.swap(other);
	}

private:
	Container mContainer;
};