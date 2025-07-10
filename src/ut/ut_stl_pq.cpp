#include <gtest/gtest.h>
#include <string>
#include "../stl_priority.cpp"

/**
 * @brief 测试插入和顶部元素
 */
TEST(PriorityQueueWrapperTest, InsertAndTop)
{
    priorityQueueWarpper<int> pq;
    pq.insert(10);
    pq.insert(5);
    pq.insert(20);

    // 默认是大顶堆，所以顶部元素应该是最大的
    EXPECT_EQ(pq.top(), 20);
}

/**
 * @brief 测试移除顶部元素
 */
TEST(PriorityQueueWrapperTest, RemoveTop)
{
    priorityQueueWarpper<int> pq;
    pq.insert(10);
    pq.insert(5);
    pq.insert(20);

    // 移除顶部元素
    pq.removeTop();
    EXPECT_EQ(pq.top(), 10);

    pq.removeTop();
    EXPECT_EQ(pq.top(), 5);
}

/**
 * @brief 测试空队列
 */
TEST(PriorityQueueWrapperTest, EmptyQueue)
{
    priorityQueueWarpper<int> pq;

    // 新创建的队列应该是空的
    EXPECT_TRUE(pq.empty());
    EXPECT_EQ(pq.size(), 0);

    // 插入元素后应该不为空
    pq.insert(10);
    EXPECT_FALSE(pq.empty());
    EXPECT_EQ(pq.size(), 1);

    // 移除元素后应该为空
    pq.removeTop();
    EXPECT_TRUE(pq.empty());
    EXPECT_EQ(pq.size(), 0);
}

/**
 * @brief 测试大小
 */
TEST(PriorityQueueWrapperTest, Size)
{
    priorityQueueWarpper<int> pq;
    EXPECT_EQ(pq.size(), 0);

    pq.insert(10);
    EXPECT_EQ(pq.size(), 1);

    pq.insert(5);
    EXPECT_EQ(pq.size(), 2);

    pq.removeTop();
    EXPECT_EQ(pq.size(), 1);
}

/**
 * @brief 测试string类型
 */
TEST(PriorityQueueWrapperTest, StringType)
{
    priorityQueueWarpper<std::string> pq;
    pq.insert("apple");
    pq.insert("banana");
    pq.insert("cherry");

    // 字符串按字典序排序，"cherry" 应该在顶部
    EXPECT_EQ(pq.top(), "cherry");
}
