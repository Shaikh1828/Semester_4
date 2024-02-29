#include<bits/stdc++.h>
using namespace std ; 

struct Process
{
    int processID ; 
    int burstTime ; 
    int arrivalTime ; 
    int priority ; 
    int waitingTime ; 
    int turnaroundTime ; 
    int runTime ;
} ; 

bool compareProcess(Process a, Process b)
{
    return (a.burstTime <= b.burstTime) && (a.arrivalTime <= b.arrivalTime) ; 
} 

int main()
{
    freopen("inputAr.txt", "r", stdin) ; 
    int processNumber = 5 , i ; 
    vector<Process> process(processNumber) ; 
    int value, wait = 0, turn = 0 ; 
    string curr_process ; 
    char ch ; 

    cin >> processNumber ;

    for( i = 1 ; i <= processNumber ; i++ )
    {
        cin >> value ; 
        process[i].burstTime = value ; 
        cin >> value ; 
        process[i].priority = value ; 
        cin >> value ; 
        process[i].arrivalTime = value ; 
        process[i].processID = i  ; 
    }

    sort(process.begin(), process.end(), compareProcess) ; 
    
    process[0].turnaroundTime = process[0].burstTime ; 
    process[0].waitingTime = 0 ; 
    for( i = 1 ; i <= processNumber ; i++ )
    {
        process[i].turnaroundTime = process[i].burstTime + process[i-1].turnaroundTime ; 
        process[i].waitingTime = process[i].turnaroundTime - process[i].burstTime ; 
    }

    cout << "\nGantt chart:" << endl ; 
    cout << "|" ; 
    for( i = 0 ; i < processNumber ; i++ )
    {
        cout << "---P" << process[i].processID << "---|" ; 
    }
    cout << endl << endl ; 
    printf("%-9d", 0) ; 
    for( auto p : process )
    {
        printf("%-9d", p.turnaroundTime) ; 
    }
    cout << endl ; 

    printf("%s\t%s\t\t%s\n", "Process ID", "Turnaround Time", "Waiting Time") ; 

    for( auto p : process )
    {
        printf("P%d %20d %23d\n", p.processID, p.turnaroundTime, p.waitingTime) ; 
        wait += p.waitingTime ; 
        turn += p.turnaroundTime ; 
    }
    cout << "Average turnaround time: " << (double)turn/processNumber << endl ; 
    cout << "Average waiting time: " << (double)wait/processNumber << endl ; 
}

/*

6
20 40 0
25 30 25
10 30 30 
15 35 10
15 5 40
30 10 10

*/