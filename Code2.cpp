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
    std::string name;
    int price;

public:
    Item(std::string itemName, int itemPrice)
        : name(itemName), price(itemPrice) {}
        
        
	virtual void use(Player& player) const=0;
    virtual void use(Player& player, Enemy& enemy) const = 0;

    std::string getName() const {
        return name;
    }

    int getPrice() const {
        return price;
    }
};
class Player {
    public:
    std::string name;
    int age;
    char gender;
    int level;
    int experience;
    int meleeSkill;
    int rangedSkill;
    std::string weapon;
    int health;
    int gold=100;
    int stamina;
    int damage;
	vector <Item*>inventory;
    Player(std::string playerName, int playerAge, char playerGender, int playerLevel, int playerExperience, int playerMeleeSkill, int playerRangedSkill, std::string playerWeapon, int playerHealth,int stamina,int damage)
        :stamina(stamina),damage(damage) ,name(playerName), age(playerAge), gender(playerGender), level(playerLevel), experience(playerExperience), meleeSkill(playerMeleeSkill), rangedSkill(playerRangedSkill), weapon(playerWeapon), health(playerHealth) {}

    void upgradeLevel() {
        level++;
    }
    void attack(Enemy& enemy);
    void chooseSkillUpgrade(int choice) {
        // Implementation of choosing skill upgrade
    }

   void equipWeapon(std::string weaponName, int damage) {
        // Equip the weapon
        this->damage=damage;
        weapon=weaponName;
        std::cout << name << " equipped " << weaponName << ". Damage increased by " << damage-this->damage << "." << std::endl;
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
       std::string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    void attack(Player& enemy) {
        std::cout << name << " attacks " << enemy.getName() << "!" << std::endl;
        enemy.takeDamage(20);
    }

    void takeDamage(int amount) {
        health -= amount;
        if (health <= 0) {
            std::cout << name << " has been defeated!" << std::endl;
        }
    }


};



// Permanent item: Weapon
class Weapon : public Item {
private:
    int damage;

public:
    Weapon(std::string weaponName, int weaponPrice, int weaponDamage)
        : Item(weaponName, weaponPrice), damage(weaponDamage) {}

    void use(Player& player) const override {
        // Equip the weapon
        player.equipWeapon(name, damage);
    }

    // Implementing the pure virtual function to avoid abstract class
    void use(Player& player, Enemy& enemy) const override {
        // Not applicable for weapons
        std::cout << "Cannot use weapon on enemy." << std::endl;
    }
};

// Throwable item: Grenade
class Grenade : public Item {
public:
    Grenade(std::string grenadeName, int grenadePrice)
        : Item(grenadeName, grenadePrice) {}

    void use(Player& player) const override {
        // Not applicable for grenades
        std::cout << "Cannot use grenade on player." << std::endl;
    }

    // Implementing the pure virtual function to avoid abstract class
 	void use(Player& player, Enemy& enemy) const override;
};

// Consumable item: Food
class Food : public Item {
private:
    int healAmount;

public:
    Food(std::string foodName, int foodPrice, int heal)
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
    std::string type;
    int level;
    int health;
    int attack;

public:
    Enemy(std::string enemyType, int enemyLevel, int enemyHealth, int enemyAttack)
        : type(enemyType), level(enemyLevel), health(enemyHealth), attack(enemyAttack) {}

    virtual void attackPlayer() {
        std::cout << "The enemy attacks the player!" << std::endl;
    }
   void takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        std::cout << type << " has been defeated!" << std::endl;
    }
}
   void attackPlayer(Player& player);
   

    bool isAlive() const {
        return health > 0;
    }

    // Getters and setters
    std::string getType() const {
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
        std::cout << "The zombie attacks the player!" << std::endl;
    }
};

class StrongerZombie : public Enemy {
public:
    StrongerZombie(int enemyLevel)
        : Enemy("Stronger Zombie", enemyLevel, 150, 30) {}

    void attackPlayer() override {
        std::cout << "The stronger zombie attacks the player!" << std::endl;
    }
};

class Human : public Enemy {
public:
    Human(int enemyLevel)
        : Enemy("Human", enemyLevel, 120, 25) {}

    void attackPlayer() override {
        std::cout << "The human attacks the player!" << std::endl;
    }
};