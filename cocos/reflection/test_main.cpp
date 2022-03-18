//
//  main.cpp
//  CocosReflection
//
//  Created by James Chen on 3/15/22.
//
#include "test_main.h"
#include <stdio.h>

#include "AzCore/RTTI/BehaviorContext.h"

#define EXPECT_EQ(a, b) do { if ((a) != (b)) assert(false); } while(0);

struct MyClass1 {
    AZ_RTTI(MyClass1, "{BEA0AEE2-9D09-4C02-B3F2-28CE74573EE9}")
    AZ_CLASS_ALLOCATOR(MyClass1, AZ::SystemAllocator, 0)

    MyClass1() {

    }

    virtual ~MyClass1() {

    }

    void foo1(int a, bool b) {
        m_a = a;
        m_b = b;
    }

    virtual void virtualMethod(const AZStd::string& str) {
        m_c = str;
    }

    int m_a{0};
    bool m_b{false};
    AZStd::string m_c;
};

template <typename T>
class MyVector {
public:
    void push(T a) {
        _data.push_back(a);
    }

    std::vector<T> _data;
};

namespace AZ {
AZ_TYPE_INFO_TEMPLATE(MyVector, "{8E3A22F8-2D9C-4B33-894D-381F94D6BB41}", AZ_TYPE_INFO_INTERNAL_TYPENAME);
}

struct MySubClass : public MyClass1 {
    AZ_RTTI(MySubClass, "{26D8063E-0B16-4194-AF5F-298970239C3A}", MyClass1)
    AZ_CLASS_ALLOCATOR(MySubClass, AZ::SystemAllocator, 0)

    MySubClass() {

    }

    ~MySubClass() override {

    }

    void virtualMethod(const AZStd::string& str) override {
        m_c = str + "+sub";
    }

    void setMyVector(const MyVector<std::string>& a) {
        EXPECT_EQ(a._data[0], "hello");
        EXPECT_EQ(a._data[1], "world");
    }

    AZStd::string getResult() {
        return "i'm result";
    }

    AZStd::vector<int> getIntArr() {
        return {1, 2, 3, 4, 5};
    }

    AZStd::array<std::string, 3> getStrArr() {
        return {"a", "b", "c"};
    }
};

struct alignas(16) MyStruct {
    AZ_TYPE_INFO(MyStruct, "{A20D5D03-AF59-450F-AA9B-3E99552BE838}")

    int a;
    char b[100];
    alignas(2) bool c;

    AZStd::vector<AZStd::string> arr;

    void setAAA(int a) {
        this->a = a;
    }
    int getAAA() const {
        return this->a;
    }
};

struct alignas(16) MyStruct2 {
    AZ_TYPE_INFO(MyStruct, "{A20D5D03-AF59-450F-AA9B-3E99552BE838}")

    int a;
    char b;
    alignas(2) bool c;
    char buffer;
};


int main_entry() {
    printf("sizeof struct: %d\n", (int)sizeof(MyStruct));
    printf("offsetof a: %d\n", (int)offsetof(MyStruct, a));
    printf("offsetof b: %d\n", (int)offsetof(MyStruct, b));
    printf("offsetof c: %d\n", (int)offsetof(MyStruct, c));

    printf("is_pod MyStruct: %d\n", (int) AZStd::is_pod_v<MyStruct>);
    printf("is_pod MyStruct2: %d\n", (int) AZStd::is_pod_v<MyStruct2>);

    AZ::BehaviorContext m_behaviorContext;

    m_behaviorContext.Class<MyStruct>("MyStruct")
        ->Attribute(AZ_CRC_CE("class attr test"), 100.123f)
        ->Constructor<>()
        ->Property("a", &MyStruct::a)
        ->Property("b", &MyStruct::b)
            ->Attribute(AZ::Script::Attributes::ToolTip, "bb attribute")
        ->Property("c", &MyStruct::c)
            ->Attribute(AZ_CRC_CE("hello c"), 123)
        ->Property("arr", &MyStruct::arr)
        ->Property("aaa", &MyStruct::getAAA, &MyStruct::setAAA)
    ;

    {
        AZ::BehaviorClass* behaviorClass = m_behaviorContext.m_classes["MyStruct"];

        AZ::BehaviorObject instance = behaviorClass->Create();
        MyStruct* pClass = reinterpret_cast<MyStruct*>(instance.m_address);

        {
            auto& clsAttrs = behaviorClass->m_attributes;
            EXPECT_EQ(clsAttrs[0].first, AZ_CRC_CE("class attr test"));

            AZ::AttributeData<float>* attrData = azrtti_cast<AZ::AttributeData<float>*>(clsAttrs[0].second);
            EXPECT_EQ(fabs(attrData->Get(nullptr) - 100.123f) < FLT_EPSILON, true);
        }

        {
            auto iter = behaviorClass->m_properties.find("b");
            assert(iter != behaviorClass->m_properties.end());
            iter->second->SetValue(instance, "hello");
            EXPECT_EQ(strcmp(pClass->b, "hello"), 0);

            char b[100];
            iter->second->GetValue(instance, b);
            EXPECT_EQ(strcmp(b, "hello"), 0);

            auto& attrs = iter->second->m_attributes;
            EXPECT_EQ(attrs[0].first, AZ::Script::Attributes::ToolTip);
            AZ::AttributeData<const char*>* attrData = azrtti_cast<AZ::AttributeData<const char*>*>(attrs[0].second);
            EXPECT_EQ(strcmp(attrData->Get(nullptr), "bb attribute"), 0);
        }

        {
            auto iter = behaviorClass->m_properties.find("aaa");
            assert(iter != behaviorClass->m_properties.end());
//            iter->second->m_setter->Invoke(instance, 144);
            iter->second->SetValue(instance, 144);
            EXPECT_EQ(pClass->a, 144);

            int aaa{};
//            iter->second->m_getter->InvokeResult(aaa, instance);
            iter->second->GetValue(instance, aaa);
            EXPECT_EQ(aaa, 144);
        }

        {
            auto iter = behaviorClass->m_properties.find("c");
            assert(iter != behaviorClass->m_properties.end());
            EXPECT_EQ(iter->second->m_attributes[0].first, AZ_CRC_CE("hello c"));

            AZ::AttributeData<int>* attrData = azrtti_cast<AZ::AttributeData<int>*>(iter->second->m_attributes[0].second);
            EXPECT_EQ(attrData->Get(nullptr), 123);
        }

        {
            auto iter = behaviorClass->m_properties.find("arr");
            assert(iter != behaviorClass->m_properties.end());

            AZStd::vector<AZStd::string> arr{"Hello", "World"};

            iter->second->SetValue(instance, arr);
            EXPECT_EQ(pClass->arr[0], "Hello");
            EXPECT_EQ(pClass->arr[1], "World");

            AZStd::vector<AZStd::string> ret{};
            iter->second->GetValue(instance, ret);
            EXPECT_EQ(ret[0], "Hello");
            EXPECT_EQ(ret[1], "World");
        }

        behaviorClass->Destroy(instance);
    }

    m_behaviorContext.Class<MyClass1>("MyClass1")
        ->Constructor<>()
        ->Method("foo1", &MyClass1::foo1)
        ->Method("virtualMethod", &MyClass1::virtualMethod)
    ;

    m_behaviorContext.Class<MySubClass>("MySubClass")
        ->Constructor<>()
        ->Method("getResult", &MySubClass::getResult)
        ->Method("getIntArr", &MySubClass::getIntArr)
        ->Method("getStrArr", &MySubClass::getStrArr)
        ->Method("setMyVector", &MySubClass::setMyVector)
    ;

    AZ::BehaviorClass* baseClass = m_behaviorContext.m_classes["MyClass1"];
    AZ::BehaviorClass* behaviorClass = m_behaviorContext.m_classes["MySubClass"];
    AZ::BehaviorObject instance = behaviorClass->Create();

    MyClass1* pClass = reinterpret_cast<MyClass1*>(instance.m_address);

    auto iter = baseClass->m_methods.find("foo1");
    assert(iter != baseClass->m_methods.end());

    iter->second->Invoke(instance, 100, true);

    EXPECT_EQ(pClass->m_a, 100);
    EXPECT_EQ(pClass->m_b, true);

    iter = baseClass->m_methods.find("virtualMethod");
    assert(iter != baseClass->m_methods.end());
    iter->second->Invoke(instance, AZStd::string("hello world"));

    EXPECT_EQ(pClass->m_c, "hello world+sub");

    iter = behaviorClass->m_methods.find("getResult");
    assert(iter != behaviorClass->m_methods.end());

    AZStd::string strRet;
    iter->second->InvokeResult(strRet, instance);
    EXPECT_EQ(strRet, "i'm result");

    {
        iter = behaviorClass->m_methods.find("getIntArr");
        assert(iter != behaviorClass->m_methods.end());

        AZStd::vector<int> ret;
        iter->second->InvokeResult(ret, instance);
        AZStd::vector<int> expect{1, 2, 3, 4, 5};
        EXPECT_EQ(ret, expect);
    }

    {
        iter = behaviorClass->m_methods.find("getStrArr");
        assert(iter != behaviorClass->m_methods.end());

        AZStd::array<std::string, 3> ret;
        iter->second->InvokeResult(ret, instance);
        AZStd::array<std::string, 3> expect{"a", "b", "c"};
        EXPECT_EQ(ret, expect);
    }

    {
        iter = behaviorClass->m_methods.find("setMyVector");
        assert(iter != behaviorClass->m_methods.end());

        MyVector<std::string> arg1;
        arg1.push("hello");
        arg1.push("world");
        iter->second->Invoke(instance, arg1);
    }

    behaviorClass->Destroy(instance);

    return 0;
}

