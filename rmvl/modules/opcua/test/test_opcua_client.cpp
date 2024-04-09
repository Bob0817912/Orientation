/**
 * @file test_opcua_client.cpp
 * @author zhaoxi (535394140@qq.com)
 * @brief OPC UA 客户端单元测试
 * @version 1.0
 * @date 2023-11-09
 *
 * @copyright Copyright 2023 (c), zhaoxi
 *
 */

#include <gtest/gtest.h>

#include "rmvl/opcua/client.hpp"
#include "rmvl/opcua/server.hpp"

#include "rmvlpara/opcua.hpp"

namespace rm_test
{

void setSvr(rm::Server &svr)
{
    // 添加单变量节点
    rm::Variable single_value = 42;
    single_value.browse_name = "single";
    single_value.description = "this is single value";
    single_value.display_name = "单值";
    svr.addVariableNode(single_value);
    // 添加数组变量节点
    rm::Variable variable = std::vector({1, 2, 3, 4, 5});
    variable.browse_name = "array";
    variable.description = "this is array";
    variable.display_name = "数组";
    svr.addVariableNode(variable);
    // 添加加法方法节点
    rm::Method method;
    method.browse_name = "add";
    method.description = "this is add method";
    method.display_name = "加法";
    method.iargs = {{"a", UA_TYPES_INT32}, {"b", UA_TYPES_INT32}};
    method.oargs = {{"c", UA_TYPES_INT32}};
    method.func = [](UA_Server *, const UA_NodeId *, void *, const UA_NodeId *, void *, const UA_NodeId *,
                     void *, size_t, const UA_Variant *input, size_t, UA_Variant *output) -> UA_StatusCode {
        int32_t a = *reinterpret_cast<int *>(input[0].data);
        int32_t b = *reinterpret_cast<int *>(input[1].data);
        int32_t c = a + b;
        return UA_Variant_setScalarCopy(output, &c, &UA_TYPES[UA_TYPES_INT32]);
    };
    svr.addMethodNode(method);
    // 添加对象节点，包含字符串变量和乘法方法
    svr.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

// 路径搜索
TEST(OPC_UA_ClientTest, read_variable)
{
    rm::Server svr(5000);
    setSvr(svr);
    rm::Client client("opc.tcp://localhost:5000");
    // 读取测试服务器上的变量值
    auto id = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER) | client.find("array");
    rm::Variable variable = client.read(id);
    EXPECT_FALSE(variable.empty());
    auto vec = rm::Variable::cast<std::vector<int>>(variable);
    for (size_t i = 0; i < vec.size(); ++i)
        EXPECT_EQ(vec[i], i + 1);
    svr.stop();
    svr.join();
}

// 变量读写
TEST(OPC_UA_ClientTest, variable_IO)
{
    rm::Server svr(5001);
    setSvr(svr);
    rm::Client client("opc.tcp://localhost:5001");
    // 读取测试服务器上的变量值
    auto id = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER) | client.find("single");
    EXPECT_TRUE(client.write(id, 99));
    rm::Variable variable = client.read(id);
    EXPECT_FALSE(variable.empty());
    int single_value = rm::Variable::cast<int>(variable);
    EXPECT_EQ(single_value, 99);
    svr.stop();
    svr.join();
}

// 方法调用
TEST(OPC_UA_ClientTest, call)
{
    rm::Server svr(5002);
    setSvr(svr);
    rm::Client client("opc.tcp://localhost:5002");
    // 调用测试服务器上的方法
    std::vector<rm::Variable> input = {1, 2};
    std::vector<rm::Variable> output;
    EXPECT_TRUE(client.call("add", input, output));
    EXPECT_EQ(rm::Variable::cast<int>(output[0]), 3);
    svr.stop();
    svr.join();
}

std::string type_name{};
int receive_data{};

void onChange(UA_Client *, UA_UInt32, void *, UA_UInt32, void *, UA_DataValue *value)
{
    type_name = value->value.type->typeName;
    receive_data = *reinterpret_cast<int *>(value->value.data);
}

// 订阅
TEST(OPC_UA_ClientTest, variable_monitor)
{
    rm::Server svr(5003);
    setSvr(svr);
    rm::Client client("opc.tcp://localhost:5003");
    // 订阅测试服务器上的变量
    auto node_id = rm::nodeObjectsFolder | client.find("single");
    EXPECT_TRUE(client.monitor(node_id, onChange, 5));
    // 数据更新
    client.write(node_id, 66);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    client.spinOnce();
    EXPECT_EQ(type_name, "Int32");
    EXPECT_EQ(receive_data, 66);
    svr.stop();
    svr.join();
}

// 事件响应
std::string source_name;
int aaa{};
void onEvent(UA_Client *, UA_UInt32, void *, UA_UInt32, void *, size_t size, UA_Variant *event_fields)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (UA_Variant_hasScalarType(&event_fields[i], &UA_TYPES[UA_TYPES_STRING]))
        {
            UA_String *tmp = reinterpret_cast<UA_String *>(event_fields[i].data);
            source_name = reinterpret_cast<char *>(tmp->data);
        }
        else if (UA_Variant_hasScalarType(&event_fields[i], &UA_TYPES[UA_TYPES_INT32]))
            aaa = *reinterpret_cast<UA_Int32 *>(event_fields[i].data);
    }
}

TEST(OPC_UA_ClientTest, event_monitor)
{
    rm::Server svr(5004);
    setSvr(svr);
    rm::EventType etype;
    etype.browse_name = "TestEventType";
    etype.display_name = "测试事件类型";
    etype.description = "测试事件类型";
    etype.add("aaa", 3);
    svr.addEventTypeNode(etype);
    rm::Client client("opc.tcp://localhost:5004");
    client.monitor(rm::nodeServer, {"SourceName", "aaa"}, onEvent);
    // 触发事件
    rm::Event event(etype);
    event.source_name = "GtestServer";
    event.message = "this is test event";
    event["aaa"] = 66;
    svr.triggerEvent(rm::nodeServer, event);
    client.spinOnce();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    EXPECT_EQ(source_name, "GtestServer");
    EXPECT_EQ(aaa, 66);
    svr.stop();
    svr.join();
}

} // namespace rm_test
