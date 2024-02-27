/**
 * @file ort_print.cpp
 * @author RoboMaster Vision Community
 * @brief
 * @version 1.0
 * @date 2022-02-04
 *
 * @copyright Copyright 2023 (c), RoboMaster Vision Community
 *
 */

#include "ort_impl.h"

using namespace std;
using namespace Ort;

void rm::OnnxRT::Impl::printModelInfo() noexcept
{
    printf("-------------- Input Layer --------------\n");
    int input_node = _p_session->GetInputCount();
    printf("the number of input node is: %d\n", input_node);
    for (int i = 0; i < input_node; i++)
    {
        printf("[%d]\t┬ name is: %s\n", i, _p_session->GetInputName(i, _allocator));
        vector<int64_t> input_dims = _p_session->GetInputTypeInfo(i).GetTensorTypeAndShapeInfo().GetShape();
        printf("\t│ dim is: [\n");
        for (auto dim : input_dims)
            printf("%ld, ", dim);
        printf("\b\b]\n");
        printf("\t└ type of each element is: %d\n", _p_session->GetInputTypeInfo(i).GetTensorTypeAndShapeInfo().GetElementType());
    }

    printf("\n------------- Output  Layer -------------\n");
    int output_node = _p_session->GetOutputCount();
    printf("the number of output node is: %zu\n", _p_session->GetOutputCount());
    for (int i = 0; i < output_node; i++)
    {
        printf("[%d]\t┬ name is: %s\n", i, _p_session->GetOutputName(i, _allocator));
        vector<int64_t> output_dims = _p_session->GetOutputTypeInfo(i).GetTensorTypeAndShapeInfo().GetShape();
        printf("\t│ dim is: [");
        for (auto dim : output_dims)
            printf("%ld, ", dim);
        printf("\b\b]\n");
        printf("\t└ type of each element is: %d\n", _p_session->GetOutputTypeInfo(i).GetTensorTypeAndShapeInfo().GetElementType());
    }
}
