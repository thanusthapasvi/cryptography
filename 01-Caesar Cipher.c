#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{
	int k,i;
	char in[50],ci[50];
	printf("Enter input string : ");
	scanf("%s",&in);
	printf("Enter key value (1 to 25) : ");
	scanf("%d",&k);
	printf("Encrytption is : ");
	for(i=0;i<strlen(in);i++)
	{
		if(islower(in[i]))
			ci[i]=((in[i]-'a'+k)%26)+'a';	
		else
			ci[i]=((in[i]-'A'+k)%26)+'A';	
		printf("%c",ci[i]);
	}
	printf("\nDecrytption is : ");
	for(i=0;i<strlen(ci);i++)
	{
		if(islower(in[i]))
			in[i]=((ci[i]-'a'-k)%26)+'a';	
		else
			in[i]=((ci[i]-'A'-k)%26)+'A';	
		printf("%c",in[i]);
	}
}
