#include<bits/stdc++.h>
using namespace std ; 

struct Process
{
    int process_id ; 
    int burst_time ; 
    int priority ; 
    int waiting_time ; 
    int turnaround_time ; 
} ; 

bool compareProcess(Process a, Process b)
{
    return a.burst_time < b.burst_time ; 
} 

int main()
{
    freopen("input.txt", "r", stdin) ; 
    int processNumber = 5 , i ; 
    vector<Process> process(processNumber) ; 
    int value, wait = 0, turn = 0 ; 
    string curr_process ; 
    char ch ; 

    cin >> processNumber ;

    for( i = 0 ; i < processNumber ; i++ )
    {
        cin >> value ; 
        process[i].burst_time = value ; 
        cin >> value ; 
        process[i].priority = value ; 
        process[i].process_id = i + 1 ; 
    }

    sort(process.begin(), process.end(), compareProcess) ; 
    
    process[0].turnaround_time = process[0].burst_time ; 
    process[0].waiting_time = 0 ; 
    for( i = 1 ; i <= processNumber ; i++ )
    {
        process[i].turnaround_time = process[i].burst_time + process[i-1].turnaround_time ; 
        process[i].waiting_time = process[i].turnaround_time - process[i].burst_time ; 
    }
    cout << "\nGantt chart:" << endl ; 
    cout << "|" ; 
    for( i = 0 ; i < processNumber ; i++ )
    {
        cout << "---P" << process[i].process_id << "---|" ; 
    }
    cout << endl ; 
    printf("%-9d", 0) ; 
    for( auto p : process )
    {
        printf("%-9d", p.turnaround_time) ; 
    }
    cout << endl ; 
    printf("%s\t%s\t\t%s\n", "Process ID", "Turnaround Time", "Waiting Time") ; 

    for( auto p : process )
    {
        printf("P%d %20d %23d\n", p.process_id, p.turnaround_time, p.waiting_time) ; 
        wait += p.waiting_time ; 
        turn += p.turnaround_time ; 
    }
    cout << "Average turnaround time: " << (double)turn/processNumber << endl ; 
    cout << "Average waiting time: " << (double)wait/processNumber << endl ; 
}

