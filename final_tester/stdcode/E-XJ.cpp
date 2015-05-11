#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Maxn=50100;
const int Maxlen=1100000;

struct Tree
{
	int lch,rch,p,size,v,plus_v,plus,L,num,d,Max;
};

Tree tree[Maxlen];
int v[Maxn];
int pos[Maxn];
int son[Maxlen][5];
int list[Maxlen];
int n,m,tot,root,Test;
char st[Maxlen],op[5];

void Update(int x)//更新点的size和Max
{
	tree[0].Max=0;
	tree[x].size=tree[tree[x].lch].size+tree[tree[x].rch].size+1;
	tree[x].Max=max(tree[x].d,max(tree[tree[x].lch].Max,tree[tree[x].rch].Max));
}

void Down(int x)//下传标记
{
	int l=tree[x].lch,r=tree[x].rch;
	if (tree[x].plus_v!=0)
	{
		int y=tree[x].plus_v;
		tree[l].Max+=y;tree[l].d+=y;tree[l].plus_v+=y;
		tree[r].Max+=y;tree[r].d+=y;tree[r].plus_v+=y;
		tree[x].plus_v=0;
	}
	if (tree[x].plus!=0)
	{
		int y=tree[x].plus;
		tree[l].L+=y;tree[l].plus+=y;
		tree[r].L+=y;tree[r].plus+=y;
		tree[x].plus=0;
	}
}

void Zig(int x)
{
	int y=tree[x].p,z=tree[y].p;
	if (tree[z].lch==y) tree[z].lch=x;
	else tree[z].rch=x;
	tree[x].p=z;
	int r=tree[x].rch;
	tree[y].lch=r;tree[r].p=y;
	tree[x].rch=y;tree[y].p=x;
	Update(y);
}

void Zag(int x)
{
	int y=tree[x].p,z=tree[y].p;
	if (tree[z].lch==y) tree[z].lch=x;
	else tree[z].rch=x;
	tree[x].p=z;
	int l=tree[x].lch;
	tree[y].rch=l;tree[l].p=y;
	tree[x].lch=y;tree[y].p=x;
	Update(y);
}

void Splay(int x)
{
	int now=x;
	int total=0;
	for (;now;now=tree[now].p) list[++total]=now;
	for (int i=total;i>0;--i)
		if (tree[list[i]].plus_v!=0 || tree[list[i]].plus!=0) Down(list[i]);
	for (;tree[x].p;)
	{
		int y=tree[x].p,z=tree[y].p;
		if (!z) if (tree[y].lch==x) Zig(x);
				else Zag(x);
		else if (tree[z].lch==y) if (tree[y].lch==x) Zig(y),Zig(x);
								 else Zag(x),Zig(x);
			 else if (tree[y].rch==x) Zag(y),Zag(x);
				  else Zig(x),Zag(x);
	}
	Update(x);
	root=x;
}

void Find_kth(int x)//找到第x个元素并旋为根
{
	int now=root;
	for (;now;)
	{
		int z=tree[tree[now].lch].size;
		if (z+1==x) 
		{
			Splay(now);
			return;
		}
		if (z<x)
		{
			x-=z+1;
			now=tree[now].rch;
		}
		else now=tree[now].lch;
	}
}

void Insert(int x,int y)//在平衡树中的第y位插入点x
{
	--y;
	int now=root;
	int p,type;
	for (;now;)
	{
		++tree[now].size;
		p=now;
		if (tree[tree[now].lch].size+1<=y) 
		{ 
			y-=tree[tree[now].lch].size+1;
			now=tree[now].rch;
			type=1;
		}
		else { type=0;now=tree[now].lch; }
	}
	tree[x].p=p;
	if (!type) tree[p].lch=x;
	else tree[p].rch=x;
	Splay(x);
}

void Change_v(int x,int y)
{
	if (y<0) y=0;
	if (v[x]==y) return;
	int delt=y-v[x];
	tree[pos[x]].v+=delt;
	v[x]=y;
	Splay(pos[x]);
	int s=tree[root].L,num=tree[root].num;
	
	Find_kth(s);
	int L=tree[root].lch;
	tree[root].lch=tree[L].p=0;
	Update(root);
	
	Find_kth(num);
	int R=tree[root].rch;
	tree[root].rch=tree[R].p=0;
	Update(root);
	
	tree[root].plus_v+=delt;tree[root].Max+=delt;tree[root].d+=delt;
	Down(root);
	tree[root].rch=R;tree[R].p=root;
	Update(root);
	Find_kth(1);
	tree[root].lch=L;tree[L].p=root;
	Update(root);
}
	
void Insert_tree(char st[],int x)//在字母树中加入st
{
	int len=strlen(st);
	int now=1;
	bool flag=false;
	int z=0;
	int res=0;
	for (int i=0;i<len;++i)
	{
		res+=tree[now].v;
		int xx=st[i]-'a';
		if (!son[now][xx]) 
		{
			flag=true;
			Splay(now);
			int cnt=tree[now].L+tree[now].num-1;
			int Now=now;
			z=len-i;
			int Z=0;
			for (int j=i;j<len;++j)
			{
				int yy=st[j]-'a';
				son[Now][yy]=++tot;
				++cnt;
				Insert(tot,cnt);
				tree[tot].L=cnt;tree[tot].num=z-Z;tree[tot].size=1;
				tree[tot].d=res;
				Update(tot);
				Now=tot;
				++Z;
			}
			pos[x]=Now;
			break;
		}
		now=son[now][xx];
	}
	if (!flag) pos[x]=now;
	int Now=1;
	for (int i=0;i<len;++i)
	{
		tree[Now].num+=z;
		if (Now==now) break;
		Now=son[Now][st[i]-'a'];
	}
	if (z)
	{
		Splay(tot);
		if (tree[tot].rch) 
		{
			int R=tree[tot].rch;
			tree[R].plus+=z;
			tree[R].L+=z;
		}
	}
}

void Init()
{
	memset(tree,0,sizeof(tree));
	memset(son,0,sizeof(son));
	memset(v,0,sizeof(v));
	root=tot=1;
	tree[1].L=tree[1].num=1;
	Test = 2;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
	{
		scanf("%s",st);
		Insert_tree(st,i);
	}
	for (int i=1;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		Change_v(i,x);
	}
}

void Work()
{
	int last_ans=0;
	for (int i=0;i<m;++i)
	{
		int x,y;
		scanf("%s",op);
		if (op[0]=='Q') printf("%d\n",last_ans=tree[root].Max);
		if (op[0]=='C')
			if (op[1]=='v')
			{
				scanf("%d%d",&x,&y);
				Change_v(x,y);
			}
			else
			{
				scanf("%d%s",&x,st);
				if (Test==2)
				{
					int Len=strlen(st);
					int delt=last_ans % 5;
					for (int j=0;j<Len;++j)
					{
						int t=st[j]-'a'+delt;
						if (t>=5) t-=5;
						st[j]='a'+t;
					}
				}
				Splay(pos[x]);
				int tmp=v[x];
				Change_v(x,0);
				Insert_tree(st,x);
				Change_v(x,tmp);
			}
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--) {
	Init();
	
	Work();
	}
	return 0;
}