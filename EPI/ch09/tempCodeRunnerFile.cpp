int SumRoomToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
    return SumRootToLeafHelper(tree, 0);
}
