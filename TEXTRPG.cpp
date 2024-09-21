/*
This is a prototype of an RPG. You will fight a series of battles against infinite opponents, each with random difficulty until you get bored.

I have attempted the following features:
1) I have added an Armor to the game. It is a piece of gear that increases the defense stat of the character.

2) I have also utilized a shop call. If the player decides to choose the shop, they are prompted with the shop menu.
They can spend the gold they earned from defeating monsters to purchase better gear. 
For the purpose of the project you, the player, haVE been granted 1,000,000 gold.

DAMAGE VALUES ARE BASED OFF OF A FORMULA THAT TAKES DEFENSE VALUES INTO ACCOUNT. THEREFORE DAMAGE DEALT DOES NOT EQUAL HEALTH SUBRACTED FROM ENEMY/HERO.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;


class Character{
	protected:
		string name;
		int HP; // hitpoints
		int str;
		int def;
		
	public:
		Character(string n, int h, int s, int d){
			name = n;
			HP = h;
			str = s;
			def = d;
		}
		int getHP(){ //gets health value of character
			return HP;
		}
		int attack(){
			bool crit = false;
			int damage = rand() % str;
			
			// roll for crit
			if(rand() % 21 == 20){
				crit = true;
				damage *= 2; // double the damage
				cout << "CRIT!\n";
			}
			
			cout << name << " attacks with " << damage << " damage.\n";
			return damage;
		}
		
		void defend(int damage){
			int realdamage = damage * damage / (damage + def); //formula for damage taken with specific defense stats (makes it so damage is never = 0)
			HP -= realdamage; 
				
		}
		int getstr(){ //gets strength value of hero
			return str;
		}
		int getdef(){ //gets defense value of hero
			return def;
		}
		
		void printstats(){
			cout << name <<endl;
			cout << "HP: "<< HP <<endl;
			cout << "Strength: "<< str <<endl;
			cout << "Defense: "<< def <<endl;			
		}
};

class Weapon{
	public:
		string name;
		int attMod;
		int durability; // % based 100% is new... 0% broken
	
		
		// Default constructor
		Weapon (){
		}
		
		// Only Overload if there is already a default constructor
		Weapon(string n, int a){
			name = n;
			attMod = a;
			durability = 100;
		}
		void printstats(){
			cout << "This weapons adds " << attMod <<" To your damage." <<endl;
		}
		
};




class Armor{
	public:
		string name;
		int defMod;
		
		Armor(){
		}
		Armor(string n, int d){
			name = n;
			defMod = d;  //defence mod
		}
		void printstats(){
			cout << "This Armor adds " << defMod <<" To your defence stat." <<endl;
		}
		
};



// Hero IS A Character. Therefore Hero INHERIT from Character
class Hero : public Character{
	private:
		Weapon mainWeapon;
		Armor mainArmor;
		
	public:
		Hero(string n, int h, int s, int d) : Character(n,h,s,d){
			Weapon starterWeapon("Wooden Sword", 5); // creating a new Weapon
			mainWeapon = starterWeapon; // Assigning that new weapon to the class's mainweapon.
			Armor starterArmor("Wooden Armor", 5);
			mainArmor = starterArmor; //Assigning the new armor to the class's mainarmor
		}
	    void setstr(int x){
			str += x;
		}
		void setdef(int x){
			def += x;
		}
		//overiding the parent's attack()
		int attack(){
			bool crit = false;
			int damage = rand() % str;
			
			if(mainWeapon.durability >0)
				damage += mainWeapon.attMod;
			//cout << damage<<endl;
			// roll for crit
			if(rand() % 21 == 20){
				crit = true;
				damage = damage * 2; // double the damage
				cout << "CRIT!\n";
			}
		
			if(mainWeapon.durability >0)
				cout << name << " attacks with "<< mainWeapon.name << " for " << damage << " damage.\n";
			else
				cout << name << " attacks for "<< damage << " damage.\n";
			
			int durabilitycheck = rand() % 10;
			if(durabilitycheck == 0){
				mainWeapon.durability -=10;
			}
			
			return damage;
		}
		
		void printstats(){
			cout << name <<"'s Stats"<<endl;
			cout << "HP: "<< HP <<endl;
			cout << "Strength: "<< str <<endl;
			cout << "Defense: "<< def <<endl;	
		}
		
};


class Badguy:public Character{
	private:
		Weapon MainEnemyWeapon;
	public:
		Badguy(string n, int h, int s, int d) : Character(n,h,s,d){
		 name = n;
		 h = h;
		 s = s;
		 d = d;
		 string WeaponArr[5] = {"Club", "Mallet", "Sword", "Bow" , "Shovel"}; //randomizes
		 int EWeapon = rand() % 5;
		 Weapon Enemy (WeaponArr[EWeapon],10);
		 MainEnemyWeapon = Enemy;
		}
		int attack(){
			bool crit = false;
			int damage = rand() % str;
			if(rand() % 21 == 20){
				crit = true;
				damage = damage * 2; // double the damage
				cout << "CRIT!\n";
			}
				cout << name << " attacks with "<< MainEnemyWeapon.name << " for " << damage << " damage.\n";
			return damage;
		}
		

        string getName(){
        	return name;
		}
};

void displayoptions(){
	cout << "Select your next move: " <<endl;
	cout << "Attack(1)" << '\t' << "Shop(2)"<<endl;
	cout << "Check Stats(3)" << '\t' << "Exit Game(4)" <<endl; 
}




int main(){
	srand(time(0));	
	string charName;
	bool exitgame = false; //to exit game if desired
	int playergold = 1000000;
	cout << "Welcome to Basic RPG 101! Please Enter Your Desired Character's Name: \n";
	cin >> charName;
	system("cls");
	
	Hero myHero(charName, 200, 20, 10);
	myHero.printstats(); 
	
	cout <<"----------------------------------------------------------------------"<<endl;
	cout << "You are a new adventurer who had just signed up. Your first task was to explore the beginner dungeon."<<endl;
    cout <<"As you are progressing, you notice a hidden passage behind a fake wall." <<endl;
	cout << "Instead of reporting this to guild officials you explore this dungeon alone."<< endl;
	cout << "As you wonder around the dungeon, you notice that it is filled with infinite monsters.\nYou foresee youself getting rich off of the drops from these monsters." <<endl;
	cout << "You decide to fight until you are rich." <<endl;
    cout <<"----------------------------------------------------------------------"<<endl;
    
	while(myHero.getHP() > 0 && exitgame == false){ // START OF LOOP UNTIL USER WANTS TO EXIT
		int enemydefeatedcounter = 0;
     	int dropped_gold;
		int randenemy = rand() % 5;
		int playerchoice;
		int enemyhealth = rand() % 100; //random between 0 to 100
		int enemystr = rand() % 50;
		int enemydef = rand() % 35;
		
		
		string enemyArr[5] = {"Goblin", "Troll", "Ghoul", "Orc" ,"Golem" }; //random array of enemies
		Badguy randEnemy(enemyArr[randenemy], enemyhealth, enemystr, enemydef); // RANDOM ENEMY CREATED
		cout << "You have encountered a " << enemyArr[randenemy] << endl; 
		cout <<"----------------------------------------------------------------------"<<endl;
		randEnemy.printstats();
		cout <<"----------------------------------------------------------------------"<<endl;
		displayoptions();
		cin >> playerchoice;
		    if (playerchoice == 1){ //battle function basically (I did not make this a function by itself due to complications of things not being decleared in the scope)
		    	
				while(playerchoice == 1){ //When the player wants to attack
					cout << "\n";
		        	system("cls"); //clears the console to make it look nice.
		            randEnemy.defend(myHero.attack());
		            myHero.defend(randEnemy.attack());
		            cout <<"----------------------------------------------------------------------"<<endl;
		            myHero.printstats();
		            cout <<"----------------------------------------------------------------------"<<endl;
		            randEnemy.printstats();
		            cout <<"----------------------------------------------------------------------"<<endl;
		            displayoptions();
		            cin >> playerchoice;
		            
		            if (randEnemy.getHP() <= 0){
		            	enemydefeatedcounter++;
		            	system("cls");
		            	dropped_gold = rand() % 30; //randomly drops gold from 0 to 30
		            	cout << "You got " <<dropped_gold <<" Gold from the enemy!" <<endl;
		            	playergold += dropped_gold; //adds gold to player amount
		            	break;    //ends loop
				}
			}
 	
	}
			if (playerchoice == 2){ //SHOP FUNCTION BASICALLY (I did not make this a function by itself due to complications of things not being decleared in the scope)
				int playerbuychoice;
				char confirm; //Confirm purchase to make sure you dont accidentally buy
				system("cls");
				cout << "Welcome to the Shop!\n";
				cout << "You currently have: " << playergold << " gold!\n" <<endl;
				cout << "(1) Iron Sword - 1000 Gold " << '\t' << "(2) Diamond Sword - 2500 Gold" << '\t' << "(3) Holy Sword - 5000 Gold\n";
				cout << "(4) Iron Armor - 1500 Gold " << '\t' << "(5) Diamond Armor - 3000 Gold" << '\t' << "(6) Holy Armor - 6000 Gold\n";
				cout << "Select the number of the gear you wish to purchase." <<endl;
				cin >> playerbuychoice;
				
				if (playerbuychoice == 1){
					Weapon Iron_Sword("Iron Sword", 10); // Creates the weapon. 
		        	cout << "The Iron Sword adds " << Iron_Sword.attMod <<" to your attack stat." <<endl; //DISPLAYS ATTACK MOD
					cout << "Are you sure you want to purchase this item?(y/n)";
					cin >> confirm;
					
					if (confirm == 'y' ){
						myHero.setstr(Iron_Sword.attMod); //adds the attack mod of weapon to hero's strength stat.
					    playergold -= 1000; //removes gold from account
						system("cls");
						cout << "Thanks for your purchase! Your attack strength is now: "<< myHero.getstr() <<endl <<endl;
					}
					
					else {
						system("cls"); //clears the console if player did not intend to buy gear.
					}
				}
				if (playerbuychoice == 2){
					Weapon Diamond_Sword("Diamond Sword",25);
					cout << "The Diamond Sword adds " << Diamond_Sword.attMod <<" to your attack stat." <<endl;
					cout << "Are you sure you want to purchase this item?(y/n)";
					cin >> confirm;
					
					if (confirm == 'y' ){
						myHero.setstr(Diamond_Sword.attMod);
					    playergold -= 2500;
						system("cls");
						cout << "Thanks for your purchase! Your attack strength is now: "<< myHero.getstr() <<endl <<endl;
					}
					
					else {
						system("cls");
					}
			}
					if (playerbuychoice == 3){
					Weapon Holy_Sword("Holy Sword",50);
					cout << "The Holy Sword adds " << Holy_Sword.attMod <<" to your attack stat." <<endl;
					cout << "Are you sure you want to purchase this item?(y/n)";
					cin >> confirm;
					
					if (confirm == 'y' ){
						myHero.setstr(Holy_Sword.attMod);
					    playergold -= 2500;
						system("cls");
						cout << "Thanks for your purchase! Your attack strength is now: "<< myHero.getstr() <<endl <<endl;
					}
					
					else {
						system("cls");
					}
				}
				if (playerbuychoice == 4){
					Armor Iron_Armor("Iron Armor",10);
					cout << "The Iron Armor adds " << Iron_Armor.defMod << " to your defense stat" <<endl;
					cout << "Are you sure you want to purchase this item?(y/n)";
					cin >> confirm;
					
					if (confirm == 'y' ){
					myHero.setdef(Iron_Armor.defMod);
					playergold -= 1500;
					system("cls");
					cout << "Thanks for your purchase! Your Defense Stat is now: "<< myHero.getdef() <<endl <<endl;
				}
				
				    else{
					    system("cls");
				}
			}
			    if (playerbuychoice == 5){
			    	Armor Diamond_Armor("Diamond Armor", 25);
			    	cout << "The Diamond Armor adds "<< Diamond_Armor.defMod << " to your defense stat" <<endl;
			    	cout << "Are you sure you want to purchase this item?(y/n)";
			    	cin >> confirm;
			    	
			    	if (confirm == 'y' ){
			    		myHero.setdef(Diamond_Armor.defMod);
			    		playergold -=3000;
			    		system("cls");
			    		cout << "Thanks for your purchase! Your Defense Stat is now: "<< myHero.getdef() <<endl <<endl;
			    	}
			    	
			    	else{
			    		system("cls");
					}
 				}
 				if (playerbuychoice == 6){
			    	Armor Holy_Armor("Holy Armor", 50);
			    	cout << "The Holy Armor adds "<< Holy_Armor.defMod << " to your defense stat" <<endl;
			    	cout << "Are you sure you want to purchase this item?(y/n)";
			    	cin >> confirm;
			    	
			    	if (confirm == 'y' ){
			    		myHero.setdef(Holy_Armor.defMod);
			    		playergold -=3000;
			    		system("cls");
			    		cout << "Thanks for your purchase! Your Defense Stat is now: "<< myHero.getdef() <<endl <<endl;
			    	}
			    	
			    	else{
			    		system("cls");
					}
 				}
				
			}
			if(playerchoice == 3){ //check stats function
				system("cls");
				cout <<"----------------------------------------------------------------------"<<endl;
				myHero.printstats();
				cout << "You Have Slain " <<enemydefeatedcounter <<" Enemies!" <<endl;
				cout << "You currently have: " << playergold << " gold." <<endl;
				cout <<"----------------------------------------------------------------------"<<endl;
			}
			if(playerchoice == 4){ //exits game (nothing special)
				exitgame = true;
				break;
			}		
}
	
}







