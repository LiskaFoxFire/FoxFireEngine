#pragma once
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <functional>

class Object;
template<class T>
class Datum;
template<class R, class... Args>
class Behavior;

//==================================================================//

class Object {};

template<class T>
class Datum
{
  public:
  std::unordered_map<Object*, T> data;
  T* operator [] (Object* object)
  {
    if(!data.contains(object)) return nullptr;

    return &(data[object]);
  };
  T* operator [] (Object& object)
  {
    if(!data.contains(&object)) return nullptr;
    return &(data[&object]);
  };
};

template<class R, class... Args>
class Behavior
{
  public:
  std::unordered_set<Object*> objects;
  std::function<R(Object*, Args...)> behavior;
  std::function<R(Args...)>& operator [] (Object* object)
  {
    if(!objects.contains(object)) return std::function<R(Args...)>();
    return [&](Args... args) -> R
    {
      return behavior(object, args...);
    };
  };
  std::function<R(Args...)>& operator [] (Object& object)
  {
    if(!objects.contains(object)) return std::function<R(Args...)>();
    return [&](Args... args) -> R
    {
      return behavior(&object, args...);
    };
  };

  Behavior<R(Args...)>(std::function<R(Object*, Args...)> behavior) :
  behavior(behavior)
  {
    
  }
};

//===================================================================//

template<class T>
T& operator + (Object& object, Datum<T>& datum)
{
  return datum.data[&object];
};

template<class T>
T& operator + (Object* object, Datum<T>& datum)
{
  return datum.data[object];
};

template<class R, class... Args>
void operator += (Object& object, Behavior<R(Args...)> behavior)
{
  behavior.objects.insert(&object);
};

template<class R, class... Args>
void operator += (Object* object, Behavior<R(Args...)> behavior)
{
  behavior.objects.insert(object);
};
