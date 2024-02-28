#include<bits/stdc++.h>
using namespace std ;

int main()
{
    freopen("inputAr.txt", "r", stdin) ;

    int processNumber , i, value, turn_time_sum = 0, wait_time_sum = 0 ;
    vector<int> burstTime, priority, arrival, waitingTime, turnaroundTime , runTime ;
    burstTime.push_back(0) ;
    arrival.push_back(0) ;
    turnaroundTime.push_back(0) ;
    waitingTime.push_back(0) ;
    runTime.push_back(0) ;

    cin >> processNumber ;

    for( i=1 ; i <= processNumber ; i++ )
    {
        cin >> value ;
        burstTime.push_back(value) ;
        cin >> value ;
        priority.push_back(value) ;
        cin >> value ;
        arrival.push_back(value) ;

    }

    for( i=1 ; i <= processNumber ; i++ )
    {
        if( arrival[i] <= turnaroundTime[i-1]) 
        {
            turnaroundTime.push_back(burstTime[i] + runTime[i]) ;
            waitingTime.push_back(turnaroundTime[i] - burstTime[i]) ;
            runTime[i] = runTime[i] + (burstTime[i]) ;
        }
        else
        {
            turnaroundTime.push_back(burstTime[i] ) ;
            waitingTime.push_back(0) ;
            runTime[i] += burstTime[i] + arrival[i] ;
        }
            
        turn_time_sum += turnaroundTime[i] ;
        wait_time_sum += waitingTime[i] ;
    }

    cout << "\nGantt chart:\n" << endl ;
    cout << "|" ;
    for( i=1 ; i <= processNumber ; i++ )
    {
        cout << "---P" << i << "---|" ;
    }
    cout << endl ;
    for( auto t : turnaroundTime )
    {
        printf("%-9d", t ) ;
    }
    cout << endl << endl ;

    printf("%s\t%s\t\t%s\n","Process-ID", "TurnAround-Time", "Waiting-Time") ;

    for( i=1 ; i <= processNumber ; i++ )
    {
        printf("P%d %20d %23d\n",i, turnaroundTime[i], waitingTime[i] ) ;
    }
    cout << endl ;
    cout << "Average turnaround time: " << (double)turn_time_sum/processNumber << endl ;
    cout << "Average waiting time: " << (double)wait_time_sum/processNumber << endl << endl ;

}