// kochubey_lab7.cpp


#include <iostream>
#include <stdlib.h>
using namespace std;


/*
 * Класс Башни
 *
 * @field health_point количество очков жизни башни
 * @field sum_damage суммарный урон башни по дракону
 * @field destroyed статус башни
 * Башня может атаковать дракона и получать урон от дракона
 */
class Tower {
private:
    int health_point;
    int sum_damage;
    bool destroyed;

public:
    Tower() {
        this->health_point = 100;
        this->destroyed = false;
        this->sum_damage = 0;
    }

    /*
     * Атака башни
     *
     * Башня наносит урон от 20 до 50
     */
    int attack() {
        int damage = rand() % 31 + 20;

        sum_damage += damage;

        return damage;
    }

    /*
     * Принятие урона
     *
     * @param damage урон нанесённый башне
     * Башня получает урон от дракона
     */
    int take_damage(int damage) {
        health_point -= damage;

        if (health_point <= 0)
            destroyed = true;

        return damage;
    }


    /*
     * Проверка статуса
     *
     * Проверка на целостность башни, true - разрушена, false - не разрушена
     */
    bool get_status() {
        return destroyed;
    }


    /*
     * Получение количества очков жизни башни
     *
     * Возвращает количество  очков жизни башни
     */
    int get_hp() {
        return health_point;
    }


    /*
     * Получение количества урона башни
     *
     * Возвращает количество суммарного урона, нанесённого башней дракону
     */
    int get_damage_tower() {
        return sum_damage;
    }
};


/*
 * Класс Замка
 *
 * @field num_tower количество башен
 * @field tower_array массив башен
 * @field destroyed статус замка
 * @field damage_dragon массив суммарного урона от голов дракона
 * @field damage_castle суммарный урон замка
 * Замок может атаковать дракона и получать от него урон
 */
class Castle {
private:
    int num_tower;
    Tower* tower_array;
    bool destroyed;
    int damage_dragon[3] = {0, 0, 0};
    int damage_castle;

public:

    Castle(int num_tower) {
        this->num_tower = num_tower;
        this->tower_array = new Tower[num_tower];
        this->destroyed = false;
        this->damage_castle = 0;
    }

    /*
     * Проверка статуса
     *
     * Проверка на целостность замка, прохождение по массиву башен и проверка их целостности,
     * true - разрушена, false - не разрушена
     */
    bool get_status() {
        int num_intact = 0;
        
        for (int i = 0;i < num_tower; i++) {
            if (!tower_array[i].get_status())
                num_intact++;
        }
        
        if (num_intact == 0)
            destroyed = true;
        
        return destroyed;
    }


    /*
     * Получение количества башен
     *
     * Возвращает количество башен в массиве башен
     */
    int get_num_tower() {
        return this->num_tower;
    }
    

    /*
     * Получение башни
     * 
     * @param ind_tower индекс выбранной башни
     * Возвращает объект выбранной башни из массива башен
     */
    Tower get_tower(int ind_tower) {
        if (ind_tower == num_tower)
            return tower_array[0];
        else if (ind_tower == -1)
            return tower_array[num_tower - 1];

        return tower_array[ind_tower];
    }


    /*
     * Атака замка
     *
     * @param ind_tower индекс центральной атакуемой башни
     * Прохождение по трём башням и получение от них урона, если они целы
     * Возвращает суммарный урон трёх башен по дракону
     */
    int attack(int ind_tower) {
        int sum_damage = 0;

        // center
        if (!tower_array[ind_tower].get_status())
            sum_damage += tower_array[ind_tower].attack();

        // right
        if (num_tower > 1) {
            if (ind_tower + 1 == num_tower) {
                if (!tower_array[0].get_status())
                    sum_damage += tower_array[0].attack();
            }       
            else {
                if (!tower_array[ind_tower + 1].get_status())
                    sum_damage += tower_array[ind_tower + 1].attack();
            }
        }
        
        // left
        if (num_tower > 2) {
            if (ind_tower - 1 == -1) {
                if (!tower_array[num_tower - 1].get_status())
                    sum_damage += tower_array[num_tower - 1].attack();
            }       
            else {
                if (!tower_array[ind_tower - 1].get_status())
                    sum_damage += tower_array[ind_tower -1].attack();
            }
        }

        damage_castle += sum_damage;
        return sum_damage;
    }


    /*
     * Получение урона от дракона
     *
     * @param ind_tower индекс центральной атакуемой башни
     * Нанесение урона центральной и соседним башням
     */
    void take_damage(int ind_tower) {
        // center
        if (!tower_array[ind_tower].get_status())
            damage_dragon[0] += tower_array[ind_tower].take_damage(rand() % 31 + 20);
        
        // right
        if (num_tower > 1) {
            
            if (ind_tower + 1 == num_tower) {
                if (!tower_array[0].get_status())
                    damage_dragon[1] += tower_array[0].take_damage(rand() % 31 + 20);
            }              
            else {
                if (!tower_array[ind_tower + 1].get_status())
                    damage_dragon[1] += tower_array[ind_tower + 1].take_damage(rand() % 31 + 20);
            }              
        }
        
        // left
        if (num_tower > 2) {
            
            if (ind_tower - 1 == -1) {
                if (!tower_array[num_tower - 1].get_status())
                    damage_dragon[2] += tower_array[num_tower - 1].take_damage(rand() % 31 + 20);
            }               
            else {
                if (!tower_array[ind_tower - 1].get_status())
                    damage_dragon[2] += tower_array[ind_tower - 1].take_damage(rand() % 31 + 20);
            }               
        }       
    }


    /*
     * Получение количества урона дракона
     *
     * Возвращает суммарный урон трёх голов по отдельности
     */
    int* get_dragon_damage() {
        return damage_dragon;
    }


    /*
     * Получение количества урона замка
     *
     * Возвращает суммарный урон, нанесённый замком дракону
     */
    int get_castle_damage() {
        return damage_castle;
    }
};



/*
 * Класс Дракона
 *
 * @field health_point количество очков жизни дракона 
 * @field destroyed текущий статус дракона
 * Дракон может атаковать замок и получать урон от замка
 */
class Dragon {
private:
    int health_point;
    bool destroyed;

public:
    Dragon() {
        this->health_point = 1000;    
        this->destroyed = false;
    }


    /*
     * Атака дракона
     *
     * @param castle объект замка, который атакуется 
     * @param ind_tower индекс атакуемой центральной башни
     * Башня получает урон от дракона
     */
    void attack(Castle* castle , int ind_tower) {
        castle->take_damage(ind_tower);
    }


    /*
     * Получение количество hp
     *
     * Возвращает текущее количество очков жизни дракона
     */
    int get_hp() {
        return health_point;
    }


    /*
     * Принятие урона
     *
     * @param damage урон нанесённый дракону
     * Дракон получает суммарный урон от трёх башен
     */
    void take_damage(int damage) {
        health_point -= damage;

        if (health_point <= 0)
            destroyed = true;
    }

    /*
     * Проверка статуса
     *
     * Проверка на целостность дракона
     * true - разрушен, false - не разрушен
     */
    bool get_status() {
        return destroyed;
    }

};

int main()
{
    srand(time(NULL));

    int num_tower = 8;
    Dragon new_dragon;
    Castle new_castle(num_tower);
    int tactic_type;
    int fight_step = 0;

    cout << "Enter number of dragon tactic" << endl;
    cout << "1. Until complete destruction" << endl;
    cout << "2. Constant attack of random towers" << endl;
    cout << "Your answer: ";
    cin >> tactic_type;

    //cout << "first D: " << new_dragon.get_status() << endl;
    

    while (!new_castle.get_status() and !new_dragon.get_status()) {
        int ind_tower;
        
        if (tactic_type == 1) {
            ind_tower = rand() % num_tower;

            while (!new_dragon.get_status() and !new_castle.get_tower(ind_tower).get_status()) {
                new_dragon.attack(&new_castle, ind_tower);
                new_dragon.take_damage(new_castle.attack(ind_tower));
                fight_step++;

                /*cout << "attaced is: " << ind_tower << endl;
                for (int i = 0; i < num_tower; i++) {
                    cout << "T " << i << ": " << new_castle.get_tower(i).get_hp() << endl;
                }
                cout << "D: " << new_dragon.get_hp() << "\n" << endl;*/
            }
        } 
        else {
            ind_tower = rand() % num_tower;

            if (!new_dragon.get_status() and !new_castle.get_tower(ind_tower).get_status()) {
                new_dragon.attack(&new_castle, ind_tower);
                new_dragon.take_damage(new_castle.attack(ind_tower));
                fight_step++;

                /*cout << "attaced is: " << ind_tower << endl;
                for (int i = 0; i < num_tower; i++) {
                    cout << "T " << i << ": " << new_castle.get_tower(i).get_hp() << endl;
                }
                cout << "D: " << new_dragon.get_hp() << "\n" << endl;*/
            }
        }
        
    }

    // Statistic
    cout << "\nWinner is ";
    if (!new_dragon.get_status())
        cout << "Dragon\n" << endl;
    else
        cout << "Castle\n" << endl;

    int* damage_dragon = new_castle.get_dragon_damage();
    
    cout << "Sum damage of Dragon: " << damage_dragon[0] + damage_dragon[1] + damage_dragon[2] << endl;   
    for (int i = 0;i < 3;i++) {
        cout << "Damage of " << i+1 << " head: " << damage_dragon[i] << endl;
    }

    cout << "\nSum damage of Castle: " << new_castle.get_castle_damage() << endl;
    for (int i = 0;i < num_tower;i++) {
        cout << "Damage T" << i+1 << ": " << new_castle.get_tower(i).get_damage_tower() << endl;
    }

    cout << "\nNum of step of fight: " << fight_step << endl;
    
    int num_intact_tower = 0;
    for (int i = 0; i < num_tower; i++) {
        if (!new_castle.get_tower(i).get_status())
            num_intact_tower++;
    }
    cout << "Num of intact tower: " << num_intact_tower << endl;
    cout << "HP of Dragon: " << new_dragon.get_hp() << endl;

    /*cout << "dragon status: " << new_dragon.get_status() << endl;
    cout << "castle status: " << new_castle.get_status() << endl;
    cout << true;*/
}

