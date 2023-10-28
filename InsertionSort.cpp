#include<bits/stdc++.h>
using namespace std;


// void insertionSort(int arr[], int n) {
//     int i = 0, j = 0;
//     for(int i = 1; i < n; i ++) {
//         j = i-1;
//         int k = arr[i];
//         while(j >= 0 && arr[j] > k) {
//             arr[j+1] = arr[j];
//             j--;
//         }
//         arr[j+1] = k;
//     }
// }

void insertionSort(int arr[], int n, int incr, int &count) {  
    for (int i = incr; i < n; i += incr) {  
        for (int j=i; (j>=incr) && (arr[j] > arr[j-incr]); j-=incr) {    
            int data = arr[j];
            arr[j] = arr[j-incr];
            arr[j-incr] = data;
            count++;
        }   
    }
        
}

int shellSort(int arr[], int n) {
    int count = 0;
    for(int i = n/2; i > 2; i /=2) {
        cout << i << endl;
        for(int j = 0; j < i; j++) {
            insertionSort(&arr[j], n-j, i, count);
        }
    }
    insertionSort(arr, n, 1, count);
    return count;
}




int main() {
    // int arr[8] = {1,2,3,4,5,6,7,8};
    // cout << shellSort(arr, 8) << endl;
    // for(int i = 0; i < 8; i++) cout << arr[i] << " ";

    return 0;
}