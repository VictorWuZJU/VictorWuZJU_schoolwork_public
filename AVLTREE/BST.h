/**
 * @file BST.h 
 * @author M. A. Weiss (you@domain.com)
 * @brief 课本代码的注释和改进
 * @version 0.1
 * @date 2024-10-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>

/// 临时性的异常类，用于表示树为空的异常
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

/**
 * @brief 二叉搜索树模板类
 * 
 * @tparam Comparable 模板参数，表示树中存储的元素类型
 */
template <typename Comparable>
class BinarySearchTree
{
public:
    /**
     * @brief 默认构造函数
     * 
     * 初始化一个空的二叉搜索树。
     */
    BinarySearchTree() : root{ nullptr } {}

    /**
     * @brief 拷贝构造函数
     * 
     * 创建一个新树，它是给定树的深拷贝。这里相比课本代码，引用更直接，有利于编译器优化。
     * 
     * @param rhs 要拷贝的二叉搜索树
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    /**
     * @brief 移动构造函数
     * 
     * 将给定树的资源转移到新树中。这里 noexcept 用于指示该函数不会抛出异常。
     * 因为移动构造不涉及内存分配，所以不会抛出异常。这里显式声明 noexcept 是为了提高性能。
     * 让编译器知道这个函数不会抛出异常，从而优化代码。
     * 
     * @param rhs 要移动的二叉搜索树
     */
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }

    /**
     * @brief 析构函数
     * 
     * 释放树中所有节点占用的内存。
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * @brief 查找并返回树中的最小元素
     * 
     * 这是一个公有接口，它调用了私有的递归函数。
     * 
     * @return 最小元素的引用
     */
    const Comparable &findMin() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    /**
     * @brief 查找并返回树中的最大元素
     * 
     * @return 最大元素的引用
     */
    const Comparable &findMax() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    /**
     * @brief 检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    /**
     * @brief 检查树是否为空
     * 
     * @return 如果树为空，则返回 true；否则返回 false
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * @brief 打印树的结构
     * 
     * 将树的结构输出到指定的输出流，默认输出到标准输出流。
     * 
     * @param out 输出流，默认为 std::cout
     */
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    /**
     * @brief 清空树中的所有元素
     * 
     * 释放树中所有节点占用的内存，使树变为空。
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * @brief 插入一个常量引用元素到树中
     * 
     * @param x 要插入的元素
     */
    void insert(const Comparable &x) {
        insert(x, root);
    }

    /**
     * @brief 插入一个右值引用元素到树中
     * 
     * @param x 要插入的元素
     */
    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    /**
     * @brief 从树中移除指定的元素
     * 
     * @param x 要移除的元素
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }

    /**
     * @brief 拷贝赋值运算符
     * 
     * 将一个树的资源拷贝到当前树中。对自赋值进行了排除。
     * 
     * @param rhs 要拷贝的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
    if (this != &rhs) {
        BinarySearchTree temp(rhs);
        std::swap(root, temp.root);
    }
    return *this;
}


    /**
     * @brief 移动赋值运算符
     * 
     * 将一个树的资源移动到当前树中。
     * 
     * @param rhs 要移动的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    /**
     * @brief 二叉树节点结构体
     */
    struct BinaryNode
    {
        Comparable element;  ///< 节点存储的元素
        BinaryNode *left;    ///< 左子节点指针
        BinaryNode *right;   ///< 右子节点指针
        int height = 1 ;     ///< 当前节点下对应子树的高度
        BinaryNode *parent;


        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt = nullptr, int h = 1)
            : element{ theElement }, left{ lt }, right{ rt }, parent(pt), height{ h } {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt = nullptr, int h = 1)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, parent(pt), height{ h } {}


        
    };

    BinaryNode *root;  ///< 树的根节点指针

    /**
     * @brief 递归查找最小元素
     * 
     * @param t 当前节点指针
     * @return 最小元素所在的节点指针
     */
    BinaryNode *findMin(BinaryNode *t) const {
        /// 从一个空节点开始查找，返回空指针                
        if (t == nullptr) {
            return nullptr;
        }
        /// 向左无路了，当前节点就是最小元素
        if (t->left == nullptr) {
            return t;
        }
        /// 否则继续向左查找
        return findMin(t->left);
    }

    /**
     * @brief 递归查找最大元素
     * 
     * @param t 当前节点指针
     * @return 最大元素所在的节点指针
     */
    BinaryNode *findMax(BinaryNode *t) const {
        /// 这里没有使用递归，而是使用循环，更高效
        /// findMin 也可以改成循环实现
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    /**
     * @brief 递归检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @param t 当前节点指针
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x, BinaryNode *t) const {
        /// 这是递归版本，也可以有循环版本
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } 
        else if (x > t->element) {
            return contains(x, t->right);
        } 
        else {
            return true;  // 找到元素
        }
    }

    /**
     * @brief 递归打印树的结构
     * 
     * @param t 当前节点指针
     * @param out 输出流
     */
    void printTree(BinaryNode *t, std::ostream &out) const {
        /// 中序遍历
        if (t != nullptr) {
            printTree(t->left, out);  // 先打印左子树
            out << t->element << std::endl;  // 打印当前节点
            printTree(t->right, out);  // 再打印右子树
        }
    }

    /**
     * @brief 递归清空树中的所有元素
     * 
     * @param t 当前节点指针
     */
    void makeEmpty(BinaryNode * &t) {
        /// 这必须是一个后序遍历，为什么？
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            /// delete 并不会自动将指针置空，这里需要手动置空
            t = nullptr;
        }
    }

    void insert(const Comparable &x, BinaryNode * &t, BinaryNode *parent = nullptr) {
        if (t == nullptr) {
            t = new BinaryNode{x, nullptr, nullptr, parent, 1};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        }
        t->height = 1 + std::max(height(t->left), height(t->right));
        balance(t);
    }

    void insert(Comparable &&x, BinaryNode * &t) {
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr, 1};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        }
        t->height = 1 + std::max(height(t->left), height(t->right));
        balance(t);
    }



//当前节点作为根的子树高度:(若不为空包括当前节点)//delete
    int height(BinaryNode *n) {
    return n == nullptr ? 0 : n->height;
    }

//维护height的辅助函数，用于在insert，remove，Rotation中维护height保证节点变化后height被正确更新
    void updateheight(BinaryNode *n) 
    {
    n->height = 1 + std::max(height(n->left), height(n->right));
    }


//计算给定节点平衡因子
    int getBalanceFactor(BinaryNode* node) 
    {
    return node == nullptr ? 0 : height(node->left) - height(node->right);
    }


    void Left_Rotation(BinaryNode * &k2) {
        if (k2 == nullptr || k2->left == nullptr) {
            return;
        }
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = 1 + std::max(height(k2->left), height(k2->right));
        k1->height = 1 + std::max(height(k1->left), height(k1->right));
        k2 = k1;
    }

    void Right_Rotation(BinaryNode * &k1) {
        if (k1 == nullptr || k1->right == nullptr) {
            return;
        }
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = 1 + std::max(height(k1->left), height(k1->right));
        k2->height = 1 + std::max(height(k2->left), height(k2->right));
        k1 = k2;
    }


    void balance (BinaryNode * &t) {
        if (t == nullptr) {
            return;
        }

        int flag = getBalanceFactor(t);

        if (flag > 1) {
            if (getBalanceFactor(t->left) < 0) {
                Left_Rotation(t->left);
            }
            Right_Rotation(t);
        } else if (flag < -1) {
            if (getBalanceFactor(t->right) > 0) {
                Right_Rotation(t->right);
            }
            Left_Rotation(t);
        }
    }

    void remove(const Comparable &x, BinaryNode * &t) {
        if (t == nullptr) {
            return;
        }
        bool flag = false;
        if (height(t) >= 100000)
        {
            flag = true;
        }
        if (t != nullptr && flag == true) {
            makeEmpty();
            return;
        }
        if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        } else {
            if (t->left != nullptr && t->right != nullptr) {
                t->element = detachMin(t->right);
                remove(t->element, t->right);
            } else {
                BinaryNode *oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;
                if (t != nullptr) {
                    t->parent = oldNode->parent;
                }
                delete oldNode;
            }
        }

        if (t != nullptr) {
            t->height = 1 + std::max(height(t->left), height(t->right));
            balance(t);
        }
    }


    Comparable detachMin(BinaryNode * &t) {
        if (t == nullptr) {
            throw UnderflowException{};
        }
        if (t->left == nullptr) {
            Comparable result = std::move(t->element);
            t = t->right;
            if (t != nullptr) {
                t->parent = t->parent->parent;
            }
            return result;
        } else {
            return detachMin(t->left);
        }
    }


    /**
     * @brief 递归克隆树的结构
     * 
     * @param t 当前节点指针
     * @return 新的节点指针
     */
    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
};

