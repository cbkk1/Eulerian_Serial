#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Node1{
    int e1;
    int e2;
    int rank;
    Node1* next;
};

struct Node2{
    int e;
    int rank;
    Node2* next;
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
// void adjacencyListToCSR(const vector<vector<int>>& adjList, vector<int>& row, vector<int>& col) {
//     row.push_back(0); // Start the row index with 0
//     for (const auto& neighbors : adjList) {
//         row.push_back(row.back() + neighbors.size());
//         for (int neighbor : neighbors) {
//             col.push_back(neighbor);
//         }
//     }
// }

void mapEdges(const std::vector<std::vector<int>>& adjList, int* arr1, int* arr2) {
    int no_of_edges = 0;

    // First, count the total number of unique edges
    for (int u = 0; u < adjList.size(); u++) {
        for (int v : adjList[u]) {
            if (u < v) { // Only count each edge once (u < v avoids duplicates)
                no_of_edges++;
            }
        }
    }

    // Assign edges to arr1 and arr2
    int index = 0;
    for (int u = 0; u < adjList.size(); u++) {
        for (int v : adjList[u]) {
            if (u < v) { 
                // Forward edge
                arr1[index] = u;
                arr2[index] = v;

                // Reverse edge
                arr1[index + no_of_edges] = v;
                arr2[index + no_of_edges] = u;

                index++;
            }
        }
    }
}
void addNode2(Node2*& head, Node2* temp) {
    if (head == nullptr) {
        head = temp;
    } else {
        Node2* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = temp;
    }
}

void addNode(Node1*& head, Node1* temp) {
    if (head == nullptr) {
        head = temp;
    } else {
        Node1* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = temp;
    }
}
int main() {
    int no_of_vertex= 8; // Number of nodes in the tree
    int no_of_edges=no_of_vertex-1;
    vector<vector<int>> adjList(no_of_vertex);

    adjList[0] = {1, 2, 7};
    adjList[1] = {0, 3, 4};
    adjList[2] = {0, 5, 6};
    adjList[3] = {1};
    adjList[4] = {1};
    adjList[5] = {2};
    adjList[6] = {2};
    adjList[7] = {0};
    int arr1[2*no_of_edges],arr2[2*no_of_edges];
    int row[no_of_vertex+1];
        mapEdges(adjList,arr1,arr2);
    row[0]=0;

    for(int i=1;i<no_of_edges+2;i++)
    {
        row[i]=row[i-1]+adjList[i-1].size();
    }



    int col[(2*no_of_edges)+1]={-1};

        for(int i=0;i<2*no_of_edges;i++)
    {
        col[i]=-1;
    }
    for(int i=0;i<2*no_of_edges;i++)
    {

        int vertex=arr1[i];
        int offset=row[vertex];

        while(col[offset]!=-1)
        {
            offset++;
        }
        col[offset]=i;
        //col[offset]=(i+no_of_edges)%(2*no_of_edges);


    }
    cout << "Rows " << endl;

    for(int i=0;i<no_of_edges+2;i++)
    {
        cout << " " << row[i];
    }
     cout << endl;

    cout << "Column" << endl;
    for(int i=0;i<2*no_of_edges;i++)
    {
        cout << col[i] << " ";
    }
    cout << endl;

    int succ[2*no_of_edges];
    int row_val=1;

    for(int i=0;i<2*no_of_edges;i++)
    {
        if(i>=row[row_val])
        {
            row_val++;
        }
        int x=col[i];
        int succ_val= (x+no_of_edges)%((2*no_of_edges));
        
        if (i + 1 == row[row_val]) {
        succ[succ_val] = col[row[row_val - 1]]; // Back to the first column of the current row
        //cout << "Succ = " << succ_val << " val= " << col[row[row_val - 1]] << " Calculatedby = " << i << " Row val = " << row_val << endl;
        }

        else
        {
            //cout << "Succ = " << succ_val << " val= " << col[i+1] << "Calculatedby = " << i << endl;
            succ[succ_val]=col[i+1];
        }
            
        //cout << " "<<succ_val << "=" << col[i+1] << endl;
    }    

    cout << endl;cout << endl;
    for(int i=0;i<2*no_of_edges;i++)
    {
        cout << " "<< succ[i] ;
    }    



    int root = 0; 

    int final[2*no_of_edges];
    int next=succ[root],k=0;
    final[k]=root;
    k++;

    while(next!=root)
    {
        final[k]=next;
        k++;
        next=succ[next];
    }

    cout << endl << endl;

    for(int i=0;i<2*no_of_edges;i++)
    {
        cout << " "<< final[i] ;
    }

    Node2* head2=nullptr;

    for(int i=0;i<2*no_of_edges;i++)
    {
        Node2* templl2 = new Node2{final[i],i+1,nullptr};
        addNode2(head2,templl2);
    }   

    int p[2*no_of_edges];
    // Node1* head=nullptr;

    // for(int i=0;i<2*no_of_edges;i++)
    // {
    //     Node1* templl = new Node1{arr1[final[i]],arr2[final[i]],i+1,nullptr};
    //     addNode(head,templl);
    // }   



    //     for (int i = 0; i < no_of_edges*2; i++) {
    //     printf("e%d: (%d, %d)\n", i, arr1[i], arr2[i]);




    //     //printf("e%d: (%d, %d)\no_of_edges", i + no_of_edges, arr1[i + no_of_edges], arr2[i + no_of_edges]);
    // }
    // printf("OVER\n");


//     vector<int> row, col;
//    // adjacencyListToCSR(adjList, row, col);

//     Node1* head=nullptr;
//     map<pair<int, int>,pair<int, int>> succ;
//     pair<int,int> temp1,temp2;
//     int temp;



    // for(int i=0;i<no_of_edges;i++)
    // {
    //     for(int j=row[i];j<row[i+1];j++)
    //     {
    //         temp1.first=i;
    //         temp1.second=col[j];

    //         temp2.first=col[j];
    //         if(row[col[j]]+1!=row[col[j]+1])
    //         {
    //             temp=row[col[j]]+1;
    //             while(col[temp]==i)
    //             {
    //                 temp++;
    //             }
    //             temp2.second=col[temp];
    //             if(i==col[row[col[j]+1]-1])
    //             {
    //                 //printf("hi i =%d\t val=%d\t",i,col[row[col[j]]]);
    //                temp2.second=col[row[col[j]]];
                   
    //             }

    //         }
    //         else
    //         {
    //             temp2.second=i;
    //         }
    //         succ[temp1]=temp2;
    //         //cout << "(" << temp1.first << "," << temp1.second  << ")" << "(" << temp2.first << "," << temp2.second << ")" << "for i="<< i << "j="<<j <<"Temp"<< temp << endl;
    //     }
    // }
   //printMap(succ);
    

//   std::pair<int, int> currentKey = {0,1};
//   Node1 *templ1 = new Node1{1,0,1,nullptr};
//   addNode(head,templ1);

//     for (int i = 0; i < succ.size() ; ++i) {

//         auto it = succ.find(currentKey);

//         const auto &value = it->second;
//         std::cout << "(" << value.first << ", " << value.second << ")" << std::endl;

//         Node1* templl = new Node1{value.first,value.second,i+2,nullptr};
//         addNode(head,templl);


//         currentKey = value;
//     }


    Node2* current = head2;
        cout << "Linked List Representation:" << endl;
    while (current) {
        cout << "( " << current->e << ", " << current->rank << ") -> ";
        current = current->next;
    }
    cout << "nullptr" << endl;

    // int p[row.size()]={0};


    // cout << "CSR Format:" << endl;
    // cout << "Row: ";
    // for (int val : row) cout << val << " ";
    // cout << endl;

    // cout << "Col: ";
    // for (int val : col) cout << val << " ";
    // cout << endl;

    // cout << "Root node: " << root << endl;

    return 0;
}
