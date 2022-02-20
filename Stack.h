#pragma once

#include "Vector.h"

template<typename T>
class Stack
{
public:

	// constructor

	explicit Stack()
		: mData(Vector<T>())
	{}

	Stack(const Stack& other)
		: mData(other.mData)
	{}

	Stack(Stack&& other) noexcept
		: mData(std::move(other.mData))
	{}

	//

	// destructor

	~Stack() {}

	//

	// operator=

	Stack& operator=(const Stack& other)
	{
		mData = other.mData;
		return *this;
	}

	Stack& operator=(Stack&& other)
	{
		mData = std::move(other.mData);
		return *this;
	}

	//

	// Element access

	inline T& top()
	{
		return mData.back();
	}

	inline const T& top() const
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
		mData.pop_back();
	}

	inline void swap(Stack& other) noexcept
	{
		mData.size(other);
	}

private:
	Vector<T> mData;
};