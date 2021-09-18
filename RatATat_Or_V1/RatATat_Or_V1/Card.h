#ifndef _CARD_H_
#define _CARD_H_

#include <time.h>
#include<string>
#include <iostream>
using namespace std;

class Player;
class Pile;
class RatATat;

class Card
{
protected:
	int m_value;          // The numerical value of the card
	string m_text;        //Describes the card "Cat/Rat,m_value" or for special_cards "Peek/Draw 2/Swap"

	//Extras:
	static int m_number_of_cards_already_made ;         //the number of cards that made till now   //??need to initialize it in cpp??// 
	const static int m_total_number_of_cards_in_1_ratatat_pile = 54;   //total number of cards in 1 ratatat pile

public:
	//who that go to manage what card to create is pile! (first need to check with yael because if yes there is no need to toss_val , and if no so we need toss_val and class card will manage what card value to create)
	Card(const string& card_type , const int card_value );       //ctor - get card_type: (cat/rat/peek/draw 2/swap) , and card_value: if cat 0-5 , if rat 6-9 and if one of the special cards -1 . then create a card.
	//using default dtor
	//using default copy ctor
	//static , friends and virtual members and methodes:
	friend ostream& operator<<(ostream& os, const Card& c);  //prints card m_text
	//pure virtual methods:
	virtual void use(Player** players, int curr_player, RatATat& rat) = 0;  //there are some implementations : in play_card , and *each* of special_card!.
	virtual void print_card_action_menu() const = 0;   //there are 2 implementations - in play_card , and in special_card
	virtual int get_card_action_menu_max_num() const = 0;  //there are 2 implementations - in play_card and in special_card - always return 2

	//Extras:
	static int get_number_of_cards_already_made();                //returns number_of_cards_already_made               
	static int get_total_number_of_cards_in_1_ratatat_pile();     //return total_number_of_cards_in_1_ratatat_pile     
	int get_card_value() const ;
	bool is_special_card() const;  //return 1 if card is special card and 0 if not

	//static void swap_cards(Card*& card_a_pointer, Card*& card_b_pointer);
};

/////////////////////////////////////////////////////////////////////////////
class Play_card : public Card
{
protected:

	//Extras:
	static int m_Play_cards_hist_total[10];        //the total number of Play_cards from each type that need to be in 1 Ratatat pile. //can be const also?
	static int m_Play_cards_hist_made_till_now[10];  //the number of Play_cards from each type that made till now.

public:
	Play_card(const string& card_type, const int card_value); //ctor with empty implementaion - will get from initialization list of his sons - card_type = "Rat"/"Cat" and card_value (from toss_val of each of them), this will sent with the initialization list of himself to his father the members :m_value ,m_text
	//using default dtor
	//the virtual function of class card
	void use(Player** players, int curr_player, RatATat& rat);             //does what he named about
	void print_card_action_menu() const;                                   //does what he named about
	int get_card_action_menu_max_num() const;                              //return 2 always 
};

/////////////////////////////////
class Rat_card : public Play_card
{
protected:
	static unsigned int m_num_cards; //static member describes how much Rat_cards made till now (need to initialize it in cpp in first lines of Rat_card) //?where the initializations?// //?where to put this line in public or protected?//

	//Extras:
	const static int m_total_Rat_cards_in_1_pile = 21;      //for new pile
	const static int m_Rat_card_min_value = 6;              //for toss_val
	const static int m_number_of_Rat_card_types = 4;        //for toss_val

public:
	Rat_card(unsigned int card_value); //ctor with empty implementation - will send with initialization list to his father (the class play_card) the members m_text="Rat,m_value",and m_value=card_value
									   ////to create a card i will use method toss_vall in class Rat_card to be card value .
    //using default dtor
	//static methodes
	static int get_total_cards();  //return the number of Rat_cards made till now (return m_num_cards).  //?ask yael if thats what she wants!?//  
	static int toss_val();         //Scores a numerical value to the card according to the rules of 4 cards per card type

    //Extras:
	static int get_total_Rat_cards_in_1_pile(); //return the number of Rat_cards need to be in 1 pile (return total_Rat_cards_need_in_1_pile)
};

/////////////////////////////////
class Cat_card : public Play_card
{
protected:
	static unsigned int m_num_cards; //static member describes how much Cat_cards made till now (need to initialize it in cpp in first lines of Cat_card) //??//

	//Extras:
	const static int m_total_Cat_cards_in_1_pile = 24;      //for new pile
	const static int m_Cat_card_min_value = 0;              //for toss_val
	const static int m_number_of_Cat_card_types = 6;        //for toss_val

public:
	Cat_card(unsigned int card_value);   //ctor with empty implementation - will send with initialization list to his father (the class play_card) the members m_text="Cat,m_value",and m_value=card_value.
										 //to create a card i will use method toss_vall in class Cat_card to be card value .
	//using default dtor
	//static methodes:
	static int get_total_cards();  //return the number of Cat_cards made till now (return m_num_cards).  //?ask yael if thats what she wants!?//  
	static int toss_val();         //Scores a numerical value to the card according to the rules of 4 cards per card type

    //Extras:
	static int get_total_Cat_cards_in_1_pile(); //return the number of Cat_cards need to be in 1 pile (return total_Cat_cards_need_in_1_pile)
};
//////////////////////////////////////////////////////////////////////////////
class Special_card : public Card
{
protected:

public:
	Special_card(const string& special_card_type , const int card_value = -1);//ctor with empty implementaion - will get from initialization list of his sons - special_card_type = "Draw 2"/"Swap"/"Peek", this will initialize his father the members :m_text=special_card_type ,m_value =-1 ,m_text
	//using default dtor
	//the virtual function of class card
	void print_card_action_menu() const;  //1 to discard card . 2 for use it
	int get_card_action_menu_max_num() const;  //return 2
};

/////////////////////////////////
class Draw2_card : public Special_card
{
protected:
	static unsigned int m_num_cards; //static member describes how much Draw2_cards made till now (need to initialize it in cpp in first lines of Draw2_card) //?where the initializations?// //?where to put this line in public or protected?//

	//Extras:
	const static int m_total_Draw2_cards_in_1_pile = 3;

public:
	Draw2_card();   //ctor with empty implementaion - will send to his father (the class special card) with initialization list "Draw 2"
	//using default dtor
	//the virtual function of class card
	void use(Player** players, int curr_player, RatATat& rat);
	//static methodes:
	static int get_total_cards();  //return the number of Draw2_cards made till now (return m_num_cards).  //?ask yael if thats what she wants!?//  
	//the virtual function of class card

	//Extras:
	static int get_total_Draw2_cards_in_1_pile(); //return the number of Draw2_cards need to be in 1 pile (return total_Draw2_cards_need_in_1_pile)
};

/////////////////////////////////
class Swap_card : public Special_card
{
protected:
	static unsigned int m_num_cards; //static member describes how much Swap_cards made till now (need to initialize it in cpp in first lines of Swap_card) //?where the initializations?// //?where to put this line in public or protected?//

	//Extras:
	const static int m_total_Swap_cards_in_1_pile = 3;
	void swap_cards(Card*& card_a_pointer, Card*& card_b_pointer);

public:
	Swap_card();   //ctor with empty implementaion - will send to his father (the class special card) with initialization list "Swap"
	//using default dtor
	//the virtual function of class card
	void use(Player** players, int curr_player, RatATat& rat);
	//static methodes:
	static int get_total_cards();  //return the number of Swap_cards made till now (return m_num_cards).  //?ask yael if thats what she wants!?// 
	//Extras:
	static int get_total_Swap_cards_in_1_pile(); //return the number of Swap_cards need to be in 1 pile (return total_Draw2_cards_need_in_1_pile)

};

/////////////////////////////////
class Peek_card : public Special_card
{
protected:
	static unsigned int m_num_cards; //static member describes how much Peek_cards made till now (need to initialize it in cpp in first lines of Peek_card) //?where the initializations?// //?where to put this line in public or protected?//

	//Extras:
	const static int m_total_Peek_cards_in_1_pile = 3;

public:
	Peek_card();   //ctor with empty implementaion - will send to his father (the class special card) with initialization list "Peek"
    //using default dtor
	//the virtual function of class card
	void use(Player** players, int curr_player, RatATat& rat);
	//static methodes:
	static int get_total_cards();  //return the number of Peek_cards made till now (return m_num_cards).  //?ask yael if thats what she wants!?//  
	//Extras:
	static int get_total_Peek_cards_in_1_pile(); //return the number of Peek_cards need to be in 1 pile (return total_Draw2_cards_need_in_1_pile)

};


#endif // !_CARD_H_
