#include <iostream>

#include <vector>

using namespace std;



const int MAX = 100;



double cost[MAX][MAX];

int root[MAX][MAX];



// Function to compute sum of probabilities from i to j

double sum(const vector<double>& p, int i, int j) {

    double total = 0;

    for (int k = i; k <= j; ++k)

        total += p[k];

    return total;

}



// Function to build the optimal BST

void optimalBST(const vector<double>& p, int n) {

    for (int i = 0; i < n; ++i) {

        cost[i][i] = p[i];

        root[i][i] = i;

    }



    for (int l = 2; l <= n; ++l) {

        for (int i = 0; i <= n - l; ++i) {

            int j = i + l - 1;



            // Initialize with the cost when the leftmost key is root

            double minCost = 0;

            if (i < j)

                minCost = cost[i + 1][j];

            minCost += sum(p, i, j);

            cost[i][j] = minCost;

            root[i][j] = i;



            // Try all other possible roots

            for (int r = i + 1; r <= j; ++r) {

                double c = 0;

                if (r > i) c += cost[i][r - 1];

                if (r < j) c += cost[r + 1][j];

                c += sum(p, i, j);



                if (c < cost[i][j]) {

                    cost[i][j] = c;

                    root[i][j] = r;

                }

            }

        }

    }



    cout << "Minimum cost of Optimal BST: " << cost[0][n - 1] << endl;

}



// Function to print the structure of the tree

void printTree(int i, int j, int parent, bool isLeft, const vector<int>& keys) {

    if (i > j) return;

    int r = root[i][j];

    if (parent == -1)

        cout << "Root: " << keys[r] << endl;

    else if (isLeft)

        cout << "Left child of " << keys[parent] << ": " << keys[r] << endl;

    else

        cout << "Right child of " << keys[parent] << ": " << keys[r] << endl;



    printTree(i, r - 1, r, true, keys);

    printTree(r + 1, j, r, false, keys);

}



int main() {

    int n;

    cout << "Enter number of keys: ";

    cin >> n;



    vector<int> keys(n);

    vector<double> probs(n);



    cout << "Enter " << n << " sorted keys:\n";

    for (int i = 0; i < n; ++i)

        cin >> keys[i];



    cout << "Enter " << n << " search probabilities:\n";

    for (int i = 0; i < n; ++i)

        cin >> probs[i];



    optimalBST(probs, n);



    cout << "\nStructure of Optimal BST:\n";

    printTree(0, n - 1, -1, false, keys);



    return 0;

}

