#include <iostream>
using namespace std;

int main() {
    int n, m;

    // Input the number of processes and resource types
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resource types: ";
    cin >> m;

    int alloc[n][m];       // Allocation Matrix
    int max[n][m];         // Max Matrix
    int avail[m];          // Available Resources
    int need[n][m];        // Need Matrix
    int f[n] = {0};        // Flag for finished processes
    int ans[n];            // To store the safe sequence

    // Input the Allocation Matrix
    cout << "Enter the Allocation Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "Allocation of P" << i << " for R" << j << ": ";
            cin >> alloc[i][j];
        }
    }

    // Input the Max Matrix
    cout << "Enter the Max Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "Max of P" << i << " for R" << j << ": ";
            cin >> max[i][j];
        }
    }

    // Input the Available Resources
    cout << "Enter the Available resources:\n";
    for (int j = 0; j < m; j++) {
        cout << "Available of R" << j << ": ";
        cin >> avail[j];
    }

    // Calculate the Need Matrix (Need = Max - Allocation)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Safety Algorithm to find the safe sequence
    int ind = 0;  // Index for safe sequence
    int y = 0;
    
    // Safety Check
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {  // If process i is not finished
                int flag = 0;
                // Check if the process can execute
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                // If the process can execute, add it to the safe sequence
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];  // Release resources
                    }
                    f[i] = 1;  // Mark process as finished
                }
            }
        }
    }

    // Check if the system is in a safe state
    bool safe = true;
    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            safe = false;  // Not all processes finished
            cout << "The system is not in a safe state.\n";
            break;
        }
    }

    if (safe) {
        cout << "The system is in a safe state.\n";
        cout << "Following is the SAFE Sequence: ";
        for (int i = 0; i < n - 1; i++) {
            cout << "P" << ans[i] << " -> ";
        }
        cout << "P" << ans[n - 1] << endl;
    }

    return 0;
}
