#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int at;
	int bt;
	int wt;
	int ft;
	int tt;
	int id;
	int pri;
	char state[20];
}*p;

int compare(const void *e1,const void *e2);

int main(int argc,char *argv[])
{
	int n=0,i=0,quantum,ts=0;
	int u=0,k=0;
	int j=0,idle=0;
	int time=0;
	int waitsum=0,turnsum=0,ressum=0;
	FILE *fp,*wp;
	
	fp=fopen(argv[1],"r");
	wp=fopen(argv[2],"w");
	p=(struct node *)malloc(10*sizeof(struct node));
	
	while(fscanf(fp,"%d %d %d %d",&p[i].id,&p[i].pri,&p[i].at,&p[i].bt)!=EOF)
	{
		n++;
		i++;
	}
	quantum=atoi(argv[3]);
	fprintf(wp,"Round Robin\n");
	fprintf(wp,"====================================\n");
	qsort(p,n,sizeof(struct node),compare);
	ts=p[0].at;
	for(i=0;i<n;i++)
		p[i].ft=-1;
	
	while(!notfinish(n))

	{
		
		for(i=0;i<n;i++)
		{
			if(p[i].bt==0){
				continue;
			}
			else if(p[i].bt>quantum)
			{
				
				if(p[u].at>time)
				{
					fprintf(wp,"<time %d> ---- system idle ----\n",time);
					idle++;
					u++;
					time++;
				}
				
				for(j=0;j<quantum;j++)
				{
					if(p[k].at==time)
					{
						fprintf(wp,"<time %d> [new arrival]node %d\n",time,p[k].id);
						strcpy(p[k].state,"new");
						k++;
			
					}
					
					fprintf(wp,"<time %d> node %d is running\n",time,p[i].id);
					strcpy(p[i].state,"running");
					time++;
				}
				if(i<10)
				fprintf(wp,"-----------------context switching\n\n");
				strcpy(p[i].state,"ready");
				p[i].bt=p[i].bt-quantum;
				
				if(p[i].ft==-1)
					p[i].wt=ts-p[i].at;
				else p[i].wt+= ts-p[i].ft;
				p[i].ft=ts+quantum;
				ts+=quantum;
			}
			else
			{
				int btt= p[i].bt;
				for(j=0;j<btt;j++)
				{
					if(p[k].at==time)
					{
						fprintf(wp,"<time %d> [new arrival]node %d\n",time,p[k].id);
						strcpy(p[k].state,"new");
						k++;
						
					}

					fprintf(wp,"<time %d> node %d is running\n",time,p[i].id);
					strcpy(p[i].state,"running");
					time++;
				}

				p[i].bt=0;
				fprintf(wp,"<time %d> node %d is finished\n",time,p[i].id);
				strcpy(p[i].state,"terminated");
				if(i<9)
				fprintf(wp,"-------------------context switching\n\n");

				if(p[i].ft==-1)
					p[i].wt=ts-p[i].at;
				else
					p[i].wt+= ts-p[i].ft;
				p[i].ft=ts+btt;
				ts+=btt;
			}
		}
		
	}
	for(i=0;i<n;i++)
	{
		p[i].tt=p[i].ft-p[i].at;
	}
	

	for(i=0;i<n;i++)
	{
		waitsum=p[i].wt+waitsum;
		turnsum=p[i].tt+turnsum;
		ressum=(p[i].ft-quantum-p[i].at)+ressum;
	
	}
	fprintf(wp,"\n\n<time %d> all node is finished\n",time);
	fprintf(wp,"-----------------------------------\n");
	fprintf(wp,"-----------------------------------\n");
	fprintf(wp,"Avarage Cpu usage : %d percent\n",((time-idle)*100)/time);
	fprintf(wp,"Avarage waiting time : %d\n",waitsum/n);
	fprintf(wp,"Avarage response time : %d\n",ressum/n);
	fprintf(wp,"Avarage turnaround time : %d\n",turnsum/n);
	fclose(fp);
	fclose(wp);
	
}
int notfinish(int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(p[i].bt==0)
			continue;
		else
			break;
		if(i==(n-1))
			return 1;
		else 
			return 0;
	}
}

int compare(const void *e1,const void *e2)
{
	return *(int *)e1- *(int *)e2;
}