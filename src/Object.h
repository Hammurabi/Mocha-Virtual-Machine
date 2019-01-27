//
// Created by Riverssen on 2019-01-27.
// Copyright (c) 2019 Riverssen GmbH. All rights reserved.
//

#ifndef MOCHAXX_OBJECT_H
#define MOCHAXX_OBJECT_H

#include <string>

typedef unsigned short  mfieldID;
typedef mfieldID        mfieldid_t;

class Field
{
private:
    const std::string   mName;
    const std::string   mType;
    const mfieldid_t    mFieldID;
    const unsigned long mSize;
protected:
public:
    Field(std::string name, std::string tname, mfieldid_t fid, unsigned long size);
    const std::string& GetFieldName();
    const std::string& GetFieldTypeName();
    const mfieldid_t & GetFieldID();
    const unsigned long & GetFieldSize();
};

class Struct
{
private:
protected:
    std::string         mTypeName;
    Struct*             mParent;
    const Field*        mFields;
    unsigned long       mSize;
    unsigned long       mRealSize;
public:
    inline const Field& GetField(const mfieldid_t);
    inline const mfieldid_t& GetSize();
    inline const std::string& GetTypeName();
};

class Object
{
private:
protected:
    Struct*             mType;
    void*               mFields;
    inline mfieldid_t   GetField(const mfieldid_t);
public:
                        Object(Struct* type);
    inline char         GetByteField(const mfieldid_t);
    inline short        GetShortField(const mfieldid_t);
    inline int          GetIntField(const mfieldid_t);
    inline long         GetLongField(const mfieldid_t);
    inline float        GetFloatField(const mfieldid_t);
    inline double       GetDoubleField(const mfieldid_t);
    inline Object*      GetObjectField(const mfieldid_t);

    inline void         SetByteField(const mfieldid_t, const char);
    inline void         SetShortField(const mfieldid_t, const short);
    inline void         SetIntField(const mfieldid_t, const int);
    inline void         SetLongField(const mfieldid_t, const long);
    inline void         SetFloatField(const mfieldid_t, const float);
    inline void         SetDoubleField(const mfieldid_t, const double);
    inline void         SetObjectField(const mfieldid_t, const Object*);
};


#endif //MOCHAXX_OBJECT_H
