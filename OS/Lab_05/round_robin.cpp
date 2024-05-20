#include<bits/stdc++.h>
using namespace std;
struct Process{
    int process_id;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
};
struct Result{
    int process_id;
    int start;
    int end;
};
int main(){
    freopen("input.txt","r",stdin);
    int process_num=5,i,j;
    int remaining_process=process_num;
    vector<Process> process(process_num);
    vector<Result> result;
    int value,wait=0,turn=0,quantam;
    int curr_process,s,e;
    char ch;
    for(i=0;i<process_num;i++){
        cin>>value;
        process[i].burst_time=value;
        cin>>value;
        process[i].priority=value;
        process[i].process_id=i+1;
        process[i].remaining_time=process[i].burst_time;
    }
    cin>>quantam;   // To be taken from file
    i=0;
    int curr_time=0;
    Result temp;
    while(remaining_process){
        if(i==process_num){
            i=0;
        }
        if(process[i].remaining_time>0){
            if(process[i].remaining_time<=quantam){
                curr_process=process[i].process_id;
                s=curr_time;
                e=curr_time+process[i].remaining_time;
                curr_time=e;
                process[i].remaining_time=0;
                remaining_process--;
            }
            else{
                curr_process=process[i].process_id;
                s=curr_time;
                e=curr_time+quantam;
                process[i].remaining_time-=quantam;
                curr_time=e;
            }
            temp.process_id=process[i].process_id;
            temp.start=s;
            temp.end=e;
            result.push_back(temp);
        }
        i++;
    }
    cout<<"Gantt chart:"<<endl;
    cout<<"|";
    for(auto r:result){
        cout<<"---P"<<r.process_id<<"---|";
    }
    cout<<endl;
    printf("%-9d",0);
    for(auto r:result){
        printf("%-9d",r.end);
    }
    cout<<endl;
    for(auto r:result){
        for(i=0;i<process_num;i++){
            if(process[i].process_id==r.process_id){
                process[i].turnaround_time=r.end;
                break;
            }
        }
    }
    for(i=0;i<process_num;i++){
        process[i].waiting_time=process[i].turnaround_time-process[i].burst_time;
        turn+=process[i].turnaround_time;
        wait+=process[i].waiting_time;
    }
    printf("PID\tTurn\tWait\n");
    for(i=0;i<process_num;i++){
        printf("P%d\t%d\t%d\n",process[i].process_id,process[i].turnaround_time,process[i].waiting_time);
    }
    cout<<"Average turnaround time: "<<(double)turn/process_num<<endl;
    cout<<"Average waiting time: "<<(double)wait/process_num<<endl;
    return 0;
}