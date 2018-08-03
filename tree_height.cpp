#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>

#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
        this->parent = NULL;
    }

    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
};

int height(Node *nodep){
    std::vector<Node*> children = (*nodep).children;
    if(children.empty()) return 1;
    int heights[children.size()];
    for (int i = 0; i < children.size(); i++){
        heights[i] = height(children[i]);
    }
    return 1 + *std::max_element(heights, heights + children.size());
                                                                //Im not a C++Dev, so figuring this out took some time
}

Node* getRoot(Node *node){
    if ((*node).parent == NULL)
        return node;
    return getRoot((*node).parent);
}

int main_with_large_stack_space() {
    std::ios_base::sync_with_stdio(0);
    int n;
    std::cin >> n;

    std::vector<Node> nodes;
    nodes.resize(n);
    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        std::cin >> parent_index;
        if (parent_index >= 0)
            nodes[child_index].setParent(&nodes[parent_index]);
        nodes[child_index].key = child_index;
    }

    std::cout << height(getRoot(&nodes[0])) << std::endl;
    return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 32 * 1024 * 1024;   // min stack size = 32 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }

#endif
    return main_with_large_stack_space();
}
