#include <iostream>
#include <stack>
#include <vector>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
bool kmp(string stra,string strb){
	int lena = strlen(stra.c_str());
	int lenb = strlen(strb.c_str());
	for(int i = 0;i < lena;i++){
		int j;
		for(j = 0;j < lenb;j++){
			if(stra[i+j] != strb[j])
				break;
		}
		if(j == lenb)
			return true;//找到
	}
	return false;
}

//判断A和B是否互为旋转词
bool chkRotation(string A, int lena, string B, int lenb) {
	string ab = A+A;
	//cout << ab << endl;
	int lenab = lena+lenb;
	return kmp(ab,A) && kmp(ab,B);
}
//字符串A和B及他们的长度返回一个bool值，代表他们是否互为变形词
bool chkTransform(string A, int lena, string B, int lenb) {
	if(lena != lenb)
		return false;
	if(lena == 0 || lenb == 0)
		return false;
	int a[256],b[256];
	for(int i = 0;i < 256;i++){
		a[i] = 0;
		b[i] = 0;
	}
	for(int i = 0;i < lena;i++)
		a[A[i]]++;
	for(int i = 0;i < lenb;i++)
		b[B[i]]++;
	for(int i = 0;i < 256;i++){
		if(a[i] != b[i])
			return false;
	}
	return true;
}
void swap(char& a,char& b){
	char tmp;
	tmp = a;
	a = b;
	b = tmp;
}
void reverse(string& str,int low,int high){
	while(low < high){
		swap(str[low],str[high]);
		low++;
		high--;
	}
	//cout << str << endl;
}
//返回逆序后的字符串
string reverseSentence(string A, int n) {
	//整个逆序
	int len = strlen(A.c_str());
	int low = 0,high = len-1;
	reverse(A,low,high);
	//cout << A << endl;
	//空格分割逆序
	int i = 0;
	for(;i < len;i++){
		if(A[i] == ' '){
			reverse(A,low,i-1);
			low = i+1;
		}
	}
	if(A[i-1] !=' '){
		reverse(A,low,i-1);
	}
	return A;
}
//将字符串的长度为len的前缀平移到字符串的最后，返回平移后的字符串。
string stringTranslation(string A, int n, int len) {
	int lena = strlen(A.c_str());
	reverse(A,0,len-1);
	reverse(A,len,lena-1);
	reverse(A,0,lena-1);
	return A;
}
bool cmp(const string& a,const string& b){
	string ab = a+b;
	string ba = b+a;
	return ab<ba;
}
//返回拼接成的串
string findSmallest(vector<string> strs, int n) {
	string ret;
	sort(strs.begin(),strs.end(),cmp);
	for(auto it = strs.begin();it!=strs.end();it++)
		ret += *it;

	return ret;
}

//空格替换
string replaceSpace(string iniString, int length) {
	int num = 0;
	for(int i = 0;i < length;i++)
		if(iniString[i] == ' ')
			num++;
	int k = length + 2*num;
	for( int i = length;i < k ;i++)
		iniString += '0';
	for(int j = k-1,i = length-1;(j>= 0);i--){
		if(iniString[i] == ' '){
			iniString[j--] = '0';
			iniString[j--] = '2';
			iniString[j--] = '%';
		}else{
			iniString[j--] = iniString[i];
		}
	}
	return iniString;
}
//字符串A(只包含括号)和它的长度n,返回bool值代表它是否为一个合法的括号串
bool chkParenthesis(string A, int n) {
	int num = 0;
	int len = strlen(A.c_str());
	for(int i = 0;i < len;i++){
		if(A[i] == '(')
			num++;
		else if(A[i] == ')'){
			num--;
			if(num < 0)
				return false;
		}else
			return false;
	}
	if(num == 0)
		return true;
	return false;
}
//字符串A及它的长度n，请返回它的最长无重复字符子串长度
int longestSubstring(string A, int n) {
	int lena = strlen(A.c_str());
	int hash[256];
	for(int i = 0;i < 256;i++)
		hash[i] =-1;
	int pre = -1;//前一个字符位置
	int maxlen = 1;
	for(int i = 0;i < lena;i++){
		pre = (pre > hash[A[i]])? pre:hash[A[i]];
		int len = i-pre;
		if(len > maxlen)
			maxlen = len;
		hash[A[i]] = i;
	}
	return maxlen;
}
int main(){
/*
	//返回拼接成的串
	vector<string> strs = {"abc","de","b","ba"};
	int n = 4;
	string ret = findSmallest(strs,n);
	cout << ret << endl;
*/
	/*
	//空格替换
	string iniString = "Mr John Smith";
	int len = 13;
	string ret = replaceSpace(iniString,len);
	cout << ret << endl;
	*/
	/*
	//将字符串的长度为len的前缀平移到字符串的最后，返回平移后的字符串。
	string A = "ABCDE";
	int n = 5;
	int len = 3;
	string ret = stringTranslation(A,n,len);
	cout << ret << endl;
	*/

	/*
	//返回逆序后的字符串
	string A = "dog loves pig";
	int n= 13;
	string ret = reverseSentence(A,n);
	cout << ret << endl;
	*/


	//A中是否存在一棵同构于B的子树


	/*
	//判断A和B是否互为旋转词
	string A = "cdab";
	string B = "abcd";
	int lena = 4,lenb = 4;
	bool ret = chkRotation(A,4,B,4);
	cout << ret << endl;
	*/
	/*
	//字符串A和B及他们的长度返回一个bool值，代表他们是否互为变形词
	string A = "abc";
	string B = "bca";
	int lena = 3,lenb = 3;
	bool ret = chkTransform(A,3,B,3);
	cout << ret << endl;
	*/

}
