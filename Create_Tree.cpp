#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int find(int parent[], int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent, parent[x]);
}

void unite(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

void createCSR(int N,int arr1[],int arr2[],int edgeCount)
{
    int row[N];
    for (int i = 0; i < N+1; i++) {
    row[i] = 0;
    }

    for (int i = 0; i < 2*N-1; i++){
        row[arr1[i]]++;

    } cout<<"Rows " << endl;

    for (int i = 0; i <N; i++){
        printf("%d ",row[i]++);

    }cout << endl;
    
}

void generateCSR(int N, int arr1[], int arr2[], int edgeCount) {
    int* edge_start = new int[N + 1](); 
    int* edge_numbers = new int[edgeCount]; 


    for (int i = 0; i < edgeCount; i++) {
        edge_start[arr1[i]+1]++; 
    }

    cout << "Start Arrays " << endl;
    for (int i = 0; i < edgeCount; i++) {
        printf("%d ",edge_start[i]); 
    }
    cout << endl;


    for (int i = 1; i <= N; i++) {
        edge_start[i] += edge_start[i - 1];
    }

    // Temporary array to track positions within each vertex's range
    int* temp = new int[N]();
    for (int i = 0; i < edgeCount; i++) {
        int parent = arr1[i];
        int pos = edge_start[parent] + temp[parent];
        edge_numbers[pos] = i; // Insert edge index
        temp[parent]++;
    }

    delete[] temp;

    // Output the CSR representation (only edge numbers)
    cout << "CSR Representation (Edge Numbers Only):" << endl;
    cout << "edge_start: ";
    for (int i = 0; i <= N; i++) {
        cout << edge_start[i] << " ";
    }
    cout << endl;

    cout << "edge_numbers: ";
    for (int i = 0; i < edgeCount; i++) {
        cout << edge_numbers[i] << " ";
    }
    cout << endl;

    // Clean up
    delete[] edge_start;
    delete[] edge_numbers;
}



void generateTree(int N, int root) {


    int* arr1 = new int[2*(N - 1)];          
    int* arr2 = new int[2*(N - 1)];
    int* parentArray = new int[N]; 
    int* parent = new int[N];  
    int* rank = new int[N](); 


    for (int i = 0; i < N; i++) {
        parent[i] = i;
        parentArray[i] = -1;
    }

    srand(time(0));


    int edgeIndex = 0;
    int firstChild = (root + 1) % N;
    arr1[edgeIndex] = root;
    arr2[edgeIndex] = firstChild;
    arr1[edgeIndex+(N-1)] = firstChild;
    arr2[edgeIndex+(N-1)] = root;
    parentArray[firstChild] = root;
    unite(parent, rank, root, firstChild);
    edgeIndex++;


    for (int i = 0; i < N; i++) {
        if (i == root || i == firstChild) continue; 

        int parentVertex = rand() % N;
        while (find(parent, i) == find(parent, parentVertex) || parentArray[i] != -1 || parentVertex == i) {
            parentVertex = rand() % N; 
        }

        arr1[edgeIndex] = parentVertex;
        arr2[edgeIndex] = i;
        arr1[edgeIndex+(N-1)] = i;
        arr2[edgeIndex+(N-1)] = parentVertex;
        parentArray[i] = parentVertex;
        unite(parent, rank, parentVertex, i);
        edgeIndex++;
    }


    cout << "Edge Arrays:" << endl;
    cout << "arr1: ";
    for (int i = 0; i < 2*(N-1); i++) cout << arr1[i] << " ";
    cout << endl;

    cout << "arr2: ";
    for (int i = 0; i < 2*(N - 1); i++) cout << arr2[i] << " ";
    cout << endl;


    cout << "Parent Array (Index represents the node, value represents its parent):" << endl;
    for (int i = 0; i < N; i++) {
        cout << parentArray[i] << " ";
    }
    cout << endl;


    //generateCSR(N, arr1, arr2, N - 1);
    createCSR(N,arr1,arr2,edgeIndex);


}

int main() {
    int N, root;
    cout << "Enter the number of vertices: ";
    cin >> N;
    cout << "Enter the root vertex: ";
    cin >> root;

    generateTree(N, root);

    return 0;
}
