#include "HeapSort.h"
#include <chrono>
#include <random>

int main()
{
    //1000000随机序列v_1

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0, 1000009); 

    std::vector<int> v_1(1000000);

    for (int& num : v_1) 
    {
        num = dis(gen);
    }

    //1000000有序序列v_2

    std::vector<int> v_2(1000000);

    int i = 1 ;
    for (int& num : v_2) 
    {
        num = i ++ ;
    }

    //1000000逆序序列v_3

    std::vector<int> v_3(1000000);

    int j = 1000002 ;

    for (int& num : v_3) 
    {
        num = j -- ;
    }

    //1000000随机有重序列v_4

    std::random_device rd_sp;
    std::mt19937 gen_sp(rd_sp());

    std::uniform_int_distribution<> dis_sp(0, 999); 

    std::vector<int> v_4(1000000);

    for (int& num : v_4) {
        num = dis(gen_sp);
    }
/*
    //输出比对
    //v_1
    for (int num : v_1) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    HeapSort(v_1.begin()+1,v_1.end());

    for (int num : v_1) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    //v_2
    for (int num : v_2) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    HeapSort(v_2.begin()+1,v_2.end());

    for (int num : v_2) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    //v_3
    for (int num : v_3) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    HeapSort(v_3.begin()+1,v_3.end());

    for (int num : v_3) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    //v_4
    for (int num : v_4) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    HeapSort(v_4.begin()+1,v_4.end());

    for (int num : v_4) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
*/


    std::cout<<"简洁起见，只输出排序前十位"<<std::endl;
    //计时器
    auto start = std::chrono::high_resolution_clock::now();

    // 对 v_1 进行堆排序
    HeapSort(v_1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "v_1 排序耗时: " << duration.count() << " 毫秒" << std::endl;

    // 输出 v_1 排序后的部分结果
    std::cout << "v_1 排序后序列: ";
    for (int i = 0; i <= 10; ++i) {
        std::cout << v_1[i] << " ";
    }
    std::cout << std::endl;

    std::random_device rd_1sp;
    std::mt19937 gen_1sp(rd_1sp());

    std::uniform_int_distribution<> dis_1sp(0, 1000009); 

    std::vector<int> v_1sp(1000000);

    for (int& num : v_1sp) 
    {
        num = dis(gen);
    }



    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(v_1sp.begin(), v_1sp.end());
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "v_1sp STD排序耗时: " << duration.count() << " 毫秒" << std::endl;

    // 输出 v_1sp 排序后的部分结果
    std::cout << "v_1sp 排序后序列: ";
    for (int i = 0; i <= 10; ++i) {
        std::cout << v_1sp[i] << " ";
    }
    
    std::cout << std::endl;
    // 对 v_2 进行堆排序
    start = std::chrono::high_resolution_clock::now();
    HeapSort(v_2);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "v_2 排序耗时: " << duration.count() << " 毫秒" << std::endl;

    // 输出 v_2 排序后的部分结果
    std::cout << "v_2 排序后序列: ";
    for (int i = 0; i <= 10; ++i) {
        std::cout << v_2[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int> v_2sp(1000000);

    int k = 1 ;
    for (int& num : v_2) 
    {
        num = k ++ ;
    }

    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(v_2sp.begin(), v_2sp.end());
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "v_2sp STD排序耗时: " << duration.count() << " 毫秒" << std::endl;



    // 对 v_3 进行堆排序
    start = std::chrono::high_resolution_clock::now();
    HeapSort(v_3);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "v_3 排序耗时: " << duration.count() << " 毫秒" << std::endl;

    // 输出 v_3 排序后的部分结果
    std::cout << "v_3 排序后序列: ";
    for (int i = 0; i <= 10; ++i) {
        std::cout << v_3[i] << " ";
    }
    std::cout << std::endl;

    
    std::vector<int> v_3sp(1000000);

    int l = 1000002 ;

    for (int& num : v_3sp) 
    {
        num = l -- ;
    }

    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(v_3sp.begin(), v_3sp.end());
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "v_3sp STD排序耗时: " << duration.count() << " 毫秒" << std::endl;

    std::cout << "v_3sp 排序后序列: ";
    for (int i = 0; i <= 10; ++i) {
        std::cout << v_3sp[i] << " ";
    }
    std::cout << std::endl;

    // 对 v_4 进行堆排序
    start = std::chrono::high_resolution_clock::now();
    HeapSort(v_4);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "v_4 排序耗时: " << duration.count() << " 毫秒" << std::endl;

    // 输出 v_4 排序后的部分结果
    std::cout << "v_4sp 排序后序列: ";
    for (int i = 0; i <= 10; ++i)
    {
        std::cout << v_4[i] << " ";
    }
    std::cout << std::endl;

    
    std::random_device rd_4sp;
    std::mt19937 gen_4sp(rd_4sp());
    std::uniform_int_distribution<> dis_4sp(2, 999); 
    std::vector<int> v_4sp(1000000);
    for (int& num : v_4sp) {
        num = dis_4sp(gen_4sp);
    }

    // 对 v_4sp 进行堆排序(STL)
    start = std::chrono::high_resolution_clock::now();
    std::sort_heap(v_4sp.begin(), v_4sp.end());
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "v_4 STD排序耗时: " << duration.count() << " 毫秒" << std::endl;

    std::cout << "v_4sp 排序后序列: ";
    for (int i = 0; i <= 10; ++i)
    {
        std::cout << v_4sp[i] << " ";
    }
    std::cout << std::endl;

    // 等待用户输入，以便查看输出结果
    std::cout << "按任意键继续..." << std::endl;
    std::getchar(); // 等待用户输入一个字符

    return 0;
}
