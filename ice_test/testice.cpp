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
// Generated from file `testice.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#include <testice.h>
#include <IceUtil/PushDisableWarnings.h>
#include <Ice/LocalException.h>
#include <Ice/ValueFactory.h>
#include <Ice/Outgoing.h>
#include <Ice/OutgoingAsync.h>
#include <Ice/InputStream.h>
#include <Ice/OutputStream.h>
#include <IceUtil/Iterator.h>
#include <IceUtil/PopDisableWarnings.h>

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

namespace
{

const ::std::string __WG__WGTestIce_ids[2] =
{
    "::Ice::Object",
    "::WG::WGTestIce"
};
const ::std::string __WG__WGTestIce_ops[] =
{
    "GetTime",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "ping"
};
const ::std::string __WG__WGTestIce__ping_name = "ping";
const ::std::string __WG__WGTestIce__GetTime_name = "GetTime";

}

void
WG::WGTestIcePrx::__ping(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<int>>& __outAsync, const ::Ice::Context& __ctx)
{
    __checkAsyncTwowayOnly(__WG__WGTestIce__ping_name);
    __outAsync->invoke(__WG__WGTestIce__ping_name, ::Ice::OperationMode::Normal, ::Ice::DefaultFormat, __ctx, 
        nullptr,
        nullptr);
}

void
WG::WGTestIcePrx::__GetTime(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<Result_GetTime>>& __outAsync, const ::Ice::Context& __ctx)
{
    __checkAsyncTwowayOnly(__WG__WGTestIce__GetTime_name);
    __outAsync->invoke(__WG__WGTestIce__GetTime_name, ::Ice::OperationMode::Normal, ::Ice::DefaultFormat, __ctx, 
        nullptr,
        nullptr,
        [&](::Ice::InputStream* __is)
        {
            Result_GetTime v;
            __is->read(v.strTime);
            __is->read(v.returnValue);
            return v;
        });
}

const ::std::string&
WG::WGTestIcePrx::ice_staticId()
{
    return WG::WGTestIce::ice_staticId();
}

bool
WG::WGTestIce::ice_isA(::std::string _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__WG__WGTestIce_ids, __WG__WGTestIce_ids + 2, _s);
}

::std::vector< ::std::string>
WG::WGTestIce::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__WG__WGTestIce_ids[0], &__WG__WGTestIce_ids[2]);
}

const ::std::string&
WG::WGTestIce::ice_id(const ::Ice::Current&) const
{
    return __WG__WGTestIce_ids[1];
}

const ::std::string&
WG::WGTestIce::ice_staticId()
{
    return __WG__WGTestIce_ids[1];
}

::Ice::DispatchStatus
WG::WGTestIce::___ping(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::OperationMode::Normal, __current.mode);
    __inS.readEmptyParams();
    int __ret = ping(__current);
    auto __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
WG::WGTestIce::___GetTime(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::OperationMode::Normal, __current.mode);
    __inS.readEmptyParams();
    ::std::string __p_strTime;
    int __ret = GetTime(__p_strTime, __current);
    auto __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__p_strTime);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
WG::WGTestIce::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& c)
{
    ::std::pair< const ::std::string*, const ::std::string*> r = ::std::equal_range(__WG__WGTestIce_ops, __WG__WGTestIce_ops + 6, c.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, c.id, c.facet, c.operation);
    }

    switch(r.first - __WG__WGTestIce_ops)
    {
        case 0:
        {
            return ___GetTime(in, c);
        }
        case 1:
        {
            return ___ice_id(in, c);
        }
        case 2:
        {
            return ___ice_ids(in, c);
        }
        case 3:
        {
            return ___ice_isA(in, c);
        }
        case 4:
        {
            return ___ice_ping(in, c);
        }
        case 5:
        {
            return ___ping(in, c);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, c.id, c.facet, c.operation);
}

#else // C++98 mapping

namespace
{

const ::std::string __WG__WGTestIce__ping_name = "ping";

const ::std::string __WG__WGTestIce__GetTime_name = "GetTime";

}
::IceProxy::Ice::Object* ::IceProxy::WG::upCast(::IceProxy::WG::WGTestIce* p) { return p; }

void
::IceProxy::WG::__read(::Ice::InputStream* __is, ::IceInternal::ProxyHandle< ::IceProxy::WG::WGTestIce>& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::WG::WGTestIce;
        v->__copyFrom(proxy);
    }
}

::Ice::Int
IceProxy::WG::WGTestIce::ping(const ::Ice::Context& __ctx)
{
    __checkTwowayOnly(__WG__WGTestIce__ping_name);
    ::IceInternal::Outgoing __og(this, __WG__WGTestIce__ping_name, ::Ice::Normal, __ctx);
    __og.writeEmptyParams();
    if(!__og.invoke())
    {
        try
        {
            __og.throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_id());
            throw __uue;
        }
    }
    ::Ice::Int __ret;
    ::Ice::InputStream* __is = __og.startReadParams();
    __is->read(__ret);
    __og.endReadParams();
    return __ret;
}

::Ice::AsyncResultPtr
IceProxy::WG::WGTestIce::__begin_ping(const ::Ice::Context& __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__WG__WGTestIce__ping_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::CallbackOutgoing(this, __WG__WGTestIce__ping_name, __del, __cookie);
    try
    {
        __result->prepare(__WG__WGTestIce__ping_name, ::Ice::Normal, __ctx);
        __result->writeEmptyParams();
        __result->invoke(__WG__WGTestIce__ping_name);
    }
    catch(const ::Ice::Exception& __ex)
    {
        __result->abort(__ex);
    }
    return __result;
}

::Ice::Int
IceProxy::WG::WGTestIce::end_ping(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __WG__WGTestIce__ping_name);
    ::Ice::Int __ret;
    if(!__result->__wait())
    {
        try
        {
            __result->__throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_id());
        }
    }
    ::Ice::InputStream* __is = __result->__startReadParams();
    __is->read(__ret);
    __result->__endReadParams();
    return __ret;
}

::Ice::Int
IceProxy::WG::WGTestIce::GetTime(::std::string& __p_strTime, const ::Ice::Context& __ctx)
{
    __checkTwowayOnly(__WG__WGTestIce__GetTime_name);
    ::IceInternal::Outgoing __og(this, __WG__WGTestIce__GetTime_name, ::Ice::Normal, __ctx);
    __og.writeEmptyParams();
    if(!__og.invoke())
    {
        try
        {
            __og.throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_id());
            throw __uue;
        }
    }
    ::Ice::Int __ret;
    ::Ice::InputStream* __is = __og.startReadParams();
    __is->read(__p_strTime);
    __is->read(__ret);
    __og.endReadParams();
    return __ret;
}

::Ice::AsyncResultPtr
IceProxy::WG::WGTestIce::__begin_GetTime(const ::Ice::Context& __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__WG__WGTestIce__GetTime_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::CallbackOutgoing(this, __WG__WGTestIce__GetTime_name, __del, __cookie);
    try
    {
        __result->prepare(__WG__WGTestIce__GetTime_name, ::Ice::Normal, __ctx);
        __result->writeEmptyParams();
        __result->invoke(__WG__WGTestIce__GetTime_name);
    }
    catch(const ::Ice::Exception& __ex)
    {
        __result->abort(__ex);
    }
    return __result;
}

::Ice::Int
IceProxy::WG::WGTestIce::end_GetTime(::std::string& __p_strTime, const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __WG__WGTestIce__GetTime_name);
    ::Ice::Int __ret;
    if(!__result->__wait())
    {
        try
        {
            __result->__throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_id());
        }
    }
    ::Ice::InputStream* __is = __result->__startReadParams();
    __is->read(__p_strTime);
    __is->read(__ret);
    __result->__endReadParams();
    return __ret;
}

const ::std::string&
IceProxy::WG::WGTestIce::ice_staticId()
{
    return ::WG::WGTestIce::ice_staticId();
}

::Ice::Object* WG::upCast(::WG::WGTestIce* p) { return p; }

namespace
{
const ::std::string __WG__WGTestIce_ids[2] =
{
    "::Ice::Object",
    "::WG::WGTestIce"
};

}

bool
WG::WGTestIce::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__WG__WGTestIce_ids, __WG__WGTestIce_ids + 2, _s);
}

::std::vector< ::std::string>
WG::WGTestIce::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__WG__WGTestIce_ids[0], &__WG__WGTestIce_ids[2]);
}

const ::std::string&
WG::WGTestIce::ice_id(const ::Ice::Current&) const
{
    return __WG__WGTestIce_ids[1];
}

const ::std::string&
WG::WGTestIce::ice_staticId()
{
#ifdef ICE_HAS_THREAD_SAFE_LOCAL_STATIC
    static const ::std::string typeId = "::WG::WGTestIce";
    return typeId;
#else
    return __WG__WGTestIce_ids[1];
#endif
}

::Ice::DispatchStatus
WG::WGTestIce::___ping(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    __inS.readEmptyParams();
    ::Ice::Int __ret = ping(__current);
    ::Ice::OutputStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
WG::WGTestIce::___GetTime(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    __inS.readEmptyParams();
    ::std::string __p_strTime;
    ::Ice::Int __ret = GetTime(__p_strTime, __current);
    ::Ice::OutputStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__p_strTime);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

namespace
{
const ::std::string __WG__WGTestIce_all[] =
{
    "GetTime",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "ping"
};

}

::Ice::DispatchStatus
WG::WGTestIce::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< const ::std::string*, const ::std::string*> r = ::std::equal_range(__WG__WGTestIce_all, __WG__WGTestIce_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __WG__WGTestIce_all)
    {
        case 0:
        {
            return ___GetTime(in, current);
        }
        case 1:
        {
            return ___ice_id(in, current);
        }
        case 2:
        {
            return ___ice_ids(in, current);
        }
        case 3:
        {
            return ___ice_isA(in, current);
        }
        case 4:
        {
            return ___ice_ping(in, current);
        }
        case 5:
        {
            return ___ping(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
WG::WGTestIce::__writeImpl(::Ice::OutputStream* __os) const
{
    __os->startSlice(ice_staticId(), -1, true);
    __os->endSlice();
}

void
WG::WGTestIce::__readImpl(::Ice::InputStream* __is)
{
    __is->startSlice();
    __is->endSlice();
}

void 
WG::__patch(WGTestIcePtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = ::WG::WGTestIcePtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(::WG::WGTestIce::ice_staticId(), v);
    }
}

#endif
