#include <iostream>
#include <unordered_map>

using std::unordered_map;

template <typename K, typename V>
class unorderedMapWarpper
{
public:
    unorderedMapWarpper()
    {
        _map = new unordered_map<K, V>();
    };
    unorderedMapWarpper(const unorderedMapWarpper &) = delete;
    unorderedMapWarpper(unorderedMapWarpper &&) = delete;
    unorderedMapWarpper &operator=(const unorderedMapWarpper &) = delete;
    unorderedMapWarpper &operator=(unorderedMapWarpper &&) = delete;
    V &operator[](const K &key)
    {
        return (*_map)[key];
    }
    const V &operator[](const K &key) const
    {
        return _map->at(key);
    }
    ~unorderedMapWarpper()
    {
        delete _map;
    }

private:
    unordered_map<K, V> *_map;
};
