#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);
int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
int quickSort(int *a, int n);
int hashCode(int key);
int hashing(int *a, int **ht);
int search(int *ht, int key);


int main()
{
	printf("[----- [오인화] [2022078036] -----]\n\n");

	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);
			break;
		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;
		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;
		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');

	return 1;
}

/*배열을 초기화하는 함수*/
int initialize(int** a)
{
	int *temp = NULL;

	/*빈 배열인 경우, 새로운 배열 생성*/
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  
	} 
	else
		temp = *a;

	/*배열에 임의의 숫자를 삽입*/
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

/*배열의 메모리를 해제하는 함수*/
int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

/*배열의 원소를 출력하는 함수*/
void printArray(int *a)
{
	if (a == NULL) {	/*빈 배열일 경우 함수 종료*/
		printf("nothing to print.\n");
		return;
	}
	/*배열의 인덱스와 원소 출력*/
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

/*선택정렬 함수*/
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	//정렬 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		/*i번째 원소를 가장 작은 원소로 변경하기 위해 i번째 원소를 미리 저장*/
		minindex = i;	
		min = a[i];

		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			/*더 작은 원소가 있을 경우, 그 값과 인덱스를 저장*/
			if (min > a[j])		
			{
				min = a[j];		
				minindex = j;
			}
		}
		/*i번째 위치에 가장 작은 원소를 삽입*/
		a[minindex] = a[i];		
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	//정렬 후 배열 출력
	return 0;
}

/*삽입정렬 함수*/
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	/*앞의 원소가 뒤의 원소보다 클 경우 두 원소의 위치 변경을 반복*/
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

/*버블정렬 함수*/
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전 배열 출력

	//오름차순으로 정렬하는 반복문
	//가장 큰 수부터 오른쪽 끝에 정렬되며 배열의 크기만큼 반복하면 모든 수가 오름차순으로 정렬된다
	for(i = 0; i < MAX_ARRAY_SIZE; i++) 
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])	//배열의 앞 원소가 뒷 원소보다 클 경우, 원소의 위치를 바꾼다
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); 	//정렬 후 배열 출력

	return 0;
}

/*셸 정렬 함수*/
int shellSort(int *a)
{
	int i, j, k, h, v; //인덱스, v는 원소

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	//정렬 전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)	//h는 교체할 두 원소의 간격을 나타내며 1/2씩 줄어든다
	{
		for (i = 0; i < h; i++)	//원소의 인덱스를 하나씩 증가한다
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)	//j를 간격 h씩 증가시키며 두 원소를 비교하도록 한다
			{
				v = a[j];	
				k = j;

				/*간격 h만큼 앞에 있는 원소와 비교하며 두번째 원소가 작을 경우 원소의 위치를 변경한다*/
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];				
					k -= h;		//순서는 뒤에서 앞으로 간다
				}
				a[k] = v;	//저장해 놓은 값을 앞에 저장
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);	//정렬 후 배열 출력

	return 0;
}

/*퀵 정렬 함수*/
int quickSort(int *a, int n)
{
	int v, t;	//배열의 원소를 저장할 변수
	int i, j;	//배열의 인덱스를 저장할 변수

	if (n > 1)
	{
		v = a[n-1];	 //마지막 원소(pivot)
		i = -1;		 //밑의 반복문에서 첫 원소를 가리키기 위해 -1로 설정
		j = n - 1;	 //마지막 원소의 인덱스

		while(1)
		{
			while(a[++i] < v);  //pivot보다 큰 값을 찾으면 반복 종료
			while(a[--j] > v);	//pivot보다 작은 값을 찾으면 반복 종료

			if (i >= j) break;	//큰 값이 작은 값보다 뒤에 위치할 경우 while문 종료

			//pivot보다 더 큰 값과 작은 값의 위치를 변경
			t = a[i];		
			a[i] = a[j];
			a[j] = t;
		}
		//pivot의 위치와 pivot보다 큰 수의 위치를 변경
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		
		quickSort(a, i); 		  //변경된 pivot의 위치를 기준으로 앞에 위치한 수들을 퀵정렬
		quickSort(a+i+1, n-i-1);  //변경된 pivot의 위치를 기준으로 뒤에 위치한 수들을 퀵정렬
	}

	return 0;
}

/*해시 코드를 key/(배열의 크기)의 나머지로 계산해 반환하는 함수*/
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

/*배열의 값을 해시테이블에 저장하는 함수*/
int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/*해시테이블이 비었을 경우, 공간을 동적할당*/
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  
	}
	/*비지 않았을 경우, 주소를 hashtable에 넘겨준다*/
	else {
		hashtable = *ht;	
	}

	/*해시테이블의 값을 -1로 초기화*/
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];		
		hashcode = hashCode(key);

		/*값이 지정되지 않은 슬롯인 경우, key를 저장*/
		if (hashtable[hashcode] == -1){
			hashtable[hashcode] = key;
		}
		/*값이 지정되어 있는 슬롯인 경우*/
		else {
			index = hashcode;
			while(hashtable[index] != -1) {	//빈 슬롯을 찾는다 
				index = (++index) % MAX_HASH_TABLE_SIZE;
			}
			
			hashtable[index] = key;		//빈 슬롯에 값 저장
		}
	}

	return 0;
}

/*해시테이블에서 key를 찾아 인덱스를 리턴하는 함수*/
int search(int *ht, int key)
{
	int index = hashCode(key);

	/*해시테이블에서 key를 찾은 경우*/
	if(ht[index] == key)
		return index;	//인덱스 리턴

	/*key를 찾을 때까지 반복 후 인덱스 리턴*/
	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}


