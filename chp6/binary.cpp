#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
//返回arr中任意一个局部最小出现的位置
int getLessIndex(vector<int> arr) {
	int len = arr.size();
	//arr长度为0,返回-1
	if(len == 0)
		return -1;
	if(len == 1)
		return arr[0];
	/*
	   if(arr[0] < arr[1])
	   return arr[0];
	   */
	if(arr[len-1] < arr[len-2])
		return arr[len-1];
	int left = 1,right = len-2;
	int mid;
	while(left <= right){
		mid = left + (right-left)/2;
		//cout << mid << " " <<arr[mid]<<endl;
		if(arr[mid] < arr[mid+1] && (arr[mid] < arr[mid-1]))
			return arr[mid];
		if(arr[mid] > arr[mid+1]){
			left = mid+1;
		}else{
			right = mid-1;
		}
	}
	return -1;
}


//在arr中找到num这个数出现的最左边的位置
int findPos(vector<int> arr, int n, int num) {
	int res = -1;
	int mid,left = 0,right = n-1;
	while(left <= right){
		mid = left +(right - left)/2;
		//cout << mid << endl;
		if(arr[mid] == num){
			res = mid;
			right = mid-1;
		}else if(arr[mid] > num){
			right = mid-1;
		}else
			left = mid+1;
	}
	return res;
}

//有序循环数组arr及它的大小n，请返回最小值
int getMin(vector<int> arr, int n) {
	int ret,flag = 0;
	int len = arr.size();
	int mid,left = 0,right = len-1;
	//arr包含循环部分
	while(left < right){
		//有序，返回最左边的数字
		if(arr[left] < arr[right])
			return arr[left];
		mid = left + (right-left)/2;
		if(arr[left] > arr[mid]){//在左部分
			right = mid;
		}else if(arr[right] < arr[mid]){//在右部分
			left = mid + 1;
		}else{
			flag = 1;
			break;
		}
	}
	ret = arr[left];
	if(flag && arr[left] <= arr[mid] && arr[right] >= arr[mid]){
		//有序循环数组，说明arr[right] = arr[mid] = arr[left],只能遍历
		int tmp = arr[left];
		for(int i = 0;i < len;i++){
			if(arr[i] < ret)
				ret = arr[i];
		}
	}


	return ret;
}

//找到满足arr[i]==i条件的最左的位置
int find(vector<int> arr, int n) {
	int res = -1;
	int len = arr.size();
	if(len == 0)
		return -1;
	int left = 0,right = len-1,mid;
	if(arr[0] > right)
		return -1;
	if(arr[right] < 0)
		return -1;
	//下标严格增1,数组有序
	while(left <= right){
		mid = left + (right-left)/2;
		if(arr[mid] > mid){
			right = mid-1;
		}else if(arr[mid] < mid){
			left = mid+1;
		}else{
			res = mid;
			right = mid-1;
		}
	}

	return res;
}

//得到整数k的N次方的过程请实现时间复杂度为O(logN)的方法，为了防止溢出，请返回结果Mod 1000000007的值。
int getPower(int k, int N) {
	if(k==0) return 0;
	if(N==0) return 1;
	unsigned long long base =(unsigned long long)k;
	unsigned long long res = 1;
	unsigned long long exp = 1;
	for(;exp <=  N;exp = exp << 1){
		//注意:exp <= N,否则N正好是4这种数字的时候，exp&N会一直为0

		cout << exp <<" " << N<< endl;
		if(exp&N)
			res = res*base % 1000000007;
		base = base*base % 1000000007;
	}
	return res;
}
int main(){
	int k = 2,N= 3;
	cout << getPower(k,N) << endl;




	/*
	//找到满足arr[i]==i条件的最左的位置
	vector<int> arr = {-1,0,2,3};
	int n= 4;
	int ret = find(arr,n);
	cout << ret << endl;
	*/

	/*
	//找到满足arr[i]==i条件的最左的位置
	//vector<int> arr = {10,4,5,6,7,11,12,13,14,15};
	//vector<int> arr = {3,2,9,2,1,4,0,10,9,0,8,3,5,6,7,1,9,2,4,0,7};
	vector<int> arr = {3,5,1,5,9,4,6,5,3,0,8,4,5,8,7,1,4,5,2,3,0,5,0,4};
	cout << getLessIndex(arr) << endl;
	*/
	/*
	//在arr中找到num这个数出现的最左边的位置
	vector<int> arr = {36,67,146,208,210,369,616};
	int n= 7;
	int num = 616;
	int ret = findPos(arr,n,num);
	cout << ret << endl;
	*/


	/*
	//有序循环数组arr及它的大小n，请返回最小值
	vector<int> arr = {4,1,2,3,3};
	int n= 5;
	int ret = getMin(arr,n);
	cout << ret << endl;
	*/
	return 0;
}
