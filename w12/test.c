#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TEST_CASES 1
#define ARRAY_SIZE 100
#define MAX_BUFFER 65536 // 适当调整缓冲区大小

// 执行命令并获取输出 (Windows 兼容)
char* execute_command(char* command) {
    char buffer[MAX_BUFFER];
    char* result = (char*)malloc(MAX_BUFFER * sizeof(char));
    result[0] = '\0';
    FILE* pipe = _popen(command, "r"); // 使用 _popen 在 Windows 上
    if (!pipe) {
        perror("_popen failed");
        exit(EXIT_FAILURE);
    }
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strcat(result, buffer);
    }
    _pclose(pipe); // 使用 _pclose 在 Windows 上
    return result;
}

// 比较两个整数数组是否相等
bool arrays_equal(int* arr1, int* arr2, int n) {
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

// 从字符串中解析整数数组
void parse_int_array(char* str, int* arr, int n) {
    char* token = strtok(str, " ");
    for (int i = 0; i < n && token != NULL; i++) {
        arr[i] = atoi(token);
        token = strtok(NULL, " ");
    }
}

int main() {
    int correct_count = 0;
    for (int i = 0; i < TEST_CASES; i++) {
        printf("--- Test Case %d ---\n", i + 1);

        // 1. 生成测试数据
        char* o_output = execute_command("./o.exe"); // 显式指定 .exe

        // 解析 o.c 的输出
        int in_arr[ARRAY_SIZE];
        int out_arr[ARRAY_SIZE];
        int expected_sorted_arr[ARRAY_SIZE];
        int m;

        char* line = strtok(o_output, "\n"); // 获取第一行 (n=100)
        line = strtok(NULL, "\n");      // 获取第二行 (in_arr)
        parse_int_array(line, in_arr, ARRAY_SIZE);
        line = strtok(NULL, "\n");      // 获取第三行 (out_arr)
        parse_int_array(line, out_arr, ARRAY_SIZE);
        line = strtok(NULL, "\n");      // 获取第四行 (m)
        m = atoi(line);
        line = strtok(NULL, "\n");      // 获取第五行 (expected_sorted_arr)
        parse_int_array(line, expected_sorted_arr, ARRAY_SIZE);

        free(o_output); // 释放 o.c 输出的内存

        // 2. 运行 InserOrHeap.c
        char input_str[MAX_BUFFER];
        sprintf(input_str, "%d\n", ARRAY_SIZE);
        for (int j = 0; j < ARRAY_SIZE; j++) {
            sprintf(input_str + strlen(input_str), "%d ", in_arr[j]);
        }
        sprintf(input_str + strlen(input_str), "\n");
        for (int j = 0; j < ARRAY_SIZE; j++) {
            sprintf(input_str + strlen(input_str), "%d ", out_arr[j]);
        }
        sprintf(input_str + strlen(input_str), "\n");

        FILE* inser_or_heap_in = _popen("./inser_or_heap.exe", "w"); // 显式指定 .exe
        if (!inser_or_heap_in) {
            perror("_popen for inser_or_heap input failed");
            exit(EXIT_FAILURE);
        }
        fprintf(inser_or_heap_in, "%s", input_str);
        _pclose(inser_or_heap_in); // 显式指定 .exe

        char* inser_or_heap_out = execute_command("./inser_or_heap.exe"); // 显式指定 .exe

        // 3. 验证判断结果
        bool correct_type = strstr(inser_or_heap_out, "Insertion Sort") != NULL;
        printf("InserOrHeap Output:\n%s\n", inser_or_heap_out);

        if (!correct_type) {
            printf("  Error: Incorrect sort type detected (Expected Insertion Sort).\n");
            printf("  Input:\n%s\n", input_str);
            free(inser_or_heap_out);
            continue; // 跳过后续检查
        } else {
            printf("  Correct sort type detected: Insertion Sort\n");
        }

        // 4. 验证排序结果
        char* sorted_output_str = strstr(inser_or_heap_out, "Sort\n") + strlen("Sort\n"); // 获取排序后的数组字符串
        int inser_or_heap_result[ARRAY_SIZE];
        parse_int_array(sorted_output_str, inser_or_heap_result, ARRAY_SIZE);

        bool correct_sort = arrays_equal(inser_or_heap_result, expected_sorted_arr, ARRAY_SIZE);

        if (correct_sort) {
            printf("  Correct sort result.\n");
            correct_count++;
        } else {
            printf("  Error: Incorrect sort result.\n");
            printf("  Expected:\n");
            for (int j = 0; j < ARRAY_SIZE; j++) {
                printf("%d ", expected_sorted_arr[j]);
            }
            printf("\n  Actual:\n");
            for (int j = 0; j < ARRAY_SIZE; j++) {
                printf("%d ", inser_or_heap_result[j]);
            }
            printf("\n");

            // 使用 judge.c 验证差异
            FILE* judge_in = _popen("./judge.exe", "w"); // 显式指定 .exe
            if (!judge_in) {
                perror("_popen for judge input failed");
                exit(EXIT_FAILURE);
            }
            fprintf(judge_in, "%d\n", ARRAY_SIZE);
            for (int j = 0; j < ARRAY_SIZE; j++) {
                fprintf(judge_in, "%d ", expected_sorted_arr[j]);
            }
            fprintf(judge_in, "\n");
            for (int j = 0; j < ARRAY_SIZE; j++) {
                fprintf(judge_in, "%d ", inser_or_heap_result[j]);
            }
            fprintf(judge_in, "\n");
            _pclose(judge_in); // 显式指定 .exe

            char* judge_out = execute_command("./judge.exe"); // 显式指定 .exe
            printf("  Judge Output: %s\n", judge_out);
            free(judge_out);
        }

        free(inser_or_heap_out);
    }

    // 5. 输出测试总结
    printf("\n--- Test Summary ---\n");
    printf("Correct InserSort Count: %d / %d\n", correct_count, TEST_CASES);

    return 0;
}