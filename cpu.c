#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


/*
void getResourceRatio(){
	system("top -n 1|grep Cpu|cut -d \",\" -f 1|cut -d \":\" -f 2 >>cpu.txt");
	system("top -n 1|grep Cpu|cut -d \",\" -f 2 >>cpu.txt");
	system("top -n 1|grep Mem|cut -d \",\" -f 1 |cut -d \":\" -f 2 >>cpu.txt");
	system("top -n 1|grep Mem|cut -d \",\" -f 2 >>cpu.txt");
}
*/

//cpu information
typedef struct CPU_OCCUPY{
	char name[20];
	unsigned int user;
	unsigned int nice;
	unsigned int system;
	unsigned int idle;

}CPU_OCCUPY;


//mem info

typedef struct PACKED{  
	char name[32];
	unsigned long total;
	char name2[32];
	unsigned long free;
}MEM_OCCUPY;

void get_memoccupy(MEM_OCCUPY *mem){
	FILE *fd;
	int n;
	char buf[256];
	MEM_OCCUPY *m;
	m = mem;

	fd = fopen("/proc/meminfo","r");

	fgets(buf,sizeof(buf),fd);

//	printf("%s\n",buf);
	fgets(buf,sizeof(buf),fd);
//	printf("%s\n",buf);
	fgets(buf,sizeof(buf),fd);
//	printf("%s\n",buf);
	fgets(buf,sizeof(buf),fd);
	printf("%s\n",buf);
/*
	sscanf(buf,"%s %u %s",m->name,&m->free,m->name2);

	fgets(buf,sizeof(buff),fd);

	sscanf(buf,"%s %u %s",m->name,&m->free,m->name2);
*/
	fclose(fd);
}





//
void get_cpu_occupy(CPU_OCCUPY *cpuinfo){

	char buf[256];
	FILE *fp;
	fp = fopen("/proc/stat","r");
	if(fp==NULL) return;
	fgets(buf,sizeof(buf),fp);
	sscanf(buf,"%s %u %u %u %u",cpuinfo->name,&cpuinfo->user,&cpuinfo->nice,&cpuinfo->system,&cpuinfo->idle);
	printf("%s %u %u %u %u\n",cpuinfo->name,cpuinfo->user,cpuinfo->nice,cpuinfo->system,cpuinfo->idle);
	fclose(fp);
	return ;

}


int cal_cpuoccupy(CPU_OCCUPY *o,CPU_OCCUPY *n){

	unsigned long od,nd;
	unsigned long id,sd;

	int cpu_use = 0;

	od = (unsigned long)(o->user+o->nice+o->system+o->idle);
	nd = (unsigned long)(n->user+n->nice+n->system+n->idle);

	id = (unsigned long)(n->user-o->user);
	sd = (unsigned long)(n->system-n->system);

	if((nd-od)!=0){
		cpu_use = (int)((sd+id)*10000)/(nd-od);
	}else
		cpu_use = 0;
	return cpu_use;
}
/*
void get_mem_occupy(MEM_INFO &meminfo){


}
*/


int main(){

	CPU_OCCUPY cpu_stat1;
	CPU_OCCUPY cpu_stat2;
	MEM_OCCUPY mem_stat;

	/*
	//获取第一次cpu使用情况
//	get_cpu_occupy((CPU_OCCUPY*)&cpu_stat1);
	get_cpu_occupy(&cpu_stat1);
	sleep(10);

	//获取第二次cpu使用情况
//	get_cpu_occupy((CPU_OCCUPY*)&cpu_stat2);
	get_cpu_occupy(&cpu_stat2);
	
	double cpu_use = cal_cpuoccupy(&cpu_stat1,&cpu_stat2);
	printf("cpu_use = %f",cpu_use);
	*/

	get_memoccupy(&mem_stat);
	return 0;

}
