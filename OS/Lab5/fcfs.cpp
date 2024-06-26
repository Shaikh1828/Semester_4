#include<bits/stdc++.h>
using namespace std ;

int main()
{
    freopen("input.txt", "r", stdin) ;

    int processNumber , i, value, turn_time_sum = 0, wait_time_sum = 0  ;
    vector<int> burstTime, priority, waitingTime, turnaroundTime  ;
    burstTime.push_back(0) ;
    turnaroundTime.push_back(0) ;
    waitingTime.push_back(0) ;
    priority.push_back(0) ;

    cin >> processNumber ;

    for( i=1 ; i <= processNumber ; i++ )
    {
        cin >> value ;
        burstTime.push_back(value) ;
        cin >> value ;
        priority.push_back(value) ;

        turnaroundTime.push_back(burstTime[i] + turnaroundTime[i-1]) ;
        waitingTime.push_back(turnaroundTime[i] - burstTime[i]) ;
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

    printf("%s\t%s\t\t%s\n","Process ID", "TurnAround Time", "Waiting Time") ;

    for( i=1 ; i <= processNumber ; i++ )
    {
        printf("P%d %20d %23d\n",i, turnaroundTime[i], waitingTime[i] ) ;
    }
    cout << endl ;
    cout << "Average turnaround time: " << (double)turn_time_sum/processNumber << endl ;
    cout << "Average waiting time: " << (double)wait_time_sum/processNumber << endl << endl ;

}