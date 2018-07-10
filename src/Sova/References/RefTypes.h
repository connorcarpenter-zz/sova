#pragma once

//
// Created by connor on 7/9/18.
//

namespace Sova {
    typedef void* TypeId;
}
#define SovaBaseTypeDecl(CLASS)\
    template<class T> static Sova::TypeId getTypeId() { static char _type_id; return &_type_id; };\
    virtual bool isOfType(const Sova::TypeId t) const { return t == getTypeId<CLASS>(); };\
    template<class T> bool IsA() const { return this->isOfType(getTypeId<T>()); };\
    template<class T> Sova::Ref<T> DynamicCast() const { return (T*) (this->isOfType(getTypeId<T>()) ? this : nullptr); };\

#define SovaTypeDecl(CLASS, BASECLASS)\
    virtual bool isOfType(const Sova::TypeId t) const override { return t == getTypeId<CLASS>() ? true : BASECLASS::isOfType(t); };\
