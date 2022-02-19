#pragma once

#include <cassert>

template<typename T>
class Vector
{
private:
	class Iterator
	{
	public:
		Iterator()
			: mDataPtr(nullptr)
			, mPos(0)
		{}

		Iterator(T* data, size_t pos)
			: mDataPtr(data)
			, mPos(pos)
		{}

		Iterator& operator++()
		{
			++mPos;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator temp = *this;
			++mPos;
			return temp;
		}

		Iterator& operator--()
		{
			--mPos;
			return *this;
		}

		Iterator operator--(int)
		{
			Iterator temp = *this;
			--mPos;
			return temp;
		}

		T& operator*()
		{
			return mDataPtr[mPos];
		}

		Iterator& operator=(const Iterator& other)
		{
			mDataPtr = other.mDataPtr;
			mPos = other.mPos;
		}

		bool operator==(const Iterator& other) const noexcept
		{
			return &mDataPtr[mPos] == &other.mDataPtr[other.mPos];
		}

		bool operator!=(const Iterator& other) const noexcept
		{
			return &mDataPtr[mPos] != &other.mDataPtr[other.mPos];
		}

		Iterator& operator+(const size_t value)
		{
			Iterator temp(mDataPtr, mPos + value);

			return temp;
		}

		Iterator& operator-(const size_t value)
		{
			Iterator temp(mDataPtr, mPos - value);

			return temp;
		}

		Iterator& operator+=(const size_t value)
		{
			mPos += value;

			return *this;
		}

		Iterator& operator-=(const size_t value)
		{
			mPos -= value;

			return *this;
		}

		operator size_t()
		{
			return mPos;
		}

	private:
		T* mDataPtr;
		size_t mPos;
	};

public:
	using iterator = Iterator;

	// constructor

	explicit Vector() noexcept
		: mData(nullptr)
		, mCapacity(0)
		, mSize(0)
	{}

	explicit Vector(size_t count, const T& value = T())
		: mData(new T[count])
		, mCapacity(count)
		, mSize(count)
	{
		for (size_t i = 0; i < count; i++)
		{
			mData[i] = value;
		}
	}

	Vector(std::initializer_list<T> init)
		: mData(new T[init.size()])
		, mCapacity(init.size())
		, mSize(init.size())
	{
		memcpy(mData, init.begin(), sizeof(T) * init.size());
	}

	Vector(const Vector& other)
		: mData(new T[other.mCapacity])
		, mCapacity(other.mCapacity)
		, mSize(other.mSize)
	{
		memcpy(mData, other.mData, sizeof(T) * other.size());
	}

	Vector(Vector&& other)
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

	~Vector()
	{
		if (mData)
		{
			delete mData;
		}
	}

	//

	// operator =

	Vector& operator=(const Vector& other)
	{
		if (this != &other)
		{
			Vector temp(other);
			swap(temp);
		}

		return *this;
	}

	Vector& operator=(Vector&& other)
	{
		swap(other);

		return *this;
	}

	Vector& operator=(std::initializer_list<T> ilist)
	{
		Vector temp(ilist);
		swap(temp);

		return *this;
	}

	inline void assign(size_t count, const T& value)
	{
		Vector temp(count, value);
		swap(temp);
	}

	inline void assign(std::initializer_list<T> ilist)
	{
		Vector temp(ilist);
		swap(temp);
	}

	//

	// Element access

	inline T& at(size_t pos)
	{
		if (pos < 0 || pos >= mSize)
			throw std::out_of_range("invalid Vector subscript");

		return mData[pos];
	}

	inline const T& at(size_t pos) const
	{
		if (pos < 0 || pos >= mSize)
			throw std::out_of_range("invalid Vector subscript");

		return mData[pos];
	}

	inline T& operator[](size_t pos)
	{
		assert(pos > -1 || pos < mSize);

		return mData[pos];
	}

	inline const T& operator[](size_t pos) const
	{
		assert(pos > -1 || pos < mSize);

		return mData[pos];
	}

	inline T& front()
	{
		assert(mSize > 0);

		return mData[0];
	}

	inline const T& front() const
	{
		assert(mSize > 0);

		return mData[0];
	}

	inline T& back()
	{
		assert(mSize > 0);

		return mData[mSize - 1];
	}

	inline const T& back() const
	{
		assert(mSize > 0);

		return mData[mSize - 1];
	}

	inline T* data() noexcept
	{
		return mData;
	}

	inline const T* data() const noexcept
	{
		return mData;
	}

	//

	// Iterators

	inline iterator begin() noexcept
	{
		return iterator(mData, 0);
	}

	inline iterator end() noexcept
	{
		return iterator(mData, mSize);
	}

	//

	// Capacity

	inline bool empty() const noexcept
	{
		return mSize == 0;
	}

	inline size_t size() const noexcept
	{
		return mSize;
	}

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

	inline size_t capacity() const noexcept
	{
		return mCapacity;
	}

	//

	// Modifiers

	inline void clear() noexcept
	{
		mSize = 0;
	}

	// insert() : 올바르게 작동은 하나, 비효율적인 것 같다.
	inline iterator insert(iterator pos, const T& value)
	{
		assert(pos <= mSize);

		Vector temp;

		for (size_t i = 0; i < pos; i++)
		{
			temp.push_back(mData[i]);
		}

		temp.push_back(value);

		for (size_t i = pos; i < mSize; i++)
		{
			temp.push_back(mData[i]);
		}

		swap(temp);

		return Iterator(mData, pos);
	}

	inline iterator insert(iterator pos, const T&& value)
	{
		assert(pos <= mSize);

		Vector temp;

		for (size_t i = 0; i < pos; i++)
		{
			temp.push_back(mData[i]);
		}

		temp.push_back(value);

		for (size_t i = pos; i < mSize; i++)
		{
			temp.push_back(mData[i]);
		}

		swap(temp);

		return Iterator(mData, pos);
	}

	inline iterator insert(iterator pos, size_t count, const T& value)
	{
		assert(pos <= mSize);

		Vector temp;

		for (size_t i = 0; i < pos; i++)
		{
			temp.push_back(mData[i]);
		}

		for (size_t i = 0; i < count; i++)
		{
			temp.push_back(value);
		}

		for (size_t i = pos; i < mSize; i++)
		{
			temp.push_back(mData[i]);
		}

		swap(temp);

		return Iterator(mData, pos);
	}

	inline iterator insert(iterator pos, std::initializer_list<T> ilist)
	{
		assert(pos <= mSize);

		Vector temp;

		for (size_t i = 0; i < pos; i++)
		{
			temp.push_back(mData[i]);
		}

		for (auto& i : ilist)
		{
			temp.push_back(i);
		}

		for (size_t i = pos; i < mSize; i++)
		{
			temp.push_back(mData[i]);
		}

		swap(temp);

		return Iterator(mData, pos);
	}

	inline void push_back(const T& value)
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

	inline void push_back(T&& value)
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

		mData[mSize++] = std::move(value);
	}

	inline void pop_back()
	{
		mSize = mSize > 0 ? mSize - 1 : 0;
	}

	inline void resize(size_t newSize, const T& value = T())
	{
		if (newSize == mSize ||
			newSize < mSize)
		{
			mSize = newSize;
			return;
		}

		reserve(newSize);

		T* newData = new T[mCapacity];

		for (size_t i = 0; i < mSize; i++)
		{
			newData[i] = mData[i];
		}

		for (size_t i = mSize; i < mCapacity; i++)
		{
			newData[i] = value;
		}

		if (mData)
		{
			delete mData;
		}

		mData = newData;
		mSize = newSize;
	}

	inline void swap(Vector& other)
	{
		std::swap(mData, other.mData);
		std::swap(mCapacity, other.mCapacity);
		std::swap(mSize, other.mSize);
	}

	//

	inline bool operator==(const Vector& other)
	{
		if (mSize != other.mSize)
		{
			return false;
		}

		for (int i = 0; i < mSize; i++)
		{
			if (mData[i] != other.mData[i])
			{
				return false;
			}
		}

		return true;
	}

	inline bool operator!=(const Vector& other)
	{
		return !(*this == other);
	}

private:
	T* mData;
	size_t mCapacity;
	size_t mSize;
};
