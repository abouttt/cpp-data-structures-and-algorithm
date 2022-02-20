#pragma once

#include "List.h"

template<typename T>
class Queue
{
public:

	// constructor

	explicit Queue()
		: mData(List<T>())
	{}

	Queue(const Queue& other)
		: mData(other.mData)
	{}

	Queue(Queue&& other)
		: mData(std::move(other.mData))
	{}

	//

	// destructor

	~Queue() {}

	//

	// operator =

	Queue& operator=(const Queue& other)
	{
		mData = other.mData;
		return *this;
	}

	Queue& operator=(Queue&& other)
	{
		mData = std::move(other.mData);
		return *this;
	}

	//

	// Element access

	inline T& front()
	{
		return mData.front();
	}

	inline const T& front() const
	{
		return mData.front();
	}

	inline T& back()
	{
		return mData.back();
	}

	inline const T& back() const
	{
		return mData.back();
	}

	//

	// Capacity

	inline bool empty() const
	{
		return mData.empty();
	}

	inline size_t size() const
	{
		return mData.size();
	}

	//

	// Modifiers

	inline void push(const T& value)
	{
		mData.push_back(value);
	}

	inline void push(T&& value)
	{
		mData.push_back(value);
	}

	inline void pop()
	{
		mData.pop_front();
	}

	inline void swap(Queue& other) noexcept
	{
		mData.swap(other);
	}

private:
	List<T> mData;
};