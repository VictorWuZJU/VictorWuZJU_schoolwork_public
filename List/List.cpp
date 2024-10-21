#include <iostream>
#include "List.h" 

int main() {
    // 创建一个整数类型的List
    List<int> intList;

    // 测试插入操作
    intList.push_back(10);
    intList.push_back(20);
    intList.push_front(5);

    // 测试迭代器
    std::cout << "List elements: ";
    for (auto it = intList.begin(); it != intList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试大小和空检查
    std::cout << "List size: " << intList.size() << std::endl;
    std::cout << "List empty: " << (intList.empty() ? "true" : "false") << std::endl;

    // 测试清空操作
    intList.clear();
    std::cout << "List empty after clear: " << (intList.empty() ? "true" : "false") << std::endl;

    // 重新添加元素
    intList.push_back(30);
    intList.push_back(40);

    // 测试常量迭代器
    const List<int>& constIntList = intList;
    std::cout << "Const List elements: ";
    for (auto it = constIntList.begin(); it != constIntList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试插入和删除操作
    intList.insert(++intList.begin(), 25); // 在第二个元素前插入25
    std::cout << "List after inserting 25: ";
    for (auto it = intList.begin(); it != intList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    intList.erase(++intList.begin()); // 删除第二个元素
    std::cout << "List after erasing second element: ";
    for (auto it = intList.begin(); it != intList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试边界情况，如插入到末尾，删除第一个元素
    intList.push_back(50);
    intList.erase(intList.begin()); // 删除第一个元素

    // 测试前后元素的访问
    std::cout << "Front element: " << intList.front() << std::endl;
    std::cout << "Back element: " << intList.back() << std::endl;

    return 0;
}