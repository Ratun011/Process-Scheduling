#include<bits/stdc++.h>
#include <iostream>

#define mp(x, y) make_pair((x), (y))
#define ft first
#define sc second
#define X first
#define Y second
#define PI acos(-1)
#define FastRead                      \
            ios_base::sync_with_stdio(false); \
            cin.tie(0);
#define endl "\n"
using namespace std;

typedef long long int ll;
typedef pair<int, int> pt;

ll t,n,m,temp,i,j,k,e,f,g,x,y,z,sum,o,a,b,l,u,c,d,ma,mi,p;
string s,s1,s2,s3,h;

void getSJF(int a[]){
    cout<<"a. SJF [All processes arrive at 0]:"<<endl;
    vector<int>seq;
    int temp,b[6]= {0},k=5;
    while(k--)
    {
        temp=9999;
        for(i=1; i<6; i++)
        {
            if(a[i]<temp&&b[i]!=1)
            {
                temp=a[i];
                j=i;
            }
        }
        //cout<<temp<<endl;
        seq.push_back(j);//temp is the smallest burst and j it's index
        b[j]=1;
    }
    cout<<"- Sequence: [";
    for(i=0; i<5; i++)
    {
        cout<<seq[i];
        if(i!=4)
            cout<<", ";
        else
            cout<<"]"<<endl;
    }
    ll s=0;
    float awt=0;
    cout<<"- Intervals: [0, ";
    for(i=0;i<5;i++){
        s=s+a[seq[i]];
        cout<<s; //the intervals value
        if(i!=4){
            awt=awt+s; // saving total time as well
            cout<<", ";
        }
        else
            cout<<"]";
    }
    cout<<endl;
    cout<<"- Average Waiting Time: "<<awt/5<<"ms"<<endl;
    cout<<endl;
}

void getSRTF(int a[],int arrivalTime[]){
    cout<<"b. SRTF:"<<endl;
    ll waiting[5]={0},time,c=0,a2[6];
    ll smallValue,smallIndex,previousIndex=9999;
    vector<int>seq2,int2;
    for(i=1;i<6;i++)
    {
        a2[i]=a[i];
    }
    for(time=0; c!=5; time++)
    {
        smallValue=9999;
        for(i=1; i<6; i++)
        {
            if(arrivalTime[i-1]<=time && a2[i]<smallValue && a2[i]>0 ){
                smallIndex=i;
                smallValue=a2[i];
            }
        }
        if(smallIndex!=previousIndex){
            seq2.push_back(smallIndex);
            int2.push_back(time);
        }
        a2[smallIndex]--;
        for(i=1; i<6; i++)
        {
            if(arrivalTime[i-1]<=time && i!=smallIndex && a2[i]>0 )
                waiting[i-1]++;
        }
        if(a2[smallIndex]==0)
            c++;
        previousIndex=smallIndex;
    }
    cout<<"- Sequence: [";
    for(i=0;i<seq2.size();i++){
        cout<<seq2[i];
        if(i!=seq2.size()-1)
            cout<<", ";
        else
            cout<<"]"<<endl;
    }
    cout<<"- Intervals: [";
    for(i=0;i<int2.size();i++)
        cout<<int2[i]<<", ";
    cout<<time<<"]"<<endl;
    float awt=0;
    for(i=0;i<5;i++)
        awt=awt+waiting[i];
    cout<<"- Average waiting time: "<<awt/5<<"ms"<<endl;
    cout<<endl;
}

void getPPS(int a[],int arrivalTime[], int priority[]){
    cout<<"c. PPS:"<<endl;
    ll a3[6],waiting2[5]={0},time,smallIndex;
    vector<int>seq3,int3;
    c=0;
    int previousIndex=9999;
    for(i=1;i<6;i++)
    {
        a3[i]=a[i];
    }
    for(time=0; c!=5; time++) // checking every time
    {
        p=9999;
        for(i=1; i<6; i++)
        {                       // if process arrives and its not finished yet
            if(arrivalTime[i-1]<=time && priority[i-1]<p && a3[i]>0 ){
                smallIndex=i;   //get lowest priority index
                p=priority[i-1];//get the priority
            }
        }
        if(smallIndex!=previousIndex){ // if current index and previous index does not match
            seq3.push_back(smallIndex); //smallIndex to sequence
            int3.push_back(time);      //time to interval
        }
        a3[smallIndex]--;
        for(i=1; i<6; i++)
        {
            if(arrivalTime[i-1]<=time && i!=smallIndex && a3[i]>0 )
                waiting2[i-1]++;  //if process is available and not finished, other than the current
        }                         //index, they are in waiting list
        if(a3[smallIndex]==0)
            c++;
        previousIndex=smallIndex;
    }
    cout<<"- Sequence: [";
    for(i=0;i<seq3.size();i++){
        cout<<seq3[i];
        if(i!=seq3.size()-1)
            cout<<", ";
        else
            cout<<"]"<<endl;
    }
    cout<<"- Intervals: [";
    for(i=0;i<int3.size();i++)
        cout<<int3[i]<<", ";
    cout<<time<<"]"<<endl;
    float awt=0;
    for(i=0;i<5;i++)
        awt=awt+waiting2[i];
    cout<<"- Average waiting time: "<<awt/5<<"ms"<<endl;
    cout<<endl;
}
void getRR(int cpuBurst[],int a[],int arrivalTime[],int priority[]){
    cout<<"d. RR [All process arrive at 0]:"<<endl;
    vector<int>seq4,int4;
    int q=ceil(a[1]*0.5+cpuBurst[0]*0.5),m,waiting4[5]={0}; //Value of Q
    c=0;
    int s=0;
    float awt=0;
    int4.push_back(s); //inital value of interval
    cout<<"- Quantum (Q): "<<q<<endl;
    for(i=1;c!=5&&a[i]>0; i++){
        m=min(q,a[i]); //minimum of Q and CPU burst
        a[i]=a[i]-m;
        s=s+m;
        awt=awt+(5-c-1)*m;
        //cout<<awt<<" "<<c<<" "<<endl;
        if(a[i]==0)
            c++;
        seq4.push_back(i);
        int4.push_back(s);
        if(i==5)
            i=0;
    }
    cout<<"- Sequence: [";
    for(i=0;i<seq4.size();i++){
        cout<<seq4[i];
        if(i!=seq4.size()-1)
            cout<<", ";
        else
            cout<<"]"<<endl;
    }
    cout<<"- Intervals: [";
    for(i=0;i<int4.size();i++){
        cout<<int4[i];
        if(i!=int4.size()-1)
            cout<<", ";
        else
            cout<<"]"<<endl;
    }
    cout<<"- Average waiting time: "<<awt/5<<"ms"<<endl;
    cout<<endl;
}
int main()
{
    float alpha=0.5;
    int cpuBurst[5],arrivalTime[5],priority[5];
    cout<<"ID: ";
    cin>>n;
    cout<<"Given CPU burst: ";
    for(i=0; i<5; i++)
        cin>>cpuBurst[i];
    cout<<"Arrival times: ";
    for(i=0; i<5; i++)
        cin>>arrivalTime[i];
    cout<<"Process priority: ";
    for(i=0; i<5; i++)
        cin>>priority[i];


    //get predicted burst
    int a[6];
    a[0]=n;
    for(i=1; i<6; i++)
    {
        a[i]=ceil( a[i-1]*alpha+cpuBurst[i-1]*(1-alpha)); //predicted burst formula
    }
    cout<<"Predicted burst: [";
    for(i=1; i<6; i++)
    {
        cout<<a[i];
        if(i!=5)
            cout<<", ";
        else
            cout<<"]"<<endl;
    }
    cout<<endl;

    //sjf
    getSJF(a);

    //srtf
    getSRTF(a,arrivalTime);

    //pps
    getPPS(a,arrivalTime,priority);

    //rr
    getRR(cpuBurst,a,arrivalTime,priority);
    return 0;
}


