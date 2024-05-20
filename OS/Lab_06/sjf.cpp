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
bool process_arrival_comparator(Process a,Process b);
bool process_burst_comparator(Process a,Process b);
void set_arrived_process(vector<Process> &arrived_process,vector<Process> temp,int curr_time,vector<int> &next_arrival);
int main(){
    freopen("input.txt","r",stdin);
    int i,j;
    int wait=0,turn=0;
    int value,process_num=6,arrived_processes=0,remaining_processes=process_num;
    vector<Process> process;
    vector<Result> results;
    vector<int> next_arrival;
    Process temp_process;
    for(i=0;i<process_num;i++){
        temp_process.name="P"+to_string(i+1);
        cin>>value;
        temp_process.burst_time=value;
        cin>>value;
        temp_process.priority=value;
        cin>>value;
        temp_process.arrival=value;
        next_arrival.push_back(value);
        temp_process.turn_around_time=0;
        temp_process.waiting_time=0;
        process.push_back(temp_process);
    }
    sort(next_arrival.begin(),next_arrival.end());
    vector<Process> temp;
    temp=process;
    sort(temp.begin(),temp.end(),process_arrival_comparator);
    int curr_time=0;
    Result result;
    vector<Process> arrived_process;
    Process curr_process;
    while(remaining_processes>0){
        if(arrived_process.empty()){
            result.name="DL";
            result.start=curr_time;
            curr_time=next_arrival.front();
            result.end=curr_time;
            results.push_back(result);
            set_arrived_process(arrived_process,temp,curr_time,next_arrival);
        }
        if(curr_process.name!=arrived_process.front().name){
            result.end=curr_time;
            results.push_back(result);
            curr_process=arrived_process.front();
            result.name=curr_process.name;
            result.start=curr_time;
        }
        
        else{
            result.end=curr_time;
            results.push_back(result);
            curr_process=arrived_process.front();
            result.name=curr_process.name;
            result.start=curr_time;
            if(!next_arrival.empty()){
                if(curr_process.burst_time+curr_time>next_arrival.front()){
                    for(auto &t:temp){
                        if(curr_process.name==t.name){
                            t.burst_time-=next_arrival.front()-curr_time;
                            break;
                        }
                    }
                    curr_time=next_arrival.front();
                }
                else{
                    curr_time+=curr_process.burst_time;
                    auto it=temp.begin();
                    while(it!=temp.end()){
                        if((*it).name==curr_process.name){
                            temp.erase(it);
                        }
                    }
                }
                set_arrived_process(arrived_process,temp,curr_time,next_arrival);
            }
            else{
                curr_time+=curr_process.burst_time;
                auto it=temp.begin();
                while(it!=temp.end()){
                    if((*it).name==curr_process.name){
                        temp.erase(it);
                    }
                }
                auto it=arrived_process.begin();
                while(it!=arrived_process.end()){
                    if((*it).name==curr_process.name){
                        arrived_process.erase(it);
                    }
                }
            }
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
        if(r.name!="DL"){
            for(auto &p:process){
                if(p.name==r.name){
                    p.turn_around_time=r.end-p.arrival;
                    p.waiting_time=p.turn_around_time-p.burst_time;
                }
            }
        }
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
bool process_arrival_comparator(Process a,Process b){
    if(a.arrival==b.arrival){
        return a.burst_time<b.burst_time;
    }
    return a.arrival<b.arrival;
}

void set_arrived_process(vector<Process> &arrived_process,vector<Process> temp,int curr_time,vector<int> &next_arrival){
    arrived_process.clear();
    for(auto t:temp){
        if(t.arrival>curr_time){
            break;
        }
        arrived_process.push_back(t);
        next_arrival.erase(next_arrival.begin());
    }
    sort(arrived_process.begin(),arrived_process.end(),process_burst_comparator);
}

bool process_burst_comparator(Process a,Process b){
    return a.burst_time<b.burst_time;
}