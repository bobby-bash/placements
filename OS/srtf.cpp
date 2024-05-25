#include<bits/stdc++.h>
using namespace std;

struct process {

    int pid, arrival_time, burst_time, remaining_time, predicted_time;
};

bool cmp(process a, process b) {
    if (a.arrival_time == b.arrival_time) {
        if (a.predicted_time == b.predicted_time) {
            return a.pid < b.pid;
        }
        return a.predicted_time < b.predicted_time;
    }
    return a.arrival_time < b.arrival_time;
}

void SRTF(vector<process>& processes) {
    int n = processes.size();
    int current_time = 0, completed = 0;
    vector<int> waiting_time(n, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                pq.push(make_pair(processes[i].predicted_time, processes[i].pid));
            }
        }
        if (pq.empty()) {
            current_time++;
            continue;
        }
        int pid = pq.top().second;
        pq.pop();
        processes[pid].remaining_time--;
        current_time++;
        if (processes[pid].remaining_time == 0) {
            completed++;
            waiting_time[pid] = current_time - processes[pid].arrival_time - processes[pid].burst_time;
        }
        else {
            processes[pid].predicted_time = processes[pid].remaining_time + current_time;
        }
    }

    cout << "PID\tArrival Time\tBurst Time\tTurn Around Time\tWaiting Time\n";
    int total_waiting_time = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << waiting_time[i] + processes[i].burst_time << "\t\t\t" << waiting_time[i] << "\n";
        total_waiting_time += waiting_time[i];
        total_tat += waiting_time[i] + processes[i].burst_time;
    }
    cout << "Average waiting time = " << (float)total_waiting_time / n << "\n";
    cout << "Average Turn Around time = " << (float)total_tat / n << "\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].pid = i;
        cout << "Enter the arrival time and burst time of process " << i << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].predicted_time = processes[i].burst_time;
    }
    sort(processes.begin(), processes.end(), cmp);
    SRTF(processes);
    return 0;
}

