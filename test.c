#include <stdio.h>
	#include <stdlib.h>
	#include <assert.h>
	#include <unistd.h>  // 为了使用access()函数
	 
	int main() {
	   
	 
	    int ret = system("make");
	    assert(ret != -1);
	 
	    ret = system("./glimmer -t result.txt < test.txt");
	    assert(ret != -1);

	    system("diff -y -w test.txt result.txt");
	 
	    return 0;
	}
