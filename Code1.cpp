
#include <iostream>
#include <string>
#include <vector>
class Enemy;
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
    Player(std::string playerName, int playerAge, char playerGender, int playerLevel, int playerExperience, int playerMeleeSkill, int playerRangedSkill, std::string playerWeapon, int playerHealth)
        : name(playerName), age(playerAge), gender(playerGender), level(playerLevel), experience(playerExperience), meleeSkill(playerMeleeSkill), rangedSkill(playerRangedSkill), weapon(playerWeapon), health(playerHealth) {}

    void upgradeLevel() {
        level++;
    }
    void attack(Enemy& enemy);
    void chooseSkillUpgrade(int choice) {
        // Implementation of choosing skill upgrade
    }

   void equipWeapon(std::string weaponName, int damage) {
        // Equip the weapon
        std::cout << name << " equipped " << weaponName << ". Damage increased by " << damage << "." << std::endl;
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

class Item {
protected:
    std::string name;
    int price;

public:
    Item(std::string itemName, int itemPrice)
        : name(itemName), price(itemPrice) {}

    virtual void use(Player& player) const = 0;

    std::string getName() const {
        return name;
    }

    int getPrice() const {
        return price;
    }
};