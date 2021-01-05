#ifndef BITREE_H
#define BITREE_H

#include <cstddef>
#include <algorithm>
#include <functional>

template <typename T>
class BiTreeNode
{
    public:
        BiTreeNode(T _data);
        ~BiTreeNode();
        bool isLeaf() const;
        //void setParent(BiTreeNode<T> * p);
        //BiTreeNode<T> * getParent();
        void setLChild(BiTreeNode<T> * l);
        BiTreeNode<T> * getLChild();
        void setRChild(BiTreeNode<T> * r);
        BiTreeNode<T> * getRChild();

        void setData(T _newData);
        const T & getData() const;
    private:
        BiTreeNode<T> * lChild;
        BiTreeNode<T> * rChild;
        BiTreeNode<T> * parent;

        T data;
};

template <typename T>
BiTreeNode<T>::BiTreeNode(T _data)
:data(_data), parent(nullptr), lChild(nullptr), rChild(nullptr){}

template <typename T>
BiTreeNode<T>::~BiTreeNode()
{}

template<typename T>
bool BiTreeNode<T>::isLeaf() const
{
    return ((lChild == nullptr) && (rChild == nullptr));
}

/*
template <typename T>
void BiTreeNode<T>::setParent(BiTreeNode<T> * p)
{
    parent = p;
}

template <typename T>
BiTreeNode<T> * BiTreeNode<T>::getParent()
{
    return parent;
}
*/

template <typename T>
void BiTreeNode<T>::setLChild(BiTreeNode<T> * l)
{
    lChild = l;
    l -> parent = this;
}

template <typename T>
BiTreeNode<T> * BiTreeNode<T>::getLChild()
{
    return lChild;
}

template <typename T>
void BiTreeNode<T>::setRChild(BiTreeNode<T> * r)
{
    rChild = r;
    r -> parent = this;
}

template <typename T>
BiTreeNode<T> * BiTreeNode<T>::getRChild()
{
    return rChild;
}

template <typename T>
void BiTreeNode<T>::setData(T _newData)
{
    data = _newData;
}

template <typename T>
const T & BiTreeNode<T>::getData() const
{
    return data;
}

template <typename T>
class BiTree
{
    public:
        BiTree();
        BiTree(BiTreeNode<T> * root);
        ~BiTree();
        void clear();
        //清除以_root为根的子树
        void clear(BiTreeNode<T> * _root);
        void setRoot(BiTreeNode<T> * _root);
        BiTreeNode<T> * getRoot() const;

        bool isEmpty();
        unsigned int depth();
        //以_root为根的子树的深度
        unsigned int depth(BiTreeNode<T> * _root);
        //先序遍历
        void preOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit);
        void preOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit, BiTreeNode<T> * _root);
        //中序遍历
        void inOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit);
        void inOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit, BiTreeNode<T> * _root);
        //后序遍历
        void postOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit);
        void postOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit, BiTreeNode<T> * _root);
    private:
        BiTreeNode<T> * root;
};

template <typename T>
BiTree<T>::BiTree()
:root(nullptr){}

template <typename T>
BiTree<T>::BiTree(BiTreeNode<T> * _root)
:root(_root){}

template <typename T>
BiTree<T>::~BiTree()
{
    clear(root);
}

template <typename T>
void BiTree<T>::clear()
{
    clear(root);
}

template <typename T>
void BiTree<T>::clear(BiTreeNode<T> * _root)
{
    if(_root == nullptr)
    {
        return;
    }

    this -> clear(_root -> getLChild());
    this -> clear(_root -> getRChild());
    delete _root;
}

template <typename T>
void BiTree<T>::setRoot(BiTreeNode<T> * _root)
{
    clear();
    root = _root;
}

template <typename T>
BiTreeNode<T> * BiTree<T>::getRoot() const
{
    return root;
}

template <typename T>
bool BiTree<T>::isEmpty()
{
    return (root == nullptr);
}

template <typename T>
unsigned int BiTree<T>::depth()
{
    return depth(root);
}

template <typename T>
unsigned int BiTree<T>::depth(BiTreeNode<T> * _root)
{
    if(_root == nullptr)
    {
        return 0;
    } 
    unsigned int left = depth(_root -> getLChild());
    unsigned int right = depth(_root -> getRChild());
    return std::max(left, right) + 1;
}

template <typename T>
void BiTree<T>::preOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit)
{
    preOrderTraverse(visit, this -> root);
}

template <typename T>
void BiTree<T>::preOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit, BiTreeNode<T> * _root)
{
    if(_root == nullptr)
    {
        return;
    }
    visit(_root);
    preOrderTraverse(visit, _root -> getLChild());
    preOrderTraverse(visit, _root -> getRChild());
}

template <typename T>
void BiTree<T>::inOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit)
{
    inOrderTraverse(visit, this -> root);
}

template <typename T>
void BiTree<T>::inOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit, BiTreeNode<T> * _root)
{
    if(_root == nullptr)
    {
        return;
    }
    preOrderTraverse(visit, _root -> getLChild());
    visit(_root);
    preOrderTraverse(visit, _root -> getRChild());
}

template <typename T>
void BiTree<T>::postOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit)
{
    postOrderTraverse(visit, this -> root);
}

template <typename T>
void BiTree<T>::postOrderTraverse(std::function<bool(BiTreeNode<T> *)> visit, BiTreeNode<T> * _root)
{
    if(_root == nullptr)
    {
        return;
    }
    preOrderTraverse(visit, _root -> getLChild());
    preOrderTraverse(visit, _root -> getRChild());
    visit(_root);
}

#endif