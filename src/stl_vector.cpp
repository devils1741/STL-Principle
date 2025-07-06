#include <iostream>
#include <vector>
#include <stdexcept>

using std::forward;
using std::size_t;
using std::vector;
/**
 * @brief 一个自定义的类，封装了 std::vector 的部分功能。
 *
 */
template <typename T>
class Vector
{
public:
    /**
     * @brief 无参构造函数。
     *
     * 将 _vec 初始化为 nullptr，表示未分配内存。
     */
    Vector() : _vec(nullptr) {}

    /**
     * @brief 参数化构造函数。
     *
     * 初始化 _vec 为一个指定大小的 std::vector。
     *
     * @param size vector 的长度，必须为非零正数。
     */
    explicit Vector(size_t size)
    {
        if (size < 0)
        {
            throw std::invalid_argument("size of Vectot can't be negetive");
        }
        _vec = new std::vector<T>(size);
    }

    /**
     * @brief 禁止拷贝构造函数。
     */
    Vector(const Vector &) = delete;

    /**
     * @brief 禁止赋值运算符。
     */
    Vector &operator=(const Vector &) = delete;

    /**
     * @brief 析构函数。
     *
     * 释放动态分配的 std::vector 对象。
     */
    ~Vector()
    {
        delete _vec; ///< 释放动态分配的 std::vector 对象
    }

    /**
     * @brief 获取开始位置迭代器
     * @return 迭代器
     */
    typename vector<T>::iterator begin()
    {
        return _vec->begin();
    }

    /**
     * @brief 获取结束位置迭代器
     * @return 迭代器
     */
    typename vector<T>::iterator end()
    {
        return _vec->end();
    }

    /**
     *  @brief 从尾部插入一个对象
     *  vector首先会检查空间是否足够如果足够那么就会直接插入，不够会让内存翻倍再插入
     *  push_back底层调用的是emplace_back
     *  @param t 一个类型为T的元素
     *  @return 成功会返回0
     */
    int push_back(T &&t)
    {
        _vec->push_back(forward<T>(t));
        return 0;
    }

    /**
     *  @brief 从尾部插入一个对象
     *  vector首先会检查空间是否足够如果足够那么就会直接插入，不够会让内存翻倍再插入。
     *  因为底层使用_Alloc_traits在尾部直接构造对象，因此效率比push_back高很多。
     *  @param t 一个类型为T的元素
     *  @return 成功会返回0
     */
    int emplace_back(T &&t)
    {
        _vec->emplace_back(forward<T>(t));
        return 0;
    }

    /**
     *  @brief 任意位置插入一个对象
     *  vector首先会检查空间是否足够如果足够那么就会直接插入，不够会让内存翻倍再插入。
     *  插入元素位置之后的所有元素都往后平移1位
     *  @param index 插入元素的索引
     *  @param t 一个类型为T的元素
     *  @return 成功会返回0
     */
    int insert(const size_t &index, T &t)
    {
        _vec->insert(_vec->begin() + index, t);
        return 0;
    }

    /**
     *  @brief 任意位置插入一个Vector<T>中的所有元素
     *  vector首先会检查空间是否足够如果足够那么就会直接插入，不够会让内存翻倍再插入。
     *  插入元素位置之后的所有元素都往后平移1位
     *  @param index 插入元素的索引
     *  @param other Vector<T>
     *  @return 成功会返回0
     */
    int insert(const size_t &index, Vector<T> &other)
    {
        _vec->insert(_vec->begin() + index, other.begin(), other.end());
        return 0;
    }

    /**
     *  @brief 移除一定范围的元素
     *  会检查越界
     *  @param begin_index 被删除元素的起始位置
     *  @param end_index 被删除元素的结束位置
     *  @return 成功会返回0
     */
    int erase(const size_t begin_index, const size_t end_index)
    {
        if (begin_index >= _vec->size() || end_index > _vec->size() || begin_index > end_index)
        {
            throw std::out_of_range("Index out of range");
        }
        _vec->erase(_vec->begin() + begin_index, _vec->begin() + end_index);
        return 0;
    }
    /**
     *  @brief 获取某个元素的引用
     *  @param index 需要获取元素的索引
     *  @return 成功会返回元素的引用
     */
    T &operator[](const size_t index)
    {
        return (*_vec)[index];
    }

private:
    std::vector<T> *_vec; ///< 私有成员变量，指向动态分配的 std::vector 对象
};

int main()
{
    // 测试无参构造函数
    Vector<int> vec1;
    std::cout << "测试无参构造函数成功" << std::endl;

    // 测试参数化构造函数
    Vector<int> vec2(5);
    std::cout << "测试参数化构造函数成功" << std::endl;

    // 测试 push_back
    vec2.push_back(10);
    std::cout << "测试 push_back 成功，元素为: " << vec2.begin()[5] << std::endl;

    // 测试 emplace_back
    vec2.emplace_back(20);
    std::cout << "测试 emplace_back 成功，元素为: " << vec2.begin()[6] << std::endl;

    // 测试 insert（单个元素）
    int value = 30;
    vec2.insert(3, value);
    std::cout << "测试 insert（单个元素）成功，元素为: " << vec2.begin()[3] << std::endl;

    // 测试 insert（Vector对象）
    Vector<int> vec3(2);
    vec3.push_back(40);
    vec3.push_back(50);
    vec2.insert(1, vec3);
    std::cout << "测试 insert（Vector对象）成功，元素为: ";
    for (auto it = vec2.begin(); it != vec2.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试 erase
    vec2.erase(1, 3);
    std::cout << "测试 erase 成功，元素为: ";
    for (auto it = vec2.begin(); it != vec2.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试迭代器
    for (auto it = vec2.begin(); it != vec2.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试[]运算符
    vec2[10] = 100;
    std::cout << "vec2[10]=" << vec2[10] << std::endl;

    // 测试析构函数
    std::cout << "测试析构函数成功" << std::endl;
}