     #include <sys/types.h>
     #include <unistd.h>
     #include <stdio.h>
     #include <stdlib.h>
     #include <string.h>
	int cnt=0;
	
	void write_to_pipe(int pipe)
	{
		FILE *stream;
		int c;
		stream=fdopen(pipe,"w");
		char word[50];
		printf("\n Enter the words:");
		gets(word);
		fprintf(stream,"%s",word);
		fclose(stream);
	}
	
	void read_from_pipe( int pipe)
	{
		FILE *stream;
		int c;
		char word_cnt[50][10];
		char arr[50];
		int i=0,j=0;
		stream=fdopen(pipe,"r");
		int chk=0;
		while((c=fgetc(stream))!=EOF)
		{
			chk=0;
			word_cnt[i][j]=c;
			if(c==(char)' ')
			{
				word_cnt[i][j]='\0';
				j=0;
				i++;
				cnt++;
				chk=1;
			}
			putchar(c);
			if(chk==0)
			{
				j++;
			}
		}
		word_cnt[i][j]='\0';
		
		for(i=0;i<cnt;i++)
		{
			for(j=i+1;j<=cnt;j++)
			{
				if(strcmp(word_cnt[i],word_cnt[j])>0)
				{
					strcpy(arr,word_cnt[i]);
					strcpy(word_cnt[i],word_cnt[j]);
					strcpy(word_cnt[j],arr);
				}
			}
		}
		printf("\n The Sorted words are :\n");
		int len=0;
		for(i=0;i<=cnt;i++)
		{
			len=strlen(word_cnt[i]);
			for(j=0;j<len;j++)
			{
				printf("%c",word_cnt[i][j]);
			}
			printf("\n");
		}
		fclose(stream);
	}
	
	int main()
	{
		pid_t pid;
		int filed[2];
		
		if(pipe(filed))
		{
			printf("Pipe failed");
			return EXIT_FAILURE;
		}
		
		pid=fork();
		
		if(pid==(pid_t)0)
		{
			close(filed[1]);
			read_from_pipe(filed[0]);
			return EXIT_SUCCESS;
		}
		else if(pid<(pid_t)0)
		{
			printf("pipe failed \n");
			return EXIT_FAILURE;
		}
		else
		{
			close(filed[0]);
			write_to_pipe(filed[1]);
			return EXIT_SUCCESS;
		}
	}
