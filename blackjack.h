// Blackjack by Paul Serra
// All Rights Reserverd
// Contact Addiction2Code@Gmail.com for Rights Information

#include <iostream>
#include <cstdio>

using namespace std;

class Deck {
  string buffer;
  char map_card[54][4];
  int b, card[52];
  public:
    Deck(); /*Constructor*/
    const char * pull(int x) { return map_card[card[x]]; }
    void display();
    void shuffle();
};

Deck::Deck() { /*This is the constructor and takes care of initalizing the deck when an instance of Deck is made.*/
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
        sprintf(map_card[(b+j)-1], "A%c", a);
      else if(j == 10)
        sprintf(map_card[(b+j)-1], "T%c", a);
      else if(j == 11)
        sprintf(map_card[(b+j)-1], "J%c", a);
      else if(j == 12)
        sprintf(map_card[(b+j)-1], "Q%c", a);
      else if(j == 13)
        sprintf(map_card[(b+j)-1], "K%c", a);
      else
        sprintf(map_card[(b+j)-1], "%d%c", j, a);
    }
  }
  for (int k=1; k<=52; k++) /*Fill array in order*/
  {
    card[k] = k;
  }
}

void Deck::shuffle() { /*This code goes through and shuffles the deck card by card.*/
  //Requires ctime
  for (int i=0; i<(52); i++)
  {
    int r = i + (rand() % 51-i);
    int temp = card[i]; card[i] = card[r]; card[r] = temp;
  }
}

void Deck::display() { /*For debugging purposes this will display the deck.*/
  int i = 0;
  for(i=0;i<52;i++)
  {
    cout << i << ": " << pull(i) << "\n";
  }
}