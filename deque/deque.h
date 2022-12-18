#ifndef _DEQUE_
#define _DEQUE_

template <class T>
class Deque
{
private:
    int _front, _back, _count;
    T *_data;
    int _maxitems;

public:
    Deque(int maxitems = 256)
    {
        _front = 0;
        _back = 0;
        _count = 0;
        _maxitems = maxitems;
        _data = new T[_maxitems + 2];
        _data[_maxitems + 1] = T();
    }
    ~Deque()
    {
        delete[] _data;
    }
    inline int count();
    inline int front();
    inline int back();
    void push_front(const T &item);
    void push_back(const T &item);
    T peek_front();
    T peek_back();
    T pop_front();
    T pop_back();
    T &operator[](int index);
    T *to_array();
    T *data_array();
    void clear();
};

template <class T>
inline int Deque<T>::count()
{
    return _count;
}

template <class T>
inline int Deque<T>::front()
{
    return _front;
}

template <class T>
inline int Deque<T>::back()
{
    return _back;
}

template <class T>
void Deque<T>::push_front(const T &item)
{
    if (_count < _maxitems)
    { // Drops out when full
        _front--;
        // Check wrap around
        if (_front < 0)
            _front = _maxitems;

        _data[_front] = item;
        ++_count;
    }
}

template <class T>
void Deque<T>::push_back(const T &item)
{
    if (_count < _maxitems)
    { // Drops out when full
        _data[_back++] = item;
        ++_count;
        // Check wrap around
        if (_back > _maxitems)
            _back = 0;
    }
}

template <class T>
T Deque<T>::pop_front()
{
    if (_count <= 0)
        return T(); // Returns empty
    else
    {
        T result = _data[_front];
        _front++;
        --_count;
        // Check wrap around
        if (_front > _maxitems)
            _front -= (_maxitems + 1);
        return result;
    }
}

template <class T>
T Deque<T>::pop_back()
{
    if (_count <= 0)
        return T(); // Returns empty
    else
    {
        // Check wrap around
        if (_back <= 0)
            _back += (_maxitems + 1);

        T result = _data[--_back];
        --_count;
        return result;
    }
}

template <class T>
T Deque<T>::peek_front()
{
    if (_count <= 0)
        return T(); // Returns empty
    else
        return _data[_front];
}

template <class T>
T Deque<T>::peek_back()
{
    if (_count <= 0)
        return T(); // Returns empty
    else
        return _data[_back];
}

template <class T>
T &Deque<T>::operator[](int index)
{
    if (_count <= 0 || index < 0 || index >= _count)
        return _data[_maxitems + 1]; // Returns empty
    else
        return _data[(_front + index) % (_maxitems + 1)];
}

template <class T>
T *Deque<T>::to_array()
{
    T *a = new T[_count];
    for (int i = 0; i < _count; i++)
    {
        a[i] = _data[(i + _front) % (_maxitems + 1)];
    }
    return a;
}

template <class T>
T *Deque<T>::data_array()
{
    return _data;
}

template <class T>
void Deque<T>::clear()
{
    _front = _back = 0;
    _count = 0;
}

//Deque<test01> lista = Deque<test01>(63);
//lista.push_back(obj);

#endif