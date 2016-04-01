// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.7.0
//
// <auto-generated>
//
// Generated from file `t.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __t_h__
#define __t_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/ValueF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/GCObject.h>
#include <Ice/Value.h>
#include <Ice/Incoming.h>
#include <Ice/FactoryTableInit.h>
#include <IceUtil/ScopedArray.h>
#include <IceUtil/Optional.h>
#include <IceUtil/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 307
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 0
#       error Ice patch level mismatch!
#   endif
#endif

#ifdef ICE_CPP11_MAPPING // C++11 mapping

namespace Pri
{

class xyd;
class xydPrx;
class Xu;
class XuPrx;

}

namespace Pri
{

typedef ::std::vector<int> seqOpt;

typedef ::std::map< ::Ice::Byte, ::Pri::seqOpt> dict;

class Err : public ::Ice::UserException
{
public:

    Err() = default;

    Err(const ::Pri::seqOpt& __ice_maxi) :
        maxi(::std::move(__ice_maxi))
    {
    }

    virtual ::std::string ice_id() const;
    virtual void ice_throw() const;

    ::Pri::seqOpt maxi;

protected:

    virtual void __writeImpl(::Ice::OutputStream*) const;
    virtual void __readImpl(::Ice::InputStream*);
};

static Err __Err_init;

}

namespace Pri
{

class xydPrx : public virtual ::Ice::Proxy<xydPrx, ::Ice::ObjectPrx>
{
public:

    struct Result_pri
    {
        int i;
        int returnValue;
    };

    int pri(int& __p_i, const ::Ice::Context& __ctx = Ice::noExplicitContext)
    {
        auto __result = 
        makePromiseOutgoing<Result_pri>(true, this, &Pri::xydPrx::__pri, __ctx).get();
        __p_i = __result.i;
        return __result.returnValue;
    }

    ::std::function<void ()>
    pri_async(::std::function<void (int, int)> __response,
              ::std::function<void (::std::exception_ptr)> __ex = nullptr,
              ::std::function<void (bool)> __sent = nullptr,
              const ::Ice::Context& __ctx = Ice::noExplicitContext)
    {
        auto __responseCb = [__response](Result_pri&& result)
        {
            __response(result.returnValue, result.i);
        };
        return makeLambdaOutgoing<Result_pri>(__responseCb, __ex, __sent, this, &Pri::xydPrx::__pri, __ctx);
    }

    template<template<typename> class P = ::std::promise>
    auto pri_async(const ::Ice::Context& __ctx = Ice::noExplicitContext)
        -> decltype(::std::declval<P<Result_pri>>().get_future())
    {
        return makePromiseOutgoing<Result_pri, P>(false, this, &Pri::xydPrx::__pri, __ctx);
    }

    void __pri(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<Result_pri>>&, const ::Ice::Context& = Ice::noExplicitContext);

    static const ::std::string& ice_staticId();

protected: 

    xydPrx() = default;
    friend ::std::shared_ptr<xydPrx> IceInternal::createProxy<xydPrx>();
};

class XuPrx : public virtual ::Ice::Proxy<XuPrx, ::Ice::ObjectPrx>
{
public:

    void add(const ::std::shared_ptr<::Pri::xydPrx>& __p_x, const ::Ice::Context& __ctx = Ice::noExplicitContext)
    {
        
        makePromiseOutgoing(true, this, &Pri::XuPrx::__add, __p_x, __ctx).get();
    }

    ::std::function<void ()>
    add_async(const ::std::shared_ptr<::Pri::xydPrx>& __p_x, 
              ::std::function<void ()> __response,
              ::std::function<void (::std::exception_ptr)> __ex = nullptr,
              ::std::function<void (bool)> __sent = nullptr,
              const ::Ice::Context& __ctx = Ice::noExplicitContext)
    {
        return makeLambdaOutgoing(__response, __ex, __sent, this, &Pri::XuPrx::__add, __p_x, __ctx);
    }

    template<template<typename> class P = ::std::promise>
    auto add_async(const ::std::shared_ptr<::Pri::xydPrx>& __p_x, const ::Ice::Context& __ctx = Ice::noExplicitContext)
        -> decltype(::std::declval<P<void>>().get_future())
    {
        return makePromiseOutgoing<P>(false, this, &Pri::XuPrx::__add, __p_x, __ctx);
    }

    void __add(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<void>>&, const ::std::shared_ptr<::Pri::xydPrx>&, const ::Ice::Context& = Ice::noExplicitContext);

    ::std::shared_ptr<::Pri::xydPrx> get(const ::Ice::Context& __ctx = Ice::noExplicitContext)
    {
        return 
        makePromiseOutgoing<::std::shared_ptr<::Pri::xydPrx>>(true, this, &Pri::XuPrx::__get, __ctx).get();
    }

    ::std::function<void ()>
    get_async(::std::function<void (::std::shared_ptr<::Pri::xydPrx>)> __response,
              ::std::function<void (::std::exception_ptr)> __ex = nullptr,
              ::std::function<void (bool)> __sent = nullptr,
              const ::Ice::Context& __ctx = Ice::noExplicitContext)
    {
        return makeLambdaOutgoing<::std::shared_ptr<::Pri::xydPrx>>(__response, __ex, __sent, this, &Pri::XuPrx::__get, __ctx);
    }

    template<template<typename> class P = ::std::promise>
    auto get_async(const ::Ice::Context& __ctx = Ice::noExplicitContext)
        -> decltype(::std::declval<P<::std::shared_ptr<::Pri::xydPrx>>>().get_future())
    {
        return makePromiseOutgoing<::std::shared_ptr<::Pri::xydPrx>, P>(false, this, &Pri::XuPrx::__get, __ctx);
    }

    void __get(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<::std::shared_ptr<::Pri::xydPrx>>>&, const ::Ice::Context& = Ice::noExplicitContext);

    static const ::std::string& ice_staticId();

protected: 

    XuPrx() = default;
    friend ::std::shared_ptr<XuPrx> IceInternal::createProxy<XuPrx>();
};

}

namespace Pri
{

class xyd : public virtual ::Ice::Object
{
public:

    typedef xydPrx ProxyType;

    virtual bool ice_isA(::std::string, const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    static const ::std::string& ice_staticId();

    virtual int pri(int&, const ::Ice::Current& = ::Ice::noExplicitCurrent) = 0;

    ::Ice::DispatchStatus ___pri(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
};

class Xu : public virtual ::Ice::Object
{
public:

    typedef XuPrx ProxyType;

    virtual bool ice_isA(::std::string, const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    static const ::std::string& ice_staticId();

    virtual void add(::std::shared_ptr<::Pri::xydPrx>, const ::Ice::Current& = ::Ice::noExplicitCurrent) = 0;

    ::Ice::DispatchStatus ___add(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::shared_ptr<::Pri::xydPrx> get(const ::Ice::Current& = ::Ice::noExplicitCurrent) = 0;

    ::Ice::DispatchStatus ___get(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
};

}

namespace Pri
{

typedef ::std::shared_ptr<xyd> xydPtr;
class xydPrx;
typedef ::std::shared_ptr<xydPrx> xydPrxPtr;

typedef ::std::shared_ptr<Xu> XuPtr;
class XuPrx;
typedef ::std::shared_ptr<XuPrx> XuPrxPtr;

}

#else // C++98 mapping

namespace IceProxy
{

namespace Pri
{

class xyd;
void __read(::Ice::InputStream*, ::IceInternal::ProxyHandle< ::IceProxy::Pri::xyd>&);
::IceProxy::Ice::Object* upCast(::IceProxy::Pri::xyd*);

class Xu;
void __read(::Ice::InputStream*, ::IceInternal::ProxyHandle< ::IceProxy::Pri::Xu>&);
::IceProxy::Ice::Object* upCast(::IceProxy::Pri::Xu*);

}

}

namespace Pri
{

class xyd;
::Ice::Object* upCast(::Pri::xyd*);
typedef ::IceInternal::Handle< ::Pri::xyd> xydPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Pri::xyd> xydPrx;
typedef xydPrx xydPrxPtr;
void __patch(xydPtr&, const ::Ice::ObjectPtr&);

class Xu;
::Ice::Object* upCast(::Pri::Xu*);
typedef ::IceInternal::Handle< ::Pri::Xu> XuPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Pri::Xu> XuPrx;
typedef XuPrx XuPrxPtr;
void __patch(XuPtr&, const ::Ice::ObjectPtr&);

}

namespace Pri
{

typedef ::std::vector< ::Ice::Int> seqOpt;

typedef ::std::map< ::Ice::Byte, ::Pri::seqOpt> dict;

class Err : public ::Ice::UserException
{
public:

    Err() {}
    explicit Err(const ::Pri::seqOpt&);
    virtual ~Err() throw();

    virtual ::std::string ice_id() const;
    virtual Err* ice_clone() const;
    virtual void ice_throw() const;

    ::Pri::seqOpt maxi;

protected:
    virtual void __writeImpl(::Ice::OutputStream*) const;
    virtual void __readImpl(::Ice::InputStream*);
};

static Err __Err_init;

}

namespace Ice
{
template<>
struct StreamableTraits< ::Pri::Err>
{
    static const StreamHelperCategory helper = StreamHelperCategoryUserException;
};

}

namespace Pri
{

class Callback_xyd_pri_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_xyd_pri_Base> Callback_xyd_priPtr;

class Callback_Xu_add_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_Xu_add_Base> Callback_Xu_addPtr;

class Callback_Xu_get_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_Xu_get_Base> Callback_Xu_getPtr;

}

namespace IceProxy
{

namespace Pri
{

class xyd : public virtual ::IceProxy::Ice::Proxy< ::IceProxy::Pri::xyd, ::IceProxy::Ice::Object>
{
public:
    ::Ice::Int pri(::Ice::Int& __p_i, const ::Ice::Context& __ctx = ::Ice::noExplicitContext);

    ::Ice::AsyncResultPtr begin_pri(const ::Ice::Context& __ctx = ::Ice::noExplicitContext)
    {
        return __begin_pri(__ctx, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_pri(const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_pri(::Ice::noExplicitContext, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_pri(const ::Ice::Context& __ctx, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_pri(__ctx, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_pri(const ::Pri::Callback_xyd_priPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_pri(::Ice::noExplicitContext, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_pri(const ::Ice::Context& __ctx, const ::Pri::Callback_xyd_priPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_pri(__ctx, __del, __cookie);
    }

    ::Ice::Int end_pri(::Ice::Int& __p_i, const ::Ice::AsyncResultPtr&);
    
private:
    ::Ice::AsyncResultPtr __begin_pri(const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& __cookie = 0);
    
public:
    
    static const ::std::string& ice_staticId();
};

class Xu : public virtual ::IceProxy::Ice::Proxy< ::IceProxy::Pri::Xu, ::IceProxy::Ice::Object>
{
public:
    void add(const ::Pri::xydPrx& __p_x, const ::Ice::Context& __ctx = ::Ice::noExplicitContext);

    ::Ice::AsyncResultPtr begin_add(const ::Pri::xydPrx& __p_x, const ::Ice::Context& __ctx = ::Ice::noExplicitContext)
    {
        return __begin_add(__p_x, __ctx, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_add(const ::Pri::xydPrx& __p_x, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_add(__p_x, ::Ice::noExplicitContext, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_add(const ::Pri::xydPrx& __p_x, const ::Ice::Context& __ctx, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_add(__p_x, __ctx, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_add(const ::Pri::xydPrx& __p_x, const ::Pri::Callback_Xu_addPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_add(__p_x, ::Ice::noExplicitContext, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_add(const ::Pri::xydPrx& __p_x, const ::Ice::Context& __ctx, const ::Pri::Callback_Xu_addPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_add(__p_x, __ctx, __del, __cookie);
    }

    void end_add(const ::Ice::AsyncResultPtr&);
    
private:
    ::Ice::AsyncResultPtr __begin_add(const ::Pri::xydPrx&, const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& __cookie = 0);
    
public:
    ::Pri::xydPrx get(const ::Ice::Context& __ctx = ::Ice::noExplicitContext);

    ::Ice::AsyncResultPtr begin_get(const ::Ice::Context& __ctx = ::Ice::noExplicitContext)
    {
        return __begin_get(__ctx, ::IceInternal::__dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_get(const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_get(::Ice::noExplicitContext, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_get(const ::Ice::Context& __ctx, const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_get(__ctx, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_get(const ::Pri::Callback_Xu_getPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_get(::Ice::noExplicitContext, __del, __cookie);
    }

    ::Ice::AsyncResultPtr begin_get(const ::Ice::Context& __ctx, const ::Pri::Callback_Xu_getPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0)
    {
        return __begin_get(__ctx, __del, __cookie);
    }

    ::Pri::xydPrx end_get(const ::Ice::AsyncResultPtr&);
    
private:
    ::Ice::AsyncResultPtr __begin_get(const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& __cookie = 0);
    
public:
    
    static const ::std::string& ice_staticId();
};

}

}

namespace Pri
{

class xyd : public virtual ::Ice::Object
{
public:

    typedef xydPrx ProxyType;
    typedef xydPtr PointerType;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::Int pri(::Ice::Int&, const ::Ice::Current& = ::Ice::noExplicitCurrent) = 0;
    ::Ice::DispatchStatus ___pri(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

protected:
    virtual void __writeImpl(::Ice::OutputStream*) const;
    virtual void __readImpl(::Ice::InputStream*);
    using ::Ice::Object::__writeImpl;
    using ::Ice::Object::__readImpl;
};

inline bool operator==(const xyd& l, const xyd& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

inline bool operator<(const xyd& l, const xyd& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

class Xu : public virtual ::Ice::Object
{
public:

    typedef XuPrx ProxyType;
    typedef XuPtr PointerType;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::noExplicitCurrent) const;
    static const ::std::string& ice_staticId();

    virtual void add(const ::Pri::xydPrx&, const ::Ice::Current& = ::Ice::noExplicitCurrent) = 0;
    ::Ice::DispatchStatus ___add(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Pri::xydPrx get(const ::Ice::Current& = ::Ice::noExplicitCurrent) = 0;
    ::Ice::DispatchStatus ___get(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

protected:
    virtual void __writeImpl(::Ice::OutputStream*) const;
    virtual void __readImpl(::Ice::InputStream*);
    using ::Ice::Object::__writeImpl;
    using ::Ice::Object::__readImpl;
};

inline bool operator==(const Xu& l, const Xu& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

inline bool operator<(const Xu& l, const Xu& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

}

namespace Pri
{

template<class T>
class CallbackNC_xyd_pri : public Callback_xyd_pri_Base, public ::IceInternal::TwowayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)(::Ice::Int, ::Ice::Int);

    CallbackNC_xyd_pri(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallbackNC<T>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::Pri::xydPrx __proxy = ::Pri::xydPrx::uncheckedCast(__result->getProxy());
        ::Ice::Int i;
        ::Ice::Int __ret;
        try
        {
            __ret = __proxy->end_pri(i, __result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::CallbackNC<T>::exception(__result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::CallbackNC<T>::_callback.get()->*_response)(__ret, i);
        }
    }

    private:

    Response _response;
};

template<class T> Callback_xyd_priPtr
newCallback_xyd_pri(const IceUtil::Handle<T>& instance, void (T::*cb)(::Ice::Int, ::Ice::Int), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_xyd_pri<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_xyd_priPtr
newCallback_xyd_pri(T* instance, void (T::*cb)(::Ice::Int, ::Ice::Int), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_xyd_pri<T>(instance, cb, excb, sentcb);
}

template<class T, typename CT>
class Callback_xyd_pri : public Callback_xyd_pri_Base, public ::IceInternal::TwowayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(::Ice::Int, ::Ice::Int, const CT&);

    Callback_xyd_pri(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallback<T, CT>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::Pri::xydPrx __proxy = ::Pri::xydPrx::uncheckedCast(__result->getProxy());
        ::Ice::Int i;
        ::Ice::Int __ret;
        try
        {
            __ret = __proxy->end_pri(i, __result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::Callback<T, CT>::exception(__result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::Callback<T, CT>::_callback.get()->*_response)(__ret, i, CT::dynamicCast(__result->getCookie()));
        }
    }

    private:

    Response _response;
};

template<class T, typename CT> Callback_xyd_priPtr
newCallback_xyd_pri(const IceUtil::Handle<T>& instance, void (T::*cb)(::Ice::Int, ::Ice::Int, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_xyd_pri<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_xyd_priPtr
newCallback_xyd_pri(T* instance, void (T::*cb)(::Ice::Int, ::Ice::Int, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_xyd_pri<T, CT>(instance, cb, excb, sentcb);
}

template<class T>
class CallbackNC_Xu_add : public Callback_Xu_add_Base, public ::IceInternal::OnewayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)();

    CallbackNC_Xu_add(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallbackNC<T>(obj, cb, excb, sentcb)
    {
    }
};

template<class T> Callback_Xu_addPtr
newCallback_Xu_add(const IceUtil::Handle<T>& instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Xu_add<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_Xu_addPtr
newCallback_Xu_add(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Xu_add<T>(instance, 0, excb, sentcb);
}

template<class T> Callback_Xu_addPtr
newCallback_Xu_add(T* instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Xu_add<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_Xu_addPtr
newCallback_Xu_add(T* instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Xu_add<T>(instance, 0, excb, sentcb);
}

template<class T, typename CT>
class Callback_Xu_add : public Callback_Xu_add_Base, public ::IceInternal::OnewayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const CT&);

    Callback_Xu_add(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallback<T, CT>(obj, cb, excb, sentcb)
    {
    }
};

template<class T, typename CT> Callback_Xu_addPtr
newCallback_Xu_add(const IceUtil::Handle<T>& instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Xu_add<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_Xu_addPtr
newCallback_Xu_add(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Xu_add<T, CT>(instance, 0, excb, sentcb);
}

template<class T, typename CT> Callback_Xu_addPtr
newCallback_Xu_add(T* instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Xu_add<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_Xu_addPtr
newCallback_Xu_add(T* instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Xu_add<T, CT>(instance, 0, excb, sentcb);
}

template<class T>
class CallbackNC_Xu_get : public Callback_Xu_get_Base, public ::IceInternal::TwowayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)(const ::Pri::xydPrx&);

    CallbackNC_Xu_get(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallbackNC<T>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::Pri::XuPrx __proxy = ::Pri::XuPrx::uncheckedCast(__result->getProxy());
        ::Pri::xydPrx __ret;
        try
        {
            __ret = __proxy->end_get(__result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::CallbackNC<T>::exception(__result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::CallbackNC<T>::_callback.get()->*_response)(__ret);
        }
    }

    private:

    Response _response;
};

template<class T> Callback_Xu_getPtr
newCallback_Xu_get(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::Pri::xydPrx&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Xu_get<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_Xu_getPtr
newCallback_Xu_get(T* instance, void (T::*cb)(const ::Pri::xydPrx&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_Xu_get<T>(instance, cb, excb, sentcb);
}

template<class T, typename CT>
class Callback_Xu_get : public Callback_Xu_get_Base, public ::IceInternal::TwowayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const ::Pri::xydPrx&, const CT&);

    Callback_Xu_get(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallback<T, CT>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& __result) const
    {
        ::Pri::XuPrx __proxy = ::Pri::XuPrx::uncheckedCast(__result->getProxy());
        ::Pri::xydPrx __ret;
        try
        {
            __ret = __proxy->end_get(__result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::Callback<T, CT>::exception(__result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::Callback<T, CT>::_callback.get()->*_response)(__ret, CT::dynamicCast(__result->getCookie()));
        }
    }

    private:

    Response _response;
};

template<class T, typename CT> Callback_Xu_getPtr
newCallback_Xu_get(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::Pri::xydPrx&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Xu_get<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_Xu_getPtr
newCallback_Xu_get(T* instance, void (T::*cb)(const ::Pri::xydPrx&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_Xu_get<T, CT>(instance, cb, excb, sentcb);
}

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif
