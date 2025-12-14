#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

const int DISK_SIZE = 200;

// ============================================================
// FCFS DISK SCHEDULING ALGORITHM
// ============================================================
void FCFS(int requests[], int n, int head) {
    int totalSeek = 0;
    
    cout << "\nFCFS ALGORITHM" << endl;
    cout << "Seek Sequence: " << head;
    
    for (int i = 0; i < n; i++) {
        int distance = abs(requests[i] - head); 
        totalSeek += distance;          
        head = requests[i];            
        cout << " -> " << head;
    }
    
    cout << endl;
    cout << "Total Seek Operations: " << totalSeek << endl;
}

// ============================================================
// SSTF DISK SCHEDULING ALGORITHM
// ============================================================
void SSTF(int request[], int n, int head) {
    bool visited[100] = {false};   
    int totalSeek = 0;
    
    cout << "\nSSTF ALGORITHM" << endl;
    cout << "Seek Sequence: " << head;
    
    for (int step = 0; step < n; step++) {
        int idx = -1;
        int minDist = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int dist = abs(head - request[i]);
                if (dist < minDist) {
                    minDist = dist;
                    idx = i;
                }
            }
        }
        
        visited[idx] = true;
        totalSeek += minDist;
        head = request[idx];
        cout << " -> " << head;
    }
    
    cout << endl;
    cout << "Total Seek Operations: " << totalSeek << endl;
}

// ============================================================
// SCAN DISK SCHEDULING ALGORITHM
// ============================================================
void SCAN(int arr[], int n, int head, string direction)
{
    int seek_count = 0;
    vector<int> left, right, seek_sequence;

    // Add boundaries
    left.push_back(0);
    right.push_back(DISK_SIZE - 1);

    // Split requests based on head position
    for (int i = 0; i < n; i++) {
        if (arr[i] < head) left.push_back(arr[i]);
        else if (arr[i] > head) right.push_back(arr[i]);
    }

    // Sort vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    if (direction == "left") {
        // Service left side first (descending)
        for (int i = left.size() - 1; i >= 0; i--) {
            seek_sequence.push_back(left[i]);
            seek_count += abs(head - left[i]);
            head = left[i];
        }
        // Then service right side (ascending)
        for (int i = 0; i < right.size(); i++) {
            seek_sequence.push_back(right[i]);
            seek_count += abs(head - right[i]);
            head = right[i];
        }
    } 
    else { // direction == "right"
        // Service right side first (ascending)
        for (int i = 0; i < right.size(); i++) {
            seek_sequence.push_back(right[i]);
            seek_count += abs(head - right[i]);
            head = right[i];
        }
        // Then service left side (descending)
        for (int i = left.size() - 1; i >= 0; i--) {
            seek_sequence.push_back(left[i]);
            seek_count += abs(head - left[i]);
            head = left[i];
        }
    }

    // Output results
    cout << "\nSCAN ALGORITHM (Direction: " << direction << ")" << endl;
    cout << "Total Seek Operations: " << seek_count << endl;
    cout << "Seek Sequence: ";
    for (size_t i = 0; i < seek_sequence.size(); i++) {
        cout << seek_sequence[i];
        if (i < seek_sequence.size() - 1) cout << " -> ";
    }
    cout << endl;
}

// ============================================================
// C-SCAN DISK SCHEDULING ALGORITHM
// ============================================================
void CSCAN(int arr[], int n, int head)
{
    int seek_count = 0;
    vector<int> left, right, seq;

    // Add boundaries
    left.push_back(0);
    right.push_back(DISK_SIZE - 1);

    // Split requests
    for (int i = 0; i < n; i++) {
        if (arr[i] < head) left.push_back(arr[i]);
        else if (arr[i] > head) right.push_back(arr[i]);
    }

    // Sort vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Service right side (ascending)
    for (int x : right) {
        seq.push_back(x);
        seek_count += abs(head - x);
        head = x;
    }

    // Jump to beginning and add seek for jump
    if (!right.empty()) {
        seek_count += abs(head - (DISK_SIZE - 1));
    }
    seek_count += (DISK_SIZE - 1); // Jump from end to start
    head = 0;

    // Service left side (ascending)
    for (int x : left) {
        seq.push_back(x);
        seek_count += abs(head - x);
        head = x;
    }

    // Output results
    cout << "\nC-SCAN ALGORITHM" << endl;
    cout << "Total Seek Operations: " << seek_count << endl;
    cout << "Seek Sequence: ";
    for (size_t i = 0; i < seq.size(); i++) {
        cout << seq[i];
        if (i < seq.size() - 1) cout << " -> ";
    }
    cout << endl;
}

// ============================================================
// C-LOOK DISK SCHEDULING ALGORITHM
// ============================================================
void CLOOK(int arr[], int n, int head)
{
    int seek_count = 0;
    vector<int> left, right, seq;

    // Split requests (no boundaries needed for LOOK)
    for (int i = 0; i < n; i++) {
        if (arr[i] < head) left.push_back(arr[i]);
        else if (arr[i] > head) right.push_back(arr[i]);
    }

    // Sort vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Service right side (ascending)
    for (int x : right) {
        seq.push_back(x);
        seek_count += abs(head - x);
        head = x;
    }

    // Jump to smallest on left side
    if (!left.empty()) {
        seek_count += abs(head - left[0]);
        head = left[0];
    }

    // Service left side (ascending)
    for (int x : left) {
        seq.push_back(x);
        seek_count += abs(head - x);
        head = x;
    }

    // Output results
    cout << "\nC-LOOK ALGORITHM" << endl;
    cout << "Total Seek Operations: " << seek_count << endl;
    cout << "Seek Sequence: ";
    for (size_t i = 0; i < seq.size(); i++) {
        cout << seq[i];
        if (i < seq.size() - 1) cout << " -> ";
    }
    cout << endl;
}



struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    bool isCompleted;
};
// ============================================================
// FCFS CPU SCHEDULING ALGORITHM
// ============================================================
void fcfsCPU() {
    int n;
    cout << "How many processes? ";
    cin >> n;

    int arrival[100];
    int burst[100];
    int waiting[100];

    for (int i = 0; i < n; i++) {
        cout << "P" << (i+1) << " arrival time: ";
        cin >> arrival[i];

        cout << "P" << (i+1) << " burst time: ";
        cin >> burst[i];

        waiting[i] = 0;
    }

    int currentTime = 0;
//sort by arrival time
    for (int i = 0; i < n; i++) {
        if (currentTime < arrival[i]) {
            currentTime = arrival[i];
        }

        waiting[i] = currentTime - arrival[i];
        currentTime += burst[i];
    }
// Output results
    cout << "\nResults:\n";
    int total = 0;

    for (int i = 0; i < n; i++) {
        cout << "P" << (i+1) << " waiting time = " << waiting[i] << endl;
        total += waiting[i];
    }

    cout << "\nAverage waiting time = " << (double)total / n << endl;
}


// ============================================================
// SJF CPU SCHEDULING ALGORITHM
// ============================================================

void sjfCPU() {
    int n;
    cout << "How many processes? ";
    cin >> n;

    int arrival[100];
    int burst[100];
    int waiting[100];
    bool isCompleted[100];

  
    for (int i = 0; i < n; i++) {
        cout << "P" << (i+1) << " arrival time: ";
        cin >> arrival[i];

        cout << "P" << (i+1) << " burst time: ";
        cin >> burst[i];

        waiting[i] = 0;
        isCompleted[i] = false;  
    }

    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int minBurst = INT_MAX;
    
        // find process with shortest burst time
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= currentTime && !isCompleted[i]) {

                if (burst[i] < minBurst) {
                    minBurst = burst[i];
                    idx = i;
                }
                // If burst times are equal, choose the one that arrived first
                else if (burst[i] == minBurst) {
                    if (arrival[i] < arrival[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            waiting[idx] = currentTime - arrival[idx];
            currentTime += burst[idx];
            isCompleted[idx] = true;
            completed++;
        } else {
            currentTime++; 
        }
    }

    // Output results
    cout << "\nResults:\n";
    int total = 0;

    for (int i = 0; i < n; i++) {
        cout << "P" << (i+1) << " waiting time = " << waiting[i] << endl;
        total += waiting[i];
    }

    cout << "\nAverage waiting time = " << (double)total / n << endl;
}

//=============================================================
// SRTF CPU SCHEDULING ALGORITHM
//=============================================================
void srtfCPU() {
    
    cout << "How many processes? ";
    // number op processes
    int n;
    cin >> n;
    
    // all the arrayes for processes info
    int arrival[100];
    int burst[100];
    int remaining[100];
    int waiting[100];
    int finish[100];
    
    // loop for inputs the arrival and burst time

    for (int i = 0; i < n; i++) {
        cout << "P" << (i+1) << " arrival time: ";
        cin >> arrival[i];
        cout << "P" << (i+1) << " burst time: ";
        cin >> burst[i];

        // set the remaning time
        remaining[i] = burst[i];  
        waiting[i] = 0;
        finish[i] = 0;
    }
    // for tracking 
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int minRemain = INT_MAX;

        // to find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= currentTime && remaining[i] > 0) {
                if (remaining[i] < minRemain) {
                    minRemain = remaining[i];
                    idx = i;
                }
                else if (remaining[i] == minRemain) {
                    if (arrival[i] < arrival[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            remaining[idx]--;
            
            if (remaining[idx] == 0) {
                completed++;
                finish[idx] = currentTime + 1;
                waiting[idx] = finish[idx] - arrival[idx] - burst[idx];
                if (waiting[idx] < 0) waiting[idx] = 0;
            }
        }
        // move to next time unit
        currentTime++;
    }

    // The results
    cout << "\nResults:\n";
    int total = 0;

    for (int i = 0; i < n; i++) {
        cout << "P" << (i+1) << " waiting time = " << waiting[i] << endl;
        total += waiting[i];
    }

    cout << "\nAverage waiting time = " << (double)total / n << endl;
}

//=============================================================
// PRIORITY CPU SCHEDULING ALGORITHM
//=============================================================
void priorityCPU() {
    
    cout << "How many processes? ";
    // number of processes
    int n;
    cin >> n;

    // all the arrayes for processes info
    int arrival[100];
    int burst[100];
    int priority[100];
    int waiting[100];
    int finish[100];
    bool done[100];
    
    // input for arrival , burst time and priority for each process
    for (int i = 0; i < n; i++) {
        cout << "P" << (i+1) << " arrival time: ";
        cin >> arrival[i];

        cout << "P" << (i+1) << " burst time: ";
        cin >> burst[i];

        cout << "P" << (i+1) << " priority: ";
        cin >> priority[i];

        waiting[i] = 0;
        done[i] = false;
    }
    
    // for tracking
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int bestPriority = INT_MAX;

        // Find process with the highest priority
        for (int i = 0; i < n; i++) {
            if (!done[i] && arrival[i] <= currentTime) {
                if (priority[i] < bestPriority) {
                    bestPriority = priority[i];
                    idx = i;
                }
                else if (priority[i] == bestPriority) {
                    if (arrival[i] < arrival[idx]) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            waiting[idx] = currentTime - arrival[idx];
            currentTime += burst[idx];
            done[idx] = true;
            completed++;
        }
        else {
            currentTime++;
        }
    }

    // The Results
    cout << "\nResults:\n";
    int total = 0;

    for (int i = 0; i < n; i++) {
        cout << "P" << (i+1) 
             << " waiting time = " << waiting[i]
             << " (priority = " << priority[i] << ")" << endl;
        total += waiting[i];
    }

    cout << "\nAverage waiting time = " << (double)total / n << endl;
}

// ============================================================
// MAIN FUNCTION
// ============================================================
int main() {
    int typeChoice;
    cout << "Scheduling Type:\n";
    cout << "1 - Disk Scheduling\n";
    cout << "2 - CPU Scheduling\n";
    cout << "Enter your choice: ";
    cin >> typeChoice;

    if (typeChoice == 1) {
        int algoChoice;
        cout << "\nDisk Scheduling Algorithms:\n";
        cout << "1 - FCFS\n";
        cout << "2 - SSTF\n";
        cout << "3 - SCAN\n";
        cout << "4 - C-SCAN\n";
        cout << "5 - C-LOOK\n";
        cout << "Enter your choice: ";
        cin >> algoChoice;

        int n;
        cout << "\nEnter number of disk requests: ";
        cin >> n;

        int requests[100];
        cout << "Enter the disk request queue:\n";
        for (int i = 0; i < n; i++) {
            cout << "Request " << i+1 << ": ";
            cin >> requests[i];
        }

        int head;
        cout << "Enter initial head position: ";
        cin >> head;
        
        cout << "\nDisk Size: " << DISK_SIZE << " cylinders (0-" << DISK_SIZE-1 << ")" << endl;
        cout << "Initial Head Position: " << head << endl;
        cout << "Request Queue: ";
        for (int i = 0; i < n; i++) {
            cout << requests[i];
            if (i < n - 1) cout << ", ";
        }
        cout << endl;

        if (algoChoice == 1) {
            FCFS(requests, n, head);
        } 
        else if (algoChoice == 2) {
            SSTF(requests, n, head);
        }
        else if (algoChoice == 3) {
            string direction;
            cout << "Enter direction for SCAN (left/right): ";
            cin >> direction;
            SCAN(requests, n, head, direction);
        }
        else if (algoChoice == 4) {
            CSCAN(requests, n, head);
        }
        else if (algoChoice == 5) {
            CLOOK(requests, n, head);
        }
        
        else {
            cout << "Invalid disk algorithm choice.\n";
        }
    }
    else if (typeChoice == 2) {
        int urChoice;
        cout << "\nCPU Scheduling Algorithms:\n";
        cout << "1 - FCFS\n";
        cout << "2 - SJF\n";
        cout << "3 - SRTF\n";
        cout << "4 - PRIORITY\n";
        cout << "Enter your choice: ";
        cin >> urChoice;
        
        if (urChoice== 1) {
            fcfsCPU();
        } 
        else if (urChoice== 2) {
            sjfCPU();
        }
        else if (urChoice == 3){
            srtfCPU();
        }
        else if (urChoice == 4){
            priorityCPU();
        }

        
    }
    else {
        cout << "Invalid main choice.\n";
    }

    return 0;
}