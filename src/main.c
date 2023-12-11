#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct EncodeElement
{
    int characture;
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
    for (int i = 2; i < len; i++)
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

    for (int i = 0; i < len; i++)
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

int searchTable(int start, int array[])
{
    const struct EncodeElement table[] = {
        {1, {1, 0, 0, 0, 1}},
        {2, {0, 1, 0, 0, 1}},
        {3, {1, 1, 0, 0, 0}},
        {4, {0, 0, 1, 0, 1}},
        {5, {1, 0, 1, 0, 0}},
        {6, {0, 1, 1, 0, 0}},
        {7, {0, 0, 0, 1, 1}},
        {8, {1, 0, 0, 1, 0}},
        {9, {1, 0, 0, 0, 0}},
        {0, {0, 0, 0, 0, 1}},
        {10, {0, 0, 1, 0, 0}},  // -
        {11, {0, 0, 1, 1, 0}}}; // Start/Stop

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

    return -1;
}

void fixCodeDirection(int array[], int size)
{
    int firstEle = searchTable(0, array);

    if (firstEle != 11)
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

int decoding(int array[], int len, int resultNoCorrectCode[])
{
    int strCount = ((len + 1) / 6) - 2;
    int resultSize = ((len + 1) / 6) - 4;
    int *result = (int *)malloc(strCount * sizeof(int));
    int *reverse = (int *)malloc(resultSize * sizeof(int));

    for (int x = 0; x < strCount; x++)
    {
        int element = searchTable(5 * (x + 1) + x + 1, array);

        if (element != -1)
        {
            result[x] = element;
        }
    }

    for (int x = 0; x < resultSize; x++)
    {
        int element = searchTable(5 * (x + 1) + x + 1, array);

        if (element != -1)
        {
            resultNoCorrectCode[x] = element;
            reverse[resultSize - x - 1] = element;
        }
    }

    // for (size_t i = 0; i < strCount; i++)
    // {
    //     printf("Result:%d\n", result[i]);
    // }

    // printf("\n");

    // for (size_t i = 0; i < resultSize; i++)
    // {
    //     printf("ResultB:%d\n", resultNoCorrectCode[i]);
    // }

    // printf("\n");

    // for (size_t i = 0; i < resultSize; i++)
    // {
    //     printf("Reverse:%d\n", reverse[i]);
    // }

    // printf("\n");

    int readC = result[resultSize];
    int readK = result[strCount - 1];
    // printf("Read C:%d\n", readC);
    // printf("Read K:%d\n", readK);

    int sumC = 0;
    int countWeightC = 1;
    for (int i = 0; i < resultSize; i++)
    {
        sumC += (reverse[i] * countWeightC);
        if (countWeightC == 10)
        {
            countWeightC = 1;
        }
        else
        {
            countWeightC++;
        }
    }
    int c = sumC % 11;
    // printf("%d\n", c);
    if (c != readC)
    {
        return -1;
    }

    int sumK = c;
    int countWeightK = 2;
    for (int i = 0; i < resultSize; i++)
    {
        sumK += (reverse[i] * countWeightK);
        if (countWeightK == 9)
        {
            countWeightK = 1;
        }
        else
        {
            countWeightK++;
        }
    }
    int k = sumK % 11;
    // printf("%d\n", k);
    if (k != readK)
    {
        return -2;
    }

    return 0;
}


int openfile(FILE *fp)
{
    int x=0;
    fscanf(fp, "%d", &x);
    return x;
}

int verify(int code[],int len)
{
    int start=searchTable(0,code);
    int end=searchTable(len-5,code);
    if(start==11&&end==11)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int space_check(int code[],int len)
{
    int x=1;
    for(int i=5;i<len;i=i+6)
    {
        if(code[i]==1)
        {
            x=0;
            break;
        }
    }
    if(x==1)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}


int main()
{
    int codeLen = -1;
    int **barcodeResult;
    int indexResult[20] = {0};
    int size=0;
    int sizearr[20]={0};
    barcodeResult = (int **)malloc(20 * sizeof(int));   //(((codeLen + 1) / 6) - 4)
    FILE *fp=fopen("test.txt", "r");  //開啟檔案
    if (ferror(fp))
    {
        printf("讀取時發生錯誤");
    }
    for(size = 0; ;size++)
    {
        codeLen = -1;
        int *code;

        codeLen=openfile(fp);      //scanf("%d", &codeLen);
        sizearr[size]=codeLen;
        barcodeResult[size] = (int *)malloc((((codeLen + 1) / 6) - 4) * sizeof(int));
        if(codeLen == 0)
        {
            break;
        }
        code = (int *)malloc(codeLen * sizeof(int));
        int j = 0;
        for (j = 0; j < codeLen; j++)
        {
            code[j]=openfile(fp);      //scanf("%d", &code[j]);
        }
        //printf("\n");
        if (toBinary(code, codeLen)==false)
        {
            indexResult[size]=-3;
            continue;
        }
        // for (size_t i = 0; i < codeLen; i++)
        // {
        //     printf("%d ", code[i]);
        // }

        // printf("\n");

        fixCodeDirection(code, codeLen);

        // for (size_t i = 0; i < codeLen; i++)
        // {
        //     if (i % 6 == 0)
        //     {
        //         printf("\n");
        //     }
        //     printf("%d ", code[i]);
        // }

        // printf("\n");
        if(verify(code, codeLen)==1&&space_check(code, codeLen)==1)
        {
            indexResult[size]=decoding(code, codeLen, barcodeResult[size]);
        }
        else
        {
            indexResult[size]=-3;
        }
    }
    //printf("%d",indexResult[0]);
    for(int i = 0; i < size; i++)
    {
        printf("Case %d:",i);
        if (indexResult[i] == 0)
        {
            for (int a = 0; a < ((( sizearr[i] + 1) / 6) - 4); a++)
            {
                if (barcodeResult[i][a] == 10)
                {
                    printf("-");
                }
                else
                {
                    printf("%d", barcodeResult[i][a]);
                }
            }
        }
        else if (indexResult[i] == -1)
        {
            printf("bad C");
        }
        else if (indexResult[i] == -2)
        {
            printf("bad K");
        }
        else if (indexResult[i] == -3)
        {
            printf("bad code");
        }
        printf("\n");
    }
    return 0;
}