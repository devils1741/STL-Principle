#include <gtest/gtest.h>
#include "../stl_vector.cpp"

/**
 * @brief 测试默认构造函数
 */
TEST(VectorWarpperTest, DefaultConstructor)
{
    vectorWarpper<int> vw;
}

/**
 * @brief 测试参数化构造函数
 */
TEST(VectorWarpperTest, ParamConstructor)
{
    vectorWarpper<int> vw(5);
    EXPECT_EQ(vw[0], 0);
    EXPECT_EQ(vw[4], 0);
}

/**
 * @brief 测试 push_back
 */
TEST(VectorWarpperTest, PushBack)
{
    vectorWarpper<int> vw;
    vw.push_back(10);
    EXPECT_EQ(vw[0], 10);
}

/**
 * @brief 测试 emplace_back
 */
TEST(VectorWarpperTest, EmplaceBack)
{
    vectorWarpper<int> vw;
    vw.emplace_back(20);
    EXPECT_EQ(vw[0], 20);
}

/**
 * @brief 测试 insert 插入单个元素
 */
TEST(VectorWarpperTest, InsertSingleElement)
{
    vectorWarpper<int> vw(3);
    vw.insert(1, 42);
    EXPECT_EQ(vw[1], 42);
}

/**
 * @brief 测试 insert 插入另一个 vectorWarpper
 */
TEST(VectorWarpperTest, InsertVectorWarpper)
{
    vectorWarpper<int> vw1(3);
    vectorWarpper<int> vw2(2);
    vw2.push_back(1);
    vw2.push_back(2); 
    vw1.insert(1, vw2);
    EXPECT_EQ(vw1[3], 1);
    EXPECT_EQ(vw1[4], 2);
}

/**
 * @brief 测试 erase 删除元素
 */
TEST(VectorWarpperTest, Erase)
{
    vectorWarpper<int> vw(5);
    vw.erase(1, 3);
    EXPECT_EQ(vw.size(), 3);
}

/**
 * @brief 测试 erase 越界异常
 */
TEST(VectorWarpperTest, EraseOutOfRange)
{
    vectorWarpper<int> vw(5);
    EXPECT_THROW(vw.erase(3, 6), std::out_of_range);
}

/**
 * @brief 测试 resize 缩小
 */
TEST(VectorWarpperTest, ResizeShrink)
{
    vectorWarpper<int> vw(5);
    vw.resize(3);
    EXPECT_EQ(vw.size(), 3);
}

/**
 * @brief 测试 resize 扩大
 */
TEST(VectorWarpperTest, ResizeExpand)
{
    vectorWarpper<int> vw(3);
    vw.resize(5);
    EXPECT_EQ(vw.size(), 5);
}

/**
 * @brief 测试 reserve
 */
TEST(VectorWarpperTest, Reserve)
{
    vectorWarpper<int> vw;
    vw.reserve(10);
    EXPECT_GE(vw.capacity(), 10);
}

/**
 * @brief 测试 operator[] 访问元素
 */
TEST(VectorWarpperTest, SubscriptOperator)
{
    vectorWarpper<int> vw(3);
    vw[1] = 99;
    EXPECT_EQ(vw[1], 99);
}

/**
 * @brief 测试拷贝构造被删除
 */
TEST(VectorWarpperTest, CopyConstructorDeleted)
{
    EXPECT_FALSE(std::is_copy_constructible<vectorWarpper<int>>::value);
}

/**
 * @brief 测试移动构造被删除
 */
TEST(VectorWarpperTest, MoveConstructorDeleted)
{
    EXPECT_FALSE(std::is_move_constructible<vectorWarpper<int>>::value);
}

/**
 * @brief 测试拷贝赋值被删除
 */
TEST(VectorWarpperTest, CopyAssignmentDeleted)
{
    EXPECT_FALSE(std::is_copy_assignable<vectorWarpper<int>>::value);
}

/**
 * @brief 测试移动赋值被删除
 */
TEST(VectorWarpperTest, MoveAssignmentDeleted)
{
    EXPECT_FALSE(std::is_move_assignable<vectorWarpper<int>>::value);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}