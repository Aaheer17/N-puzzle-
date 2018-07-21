#include <bits/stdc++.h>
using namespace std;
#define N 3


int row[]={0,0,-1,1};
int col[]={-1,1,0,0};

//int goal[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
int goal[3][3]={1,2,3,4,5,6,7,8,0};

bool isValid(int x, int y){
	if(x<0 || y<0 || x>=N || y>=N){
		return false;

	}
	return true;

}

bool isGoal(int chk[N][N]){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(chk[i][j] != goal[i][j])
			{
				return false;
			}
		}
	}
	return true;

}


class state{
public:

	int gScore;
	double hScore;
	double fScore;
	int grid[N][N];
	state* parent;

	state(int g[N][N]){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				grid[i][j]=g[i][j];
			}
		}
	}

};

int Hamming(int g[N][N]){
	int count=0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			
			if(goal[i][j] != g[i][j] && g[i][j]!=0)
			{
				count++;
			}
		}
		
	}
	return count;

}

int Manhattan(int g[N][N]){
	int distance=0;

	for (int i = 0; i < N; i++)
	{
		for(int j=0;j<N;j++){

			if(g[i][j]!=0){

				for(int k=0;k<N;k++){

					for (int l = 0; l < N; l++)
					{
						if(g[i][j]==goal[k][l]){
							distance+= abs(i-k)+abs(j-l);
							break;

						}
						
					}
				}
			}
		}

		
		
	}
	return distance;
}

double Euclidean(int g[N][N]){

	double distance=0;

	for (int i = 0; i < N; i++)
	{
		for(int j=0;j<N;j++){

			if(g[i][j]!=0){

				for(int k=0;k<N;k++){

					for (int l = 0; l < N; l++)
					{
						if(g[i][j]==goal[k][l]){
							int cost=(i-k)*(i-k) + (j-l)*(j-l);
						    double fCost=sqrt(cost);
							distance=distance+fCost;
							break;
						}
						
					}
				}
			}
		}

		
		
	}
	return distance;

}


int OutRowOutCol(int g[N][N]){

	int distance=0;

	for (int i = 0; i < N; i++)
	{
		for(int j=0;j<N;j++){

			if(g[i][j]!=0){

				for(int k=0;k<N;k++){

					for (int l = 0; l < N; l++)
					{
						if(g[i][j]==goal[k][l]){
							if(i != k){
								distance++;
							}
							if(j != l){
								distance++;
							}

							break;
						}
						/* code */
					}
				}
			}
		}

		
		/* code */
	}
	return distance;


}

int nMaxSwap(int g[N][N]){
	int val,distance=0,flag=0;
	int i,j,k,l;

	while(isGoal(g)==false){
		// get 0's location.
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				if(g[i][j]==0)
				{
					flag=1;
					break;
				} 
			}
			if(flag==1) break;
		}
		flag=0;
		

		if(i==(N-1) && j==(N-1)){
			if(isGoal(g)!=true){
				distance++;
				for(int m=0;m<N;m++){
					for (int n=0;n<N;n++)
					{
						if(g[m][n]!=goal[m][n]){
							g[N-1][N-1]=g[m][n];
							g[m][n]=0;
							i=m;
							j=n;
							flag=1;
							break;

						}
						
					}
					if(flag==1) {flag=0;break;}
				}
			}
			else{
				return distance;
			}
		}

		
		val=goal[i][j];
		
		flag=0;
		for(k=0;k<N;k++){
			for(l=0;l<N;l++){
				if(val==g[l][k]){
					g[i][j]=val;
					g[l][k]=0;

					//printGrid(g);
					distance++;
					flag=1;
					break;
				}
			}
			if(flag==1) {flag=0;break;}
		}
	}
	return distance;	
}

// To compare two points
class myComparator
{
public:
    int operator() (const state* s1, const state* s2)
    {
 
      	return s1->fScore > s2->fScore;
    }
};


void print_grid(state* s){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<s->grid[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}


vector<state*> neighbours(state* s){

	int posX,posY;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			
			
			if(s->grid[i][j]==0){
				posX=i;
				posY=j;
				
				break;

			}
			
		}
		
	}

	vector<state*> nList;

	for(int i=0;i<4;i++){
		int x=posX+row[i];
		int y=posY+col[i];

		
		if (isValid(x,y)){
			
			state* temp=new state(s->grid);
			temp->parent=s;
			temp->grid[posX][posY]=s->grid[x][y];
			temp->grid[x][y]=0;
			temp->gScore=s->gScore+1;
			temp->fScore=0;
			temp->hScore=0;

			
			nList.push_back(temp);

		}

		
	}

	/*cout<<"Printing who is neighbour"<<endl;
	vector<state*>::iterator it;
	 	for(it=nList.begin();it!=nList.end();it++){
	 		state* tmp= *it;
	 		print_grid(tmp);
	 	}

	 */
	
	
	return nList;

}


//b^(d+1)-b(n+1)+n=0


double func(double b,int node, int depth)
{
   
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

void path(state* s){
	if(s->parent!=NULL){
		path(s->parent);
	}

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<s->grid[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<endl<<endl;
}


bool isSameState(state* s1, state* s2){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(s1->grid[i][j]!=s2->grid[i][j]){
				return false;
			}
		}
	}
	return true;
}
int sln(state* start,int choice){

	 priority_queue <state*, vector<state*>, myComparator > openList;
	 vector<state*> closedList;
	 openList.push(start);
	 int nodeCntr=0,depth=0;
	 int a,foundGoal=0;
	 while(openList.empty()==false){
	 	a=0;
	 	state* s=openList.top();

	 	openList.pop();
	 	


	 	if(isGoal(s->grid)){
	 			depth=s->gScore;
	 			cout<<"Depth: "<<depth<<endl<<endl;
		 		cout<<"Printing Path to goal."<<endl;
		 		path(s);
		 		break;
	 	}

	 	vector<state*>::iterator closedit1;
		for(closedit1=closedList.begin();closedit1!=closedList.end();closedit1++){
		 			
		 		state* ob2= *closedit1;
		 			
		 		if(isSameState(s,ob2)){
		 			a=1;
		 			break;
		 		}
		}
		
		 if(a==1) continue;
		 nodeCntr++;

	 	closedList.push_back(s);

	 	
		vector<state*> ns=neighbours(s);
	 	vector<state*>::iterator it;
	 	for(it=ns.begin();it!=ns.end();it++){
	 		state* tmp= *it;

	 		if(choice==0){tmp->hScore=Hamming(tmp->grid);}

	 		else if(choice==1){tmp->hScore=Manhattan(tmp->grid);}

	 		else if(choice==2){tmp->hScore=Euclidean(tmp->grid);}

	 		else if(choice==3){tmp->hScore=OutRowOutCol(tmp->grid);}

	 		else if(choice==4){
	 			int dummyGrid[N][N];
	 			for(int i=0;i<N;i++){
	 				for(int j=0;j<N;j++){
	 					dummyGrid[i][j]=tmp->grid[i][j];
	 				}
	 			}

	 			tmp->hScore=nMaxSwap(dummyGrid);

	 		}

	 		
	 		tmp->fScore=tmp->gScore+tmp->hScore;
	 		double fVal=tmp->fScore;
	 		int flag=0;

		 	vector<state*>::iterator it1;
		 	for(it1=closedList.begin();it1!=closedList.end();it1++){
		 			
		 		state* ob2= *it1;
		 			
		 		if(isSameState(tmp,ob2)){
		 			
		 			flag=1;
		 			break;
		 		}
		 	}
	 		
	 		if(flag==0){
	 			openList.push(tmp);
	 		}	



	 	}
	 	if(foundGoal==1) break;


	 }

	 cout<<endl<<endl<<"Number of Nodes: "<<nodeCntr<<endl;
	 bisection(0,4,nodeCntr,depth);

	 return 0;


	
}




int main(){
	
	///input initial state

	int initGrid[N][N];

	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j < N; j++)
		{

			cin>>initGrid[i][j];
		}
		cout<<endl;
		
	}


	cout<<endl;
	if(isGoal(initGrid)==false){
		state* start=new state(initGrid);
		start->gScore=0;
		start->hScore=0;
		start->fScore=0;
		start->parent=NULL;

		//sln(start,1);
		//slnManhattan(start);
		/*for(int i=0;i<5;i++)
		{	cout<<"i: "<<i<<endl;
		     sln(start,i);
		     cout<<endl<<endl<<endl;

		}*/
		cout<<"Hamming\n";
		sln(start,0);
		cout<<endl<<endl;
		cout<<"Manhattan\n";
		sln(start,1);
		cout<<endl<<endl;
		cout<<"Euclidean\n";
		sln(start,2);
		cout<<endl<<endl;
		cout<<"Out of row out of column\n";
		sln(start,3);
		cout<<endl<<endl;
		cout<<"N-max swap\n";
		sln(start,4);
		cout<<endl<<endl;

	}


}

