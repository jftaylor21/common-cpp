#ifndef CALLBACK_H
#define CALLBACK_H
#include <iostream>

namespace Utilities
{
  void nop();

  class Callback0
  {
  public:
    typedef void (*Function)();

    Callback0(Function f) : mFunction(f){}

    virtual Callback0* clone() const
    {
      return new Callback0(*this);
    }

    virtual void operator()() const
    {
      mFunction();
    }

  private:
    Function mFunction;
  };

  template<typename Object>
  class ObjectCallback0 : public Callback0
  {
  public:
    typedef void (Object::*Function)();

    ObjectCallback0(Object* o, Function f) : Callback0(nop), mObject(o), mFunction(f){}

    virtual ObjectCallback0* clone() const
    {
      return new ObjectCallback0<Object>(*this);
    }

    virtual void operator()() const
    {
      (mObject->*mFunction)();
    }

  private:
    Object* mObject;
    Function mFunction;
  };

  template<typename Arg>
  class Callback1
  {
  public:
    typedef void (*Function)(const Arg&);

    Callback1(Function f) : mFunction(f){}

    virtual Callback1* clone() const
    {
      return new Callback1<Arg>(*this);
    }

    virtual void operator()(const Arg& a) const
    {
      mFunction(a);
    }

  private:
    Function mFunction;
  };

  template<typename Object, typename Arg>
  class ObjectCallback1 : public Callback1<Arg>
  {
  public:
    typedef void (Object::*Function)(const Arg&);

    ObjectCallback1(Object* o, Function f) : Callback1<Arg>(nop), mObject(o), mFunction(f){}

    virtual ObjectCallback1* clone() const
    {
      return new ObjectCallback1<Object, Arg>(*this);
    }

    virtual void operator()(const Arg& a) const
    {
      (mObject->*mFunction)(a);
    }

  private:
    Object* mObject;
    Function mFunction;
  };

  template<typename Arg1, typename Arg2>
  class Callback2
  {
  public:
    typedef void (*Function)(const Arg1&, const Arg2&);

    Callback2(Function f) : mFunction(f){}

    virtual Callback2* clone() const
    {
      return new Callback2<Arg1, Arg2>(*this);
    }

    virtual void operator()(const Arg1& a1, const Arg2& a2) const
    {
      mFunction(a1, a2);
    }

  private:
    Function mFunction;
  };

  template<typename Object, typename Arg1, typename Arg2>
  class ObjectCallback2 : public Callback2<Arg1, Arg2>
  {
  public:
    typedef void (Object::*Function)(const Arg1&, const Arg2&);

    ObjectCallback2(Object* o, Function f) : Callback2<Arg1, Arg2>(nop), mObject(o), mFunction(f){}

    virtual ObjectCallback2* clone() const
    {
      return new ObjectCallback2<Object, Arg1, Arg2>(*this);
    }

    virtual void operator()(const Arg1& a1, const Arg2& a2) const
    {
      (mObject->*mFunction)(a1, a2);
    }

  private:
    Object* mObject;
    Function mFunction;
  };

  template<typename Arg1, typename Arg2, typename Arg3>
  class Callback3
  {
  public:
    typedef void (*Function)(const Arg1&, const Arg2&, const Arg3&);

    Callback3(Function f) : mFunction(f){}

    virtual Callback3* clone() const
    {
      return new Callback3<Arg1, Arg2, Arg3>(*this);
    }

    virtual void operator()(const Arg1& a1, const Arg2& a2, const Arg3& a3) const
    {
      mFunction(a1, a2, a3);
    }

  private:
    Function mFunction;
  };

  template<typename Object, typename Arg1, typename Arg2, typename Arg3>
  class ObjectCallback3 : public Callback3<Arg1, Arg2, Arg3>
  {
  public:
    typedef void (Object::*Function)(const Arg1&, const Arg2&, const Arg3&);

    ObjectCallback3(Object* o, Function f) : Callback3<Arg1, Arg2, Arg3>(nop), mObject(o), mFunction(f){}

    virtual ObjectCallback3* clone() const
    {
      return new ObjectCallback3<Object, Arg1, Arg2, Arg3>(*this);
    }

    virtual void operator()(const Arg1& a1, const Arg2& a2, const Arg3& a3) const
    {
      (mObject->*mFunction)(a1, a2, a3);
    }

  private:
    Object* mObject;
    Function mFunction;
  };
}

#endif
