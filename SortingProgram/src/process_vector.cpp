#include "process_vector.h"
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <limits>

using std::vector;
using std::unordered_map;

// Merge function to merge two sorted subarrays
//left subarray: v[left..mid], right subarray: v[mid+1..right]
void merge(vector<double>& v, std::vector<double>::size_type left, std::vector<double>::size_type mid, std::vector<double>::size_type right) {
    std::vector<double>::size_type n1 = mid - left + 1;
    std::vector<double>::size_type n2 = right - mid;

    vector<double> L(n1); //temporary array for left
    vector<double> R(n2); //temporary array for right

    //copies data into temporary arrays
    for (std::vector<double>::size_type i = 0; i < n1; i++)
        L[i] = v[left + i];
    for (std::vector<double>::size_type i = 0; i < n2; i++)
        R[i] = v[mid + 1 + i];

    std::vector<double>::size_type i = 0; 
    std::vector<double>::size_type j = 0; 
    std::vector<double>::size_type k = left; 

    //merges L and R into v[]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    //copies remaining elemtents of L[]
    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }
    //copies remaining elements of R[]
    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}

//recursive merge sort function to sort left and right
void merge_sort(vector<double>& v, std::vector<double>::size_type left, std::vector<double>::size_type right) {
    if (left < right) {
        std::vector<double>::size_type mid = left + (right - left) / 2;

        merge_sort(v, left, mid); //sort first half
        merge_sort(v, mid + 1, right); //sort second half

        merge(v, left, mid, right); //merge both halves
    }
}

//sorts entire vector in ascending order with merge sort
void sort_vector_ascending(vector<double>& v) {
    if (!v.empty()) {
        merge_sort(v, 0, v.size() - 1);
    }
}

//merges two sorted vectors v1 and v2 into a single result vector
vector<double> merge(const vector<double>& v1, const vector<double>& v2) {
    vector<double> result;
    std::vector<double>::size_type i = 0;
    std::vector<double>::size_type j = 0;

    while (i < v1.size() && j < v2.size()) {
        if (v1[i] <= v2[j]) {
            result.push_back(v1[i]);
            i++;
        } else {
            result.push_back(v2[j]);
            j++;
        }
    }

    //append any remaining elements from v1
    while (i < v1.size()) {
        result.push_back(v1[i]);
        i++;
    }

    //append any remaining elements from v2
    while (j < v2.size()) {
        result.push_back(v2[j]);
        j++;
    }

    return result;
}

//calculates the average of the values 
//returns Nan if the vector is empty
double find_mean(const vector<double>& v) {
    if (v.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    double sum = 0.0;
    for (double num : v) {
        sum += num;
    }
    return sum / v.size();
}

//calculates the middle value of the sorted vecotr
//returns Nan if the vector is empty
double find_median(vector<double> v) {
    if (v.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    sort_vector_ascending(v); //makes sure the vector is sorted
    std::vector<double>::size_type n = v.size();
    if (n % 2 == 0) {
        //takes the average of the middle elements if the lsit is an even
        //length of numbers
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
    } else {
        //returns middle number if the length is odd
        return v[n / 2];
    }
}

//finds the most frequently occurring vlaue
//if multiple exist, then it returns the smallest one
//returns NaN if the vector is empty
double find_mode(vector<double> v) {
    if (v.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    unordered_map<double, int> frequency;
    for (double num : v) {
        frequency[num]++;
    }

    int max_count = 0;
    vector<double> modes;

    for (auto& pair : frequency) {
        if (pair.second > max_count) {
            max_count = pair.second;
            modes.clear();
            modes.push_back(pair.first);
        } else if (pair.second == max_count) {
            modes.push_back(pair.first);
        }
    }

    if (modes.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return *min_element(modes.begin(), modes.end());
    
}
