#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    char *a; char* c; char* e;
    char b,d;
    int x,y,z;
    while(t){
      cin>>a; cin>>b; cin>>c; cin>>d; cin>>e;
      cout<<a[0]<<" "<<c[0]<<" "<<e[0]<<" ";
      if(isdigit(a[0]) && isdigit(c[0])){
          sscanf(a, "%d", &x); 
          sscanf(c, "%d", &y);
          z=y+x;
          cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<z;
      }
     else if(isdigit(a[0]) && isdigit(e[0])){
          sscanf(a, "%d", &x); 
          sscanf(e, "%d", &y);
          z=y-x;
          cout<<a<<" "<<b<<" "<<z<<" "<<d<<" "<<e;
      }
     else if(isdigit(e[0]) && isdigit(c[0])){
          sscanf(e, "%d", &x); 
          sscanf(c, "%d", &y);
          z=x-y;
          cout<<z<<" "<<b<<" "<<c<<" "<<d<<" "<<e;
      }
      else{}

        t--;
    }

    return 0;
}