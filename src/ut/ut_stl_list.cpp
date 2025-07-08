#include <gtest/gtest.h>
#include <stdexcept>
#include "../stl_list.cpp"
// 测试类
class ListWarpperTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        listWrapper = new listWarpper<int>();
    }

    void TearDown() override
    {
        delete listWrapper;
    }

    listWarpper<int>* listWrapper;
};

// 测试构造函数和析构函数
TEST_F(ListWarpperTest, ConstructorAndDestructor)
{
    listWarpper<int> wrapper;
    SUCCEED(); // 如果没有崩溃或异常，则认为通过
}

// 测试begin和end函数
TEST_F(ListWarpperTest, BeginAndEnd)
{
    listWrapper->push_back(1);
    listWrapper->push_back(2);

    auto beginIt = listWrapper->begin();
    auto endIt = listWrapper->end();

    EXPECT_EQ(*beginIt, 1); // 检查begin是否指向第一个元素
    --endIt; // 将end迭代器向前移动一位，使其指向最后一个有效元素
    EXPECT_EQ(*endIt, 2); // 检查end是否指向最后一个元素
}

// 测试insert函数
TEST_F(ListWarpperTest, Insert)
{
    listWrapper->push_back(1);
    listWrapper->push_back(2);
    listWrapper->push_back(3);

    // 插入单个元素
    listWrapper->insert(1, 99); // 在索引1处插入99
    auto it = listWrapper->begin();
    std::advance(it, 1); // 移动到索引1
    EXPECT_EQ(*it, 99); // 检查是否正确插入

    // 插入多个相同元素
    listWrapper->insert(3, 2, 88); // 在索引3处插入两个88
    it = listWrapper->begin();
    std::advance(it, 3); // 移动到索引3
    EXPECT_EQ(*it, 88); // 检查是否正确插入
    std::advance(it, 1); // 移动到下一个元素
    EXPECT_EQ(*it, 88); // 检查是否正确插入
}

// 测试splice函数
TEST_F(ListWarpperTest, Splice)
{
    listWrapper->push_back(1);
    listWrapper->push_back(2);

    list<int> otherList;
    otherList.push_back(99);
    otherList.push_back(88);

    listWrapper->splice(1, otherList); // 在索引1处插入otherList
    auto it = listWrapper->begin();
    std::advance(it, 1); // 移动到索引1
    EXPECT_EQ(*it, 99); // 检查是否正确插入
    std::advance(it, 1); // 移动到下一个元素
    EXPECT_EQ(*it, 88); // 检查是否正确插入
}

// 测试push_front和push_back函数
TEST_F(ListWarpperTest, PushFrontAndPushBack)
{
    listWrapper->push_front(1);
    listWrapper->push_front(2);
    listWrapper->push_back(3);
    listWrapper->push_back(4);

    auto it = listWrapper->begin();
    EXPECT_EQ(*it, 2); // 检查push_front是否正确
    std::advance(it, 1);
    EXPECT_EQ(*it, 1); // 检查push_front是否正确
    std::advance(it, 1);
    EXPECT_EQ(*it, 3); // 检查push_back是否正确
    std::advance(it, 1);
    EXPECT_EQ(*it, 4); // 检查push_back是否正确
}

// 测试pop_front和pop_back函数
TEST_F(ListWarpperTest, PopFrontAndPopBack)
{
    listWrapper->push_front(1);
    listWrapper->push_front(2);
    listWrapper->push_back(3);
    listWrapper->push_back(4);

    listWrapper->pop_front();
    auto it = listWrapper->begin();
    EXPECT_EQ(*it, 1); // 检查pop_front是否正确

    listWrapper->pop_back();
    it = listWrapper->end();
    --it; // 移动到最后一个元素
    EXPECT_EQ(*it, 3); // 检查pop_back是否正确
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}