#include"stdafx.h"
#include"work.h"
const int N=100;
char fs1[N][N];
char fs2[N][N][N];
int fp[N][N],pcnt;
const int seed=19990824;
int randseed[2005];//power seed 
int rs[2][2005];//fight seed
int fcnt;//���̼����� 
int hp[3],power[3];
char opt[N][N*2];
char s1[N],s2[N];
struct fight
{
	int id;
	int mid,fid,fidt;//�����Լ�����
	int hp;//�˺� 
}pro[N]; 
const int seed2=5927;
int ch[2],c1,c2;//c1���� c2 ���� 
void int2str(const int &int_temp,string &string_temp)  
{  
	stringstream stream;  
	stream<<int_temp;  
	string_temp=stream.str();   //�˴�Ҳ������ stream>>string_temp  
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
	strcpy(fs1[0],"ʹ����");
	strcpy(fs1[1],"��������");
	strcpy(fs1[2],"ʹ����");
	strcpy(fs1[3],"�þ�ȫ��ʹ����");
	strcpy(fs1[4],"��Ц��ʹ����");
	strcpy(fs1[5],"������ʹ����");
	strcpy(fs1[6],"ʹ����");
	strcpy(fs1[7],"����");
	strcpy(fs1[8],"���������");
	strcpy(fs2[0][0],"����ȭ");
	strcpy(fs2[0][1],"&��ͬ����һ����������");
	fp[0][1]=800;
	strcpy(fs2[0][2],"&���ɵĶ㿪��");
	fp[0][2]=0;
	strcpy(fs2[1][0],"��ײ");
	strcpy(fs2[1][1],"&��������");
	fp[1][1]=600;
	strcpy(fs2[1][2],"&���ǵĶ㿪��");
	fp[1][2]=0;
	strcpy(fs2[2][0],"��������ȭ");
	strcpy(fs2[2][1],"&��һȭ���");
	fp[2][1]=2000;
	strcpy(fs2[2][2],"���˾�����ǣ�&��Ȼ�㿪�ˣ����ǻ��ǲ�С�ı�����");
	fp[2][2]=200;
	strcpy(fs2[3][0],"®ɽ������");
	strcpy(fs2[3][1],"&�����ɺ��ڿ����������˹ȫ��");
	fp[3][1]=1700;
	strcpy(fs2[3][2],"����&��С��®ɽ���󣬲�������");
	fp[3][2]=0;
	strcpy(fs2[4][0],"��������");
	strcpy(fs2[4][1],"&��ǯ��ס��");
	fp[4][1]=1000;
	strcpy(fs2[4][2],"��&û�б�ǯ��ס");
	fp[4][2]=0;
	strcpy(fs2[5][0],"��ҩ");
	strcpy(fs2[5][1],"&�����˶�ҩ���ж���");
	fp[5][1]=1200;
	strcpy(fs2[5][2],"����&û�г��¶�ҩ");
	fp[5][2]=0;
	strcpy(fs2[6][0],"��ֻ�������ȭ");
	strcpy(fs2[6][1],"&�������ˣ�ȫ��ȼ���˻���");
	fp[6][1]=1800;
	strcpy(fs2[6][2],"&��Ȼ�㿪�ˣ��������Ż���");
	fp[6][2]=800;
	strcpy(fs2[7][0],"�����");
	strcpy(fs2[7][1],"&���䴩��");
	fp[7][1]=1000;
	strcpy(fs2[7][2],"&���ɵıܿ���");
	fp[7][2]=0;
	strcpy(fs2[8][0],"��ʯ���");
	strcpy(fs2[8][1],"&��������");
	fp[8][1]=1400;
	strcpy(fs2[8][2],"&������ǿ�㿪��");
	fp[8][2]=0;
	strcpy(fs2[9][0],"��������");
	strcpy(fs2[9][1],"&���յ�һ���غ�");
	fp[9][1]=1000;
	strcpy(fs2[9][2],"����&���»�");
	fp[9][2]=0;
	strcpy(fs2[10][0],"���ȱ���");
	strcpy(fs2[10][1],"&�챻������");
	fp[10][1]=2000;
	strcpy(fs2[10][2],"&���񲢲����º���");
	fp[10][2]=0;
	strcpy(fs2[11][0],"�嶥");
	strcpy(fs2[11][1],"&��������");
	fp[11][1]=900;
	strcpy(fs2[11][2],"��ϧ&�㿪��");
	fp[11][2]=0;

}
int getpower(char ta[])
{
	int len=strlen(ta);int ret=0;
	if(strcmp(ta,"����Խ")==0)return 100000;
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
void getchance(int p1,int p2)//�������ݱ��뱣֤p1<p2 
{
	double chance=(double)p1/(double)p2;
	ch[0]=chance*10000;
	ch[1]=10000-ch[0];
	ch[1]+=3500;
	if(ch[0]<=4000)ch[0]+=1000;
}
void nmaker(char nm[],int sed[])//������Ϊseed �õ������ 
{
	int len=strlen(nm);
	unsigned int ts=0;
	for(int i=0;i<len;i++)ts+=nm[i]*('f'+91);
	srand(ts);
	for(int i=0;i<=2000;i++)sed[i]=rand()%10086;//ǰ1000�������� ��1000�������� 
}
void mix()
{
	for(int i=0;i<2000;i++)
	swap(rs[0][randseed[i]%2000],rs[1][randseed[i-1]%2000]);
} 
void go(int i,int t,int mv,int fi)
{
	int hpp=fp[fi][t];
	if(hpp!=0)//����û���� 
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
		for(int i=0;i<=1&&(hp[0]>0&&hp[1]>0);i++)//i �ƶ� 
		{
			int now=(randseed[sscnt]*(power[i]%99+1))%10000+1;		
			int t=(now<=ch[i])?1:2;//1Ϊ������	
			int mv=(rs[i][sscnt-1000]*(power[i]%50+1))%c1;//�������;
			int fi=(rs[i][sscnt]*(power[(i+1)%2]%30+1)+rs[(i+1)%2][mv])%c2;//���ܱ��;
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
		p+="�ܵ�";
		string hpp="";
		int2str(pro[i].hp,hpp);
		p+=hpp;
		p+="���˺���"; 	
		if(i==pcnt-1)
		{
			if(pro[i].id==0)p+=s2;
			else p+=s1;
			p+="��KO����Ϸ������";
		}
		strcpy_s(opt[i],p.c_str());

	}
} 

void error(int x)
{
	switch(x)
	{
	case 1:
		MessageBox(NULL,L"�������� �������001",L"error",MB_ICONERROR);return;
	case 2:
		MessageBox(NULL,L"���ֱ������ĸ������ڣ�",L"error2",MB_ICONERROR);return;
	case 3:
		MessageBox(NULL,L"���������������֣�",L"error3",MB_ICONERROR);return;
	case 4:
		MessageBox(NULL,L"����̫�̣�",L"error4",MB_ICONERROR);return;
	case 5:
		MessageBox(NULL,L"����ֻ�ܺ�����Ӣ�ģ�",L"error5",MB_ICONERROR);return;
	case 6:
		MessageBox(NULL,L"�öԻ����Ѿ��򿪣�",L"error6",MB_ICONERROR);return;
	case 7:
		MessageBox(NULL,L"�������� �������007",L"error",MB_ICONERROR);return;
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
	temp+=s1;temp+="ս����:";int2str(power[0],t2);temp+=t2;temp+="  ";t2="";
	temp+="Ѫ��:",int2str(hp[0],t2);temp+=t2;temp+='#';t2="";
	temp+=s2;temp+="ս����:";int2str(power[1],t2);temp+=t2;temp+="  ";t2="";
	temp+="Ѫ��:",int2str(hp[1],t2);temp+=t2;temp+='#';
	temp+="Ready?";temp+='#';temp+="Fight!";temp+='#';
	getfight();
	outpt(s1,s2);
	for(int i=0;i<pcnt;i++)temp+=opt[i],temp+='#';
	strcpy(output,temp.c_str());
}