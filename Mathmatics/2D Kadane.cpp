#include <bits/stdc++.h>
using namespace std;

const int ROW = 4;
const int COL = 5;

// Standard Kadane's Algorithm for 1D array
int kadane(int* arr, int* start, int* finish, int n) {
    int sum = 0, maxSum = INT_MIN;
    int local_start = 0;
    *finish = -1;

    for (int i = 0; i < n; ++i) {
        sum += arr[i];

        if (sum < 0) {
            sum = 0;
            local_start = i + 1;
        } else if (sum > maxSum) {
            maxSum = sum;
            *start = local_start;
            *finish = i;
        }
    }

    // All elements are negative — fallback to max element
    if (*finish == -1) {
        maxSum = arr[0];
        *start = *finish = 0;
        for (int i = 1; i < n; ++i) {
            if (arr[i] > maxSum) {
                maxSum = arr[i];
                *start = *finish = i;
            }
        }
    }

    return maxSum;
}

// Function to find maximum sum rectangle in 2D matrix
void findMaxSum(int M[][COL]) {
    int maxSum = INT_MIN;
    int finalLeft, finalRight, finalTop, finalBottom;

    int temp[ROW], start, finish;

    for (int left = 0; left < COL; ++left) {
        memset(temp, 0, sizeof(temp));

        for (int right = left; right < COL; ++right) {
            for (int i = 0; i < ROW; ++i)
                temp[i] += M[i][right];

            int sum = kadane(temp, &start, &finish, ROW);

            if (sum > maxSum) {
                maxSum = sum;
                finalLeft = left;
                finalRight = right;
                finalTop = start;
                finalBottom = finish;
            }
        }
    }

    cout << "Top-Left:     (" << finalTop << ", " << finalLeft << ")\n";
    cout << "Bottom-Right: (" << finalBottom << ", " << finalRight << ")\n";
    cout << "Max Sum:      " << maxSum << "\n";
}

// Example usage
int main() {
    int M[ROW][COL] = {
        {1,  2,  -1, -4, -20},
        {-8, -3, 4,  2,   1},
        {3,  8, 10, 1,   3},
        {-4, -1, 1,  7,  -6}
    };

    findMaxSum(M);
    return 0;
}
