#include "Set.h"
#include "math.h"



template class Set<int>;
template class Set<float>;
template class Set<std::string>;
template class Set<std::pair<int, double>>;




template<class T> inline
Set<T>::Set(size_t count)
{
    arr = new int[count];
    size = count;
    size_t i = 0;
    do
    {
        int add_elem;
        std::cout << "Input uniq elem for array: ";
        std::cin >> add_elem;
        if (!contain_num(add_elem))
        {
            arr[i] = add_elem;
            i++;
        }
        else
            std::cout << "This num contain in array" << std::endl;
    } while (i < size);

}

template<class T>
Set<T>::Set(const Set<T>& set)
{
    size = set.size;
    arr = new int[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = set.arr[i];
    }
}


template<class T>
Set<T>::~Set()
{
    delete[]arr;
    size = 0;
}


template<class T>
size_t Set<T>::get_size()
{
    return size;
}


template<class T>
Set<T> Set<T>::operator+(const Set<T>& set)
{
    int* ret_arr = new int[set.size + size];
    int size_arr = 0;

    for (size_t first = 0; first < size; first++, size_arr++) {
        ret_arr[size_arr] = arr[first];

    }
    for (size_t sec = 0; sec < set.size; sec++)
    {
        if (!contain_num(set.arr[sec])) {
            ret_arr[size_arr] = set.arr[sec];
            size_arr++;

        }
    }
    return Set(ret_arr, size_arr);
}


template<class T>
Set<T> Set<T>::operator-(const Set<T>& set)
{
    int* ret_arr = new int[size];
    int size_arr = 0;
    bool flag;
    for (size_t first = 0; first < size; first++)
    {
        flag = true;
        for (size_t sec = 0; sec < set.size; sec++)
        {
            if (arr[first] == set.arr[sec])
                flag = false;
        }
        if (flag)
            ret_arr[size_arr++] = arr[first];
    }
    return Set(ret_arr, size_arr);
}


template<class T>
void Set<T>::operator+(const T add_num)
{
    if (contain_num(add_num))
    {
        std::cout << "Collections already have this num";
        return;
    }
    size++;
    int* new_arr = new int[size];
    for (size_t i = 0; i < size - 1; i++)
    {
        new_arr[i] = arr[i];
    }
    new_arr[size - 1] = add_num;
    if (arr != nullptr)
        delete[] arr;
    arr = new_arr;
}



template <class T> Set<T>& Set<T>::operator+=(const T add_num)
{
    if (contain_num(add_num))
    {
        std::cout << "Collections already have this num";
    }
    else
    {
        size++;
        int* new_arr = new int[size];
        for (size_t i = 0; i < size - 1; i++)
        {
            new_arr[i] = arr[i];
        }
        new_arr[size - 1] = add_num;
        if (arr != nullptr)
            delete[] arr;
        arr = new_arr;
    }
    return *this;
}


template <class T>
void Set<T>::operator-(const T del_num)
{
    if (!contain_num(del_num))
        throw std::logic_error("Delete non-exist element");
    for (size_t i = 0; i < size - 1; i++)
    {
        if (arr[i] == del_num)
        {
            for (; i < size - 1; i++)
                arr[i] = arr[i + 1];
            break;
        }
    }
    size--;
}


template <class T>
Set<T>& Set<T>::operator-=(const T del_num)
{
    if (!contain_num(del_num))
        throw std::logic_error("Delete non-exist element");
    for (size_t i = 0; i < size - 1; i++)
    {
        if (arr[i] == del_num)
        {
            for (; i < size - 1; i++)
                arr[i] = arr[i + 1];
            break;
        }
    }
    size--;
    return *this;
}


template <class T>
int& Set<T>::operator[](const size_t index)
{
    if (arr == nullptr)
        throw std::logic_error("Your array is empty");
    if ((index >= size) || (index < 0)) throw std::logic_error("Index is invalid");
    return arr[index];
}


template <class T>
int Set<T>::operator[](const size_t index) const
{
    if (arr == nullptr)
        throw std::logic_error("Your array is empty");
    if ((index >= size) || (index < 0)) throw std::logic_error("Index is invalid");
    return arr[index];
}


template <class T>
bool Set<T>::operator==(const Set<T>& set)
{
    if (size != set.size)
        return false;
    for (size_t i = 0; i < size; i++)
    {
        if (!contain_num(set.arr[i]))
        {
            return false;
        }
    }
    return true;
}


template <class T>
bool Set<T>::operator!=(const Set<T>& set)
{
    if (size != set.size)
        return true;
    for (size_t i = 0; i < size; i++)
    {
        if (!contain_num(set.arr[i]))
        {
            return true;
        }
    }
    return false;
}


template <class T>
Set<T>& Set<T>::operator=(const Set<T>& set)
{
    if (this == (&set))
        return *this;
    if (arr)
    {
        delete[] arr;
        arr = nullptr;
        size = 0;
    }
    if (set.arr)
    {
        arr = new int[set.size];
        size = set.size;
        for (size_t i = 0; i < size; i++)
        {
            arr[i] = set.arr[i];
        }
    }
    return *this;
}



template <class T>
Set<T> Set<T>::intersection(const Set<T>& set)
{
    size_t N = 0;
    if (set.size < size)
        N = set.size;
    else
        N = size;
    int* arr_in = new int[N];
    int sz = 0;
    for (size_t i = 0; i < set.size; i++)
    {
        if (contain_num(set.arr[i]))
        {
            arr_in[sz++] = set.arr[i];
        }
    }
    return Set(arr_in, sz);
}


template <class T>
std::ostream& operator<<(std::ostream& s, const Set<T>& set)
{
    if (set.size == 0)
        throw std::logic_error("You don't write empty array");
    s << "(";
    for (size_t i = 0; i < set.size - 1; i++) {
        s << set.arr[i] << ", ";
    }
    s << set.arr[set.size - 1];
    return s << ")";
}



template <>
bool Set<std::string>::contain_num(const std::string number)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == number)
            return true;
    }
    return false;
}


template<> inline
Set<std::string>::Set(size_t count)
{
    arr = new int[count];
    size = count;
    size_t i = 0;
    do
    {
        int add_elem;
        std::cout << "Input uniq elem for array: ";
        std::cin >> add_elem;
        if (!contain_num(add_elem))
        {
            arr[i] = add_elem;
            i++;
        }
        else
            std::cout << "This num contain in array" << std::endl;
    } while (i < size);

}

template<>
Set<std::string>::Set(const Set<std::string>& set)
{
    size = set.size;
    arr = new int[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = set.arr[i];
    }
}


template<>
Set<std::string>::~Set()
{
    delete[]arr;
    size = 0;
}


template<>
size_t Set<std::string>::get_size()
{
    return size;
}


template<>
Set<std::string> Set<std::string>::operator+(const Set<std::string>& set)
{
    int* ret_arr = new int[set.size + size];
    int size_arr = 0;

    for (size_t first = 0; first < size; first++, size_arr++) {
        ret_arr[size_arr] = arr[first];

    }
    for (size_t sec = 0; sec < set.size; sec++)
    {
        if (!contain_num(set.arr[sec])) {
            ret_arr[size_arr] = set.arr[sec];
            size_arr++;

        }
    }
    return Set(ret_arr, size_arr);
}


template<>
Set<std::string> Set<std::string>::operator-(const Set<std::string>& set)
{
    int* ret_arr = new int[size];
    int size_arr = 0;
    bool flag;
    for (size_t first = 0; first < size; first++)
    {
        flag = true;
        for (size_t sec = 0; sec < set.size; sec++)
        {
            if (arr[first] == set.arr[sec])
                flag = false;
        }
        if (flag)
            ret_arr[size_arr++] = arr[first];
    }
    return Set(ret_arr, size_arr);
}


template<>
void Set<std::string>::operator+(const std::string add_num)
{
    if (contain_num(add_num))
    {
        std::cout << "Collections already have this num";
        return;
    }
    size++;
    int* new_arr = new int[size];
    for (size_t i = 0; i < size - 1; i++)
    {
        new_arr[i] = arr[i];
    }
    new_arr[size - 1] = add_num;
    if (arr != nullptr)
        delete[] arr;
    arr = new_arr;
}



template <> Set<std::string>& Set<std::string>::operator+=(const std::string add_num)
{
    if (contain_num(add_num))
    {
        std::cout << "Collections already have this num";
    }
    else
    {
        size++;
        int* new_arr = new int[size];
        for (size_t i = 0; i < size - 1; i++)
        {
            new_arr[i] = arr[i];
        }
        new_arr[size - 1] = add_num;
        if (arr != nullptr)
            delete[] arr;
        arr = new_arr;
    }
    return *this;
}


template <>
void Set<std::string>::operator-(const std::string del_num)
{
    if (!contain_num(del_num))
        throw std::logic_error("Delete non-exist element");
    for (size_t i = 0; i < size - 1; i++)
    {
        if (arr[i] == del_num)
        {
            for (; i < size - 1; i++)
                arr[i] = arr[i + 1];
            break;
        }
    }
    size--;
}


template <>
Set<std::string>& Set<std::string>::operator-=(const std::string del_num)
{
    if (!contain_num(del_num))
        throw std::logic_error("Delete non-exist element");
    for (size_t i = 0; i < size - 1; i++)
    {
        if (arr[i] == del_num)
        {
            for (; i < size - 1; i++)
                arr[i] = arr[i + 1];
            break;
        }
    }
    size--;
    return *this;
}


template <>
int& Set<std::string>::operator[](const size_t index)
{
    if (arr == nullptr)
        throw std::logic_error("Your array is empty");
    if ((index >= size) || (index < 0)) throw std::logic_error("Index is invalid");
    return arr[index];
}


template <>
int Set<std::string>::operator[](const size_t index) const
{
    if (arr == nullptr)
        throw std::logic_error("Your array is empty");
    if ((index >= size) || (index < 0)) throw std::logic_error("Index is invalid");
    return arr[index];
}


template <>
bool Set<std::string>::operator==(const Set<std::string>& set)
{
    if (size != set.size)
        return false;
    for (size_t i = 0; i < size; i++)
    {
        if (!contain_num(set.arr[i]))
        {
            return false;
        }
    }
    return true;
}


template <>
bool Set<std::string>::operator!=(const Set<std::string>& set)
{
    if (size != set.size)
        return true;
    for (size_t i = 0; i < size; i++)
    {
        if (!contain_num(set.arr[i]))
        {
            return true;
        }
    }
    return false;
}


template <>
Set<std::string>& Set<std::string>::operator=(const Set<std::string>& set)
{
    if (this == (&set))
        return *this;
    if (arr)
    {
        delete[] arr;
        arr = nullptr;
        size = 0;
    }
    if (set.arr)
    {
        arr = new int[set.size];
        size = set.size;
        for (size_t i = 0; i < size; i++)
        {
            arr[i] = set.arr[i];
        }
    }
    return *this;
}



template <>
Set<std::string> Set<std::string>::intersection(const Set<std::string>& set)
{
    size_t N = 0;
    if (set.size < size)
        N = set.size;
    else
        N = size;
    int* arr_in = new int[N];
    int sz = 0;
    for (size_t i = 0; i < set.size; i++)
    {
        if (contain_num(set.arr[i]))
        {
            arr_in[sz++] = set.arr[i];
        }
    }
    return Set(arr_in, sz);
}


template <>
std::ostream& operator<<(std::ostream& s, const Set<std::string>& set)
{
    if (set.size == 0)
        throw std::logic_error("You don't write empty array");
    s << "(";
    for (size_t i = 0; i < set.size - 1; i++) {
        s << set.arr[i] << ", ";
    }
    s << set.arr[set.size - 1];
    return s << ")";
}



template <>
bool Set<std::string>::contain_num(const std::string number)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == number)
            return true;
    }
    return false;
}


template<> inline
Set<std::pair<int, double>>::Set(size_t count)
{
    arr = new int[count];
    size = count;
    size_t i = 0;
    do
    {
        int add_elem;
        std::cout << "Input uniq elem for array: ";
        std::cin >> add_elem;
        if (!contain_num(add_elem))
        {
            arr[i] = add_elem;
            i++;
        }
        else
            std::cout << "This num contain in array" << std::endl;
    } while (i < size);

}

template<>
Set<std::pair<int, double>>::Set(const Set<std::pair<int, double>>& set)
{
    size = set.size;
    arr = new int[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = set.arr[i];
    }
}


template<>
Set<std::pair<int, double>>::~Set()
{
    delete[]arr;
    size = 0;
}


template<>
size_t Set<std::pair<int, double>>::get_size()
{
    return size;
}


template<>
Set<std::pair<int, double>> Set<std::pair<int, double>>::operator+(const Set<std::pair<int, double>>& set)
{
    int* ret_arr = new int[set.size + size];
    int size_arr = 0;

    for (size_t first = 0; first < size; first++, size_arr++) {
        ret_arr[size_arr] = arr[first];

    }
    for (size_t sec = 0; sec < set.size; sec++)
    {
        if (!contain_num(set.arr[sec])) {
            ret_arr[size_arr] = set.arr[sec];
            size_arr++;

        }
    }
    return Set(ret_arr, size_arr);
}


template<>
Set<std::pair<int, double>> Set<std::pair<int, double>>::operator-(const Set<std::pair<int, double>>& set)
{
    int* ret_arr = new int[size];
    int size_arr = 0;
    bool flag;
    for (size_t first = 0; first < size; first++)
    {
        flag = true;
        for (size_t sec = 0; sec < set.size; sec++)
        {
            if (arr[first] == set.arr[sec])
                flag = false;
        }
        if (flag)
            ret_arr[size_arr++] = arr[first];
    }
    return Set(ret_arr, size_arr);
}


template<>
void Set<std::pair<int, double>>::operator+(const std::pair<int, double> add_num)
{
    if (contain_num(add_num))
    {
        std::cout << "Collections already have this num";
        return;
    }
    size++;
    int* new_arr = new int[size];
    for (size_t i = 0; i < size - 1; i++)
    {
        new_arr[i] = arr[i];
    }
    new_arr[size - 1] = add_num;
    if (arr != nullptr)
        delete[] arr;
    arr = new_arr;
}



template <> Set<std::pair<int, double>>& Set<std::pair<int, double>>::operator+=(const std::pair<int, double> add_num)
{
    if (contain_num(add_num))
    {
        std::cout << "Collections already have this num";
    }
    else
    {
        size++;
        int* new_arr = new int[size];
        for (size_t i = 0; i < size - 1; i++)
        {
            new_arr[i] = arr[i];
        }
        new_arr[size - 1] = add_num;
        if (arr != nullptr)
            delete[] arr;
        arr = new_arr;
    }
    return *this;
}


template <>
void Set<std::pair<int, double>>::operator-(const std::pair<int, double> del_num)
{
    if (!contain_num(del_num))
        throw std::logic_error("Delete non-exist element");
    for (size_t i = 0; i < size - 1; i++)
    {
        if (arr[i] == del_num)
        {
            for (; i < size - 1; i++)
                arr[i] = arr[i + 1];
            break;
        }
    }
    size--;
}


template <>
Set<std::pair<int, double>>& Set<std::pair<int, double>>::operator-=(const std::pair<int, double> del_num)
{
    if (!contain_num(del_num))
        throw std::logic_error("Delete non-exist element");
    for (size_t i = 0; i < size - 1; i++)
    {
        if (arr[i] == del_num)
        {
            for (; i < size - 1; i++)
                arr[i] = arr[i + 1];
            break;
        }
    }
    size--;
    return *this;
}


template <>
int& Set<std::pair<int, double>>::operator[](const std::pair index)
{
    if (arr == nullptr)
        throw std::logic_error("Your array is empty");
    if ((index >= size) || (index < 0)) throw std::logic_error("Index is invalid");
    return arr[index];
}


template <>
int Set<std::pair<int, double>>::operator[](const std::pair<int, double> index) const
{
    if (arr == nullptr)
        throw std::logic_error("Your array is empty");
    if ((index >= size) || (index < 0)) throw std::logic_error("Index is invalid");
    return arr[index];
}


template <>
bool Set<std::pair<int, double>>::operator==(const Set<std::pair<int, double>>& set)
{
    if (size != set.size)
        return false;
    for (size_t i = 0; i < size; i++)
    {
        if (!contain_num(set.arr[i]))
        {
            return false;
        }
    }
    return true;
}


template <>
bool Set<T>::operator!=(const Set<std::pair<int, double>>& set)
{
    if (size != set.size)
        return true;
    for (size_t i = 0; i < size; i++)
    {
        if (!contain_num(set.arr[i]))
        {
            return true;
        }
    }
    return false;
}


template <>
Set<std::pair<int, double>>& Set<std::pair<int, double>>::operator=(const Set<std::pair<int, double>>& set)
{
    if (this == (&set))
        return *this;
    if (arr)
    {
        delete[] arr;
        arr = nullptr;
        size = 0;
    }
    if (set.arr)
    {
        arr = new int[set.size];
        size = set.size;
        for (size_t i = 0; i < size; i++)
        {
            arr[i] = set.arr[i];
        }
    }
    return *this;
}



template <>
Set<std::pair<int, double>> Set<std::pair<int, double>>::intersection(const Set<std::pair<int, double>>& set)
{
    size_t N = 0;
    if (set.size < size)
        N = set.size;
    else
        N = size;
    int* arr_in = new int[N];
    int sz = 0;
    for (size_t i = 0; i < set.size; i++)
    {
        if (contain_num(set.arr[i]))
        {
            arr_in[sz++] = set.arr[i];
        }
    }
    return Set(arr_in, sz);
}


template <>
std::ostream& operator<<(std::ostream& s, const Set<std::pair<int, double>>& set)
{
    if (set.size == 0)
        throw std::logic_error("You don't write empty array");
    s << "(";
    for (size_t i = 0; i < set.size - 1; i++) {
        s << set.arr[i] << ", ";
    }
    s << set.arr[set.size - 1];
    return s << ")";
}



template <>
bool Set<std::pair<int, double>>::contain_num(const std::pair<int, double> number)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == number)
            return true;
    }
    return false;
}
