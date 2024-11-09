#include <iostream>
using namespace std;

// Structure to represent a job
struct Job {
    int id;        // Job ID
    int deadline;  // Deadline of job
    int profit;    // Profit of job
};

// Function to find the maximum profit job schedule
void jobScheduling(Job jobs[], int n) {
    // Step 1: Sort jobs in decreasing order of profit
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (jobs[i].profit < jobs[j].profit) {
                // Swap the jobs
                Job temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }

    // Step 2: Find the maximum deadline to determine the number of time slots
    int maxDeadline = 0;
    for (int i = 0; i < n; ++i) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }

    // Step 3: Create a time slot array to keep track of available time slots
    int *slots = new int[maxDeadline]; // Each slot will store the job ID or -1 if empty
    for (int i = 0; i < maxDeadline; ++i) {
        slots[i] = -1; // -1 means the time slot is empty
    }

    // Step 4: Schedule jobs
    int totalProfit = 0;
    int jobCount = 0;

    for (int i = 0; i < n; ++i) {
        // Find a time slot for this job
        for (int j = jobs[i].deadline - 1; j >= 0; --j) {
            if (slots[j] == -1) {
                // Slot found, schedule the job
                slots[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                jobCount++;
                cout << "Job " << jobs[i].id << " is placed in slot " << j + 1 << endl;
                break;
            }
        }
    }

    // Output the result
    cout << "Number of jobs scheduled: " << jobCount << endl;
    cout << "Total profit: " << totalProfit << endl;

    // Clean up
    delete[] slots;
}

int main() {
    // Array of jobs {id, deadline, profit}
    Job jobs[] = {
        {1, 4, 20},
        {2, 1, 10},
        {3, 1, 40},
        {4, 1, 30},
        {5, 3, 50}
    };
    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobScheduling(jobs, n);

    return 0;
}