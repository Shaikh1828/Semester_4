#include<bits/stdc++.h>
using namespace std ;

struct Process
{
    int processID ;
    int burstTime ;
    int priority ;
    int waitingTime ;
    int turnaroundTime ;
    int remainingTime ;
} ;

struct Result
{
    int processID ;
    int start ;
    int end ;
} ;

bool compareProcess(Process a, Process b)
{
    return a.priority > b.priority ;
}

int main()
{
    freopen("input.txt", "r", stdin) ;
    int processNumber = 5 , i, j ;
    int remaining_process = processNumber ;
    vector<Process> process(processNumber) ;
    vector<Result> result ;
    int value, wait = 0, turn = 0, quantam ;
    int curr_process, s, e ;
    char ch ;

    cin >> processNumber ;
    for(i = 0 ;i<processNumber ;i++)
    {
        cin >> process[i].burstTime ;
        cin >> process[i].priority ;
        process[i].processID = i + 1 ;
        process[i].remainingTime = process[i].burstTime ;
    }

    cin >> quantam ;
    
    i = 0 ;
    int curr_time = 0 ;
    Result temp ;
    
    while(remaining_process)
    {
        if( i == processNumber )
        {
            i = 0 ;
        }
        if( process[i].remainingTime > 0 )
        {
            if( process[i].remainingTime <= quantam )
            {
                curr_process = process[i].processID ;
                s = curr_time ;
                e = curr_time + process[i].remainingTime ;
                curr_time = e ;
                process[i].remainingTime = 0 ;
                remaining_process-- ;
            }
            else
            {
                curr_process = process[i].processID ;
                s = curr_time ;
                e = curr_time + quantam ;
                process[i].remainingTime -= quantam ;
                curr_time = e ;
            }
            temp.processID = process[i].processID ;
            temp.start = s ;
            temp.end = e ;
            result.push_back(temp) ;
        }
        i++ ;
    }

    cout << "Gantt chart:" << endl ;
    cout << "|" ;
    for(auto r:result)
    {
        cout << "---P" << r.processID << "---|" ;
    }
    cout << endl ;
    printf("%-9d", 0) ;
    for(auto r:result)
    {
        printf("%-9d", r.end) ;
    }
    cout << endl ;
<<<<<<< Updated upstream
   
=======
    
>>>>>>> Stashed changes
    for( auto r : result )
    {
        for( i = 0 ; i < processNumber ; i++ )
        {
            if( process[i].processID == r.processID )
            {
                process[i].turnaroundTime = r.end ;
                break ;
            }
        }
    }
    for( i = 0 ; i < processNumber ; i++ )
    {
        process[i].waitingTime = process[i].turnaroundTime-process[i].burstTime ;
    }
    printf("\nPID\tTurn\tWait\n") ;
    for( i = 0 ; i < processNumber ; i++ )
    {
        printf("P%d\t%d\t%d\n", process[i].processID, process[i].turnaroundTime, process[i].waitingTime ) ;
    }

    for( auto p : process )
    {
        printf("P%d\t%d\t%d\n", p.processID, p.turnaroundTime, p.waitingTime) ; 
        wait += p.waitingTime ; 
        turn += p.turnaroundTime ; 
    }
    cout << endl ;
    cout << "Average turnaround time: " << (double)turn/processNumber << endl ; 
    cout << "Average waiting time: " << (double)wait/processNumber << endl ; 
    
    return 0 ;
}

