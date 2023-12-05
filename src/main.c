#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct EncodeElement
{
    char *characture;
    int value[5];
};

bool toBinary(int array[], int len)
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
        {
            if (array[i] > min * 1.1 || array[i] < min)
            {
                return false;
            }
            else
            {
                array[i] = 0;
            }
        }
        else if (array[i] > mid)
        {
            if (array[i] < max * 0.9 || array[i] > max)
            {
                return false;
            }
            else
            {
                array[i] = 1;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
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
        {"9", {1, 0, 0, 0, 0}},
        {"0", {0, 0, 0, 0, 1}},
        {"-", {0, 0, 1, 0, 0}},
        {"Start/Stop", {0, 0, 1, 1, 0}}};

    for (size_t i = 0; i < 12; i++)
    {
        bool same = true;
        for (size_t j = 0; j < 5; j++)
        {
            if (table[i].value[j] != array[start + j])
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

void fixCodeDirection(int array[], int size)
{
    char *firstEle = searchTable(0, array);

    if (firstEle != "Start/Stop")
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
}

char **decoding(int array[], int len)
{
    char **result = (char **)malloc((len + 1) / 6 * sizeof(char *));
    for (int x = 0; x < (len + 1) / 6; x++)
    {
        char *element = searchTable(5 * x + x, array);

        if (element != NULL)
        {
            result[x] = element;
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

    if (!toBinary(code, codeLen))
    {
        printf("Bad code");
        return -1;
    }

    for (size_t i = 0; i < codeLen; i++)
    {
        printf("%d ", code[i]);
    }

    printf("\n");

    fixCodeDirection(code, codeLen);

    for (size_t i = 0; i < codeLen; i++)
    {
        printf("%d ", code[i]);
    }

    printf("\n");

    char **decodingResult = decoding(code, codeLen);
    for (size_t i = 0; i < (codeLen + 1) / 6; i++)
    {
        printf("Result:%s\n", decodingResult[i]);
    }
}