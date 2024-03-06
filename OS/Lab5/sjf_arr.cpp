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
    bool isDone ;
} ; 

bool compareProcessBurst(Process a, Process b)
{
    if( !a.isDone )
        return (a.burstTime <= b.burstTime) ; 
    else 
    return false ;
} 

bool compareProcessArr(Process a, Process b)
{
    if( !a.isDone )
        return (a.arrivalTime <= b.arrivalTime) ;
    else 
    return false ;
} 

int main()
{
    freopen("inputAr.txt", "r", stdin) ; 
    int processNumber = 5 , i ; 
    vector<Process> process(processNumber+1) ;  //  processRun(processNumber)
    Process temp;
    int value, wait = 0, turn = 0 ; 
    string curr_process ; 
    char ch ; 
    
    temp.turnaroundTime = temp.burstTime = 0 ; 
    temp.waitingTime = 0 ;
    temp.isDone = true ;  
    temp.runTime = 0 ;
    process.push_back(temp) ;

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
        process[i].isDone = false ; 
    }

    sort(process.begin(), process.end(), compareProcessArr ) ; 
    

    for( i = 0 ; i <= processNumber ; i++ )
    {
        sort(process.begin()+i-1, process.end(), compareProcessBurst ) ;
        if( process[i].arrivalTime <= process[i-1].runTime )
        {
            
            process[i].turnaroundTime = process[i].burstTime + process[i-1].turnaroundTime ; 
            process[i].waitingTime = process[i].turnaroundTime - process[i].burstTime ;
            process[i].runTime = process[i-1].runTime + process[i].burstTime ;
        } 
        else
        {
            sort(process.begin()+i, process.end(), compareProcessArr ) ;
            process[i].turnaroundTime = process[i].burstTime + process[i-1].turnaroundTime ; 
            process[i].waitingTime = process[i].turnaroundTime - process[i].burstTime ;
            process[i].runTime = process[i-1].runTime + process[i].burstTime ;
        }
    }

    cout << "\nGantt chart:" << endl ; 
    cout << "|" ; 
    for( i = 0 ; i < processNumber ; i++ )
    {
        cout << "---P" << process[i].processID << "---|" ; 
    }
    cout << endl  ; 
    printf("%-9d", 0) ; 
    for( auto p : process )
    {
        printf("%-9d", p.turnaroundTime) ; 
    }
    cout << endl << endl ; 

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