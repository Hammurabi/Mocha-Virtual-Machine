//
// Created by Riverssen on 2019-01-27.
// Copyright (c) 2019 Riverssen GmbH. All rights reserved.
//

#include <cstdint>
#include "Object.h"




const Field &Struct::GetField(const mfieldid_t fieldID)
{
    return mFields[fieldID % mSize];
}

const mfieldid_t &Struct::GetSize()
{
    return mSize;
}

const std::string &Struct::GetTypeName()
{
    return mTypeName;
}


mfieldid_t Object::GetField(const mfieldid_t fieldID)
{
    return fieldID % mType->GetSize();
}

char Object::GetByteField(const mfieldid_t fieldID)
{
    return static_cast<char*> (mFields)[GetField(fieldID)];
}

short Object::GetShortField(const mfieldid_t fieldID)
{
    return static_cast<short*> (mFields)[GetField(fieldID)];
}

int Object::GetIntField(const mfieldid_t fieldID)
{
    return static_cast<int*> (mFields)[GetField(fieldID)];
}

long Object::GetLongField(const mfieldid_t fieldID)
{
    return static_cast<long*> (mFields)[GetField(fieldID)];
}

float Object::GetFloatField(const mfieldid_t fieldID)
{
    return static_cast<float*> (mFields)[GetField(fieldID)];
}

double Object::GetDoubleField(const mfieldid_t fieldID)
{
    return static_cast<double*> (mFields)[GetField(fieldID)];
}

void Object::SetByteField(const mfieldid_t fieldID, const char i)
{
    static_cast<char*> (mFields)[GetField(fieldID)] = i;
}

void Object::SetShortField(const mfieldid_t fieldID, const short i)
{
    static_cast<short*> (mFields)[GetField(fieldID)] = i;
}

void Object::SetIntField(const mfieldid_t fieldID, const int i)
{
    static_cast<int*> (mFields)[GetField(fieldID)] = i;
}

void Object::SetLongField(const mfieldid_t fieldID, const long i)
{
    static_cast<long*> (mFields)[GetField(fieldID)] = i;
}

void Object::SetFloatField(const mfieldid_t fieldID, const float i)
{
    static_cast<float*> (mFields)[GetField(fieldID)] = i;
}

void Object::SetDoubleField(const mfieldid_t fieldID, const double i)
{
    static_cast<double*> (mFields)[GetField(fieldID)] = i;
}

Object *Object::GetObjectField(const mfieldid_t fieldID)
{
    return reinterpret_cast<Object*> (GetLongField(fieldID));
}

void Object::SetObjectField(const mfieldid_t fieldID, const Object* i)
{
    SetLongField(fieldID, reinterpret_cast<long> (i));
}

Object::Object(Struct *type)
{
}

Field::Field(std::string name, std::string tname, mfieldid_t fid, unsigned long size) : mName(name), mType(tname), mFieldID(fid), mSize(size)
{
}

const std::string &Field::GetFieldName()
{
    return mName;
}

const std::string &Field::GetFieldTypeName()
{
    return mType;
}

const mfieldid_t &Field::GetFieldID()
{
    return mFieldID;
}

const unsigned long &Field::GetFieldSize()
{
    return mSize;
}
