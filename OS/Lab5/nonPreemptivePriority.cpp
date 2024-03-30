#include<bits/stdc++.h>
using namespace std ; 

struct Process
{
    int processID ; 
    int burstTime ; 
    int priority ; 
    int waitingTime ; 
    int turnaroundTime ; 
} ; 

bool compareProcess( Process a, Process b )
{
    return a.priority > b.priority ; 
}

int main()
{
    freopen("input.txt", "r", stdin) ; 
    int processNumber = 5 , i ; 
    int value, wait = 0, turn = 0 ; 
    string curr_process ; 
    char ch ; 

    cin >> processNumber ;
    vector<Process> process(processNumber) ; 
    for( i = 0 ; i < processNumber ; i++ )
    {
        cin >> process[i].burstTime ; 
        cin >> process[i].priority ; 
        process[i].processID = i+1 ; 
    }

    sort( process.begin(), process.end(), compareProcess ) ; 

    process[0].turnaroundTime = process[0].burstTime ; 
    process[0].waitingTime = 0 ; 
    for( i = 1 ; i <= processNumber ; i++ )
    {
        process[i].turnaroundTime = process[i].burstTime + process[i-1].turnaroundTime ; 
        process[i].waitingTime = process[i].turnaroundTime - process[i].burstTime ; 
    }
    cout << "Gantt chart:" << endl ; 
    cout << "|" ; 
    for( i = 0 ; i < processNumber ; i++ )
    {
        cout << "---P" << process[i].processID << "---|" ; 
    }
    cout << endl ; 
    printf("%-9d", 0) ; 
    for( auto p : process )
    {
        printf("%-9d", p.turnaroundTime) ; 
    }
    cout << endl << endl ; 

    printf("%s\t%s\t\t%s\t%s\n", "Process ID", "Turnaround Time", "Waiting Time", "Priority") ; 
    for( auto p : process )
    {
        printf("P%d %20d %20d %17d\n", p.processID, p.turnaroundTime, p.waitingTime, p.priority) ; 
        wait += p.waitingTime ; 
        turn += p.turnaroundTime ; 
    }

    cout << "Average turnaround time: " << (double)turn/processNumber << endl ; 
    cout << "Average waiting time: " << (double)wait/processNumber << endl ; 
}

