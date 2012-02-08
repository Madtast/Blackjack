#include <iostream>
#include <cstdlib>
//#include <sstream>
#include <string>
#include <ctime>

using namespace std;

string niceCardName(char code[]) {
  char nice_num[6];
  char nice_suite[8];
  //stringstream tmp;
  char nice_name[20];
  //string name;

  if(code[0] == 'A')
    strncpy(nice_num, "Ace", 3);
  else if(code[0] == 'T')
    strncpy(nice_num, "Ten", 3);
  else if(code[0] == 'J')
    strncpy(nice_num, "Jack", 4);
  else if(code[0] == 'Q')
    strncpy(nice_num, "Queen", 5);
  else if(code[0] == 'K')
    strncpy(nice_num, "King", 4);
  else
    sprintf(nice_num, "%c", code[0]);

  if(code[1] == 'S')
  {
    //strncpy(nice_suite, "Spaids", 6);
    sprintf(nice_name, "%s of Spaids", nice_num);
  }
  else if(code[1] == 'H')
  {
    //strncpy(nice_suite, "Hearts", 6);
    sprintf(nice_name, "%s of Hearts", nice_num);
  }
  else if(code[1] == 'D')
  {
    //strncpy(nice_suite, "Diamonds", 8);
    sprintf(nice_name, "%s of Diamonds", nice_num);
  }
  else if(code[1] == 'C')
  {
    //strncpy(nice_suite, "Clubs", 5);
    sprintf(nice_name, "%s of Clubs", nice_num);
  }
  else
  { }

  //strncpy(nice_name, nice_num, sizeof(nice_num));
  //strncat(nice_name, " of ", 4);
  //strncat(nice_name, nice_suite, sizeof(nice_suite));

  return nice_name;
}

class Deck {
  string buffer;
  char map_card[54][4];
  int b, card[52];
  public:
    const char * pull(int x) { return map_card[card[x]]; }
    void shuffle();
    void init();
};

void Deck::shuffle() {
  for (int i=1; i<=(52); i++)
  {
    int r = i + (rand() % 52-i);
    int temp = card[i]; card[i] = card[r]; card[r] = temp;
  }
}

void Deck::init() {
  //Requires ctime
  char a = 0;
  for (int i=0; i<4; i++)
  {
    char name[10];
    if(i == 0) { a = 'S'; b = 0; }
    if(i == 1) { a = 'H'; b = 13; }
    if(i == 2) { a = 'D'; b = 26; }
    if(i == 3) { a = 'C'; b = 39; }
    for (int j=1; j<=13; j++)
    {
      if(j == 1)
        sprintf(map_card[(b+j)], "A%c", a);
      else if(j == 10)
        sprintf(map_card[(b+j)], "T%c", a);
      else if(j == 11)
        sprintf(map_card[(b+j)], "J%c", a);
      else if(j == 12)
        sprintf(map_card[(b+j)], "Q%c", a);
      else if(j == 13)
        sprintf(map_card[(b+j)], "K%c", a);
      else
        sprintf(map_card[(b+j)], "%d%c", j, a);
    }
  }
  for (int k=1; k<=52; k++) /*Fill array in order*/
  {
    card[k] = k;
  }
}

int countPoints(char cards[10][2], int n)
{
  int points = 0;
  for (int i=0; i<=n; i++)
  {
    if(cards[i][0] == 'T')
    {
      points += 10;
    }
    else if(cards[i][0] == 'J')
    {
      points += 10;
    }
    else if(cards[i][0] == 'Q')
    {
      points += 10;
    }
    else if(cards[i][0] == 'K')
    {
      points += 10;
    }
    else if(cards[i][0] == '1')
    {
      if(points+11 > 21)
        points += 1;
      else
        points += 11;
    }
    else if(cards[i][0] == '2')
    {
      points += 2;
    }
    else if(cards[i][0] == '3')
    {
      points += 3;
    }
    else if(cards[i][0] == '4')
    {
      points += 4;
    }
    else if(cards[i][0] == '5')
    {
      points += 5;
    }
    else if(cards[i][0] == '6')
    {
      points += 6;
    }
    else if(cards[i][0] == '7')
    {
      points += 7;
    }
    else if(cards[i][0] == '8')
    {
      points += 8;
    }
    else if(cards[i][0] == '9')
    {
      points += 9;
    }
  }
  return points;
}

int main(void)
{

  //Initialize

  srand(time(NULL));
  
  int player_hit = 0, opponent_hit = 0, player_total = 0, opponent_total = 0, off_top = 0;
  char choice[2], player_card[10][2], opponent_card[10][2];
  Deck cards;
  cards.init();
  cards.shuffle();

  //Hit first time
  choice[0] = 'H';
  
  while(choice[0] != 'Q')
  {
    cards.shuffle();
    while(opponent_total <= ((rand() % 6) + 12))
    {
      strcpy(opponent_card[opponent_hit], cards.pull(off_top));
      opponent_hit++; off_top++;
      opponent_total = countPoints(opponent_card, opponent_hit-1);
    }
    //cout << "Your opponent hit " << opponent_hit << " times.\n";

        
    do
    {
      strncpy(player_card[player_hit], cards.pull(off_top), 2);
      cout << "\nPulling Card #" << off_top << " off the top of the deck!\n";
      cout << "Card Pulled is " << niceCardName(player_card[player_hit]) << "\n\n";
      player_total = countPoints(player_card, player_hit);
      if(player_total > 21)
      {
        choice[0] = 'S';
        cout << "BUST! You have: " << player_total << "\n\n";
      }
      else
      {
        cout << "You have: " << player_total << "\n\n";
        cout << "Enter H to hit or S to stand: ";
        cin >> choice;
      }
      player_hit++; off_top++;
      //cout << off_top;
    } while(choice[0] == 'H');
    
    if(choice[0] == 'S')
    {
      cout << "\nThe Computer Has: " << opponent_total << "\n";
      cout << "You Have : " << player_total << "\n\n";
      if(opponent_total > player_total && opponent_total <= 21)
      {
        cout << "You LOST!!!\n\n";
      }
      else if(player_total > 21 && opponent_total > 21)
      {
        cout << "You both BUSTED!!!";
      }
      else if(player_total == opponent_total)
      {
        cout << "It's a DRAW!!!\n\n";
      }
      else
      {
        cout << "You WON!!!\n\n";
      }
      
      cout << "Type C to continue or Q to quit: ";
      cin >> choice[0];
      
      for(int i=0; i<=player_hit; i++)
      {
        player_card[i][0] = 0;
        player_card[i][1] = 0;
      }
      for(int i=0; i<=opponent_hit; i++)
      {
        opponent_card[i][0] = 0;
        opponent_card[i][1] = 0;
      }
      opponent_total = 0, player_hit = 0, player_total = 0, opponent_hit = 0, off_top = 0;
    }
  }
  return 0;
}