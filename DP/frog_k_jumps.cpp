/*
    Frog can jump upto k indexes at a time, i.e i -> i+1, i+2 .., i+k
    Find min energy required to reach the end.
    Energy req = abs(ar[j] - ar[i]), where i is current index and j is index to which frog has jumped
*/ 

#include<iostream>
using namespace std;

// Recursive approach
int min_energy_req(int ar[], int idx, int k){
    if(idx == 0)    return 0;
    int min_energy = INT_MAX;
    for(int i = 1; i<=k; i++){
        if(idx - i >= 0){
            int energy = min_energy_req(ar, idx-i, k);
            min_energy = min(energy, min_energy);
        }
    }
    return min_energy;
}


// Memoized approach
int min_energy_req(int ar[], int idx, int k){
    if(idx == 0)    return 0;
    int min_energy = INT_MAX;
    for(int i = 1; i<=k; i++){
        if(idx - i >= 0){
            int energy = min_energy_req(ar, idx-i, k);
            min_energy = min(energy, min_energy);
        }
    }
    return min_energy;
}

int main(){
    int ar[] = {10, 20, 30, 10, 30};
    int k;
    int n = sizeof(ar) / sizeof(ar[0]);
    vector<int> dp(n, 0);
    cout << min_energy_req(ar, n, k);
    return 0;
}

