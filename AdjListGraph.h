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

	inline void clear_edges()
	{
		for (auto& vertex : mAdjList)
		{
			vertex.mEdges.clear();
		}
	}

	inline void clear_edges(const T& value)
	{
		size_type valueIndex = findIndex(value);
		mAdjList[valueIndex].mEdges.clear();
	}

	// 정점 삭제시 해당 정점을 연결한 간선도 함께 삭제되나
	// 값들이 앞당겨져 값이 상이할 수 있음. 간선들의 값 재조정 필요.
	inline void erase_vertex(const T& value)
	{
		if (mAdjList.size() <= 0)
		{
			return;
		}

		auto eraseIt = std::find(mAdjList.begin(), mAdjList.end(), value);
		if (eraseIt == mAdjList.end())
		{
			return;
		}

		for (size_type i = 0; i < mAdjList.size(); i++)
		{
			if (mAdjList[i].mData == (*eraseIt))
			{
				continue;
			}

			auto it = std::find(mAdjList[i].mEdges.begin(), mAdjList[i].mEdges.end(), &(*eraseIt));
			if (it != mAdjList[i].mEdges.end())
			{
				mAdjList[i].mEdges.erase(it);
			}
		}

		mAdjList.erase(eraseIt);
	}

	inline void erase_edge(const T& from, const T& to)
	{
		if (mAdjList.size() <= 0)
		{
			return;
		}

		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		auto eraseIt = std::find(mAdjList[fromIndex].mEdges.begin(), mAdjList[fromIndex].mEdges.end(), &mAdjList[toIndex]);

		if (eraseIt == mAdjList[fromIndex].mEdges.end())
		{
			return;
		}

		mAdjList[fromIndex].mEdges.erase(eraseIt);
	}

	inline void push_back(const T& value)
	{
		auto it = std::find(mAdjList.begin(), mAdjList.end(), value);
		if (it != mAdjList.end())
		{
			return;
		}

		mAdjList.push_back(Vertex(value));
	}

	inline void push_back(T&& value)
	{
		auto it = std::find(mAdjList.begin(), mAdjList.end(), value);
		if (it != mAdjList.end())
		{
			return;
		}

		mAdjList.push_back(std::move(Vertex(value)));
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

	inline void unlink_vertex(const T& from, const T& to)
	{
		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		if (fromIndex == toIndex)
		{
			return;
		}

		auto eraseIt = std::find(mAdjList[fromIndex].mEdges.begin(), mAdjList[fromIndex].mEdges.end(), &mAdjList[toIndex]);
		if (eraseIt == mAdjList[fromIndex].mEdges.end())
		{
			return;
		}

		mAdjList[fromIndex].mEdges.erase(eraseIt);
	}

	inline bool is_linked(const T& from, const T& to)
	{
		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		if (fromIndex == toIndex)
		{
			return false;
		}

		auto eraseIt = std::find(mAdjList[fromIndex].mEdges.begin(), mAdjList[fromIndex].mEdges.end(), &mAdjList[toIndex]);
		if (eraseIt != mAdjList[fromIndex].mEdges.end())
		{
			return true;
		}

		return false;
	}

	inline void swap(AdjListGraph& other) noexcept
	{
		std::swap(mAdjList, other.mAdjList);
	}

	inline void dfs_search(const T& start)
	{
		std::vector<bool> visited(mAdjList.size(), false);
		dfs(start, visited);
	}

	inline void bfs_search(const T& start)
	{
		std::vector<bool> discovered(mAdjList.size(), false);
		std::queue<size_type> q;
		size_type startIndex = findIndex(start);
		q.push(startIndex);
		discovered[startIndex] = true;

		size_type currentInex;
		size_type nextIndex;
		while (q.empty() == false)
		{
			currentInex = q.front();
			q.pop();

			std::cout << mAdjList[currentInex].mData << std::endl;

			for (auto& next : mAdjList[currentInex].mEdges)
			{
				nextIndex = findIndex(next->mData);
				if (discovered[nextIndex])
				{
					continue;
				}

				q.push(nextIndex);
				discovered[nextIndex] = true;
			}
		}
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

	inline void dfs(const T& current, std::vector<bool>& visited)
	{
		size_type currentIndex = findIndex(current);
		visited[currentIndex] = true;

		std::cout << current << std::endl;

		for (size_type i = 0; i < mAdjList[currentIndex].mEdges.size(); i++)
		{
			T next = mAdjList[currentIndex].mEdges[i]->mData;
			size_type nextIndex = findIndex(next);
			if (visited[nextIndex] == false)
			{
				dfs(mAdjList[nextIndex].mData, visited);
			}
		}
	}

private:
	std::vector<Vertex> mAdjList;
};

