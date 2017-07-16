#include"stdafx.h"
#include"work.h"
const int N=100;
char fs1[N][N];
char fs2[N][N][N];
int fp[N][N],pcnt;
const int seed=19990824;
int randseed[2005];//power seed 
int rs[2][2005];//fight seed
int fcnt;//过程计数器 
int hp[3],power[3];
char opt[N][N*2];
char s1[N],s2[N];
struct fight
{
	int id;
	int mid,fid,fidt;//动作以及技能
	int hp;//伤害 
}pro[N]; 
const int seed2=5927;
int ch[2],c1,c2;//c1动作 c2 技能 
void int2str(const int &int_temp,string &string_temp)  
{  
	stringstream stream;  
	stream<<int_temp;  
	string_temp=stream.str();   //此处也可以用 stream>>string_temp  
}  
void init()
{
	srand(seed);
	for(int i=0;i<=2000;i++)
		randseed[i]=rand()%21234;
}
void initconf()
{
	c1=9,c2=12;
	strcpy(fs1[0],"使用了");
	strcpy(fs1[1],"熟练运用");
	strcpy(fs1[2],"使出了");
	strcpy(fs1[3],"用尽全力使出了");
	strcpy(fs1[4],"冷笑着使出了");
	strcpy(fs1[5],"发狂着使用了");
	strcpy(fs1[6],"使用了");
	strcpy(fs1[7],"运用");
	strcpy(fs1[8],"生疏的运用");
	strcpy(fs2[0][0],"王八拳");
	strcpy(fs2[0][1],"&如同王八一样被击中了");
	fp[0][1]=800;
	strcpy(fs2[0][2],"&灵巧的躲开了");
	fp[0][2]=0;
	strcpy(fs2[1][0],"冲撞");
	strcpy(fs2[1][1],"&被顶飞了");
	fp[1][1]=600;
	strcpy(fs2[1][2],"&机智的躲开了");
	fp[1][2]=0;
	strcpy(fs2[2][0],"天马流星拳");
	strcpy(fs2[2][1],"&被一拳打飞");
	fp[2][1]=2000;
	strcpy(fs2[2][2],"令人惊奇的是，&居然躲开了，但是还是不小心被打到了");
	fp[2][2]=200;
	strcpy(fs2[3][0],"庐山升龙霸");
	strcpy(fs2[3][1],"&被击飞后在空中完成托马斯全旋");
	fp[3][1]=1700;
	strcpy(fs2[3][2],"但是&从小在庐山长大，不怕这招");
	fp[3][2]=0;
	strcpy(fs2[4][0],"星云锁链");
	strcpy(fs2[4][1],"&被钳制住了");
	fp[4][1]=1000;
	strcpy(fs2[4][2],"但&没有被钳制住");
	fp[4][2]=0;
	strcpy(fs2[5][0],"毒药");
	strcpy(fs2[5][1],"&吃下了毒药，中毒了");
	fp[5][1]=1200;
	strcpy(fs2[5][2],"但是&没有吃下毒药");
	fp[5][2]=0;
	strcpy(fs2[6][0],"金钢火焰旋风拳");
	strcpy(fs2[6][1],"&被打中了，全身燃起了火焰");
	fp[6][1]=1800;
	strcpy(fs2[6][2],"&虽然躲开了，但还是着火了");
	fp[6][2]=800;
	strcpy(fs2[7][0],"幽灵箭");
	strcpy(fs2[7][1],"&被射穿了");
	fp[7][1]=1000;
	strcpy(fs2[7][2],"&灵巧的避开了");
	fp[7][2]=0;
	strcpy(fs2[8][0],"岩石碎击");
	strcpy(fs2[8][1],"&被击碎了");
	fp[8][1]=1400;
	strcpy(fs2[8][2],"&还是勉强躲开了");
	fp[8][2]=0;
	strcpy(fs2[9][0],"绝命火焰");
	strcpy(fs2[9][1],"&被烧得一命呜呼");
	fp[9][1]=1000;
	strcpy(fs2[9][2],"但是&不怕火");
	fp[9][2]=0;
	strcpy(fs2[10][0],"极度冰点");
	strcpy(fs2[10][1],"&快被冻死了");
	fp[10][1]=2000;
	strcpy(fs2[10][2],"&好像并不害怕寒冷");
	fp[10][2]=0;
	strcpy(fs2[11][0],"冲顶");
	strcpy(fs2[11][1],"&被顶碎了");
	fp[11][1]=900;
	strcpy(fs2[11][2],"可惜&躲开了");
	fp[11][2]=0;

}
int getpower(char ta[])
{
	int len=strlen(ta);int ret=0;
	if(strcmp(ta,"殷嫦越")==0)return 100000;
	for(int i=abs(ta[0]*ta[1])%1700,cnt=0;cnt<=len;i++,cnt++)
	{
		int now=randseed[i]*(abs(ta[cnt])%20);
		now%=6000;
		if((randseed[i]+randseed[i+1])%2==0)
			ret+=now;
		else ret-=(now%1500);
	}
	if(ret<1000)ret+=3000;
	if(ret<2000)ret+=1500;
	if(ret>0)
		return ret;
	else return (ret+1000000)%seed2;
}
int gethp(int power)
{return power/3+power;}
void getchance(int p1,int p2)//输入数据必须保证p1<p2 
{
	double chance=(double)p1/(double)p2;
	ch[0]=chance*10000;
	ch[1]=10000-ch[0];
	ch[1]+=3500;
	if(ch[0]<=4000)ch[0]+=1000;
}
void nmaker(char nm[],int sed[])//以姓名为seed 得到随机数 
{
	int len=strlen(nm);
	unsigned int ts=0;
	for(int i=0;i<len;i++)ts+=nm[i]*('f'+91);
	srand(ts);
	for(int i=0;i<=2000;i++)sed[i]=rand()%10086;//前1000用作动作 后1000用作技能 
}
void mix()
{
	for(int i=0;i<2000;i++)
	swap(rs[0][randseed[i]%2000],rs[1][randseed[i-1]%2000]);
} 
void go(int i,int t,int mv,int fi)
{
	int hpp=fp[fi][t];
	if(hpp!=0)//不是没打中 
	{
		int ext=(rs[i][(randseed[pcnt]*9)%2000])%(int)((double)fp[fi][t]*0.25);
		ext=ext*((double)ch[i]/10000);
		if(ext%10==1)ext=-ext;
		hpp+=ext+power[i]/10;
	}
	pro[pcnt].id=i;
	pro[pcnt].mid=mv;
	pro[pcnt].fid=fi;
	pro[pcnt].hp=hpp;
	pro[pcnt].fidt=t;
	pcnt++;hp[(i+1)%2]-=hpp;//cout<<hp[(i+1)%2]<<endl;
}
void getfight()
{
	int sscnt=1000;
	for(;(hp[0]>0&&hp[1]>0);sscnt++)
	{
		//cout<<hp[0]<<" "<<hp[1]<<endl; 
		for(int i=0;i<=1&&(hp[0]>0&&hp[1]>0);i++)//i 移动 
		{
			int now=(randseed[sscnt]*(power[i]%99+1))%10000+1;		
			int t=(now<=ch[i])?1:2;//1为打中了	
			int mv=(rs[i][sscnt-1000]*(power[i]%50+1))%c1;//动作编号;
			int fi=(rs[i][sscnt]*(power[(i+1)%2]%30+1)+rs[(i+1)%2][mv])%c2;//技能编号;
			go(i,t,mv,fi);//1 4 11 2 0
		}	
	}
}
void outpt(char s1[],char s2[])
{
	for(int i=0;i<pcnt;i++)
	{
		string p="";
		if(pro[i].id==0)p+=s1;
		else p+=s2;
		p+=fs1[pro[i].mid];
		p+=fs2[pro[i].fid][0];
		p+=',';
		p+=fs2[pro[i].fid][pro[i].fidt];
		p.replace(p.find('&'),1,pro[i].id==0?s2:s1);
		p+=',';
		p+=pro[i].id==0?s2:s1;
		p+="受到";
		string hpp="";
		int2str(pro[i].hp,hpp);
		p+=hpp;
		p+="点伤害。"; 	
		if(i==pcnt-1)
		{
			if(pro[i].id==0)p+=s2;
			else p+=s1;
			p+="被KO，游戏结束。";
		}
		strcpy_s(opt[i],p.c_str());

	}
} 

void error(int x)
{
	switch(x)
	{
	case 1:
		MessageBox(NULL,L"发生错误 错误代码001",L"error",MB_ICONERROR);return;
	case 2:
		MessageBox(NULL,L"名字必须是四个字以内！",L"error2",MB_ICONERROR);return;
	case 3:
		MessageBox(NULL,L"必须输入两个名字！",L"error3",MB_ICONERROR);return;
	case 4:
		MessageBox(NULL,L"名字太短！",L"error4",MB_ICONERROR);return;
	case 5:
		MessageBox(NULL,L"名字只能含有中英文！",L"error5",MB_ICONERROR);return;
	case 6:
		MessageBox(NULL,L"该对话框已经打开！",L"error6",MB_ICONERROR);return;
	case 7:
		MessageBox(NULL,L"发生错误 错误代码007",L"error",MB_ICONERROR);return;
	}
}
void calc(char ta[],char tb[],char output[])
{
	string temp="",t2="";
	pcnt=fcnt=0;
	strcpy_s(s1,ta);
	strcpy_s(s2,tb);
	init();
	initconf();
	power[0]=getpower(s1);
	power[1]=getpower(s2);
	if(power[0]>power[1])
	{
		swap(power[0],power[1]);
		swap(s1,s2);
	}
	getchance(power[0],power[1]);
	hp[0]=gethp(power[0]);
	hp[1]=gethp(power[1]);
	nmaker(s1,rs[0]);
	nmaker(s2,rs[1]);
	mix();
	temp+=s1;temp+="战斗力:";int2str(power[0],t2);temp+=t2;temp+="  ";t2="";
	temp+="血量:",int2str(hp[0],t2);temp+=t2;temp+='#';t2="";
	temp+=s2;temp+="战斗力:";int2str(power[1],t2);temp+=t2;temp+="  ";t2="";
	temp+="血量:",int2str(hp[1],t2);temp+=t2;temp+='#';
	temp+="Ready?";temp+='#';temp+="Fight!";temp+='#';
	getfight();
	outpt(s1,s2);
	for(int i=0;i<pcnt;i++)temp+=opt[i],temp+='#';
	strcpy(output,temp.c_str());
}