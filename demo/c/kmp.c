/*

Donald Knuth、Vaughan Pratt、James H. Morris三人于1977年联合发表，故取这3人的姓氏命名此算法。

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int ViolentMatch(char* s, char* p)
{
	int sLen = strlen(s);
	int pLen = strlen(p);
 
	int i = 0;
	int j = 0;
	while (i < sLen && j < pLen)
	{
		if (s[i] == p[j])
		{
			//如果当前字符匹配成功（即S[i] == P[j]），则i++，j++    
			i++;
			j++;
		}
		else
		{
			//如果失配（即S[i]! = P[j]），令i = i - (j - 1)，j = 0    
			i = i - j + 1;
			j = 0;
		}
	}
	//匹配成功，返回模式串p在文本串s中的位置，否则返回-1
	if (j == pLen)
		return i - j;
	else
		return -1;
}



const int NO_PREMATCH_TO_USE = -1;    //maigic number  -1+1 =>index 0
int index_KMP(char s[], char t[], int next[])
{
	int i = 0; //point to s
	int j = 0; //point to pattern string
	while (s[i] && t[j])
	{
		if (s[i] == t[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j]; //KMP算法的核心就是: i 指针不用回退，j指针尽量少回退
			if (j == NO_PREMATCH_TO_USE)
			{
				i++;
				j = 0;
			}
		} //if-else
	}	 //while
	if (t[j] == 0)
		return (i - strlen(t));
	else
		return 0;
}


void get_next(char t[], int next[])
{
	int i;
	int k;
	next[0] = NO_PREMATCH_TO_USE;

	/*先构造前几个next 元素，至少出现一个非 NO_PREMATCH_TO_USE 的值 */
	for(i=1;i<strlen(t);i++)
	{
		if(t[i]==t[0])  next[i]=NO_PREMATCH_TO_USE;
	}
	if (i<strlen(t)){
		int j,l;
		for (j=i-1;j>0;j--)
		{
			/*if t[0:j-1] ==t[i-j:i-1] : next[i]=j */
			int e = 1;
			for (l=0;l<j;j++){
				if (t[l]!=t[l+i-j]){
					e=0;
					break;
				}
			}
			if (e==1)
			{
				next[i]=j;
			}
		}	 
	}
	
	for(;i<strlen(t);i++)
	{
		k= next[i];
		if (k!=-1)
		{
			if (t[i] == t[k])
			{
				next[i+1]=k+1;
			}
			else 
			{
				for (;k!=-1;)
				{
					k=next[k];
					if (k== -1)
					{
						next[i+1]=-1;
						break;	
					}
					else if (t[k] == t[i])
					{
						next[i+1]=k;
						break;
					}
				}
			}
		}	
		else
		{
			if (t[i]==t[0])
				next[i+1]=-1;
			else
				next[i+1]=0;
		}
	}			
	k = strlen(t);
	printf("next[] of %s by get_next is:\n",t);
	for (i = 0; i < k; i++)
		printf("%3d", next[i]);
	printf("\n");
}

void get_next2(char t[], int next[])
{
	int i = 0;
	int k = next[0] = NO_PREMATCH_TO_USE;
	
	while (t[i])
	{
		if (k == NO_PREMATCH_TO_USE || t[i] == t[k])
		{
			i++;
			k++;
			if (t[i] == t[k])
				next[i] = next[k]; //not change k,so k always increase
			else
				next[i] = k;
		}
		else
		{
			k = next[k];
		}

	} //while

	k = strlen(t);
	printf("next[] of %s is:\n",t);
	for (i = 0; i < k; i++)
		printf("%3d", next[i]);
	printf("\n");
}




//优化过后的next 数组求法
void GetNextval(char* p, int next[])
{
	int pLen = strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < pLen - 1)
	{
		//p[k]表示前缀，p[j]表示后缀  
		if (k == -1 || p[j] == p[k])
		{
			++j;
			++k;
			//较之前next数组求法，改动在下面4行
			if (p[j] != p[k])
				next[j] = k;   //之前只有这一行
			else
				//因为不能出现p[j] = p[ next[j ]]，所以当出现时需要继续递归，k = next[k] = next[next[k]]
				next[j] = next[k];
		}
		else
		{
			k = next[k];
		}
	}
}

int KmpSearch(char* s, char* p)
{
	int i = 0;
	int j = 0;
	int sLen = strlen(s);
	int pLen = strlen(p);
	int * next = malloc(pLen * sizeof(int));

	GetNextval(p,next);

	while (i < sLen && j < pLen)
	{
		//①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++    
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			//②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]    
			//next[j]即为j所对应的next值      
			j = next[j];
		}
	}
	if (j == pLen)
		return i - j;
	else
		return -1;
}


int main()
{
	char *s = "acabaabaabcacaaaabc";
	char t[] = "aaaab";
	printf("%d \n ", ViolentMatch(s,t));
	printf("%d \n ", KmpSearch(s,t));

	int next[sizeof(t)];
	get_next2(t, next);
	get_next(t, next);
	printf("find %s in %s by index %3d\n", t,s,index_KMP(s, t, next));

	char t2[] = "abaabc";
	printf("%d \n ", ViolentMatch(s,t2));
	printf("%d \n ", KmpSearch(s,t2));


	int next2[sizeof(t2)];
	get_next2(t2, next2);
	get_next(t2, next2);

	printf("find %s in %s by index %3d\n", t2,s,index_KMP(s, t2, next2));

	return 0;
}
