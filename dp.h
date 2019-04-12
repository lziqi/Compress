int length(unsigned char i)//求i可以用几位来表示
{
	int k = 0;
	while (i != 0)
	{
		i = i >> 1;
		k++;
	}
	return k;
}


void Traceback(int n, int& m, unsigned int s[], unsigned int l[])
{
	if (n == 0)
		return;
	Traceback(n - l[n], m, s, l);
	s[m++] = n - l[n];  //重新为s[]数组赋值，用来存储分段位置  
}
