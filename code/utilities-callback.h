#ifndef CALLBACK_H
#define CALLBACK_H

namespace Utilities
{
  class Callback0
  {
  public:
    Callback0(Function f) : mFunction(f){}

    virtual void operator()() const
    {
      *mFunction();
    }

  private:
    typedef void *Function();

    Function mFunction;
  };

  template<typename Object>
  class ObjectCallback0 : public Callback0
  {
  public:
    ObjectCallback0(Object* o, Function f) : Callback0(f), mObject(o), mFunction(f){}

    virtual void operator()() const
    {
      mObject->*mFunction();
    }

  private:
    typedef void (Object::*Function)();

    Object* mObject;
    Function mFunction;
  };

  template<typename Arg>
  class Callback1
  {
  public:
    Callback1(Function f) : mFunction(f){}

    virtual void operator()(const Arg& a) const
    {
      *mFunction(a);
    }

  private:
    typedef void *Function(const Arg&);

    Function mFunction;
  };

  template<typename Object, typename Arg>
  class ObjectCallback1 : public Callback1
  {
  public:
    ObjectCallback1(Object* o, Function f) : Callback1(f), mObject(o), mFunction(f){}

    virtual void operator()(const Arg& a) const
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
