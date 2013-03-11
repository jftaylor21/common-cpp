#ifndef CALLBACK_H
#define CALLBACK_H

namespace Utilities
{
  void nop();

  class Callback0
  {
    typedef void (*Function)();

    Function mFunction;

  public:
    Callback0(Function f) : mFunction(f){}

    virtual void operator()() const
    {
      mFunction();
    }
  };

  template<typename Object>
  class ObjectCallback0 : public Callback0
  {
    typedef void (Object::*Function)();

    Object* mObject;
    Function mFunction;

  public:
    ObjectCallback0(Object* o, Function f) : Callback0(nop), mObject(o), mFunction(f){}

    virtual void operator()() const
    {
      (mObject->*mFunction)();
    }
  };

  template<typename Arg>
  class Callback1
  {
    typedef void (*Function)(const Arg&);

    Function mFunction;

  public:
    Callback1(Function f) : mFunction(f){}

    virtual void operator()(const Arg& a) const
    {
      mFunction(a);
    }
  };

  template<typename Object, typename Arg>
  class ObjectCallback1 : public Callback1<Arg>
  {
    typedef void (Object::*Function)(const Arg&);

    Object* mObject;
    Function mFunction;

  public:
    ObjectCallback1(Object* o, Function f) : Callback1<Arg>(nop), mObject(o), mFunction(f){}

    virtual void operator()(const Arg& a) const
    {
      (mObject->*mFunction)(a);
    }
  };
}

#endif
