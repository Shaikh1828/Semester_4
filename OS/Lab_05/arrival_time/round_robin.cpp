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
bool arrived_process_comparator(Process a,Process b);
void set_arrived_process(vector<Process> &arrived_process,vector<Process> temp,int curr_time);
void update_process_queue(queue<Process> &process_queue,vector<Process> temp,int from,int to);
void update_process_queue(queue<Process> &process_queue,vector<Process> temp,int curr_time);

int main()
{
    int quantam;
    cout<<"Enter quantam: ";
    cin>>quantam;
    freopen("input.txt","r",stdin);

    int i,j;
    int wait=0,turn=0;
    int value,process_num=6;
    vector<Process> process;
    vector<Result> results;
    Process temp_process;

    for(i=0;i<process_num;i++)
    {
        temp_process.name="P"+to_string(i+1);
        cin>>value;
        temp_process.burst_time=value;
        cin>>value;
        temp_process.priority=value;
        cin>>value;
        temp_process.arrival=value;
        temp_process.turn_around_time=0;
        temp_process.waiting_time=0;
        process.push_back(temp_process);
    }
    vector<Process> temp;
    temp=process;
    sort(temp.begin(),temp.end(),process_comparator);
    int curr_time=0;
    int range=0;
    Result result;
    queue<Process> process_queue;
    Process curr_process;
    if(temp.front().arrival>curr_time){
        result.name="DL";
        result.start=curr_time;
        curr_time=temp.front().arrival;
        result.end=curr_time;
        results.push_back(result);
    }
    for(auto t:temp){
        if(t.arrival>curr_time){
            break;
        }
        process_queue.push(t);
    }
    
    while(!temp.empty()){
        if(process_queue.empty()){
            result.name="DL";
            result.start=curr_time;
            curr_time=temp.front().arrival;
            result.end=curr_time;
            results.push_back(result);
            update_process_queue(process_queue,temp,curr_time);
        }
        else{
            curr_process=process_queue.front();
            result.name=curr_process.name;
            result.start=curr_time;
            if(curr_process.burst_time<=quantam){
                curr_time+=curr_process.burst_time;
                result.end=curr_time;
                results.push_back(result);
                range=curr_process.burst_time;
                curr_process.burst_time=0;
            }
            else{
                curr_time+=quantam;
                result.end=curr_time;
                results.push_back(result);
                range=quantam;
                curr_process.burst_time-=quantam;
            }
            process_queue.pop();
            update_process_queue(process_queue,temp,curr_time-range,curr_time);
            auto it=temp.begin();
            while(it!=temp.end()){
                if((*it).name==curr_process.name){
                    if(curr_process.burst_time==0){
                        temp.erase(it);
                    }
                    else{
                        (*it).burst_time-=quantam;
                        process_queue.push((*it));
                    }
                    break;
                }
                it++;
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
bool process_comparator(Process a,Process b){
    if(a.arrival==b.arrival){
        if(a.priority==b.priority){
            return a.burst_time<b.burst_time;
        }
        return a.priority>b.priority;
    }
    return a.arrival<b.arrival;
}
bool arrived_process_comparator(Process a,Process b){
    if(a.priority==b.priority){
        return a.burst_time<b.burst_time;
    }
    return a.priority>b.priority;
}

void set_arrived_process(vector<Process> &arrived_process,vector<Process> temp,int curr_time){
    arrived_process.clear();
    for(auto t:temp){
        if(t.arrival>curr_time){
            break;
        }
        arrived_process.push_back(t);
    }
    sort(arrived_process.begin(),arrived_process.end(),arrived_process_comparator);
}

void update_process_queue(queue<Process> &process_queue,vector<Process> temp,int from,int to){
    for(auto t:temp){
        if(t.arrival>from&&t.arrival<=to){
            process_queue.push(t);
        }
    }
}

void update_process_queue(queue<Process> &process_queue,vector<Process> temp,int curr_time){
    for(auto t:temp){
        if(t.arrival==curr_time){
            process_queue.push(t);
        }
    }
}