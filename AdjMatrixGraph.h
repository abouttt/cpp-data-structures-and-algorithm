#pragma once

#include <vector>

template<typename T>
class AdjMatrixGraph
{
public:
	using size_type = std::vector<T>::size_type;
	// constructor

	explicit AdjMatrixGraph() = default;

	AdjMatrixGraph(const AdjMatrixGraph& other)
		: mData(other.mData)
		, mAdjMat(other.mAdjMat)
	{}

	AdjMatrixGraph(AdjMatrixGraph&& other)
		: mData(std::move(other.mData))
		, mAdjMat(std::move(other.mAdjMat))
	{}

	//

	// destructor

	~AdjMatrixGraph() {}

	//

	// operator =

	AdjMatrixGraph& operator=(const AdjMatrixGraph& other)
	{
		mData = other.mData;
		mAdjMat = other.mAdjMat;
		return *this;
	}

	AdjMatrixGraph& operator=(AdjMatrixGraph&& other) noexcept
	{
		mData = std::move(other.mData);
		mAdjMat = std::move(other.mAdjMat);
		return *this;
	}

	//

	// Element access

	inline int& at(size_type pos)
	{
		return mData.at(pos);
	}

	inline const int& at(size_type pos) const
	{
		return mData.at(pos);
	}

	int& operator[](size_type pos)
	{
		return mData[pos];
	}

	const int& operator[](size_type pos) const
	{
		return mData[pos];
	}

	//

	// Capacity

	inline bool empty() const noexcept
	{
		return mData.empty();
	}

	inline size_type size() const noexcept
	{
		return mData.size();
	}

	inline void reserve(size_type newCapacity)
	{
		mData.reserve(newCapacity);
	}

	inline size_type capacity() const noexcept
	{
		return mData.capacity();
	}

	//

	// Modifiers

	inline void clear() noexcept
	{
		mData.clear();
		mAdjMat.clear();
	}

	inline void clear_edges()
	{
		for (auto& edge : mAdjMat)
		{
			edge.assign(mData.size(), false);
		}
	}

	inline void clear_edges(const T& value)
	{
		size_type valueIndex = findIndex(value);
		mAdjMat[valueIndex].assign(mData.size(), false);
	}

	// 정점 삭제시 해당 정점을 연결한 간선은 그대로 이므로
	// 삭제할 정점에 연결된 간선을 먼저 삭제후 정점을 삭제 권장.
	inline void erase_vertex(const T& value)
	{
		if (mData.size() <= 0)
		{
			return;
		}

		auto eraseIt = std::find(mData.begin(), mData.end(), value);
		if (eraseIt == mData.end())
		{
			return;
		}

		mData.erase(eraseIt);
		mAdjMat.resize(mData.size());
		for (auto& edges : mAdjMat)
		{
			edges.resize(mData.size());
		}
	}

	inline void erase_edge(const T& from, const T& to)
	{
		if (mData.size() <= 0)
		{
			return;
		}

		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		mAdjMat[fromIndex][toIndex] = false;
	}

	inline void push_back(const T& value)
	{
		auto it = std::find(mData.begin(), mData.end(), value);
		if (it != mData.end())
		{
			return;
		}

		mData.push_back(value);
		mAdjMat.push_back(std::vector<bool>(mData.size(), false));
		for (auto& mat : mAdjMat)
		{
			mat.resize(mData.size(), false);
		}
	}

	inline void push_back(const T&& value)
	{
		auto it = std::find(mData.begin(), mData.end(), value);
		if (it != mData.end())
		{
			return;
		}

		mData.push_back(std::move(value));
		mAdjMat.push_back(std::vector<bool>(mData.size(), false));
		for (auto& mat : mAdjMat)
		{
			mat.resize(mData.size(), false);
		}
	}

	inline void link_vertex(const T& from, const T& to)
	{
		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		if (fromIndex == toIndex)
		{
			return;
		}

		mAdjMat[fromIndex][toIndex] = true;
	}

	inline void unlink_vertex(const T& from, const T& to)
	{
		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		if (fromIndex == toIndex)
		{
			return;
		}

		mAdjMat[fromIndex][toIndex] = false;
	}

	inline bool is_linked(const T& from, const T& to)
	{
		size_type fromIndex = findIndex(from);
		size_type toIndex = findIndex(to);

		return mAdjMat[fromIndex][toIndex];
	}

	inline void swap(AdjMatrixGraph& other) noexcept
	{
		std::swap(mData, other.mData);
		std::swap(mAdjMat, other.mAdjMat);
	}

	inline void dfs_search(const T& start)
	{
		std::vector<bool> visited(mData.size(), false);
		dfs(start, visited);
	}

	inline void bfs_search(const T& start)
	{
		std::vector<bool> discovered(mData.size(), false);
		std::queue<size_type> q;
		size_type startIndex = findIndex(start);
		q.push(startIndex);
		discovered[startIndex] = true;

		size_type currentInex;
		while (q.empty() == false)
		{
			currentInex = q.front();
			q.pop();

			std::cout << mData[currentInex] << std::endl;

			for (size_type i = 0; i < mAdjMat[currentInex].size(); i++)
			{
				if (mAdjMat[currentInex][i] == false || discovered[i])
				{
					continue;
				}

				q.push(i);
				discovered[i] = true;
			}
		}
	}

private:
	inline size_type findIndex(const T& value)
	{
		for (size_type i = 0; i < mData.size(); i++)
		{
			if (mData[i] == value)
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

		for (size_type i = 0; i < mData.size(); i++)
		{
			if (mAdjMat[currentIndex][i] == false)
			{
				continue;
			}

			if (visited[i] == false)
			{
				dfs(mData[i], visited);
			}
		}
	}

private:
	std::vector<T> mData;
	std::vector<std::vector<bool>> mAdjMat;
};