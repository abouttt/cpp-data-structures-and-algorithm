#pragma once

#include <vector>
#include <queue>
using namespace std;

// 버블 정렬
// (N-1) + (N-2) + ... + 2 + 1
// 등차수열의 합 = N * (N-1) / 2
// O(N^2)
void BubbleSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (v[j] > v[j + 1])
			{
				swap(v[j], v[j + 1]);
			}
		}
	}
}

// 선택 정렬
// O(N^2)
void SelectionSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 0; i < n - 1; i++)
	{
		int bestIdx = i;

		for (int j = i + 1; j < n; j++)
		{
			if (v[j] < v[bestIdx])
			{
				bestIdx = j;
			}
		}

		swap(v[i], v[bestIdx]);
	}
}

// 삽입 정렬
// O(N^2)
void InsertionSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 1; i < n; i++)
	{
		int insertData = v[i];

		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (v[j] > insertData)
			{
				v[j + 1] = v[j];
			}
			else
			{
				break;
			}
		}

		v[j + 1] = insertData;
	}
}

void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, greater<int>> pq;

	// O(NlogN)
	for (int num : v)
	{
		pq.push(num);
	}

	v.clear();

	// O(NlogN)
	while (pq.empty() == false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
}

// 병합 정렬
// 분할 정복 (Divide and Conquer)
// - 분할 (Divide)	문제를 더 단순하게 분할한다.
// - 정복 (Conquer)	분할된 문제를 해결
// - 결합 (Combine)	결과를 취합하여 마무리

// O(NlogN)
void MergeResult(vector<int>& v, int left, int mid, int right)
{
	int leftIdx = left;
	int rightIdx = mid + 1;

	vector<int> temp;

	while (leftIdx <= mid && rightIdx <= right)
	{
		if (v[leftIdx] <= v[rightIdx])
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
		else
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}

	if (leftIdx > mid)
	{
		while (rightIdx <= right)
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	else
	{
		while (leftIdx <= mid)
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
	}

	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}

void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	MergeResult(v, left, mid, right);
}

// high, low 시작지점부터 앞으로 이동하거나 뒤로 이동할 뿐이고
// high, low가 다시 초기값으로 돌아가서 반복문을 도는것이 아니기 때문에 O(N)이다.
// O(N)
int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
		{
			low++;
		}

		while (high >= left + 1 && pivot <= v[high])
		{
			high--;
		}

		if (low < high)
		{
			swap(v[low], v[high]);
		}
	}

	swap(v[left], v[high]);
	return high;
}

// 최악 : O(N^2)
// 평균 : O(NlogN)
void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
	{
		return;
	}

	int pivot = Partition(v, left, right);
	QuickSort(v, left, pivot - 1);
	QuickSort(v, pivot + 1, right);
}