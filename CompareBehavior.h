#ifndef COMPAREBEHAVIOR_H
#define COMPAREBEHAVIOR_H

template <class T>
class CompareBehavior
{
  public:
    CompareBehavior();
    ~CompareBehavior();
    virtual bool compare(T, T) = 0;
};

template <class T>
class AscBehavior: public CompareBehavior<T>
{
  public:
    bool compare(T, T);
};

template <class T>
class DescBehavior: public CompareBehavior<T>
{
  public:
    bool compare(T, T);
};


template <class T>
CompareBehavior<T>::CompareBehavior() { };

template <class T>
CompareBehavior<T>::~CompareBehavior() { };

template <class T>
bool AscBehavior<T>::compare(T a, T b)
{
  return a < b;
}

template <class T>
bool DescBehavior<T>::compare(T a, T b)
{
    return a > b;
}


#endif
