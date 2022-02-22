#pragma once

#include <vector>

template<typename T, typename Container = std::vector<T>, typename Compare = std::less<T>>
class PriorityQueue
{
public:

	// constructor

	PriorityQueue() = default;

	explicit PriorityQueue(const Compare& compare)
		: mContainer()
		, mCompare(compare)
	{}

	PriorityQueue(const Compare& compare, const Container& cont)
		: mContainer(cont)
		, mCompare(compare)
	{}

	PriorityQueue(const Compare& compare, Container&& cont)
		: mContainer(std::move(cont))
		, mCompare(compare)
	{}

	PriorityQueue(const PriorityQueue& other)
		: mContainer(other.mContainer)
		, mCompare(other.mCompare)
	{}

	PriorityQueue(PriorityQueue&& other) noexcept
		: mContainer(std::move(other.mContainer))
		, mCompare(std::move(other.mCompare))
	{}

	//

	// destructor

	~PriorityQueue() {}

	//

	// operator =

	PriorityQueue& operator=(const PriorityQueue& other)
	{
		mContainer = other.mContainer;
		mCompare = other.mCompare;
		return *this;
	}

	PriorityQueue& operator=(PriorityQueue&& other) noexcept
	{
		mContainer = std::move(other.mContainer);
		mCompare = std::move(other.mCompare);
		return *this;
	}

	//

	// Element access

	inline const T& top() const
	{
		return mContainer.front();
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

	// Modifiers

	inline void push(const T& value)
	{
		mContainer.push_back(value);

		size_t now = mContainer.size() - 1;

		while (now > 0)
		{
			size_t parent = (now - 1) / 2;

			if (mCompare(mContainer[now], mContainer[parent]))
				break;

			std::swap(mContainer[now], mContainer[parent]);
			now = parent;
		}
	}

	inline void push(T&& value)
	{
		mContainer.push_back(std::move(value));

		size_t now = mContainer.size() - 1;

		while (now > 0)
		{
			size_t parent = (now - 1) / 2;

			if (mCompare(mContainer[now], mContainer[parent]))
				break;

			std::swap(mContainer[now], mContainer[parent]);
			now = parent;
		}
	}

	inline void pop()
	{
		mContainer[0] = mContainer.back();
		mContainer.pop_back();

		size_t now = 0;

		while (true)
		{
			size_t left = (2 * now) + 1;
			size_t right = (2 * now) + 2;

			if (left >= mContainer.size())
				break;

			size_t next = now;

			if (mCompare(mContainer[next], mContainer[left]))
				next = left;

			if (right < mContainer.size() && mCompare(mContainer[next], mContainer[left]))
				next = right;

			if (now == next)
				break;

			std::swap(mContainer[now], mContainer[next]);
			now = next;
		}
	}

	inline void swap(PriorityQueue& other) noexcept
	{
		mContainer.swap(other.mContainer);
		mCompare.swap(other.mCompare);
	}

private:
	Container mContainer;
	Compare mCompare;
};