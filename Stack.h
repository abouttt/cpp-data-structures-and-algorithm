#pragma once

#include <deque>

template<typename T, typename Container = std::deque<T>>
class Stack
{
public:

	// constructor

	explicit Stack()
		: mContainer(Container())
	{}

	Stack(const Stack& other)
		: mContainer(other.mContainer)
	{}

	Stack(Stack&& other) noexcept
		: mContainer(std::move(other.mContainer))
	{}

	//

	// destructor

	~Stack() {}

	//

	// operator=

	Stack& operator=(const Stack& other)
	{
		mContainer = other.mContainer;
		return *this;
	}

	Stack& operator=(Stack&& other)
	{
		mContainer = std::move(other.mContainer);
		return *this;
	}

	//

	// Element access

	inline T& top()
	{
		return mContainer.back();
	}

	inline const T& top() const
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
		return mContainer.push_back(value);
	}

	inline void push(T&& value)
	{
		return mContainer.push_back(value);
	}

	inline void pop()
	{
		mContainer.pop_back();
	}

	inline void swap(Stack& other) noexcept
	{
		mContainer.swap(other.mContainer);
	}

private:
	Container mContainer;
};