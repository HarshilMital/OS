#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	int rv;
	rv = remove(argv[2]);
	if(rv==0)
	  {
	    printf("successfully removed %s\n", argv[2]);
	  }
	else
	   {
	    printf("Unsuccessfull\n");
	   }
}