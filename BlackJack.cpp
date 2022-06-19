#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

struct scores
{
    int hand[5];
    int size;
    int sum;
    bool done;
    int csuit[5];
};
typedef struct scores sc;

sc player, dealer;
string card[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
string suit[] = {"Clubs", "Spades", "Hearts", "Diamond"};
void addCardPlayer()
{
    if(player.size<5)
    {
        player.hand[player.size] = 1 + (rand()%13);
        player.csuit[player.size] = 1 + (rand()%4);
        player.size++;
    }
    else
    {
        cout<<"You have reached the maximum number of cards\n";
        player.done = true;
    }
}
void addCardDealer()
{
    if(dealer.size<5)
    {
        dealer.hand[dealer.size] = 1 + (rand()%13);
        dealer.csuit[dealer.size] = 1 + (rand()%4);
        dealer.size++;
    }
    else
    {
        cout<<"You have reached the maximum number of cards\n";
        dealer.done = true;
    }
}

void sumCards()
{
    int i, j, count=0;
    player.sum = 0;
    dealer.sum =0;
    for(i=0; i<player.size; i++)
    {
        if(player.hand[i]>10)
        {
            player.sum+=10;
            continue;
        }
        if(player.hand[i]==1)
        {
            count++;
            continue;
        }
        player.sum+= player.hand[i];
    }
    while(count>0)
    {
        if((player.sum+11)>21)
            player.sum+=1;
        else
            player.sum+=11;
        count--;
    }
    count =0;
    for(j=0; j<dealer.size; j++)
    {
        if(dealer.hand[j]>10)
        {
            dealer.sum+=10;
            continue;
        }
        if(dealer.hand[j]==1)
        {
            count++;
            continue;
        }
        dealer.sum+= dealer.hand[j];
    }
    while(count>0)
    {
        if((dealer.sum+11)>21)
            dealer.sum+=1;
        else
            dealer.sum+=11;
        count--;
    }
    cout<<"Player Score is: "<<player.sum<<endl;
    cout<<"Dealer Score is: "<<dealer.sum<<endl;
}

void printCards()
{
    int i;
    cout<<"Player Cards are\n";
    for(i=0; i<player.size; i++)
        cout<<card[player.hand[i]-1]<<" of "<<suit[player.csuit[i]-1]<<" - ";
    cout<<"\b \b"<<"\b \b"<<endl;
    cout<<"Dealer Cards are\n";
    for(i=0; i<dealer.size; i++)
        cout<<card[dealer.hand[i]-1]<<" of "<<suit[dealer.csuit[i]-1]<<" - ";
    cout<<"\b \b"<<"\b \b"<<endl;
}

int checkBust()
{
    if(player.sum>21)
    {
        cout<<"Player Busted\nDealer Wins\n";
        return 1;
    }
    else if(dealer.sum>21)
    {
        cout<<"Dealer Busted\nPlayer Wins\n";
        return 1;
    }
    else return 0;
}

int checkBlackJack()
{
    if(dealer.sum==21)
    {
        cout<<"Dealer BlackJack!! Dealer Wins\n";
        return 1;
    }
    
    else if(player.sum==21)
    {
        cout<<"Player BlackJack!! Player Wins\n";
        return 1;
    }
    else return 0;
}

int checkWin()
{
    if(player.sum == 21 && dealer.sum == 21)
    {
        cout<<"Tie\n";
        return 1;
    }
    if(checkBlackJack())
        return 1;
    if((player.done == true && dealer.done ==true ) || (player.size==4 && dealer.size == 4))
    {
        if(player.sum>dealer.sum)
        {
            cout<<"Player Wins\n";
            return 1;
        }
        else if(player.sum<dealer.sum)
        {
            cout<<"Dealer Wins\n";
            return 1;
        }
        else
        {
            cout<<"Tie\n";
            return 1;
        }
    }
    return 0;
}

void playGame()
{
    srand(time(0));
    char hit, stand;
    addCardPlayer();
    addCardDealer();
    addCardPlayer();
    addCardDealer();
    printCards();
    sumCards();
    // if(checkBust() == 1)
    //     return; //return to main game if busted
    if(checkBlackJack() == 1)
        return;     //return to main game if blackjack
    while(player.done == false || dealer.done == false)
    {
        label1:
        if(player.done == false)
        {
            cout<<"Would You Like To Hit?\nYes(y) or No(n)\n";
            cin>>hit;
            if(hit=='y')
            {
                addCardPlayer();
                printCards();
                sumCards();
                if(checkBust() == 1)
                    return; //return to main game if busted
                if(checkBlackJack() == 1)
                    return;
                checkWin();
                goto label1;
            }
            else
            {
                player.done = true;
                cout<<"player Stands\n";
            }
        }
            if(dealer.sum<17 && dealer.done!= true)
            {
                addCardDealer();
                printCards();
                sumCards();
                if(checkBust())
                    return;
                //if(dealer.sum>=17)
                    //dealer.done = true;
                if(checkWin())
                    return;
                    //return;
            }
            else if(player.done == true && dealer.sum<player.sum)
            {
                addCardDealer();
                printCards();
                sumCards();
                if(checkBust())
                    return;
                if(checkWin())
                    return;
            }
            else
            {
                dealer.done  = true;
                if(checkWin())
                    return;
            }
    }
}
int main()
{
    char ch;
    playGame();
    // while(1)
    // {
    //     cout<<"Would You Like To Play Another Game?\nYes(y)/No(n)";
    //     cin>>ch;
    //     if(ch == 'y')
    //     {
    //         system("clear");
    //         playGame();
    //     }
    //     else 
    //         return 0;
    // }
}
