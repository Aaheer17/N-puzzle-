#include<bits/stdc++.h>
using namespace std;
 
#define ROW 20
#define COL 30
#define MAX 999999


//int ROW,COL;
int dir_x[]={-1,+1,0,0};
int dir_y[]={0,0,1,-1};

typedef pair<int, int> position;


class block{

public:

	int x,y,parent_x,parent_y;

	int g;
	double h,f;

};




bool isValid(int x,int y){
	if(x<0 || x>=ROW || y<0 || y>=COL) return false;
	return true;
}


bool isBlocked(int x, int y,char g[][COL]){
	if(g[x][y]=='1') return true;
	return false;
}

bool isGoal(position dest, int x,int y){
	if(dest.first==x && dest.second==y) return true;
	return false;
}

double Manhattan(position dest,int x, int y){
	return (abs(x-dest.first)+abs(y-dest.second));
}

double Euclidean(position dest,int x,int y){
	return sqrt((x-dest.first)*(x-dest.first) + (y-dest.second)*(y-dest.second));
}

double Max(position dest, int x, int y){
	return max(abs(x-dest.first),abs(y-dest.second));
}


class myComparator
{
public:
    int operator() (const block& b1, const block& b2)
    {
        return b1.f > b2.f;
    }
};



double func(double b,int node, int depth)
{
    //double res=pow(b,depth+1)-b*node+(node-1);
    //return res;
    return (pow(b,depth)-1/(b-1))-(node);
}



void bisection(double a,double b,int node,int depth)
{

	double accuracy=0.01;
	double mid;
   if(func(a,node,depth) * func(b,node,depth) >= 0)
    {
        cout<<"Incorrect a and b";
        return;
    }
 
    mid = a;
 
    while ((b-a) >= accuracy)
    {
        mid = (a+b)/2;
        if (func(mid,node,depth) == 0.0){
          break;
        }
        else if (func(mid,node,depth)*func(a,node,depth) < 0){
                b = mid;
        }
        else{
                a = mid;
        }
    }
    cout<<"Effective Branching Factor: "<<mid<<endl;
}




int aStar(char g[][COL], position src, position dest,int choice){

	block blk[ROW][COL];
	int cost=0;


	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			blk[i][j].g=MAX;
			blk[i][j].h=MAX;
			blk[i][j].f=MAX;
			blk[i][j].parent_x=-1;
			blk[i][j].parent_y=-1;
			blk[i][j].x=i;
			blk[i][j].y=j;
		}
	}



	blk[src.first][src.second].parent_x=src.first;
	blk[src.first][src.second].parent_y=src.second;
	blk[src.first][src.second].x=src.first;
	blk[src.first][src.second].y=src.second;
	blk[src.first][src.second].f=0;
	blk[src.first][src.second].g=0;
	blk[src.first][src.second].h=0;
	

	bool visited[ROW][COL];
	int flag=0,nodeCntr=0;
	memset(visited, false, sizeof (visited));


	priority_queue <block, vector<block>, myComparator > openList;

	openList.push(blk[src.first][src.second]);

	while(openList.empty()==false){
		block b=openList.top();
		openList.pop();

		int pos_x=b.x;
		int pos_y=b.y;
		cost=b.g;



		if(isGoal(dest,pos_x,pos_y)){

			int tmpX,tmpY,a,b;
			tmpX=pos_x;
			tmpY=pos_y;
			stack <position> path;

			while((blk[tmpX][tmpY].parent_x != tmpX && blk[tmpX][tmpY].parent_y!=tmpY) ||
						(blk[tmpX][tmpY].parent_x == tmpX && blk[tmpX][tmpY].parent_y!=tmpY)||
						(blk[tmpX][tmpY].parent_x != tmpX && blk[tmpX][tmpY].parent_y==tmpY))
					{
						//cout<<"in while "<<endl;
						path.push(make_pair(tmpX,tmpY));
						g[tmpX][tmpY]='*';
						a=blk[tmpX][tmpY].parent_x;
						b=blk[tmpX][tmpY].parent_y;
						//cout<<" a: "<<a<<" b: "<<b<<endl;
						tmpX=a;
						tmpY=b;
						
						
					}
					g[tmpX][tmpY]='*';
					path.push(make_pair(tmpX,tmpY));


					cout<<"Path: "<<endl;

					while (!path.empty())
				    {
				        pair<int,int> p = path.top();
				        path.pop();
				        if(path.size()!=0)
				            printf(" (%d,%d) -> ",p.first,p.second);
				         else
				         	printf(" (%d,%d).",p.first,p.second);

					    }
				    cout<<endl;
					//findPath(dest,src,g,blk);
					flag=1;
					break;


		}
		
		
		


		
		if(visited[b.x][b.y]==true) continue;

		visited[b.x][b.y]=true;
		g[pos_x][pos_y]='V';
		nodeCntr++;

		for(int i=0;i<4;i++){
			flag=0;
			int _x=pos_x+dir_x[i];
			int _y=pos_y+dir_y[i];

			//cout<<"_x: "<<_x<<" _y: "<<_y<<endl;
			//cout<<"what is in grid: "<<g[_x][_y]<<endl;

			if(isValid(_x,_y)==true && visited[_x][_y]==false && isBlocked(_x,_y,g)==false ){

				
					int gVal;
					double hVal, fVal;

					gVal=blk[pos_x][pos_y].g+1;   ///vul korsi may be

					if(choice==0) hVal=Manhattan(dest,_x,_y);

					else if(choice==1) hVal=Euclidean(dest,_x,_y);

					else hVal=Max(dest,_x,_y);

					fVal=gVal+hVal;

					//why b here.....
					if(blk[_x][_y].f==MAX || blk[_x][_y].f>fVal){
						blk[_x][_y].f=fVal;
						blk[_x][_y].g=gVal;
						blk[_x][_y].h=hVal;
						//cost=gVal;

						blk[_x][_y].parent_x=pos_x;
					    blk[_x][_y].parent_y=pos_y;

					    openList.push(blk[_x][_y]);



					}
				




			}
		

		}


		/*if(flag==1)
			break;	*/
		
	}

	if(flag!=1) {
		cout<<"No path to reach goal."<<endl;

		g[src.first][src.second]='S';
		g[dest.first][dest.second]='E';

		for(int i=0;i<ROW;i++){
			for(int j=0;j<COL; j++){
				cout<<g[i][j]<<" ";
			}
			cout<<endl;
		}



	}

	if(flag==1){
		cout<<"Printing output"<<endl;
		g[src.first][src.second]='S';
		g[dest.first][dest.second]='E';

		for(int i=0;i<ROW;i++){
			for(int j=0;j<COL; j++){
				cout<<g[i][j]<<" ";
			}
			cout<<endl;
		}
		bisection(0,10,nodeCntr,cost);
	}

	return nodeCntr;







}


void cpyGrid(char grid[][COL],char g[][COL]){

	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			g[i][j]=grid[i][j];
		}
	}
}

int main(){
	int a,b,c,d,freq,obstacles;


	position src,dest;
	cout<<"enter the source: "<<endl;
	cin>>a>>b;

	cout<<"enter the destinatiin: "<<endl;
	cin>>c>>d;

	src=make_pair(a,b);
	dest=make_pair(c,d);
	//int grid[ROW][COL];
	char grid[ROW][COL];
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL; j++){
			
			grid[i][j]='0';
		}
		//cout<<endl;
	}


	cout<<"enter the frequency of obstacles: "<<endl;
	cin>>freq;

	obstacles=((ROW*COL)*freq)/100;

	cout<<"Total number of hurdles"<<obstacles<<endl;
	//grid ta banaite hobe.

	
	for(int n=0; n<obstacles;n++){
		random_device rd;
	    mt19937 eng(rd());
	    uniform_int_distribution<> distr1(0,ROW-1);
	     uniform_int_distribution<> distr2(0,COL-1);

	    int x1=distr1(eng);
	    int y1=distr2(eng);

	    //cout<<"x1: "<<x1<<"y1: "<<y1<<endl;
	    if((x1==a && y1==b) || (x1==c && y1== d))
	    {
	    	n--;
	    	continue;
	    }


	    if( grid[x1][y1] != '1') grid[x1][y1]='1';
	    else{
	    	if(x1 != 0 && grid[x1-1][y1] != '1'){
	    		grid[x1-1][y1]='1';
	    	}
	    	else if(x1!=ROW-1 && grid[x1+1][y1]!='1')
	    		grid[x1+1][y1]='1';
	    	else if(y1!=0 && grid[x1][y1-1]!='1')
	    		grid[x1][y1-1]='1';
	    	else if(y1!=COL-1 && grid[x1][y1+1]!='1')
	    		grid[x1][y1+1]='1';

	    	else n--;
	    }



	}
         //cout<< distr(eng) << ' '; // generate numbers

	

	char grid0[ROW][COL],grid1[ROW][COL],grid2[ROW][COL];

	cout<<"source: "<<src.first<<" "<<src.second<<endl;

	cout<<"destinatiin: "<<dest.first<<" "<<dest.second<<endl;

	if(isValid(src.first,src.second)==false || isValid(dest.first,dest.second)==false){


		cout<<"Either source or destinatiin is invalid"<<endl;
		return 0;
	}

	if(isBlocked(src.first,src.second,grid)==true || isBlocked(dest.first,dest.second,grid)==true){
		cout<<"Either source or destinatiin is blocked."<<endl;
		return 0;
	}

	if(isGoal(dest,src.first,src.second)==true){
		cout<<"source and destination are same"<<endl;
		return 0;
	}
	grid[src.first][src.second]='S';
	grid[dest.first][dest.second]='E';


	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL; j++){

			cout<<grid[i][j]<<" ";
		}
		cout<<endl;
	}

	cpyGrid(grid,grid0);
	cpyGrid(grid,grid1);
	cpyGrid(grid,grid2);

	cout<<"Manhattan: "<<endl;

	int node1=aStar(grid0,src,dest,0);
	cout<<"node: "<<node1<<endl;
	cout<<"Euclidean: "<<endl;
	int node2=aStar(grid1,src,dest,1);
	cout<<"node: "<<node2<<endl;
	cout<<"Max: "<<endl;
	int node3=aStar(grid2,src,dest,2);
	cout<<"node: "<<node3<<endl;


	

	


}