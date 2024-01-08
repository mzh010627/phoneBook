#ifndef __AVL_TREE_H_
#define __AVL_TREE_H_

#include "common.h"



/* 二叉搜索树的初始化 */
int AVLInit(AVLTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (*printFunc)(ELEMENTTYPE val));

/* 二叉搜索树的插入 */
int AVLInsert(AVLTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树是否包含指定的元素 */
int AVLIsContainAppointVal(AVLTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的前序遍历 */
int AVLPreOrderTravel(AVLTree *pBstree);

/* 二叉搜索树的中序遍历 */
int AVLInOrderTravel(AVLTree *pBstree);

/* 二叉搜索树的后序遍历 */
int AVLPostOrderTravel(AVLTree *pBstree);

/* 二叉搜索树的层序遍历 */
int AVLLevelOrderTravel(AVLTree *pBstree);

/* 获取二叉搜索树的结点个数 */
int AVLGetNodeSize(AVLTree *pBstree, int *pSize);

/* 获取二叉搜索树的高度 */
int AVLGetHeight(AVLTree *pBstree, int *pHeight);

/* 二叉搜索树的删除 */
int AVLDelete(AVLTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的销毁 */
int AVLDestroy(AVLTree *pBstree);

/* 判断二叉搜索树是否是完全二叉树 */
int AVLIsComplete(AVLTree *pBSTree);

#endif  //__BINARY_SEARCH_TREE_H_