for (int i = 0; i < size(tree_data); i++) {
        tree_nodes[i] = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{tree_data[i], nullptr, nullptr});
    }