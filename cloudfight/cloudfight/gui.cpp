#include"stdafx.h"
#include"work.h"
#include"resource.h"
HWND hid;
bool AbtOpen=0,HelpOpen=0;

void OpenUrl(LPCWSTR url)
{
	HINSTANCE result=ShellExecute(NULL, L"open", url, NULL, NULL, SW_SHOW);
	if((int)result<=HINSTANCE_ERROR)
		result=ShellExecute(NULL, NULL, L"iexplore.exe", url, NULL, SW_SHOW);
}
void StrChangeToNum(int num,char str[])
{
	int cnt=0;
	while(num)
	{
		str[cnt]=num%10+'0';
		cnt++;num/=10;
	}
	reverse(str,str+cnt);
	str[cnt+1]='\0';
}
int Inc(char *str)
{
	char c;
	while(1)
	{
		c=*str++;
		if(c>='A'&&c<='z')continue;
		if(*str>='A'&&*str<='z')continue;
		if(*str=='\0')break;
		if(c==0)break;
		if(c&0x80)if(*str&0x80)continue;
		return 0;
	}
	return 1;
}
int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdline,
	_In_ int nCmdshow);
LRESULT CALLBACK WinProc(
	_In_ HWND hwnd,
	_In_ UINT message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam);
int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdline,
	_In_ int nCmdshow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style=CS_HREDRAW|CS_VREDRAW;
	wndclass.lpfnWndProc=WinProc;
	wndclass.cbClsExtra=NULL;
	wndclass.cbWndExtra=NULL;
	wndclass.hInstance=hInstance;
	wndclass.hbrBackground=CreateSolidBrush(RGB(211,211,211));
	wndclass.hIcon=LoadIcon(hInstance,IDI_APPLICATION);
	wndclass.hCursor=LoadCursor(hInstance, IDC_ARROW);
	wndclass.lpszMenuName=NULL;
	wndclass.lpszClassName=L"cloudfight";
	if(!RegisterClass(&wndclass))
	{error(1);return 0;}
	hwnd=CreateWindow(L"cloudfight",
		L"云打架",
		WS_DLGFRAME|WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		900,500,
		NULL,
		LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1)),
		hInstance,NULL);
	ShowWindow(hwnd,nCmdshow);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
void inline makeout(HWND hwnd,char ss[])
{
	int len=strlen(ss),lst=0;
	for(int i=0;i<len;i++)
	{
		if(ss[i]=='#')
		{
			Sleep(1000);
			char output[500];memset(output,0,sizeof output);
			WCHAR Buf[500];memset(Buf,0,sizeof Buf);
			for(int j=lst,k=0;j<i;j++,k++)output[k]=ss[j];
			strcat_s(output,"\r\n");
			MultiByteToWideChar(CP_ACP,0,output,strlen(output)+1,Buf,  
				sizeof(Buf)/sizeof(Buf[0])); 
			SendMessage(hwnd,EM_SETSEL,-1,-1);
			SendMessage(hwnd,EM_REPLACESEL,0,(LPARAM)Buf);
			SendMessage(hwnd,WM_VSCROLL,SB_BOTTOM,0);
			lst=i+1;
		}
	}
}
HFONT hFont;
static HWND hwndTemp,hwndEditA,hwndEditB,hwndBtn,hwndOut;
char otput[8000];
DWORD CALLBACK Paint(LPVOID lpParam)
{
	EnableWindow(hwndBtn,0);
	EnableWindow(hwndEditA,0);
	EnableWindow(hwndEditB,0);
	int len=strlen(otput),lst=0;
	for(int i=0;i<len;i++)
	{
		if(otput[i]=='#')
		{
			Sleep(1000);
			char output[500];memset(output,0,sizeof output);
			WCHAR Buf[500];memset(Buf,0,sizeof Buf);
			for(int j=lst,k=0;j<i;j++,k++)output[k]=otput[j];
			strcat_s(output,"\r\n");
			MultiByteToWideChar(CP_ACP,0,output,strlen(output)+1,Buf,  
				sizeof(Buf)/sizeof(Buf[0])); 
			SendMessage(hwndOut,EM_SETSEL,-2,-1);
			SendMessage(hwndOut,EM_REPLACESEL,0,(LPARAM)Buf);
			SendMessage(hwndOut,WM_VSCROLL,SB_BOTTOM,0);
			lst=i+1;
		}
	}
	EnableWindow(hwndBtn,1);
	EnableWindow(hwndEditA,1);
	EnableWindow(hwndEditB,1);
	return 0;
}
INT_PTR CALLBACK AbtProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)  
{
	switch(msg)
	{
	case WM_SYSCOMMAND:
		if(wParam==SC_CLOSE)
		{
			AbtOpen=0;
			DestroyWindow(hdlg);
		}
		break;
	case WM_COMMAND:
	{
		if(LOWORD(wParam)==IDC_URL)OpenUrl(L"https://icebound.win/");
		break;
	}
	}
	return (INT_PTR)FALSE; 
}
LRESULT CALLBACK WinProc(
	_In_ HWND hwnd,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	HINSTANCE clf=(HINSTANCE)GetWindowLongPtr(hwnd,GWLP_HINSTANCE); 
	switch(msg)
	{
	case WM_CREATE:
	{
		LOGFONT fontRect;
		memset(&fontRect,0,sizeof fontRect);
		fontRect.lfHeight=25;
		fontRect.lfWeight=400;
		//fontRect.lfQuality=PROOF_QUALITY;
		lstrcpy(fontRect.lfFaceName,L"黑体");
		hFont=CreateFontIndirect(&fontRect);
		hwndTemp=CreateWindow(L"STATIC",L"输入姓名A",WS_CHILD|WS_VISIBLE|SS_SIMPLE,
		40,80,200,200,hwnd,NULL,clf,NULL);
		SendMessage(hwndTemp,WM_SETFONT,(WPARAM)hFont,(LPARAM)true);
		hwndTemp=CreateWindow(L"STATIC",L"输入姓名B",WS_CHILD|WS_VISIBLE|SS_SIMPLE,
		40,160,200,200,hwnd,NULL,clf,NULL);
		SendMessage(hwndTemp,WM_SETFONT,(WPARAM)hFont,(LPARAM)true);
		hwndEditA=CreateWindow(L"EDIT",L"",WS_CHILD|WS_VISIBLE|WS_BORDER,
		160,78,200,30,hwnd,NULL,clf,NULL);
		SendMessage(hwndEditA,WM_SETFONT,(WPARAM)hFont,(LPARAM)true);
		hwndEditB=CreateWindow(L"EDIT",L"",WS_CHILD|WS_VISIBLE|WS_BORDER,
		160,158,200,30,hwnd,NULL,clf,NULL);
		SendMessage(hwndEditB,WM_SETFONT,(WPARAM)hFont,(LPARAM)true);
		hwndBtn=CreateWindow(L"BUTTON",L" FIGHT ",WS_CHILD|WS_VISIBLE,
		160,250,120,120,hwnd,NULL,clf,NULL);
		SendMessage(hwndBtn,WM_SETFONT,(WPARAM)hFont,(LPARAM)true);
		hwndOut=CreateWindow(L"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_VSCROLL| 
			WS_BORDER|ES_LEFT|ES_MULTILINE|ES_NOHIDESEL|ES_AUTOVSCROLL,
		440,20,420,400,hwnd,NULL,clf,NULL);
		fontRect.lfHeight=18;hFont=CreateFontIndirect(&fontRect);
		SendMessage(hwndOut,WM_SETFONT,(WPARAM)hFont,(LPARAM)true);
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		SetBkMode((HDC)wParam,TRANSPARENT);
		break;
	}
	case WM_COMMAND:
	{
		if(((HWND)lParam==hwndBtn)&&HIWORD(wParam)==BN_CLICKED)
		{
			char BufA[450],BufB[450],temp[450];
			WCHAR Buf1[405],Buf2[405];
			SetWindowText(hwndOut,L"");
			memset(BufA,0,sizeof BufA);
			memset(BufB,0,sizeof BufB);
			memset(temp,0,sizeof temp);
			memset(otput,0,sizeof otput);
			memset(Buf1,0,sizeof Buf1);
			memset(Buf2,0,sizeof Buf2);
			if(GetWindowText(hwndEditA,(LPWSTR)BufA,40)>0&&GetWindowText(hwndEditB,(LPWSTR)BufB,40)>0)
			{
				int lenA=strlen(BufA),lenB=strlen(BufB);
				if((lenA>8)||(lenB>8)){error(2);break;}
			//	if((lenA<2)||(lenB<2)){error(4);break;}
				int xx=GetWindowText(hwndEditA,Buf1,40);GetWindowText(hwndEditB,Buf2,40);
				int sz=WideCharToMultiByte(CP_ACP,0,Buf1,-1,NULL,0,NULL,NULL);
				WideCharToMultiByte(CP_ACP,0,Buf1,-1,BufA,sz,NULL,NULL);
				sz=WideCharToMultiByte(CP_ACP,0,Buf2,-1,NULL,0,NULL,NULL);
				WideCharToMultiByte(CP_ACP,0,Buf2,-1,BufB,sz,NULL,NULL);
				if((!Inc(BufA))||(!Inc(BufB))){error(5);break;}
				int t=0;
				calc(BufA,BufB,otput);
				DWORD tid=0;
				HANDLE pThread=CreateThread(NULL,NULL,Paint,NULL,0,&tid);
				CloseHandle(pThread);
			}
			else error(3);
		}
		else
		{
			switch(wParam)
			{
				case IDM_ABOUT:
				{
					if(AbtOpen==1){error(6);break;}
					AbtOpen=1;
					hid=CreateDialog(clf,MAKEINTRESOURCE(IDD_ABOUT),hwnd,(DLGPROC)AbtProc);
					if(hid)ShowWindow(hid,SW_NORMAL);
					else 
					{
						error(7);
						AbtOpen=0;
						break;
					}
					break;
				}
				case IDM_SETTING:
				{
					MessageBox(NULL,L"该功能正在制作中，详情请访问icebound.win",L"设置",MB_OK);
					break;
				}
				case IDM_HELP:
				{
					MessageBox(NULL,L"向两个编辑框中分别输入两个名字，再点击FIGHT，即可享受云打架的乐趣！",
						L"帮助",MB_OK);
					break;
				}
			}
		}
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}