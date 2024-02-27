#include<bits/stdc++.h>
using namespace std ;

int main()
{
    freopen("input.txt", "r", stdin) ;

    int process_num = 5, i, value, turn_time_sum = 0, wait_time_sum = 0  ;
    vector<int> burst_time, priority, waiting_time, turnaround_time  ;
    burst_time.push_back(0) ;
    turnaround_time.push_back(0) ;
    waiting_time.push_back(0) ;

    for( i=1 ; i <= process_num ; i++ )
    {
        cin >> value ;
        burst_time.push_back(value) ;
        cin >> value ;
        priority.push_back(value) ;
        turnaround_time.push_back(burst_time[i] + turnaround_time[i-1]) ;
        waiting_time.push_back(turnaround_time[i] - burst_time[i]) ;
        turn_time_sum += turnaround_time[i] ;
        wait_time_sum += waiting_time[i] ;
    }

    cout << "\nGantt chart:\n" << endl ;
    cout << "|" ;
    for( i=1 ; i <= process_num ; i++ )
    {
        cout << "---P" << i << "---|" ;
    }
    cout << endl ;
    for( auto t : turnaround_time )
    {
        printf("%-9d", t ) ;
    }
    cout << endl << endl ;

    printf("%s\t%s\t\t%s\n","Process ID", "Turnaround Time", "Waiting Time") ;

    for( i=1 ; i <= process_num ; i++ )
    {
        printf("P%d %20d %23d\n",i, turnaround_time[i], waiting_time[i] ) ;
    }
    cout << endl ;
    cout << "Average turnaround time: " << (double)turn_time_sum/process_num << endl ;
    cout << "Average waiting time: " << (double)wait_time_sum/process_num << endl << endl ;

}