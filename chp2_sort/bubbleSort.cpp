#include <iostream>
#include <vector>
using namespace std;
void swap(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;
}
int* bubbleSort(int* A,int n){
	//大的在后面
	int i = 0;
	for(i = 0;i < n;i++){
		for(int j = n-1;j > i;j--){
			if(A[j] < A[j-1]){
				swap(A[j-1],A[j]);
			}
		}
	}
	cout << "冒泡"<< endl;
	for(int i = 0;i < 9;i++)
		cout << A[i] << "  ";
	cout << endl;
	return A;
}
int* selectionSort(int* A,int n){
	cout << " 直接选择排序" << endl;
	int min;
	for(int i = 0;i < n;i++){
		min = i;
		for(int j = i+1;j < n;j++){
			if(A[j] < A[min])
				min = j;
		}
		if(i != min){
			swap(A[i],A[min]);
		}
	}
	for(int i = 0;i < 9;i++)
		cout << A[i] << "  ";
	cout << endl;
	return A;
}
int* insertionSort(int *A,int n){
	cout << "插入排序" << endl;
	int i,j;
	int temp;
	for(i = 1;i < n;i++){
		if(A[i-1] > A[i]){
			cout << i << endl;
			temp = A[i];
			/*
			   for(j = i-1;(A[j] > temp && j>=0);j--){
			   A[j+1] = A[j];
			   }
			   A[j+1] = temp;
			   }
			   */
			//二分查找
			int low = 0;
			int high = i-1;
			while(low <= high){
				int mid = (low+high)/2;
				if(A[mid] < temp)
					low = mid+1;
				else if(A[mid] > temp)
					high = mid-1;
			}
			for(int j = i-1;j >= low;j--){
				A[j+1] = A[j];
			}
			A[low] = temp;
			cout << "A[" << low << "] = " << temp << endl;
	}
}
for(int i = 0;i < 9;i++)
cout << A[i] << "  ";
cout << endl;
return A;
}
void merge(int* A,int first,int mid,int last){
	int *p = new int[last-first+1];
	int i =first, j = mid+1,k = 0;
	while(i < mid+1 && j <= last){
		if(A[i] < A[j])
			p[k++] = A[i++];
		else
			p[k++] = A[j++];
	}
	while(i < mid+1)
		p[k++] = A[i++];
	while(j < last)
		p[k++] = A[j++];
	for(int m = 0;m < k;m++)
		A[first+m] = p[m];
	delete []p;
}
void msort(int* A,int first,int last){
	if(first < last){
		int mid = (first+last)/2;
		msort(A,first,mid);
		msort(A,mid+1,last);
		merge(A,first,mid,last);
	}
}
void merge_pass(int* A,int s,int n){
	int i = 0;
	while(i < n-2*s+1){
		merge(A,i,i+s-1,i+2*s-1);
		i += 2*s;
	}
	if(i < n-s+1)
		merge(A,i,i+s-1,n);
}
int* mergeSort(int* A,int n){
	//递归归并排序
	//msort(A,0,n-1);
	//非递归归并排序
	int k = 1;
	while(k < n){
		merge_pass(A,k,n);
		k *= 2;
		merge_pass(A,k,n);
		k*=2;
	}

	for(int i = 0;i < 9;i++)
		cout << A[i] << "  ";
	cout << endl;

	return A;
}
//快速排序
int partation(int* A,int low,int high){
	int key = A[low];
	while(low < high){
		while(A[high] > key && low < high)
			high--;
		A[low] = A[high];
		while(A[low] <= key && low < high)
			low++;
		A[high] = A[low]; 
	}
	A[low] = key;
	return low;
}
void quick(int* A,int low,int high){

	int privot;
	if(low < high){
		privot = partation(A,low,high);
		quick(A,low,privot-1);
		quick(A,privot+1,high);
	}
}

int* quickSort(int* A,int n){
	cout << "快速排序" << endl;
	int low = 0;
	int high = n-1;
	quick(A,low,high);
	for(int i = 0;i < 9;i++)
		cout << A[i] << "  ";
	cout << endl;
}

//希尔排序
int* shellSort(int* A,int n){
	int increment = n;
	int i,j;
	do{
		increment = increment/3 + 1;
		for(i = increment;i < n;i++){
			if(A[i] < A[i-increment]){
				int key = A[i];
				for(j = i-increment;j >= 0 && A[j] > key;j -= increment){
					A[j+increment] = A[j];
				}
				A[j+increment] = key;
			}
		}
	}while(increment > 1);
	for(int i = 0;i < 9;i++)
		cout << A[i] << "  ";
	cout << endl;
	return A;
}
//计数排序
#define NUM 100
int* countingSort(int* A,int n){
	cout << "计数排序" << endl;
	int* p = new int[NUM];
	for(int i = 0;i < NUM;i++)
		p[i] = 0;
	for(int i = 0;i < n;i++)
		p[A[i]]++;
	int j = 0;
	for(int i = 0;i < NUM;i++){
		while(p[i] != 0){
			A[j] = i;
			j++;
			p[i]--;
		}
	}
	for(int i = 0;i < 9;i++)
		cout << A[i] << "  ";
	cout << endl;
	return A;
}
//基数排序
void countSort(int* A,int n,int exp){
	vector<vector<int> > buckets;
	buckets.resize(10);
	for(int i = 0;i < n;i++){
		if(exp == 1){
			buckets[A[i]%10].push_back(A[i]);
		}else{
			buckets[A[i]/exp%10].push_back(A[i]);
		}
	}
	int j = 0;
	for(int i = 0;i < 10;i++){
		for(auto x:buckets[i])
			A[j++] = x;
	}
}
int* radixSort(int* A,int n){
	int max = A[0];
	for(int i = 0;i < n;i++){
		if(max < A[i])
			max = A[i];
	}
	int exp = 1;
	while(max){
		countSort(A,n,exp);
		max /=10;
		exp *= 10;
	}
	for(int i = 0;i < 9;i++)
		cout << A[i] << "  ";
	cout << endl;
	return A;

}
void small_heap(vector<int> &A,int s,int m){
	//cout << A[s] << "  " << A[m] << endl;
	int temp = A[s];
	//cout << "temp = " << temp << endl;
	for(int j = 2*s +1;j <= m;j *=2){
		if(j < m && A[j+1] < A[j])
			j++;
		if(temp < A[j])
			break;
		A[s] = A[j];
		s = j;
	}
	A[s] = temp;
}
vector<int> sortElement(vector<int> A,int n,int k){
	if(n == 0 || n < k)
		return A;
	int i = 0;
	vector<int> B;
	while(i < n){
		small_heap(A,0,k-1);
		B.push_back(A[0]);
		i++;
		A.erase(A.begin());
	}
	for(int j = 0;j < n;j++){
		A[j] = B[j];
		cout << A[j] << "  ";
	}
	cout << endl;
	return A;
}
//堆排序,大顶堆
void heapAjust(int* A,int s,int m){
	int temp = A[s];
	for(int j= 2*s+1;j <= m;j = 2*j +1){
		if(j < m && A[j] < A[j+1])
			j++;
		if(temp >= A[j])
			break;
		A[s] = A[j];
		s = j;
	}
	A[s] = temp;
}

int* heapSort(int* A,int n,int* B){
	cout << "堆排序" << endl;
	for(int i = n/2-1;i >= 0;i--){
		heapAjust(A,i,n-1);
	}
	int j = 0;
	for(int i = n-1;i >=n-4;i--){
		B[j++] = A[0];
		swap(A[i],A[0]);
		heapAjust(A,0,i-1);
	}
	for(int i = 0;i < n;i++)
		cout << A[i] << "  ";
	cout << endl;
	return B;
}
int main(){
	//vector<int> A = {2,1,4,3,6,5,8,7,9,10,13,14,16,15};
	//A = sortElement(A,14,2);
	//int C[] = {1,2,3,4};
	//int A[] = {5,1,9,3,7,4,8,6,2};
	//bubbleSort(A,9);
	//selectionSort(A,9);
	//insertionSort(A,9);
	//mergeSort(A,9);
	//quickSort(A,9);
	int B[4];
	int A[] = {2,1,4,3,6,5};
	heapSort(A,6,B);
	for(int i = 0;i< 4;i++)
		cout << B[i] << endl;
	//shellSort(A,9);
	//countingSort(A,9);
	//radixSort(A,9);
	return 0;
}
