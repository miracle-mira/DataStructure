#include <stdio.h>
#include <stdlib.h> //malloc 함수가 포함된 헤더 파일


void PrintMatrix(int **matrix);                        //행렬 출력 함수
void AddMatrix(int  **matrixA , int **matrixB);        //행렬 덧셈 함수: 결과값을 PrintMatrix() 함수 호출로 출력
void Subtract(int  **matrixA , int **matrixB);         //행렬 뺄셈 함수: 결과값을 PrintMatrix() 함수 호출로 출력
void Transpose(int  **matrixA );                       //행렬 전치 함수: 결과값을 PrintMatrix() 함수 호출로 출력
void MultiplyMatrix(int  **matrixA , int **matrixB);   //행렬 곱셈 함수: 결과값을 PrintMatrix() 함수 호출로 출력
void free_matrix(int **matrix);                               //동적 메모리 할당 해제 함수

int rowA,colA;  //행렬 A의 행(row)과 열(col)의 수를 전역변수로 설정: 모든 함수가 행과 열의 개수를 알아야 하므로 매개변수를 사용하기보단 전역변수로 사용하는 것이 효율적임.
int rowB,colB;  //행령 B의 행(row)과 열(col)의 수를 전역변수로 설정: 모든 함수가 행과 열의 개수를 알아야 하므로 매개변수를 사용하기보단 전역변수로 사용하는 것이 효율적임.

int main(void){
    printf("\n\n[----- [박미라] [2020069006] -----]\n\n");


    int **matrixA;  //행렬 A를 동적 메모리로 할당 받기 위해 이중포인터 변수 선언: matrixA = 행의 첫 주소 , 각 행 = 열의 첫 주소
    int **matrixB;  //행렬 B를 동적 메모리로 할당 받기 위해 이중포인터 변수 선언
    int i,z; //반복문 변수로 사용

    /*
    행과 열 입력받기
    1) 행렬A와 행렬B의 행과 열의 수를 입력받는다.
    2) 이때, 행렬A와 행렬B의 행과 열의 수가 같지 않으면 덧셈,뺄셈,곱셈을 연산할 수 없으므로 같을 때까지 사용자에게 입력받는다.
    */
    do{
        printf("행렬A의 행의 개수를 입력하시오: ");
        scanf("%d",&rowA);
        printf("행렬A의 열의 개수를 입력하시오: ");
        scanf("%d",&colA);

        printf("행렬B의 행의 개수를 입력하시오: ");
        scanf("%d",&rowB);
        printf("행렬B의 행의 개수를 입력하시오: ");
        scanf("%d",&colB);
    }while((rowA != rowB) || (colA != colB));

    //행렬A의 행을 동적 메모리로 할당
    //주소를 담는 공간을 선언하는 것이므로 int *의 크기 단위로 동적 메모리를 할당 해야한다.
    printf("\n\n");
    matrixA = (int **)malloc(sizeof(int *) * rowA); 

    //행렬A의 각 행에 열을 동적메모리로 할당 받아 저장: 이때 열에는 데이터 값을 저장할 것이기 때문에 int형으로 크기 조절함.
    for(i=0;i<rowA;i++){
        *(matrixA+i) = (int *)malloc(sizeof(int) * colA);
    }

    //행렬B의 행을 동적 메모리로 할당
    matrixB = (int **)malloc(sizeof(int *) * rowB); 

    //행렬B의 각 행에 열을 동적메모리로 할당 받아 저장: 이때 열에는 데이터 값을 저장할 것이기 때문에 int형으로 크기 조절함.
    for(i=0;i<rowB;i++){
        *(matrixB+i) = (int *)malloc(sizeof(int) * colB);
    }

    //행렬A 값 채우기
    printf("\n[A행렬 값 넣기]\n");
    for(i=0;i<rowA;i++){
        for(z=0;z<colA;z++){
            printf("%d행 %d열: ",i,z);
            scanf("%d", (*(matrixA+i))+z); //i행z열의 값 넣기
        }
    }

    //행렬B 값 채우기
    printf("\n[B행렬 값 넣기]\n");
    for(i=0;i<rowB;i++){
        for(z=0;z<colB;z++){
            printf("%d행 %d열: ",i,z);
            scanf("%d",(*(matrixB+i))+z); //i행z열의 값 넣기
        }
    }

    printf("\n---------------------연산 결과---------------------\n");

    //행렬A 값 출력
    printf("\n[행렬A]");
    PrintMatrix(matrixA);

    //행렬B 값 출력
    printf("\n[행렬B]");
    PrintMatrix(matrixB);
    
    //행렬A,행렬B 덧셈
    printf("\n[행렬 덧셈 결과]");
    AddMatrix(matrixA,matrixB);

    //행렬A,행렬B 덧셈
    printf("\n[행렬 뺄셈 결과]");
    Subtract(matrixA,matrixB);
    
    //행렬A 전치
    printf("\n[행렬A 전치 결과]");
    Transpose(matrixA);

    //행렬A,행렬B 곱셈
    printf("\n[행렬 곱셈 결과]");
    MultiplyMatrix(matrixA,matrixB);

     //동적 메모리 할당 해제 함수 호출
    free_matrix(matrixA);
    free_matrix(matrixB);

    return 0;
}

//행렬 출력 함수
void PrintMatrix(int **matrix)
{
    int i,z; //반복문 변수
    //행렬 값 출력
    for(i=0;i<rowA;i++){
        printf("\n");
        for(z=0;z<colA;z++){
            printf("%d\t",*((*(matrix+i))+z));
        }
    }

    printf("\n");
    
}


//행렬 덧셈 함수
void AddMatrix(int  **matrixA , int **matrixB)
{
    int i,z; //반복문 변수

    //덧셈을 저장할 행렬의 행을 동적 메모리로 할당: 행렬 A와 B의 열과 행의 수는 같기 때문에 rowA,colA를 사용함.
    int **matrix = (int **)malloc(sizeof(int *) * rowA); 

    //행렬의 각 행에 열을 동적메모리로 할당 받아 저장: 이때 열에는 데이터 값을 저장할 것이기 때문에 int형으로 크기 조절함.
    for(i=0;i<rowA;i++){
        *(matrix+i) = (int *)malloc(sizeof(int) * colA);

    }

    //덧셈후 저장
    for(i=0;i<rowA;i++){
        for(z=0;z<colA;z++){
            *((*(matrix+i))+z) = *((*(matrixA+i))+z) + *((*(matrixB+i))+z); 
        }
    }

    PrintMatrix(matrix);  //결과 출력 함수 호출

     //동적 메모리 할당 해제 함수 호출
    free_matrix(matrix);
}



 //행렬 뺄셈 함수
void Subtract(int  **matrixA , int **matrixB)
{
    int i,z; //반복문 변수

    //뺄셈을 저장할 행렬의 행을 동적 메모리로 할당: 행렬 A와 B의 열과 행의 수는 같기 때문에 rowA,colA를 사용함.
    int **matrix = (int **)malloc(sizeof(int *) * rowA); 

    //행렬의 각 행에 열을 동적메모리로 할당 받아 저장: 이때 열에는 데이터 값을 저장할 것이기 때문에 int형으로 크기 조절함.
    for(i=0;i<rowA;i++){
        *(matrix+i) = (int *)malloc(sizeof(int) * colA);

    }

    //덧셈후 저장
    for(i=0;i<rowA;i++){
        for(z=0;z<colA;z++){
            *((*(matrix+i))+z) = *((*(matrixA+i))+z) - *((*(matrixB+i))+z); 
        }
    }

    PrintMatrix(matrix);  //결과 출력 함수 호출
     //동적 메모리 할당 해제 함수 호출
    free_matrix(matrix);
}     

//행렬 전치 함수
void Transpose(int  **matrixA )
{
    int i,z; //반복문 변수

    //전치한 행렬A를 저장할 행렬의 행을 동적 메모리로 할당: 행렬 A와 B의 열과 행의 수는 같기 때문에 rowA,colA를 사용함.
    int **matrix = (int **)malloc(sizeof(int *) * rowA); 

    //행렬의 각 행에 열을 동적메모리로 할당 받아 저장: 이때 열에는 데이터 값을 저장할 것이기 때문에 int형으로 크기 조절함.
    for(i=0;i<rowA;i++){
        *(matrix+i) = (int *)malloc(sizeof(int) * colA);
    }

    //전치 후 저장
    for(i=0;i<rowA;i++){
        for(z=0;z<colA;z++){
            *((*(matrix+i))+z) = *((*(matrixA+z))+i); 
        }
    }

    PrintMatrix(matrix);  //결과 출력 함수 호출
     //동적 메모리 할당 해제 함수 호출
    free_matrix(matrix);

}


//행렬 곱셈 함수
void MultiplyMatrix(int  **matrixA , int **matrixB)
{
    int i,z,x; //반복문 변수

    //곱셈한 행렬의 행을 동적 메모리로 할당: 행렬 A와 B의 열과 행의 수는 같기 때문에 rowA,colA를 사용함.
    int **matrix = (int **)malloc(sizeof(int *) * rowA); 

    //행렬의 각 행에 열을 동적메모리로 할당 받아 저장: 이때 열에는 데이터 값을 저장할 것이기 때문에 int형으로 크기 조절함.
    for(i=0;i<rowA;i++){
        *(matrix+i) = (int *)malloc(sizeof(int) * colA);
    }

    //곱셈 후 저장
    int result = 0;
    
    for(i=0;i<rowA;i++){
        for(z=0;z<colA;z++){
            for(x=0;x<colA;x++){
                result += *((*(matrixA+i))+x) * *((*(matrixB+x))+z);
            }
            *((*(matrix+i))+z) = result;
            result = 0;
        }
    }

    PrintMatrix(matrix);  //결과 출력 함수 호출

    //동적 메모리 할당 해제 함수 호출
    free_matrix(matrix);
}


//동적 메모리 할당 해제 함수
void free_matrix(int **matrix)
{   
    int i;
    free(matrix);
    for(i=0;i<rowA;i++){
        free(*(matrix+i));
    }
}
