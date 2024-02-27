/**
 * @file test_opcua_server.cpp
 * @author zhaoxi (535394140@qq.com)
 * @brief OPC UA 服务器单元测试
 * @version 1.0
 * @date 2023-11-09
 *
 * @copyright Copyright 2023 (c), zhaoxi
 *
 */

#include <gtest/gtest.h>

#include "rmvl/opcua/server.hpp"

#include "testnum.h"

namespace rm_test
{

// 变量（类型）配置
TEST(OPC_UA_Server, value_config)
{
    // 变量类型节点、字符串
    rm::VariableType variable_type = "string_test";
    EXPECT_EQ(variable_type.size(), 1);
    EXPECT_EQ(variable_type.getDataType(), UA_TYPES_STRING);
    // 添加变量节点、双精度浮点数
    rm::Variable variable = 3.1415;
    EXPECT_EQ(variable.size(), 1);
    EXPECT_EQ(variable.getDataType(), UA_TYPES_DOUBLE);
    // 添加变量节点、数组
    rm::Variable variable_array = std::vector<int>{1, 2, 3};
    EXPECT_EQ(variable_array.size(), 3);
    EXPECT_EQ(variable_array.getDataType(), UA_TYPES_INT32);
}

// 服务器添加变量节点
TEST(OPC_UA_Server, add_node)
{
    rm::Server svr(4840);
    rm::Variable variable = 3.1415;
    variable.browse_name = "test_double";
    variable.description = "this is test double";
    variable.display_name = "测试双精度浮点数";
    auto node = svr.addVariableNode(variable);
    EXPECT_FALSE(UA_NodeId_isNull(&node));
    svr.start();
    svr.stop();
    svr.join();
}

// 服务器添加变量类型节点
TEST(OPC_UA_Server, add_type_node)
{
    rm::Server svr(4842);
    rm::VariableType variable_type = "string_test";
    variable_type.browse_name = "test_string";
    variable_type.description = "this is test string";
    variable_type.display_name = "测试字符串";
    auto node = svr.addVariableTypeNode(variable_type);
    EXPECT_FALSE(UA_NodeId_isNull(&node));
    svr.start();
    svr.stop();
    svr.join();
}

// 服务器添加方法节点
TEST(OPC_UA_Server, call_method)
{
    rm::Server svr(4845);
    rm::Method method;
    method.browse_name = "test_method";
    method.description = "this is test method";
    method.display_name = "测试方法";
    method.func = [](UA_Server *, const UA_NodeId *, void *, const UA_NodeId *, void *, const UA_NodeId *,
                     void *, size_t, const UA_Variant *, size_t, UA_Variant *) -> UA_StatusCode {
        return UA_STATUSCODE_GOOD;
    };
    svr.addMethodNode(method);
    svr.start();
    svr.stop();
    svr.join();
}

// 服务器添加对象节点
TEST(OPC_UA_Server, add_object_node)
{
    rm::Server svr(4846);
    rm::Object object;
    object.browse_name = "test_object";
    object.description = "this is test object";
    object.display_name = "测试对象";
    rm::Variable val1 = 3.14;
    val1.browse_name = "test_val1";
    val1.description = "this is test val1";
    val1.display_name = "测试变量 1";
    object.add(val1);
    auto id = svr.addObjectNode(object);
    EXPECT_FALSE(UA_NodeId_isNull(&id));
    svr.start();
    svr.stop();
    svr.join();
}

// 服务器添加对象类型节点
TEST(OPC_UA_Server, add_object_type_node)
{
    rm::Server svr(4847);
    rm::ObjectType object_type;
    object_type.browse_name = "test_object_type";
    object_type.description = "this is test object type";
    object_type.display_name = "测试对象类型";
    rm::Variable val1 = 3.14;
    val1.browse_name = "test_val1";
    val1.description = "this is test val1";
    val1.display_name = "测试变量 1";
    object_type.add(val1);
    auto id = svr.addObjectTypeNode(object_type);
    EXPECT_FALSE(UA_NodeId_isNull(&id));
    svr.start();
    svr.stop();
    svr.join();
}

// 从对象类型节点派生对象节点，并添加到服务器
TEST(OPC_UA_Server, create_object_by_object_type)
{
    rm::Server svr(4848);
    rm::ObjectType object_type;
    object_type.browse_name = "test_object_type";
    object_type.description = "this is test object type";
    object_type.display_name = "测试对象类型";
    rm::Variable val1 = 3.14;
    val1.browse_name = "test_val1";
    val1.description = "this is test val1";
    val1.display_name = "测试变量 1";
    object_type.add(val1);
    svr.addObjectTypeNode(object_type);
    rm::Object object(object_type);
    object.browse_name = "test_object";
    object.description = "this is test object";
    object.display_name = "测试对象";
    auto id = svr.addObjectNode(object);
    EXPECT_FALSE(UA_NodeId_isNull(&id));
    svr.start();
    svr.stop();
    svr.join();
}

// 服务器节点服务端路径搜索
TEST(OPC_UA_Server, find_node)
{
    rm::Server svr(4850);
    rm::Object object;
    object.browse_name = "test_object";
    object.description = "this is test object";
    object.display_name = "测试对象";
    rm::Variable val1 = 3.14;
    val1.browse_name = "test_val1";
    val1.description = "this is test val1";
    val1.display_name = "测试变量 1";
    object.add(val1);
    auto id = svr.addObjectNode(object);
    auto target = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER) | svr.find("test_object");
    EXPECT_TRUE(UA_NodeId_equal(&id, &target));
    svr.start();
    svr.stop();
    svr.join();
}

// 添加自定义事件类型节点
TEST(OPC_UA_Server, add_event_type_node)
{
    rm::Server svr(4855);
    rm::EventType event_type;
    event_type.browse_name = "test_event_type";
    event_type.description = "this is test event type";
    event_type.display_name = "测试事件类型";
    int val = 3;
    event_type.add("test_val", val);
    auto id = svr.addEventTypeNode(event_type);
    auto target = rm::nodeBaseEventType | svr.find("test_event_type");
    EXPECT_TRUE(UA_NodeId_equal(&id, &target));
    svr.start();
    svr.stop();
    svr.join();
}

// 手动触发事件
TEST(OPC_UA_Server, trigger_event)
{
    rm::Server svr(4860);
    // 添加事件类型
    rm::EventType event_type;
    event_type.browse_name = "test_event_type";
    event_type.description = "this is test event type";
    event_type.display_name = "测试事件类型";
    int val = 3;
    event_type.add("test_val", val);
    svr.addEventTypeNode(event_type);
    // 创建事件
    rm::Event event(event_type);
    event.source_name = "test_event";
    event.message = "this is test event";
    event.severity = 1;
    event["test_val1"] = 99;
    // 触发事件
    EXPECT_TRUE(svr.triggerEvent(UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER), event));
    svr.start();
    svr.stop();
    svr.join();
}

// 从函数指针配置服务器
TEST(OPC_UA_Server, function_ptr)
{
    rm::Server svr(testnum, 4865);
    svr.start();
    auto id = rm::nodeObjectsFolder | svr.find("TestNumber");
    EXPECT_FALSE(UA_NodeId_isNull(&id));
    svr.stop();
    svr.join();
}

// 视图节点
TEST(OPC_UA_Server, view_node)
{
    rm::Server svr(4870);
    uaCreateVariable(demo1, 3.14);
    auto node1 = svr.addVariableNode(demo1);
    uaCreateVariable(demo2, 1);
    svr.addVariableNode(demo2);
    uaCreateVariable(demo3, "abc");
    auto node3 = svr.addVariableNode(demo3);
    svr.start();

    rm::View view;
    view.add(node1, node3);
    view.browse_name = "test_view";
    view.description = "this is test view";
    view.display_name = "测试视图";
    auto view_id = svr.addViewNode(view);
    auto target_view_id = rm::nodeViewsFolder | svr.find("test_view");
    EXPECT_TRUE(UA_NodeId_equal(&view_id, &target_view_id));

    svr.stop();
    svr.join();
}

} // namespace rm_test
