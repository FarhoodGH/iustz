// Base class for all items
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
using namespace std;
class Enemy;
class Player;
class Item {
protected:
      string name;
    int price;

public:
    Item(  string itemName, int itemPrice)
        : name(itemName), price(itemPrice) {}
        
        
	virtual void use(Player& player) const=0;
    virtual void use(Player& player, Enemy& enemy) const = 0;

      string getName() const {
        return name;
    }

    int getPrice() const {
        return price;
    }
};
class Player {
    public:
      string name;
    int age;
    char gender;
    int level;
    int experience;
    int meleeSkill;
    int rangedSkill;
      string weapon;
    int health;
    int gold=100;
    int stamina;
    int damage;
	vector <Item*>inventory;
    Player(  string playerName, int playerAge, char playerGender, int playerLevel, int playerExperience, int playerMeleeSkill, int playerRangedSkill,   string playerWeapon, int playerHealth,int stamina,int damage)
        :stamina(stamina),damage(damage) ,name(playerName), age(playerAge), gender(playerGender), level(playerLevel), experience(playerExperience), meleeSkill(playerMeleeSkill), rangedSkill(playerRangedSkill), weapon(playerWeapon), health(playerHealth) {}

    void upgradeLevel() {
        level++;
    }
    void attack(Enemy& enemy);
    void chooseSkillUpgrade(int choice) {
        // Implementation of choosing skill upgrade
    }

   void equipWeapon(  string weaponName, int damage) {
        // Equip the weapon
        this->damage=damage;
        weapon=weaponName;
        if(weaponName=="sword"||weaponName=="axe"||weaponName=="shovel"){this->damage*=(1+(meleeSkill/100));}
        else{this->damage*=(1+(rangedSkill/100));}
          cout << name << " equipped " << weaponName << ". Damage increased by " << damage-this->damage << "." <<   endl;
    }


      int getStamina() const {
        return stamina;
    }

    void setStamina(int value) {
        stamina = value;
    }
    
    // Function to decrease stamina during battle
    void decreaseStamina(int amount) {
        stamina -= amount;
        if (stamina < 0)
            stamina = 0;
    }

    // Function to restore stamina after battle
    void restoreStamina(int amount) {
        stamina += amount;
        // Assuming maximum stamina is 100
        if (stamina > 100)
            stamina = 100;
    }

    void gainExperience(int amount) {
        experience += amount;
    }

    void heal(int amount) {
        health += amount;
        if (health > 100)
            health = 100;
    }
     // Add getter and setter for gold
    int getGold() const {
        return gold;
    }

    void addGold(int amount) {
        gold += amount;
    }

    void spendGold(int amount) {
        gold -= amount;
    }
         string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    void attack(Player& enemy) {
          cout << name << " attacks " << enemy.getName() << "!" <<   endl;
        enemy.takeDamage(20);
    }

    void takeDamage(int amount) {
        health -= amount;
        if (health <= 0) {
              cout << name << " has been defeated!" <<   endl;
        }
    }


};



// Permanent item: Weapon
class Weapon : public Item {
private:
    int damage;

public:
    Weapon(  string weaponName, int weaponPrice, int weaponDamage)
        : Item(weaponName, weaponPrice), damage(weaponDamage) {}

    void use(Player& player) const override {
        // Equip the weapon
        player.equipWeapon(name, damage);
    }

    // Implementing the pure virtual function to avoid abstract class
    void use(Player& player, Enemy& enemy) const override {
        // Not applicable for weapons
       
        player.equipWeapon(name, damage);
    }
};

// Throwable item: Grenade
class Grenade : public Item {
public:
    Grenade(  string grenadeName, int grenadePrice)
        : Item(grenadeName, grenadePrice) {}

    void use(Player& player) const override {
        // Not applicable for grenades
          cout << "Cannot use grenade on player." <<   endl;
    }

    // Implementing the pure virtual function to avoid abstract class
 	void use(Player& player, Enemy& enemy) const override;
};

// Consumable item: Food
class Food : public Item {
private:
    int healAmount;

public:
    Food(  string foodName, int foodPrice, int heal)
        : Item(foodName, foodPrice), healAmount(heal) {}

    void use(Player& player) const override {
        // Heal the player
        player.heal(healAmount);
    }

    // Implementing the pure virtual function to avoid abstract class
    void use(Player& player, Enemy& enemy) const override {
        // Not applicable for food
        player.heal(healAmount);
    }
};

class Enemy {
protected:
      string type;
    int level;
    int health;
    int attack;

public:
    Enemy(  string enemyType, int enemyLevel, int enemyHealth, int enemyAttack)
        : type(enemyType), level(enemyLevel), health(enemyHealth), attack(enemyAttack) {}

    virtual void attackPlayer() {
          cout << "The enemy attacks the player!" <<   endl;
    }
   void takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
          cout << type << " has been defeated!" <<   endl;
    }
}
   void attackPlayer(Player& player);
   

    bool isAlive() const {
        return health > 0;
    }

    // Getters and setters
      string getType() const {
        return type;
    }

    int getLevel() const {
        return level;
    }

    int getHealth() const {
        return health;
    }

    int getAttack() const {
        return attack;
    }
};

class Zombie : public Enemy {
public:
    Zombie(int enemyLevel)
        : Enemy("Zombie", enemyLevel, 100, 20) {}

    void attackPlayer() override {
          cout << "The zombie attacks the player!" <<   endl;
    }
};

class StrongerZombie : public Enemy {
public:
    StrongerZombie(int enemyLevel)
        : Enemy("Stronger Zombie", enemyLevel, 150, 30) {}

    void attackPlayer() override {
          cout << "The stronger zombie attacks the player!" <<   endl;
    }
};

class Human : public Enemy {
public:
    Human(int enemyLevel)
        : Enemy("Human", enemyLevel, 120, 25) {}

    void attackPlayer() override {
          cout << "The human attacks the player!" <<   endl;
    }
};



// Shop class
class Shop {
private:
      vector<Item*> items;

public:
      Shop() {
        // Initialize the shop with some items
        items.push_back(new Weapon("Sword", 50, 20));
        items.push_back(new Weapon("Shovel", 40, 15)); // Adding a shovel weapon
        items.push_back(new Weapon("Axe", 60, 25));    // Adding an axe weapon
        items.push_back(new Weapon("Pistol", 70, 30));  // Adding a pistol weapon
        items.push_back(new Weapon("Shotgun", 90, 35)); // Adding a shotgun weapon
        items.push_back(new Weapon("Rifle", 80, 40));   // Adding a rifle weapon
        items.push_back(new Food("Bread", 15, 10));     // Adding Bread
        items.push_back(new Food("Soup", 20, 15));      // Adding Soup
        items.push_back(new Food("Apple", 10, 8));      // Adding Apple
        items.push_back(new Food("Banana", 12, 9));     // Adding Banana
        items.push_back(new Food("Steak", 25, 20)); 
        // Add more items as needed
    }


    ~Shop() {
        // Free memory allocated for items
        for (auto& item : items) {
            delete item;
        }
    }

    void displayItems() const {
          cout << "Items available in the shop:" <<   endl;
        for (size_t i = 0; i < items.size(); ++i) {
              cout << i + 1 << ". " << items[i]->getName() << " - Price: " << items[i]->getPrice() <<   endl;
        }
    }

    void buyItem(Player& player, int choice) {
        if (choice < 1 || choice > items.size()) {
              cout << "Invalid choice." <<   endl;
            return;
        }

        Item* selectedItem = items[choice - 1];
        if (player.getGold() < selectedItem->getPrice()) {
              cout << "You don't have enough gold to buy this item." <<   endl;
            return;
        }

          cout << "You purchased: " << selectedItem->getName() <<   endl;
        player.inventory.push_back(selectedItem);
        player.spendGold(selectedItem->getPrice());
    }
};

class Battle {
public:
static void fight(Player& player, Enemy& enemy) {
      cout << "A battle begins between " << player.getName() << " and " << enemy.getType() << "!" <<   endl;

    while (player.getHealth() > 0 && enemy.getHealth() > 0) {
        // Display player's health and stamina
          cout << player.getName() << "'s Health: " << player.getHealth() << ", Stamina: " << player.getStamina() <<   endl;

        // Display enemy's health
          cout << enemy.getType() << "'s Health: " << enemy.getHealth() <<   endl;

        playerTurn(player, enemy);

        if (enemy.getHealth() <= 0) {
            break;
        }

        // Display player's health and stamina
          cout << player.getName() << "'s Health: " << player.getHealth() << ", Stamina: " << player.getStamina() <<   endl;

        // Display enemy's health
          cout << enemy.getType() << "'s Health: " << enemy.getHealth() <<   endl;

        enemyTurn(player, enemy);

        if (player.getHealth() <= 0) {
        	cout<<"youdied";
        	
        	exit(0);
            break;
        }
    }

    if (player.getHealth() > 0) {
          cout << player.getName() << " wins the battle!" <<   endl;
         player.addGold(50);
    } else {
          cout << enemy.getType() << " wins the battle!" <<   endl;
    }
}

private:
 static void playerTurn(Player& player, Enemy& enemy) {
      cout << "It's " << player.getName() << "'s turn." <<   endl;
      cout << "Choose your action:" <<   endl;
      cout << "1. Attack" <<   endl;
      cout << "2. Use item" <<   endl;

    int choice;
      cin >> choice;

    switch (choice) {
        case 1:
            // Check if player has enough stamina to attack
            if (player.getStamina() >= 10) {
                player.attack(enemy);
                // Decrease player's stamina after attacking
                player.decreaseStamina(10);
            } else {
                  cout << "Not enough stamina to attack! Choose another action." <<   endl;
            }
            break;
        case 2:
            // Display player's inventory
              cout << "Inventory:" <<   endl;
            for (size_t i = 0; i < player.inventory.size(); ++i) {
                  cout << i + 1 << ". " << player.inventory[i]->getName() <<   endl;
            }
              cout << "Select an item to use (enter item number): ";
            int itemChoice;
              cin >> itemChoice;
            if (itemChoice >= 1 && itemChoice <= player.inventory.size()) {
                Item* selectedItem = player.inventory[itemChoice - 1];
                selectedItem->use(player, enemy);
                // Remove the used item from inventory
                player.inventory.erase(player.inventory.begin() + itemChoice - 1);
            } else {
                  cout << "Invalid item choice!" <<   endl;
            }
            break;
        default:
              cout << "Invalid choice. Please try again." <<   endl;
            playerTurn(player, enemy);
            break;
    }

    // Restore player's stamina after their turn
    player.restoreStamina(20);
}

    static void enemyTurn(Player& player, Enemy& enemy) {
          cout << "It's " << enemy.getType() << "'s turn." <<   endl;
        enemy.attackPlayer(player);
    }
};
Player createCharacter() {
      string name;
    int age;
    char gender;
    int meleeSkill;
    int rangedSkill;
      string weapon;
    int health;
    int stamina;
    int damage;
    int gold;
	int level =10;
	int exp =20;
      cout << "Welcome to the character creator!" <<   endl;
      cout << "Please enter the following attributes for your character:" <<   endl;

      cout << "Name: ";
      cin >> name;

      cout << "Age: ";
      cin >> age;

      cout << "Gender (M/F): ";
      cin >> gender;

      cout << "Melee Skill (0-100): ";
      cin >> meleeSkill;

      cout << "Ranged Skill (0-100): ";
      cin >> rangedSkill;

      cout << "Starting Weapon: ";
      cin >> weapon;

      cout << "Starting Health: ";
      cin >> health;

      cout << "Starting Stamina: ";
      cin >> stamina;

      cout << "Starting Damage: ";
      cin >> damage;

      cout << "Starting Gold: ";
      cin >> gold;

    // Create and return the player object
    return Player(name, age, gender,level,exp, meleeSkill, rangedSkill, weapon, health, stamina, damage);
}

void explore(Player& player) {
    // Simulate random encounters (1/3 chance for each)
    int encounter = rand() % 4; // Generate a random number between 0 and 2
    if (encounter == 0) {
          cout << "You encountered a zombie!" <<   endl;
        Zombie zombie(1);
        Battle::fight(player,zombie);
    } else if (encounter == 1) {
          cout << "You encountered a strong zombie!" <<   endl;
        // Handle strong zombie encounter
        StrongerZombie strongerzombie(1);
        Battle::fight(player,strongerzombie);
    }
    else if(encounter==2){
        Shop shop;
    shop.displayItems();
    }
     else {
          cout << "You encountered a human enemy!" <<   endl;
        // Handle human enemy encounter
        Human human(1);
        Battle::fight(player,human);
    }
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Character creation
      cout << "Welcome to the character creator!" <<   endl;
    Player player = createCharacter();
      cout << "\nCharacter Created Successfully!\n" <<   endl;

    // Give the player 300 gold
    player.addGold(300);

    // Interact with the shop
    int shopChoice=10;
    Shop shop;
    while(shopChoice!=0){
      cout << "Welcome to the shop! You have " << player.getGold() << " gold." <<   endl;
    shop.displayItems();
      cout << "Choose an item to buy (enter item number) or enter 0 to exit the shop: ";
    
      cin >> shopChoice;
    if (shopChoice != 0) {
        shop.buyItem(player, shopChoice);
    }}

    // Main game loop
    char choice;
    do {
          cout << "\nWhat would you like to do?" <<   endl;
          cout << "1. Explore" <<   endl;
          cout << "2. Exit" <<   endl;
          cout << "Choice: ";
          cin >> choice;

        switch (choice) {
            case '1':
                explore(player);
                break;
            case '2':
                  cout << "Exiting the game. Goodbye, " << player.name << "!" <<   endl;
                break;
            default:
                  cout << "Invalid choice. Please try again." <<   endl;
        }
    } while (choice != '2');

    return 0;
}

void Enemy::attackPlayer(Player& player) {
    int damage = 10; // Assuming you have a method to calculate damage
      cout << type << " attacks " << player.getName() << " for " << damage << " damage!" <<   endl;
    player.takeDamage(damage);
}
void Player::attack(Enemy& enemy) {

      cout << name << " attacks " << enemy.getType() << " for " << damage << " damage!" <<   endl;
    enemy.takeDamage(damage);
}
void Grenade::use(Player& player, Enemy& enemy) const {
        // Damage the enemy with the grenade
        int grenadeDamage = 30; // Adjust the damage as needed
        enemy.takeDamage(grenadeDamage);
          cout << "Used " << name << ". Dealt " << grenadeDamage << " damage to the enemy!" <<   endl;
    }