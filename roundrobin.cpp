#include <iostream>
using namespace std;
struct Process
{
    int processid;
    int arrivalTime;
    int executionTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};
void calculateTimes(Process processes[], int n, int quantum)
{
    int *remainingTime = new int[n];
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = processes[i].executionTime;
    }
    int currentTime = 0;
    bool allDone = false;
    while (!allDone)
    {
        allDone = true;
        for (int i = 0; i < n; i++)
        {
            if (remainingTime[i] > 0)
            {
                allDone = false;
                if (remainingTime[i] > quantum)
                {
                    currentTime = currentTime + quantum;
                    remainingTime[i] = remainingTime[i] - quantum;
                }
                else
                {
                    currentTime = currentTime + remainingTime[i];
                    processes[i].completionTime = currentTime;
                    remainingTime[i] = 0;
                }
            }
        }
    }
}
void printaddress(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "--------------------------------------------------------------------"
                "----------------------\n";
        cout << "Current Resource Address: \n"
             << &processes[i] << endl;
        cout << "--------------------------------------------------------------------"
                "----------------------\n";
        cout << "Next Resource Address: \n"
             << &processes[i + 1] << endl;
        cout << "--------------------------------------------------------------------"
                "----------------------\n";
    }
}
void calculateTurnaroundTime(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
        processes[i].turnaroundTime =
            processes[i].completionTime - processes[i].arrivalTime;
}

void calculateWaitingTime(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
        processes[i].waitingTime =
            processes[i].turnaroundTime - processes[i].executionTime;
}

void printTable(Process processes[], int n)
{
    cout << "--------------------------------------------------------------------"
            "----------------------\n";
    cout << "| Process | Arrival Time | Execution Time | Completion Time | "
            "Turnaround Time | Waiting Time \n";
    cout << "--------------------------------------------------------------------"
            "----------------------\n";
    for (int i = 0; i < n; i++)
    {
        cout << "|    " << processes[i].processid << "    |      "
             << processes[i].arrivalTime << "      |     " << processes[i].executionTime
             << "     |        " << processes[i].completionTime
             << "        |        " << processes[i].turnaroundTime
             << "         |      " << processes[i].waitingTime << " |\n";
    }
    cout << "--------------------------------------------------------------------"
            "----------------------\n";
}
int main()
{
    int n, quantum;
    cout << "Enter The Number of Process: \n";
    cin >> n;
    cout << "Enter The  Quantum Size: \n";
    cin >> quantum;

    Process *processes = new Process[n];
    cout << "Enter process details: \n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << ":\n";
        processes[i].processid = i + 1;
        cout << "   Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "   Execution Time: ";
        cin >> processes[i].executionTime;
    }

    calculateTimes(processes, n, quantum);
    calculateTurnaroundTime(processes, n);
    calculateWaitingTime(processes, n);
    cout << "\nRound Robin Scheduling Results:\n";
    printTable(processes, n);
    printaddress(processes, n);

    return 0;
}