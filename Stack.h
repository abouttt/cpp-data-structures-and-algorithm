#pragma once

// same class Vector

template<typename T>
class Stack
{
public:

	// constructor

	explicit Stack()
		: mData(nullptr)
		, mCapacity(0)
		, mSize(0)
	{}

	Stack(const Stack& other)
		: mData(new T[other.mCapacity])
		, mCapacity(other.mCapacity)
		, mSize(other.mSize)
	{
		memcpy(mData, other.mData, sizeof(T) * other.mSize);
	}

	Stack(Stack&& other)
		: mData(std::move(other.mData))
		, mCapacity(std::move(other.mCapacity))
		, mSize(std::move(other.mSize))
	{
		other.mData = nullptr;
		other.mSize = 0;
		other.mCapacity = 0;
	}

	//

	// destructor

	~Stack()
	{
		if (mData)
		{
			delete[] mData;
		}
	}

	//

	// operator=

	Stack& operator=(const Stack& other)
	{
		if (this != &other)
		{
			Stack temp(other);
			swap(temp);
		}

		return *this;
	}

	Stack& operator=(Stack&& other)
	{
		Stack temp(std::move(other));
		swap(temp);

		return *this;
	}

	//

	// Element access

	inline T& top()
	{
		return mData[mSize - 1];
	}

	inline const T& top() const
	{
		return mData[mSize - 1];
	}

	//

	// Capacity

	inline bool empty() const
	{
		return mSize == 0;
	}

	inline size_t size() const
	{
		return mSize;
	}

	//

	// Modifiers

	inline void push(const T& value)
	{
		if (mSize == mCapacity)
		{
			size_t newCapacity = static_cast<size_t>(mCapacity * 1.5f);
			if (newCapacity == mCapacity)
			{
				newCapacity++;
			}

			reserve(newCapacity);
		}

		mData[mSize++] = value;
	}

	inline void push(T&& value)
	{
		if (mSize == mCapacity)
		{
			size_t newCapacity = static_cast<size_t>(mCapacity * 1.5f);
			if (newCapacity == mCapacity)
			{
				newCapacity++;
			}

			reserve(newCapacity);
		}

		mData[mSize++] = value;
	}

	inline void pop()
	{
		mSize = mSize > 0 ? mSize - 1 : 0;
	}

	inline void swap(Stack& other) noexcept
	{
		std::swap(mData, other.mData);
		std::swap(mCapacity, other.mCapacity);
		std::swap(mSize, other.mSize);
	}

private:
	inline void reserve(size_t newCapacity)
	{
		if (mCapacity >= newCapacity)
		{
			return;
		}

		mCapacity = newCapacity;

		T* newData = new T[mCapacity];
		memcpy(newData, mData, sizeof(T) * mSize);

		if (mData)
		{
			delete mData;
		}

		mData = newData;
	}


private:
	T* mData;
	size_t mCapacity;
	size_t mSize;
};