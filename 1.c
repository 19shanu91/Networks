     #include <sys/types.h>
     #include <unistd.h>
     #include <stdio.h>
     #include <stdlib.h>
     #include <string.h>

     /* Read characters from the pipe and echo them to stdout. */
     
     void
     read_from_pipe (int file)
     {
       FILE *stream;
       int c;
       stream = fdopen (file, "r");
       while ((c = fgetc (stream)) != EOF)
         putchar (c);
       fclose (stream);
     }
     
     /* Write some random text to the pipe. */
     
     void
     write_to_pipe (int file)
     {
       FILE *stream;
       stream = fdopen (file, "w");
       fprintf (stream, "hello, world!\n");
       fprintf (stream, "goodbye, world!\n");
       fclose (stream);
     }
     
     int main (void)
     {
       pid_t pid;
       int mypipe[2];
     
       /* Create the pipe. */
       if (pipe (mypipe))
         {
           fprintf (stderr, "Pipe failed.\n");
           return EXIT_FAILURE;
         }
       /* Create the child process. */
       pid = fork ();
	pid_t gpid, gpid2;
	       
	if (pid == (pid_t) 0)
         {
	gpid2=getppid();
	gpid=getpid();
	/*	char ch ;
	ch = getchar();
	ch = getchar();
	ch=getchar();
	printf("%cshashank" ,ch);
           /* This is the child process.
              Close other end first. */
           close (mypipe[1]);
           read_from_pipe(mypipe[0]);
	printf("Presently in Child Process.\n");
	printf("Child pid : %d\n",gpid);

	printf("Child-Parent pid : %d \n",gpid2);
	printf("Value of pid : %d\n",pid);
           return EXIT_SUCCESS;
         }
       else if (pid < (pid_t) 0)
         {
           /* The fork failed. */
           fprintf (stderr, "Fork failed.\n");
           return EXIT_FAILURE;
         }
       else
         {
	pid_t ggpid;
	ggpid=getpid();
           /* This is the parent process.
              Close other end first. */
           close (mypipe[0]);
           write_to_pipe (mypipe[1]);
printf("Presently in Parent Process.\n");
	printf("Parent pid : %d \n",ggpid);
	printf("Child pid : %d \n",pid);
	printf("Value of pid : %d\n",pid);		           
		return EXIT_SUCCESS;
         }
     }
