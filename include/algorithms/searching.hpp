#pragma once

#include <vector>

namespace algo
{
template <typename T>
int linear_search(const std::vector<T>& arr, const T& value)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

template <typename T>
int binary_search(const std::vector<T>& arr, const T& value)
{
    int left = 0, right = arr.size() - 1;

    while (left <= right)
    {
        int mid = left + ((right - left) / 2);

        if (arr[mid] == value)
        {
            return mid;
        }

        if (value > arr[mid])
        {
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
    return -1;
}

template <typename T>
int interpolation_search(const std::vector<T>& arr, const T& value)
{
    int left = 0;
    int right = arr.size() - 1;
    int pos = 0;

    while (left <= right && value >= arr[left] && value <= arr[right])
    {
        pos = left + (((float)(right - left) / (arr[right] - arr[left])) *
                      (value - arr[left]));

        if (arr[pos] == value)
        {
            return pos;
        }
        if (arr[pos] < value)
        {
            left = pos + 1;
        }
        else if (arr[pos] > value)
        {
            right = pos - 1;
        }
    }
    return -1;
}
} // namespace algo
