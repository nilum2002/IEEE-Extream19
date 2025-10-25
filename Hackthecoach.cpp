#include <iostream>

using namespace std;
// Structure to store tree edges and noeds
struct TreeEdge {
    int node_from;
    int node_to;
};

// Function  we use to generate a minimal tree that hacks the coach's solution
void generate_tree() {
    int num_nodes_amount = 7;
    int root_node = 1;

    cout << num_nodes_amount << " " << root_node << endl;


    // creating the tree
    TreeEdge edges[] = {
        {1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {3, 7}
    };

    // Output edges in a loop for unique style
    for (int edge_idx = 0; edge_idx < num_nodes_amount - 1; ++edge_idx) {
        cout << edges[edge_idx].node_from << " " << edges[edge_idx].node_to << endl;
    }
}

int main() {
    // Outputying the hacking tree
    generate_tree();
    return 0;
}