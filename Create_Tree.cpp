#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void checkArrays(int arr1[], int arr2[], int N) {
    int res = 0;
    for (int i = 0; i < N; i++) {
        res = (arr1[i] ^ arr2[i]);
    }

    if (res == 0) {
        cout << "Same" << endl;
    } else {
        cout << "Not Same" << endl;
    }
}
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

void createCSR(int N,int arr1[],int arr2[],int edgeCount,int root,int actual_parent[])
{
    int* vertex= new int [N+2];
    int index,edge1,edge2;
    int* edges = new int[2*edgeCount] ();
    int* final_rank=new int[2*edgeCount] ();


    for (int i = 0; i < N+1; i++) {
    vertex[i] = 0;
    }

    for (int i = 0; i < (2*N)-2; i++){
        vertex[arr1[i]+1]++;

    } 
    //PREFIX SUM BELOW

    for (int i = 1; i < N+1; i++) {
    vertex[i] += vertex[i - 1];
    }

    for (int i = 0; i < 2*edgeCount+2; i++) {
    edges[i] = -1;
    }

    for(int i=0;i<2*N-2;i++)
    {
        index= vertex[arr1[i]];
        while(edges[index]!=-1)
        {
            index++;
        }
        edges[index]=i;
    }
    // cout<<"vertexs " << endl;

    // for (int i = 0; i <N+1; i++){
    //     printf("%d ",vertex[i]);

    // }cout << endl;


    // cout<<"Edges " << endl;

    // for (int i = 0; i <2*edgeCount; i++){
    //     printf("%d ",edges[i]);

    // }cout << endl;



    int* succ = new int[2 * edgeCount](); // Dynamically allocate and initialize to 0
    int vertex_val=1;

    for(int i=0;i<2*edgeCount;i++)
    {
        if(i>=vertex[vertex_val])
        {
            vertex_val++;
        }
        int x=edges[i];
        int succ_val= (x+edgeCount)%((2*edgeCount));
        
        if (i + 1 == vertex[vertex_val]) {
        succ[succ_val] = edges[vertex[vertex_val - 1]];
        //cout << "Succ = " << succ_val << " val= " << edges[vertex[vertex_val - 1]] << " Calculatedby = " << i << " vertex val = " << vertex_val << endl;
        }

         else
        {
            //cout << "Succ = " << succ_val << " val= " << edges[i+1] << "Calculatedby = " << i << endl;
            succ[succ_val]=edges[i+1];
        }
            
        //cout << " "<<succ_val << "=" << edges[i+1] << endl;
    }    

    // cout << endl;cout << endl << "successor " << endl;
    // for(int i=0;i<2*edgeCount;i++)
    // {
    //     cout << " "<< succ[i] ;
    // }
    int prev=edges[vertex[root]];
    final_rank[prev]=0;
    // cout <<endl << "First Child " << root<< "First Edge Number "<<prev<<endl;

    for(int i=1;i<2*edgeCount;i++)
    {
        
        final_rank[succ[prev]]=i;
        prev=succ[prev];
    }

    // cout << endl;cout << endl << "Final Rank " << endl;
    // for(int i=0;i<2*edgeCount;i++)
    // {
    //     cout << " "<< final_rank[i] ;
    // }
    // cout << endl;

    int* parent= new int [N];

    for(int i=0;i<N;i++)
    {
        edge1=i;
        edge2=i+N-1;
        if(final_rank[edge1]<final_rank[edge2])
        {
            parent[arr2[i]]=arr1[i];
        }
        else{
            parent[arr1[i]]=arr2[i];
        }
    }
    parent[root]=-1;

    // cout<< endl << "Parent List After Eulerian" << endl;

    // for (int i = 0; i < N; i++)
    // {
    //     printf("%d ",parent[i]);
    // }
    // cout << endl;

    checkArrays(parent,actual_parent,N);

    //delete[] edges;
    //delete[] final_rank;
    



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


    // cout << "Edge Arrays:" << endl;
    // cout << "arr1: ";
    // for (int i = 0; i < 2*(N-1); i++) cout << arr1[i] << " ";
    // cout << endl;

    // cout << "arr2: ";
    // for (int i = 0; i < 2*(N - 1); i++) cout << arr2[i] << " ";
    // cout << endl;


    // cout << "Parent Array Original" << endl;
    // for (int i = 0; i < N; i++) {
    //     cout << parentArray[i] << " ";
    // }
    // cout << endl;


    //generateCSR(N, arr1, arr2, N - 1);
    createCSR(N,arr1,arr2,edgeIndex,root,parentArray);

    delete[] arr1;
    delete[] arr2;
    delete[] parent;
    delete[] parentArray;
    delete[] rank;


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
