#pragma once

#include <vector>

template<typename T>
class AdjListGraph
{
private:
	class Vertex
	{
	public:
		friend class AdjListGraph;

	public:
		Vertex(const T& data)
			: mData(data)
			, mEdges()
		{}

		Vertex(const Vertex& other)
			: mData(other.mData)
			, mEdges(other.mEdges)
		{}

		Vertex(Vertex&& other) noexcept
			: mData(std::move(other.mData))
			, mEdges(std::move(other.mEdges))
		{}

		Vertex& operator=(const Vertex& other)
		{
			mData = other.mData;
			mEdges = other.mEdges;
			return *this;
		}

		Vertex& operator=(Vertex&& other) noexcept
		{
			mData = std::move(other.mData);
			mEdges = std::move(other.mEdges);
			return *this;
		}

		bool operator==(const Vertex& other)
		{
			return mData == other.mData;
		}

	private:
		T mData;
		std::vector<Vertex*> mEdges;
	};

public:
	using size_type = std::vector<Vertex>::size_type;
	using iterator = std::vector<Vertex>::iterator;

	// constructor

	explicit AdjListGraph() = default;

	AdjListGraph(const AdjListGraph& other)
		: mAdjList(other.mAdjList)
	{}

	AdjListGraph(AdjListGraph&& other) noexcept
		: mAdjList(std::move(other.mAdjList))
	{}

	//

	// destructor

	~AdjListGraph() {}

	//

	// operator =

	AdjListGraph& operator=(const AdjListGraph& other)
	{
		mAdjList = other.mAdjList;
		return *this;
	}

	AdjListGraph& operator=(AdjListGraph&& other) noexcept
	{
		mAdjList = std::move(other.mAdjList);
		return *this;
	}

	//

	// Element access

	inline T& at(size_type pos)
	{
		return mAdjList.at(pos).mData;
	}

	inline const T& at(size_type pos) const
	{
		return mAdjList.at(pos).mData;
	}

	T& operator[](size_type pos)
	{
		return mAdjList[pos].mData;
	}

	const T& operator[](size_type pos) const
	{
		return mAdjList[pos].mData;
	}

	//

	// Capacity

	inline bool empty() const noexcept
	{
		return mAdjList.empty();
	}

	inline size_type size() const noexcept
	{
		return mAdjList.size();
	}

	inline size_type max_size() const noexcept
	{
		return mAdjList.max_size();
	}

	inline void reserve(size_type newCapacity)
	{
		mAdjList.reserve(newCapacity);
	}

	inline size_type capacity() const noexcept
	{
		return mAdjList.capacity();
	}

	//

	// Modifiers

	inline void clear() noexcept
	{
		mAdjList.clear();
	}

	inline void erase(const T& value)
	{
		size_t valueIndex = findIndex(value);
		auto valueIt = std::find(mAdjList.begin(), mAdjList.end(), mAdjList[valueIndex]);

		if (valueIt == mAdjList.end())
		{
			return;
		}

		for (size_type i = 0; i < mAdjList.size(); i++)
		{
			if (i == valueIndex)
			{
				continue;
			}

			for (size_type i = 0; i < mAdjList[i].mEdges.size(); i++)
			{
				auto it = std::find(mAdjList[i].mEdges.begin(), mAdjList[i].mEdges.end(), &mAdjList[valueIndex]);
				if (it != mAdjList[i].mEdges.end())
					mAdjList[i].mEdges.erase(it);
			}
		}

		mAdjList.erase(valueIt);
	}

	inline void push_back(const T& value)
	{
		Vertex vertex(value);
		mAdjList.push_back(vertex);
	}

	inline void push_back(T&& value)
	{
		Vertex vertex(std::move(value));
		mAdjList.push_back(std::move(vertex));
	}

	inline void link_vertex(const T& from, const T& to)
	{
		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		if (fromIndex == toIndex)
		{
			return;
		}

		mAdjList[fromIndex].mEdges.push_back(&mAdjList[toIndex]);
	}

	inline void swap(AdjListGraph& other) noexcept
	{
		std::swap(mAdjList, other.mAdjList);
	}
	
	inline void DFS(const T& start, const T& value)
	{

	}

	inline void BFS(const T& start, const T& value)
	{

	}

private:
	inline size_type findIndex(const T& value)
	{
		for (size_type i = 0; i < mAdjList.size(); i++)
		{
			if (mAdjList[i].mData == value)
			{
				return i;
			}
		}

		return -1;
	}

private:
	std::vector<Vertex> mAdjList;
};

