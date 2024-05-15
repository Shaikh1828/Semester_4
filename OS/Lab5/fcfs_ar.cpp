#include<bits/stdc++.h>
using namespace std;
struct Process{
    string name;
    int burst_time;
    int priority;
    int arrival;
    int turn_around_time;
    int waiting_time;
};
struct Result{
    string name;
    int start;
    int end;
};
bool process_comparator(Process a,Process b);
int main(){
    freopen("inputAr.txt","r",stdin);
    int i,j;
    int wait=0,turn=0;
    int value,process_num=6;
    vector<Process> process;
    vector<Result> results;
    Process temp;
    for(i=0;i<process_num;i++){
        temp.name="P"+to_string(i+1);
        cin>>value;
        temp.burst_time=value;
        cin>>value;
        temp.priority=value;
        cin>>value;
        temp.arrival=value;
        temp.turn_around_time=0;
        temp.waiting_time=0;
        process.push_back(temp);
    }
    sort(process.begin(),process.end(),process_comparator);
    int curr_time=0;
    Result result;
    for(auto &p:process){
        if(p.arrival>curr_time){
            result.name="DL";
            result.start=curr_time;
            result.end=p.arrival;
            results.push_back(result);
            curr_time=p.arrival;
            result.name=p.name;
            result.start=curr_time;
            curr_time+=p.burst_time;
            result.end=curr_time;
            results.push_back(result);
            p.turn_around_time=curr_time-p.arrival;
            p.waiting_time=p.turn_around_time-p.burst_time;
        }
        else{
            result.name=p.name;
            result.start=curr_time;
            curr_time+=p.burst_time;
            result.end=curr_time;
            results.push_back(result);
            p.turn_around_time=curr_time-p.arrival;
            p.waiting_time=p.turn_around_time-p.burst_time;
        }
    }
    printf("|");
    for(auto r:results){
        printf("---%s---|",r.name.c_str());
    }
    cout<<endl;
    printf("%-9d",0);
    for(auto r:results){
        printf("%-9d",r.end);
    }
    cout<<endl<<endl;
    printf("%s\t%s\t\t%s\n","Process ID","Turnaround Time","Waiting Time");
    for(auto p:process){
        printf("%s %20d %23d\n",p.name.c_str(),p.turn_around_time,p.waiting_time);
        wait+=p.waiting_time;
        turn+=p.turn_around_time;
    }
    cout<<endl<<endl;
    cout<<"Average Turnaround Time: "<<(double)turn/process_num<<endl;
    cout<<"Average Waiting Time: "<<(double)wait/process_num<<endl;
    return 0;
}
bool process_comparator(Process a,Process b){
    if(a.arrival==b.arrival){
        return a.burst_time<b.burst_time;
    }
    return a.arrival<b.arrival;
}