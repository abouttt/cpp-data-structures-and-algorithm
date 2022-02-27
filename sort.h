#pragma once

#include <vector>
using namespace std;

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