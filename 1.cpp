#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct TreeNode {
    int value;
    TreeNode* leftChild;
    TreeNode* rightChild;

    TreeNode(int val) : value(val), leftChild(nullptr), rightChild(nullptr) {}
};

TreeNode* createTreeFromArray(const int inputList[], int totalElements) {
    if (totalElements <= 0 || inputList[0] < 0) {
        return nullptr;
    }

    TreeNode* rootNode = new TreeNode(inputList[0]);
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(rootNode);

    int index = 1;

    while (!nodeQueue.empty() && index < totalElements) {
        TreeNode* currentNode = nodeQueue.front();
        nodeQueue.pop();

        if (index < totalElements) {
            if (inputList[index] >= 0) {
                currentNode->leftChild = new TreeNode(inputList[index]);
                nodeQueue.push(currentNode->leftChild);
            }
            index++;
        }

        if (index < totalElements) {
            if (inputList[index] >= 0) {
                currentNode->rightChild = new TreeNode(inputList[index]);
                nodeQueue.push(currentNode->rightChild);
            }
            index++;
        }
    }

    return rootNode;
}

struct SubtreeData {
    bool isBST;
    long long minimumValue;
    long long maximumValue;
    long long totalSum;
};

long long maxBSTSum = 0;

SubtreeData checkAndCalculateBST(TreeNode* currentNode) {
    if (currentNode == nullptr) {
        return { true, LLONG_MAX, LLONG_MIN, 0LL };
    }

    SubtreeData leftSubtree = checkAndCalculateBST(currentNode->leftChild);
    SubtreeData rightSubtree = checkAndCalculateBST(currentNode->rightChild);

    long long currentSubtreeSum = leftSubtree.totalSum + rightSubtree.totalSum + currentNode->value;

    if (leftSubtree.isBST && rightSubtree.isBST &&
        leftSubtree.maximumValue < currentNode->value &&
        currentNode->value < rightSubtree.minimumValue) {

        maxBSTSum = max(maxBSTSum, currentSubtreeSum);

        long long currentMin = min((long long)currentNode->value, leftSubtree.minimumValue);
        long long currentMax = max((long long)currentNode->value, rightSubtree.maximumValue);

        return { true, currentMin, currentMax, currentSubtreeSum };
    }

    return { false, 0, 0, 0 };
}

int main() {
    int totalNodes;
    cout << "Enter the total number of elements: ";
    if (!(cin >> totalNodes) || totalNodes <= 0) {
        cout << "Maximum Sum BST: 0\n";
        return 0;
    }

    int* inputValues = new int[totalNodes];

    cout << "Enter " << totalNodes << " values (use -1 for NULL nodes): ";
    for (int i = 0; i < totalNodes; i++) {
        cin >> inputValues[i];
    }

    TreeNode* rootNode = createTreeFromArray(inputValues, totalNodes);

    if (rootNode == nullptr) {
        cout << "Tree is empty.\n";
        cout << "Maximum Sum BST: 0\n";
        delete[] inputValues;
        return 0;
    }

    checkAndCalculateBST(rootNode);

    cout << "Maximum Sum BST: " << maxBSTSum << "\n";

    delete[] inputValues;

    return 0;
}
