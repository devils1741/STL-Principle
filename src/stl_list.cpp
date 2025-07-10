#include <iostream>
#include <gtest/gtest.h>
#include <list>
using std::list;

/**
 * @brief 一个自定义的类，封装了stl中的list的部分功能
 * \n list是一个双向链表
 * \n 节点结构有_List_node、_List_node_header以及_List_iterator和_List_const_iterator
 * \n struct _List_node_base { _List_node_base* _M_next; _List_node_base* _M_prev;}
 * \n _List_node_header继承自_List_node_base， 新增了_M_size用于表示链表的大小
 */
template <typename T>
class listWarpper
{
public:
    listWarpper() : _list(new list<T>()) {}
    /**
     * @brief 禁止拷贝构造
     */
    listWarpper(const listWarpper &) = delete;
    /**
     * @brief 禁止移动拷贝构造
     */
    listWarpper(listWarpper &&) = delete;
    /**
     * @brief 禁止赋值
     */
    listWarpper &operator=(const listWarpper &) = delete;
    /**
     * @brief 禁止移动赋值
     */
    listWarpper &operator=(listWarpper &&) = delete;
    /**
     * @brief 析构函数
     */
    ~listWarpper()
    {
        delete _list;
    }

    /**
     * @brief 获取迭代器
     * @return 成功时返回迭代器，失败时抛出异常
     */
    typename list<T>::iterator begin()
    {
        if (_list)
            return _list->begin();
        throw std::runtime_error("List is not initialized");
    }

    /**
     * @brief 获取迭代器
     * @return 成功时返回迭代器，失败时抛出异常
     */
    typename list<T>::iterator end()
    {
        if (_list)
            return _list->end();
        throw std::runtime_error("List is not initialized");
    }

    /**
     * @brief 在指定位置插入1个元素
     * @param index 插入位置的索引
     * @param t 要插入的元素
     * @return 成功时返回0
     */
    int insert(const size_t index, const T &t)
    {
        auto it = _list->begin();
        std::advance(it, index);
        _list->insert(it, t);
        return 0;
    }

    /**
     * @brief 在指定位置插入若干个相同值的元素
     * @param index 插入位置的索引
     * @param number 插入元素的个数
     * @param t 要插入的元素
     * @return 成功时返回0
     */
    int insert(const size_t index, const size_t number, const T &t)
    {
        auto it = _list->begin();
        std::advance(it, index);
        _list->insert(it, number, t);
        return 0;
    }

    /**
     * @brief 在指定位置插入另一个list
     * @param index 插入位置的索引
     * @param other 待插入的list
     * @return 成功时返回0
     */
    int splice(const size_t index, list<T> &other)
    {

        auto it = _list->begin();
        std::advance(it, index);
        _list->splice(it, other);
        return 0;
    }

    /**
     * @brief 在链表头部位置插入1个元素
     * @param index 插入位置的索引
     * @return 成功时返回0
     */
    int push_front(const T &t)
    {
        _list->push_front(t);
        return 0;
    }

    /**
     * @brief 在链表末尾插入一个元素
     * @param t 要插入的元素
     * @return 成功时返回0
     */
    int push_back(const T &t)
    {
        _list->push_back(t);
        return 0;
    }

    /**
     * @brief 移除链表头部的元素
     * @return 成功时返回0
     */
    int pop_front()
    {
        _list->pop_front();
        return 0;
    }

    /**
     * @brief 移除链表尾部的元素
     * @return 成功时返回0
     */
    int pop_back()
    {
        _list->pop_back();
        return 0;
    }

private:
    list<T> *_list;
};
