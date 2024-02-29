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

bool compareProcess( Process a, Process b )
{
    return a.arrivalTime <= b.arrivalTime ; 
} 

int main()
{
    freopen("inputAr.txt", "r", stdin) ;

    int processNumber , i, value, turn_time_sum = 0, wait_time_sum = 0 ;
    vector<Process> processes ;
    
    Process prs ;

    cin >> processNumber ;

    for( i=0 ; i <= processNumber ; i++ )
    {
        cin >> prs.burstTime ;
        cin >> prs.priority ;
        cin >> prs.arrivalTime ;
        processes.push_back(prs) ;
    }

    sort ( processes.begin(), processes.end(), compareProcess );

    for( i=0 ; i < processNumber ; i++ )
    {
        if( processes[i].arrivalTime < processes[i-1].runTime ) 
        {
            processes[i].runTime = processes[i-1].runTime + processes[i].burstTime ;
            processes[i].turnaroundTime = ( processes[i].runTime - processes[i].arrivalTime ) ;
            processes[i].waitingTime = ( processes[i].turnaroundTime - processes[i].burstTime ) ;
        }
        else
        {
            processes[i].runTime = processes[i].burstTime + processes[i].arrivalTime ;
            processes[i].turnaroundTime = ( processes[i].burstTime ) ;
            processes[i].waitingTime = 0 ;
        }
            
        turn_time_sum += processes[i].turnaroundTime ;
        wait_time_sum += processes[i].waitingTime ;
        //cout << runTime[i] << endl ;
    }

    cout << "\nGantt chart:\n" << endl ;
    cout << "|" ;
    for( i=1 ; i <= processNumber ; i++ )
    {
        cout << "---P" << i << "---|" ;
    }
    cout << endl ;
    printf("%-9d", 0 ) ;
    for( i=0 ; i < processNumber ; i++ )
    {
        printf("%-9d", processes[i].runTime ) ;
    }
    cout << endl << endl ;

    printf("%s\t%s\t\t%s\n","Process-ID", "TurnAround-Time", "Waiting-Time") ;

    for( i=0 ; i < processNumber ; i++ )
    {
        printf("P%d %20d %23d\n",i+1, processes[i].turnaroundTime, processes[i].waitingTime ) ;
    }
    cout << endl ;
    cout << "Average turnaround time: " << (double)turn_time_sum/processNumber << endl ;
    cout << "Average waiting time: " << (double)wait_time_sum/processNumber << endl << endl ;

}