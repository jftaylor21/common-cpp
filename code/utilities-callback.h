#ifndef CALLBACK_H
#define CALLBACK_H

namespace Utilities
{
  template<typename Object>
  class Callback0
  {
  public:
    Callback0(Object* o, Function f) : mObject(o), mFunction(f){}

    void operator()() const
    {
      mObject->*mFunction();
    }

  private:
    typedef void (Object::*Function)();

    Object* mObject;
    Function mFunction;
  };

  template<typename Object, typename Arg>
  class Callback1
  {
  public:
    Callback1(Object* o, Function f) : mObject(o), mFunction(f){}

    void operator()(const Arg& a) const
    {
      mObject->*mFunction(a);
    }

  private:
    typedef void (Object::*Function)(const Arg&);

    Object* mObject;
    Function mFunction;
  };
}

#endif
