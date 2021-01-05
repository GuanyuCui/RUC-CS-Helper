#include <iostream>

const char * _strstr(char * src, char * dest)
{
	int lenSrc = strlen(src);
	int lenDest = strlen(dest);
	for(int i = 0; i <= lenSrc - lenDest; )
	{
		for(int j = 0; j < lenDest; j++)
		{
			if(dest[j] != src[i + j])
			{
				i += (j + 1);
				break;
			}
			if(j == lenDest - 1)
			{
				return src + i;
			}
		}
	}
	return NULL;
}
int main(int argc, char *argv[])
{
	char a[] = {"HelloWorld"};
	char b[] = {"World"};
	printf("%p",_strstr(a, b));
	return 0;
}