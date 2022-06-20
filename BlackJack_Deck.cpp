#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

string card[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
string suit[] = {"Clubs", "Spades", "Hearts", "Diamond"};
int cards[4][13]; 

class blackjack
{
    int hand[5];
    int size;
    int sum;
    bool done;
    int csuit[5];
    // int cards[4][13];    
    public:
        blackjack()
        {
            done = false;
            size = 0;
            sum = 0;
            // for(int i=0; i<4; i++)
            //     for(int j=0; i<13; j++)
            //         cards[i][j] = 1;
        }
        
        void addCardPlayer();
        void addCardDealer();
        void sumCards(blackjack*);
        void printCards(blackjack*);
        int checkBust(blackjack*);
        int checkBlackJack(blackjack*);
        int checkWin(blackjack*);
        void playGame(blackjack*);
};


void blackjack::addCardPlayer()
{
    
    if(size<5)
    {
        labelplay:
        hand[size] = 1 + (rand()%13);
        csuit[size] = 1 + (rand()%4);
        if(cards[csuit[size]][hand[size]]==1)
        {
            cards[csuit[size]][hand[size]]--;
            size++;
        }
        else goto labelplay;
    }
    else
    {
        cout<<"You have reached the maximum number of cards\n";
        done = true;
    }
}
void blackjack::addCardDealer()
{
    if(size<5)
    {
         labeldeal:
        hand[size] = 1 + (rand()%13);
        csuit[size] = 1 + (rand()%4);
        if(cards[csuit[size]][hand[size]]==1)
        {
            cards[csuit[size]][hand[size]]--;
            size++;
        }
        else goto labeldeal;
    }
    else
    {
        cout<<"You have reached the maximum number of cards\n";
        done = true;
    }
}

void blackjack::sumCards(blackjack* dealer)
{
    int i, j, count=0;
    sum = 0;
    dealer->sum =0;
    for(i=0; i<size; i++)
    {
        if(hand[i]>10)
        {
            sum+=10;
            continue;
        }
        if(hand[i]==1)
        {
            count++;
            continue;
        }
        sum+= hand[i];
    }
    while(count>0)
    {
        if((sum+11)>21)
            sum+=1;
        else
            sum+=11;
        count--;
    }
    count =0;
    for(j=0; j<dealer->size; j++)
    {
        if(dealer->hand[j]>10)
        {
            dealer->sum+=10;
            continue;
        }
        if(dealer->hand[j]==1)
        {
            count++;
            continue;
        }
        dealer->sum+= dealer->hand[j];
    }
    while(count>0)
    {
        if((dealer->sum+11)>21)
            dealer->sum+=1;
        else
            dealer->sum+=11;
        count--;
    }
    cout<<"Player Score is: "<<sum<<endl;
    if(done)
        cout<<"Dealer Score is: "<<dealer->sum<<endl;
}

void blackjack::printCards(blackjack* dealer)
{
    int i;
    cout<<"Player Cards are\n";
    for(i=0; i<size; i++)
        cout<<card[hand[i]-1]<<" of "<<suit[csuit[i]-1]<<" - ";
    cout<<"\b \b"<<"\b \b"<<endl;
    cout<<"Dealer Cards are\n";
    if(!done)
        cout<<card[dealer->hand[0]-1]<<" of "<<suit[dealer->csuit[0]-1]<<endl;
    else
    {
        for(i=0; i<dealer->size; i++)
        cout<<card[dealer->hand[i]-1]<<" of "<<suit[dealer->csuit[i]-1]<<" - ";
        cout<<"\b \b"<<"\b \b"<<endl;
    }
}

int blackjack::checkBust(blackjack* dealer)
{
    if(sum>21)
    {
        cout<<"Player Busted\nDealer Wins\n";
        return 1;
    }
    else if(dealer->sum>21)
    {
        cout<<"Dealer Busted\nPlayer Wins\n";
        return 1;
    }
    else return 0;
}

int blackjack::checkBlackJack(blackjack* dealer)
{
    if(sum==21)
    {
        cout<<"Player BlackJack!! Player Wins\n";
        return 1;
    }
    if(done)
    {
        if(dealer->sum==21)
        {
            cout<<"Dealer BlackJack!! Dealer Wins\n";
            return 1;
        }
    }
    return 0;
}

int blackjack::checkWin(blackjack* dealer)
{
    if(sum == 21 && dealer->sum == 21)
    {
        cout<<"Tie\n";
        return 1;
    }
    if(checkBlackJack(dealer))
        return 1;
    if((done == true && dealer->done ==true ) || (size==4 && dealer->size == 4))
    {
        if(sum>dealer->sum)
        {
            cout<<"Player Wins\n";
            return 1;
        }
        else if(sum<dealer->sum)
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

void blackjack::playGame(blackjack* dealer)
{
    srand(time(0));
    //blackjack player, dealer;
    char hit, stand;
    addCardPlayer();
    dealer->addCardDealer();
    addCardPlayer();
    dealer->addCardDealer();
    printCards(dealer);
    sumCards(dealer);
    // if(checkBust() == 1)
    //     return; //return to main game if busted
    if(checkBlackJack(dealer) == 1)
        return;     //return to main game if blackjack
    while(done == false || dealer->done == false)
    {
        label1:
        if(done == false)
        {
            cout<<"Would You Like To Hit?\nYes(y) or No(n)\n";
            cin>>hit;
            if(hit=='y')
            {
                addCardPlayer();
                printCards(dealer);
                sumCards(dealer);
                if(checkBust(dealer) == 1)
                    return; //return to main game if busted
                if(checkBlackJack(dealer) == 1)
                    return;
                checkWin(dealer);
                goto label1;
            }
            else
            {
                done = true;
                cout<<"player Stands\n";
                printCards(dealer);
                sumCards(dealer);
            }
        }
            if(dealer->sum<17 && dealer->done!= true)
            {
                dealer->addCardDealer();
                printCards(dealer);
                sumCards(dealer);
                if(checkBust(dealer))
                    return;
                //if(dealer->sum>=17)
                    //dealer->done = true;
                if(checkWin(dealer))
                    return;
                    //return;
            }
            // else if(done == true && dealer->sum<sum)
            // {
            //     dealer->addCardDealer();
            //     printCards(dealer);
            //     sumCards(dealer);
            //     if(checkBust(dealer))
            //         return;
            //     if(checkWin(dealer))
            //         return;
            // }
            else
            {
                dealer->done  = true;
                printCards(dealer);
                sumCards(dealer);
                if(checkWin(dealer))
                    return;
            }
    }
}

void initcards()
{
    for(int i=0; i<4; i++)
                for(int j=0; j<13; j++)
                    cards[i][j] = 1;
}

int main()
{
    
    char ch;
    blackjack *player = new(blackjack), *dealer = new(blackjack);
    initcards();
    player->playGame(dealer);
    while(1)
    {
        cout<<"Would You Like To Play Another Game?\nYes(y)/No(n)";
        cin>>ch;
        if(ch == 'y')
        {
            free(player);
            free(dealer);
            blackjack *player = new(blackjack), *dealer = new(blackjack);
            initcards();
            system("clear");
            player->playGame(dealer);
        }
        else 
            return 0;
    }
}







