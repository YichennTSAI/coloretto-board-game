#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<iomanip>

using namespace std;
void output(int *data,int n,int m,int choose[],int start);
void outputtable(char *data,int choose[],int whether[]);
void swap(char &a,char &b);
void swapint(int &a,int &b);
void washcard(int a, char ran[]);
void putin(int *data, int n, char t, int ct);

int main() {
    srand(time(NULL));
    char t;
    bool right;
    int choose[4]={0};
    int n, num, ct;             // the number of player/card/cardtype
    int i, j, k, l;             // used for for()
    char cardtype[9][15] = {"0+2*10", "1W*3", "2R*9", "3G*9", "4B*9", "5C*9", "6M*9", "7Y*9", "8K*9"};
    // all card type
    
    n=4;
    ct = 9;
    num = 76;					// initialize people and the number of card
        
    int playerdata[5][9] = {0}; // record everyone's cardtype and number

    char deck[] = "2222222222RRRRRRRRRGGGGGGGGGBBBBBBBBBCCCCCCCCCMMMMMMMMMYYYYYYYYYKKKKKKKKKWWW";
    //the deck
    washcard(num, deck);
    cout<<"deck:\n";
    for (i=0;i<num;i++)
        cout << deck[i] << " ";
    cout << endl;
    
	char ini[6];
	i=0;
	
	
    while (i < 4)
    {
        right = true;

        while (deck[i] == 'W')
        {
            swap(deck[rand()%(num - 4) + 4], deck[i]);
        }

        ini[i] = deck[i];

        for (j = 0; j < i; j++)
        {
            if (ini[i] == ini[j])
            {
                swap(deck[i], deck[rand() % (num - 4) + 4]);
                right = false;
                break;
            }
        }

        if (right)
        {
            putin(&playerdata[0][0], i, deck[i], ct);
            i++;
        }
    }						//the initial card
    
    
	cout<<"the deck after drawing the initial card:\n";
	for (i=4;i<num;i++)
        cout << deck[i] << " ";
    cout << endl;
    
	int chosen[4]={0};
	char table[4][4];
	int count[4]={0};
	bool exit=false,notdraw=false;
	int turn=1,move1,move2,start=rand()%4;


    
								//start the game

	cout<<"you are p0,start from p"<<start<<",you are "<<(4-start)%4+1;
	if((4-start)%4+1==1)
	cout<<"st\n";
	else if((4-start)%4+1==2)
	cout<<"nd\n";
	else if((4-start)%4+1==3)
	cout<<"rd\n";
	else
	cout<<"th\n";
	i=4;
	cout<<"Begin the game\n";
	cout<<"turn "<<turn<<endl;
	while(true)
	{
		if(start==0&&chosen[0]==1)
		;
		if(start==0&&chosen[0]==0)
		{
			cout<<" It's your turn.\n";
			cout<<"Player's hands:\n";
			cout<<"-----------------------------------------------\n";
			output(&playerdata[0][0],4,ct,chosen,start);
			cout<<"-----------------------------------------------\n";
			cout<<"Row:\n";
			cout<<"-----------------------------------------------\n";
			outputtable(&table[0][0],choose,count);
			cout<<"-----------------------------------------------\n";
			cout<<" "<<num-i<<" cards left in the draw pile\n";
			if(num-i<14)
			{
				cout<<"\n!! it's final round!!\n";
				exit=true;
			}
			cout<<"===============================================\n";
			cout<<"Please enter the corresponding to have your choices executed.\n";
			cout<<"-----------------------------------------------\n";
			for(j=0;j<4;j++)
			{
				notdraw=true;
				if((choose[j]==0&&count[j]==3)||(choose[j]==1))		//detect whether you can draw the next card
				;
				else
				{
					cout<<"0)Draw a card from the draw pile.\n";
					notdraw=false;
					break;	
				}
			}
			
			for(j=1;j<=4;j++)
			{
				if(choose[j-1]==0&&count[j-1]!=0)
				cout<<j<<")Take everything in Row"<<j<<endl;
			}
			cout<<"your choose:";
			while(cin>>move1)
			{
				if(move1==0&&notdraw==true)
				cout<<"Invalid input, please try again:";
				else if(move1==0)
				{
					cout<<"the card is "<<deck[i]<<", Where do you want to put it:\n";
					for(j=1;j<=4;j++)
					{
						if(choose[j-1]==0)
						cout<<j<<") Row "<<j<<endl;
					}
					while(cin>>move2)
					{
						move2-=1;
						if(count[move2]==3||choose[move2]==1||move2<0||move2>3)	//detect the range
							cout<<"Invalid input, please try again:";
						else
						{
							table[move2][count[move2]]=deck[i];
							count[move2]++;
							i++;
							break;
						}														//put the card
					}
					break;
				}
				else if(move1>=1&&move1<=4)
				{
					
					if(choose[move1-1]==1)
						cout<<"Invalid input, please try again:";
					else if(count[move1-1]==0)
						cout<<"Invalid input, please try again:";
					else
					{
						choose[move1-1]=1;
						for(j=0;j<count[move1-1];j++)
						putin(&playerdata[0][0], start, table[move1-1][j], ct);
						count[move1-1]=0;
						chosen[0]=1;
						break;
						
					}															//take the row
				}
				else
				cout<<"Invalid input, please try again:";
				
			}
			outputtable(&table[0][0],choose,count);
			cout<<"\n";
			output(&playerdata[0][0],4,ct,chosen,start);
			cout<<"\n\n";
			cout<<"\n\n";
		}
		if(start!=0)															//AI motion
		{
		
			if(chosen[start]==1)
			;
			else
			{
			cout<<"it's AI-p"<<start<<" turn\n";
			for(j=0;j<4;j++)
			{
				if(count[j]>=2&&choose[j]==0)
				{
				cout<<"choose to take row"<<j+1<<"\n";
				chosen[start]=1;
				choose[j]=1;
				for(k=0;k<count[j];k++)
				putin(&playerdata[0][0], start, table[j][k], ct);
				
				output(&playerdata[0][0],4,ct,chosen,start);
				cout<<"\n";
				outputtable(&table[0][0],choose,count);
				cout<<"\n\n";
				break;
				}				
			}
			if(chosen[start]==1)
			;
			else
			{
			cout<<"the card is "<<deck[i]<<endl;
			cout<<" "<<num-i<<" cards left in the draw pile\n";
			if(num-i<14)
			{
				cout<<"\n!! it's final round!!\n";
				exit=true;
			}
			
				while(true)
				{
					k=rand()%4;
					if(count[k]==3||choose[k]==1)
					;
					else
					{
						table[k][count[k]]=deck[i];
						cout<<"choose to draw and put card on row"<<k+1<<"\n\n";
						i++;
						count[k]++;
						output(&playerdata[0][0],4,ct,chosen,start);
						cout<<"\n";
						outputtable(&table[0][0],choose,count);
						cout<<"\n\n";
						
						break;
					}
				}
			}
			}
			cout<<"\n\n";
		}
		if(chosen[0]+chosen[1]+chosen[2]+chosen[3]==4)						//prepare next round
		{
			cout<<"this round is over\n\n";
			if(exit==true)													//detect whether to end the game
			{
				if(start!=0)
				cout<<"the game has reach an end by AI-p"<<start<<endl;
				
				cout<<"GAME OVER, let's show your score\n";
				break;
			}
			
			for(j=0;j<4;j++)
			{
				notdraw=false;
				choose[j]=0;
				chosen[j]=0;
				count[j]=0;
				for(k=0;k<4;k++)
				{
					table[j][k]=' ';
				}
			}		
			turn++;
			cout<<"turn "<<turn<<endl;
			cout<<"New Round Begins\n\n";
		}
		else
		start=(start+1)%4;
	}
																			//start to add score
		int sum[4]={0};
		int rank[4]={0,1,2,3};
		const int score[]={0,1,3,6,10,15,21};
		int max=-1;
		for(i=0;i<4;i++)
		sum[i]+=playerdata[i][0]*2;											//plus the +2 card
		for(i=0;i<4;i++)
		{
			for(j=9;j>2;j--)
			{
				for(k=2;k<j-1;k++)
				{
					if(playerdata[i][k+1]>playerdata[i][k])
					swapint(playerdata[i][k+1],playerdata[i][k]);
				}
			}
		}		
																	//bubble sort
		for(i=0;i<4;i++)
		{
			j=2;
			while(playerdata[i][1]!=0)
			{
				if(playerdata[i][j]>=6)
				j++;
				else
				{
					playerdata[i][j]++;
					playerdata[i][1]--;
				}
			}
		}																	//put the wild card
		for(i=0;i<4;i++)
		{
			for(j=2;j<5;j++)
			sum[i]+=score[playerdata[i][j]];
			for(j=5;j<9;j++)
			sum[i]-=score[playerdata[i][j]];
		}																	
		for(i=3;i>=0;i--)
		{
			for(j=0;j<i;j++)
			{
				if(sum[i]>sum[j])
				{
					swapint(sum[i],sum[j]);
					swapint(rank[i],rank[j]);
				}
			}
		}																	//determine the rank
		cout<<"rank   player  score\n";
		for(i=0;i<4;i++)
		{
			if(i+1==1)
			cout<<i+1<<"st    ";
			else if(i+1==2)
			cout<<i+1<<"nd    ";
			else if(i+1==3)
			cout<<i+1<<"rd    ";
			else
			cout<<i+1<<"th    ";
			
			cout<<"p"<<rank[i]<<"      "<<sum[i]<<"\n";
		}
		
		cout<<"End game";
    return 0;
}
	
				

void swap(char &a,char &b)
{
	char t;
	t=a;
	a=b;
	b=t;
	
}
void swapint(int &a,int &b)
{
	int t;
	t=a;
	a=b;
	b=t;
	
}
void washcard(int a, char ran[]) {
    int i, j, k;
    char t;
    for (i = 1; i <= 50000; i++) {
        j = rand() % a;
        k = rand() % a;
        if (j == k)
            continue;
        t = ran[j];
        ran[j] = ran[k];
        ran[k] = t;
    }
}																	//change card 50000 times

void putin(int *data, int n, char t, int ct) 
{
    switch (t) {
        case '2':
            data[n*ct + 0] += 1;
            break;
        case 'W':
            data[n*ct + 1] += 1;
            break;
        case 'R':
            data[n*ct + 2] += 1;
            break;
        case 'G':
            data[n*ct + 3] += 1;
            break;
        case 'B':
            data[n*ct + 4] += 1;
            break;
        case 'C':
            data[n*ct + 5] += 1;
            break;
        case 'M':
            data[n*ct + 6] += 1;
            break;
        case 'Y':
            data[n*ct + 7] += 1;
            break;
        case 'K':
            data[n*ct + 8] += 1;
            break;
    }															//put into playerdata
}
void output(int *data,int n,int ct,int choose[],int start)	//output the each player's data
{
	char letter[11] = "2WRGBCMYK";        // the card letter
	int i,j;
	cout<<"\t ";
	for(i=0;i<ct;i++)
    cout<<letter[i]<<" ";
    cout<<endl;
	for(i=0;i<4;i++)
    {
    	if(choose[i]==1)
    	cout<<"x";
    	else if(start==i)
    	cout<<">";
    	else
    	cout<<" ";
    	cout<<"p"<<i<<"      ";
    	for(j=0;j<ct;j++)
    	cout<<data[i*ct+j]<<" ";
    	cout<<endl;
	}
}

	

void outputtable(char *data,int choose[],int whether[])
{
	int i,j;
	for(i=0;i<4;i++)
	{
		cout<<"Row"<<i+1<<":";
		if(choose[i]==1)
			cout<<"----------------\n";
		else
		{
			for(j=0;j<whether[i];j++)
			{
				cout<<data[i*4+j]<<" ";
			}
			cout<<endl;
		}
	}
}