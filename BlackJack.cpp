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
};
typedef struct scores sc;

sc player, dealer;

void addCardPlayer()
{
    srand(time(0));
    if(player.size<=5)
    {
        player.hand[player.size] = 1 + (rand()%11);
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
    if(dealer.size<=5)
    {
        dealer.hand[dealer.size] = 1 + (rand()%11);
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
    int i, j;
    player.sum = 0;
    dealer.sum =0;
    for(i=0; i<player.size; i++)
        player.sum+= player.hand[i];
    for(j=0; j<dealer.size; j++)
        dealer.sum+= dealer.hand[j];
    cout<<"Player Score is: "<<player.sum<<endl;
    cout<<"Dealer Score is: "<<dealer.sum<<endl;
}

void printCards()
{
    int i;
    cout<<"Player Cards are\n";
    for(i=0; i<player.size; i++)
        cout<<player.hand[i]<<" - ";
    cout<<endl;
    cout<<"Dealer Cards are\n";
    for(i=0; i<dealer.size; i++)
        cout<<dealer.hand[i]<<" - ";
    cout<<endl;
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

void checkWin()
{
    if(player.sum == 21 && dealer.sum == 21)
    {
        cout<<"Tie\n";
        return;
    }
    if(checkBlackJack())
        return;
    if((player.done == true && dealer.done ==true ) || (player.size==5 && dealer.size == 5))
    {
        if(player.sum>dealer.sum)
        {
            cout<<"Player Wins\n";
            return;
        }
        else if(player.sum<dealer.sum)
        {
            cout<<"Dealer Wins\n";
            return;
        }
        else
        {
            cout<<"Tie\n";
            return;
        }
    }
}

void playGame()
{
    char hit, stand;
    addCardPlayer();
    addCardPlayer();
    addCardDealer();
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
                if(dealer.sum>=17)
                    dealer.done = true;
                checkWin();
                    //return;
            }
        }
}
int main()
{
    playGame();
}





