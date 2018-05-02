// FCFS Scheduling Algorithm
#include<iostream>
#include <stdio.h>      
#include <stdlib.h>
#include <time.h>  
using namespace std;


//waittime = startime[n+1] - arrival
//turnaroundtime = waittime + bursttime


void findWaitTime(int n, int burstTime[], int waitTime[], int arrivalTime[]);
void findTurnaroundTime(int turnaroundTime[], int waitTime[],int burstTime[], int n);
int findAvgWaitTime(int waitTime[], int n);
int findAvgTurnaroundTime(int turnaroundTime[], int n);
void swap(int* a, int* b);
int partition (int arr1[], int arr2[], int arr3[], int low, int high);
void quickSort(int arr1[], int arr2[], int arr3[], int low, int high);

int main(){
    int process_size[] = {50, 100, 500};
    cout<<"N \t\tRun number\t\tAvg. waiting time\t\tAvg. turnaround time"<<endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 5; j++){
            int amount = process_size[i];
            srand (j);
            int processes[amount];
            int burstTime[amount];
            int arrivalTime[amount];
            int waitTime[amount];
            int turnaroundTime[amount];
            int avgWaitTime = 0;
            int avgTurnaroundTime = 0;
            for(int i = 0; i < amount; i++){
                processes[i] = i+1;
                burstTime[i] = rand() % 100 +1;
                arrivalTime[i] = rand() % 1000 +1;
            }
            quickSort(arrivalTime, burstTime, processes, 0, amount-1);
            cout<<amount<<"\t\t"<<j+1<<"\t\t\t\t";
            findWaitTime(amount, burstTime, waitTime, arrivalTime);
            findTurnaroundTime(turnaroundTime, waitTime, burstTime, amount);
            avgWaitTime = findAvgWaitTime(waitTime, amount);
            avgTurnaroundTime = findAvgTurnaroundTime(turnaroundTime, amount);
            if(amount==50)
                cout<<(float)avgWaitTime<<"\t\t\t\t\t\t"<<(float)avgTurnaroundTime<<endl;
            else
                cout<<(float)avgWaitTime<<"\t\t\t\t\t"<<(float)avgTurnaroundTime<<endl;
        }
    }
    return 0;
}

void findWaitTime(int n, int burstTime[], int waitTime[], int arrivalTime[]){
    int startTime[n];
    startTime[0]=arrivalTime[0];
    waitTime[0]=0;
    for (int i = 1; i < n; ++i){
        if (arrivalTime[i]<startTime[i-1]+burstTime[i-1]){
            startTime[i]=startTime[i-1]+burstTime[i-1];
            waitTime[i]=startTime[i]-arrivalTime[i];
        }
        else{
            startTime[i]=arrivalTime[i];
            waitTime[i]=0;
        }
    }
}

void findTurnaroundTime(int turnaroundTime[], int waitTime[],int burstTime[], int n){
    for (int i = 0; i < n; ++i){
        turnaroundTime[i]=waitTime[i] + burstTime[i];
    }
}

int findAvgWaitTime(int waitTime[], int n){
    int sum = 0;
    int average = 0;
    for (int i = 0; i < n; i++) {
        sum += waitTime[i];
    }
    return average = sum/n;
}

int findAvgTurnaroundTime(int turnaroundTime[], int n){
    int sum = 0;
    int average = 0;
    for (int i = 0; i < n; i++) {
        sum += turnaroundTime[i];
    }
    return average = sum/n;
}

void swap(int* i, int* j){
    int temp = *i;
    *i = *j;
    *j = temp;
}

int partition (int arr1[], int arr2[], int arr3[], int low, int high){
    int piv = arr1[high]; 
    int i = (low - 1);  
    for (int j = low; j <= high- 1; j++){
        if (arr1[j] <= piv){
            i++; 
            swap(&arr1[i], &arr1[j]);
            swap(&arr2[i], &arr2[j]);
            swap(&arr3[i], &arr3[j]);
        }
    }
    swap(&arr1[i + 1], &arr1[high]);
    swap(&arr2[i + 1], &arr2[high]);
    swap(&arr3[i + 1], &arr3[high]);

    return (i + 1);
}

void quickSort(int arr1[], int arr2[], int arr3[], int low, int high){
    if (low < high){
        int pi = partition(arr1, arr2, arr3, low, high);
        quickSort(arr1, arr2, arr3, low, pi - 1);
        quickSort(arr1, arr2, arr3, pi + 1, high);
    }
}