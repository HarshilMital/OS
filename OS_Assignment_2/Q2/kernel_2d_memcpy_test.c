#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define KERNEL_2D_MEMCPY_SYSCALL 451
#define LEN 5
#define BRE 5

void check_equal(float lhs[LEN][BRE], float rhs[LEN][BRE], int len, int bre)
{
    int i;
    for (i = 0; i < len; i++)
    {
        for (int j = 0; j < bre; j++){
            if (lhs[i][j] != rhs[i][j])
            {
                printf("Error : LHS[%d] != RHS[%d]\n", i, i);
                return;
            }
            // printf("%f %f\n", lhs[i][j], rhs[i][j]);
        }
        
    }
    printf("Message : Success LHS = RHS \n");
}
int main()
{
    float src_arr[LEN][BRE] = {  {0.1, 0.1, 0.1, 0.1}, 
                            {0.1, 0.1, 0.1, 0.2},
                            {0.1, 0.1, 0.1, 0.2},
                            {0.1, 0.1, 0.1, 0.2},
                            {0.1, 0.1, 0.1, 0.2}
                            };

    float dest_arr[LEN][BRE]; 

    long sys_call_status;

    sys_call_status = syscall(KERNEL_2D_MEMCPY_SYSCALL, src_arr, dest_arr, LEN,BRE);

    if (sys_call_status != EFAULT)
    {
        printf("Message : System Call 451 successfuly invoked \n");
        check_equal(src_arr, dest_arr, LEN, BRE);
    }

    return 0;
}