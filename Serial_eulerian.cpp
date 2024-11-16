#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Node{
    int e1;
    int e2;
    int rank;
    Node* next;
};
void printMap(const std::map<std::pair<int, int>, std::pair<int, int>>& edgeSuccessors) {
    for (const auto& entry : edgeSuccessors) {
        const auto& key = entry.first;
        const auto& value = entry.second;

        std::cout << "Key (" << key.first << ", " << key.second << ") -> Value ("
                  << value.first << ", " << value.second << ")\n";
    }
}

// Function to convert an adjacency list to CSR format
void adjacencyListToCSR(const vector<vector<int>>& adjList, vector<int>& row, vector<int>& col) {
    row.push_back(0); // Start the row index with 0
    for (const auto& neighbors : adjList) {
        row.push_back(row.back() + neighbors.size());
        for (int neighbor : neighbors) {
            col.push_back(neighbor);
        }
    }
}
void addNode(Node*& head, Node* temp) {
    if (head == nullptr) {
        head = temp;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = temp;
    }
}
int main() {
    int n = 8; // Number of nodes in the tree
    vector<vector<int>> adjList(n);

    // Adding edges to the tree
    adjList[0] = {1, 2, 7};
    adjList[1] = {0, 3, 4};
    adjList[2] = {0, 5, 6};
    adjList[3] = {1};
    adjList[4] = {1};
    adjList[5] = {2};
    adjList[6] = {2};
    adjList[7] = {0};

    int root = 0; // Specified root node

    // Converting adjacency list to CSR format


    vector<int> row, col;
    adjacencyListToCSR(adjList, row, col);

    Node* head=nullptr;
    map<pair<int, int>,pair<int, int>> succ;
    pair<int,int> temp1,temp2;
    int temp;



    for(int i=0;i<n;i++)
    {
        for(int j=row[i];j<row[i+1];j++)
        {
            temp1.first=i;
            temp1.second=col[j];

            temp2.first=col[j];
            if(row[col[j]]+1!=row[col[j]+1])
            {
                temp=row[col[j]]+1;
                while(col[temp]==i)
                {
                    temp++;
                }
                temp2.second=col[temp];
                if(i==col[row[col[j]+1]-1])
                {
                    //printf("hi i =%d\t val=%d\t",i,col[row[col[j]]]);
                   temp2.second=col[row[col[j]]];
                   
                }

            }
            else
            {
                temp2.second=i;
            }
            succ[temp1]=temp2;
            //cout << "(" << temp1.first << "," << temp1.second  << ")" << "(" << temp2.first << "," << temp2.second << ")" << "for i="<< i << "j="<<j <<"Temp"<< temp << endl;
        }
    }
   printMap(succ);
        cout << "Linked List Representation:" << endl;
    // Node* current = head;
    // while (current) {
    //     cout << "(" << current->e1 << ", " << current->e2 << ", " << current->rank << ") -> ";
    //     current = current->next;
    // }
    // cout << "nullptr" << endl;


    // Output CSR format
    cout << "CSR Format:" << endl;
    cout << "Row: ";
    for (int val : row) cout << val << " ";
    cout << endl;

    cout << "Col: ";
    for (int val : col) cout << val << " ";
    cout << endl;

    cout << "Root node: " << root << endl;

    return 0;
}
