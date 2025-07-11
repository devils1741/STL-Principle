#include <iostream>
#include <vector>
#include <stdexcept>

using std::forward;
using std::size_t;
using std::vector;
/**
 * @brief 一个自定义的类，封装了 std::vector 的部分功能。
 * \n vector底层实现是一个动态数组,数组位于堆上。默认大小24字节
 * \n 继承自protected _Vector_base。_Vector_base控制数据的指针主要有三个:_M_start,_M_finish,_M_end_of_storage。
 * \n 无参构造函数不申请内存，有参构造函数一次性申请足够内存
 * \n 插入元素首先会检查空间是否足够，如果不够会扩容，扩容多少由编译器具体实现，vs1.5倍，gcc2倍，底层使用malloc分配内存空间。中间插入元素效率较低，尾部插入元素效率较好
 * \n 删除最后一个元素会把_M_finish指针前移一位，删除中间元素会直接把删除位置之后的元素前移一位覆盖， 删除元素不会释放已有的内存
 * \n 读取元素会检查是否越界
 * \n 修改元素不支持直接修改，需要先获取引用再修改
 * \n clear释放内存不会真的释放内存， shrink_to_fit可能释放，取决于编译器的实现。gcc会把容量缩减到和当前元素的数量相匹配
 * \n resize会截断当前vector，如果小于当前vector的size;反之会重新分配内存。resize
 */
template <typename T>
class vectorWarpper
{
public:
    /**
     * @brief 无参构造函数。
     *
     * 将 _vec 初始化为 nullptr，表示未分配内存。
     */
    vectorWarpper() : _vec(new std::vector<T>()) {}

    /**
     * @brief 参数化构造函数。
     *
     * 初始化 _vec 为一个指定大小的 std::vector。
     *
     * @param size vector 的长度，必须为非零正数。
     */
    explicit vectorWarpper(size_t size)
    {
        _vec = new std::vector<T>(size);
    }

    /**
     * @brief 禁止拷贝构造函数。
     */
    vectorWarpper(const vectorWarpper &) = delete;

    /**
     * @brief 禁止移动拷贝构造函数。
     */
    vectorWarpper(vectorWarpper &&) = delete;

    /**
     * @brief 禁止赋值运算符。
     */
    vectorWarpper &operator=(const vectorWarpper &) = delete;

    /**
     * @brief 禁止赋值运算符。
     */
    vectorWarpper &operator=(vectorWarpper &&) = delete;

    /**
     * @brief 析构函数。
     *
     * 释放动态分配的 std::vector 对象。
     */
    ~vectorWarpper()
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
    int insert(const size_t &index, T &&t)
    {
        _vec->insert(_vec->begin() + index, t);
        return 0;
    }

    /**
     *  @brief 任意位置插入一个Vector<T>中的所有元素
     *  vector首先会检查空间是否足够如果足够那么就会直接插入，不够会让内存翻倍再插入。
     *  插入元素位置之后的所有元素都往后平移1位
     *  @param index 插入元素的索引
     *  @param other vectorWarpper<T>
     *  @return 成功会返回0
     */
    int insert(const size_t &index, vectorWarpper<T> &other)
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
     *  @brief 重新分配vector的size
     *  - 如果new size < current size，只保留前n个，但是多余的元素会销毁，基本数据类型除外
     *  - 如果new size > current size，则在容器中追加元素，如果val指定了，则追加的元素为val的拷贝，否则，默认初始化
     *  - 如果new size > current capacity，内存会自动重新分配
     *  @param size 容器调整后的size
     *  @return 成功会返回0
     */
    int resize(size_t size)
    {
        _vec->resize(size);
        return 0;
    }

    /**
     *  @brief 重新分配vector的capacity
     *  - 如果n>容器的当前capacity，该函数会使得容器重新分配内存使capacity达到n
     *  - 任何其他情况，该函数调用不会导致内存重新分配，并且容器的capacity不会改变
     *  - 该函数不会影响向量的size而且不会改变任何元素
     *  @param capacity 容器调整后容量的大小
     *  @return 成功会返回0
     */
    int reserve(size_t capacity)
    {
        _vec->reserve(capacity);
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

    /**
     *  @brief 获取vector的容量
     *  @return 返回容器的容量
     */
    size_t capacity()
    {
        return _vec->capacity();
    }

    /**
     *  @brief 获取vector的大小
     *  @return 返回容器的大小
     */
    size_t size()
    {
        return _vec->size();
    }

private:
    std::vector<T> *_vec; ///< 私有成员变量，指向动态分配的 std::vector 对象
};