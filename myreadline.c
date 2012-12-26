/**********************************************************************
*File Name:myreadline.c
*Description -Reads a file, whose name is given through command line
*argument.It uses the function getline, so it can read lines of 
*any length.
**********************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
char** read_lines_from_file(FILE* fp);
void read_string_array(char** array);
void free_all_memory(char** array);

int main(int argc, char* argv[])
{
	FILE *fp = NULL;
        char** buffer = NULL;
        if (NULL == argv[1])
        {
            printf("Usage: %s <filename>\n", argv[0]);
            return 1;
        }
	fp = fopen(argv[1], "r");
	if (NULL == fp)
	{
	  printf("File %s cannot be opened\n", argv[1]);
	  return 1;
	}
	buffer = read_lines_from_file(fp);
        if (buffer == NULL)
        {
            printf("Error Occured during processing\n");
            return 1;
        }
        read_string_array(buffer);
        //Now free all memory
        free_all_memory(buffer);
        return 0;
}

/**********************************************************************
*Function Name: read_lines_from_file
*Description: Reads lines from a file.
*Arguments: File pointer
*Returns:An array of pointers to lines.Last element of the array is 
NULL. In case of any error NULL is returned.
**********************************************************************/ 

char** read_lines_from_file(FILE* fp)
{
  char *lineptr ; 
  char **buffer = NULL; 
  char **tempbuffer = NULL; 
  int linecount = 0;
  int ret = 0;
  size_t linelength;
  
  /*Using getline function to read an entire line*/
  while (1)
  {
        lineptr = NULL;
        linelength = 0;
        ret = getline(&lineptr,&linelength,fp);
        if (0 > ret)
        { 
            /*Even if getline returns -1, the buffer is allocated, so free it*/
            free(lineptr);
            /*Now check for end of file or error*/
            if (feof(fp))
            {  
                break;    
            }
            else //For Error  
            {
                free_all_memory(buffer);
                return NULL;
            }
        }
    
        linecount++;
        /*Now allocate an array to store the address of this line*/
        tempbuffer = realloc(buffer, linecount  *  sizeof(char*));
        if (NULL == tempbuffer)
        {
            /*Free all previously allocated memory*/
            free_all_memory(buffer);
            return NULL;
        
        }
        //Update buffer
        buffer = tempbuffer;
        tempbuffer = NULL;
        //Add address of this line to buffer
        *(buffer + (linecount - 1) ) = lineptr; //C array starts from 0
  }

  /*Adding the NULL at the end of the arrays of lines*/
  tempbuffer = realloc(buffer, (linecount + 1) *  sizeof(char*));
  if (NULL == tempbuffer)
  {
        /*Free all previously allocated memory*/
        free_all_memory(buffer);
        return NULL;
        
  }
  buffer = tempbuffer;
  tempbuffer = NULL;
  *(buffer + linecount ) = NULL;
  return buffer;
}

/**********************************************************************
*Function Name:read_string_array
*Description -
*Arguments -
*Returns -
**********************************************************************/ 
void read_string_array(char** array)
{
  int ctrstrings = 0;
  while(*array != NULL)
  {
		printf("%s", *array);
		array++;
		ctrstrings++;
  }
  printf("Total Number of Lines = %d", ctrstrings);
}

/**********************************************************************
*Function Name:free_all_memory
*Description -
*Arguments -
*Returns -
**********************************************************************/ 
void free_all_memory(char** array)
{
  /*Free memory for all the lines and then the array itself*/
  char **temp = array;
  if (array != NULL)
  {
    while(*array != NULL)
    {
	free(*array);
	array++;
    }
    free(temp);
  }
}
