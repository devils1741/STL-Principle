#include <iostream>
#include <queue>

using std::cout;
using std::priority_queue;

template <typename T>
class priorityQueueWarpper
{
public:
   /**
    * @brief 构造函数，创建一个新的 priority_queue 对象
    */
   priorityQueueWarpper()
   {
      _pq = new priority_queue<T>();
   }

   /**
    * @brief 析构函数，释放 priority_queue 对象的内存
    */
   ~priorityQueueWarpper()
   {
      delete _pq;
   }

   /**
    * @brief 插入一个元素到优先队列中
    * @param t 要插入的元素
    */
   void insert(const T &t)
   {
      _pq->push(t);
   }

   /**
    * @brief 移除优先队列的顶部元素（最大元素或最小元素）
    * @details 如果优先队列为空，则不执行任何操作
    */
   void removeTop()
   {
      if (!_pq->empty())
      {
         _pq->pop();
      }
   }

   /**
    * @brief 获取优先队列的顶部元素（最大元素或最小元素）
    * @return 返回优先队列顶部元素的常量引用
    */
   const T &top() const
   {
      return _pq->top();
   }

   /**
    * @brief 检查优先队列是否为空
    * @return 如果优先队列为空，则返回 true；否则返回 false
    */
   bool empty() const
   {
      return _pq->empty();
   }

   /**
    * @brief 获取优先队列中的元素数量
    * @return 返回优先队列中元素的数量
    */
   size_t size() const
   {
      return _pq->size();
   }

private:
   priority_queue<T> *_pq; ///< 指向 priority_queue 对象的指针
};