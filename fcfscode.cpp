#include<iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

// Driver code
int main(){
    srand (time(NULL));
    int processes[] = {1, 2, 3};
    int n = 7;//random number between 0-99
    int burst_time[] = {rand()%100, rand()%100, rand()%100};
    int arrival_time[] = {rand()%1000, rand()%1000, rand()%1000};
    calcAvgTime(processes, n, burst_time, arrival_time);
    return 0;
}

 // Function to calculate average waiting and turn-around
// times.
void calcAvgTime(int processes[], int n, int burstTime[], int accessTime[]){
    int waitTime[n], turnAroundTime[n];
 
    // Function to find waiting time of all processes
    calcWaitingTime(processes, n, burstTime, waitTime, accessTime);
 
    // Function to find turn around time for all processes
    calcTurnAroundTime(processes, n, burstTime, waitTime, turnAroundTime);
 
    // Display processes along with all details
    cout << "Processes " << " Burst Time " << " Arrival Time "
         << " Waiting Time " << " Turn-Around Time "
         << " Completion Time \n";
    int totalWaitTime = 0, totalTurnAroundTime = 0;
    for (int i = 0 ; i < n ; i++)
    {
        totalWaitTime = totalWaitTime + waitTime[i];
        totalTurnAroundTime = totalTurnAroundTime + turnAroundTime[i];
        int completionTime = turnAroundTime[i] + accessTime[i];
        cout << " " << i+1 << "\t\t" << burstTime[i] << "\t\t"
             << accessTime[i] << "\t\t" << waitTime[i] << "\t\t "
             << turnAroundTime[i]  <<  "\t\t " << completionTime << endl;
    }
 
    cout << "Average waiting time = "
         << (float)totalWaitTime / (float)n;
    cout << "\nAverage turn around time = "
         << (float)totalTurnAroundTime / (float)n;
}
 

// Function to find the waiting time for all processes
void calcWaitTime(int processes[], int n, int burstTime[], int waitTime[], int accessTime[]){
    int serviceTime[n];
    serviceTime[0] = 0;
    waitTime[0] = 0;
 
    // calculating waiting time
    for (int i = 1; i < n ; i++){
        // Add burst time of previous processes
        serviceTime[i] = serviceTime[i-1] + burstTime[i-1];
 
        // Find waiting time for current process =
        // sum - at[i]
        waitTime[i] = serviceTime[i] - accessTime[i];
 
        // If waiting time for a process is in negative
        // that means it is already in the ready queue
        // before CPU becomes idle so its waiting time is 0
        if (waitTime[i] < 0) waitTime[i] = 0;
    }
}
 
// Function to calculate turn around time
void calcTurnAroundTime(int processes[], int n, int burstTime[], int waitTime[], int turnAroundTime[]){
    // Calculating turnaround time by adding burstTime[i] + waitTime[i]
    for (int i = 0; i < n ; i++)
        turnAroundTime[i] = burstTime[i] + waitTime[i];
}
 