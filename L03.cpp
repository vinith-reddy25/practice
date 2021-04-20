#include<iostream>
#include<queue>
using namespace std;
#define MAX 300
int q[MAX];
int rear = - 1;
int front = - 1;
int m=0,p=0,tree=0,cross=0,t=0,time_clk=0;
void push(int add_item)
{ // To push or add elements into queue
    if (rear == MAX - 1){
    cout<<"Queue is FULL"<<endl;
    }
    else
    {
        if (front == - 1){
        front++;  // Here front is increased.
        }
        rear++;
        q[rear] = add_item;  // Item added.
    }
}

void pop()
{   // To pop or delete elements.
    if (front == - 1 || front > rear)
    {
        cout<<"Queue is EMPTY"<<endl;
        return ;
    }
    else
    {
        front++;
        if(front > rear){
            int aa=-1;
            front= aa;
            rear=aa;}
    }
}

int empty()
{  // To check is queue is empty or not
    if(front==-1 && rear==-1){
        return 1;
    }
    return 0;
}

void make_graph(vector<int>A[],int N)
{  // To create a graph
     int i,j,k;
     p=0;
     if(m==0){
          i=0;    
    while(i<N)
    {
        j=0;
       while(j<N){
            cin>>k;
            if(k==1)
            {
                A[i].push_back(j); 

            }
            j++;
        }
        i++;
    }
     }
     if(m==1){
         i=0;
    while(i<N)
    {
         j=0;
       while(j<N) 
        {
            {
                cin>>k;
                A[i].push_back(k);
                if(k<0)
                    {p=-1;}
            }
           j++;
        }
         i++;
    }
     }
}

void BFS_graph(int N,int D,int s){
    s=s-1;char o;
    int A[N][N];
       int k;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>k;
            A[i][j]=k;
        }
    }
    char aar[10];

    char colour[N];
    for(int ctr=0;ctr<N;ctr++){
        colour[ctr]='w';
        }
    colour[s]='g';
    int node_count_distance[N];
    for(int i=0;i<N;i++){
        node_count_distance[i]=0;
        }

int parent[N];
    for(int i=0;i<N;i++){
        parent[i]=-1;
    }
     int curr_distance=0,level_count=1,curr_count=0;
    int tree=0,back=0,cross=0;
    push(s);
if(D==1) {  
    while(!empty()){
        int present=q[front];
        pop();
        colour[present]='b';
        curr_count++;
        for(int i=0;i<N;i++){
            if (A[present][i]==1){
                if(colour[i]=='w'){
                    parent[i]=present;
                       push(i);
                    colour[i]='g';
                    tree++;
                    node_count_distance[curr_distance]++;
                }
                else if(colour[i]=='g')
                    cross++;
                else if(colour[i]=='b'){
                    int par=parent[present];
                    while(par!=i && par!=-1)
                        par=parent[par];
                    if(par==i){
                        back++;}
                    else{
                        cross++;}
                }
            }
        }
        if(curr_count==level_count){
            curr_count=0;
            level_count=node_count_distance[curr_distance];
            curr_distance++;
        }

    }

    
    for(int i=0;node_count_distance[i]!=0;i++){
        printf("%d ",node_count_distance[i]);
    }

    printf("%d ",0);
    printf("%d %d %d %d\n",tree,back,0,cross);
}
else{
    while(!empty()){
        int present=q[front];
        pop();
        colour[present]='b';
        curr_count++;
        int ctr1=0;
        for(int i=0;i<N;i++){
            if (A[present][i]==1){
                if(colour[i]=='w'){
                    push(i);
                  colour[i]='g';
                    tree++;
                    node_count_distance[curr_distance]++;
                    A[present][i]=0;
                    A[i][present]=0;
                }
                else if(colour[i]=='g'){
                    cross++;
                    A[present][i]=0;
                    A[i][present]=0;
                }
                else if(colour[i]=='b'){
                    back++;
                    A[present][i]=0;
                    A[i][present]=0;
                }
            }
        }
        if(curr_count==level_count){
            curr_count=0;
            level_count=node_count_distance[curr_distance];
            curr_distance++;
        }
    }
    int ctr=0;
    for(int i=0;node_count_distance[i]!=0;i++){
        printf("%d ",node_count_distance[i]);
    }

    printf("%d ",0);
    printf("%d %d\n",tree,back+cross);
        }
}



int dfs_forcyclic(vector<int>A[],int N,vector<int>&visited,int j,int ss)
{
    visited[j]=1;
    int i;
    for(i=0;i<A[j].size();i++)
    {   ss=0;
        if(visited[A[j][i]]==0 && ss==0)
        {
            if (dfs_forcyclic(A,N,visited,A[j][i],ss)){
            return 1; }
        }
    }
    return 0;
}


void topological_print(vector<int>A[],vector<int>&degree,int N)
{
      int i,k,s=0,ss=0;
       vector<int>visited;
       int ff=0;
       visited.assign(N,0);

       for(int i=0;i<N;i++)
    {      ff=0;
        if(visited[i]==0 && ff==0)
        {
            if(dfs_forcyclic(A,N,visited,i,ss)){
            s=1;
            }
        }
    }
    if(s==1)
    {
        cout<<"-1";return;
    }
    else{
        s=0;
    }
    if(s==0){
        while(!empty()){
        pop();
    }
    }
    int check[N];
    for(i=0;i<N;i++){
        check[i]=0;
    }
    for(i=0;i<N;i++)
    {
        if(degree[i]==0){ s=0;  push(i);
         check[i]=1;  
           break;
         }
    }
      

    while(!empty())
    {
         k=q[front];int l;
        l=q[front],k++;l++;
        cout<<k<<" ";
          k--;l--;
          pop();
        for(int i=0;i<A[k].size();i++)
        {
            degree[A[k][i]]=degree[A[k][i]]-1;
        }
        for(i=0;i<N;i++)
          {
        if(degree[i]==0 && check[i]==0){ s=0;  push(i);
           check[i]=1;
           break;}
          }
    }
}



void dfs_fortime(vector<int>A[],int N,int visited[],int str_time[],int fin_time[],int i,int ss)
{
    visited[i]=1;
    time_clk=time_clk+1;
    str_time[i]=time_clk;
    for(int j=0;j<A[i].size();j++)
    {  ss=0;
        if(visited[A[i][j]]==0)
           {t=t+1;
           dfs_fortime(A,N,visited,str_time,fin_time,A[i][j],ss);}
    }
    time_clk=time_clk+1;
    fin_time[i]=time_clk;
}

void dfs_Time(vector<int>A[],int N,int D,int L)
{
    int visited[N];
    int str_time[N];
    int fin_time[N],ss=0;time_clk=0;t=0;
   int i=0;
   while(i<N)
    {
        visited[i]=0;str_time[i]=0;
        fin_time[i]=0;
         i++;
    }

    dfs_fortime(A,N,visited,str_time,fin_time,L,ss);
    cout<<fin_time[L]<<" ";
    if(D==1){ 
      int f=0,be=0,cc=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<A[i].size();j++)
        { int u=i,v=A[i][j];
            if(str_time[u]<str_time[v] && str_time[v]<fin_time[v]){
                if(fin_time[v]<fin_time[u]){
                f++;}}
            if(str_time[v]<str_time[u]  && fin_time[u] < fin_time[v]){
                if(str_time[u]< fin_time[u]){
                be++;}
                }
            if(str_time[v] < fin_time[v] && str_time[u] < fin_time[u]){
                if(fin_time[v]<str_time[u]){
                cc++; }  }
        }
    }
    cout<<t<<" ";
    cout<<be<<" ";
    cout<<f-t<<" ";
    cout<<cc<<endl;
    }
    else
    {
        cout<<t<<" ";int total=0;
         for(int i=0;i<N;i++)
       {
        for(int j=0;j<A[i].size();j++)
        {
            total=total+1;
        }
       }
       cout<<total/2-t<<endl;
    }
}


void dijkstra_print(vector<int>A[],int N,int L)
{
    vector<int>dis;int s=1;
    if(s==1){
    dis.assign(N,999999);
    }
    vector<int>vis(N,0);
    dis[L]=0;
    for(int i=0;i<N;i++)
    {
          int min=1000000;
          int u;
    for(int j=0;j<dis.size();j++)
    {
        if(vis[j]==0)
        {
            if(min>=dis[j] && vis[j]==0)
            {
              min=dis[j];
              u=j;
            }
        }
    }

            vis[u]=1;
   for (int v = 0; v < A[u].size(); v++)
    {       if (!vis[v] && A[u][v]!=999999 &&A[u][v]&& dis[u] != 999999 && dis[u] + A[u][v] < dis[v] ){
                  if(A[u][v]){
                     if(!vis[v] && A[u][v]+dis[u]<dis[v]){
                dis[v] = dis[u] + A[u][v];}}}                
    }
    }
     int i=0;
     while(i<N)
    {
        cout<<dis[i]<<" ";
        i++;
        }
}

 vector<vector<int>> func(vector<vector<int>> V, int n)
 {
      for(int i=0;i<n;i++){
       for(int j=0;j<n;j++){
         cin>>V[i][j];}}
    return V;
 }

void bellmanFord_print(int N, int D, int S)
{
   
    vector<vector <int> > vt(N,vector<int>(N,0));
    vt =  func(vt,N);
    int dis[N],i=0; 
    while(i<N)
    { 
        dis[i] = 999999;
        i++; 
    }
    dis[S-1] = 0;
    int count=0;
    int mod=0;
    for (int i = 0; i < N - 1; i++) 
    { 
     for (int j = 0; j < N; j++) 
     { 
        for(int k=0;k<N;k++)
            if(vt[j][k]!=999999)
            if (dis[j] + vt[j][k] < dis[k]) 
            {
               dis[k] = dis[j] + vt[j][k]; 
                  mod=mod+1;}
                  count=count+1;
        } 
    } 
    for (int i = 0; i < N; i++) 
    { 
        for(int j=0;j<N;j++){
        if(vt[i][j]!=999999){
        if ( dis[i] + vt[i][j] < dis[j]) {

            cout << -1 << endl; 
                 return;
                 }}
                 }
    } 
    i=0;
    while(i<N){
        cout << dis[i] << " "; 
        i++;
         }
        cout<<count<<" "<<mod/2 + 1 <<endl;   
}



int main()
{
    int i,test;
    cin>>test;
    for(i=0;i<test;i++)
    {
        int input;cin>>input;
        int N,D,S;
        if(input==1)
        {
            
            cin>>N>>D>>S;
            m=0;
            BFS_graph(N,D,S);
        }
        else if(input==2)
        {
             cin>>N>>D>>S;vector<int> A[N];
              m=0;
              make_graph(A,N);
              dfs_Time(A,N,D,S-1);
        }
        else if(input==3)
        {
            cin>>N;
             vector<int> A[N];vector<int>degree;
                   degree.assign(N,0);
                    int i,j,k;
             for(i=0;i<N;i++)
              {
             for(j=0;j<N;j++)
             {
               cin>>k;
                if(k==1)
               {
                  A[i].push_back(j);
                 degree[j]++;
               }
             }
              }
           
            topological_print(A,degree,N);
            cout<<endl;

        }
        else if(input==4)
        {
            cin>>N>>D>>S;
            vector<int>A[N];
             m=1;
            make_graph(A,N);
            if(p==-1){cout<<"-1";
                cout<<endl;
                continue;}
            dijkstra_print(A,N,S-1);
            cout<<endl;
        }
        else if(input==5)
        {
             int N,D,S;
         cin >> N >> D >> S;
            bellmanFord_print(N,D,S);cout<<endl; 
        }
    }
}
