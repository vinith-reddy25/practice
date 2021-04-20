#include<bits/stdc++.h>

using namespace std;

int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   int t,n,j;
   cin>>t;
   while(t--){
     cin>>n;
     pair<int,int> arr[2*n];
     for(int i=0;i<2*n;i++){
       cin>>j;
       arr[i].second = j;
       if(j%2==0){arr[i].first = 0;}
       else{arr[i].first = 1;}
     }
     if(n==2){cout<<arr[0].second<<" "<<arr[1].second<<"\n"; continue;}
     sort(arr,arr+2*n);
    
     for(int i=0,k=0; k<(n-1);i++){
         if(arr[i].first==arr[i+1].first){
       cout<<arr[i].second<<" "<<arr[i+1].second; k++; i++;
       if(t==0 && k==n-1){continue;} cout<<"\n";
         }
     }
   }
  return 0;
}