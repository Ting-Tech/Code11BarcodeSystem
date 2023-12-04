#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct EncodeElement
{
    char *characture;
    int value[5];
};

void toBinary(int array[], int len)
{
    int max = 0, min = 0, mid = 0;
    if (array[0] > array[1])
    {
        max = array[0];
        min = array[1];
    }
    else
    {
        max = array[1];
        min = array[0];
    }
    for (size_t i = 2; i < len; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
        else if (array[i] < min)
        {
            min = array[i];
        }
    }
    mid = (max + min) / 2;

    for (size_t i = 0; i < len; i++)
    {
        if (array[i] < mid)
            array[i] = 0;
        else if (array[i] > mid)
            array[i] = 1;
    }
}

char *searchTable(int start, int array[])
{
    const struct EncodeElement table[] = {
        {"1", {1, 0, 0, 0, 1}},
        {"2", {0, 1, 0, 0, 1}},
        {"3", {1, 1, 0, 0, 0}},
        {"4", {0, 0, 1, 0, 1}},
        {"5", {1, 0, 1, 0, 0}},
        {"6", {0, 1, 1, 0, 0}},
        {"7", {0, 0, 0, 1, 1}},
        {"8", {1, 0, 0, 1, 0}},
        {"9", {11, 0, 0, 0, 0}},
        {"0", {0, 0, 0, 0, 11}},
        {"-", {0, 0, 11, 0, 0}},
        {"Start", {0, 0, 1, 1, 0}},
        {"Stop", {0, 0, 1, 1, 0}}};

    for (size_t i = 0; i < 13; i++)
    {
        bool same = true;
        for (size_t j = 0; j < 5; j++)
        {
            if (table[i].value[j] != array[j])
            {
                same = false;
                break;
            }
        }
        if (same)
        {
            return table[i].characture;
        }
    }

    return NULL;
}

bool fixCodeDirection(int array[], int size)
{
    char *firstEle = searchTable(0, array);
    if (firstEle == NULL)
    {
        return false;
    }
    if (firstEle != "Start")
    {
        int start = 0;
        int end = size - 1;
        while (start < end)
        {
            // Swap elements at start and end indices
            int temp = array[start];
            array[start] = array[end];
            array[end] = temp;

            // Move indices towards the center of the array
            start++;
            end--;
        }
    }
    return true;
}

char *decoding(int array[], int len)
{
    char *result;
    for (size_t x = 0; x < len / 5; x++)
    {
        for (size_t y = 0; y < 5; y++)
        {
            char *element = searchTable(5 * x + y, array);
            if (element != NULL)
            {
                // 重新分配内存，确保足够容纳新的字符串
                result = (char *)realloc(result, strlen(result) +
                                                     strlen(element) + 1);
                strcat(result, element);
            }
        }
    }
    return result;
}

int main()
{
    int *code;
    int codeLen = 0;

    scanf("%d", &codeLen);
    code = (int *)malloc(codeLen * sizeof(int));

    for (size_t i = 0; i < codeLen; i++)
    {
        scanf("%d", &code[i]);
    }

    toBinary(code, codeLen);

    if (fixCodeDirection(code, codeLen))
    {
        char *decodingResult = decoding(code, codeLen);
        printf("%s\n", decodingResult);
    }
}