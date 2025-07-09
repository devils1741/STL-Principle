#include <gtest/gtest.h>
#include <stdexcept>
#include "../stl_list.cpp"

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

/**
 * @brief 测试构造函数和析构函数是否正常运行
 */
TEST_F(ListWarpperTest, ConstructorAndDestructor)
{
    listWarpper<int> wrapper;
    SUCCEED();
}

/**
 * @brief 测试 begin 和 end 函数是否正确返回迭代器
 */
TEST_F(ListWarpperTest, BeginAndEnd)
{
    listWrapper->push_back(1);
    listWrapper->push_back(2);

    auto beginIt = listWrapper->begin();
    auto endIt = listWrapper->end();

    EXPECT_EQ(*beginIt, 1);
    --endIt;
    EXPECT_EQ(*endIt, 2);
}

/**
 * @brief 测试 insert 函数在指定位置插入元素的功能
 */
TEST_F(ListWarpperTest, Insert)
{
    listWrapper->push_back(1);
    listWrapper->push_back(2);
    listWrapper->push_back(3);

    listWrapper->insert(1, 99);
    auto it = listWrapper->begin();
    std::advance(it, 1);
    EXPECT_EQ(*it, 99);

    listWrapper->insert(3, 2, 88);
    it = listWrapper->begin();
    std::advance(it, 3);
    EXPECT_EQ(*it, 88);
    std::advance(it, 1);
    EXPECT_EQ(*it, 88);
}

/**
 * @brief 测试 splice 函数将另一个链表插入当前链表的功能
 */
TEST_F(ListWarpperTest, Splice)
{
    listWrapper->push_back(1);
    listWrapper->push_back(2);

    list<int> otherList;
    otherList.push_back(99);
    otherList.push_back(88);

    listWrapper->splice(1, otherList);
    auto it = listWrapper->begin();
    std::advance(it, 1);
    EXPECT_EQ(*it, 99);
    std::advance(it, 1);
    EXPECT_EQ(*it, 88);
}

/**
 * @brief 测试 push_front 和 push_back 函数在链表前后插入元素的功能
 */
TEST_F(ListWarpperTest, PushFrontAndPushBack)
{
    listWrapper->push_front(1);
    listWrapper->push_front(2);
    listWrapper->push_back(3);
    listWrapper->push_back(4);

    auto it = listWrapper->begin();
    EXPECT_EQ(*it, 2);
    std::advance(it, 1);
    EXPECT_EQ(*it, 1);
    std::advance(it, 1);
    EXPECT_EQ(*it, 3);
    std::advance(it, 1);
    EXPECT_EQ(*it, 4);
}

/**
 * @brief 测试 pop_front 和 pop_back 函数删除链表前后元素的功能
 */
TEST_F(ListWarpperTest, PopFrontAndPopBack)
{
    listWrapper->push_front(1);
    listWrapper->push_front(2);
    listWrapper->push_back(3);
    listWrapper->push_back(4);

    listWrapper->pop_front();
    auto it = listWrapper->begin();
    EXPECT_EQ(*it, 1);

    listWrapper->pop_back();
    it = listWrapper->end();
    --it;
    EXPECT_EQ(*it, 3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}