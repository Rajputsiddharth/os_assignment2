#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE4(copy_2Dmatrix, float*, source, float*, destin, int, row, int , col){
	row =3;
	col=3;
	float buff[3][3];
	if(__copy_from_user(buff,source,sizeof(buff))){
		return -EFAULT;
	}
	if(__copy_to_user(destin,buff,sizeof(buff))){
		return -EFAULT;
	}
	return 0;
}
