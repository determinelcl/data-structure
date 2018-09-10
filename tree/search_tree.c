//
// Created by determination on 2018/9/8.
//

#include "search_tree.h"
#include "linked_queue.h"


SearchTree newSearchTree(void) {
    return NULL;
}

SearchTree makeEmpty_ST(SearchTree tree) {
    if (tree) {
        makeEmpty_ST(tree->left);
        makeEmpty_ST(tree->right);
        free(tree);
    }

    return NULL;
}

Position_ST find_ST(SearchTree tree, DataType_ST data) {
    if (!tree) return NULL;

    if (COMPARE_WITH(tree->data, data) == GT)
        return find_ST(tree->left, data);
    else if (COMPARE_WITH(tree->data, data) == LT)
        return find_ST(tree->right, data);
    else
        return tree;
}


Position_ST findMin_ST(SearchTree tree) {
    if (!tree) return NULL;
    else if (!tree->left) return tree;
    else return findMin_ST(tree->left);
}

Position_ST findMax_ST(SearchTree tree) {
    if (tree)
        while (tree->right)
            tree = tree->right;

    return tree;
}

SearchTree insert_ST(SearchTree tree, DataType_ST data) {

    if (!tree) {
        tree = malloc(sizeof(struct TreeNode_ST));
        assert(tree);

        tree->data = data;
        tree->left = tree->right = NULL;
    } else {
        Comparable result = COMPARE_WITH(tree->data, data);
        if (result == GT)
            tree->left = insert_ST(tree->left, data);
        else tree->right = insert_ST(tree->right, data);
    }

    return tree;
}

SearchTree delete_ST(SearchTree tree, DataType_ST data) {
    assert(tree);

    Comparable result = COMPARE_WITH(tree->data, data);

    if (result == GT)
        tree->left = delete_ST(tree->left, data);
    else if (result == LT)
        tree->right = delete_ST(tree->right, data);
    else if (tree->left && tree->right) {
        Position_ST tempCell = findMin_ST(tree->right);
        tree->data = tempCell->data;
        tree->right = delete_ST(tree->right, tree->data);
    } else {
        Position_ST tempCell = tree;
        if (!tree->left)
            tree = tree->right;
        else if (!tree->right)
            tree = tree->left;

        free(tempCell);
    }

    return tree;
}

DataType_ST retrieve_ST(Position_ST pos) {
    return pos->data;
}


void preTraversal_ST(SearchTree tree) {
    if (!tree) return;

    PRINT_FMT(tree->data);
    preTraversal_ST(tree->left);
    preTraversal_ST(tree->right);
}

void middleTraversal_ST(SearchTree tree) {
    if (!tree) return;

    middleTraversal_ST(tree->left);
    PRINT_FMT(tree->data);
    middleTraversal_ST(tree->right);
}

void behindTraversal_ST(SearchTree tree) {
    if (!tree) return;

    behindTraversal_ST(tree->left);
    behindTraversal_ST(tree->right);
    PRINT_FMT(tree->data);
}


void levelTraversal_ST(SearchTree tree) {
    if (!tree) return;

    LinkedQueue queue = newLinkedQueue();
    enqueue_LQ(queue, tree);

    while (!isEmpty_LQ(queue)) {
        Position_ST node = frontAndDequeue_LQ(queue);
        PRINT_FMT(node->data);

        if (node->left)
            enqueue_LQ(queue, node->left);
        if (node->right)
            enqueue_LQ(queue, node->right);
    }

    puts("\n");
}

int size_ST(SearchTree tree) {
    int size = 0;

    if (tree) {
        size++;
        size += size_ST(tree->left);
        size += size_ST(tree->right);
    }

    return size;
}


bool isEmpty_ST(SearchTree tree) {
    return tree == NULL;
}