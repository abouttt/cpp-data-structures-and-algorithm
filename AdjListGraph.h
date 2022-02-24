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
		: mVertices(other.mVertices)
	{}

	AdjListGraph(AdjListGraph&& other) noexcept
		: mVertices(std::move(other.mVertices))
	{}

	//

	// destructor

	~AdjListGraph() {}

	//

	// operator =

	AdjListGraph& operator=(const AdjListGraph& other)
	{
		mVertices = other.mVertices;
		return *this;
	}

	AdjListGraph& operator=(AdjListGraph&& other) noexcept
	{
		mVertices = std::move(other.mVertices);
		return *this;
	}

	//

	// Element access

	inline T& at(size_type pos)
	{
		return mVertices.at(pos).mData;
	}

	inline const T& at(size_type pos) const
	{
		return mVertices.at(pos).mData;
	}

	T& operator[](size_type pos)
	{
		return mVertices[pos].mData;
	}

	const T& operator[](size_type pos) const
	{
		return mVertices[pos].mData;
	}

	//

	// Capacity

	inline bool empty() const noexcept
	{
		return mVertices.empty();
	}

	inline size_type size() const noexcept
	{
		return mVertices.size();
	}

	inline void reserve(size_type newCapacity)
	{
		if (newCapacity <= mVertices.capacity())
		{
			return;
		}

		mVertices.reserve(newCapacity);
	}

	inline size_type capacity() const noexcept
	{
		return mVertices.capacity();
	}

	//

	// Modifiers

	inline void clear() noexcept
	{
		mVertices.clear();
	}

	inline void clear_edges()
	{
		for (auto& vertex : mVertices)
		{
			vertex.mEdges.clear();
		}
	}

	inline void clear_edges(const T& value)
	{
		size_type valueIndex = findIndex(value);
		mVertices[valueIndex].mEdges.clear();
	}

	// 정점 삭제시 해당 정점을 연결한 간선도 함께 삭제되나
	// 값들이 앞당겨져 값이 상이할 수 있음. 간선들의 값 재조정 필요.
	inline void erase_vertex(const T& value)
	{
		if (mVertices.size() <= 0)
		{
			return;
		}

		auto eraseIt = std::find(mVertices.begin(), mVertices.end(), value);
		if (eraseIt == mVertices.end())
		{
			return;
		}

		for (size_type i = 0; i < mVertices.size(); i++)
		{
			if (mVertices[i].mData == (*eraseIt))
			{
				continue;
			}

			auto it = std::find(mVertices[i].mEdges.begin(), mVertices[i].mEdges.end(), &(*eraseIt));
			if (it != mVertices[i].mEdges.end())
			{
				mVertices[i].mEdges.erase(it);
			}
		}

		mVertices.erase(eraseIt);
	}

	inline void erase_edge(const T& from, const T& to)
	{
		if (mVertices.size() <= 0)
		{
			return;
		}

		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		auto eraseIt = std::find(mVertices[fromIndex].mEdges.begin(), mVertices[fromIndex].mEdges.end(), &mVertices[toIndex]);

		if (eraseIt == mVertices[fromIndex].mEdges.end())
		{
			return;
		}

		mVertices[fromIndex].mEdges.erase(eraseIt);
	}

	inline void push_back(const T& value)
	{
		auto it = std::find(mVertices.begin(), mVertices.end(), value);
		if (it != mVertices.end())
		{
			return;
		}

		mVertices.push_back(Vertex(value));
	}

	inline void push_back(T&& value)
	{
		auto it = std::find(mVertices.begin(), mVertices.end(), value);
		if (it != mVertices.end())
		{
			return;
		}

		mVertices.push_back(std::move(Vertex(value)));
	}

	inline void link_vertex(const T& from, const T& to)
	{
		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		if (fromIndex == toIndex)
		{
			return;
		}

		mVertices[fromIndex].mEdges.push_back(&mVertices[toIndex]);
	}

	inline void unlink_vertex(const T& from, const T& to)
	{
		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		if (fromIndex == toIndex)
		{
			return;
		}

		auto eraseIt = std::find(mVertices[fromIndex].mEdges.begin(), mVertices[fromIndex].mEdges.end(), &mVertices[toIndex]);
		if (eraseIt == mVertices[fromIndex].mEdges.end())
		{
			return;
		}

		mVertices[fromIndex].mEdges.erase(eraseIt);
	}

	inline bool is_linked(const T& from, const T& to)
	{
		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		if (fromIndex == toIndex)
		{
			return false;
		}

		auto eraseIt = std::find(mVertices[fromIndex].mEdges.begin(), mVertices[fromIndex].mEdges.end(), &mVertices[toIndex]);
		if (eraseIt != mVertices[fromIndex].mEdges.end())
		{
			return true;
		}

		return false;
	}

	inline void swap(AdjListGraph& other) noexcept
	{
		std::swap(mVertices, other.mVertices);
	}

	inline void dfs_search(const T& start)
	{
		std::vector<bool> visited(mVertices.size(), false);
		dfs(start, visited);
	}

	inline void bfs_search(const T& start)
	{
		std::vector<bool> discovered(mVertices.size(), false);
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

			std::cout << mVertices[currentInex].mData << std::endl;

			for (auto& next : mVertices[currentInex].mEdges)
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
		for (size_type i = 0; i < mVertices.size(); i++)
		{
			if (mVertices[i].mData == value)
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

		for (size_type i = 0; i < mVertices[currentIndex].mEdges.size(); i++)
		{
			T next = mVertices[currentIndex].mEdges[i]->mData;
			size_type nextIndex = findIndex(next);
			if (visited[nextIndex] == false)
			{
				dfs(mVertices[nextIndex].mData, visited);
			}
		}
	}

private:
	std::vector<Vertex> mVertices;
};