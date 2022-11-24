#define _GNU_SOURCE
#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define SYS_copy_2Dmatrix 451

void check_equal(float lhs[3][3], float rhs[3][3], int r, int c)
{
    int i, j;
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (lhs[i][j] != rhs[i] [j])
            {
                printf("Error : LHS[%d][%d] != RHS[%d][%d]\n", i, j, i, j);
                return;
            }
        }
    }
    printf("Message : Success LHS = RHS \n");
}

int main()
{
    float src_arr[3][3]={{1,2,3},{21,22,23},{31,32,33}};
    float dest_arr [3][3];
    long sys_call_status = syscall(SYS_copy_2Dmatrix, src_arr, dest_arr, 3, 3);
    for(int i=0;i<3;i++){
    	for(int j=0;j<3;j++){
		printf("%lf ",dest_arr[i][j]);
	}
	printf("\n");
    }

   if(sys_call_status !=EFAULT){
     	 printf("Message : System Call 451 successfuly invoked \n");
       	 check_equal(src_arr, dest_arr, 3, 3);
   }

    return 0;
}
