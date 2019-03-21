
#include<stdio.h>
#include<string.h>
char c[20];
int main()
{
	struct st
	{
		char s[20];
	} a[1010];
	int i, j, k, t, n;
	while (~scanf("%d", &n) && n)
	{
		k = -1, t = 0;
		for (i = 0; i < n; i++)
		{
			scanf("%s", a[i].s);
		}
		for (i = 0; i < n; i++)
		{
			for (j = i + 1; j < n; j++)
			{
				if (strcmp(a[i].s, a[j].s) == 0)
					t++;//单词出现次数
			}
			if (t > k)
			{
				k = t;
				strcpy(c, a[i].s);//将单词出现次数最多的单词不断更新
			}
			t = 0;
		}
		printf("%s\n", c);
		memset(a, 0, sizeof(a));
	}
}
/*
思路：要输出出现次数最多的单词，找到出现最多的单词再比较然后找出出现次数最多的单词。
*/
