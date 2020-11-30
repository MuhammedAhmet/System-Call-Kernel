#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>

int main(int argc,char* argv[])
{
    ///  SYSCALL --->> 335
    if(argv[1] == NULL)
    {
        printf("without parameter -> returned %d \n",syscall(335,0,NULL));    //CPU INFO
        return 0;
    }
    if(strcmp(argv[1],"-all")==0 && argv[2] == NULL)
    {
        printf("-all parameter -> returned %d - %d \n",syscall(335,0,NULL),syscall(335,1,NULL));  /// CPU INFO  +  -ALL
        return 0;
    }
    if(strcmp(argv[1],"-p")==0 && argv[2] != NULL)
    {
        printf("-p parameter -> returned %d - %d \n",syscall(335,0,NULL),syscall(335,2,argv[2])); /// CPU INFO  + -P
        return 0;
    }
    if(strcmp(argv[1],"-all") == 0 && strcmp(argv[2],"-p") == 0  && argv[3] != NULL)  /// CPU INFO + -ALL + -P
    {
        printf("-all -p (Pid) parameter -> retuned  %d - %d - %d \n",syscall(335,0,NULL),syscall(335,1,NULL),syscall(335,2,argv[3])); 
        return 0;
    }
    if(strcmp(argv[1],"-HELP") == 0 && argv[2] == NULL)    /// HELP
    {
        
        printf("\n\n---------------------------HELP SCREEN----------------------------- \n \n");
        printf("./systeminfo.out    >    only CPU information \n");
        printf("./systeminfo.out -all    >    CPU+system statistics \n");
        printf("./systeminfo.out -p 1425    >    CPU+process detail \n");
        printf("./systeminfo.out -all -p 1425    >    CPU+sys.statistics+ps.detail \n");
        printf("----------------------------------------------------------------------------\n");
        return 0;
    }
    else
    {
        printf("WRONG ARGUMENT /// enter -HELP for help \n");
        return 0;
    } 

    return 0;
}