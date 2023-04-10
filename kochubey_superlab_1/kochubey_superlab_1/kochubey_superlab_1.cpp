// kochubey_superlab_1.cpp

#include <iostream>
#include <stdlib.h>
#include <list>

// const length area DONE
// max distance DONE

// class D (Препятствие) 1/3 nn скрыты для игрока
// gen 1-12 > speed => take_damage(1)
 
using namespace std;

int dice_roll(int, int);

class Trap {
private:
    int damage;
    int* coord = new int[2];
    char lit = '#';

public:
    Trap(){
        this->damage = 1;
    }

    Trap(int damage) {
        this->damage = damage;
    }

    int trap_work(int speed) {
        if (dice_roll(1, 12) > speed)
            return damage;
        return 0;
    }

    void set_coord(int x, int y) {
        coord[0] = x;
        coord[1] = y;
    }

    int* get_coord() {
        return coord;
    }

    char get_lit() {
        return lit;
    }
};

class Weapon {
private:
    string name;
    string type;
    int damage_bonus;
    int num_roll, num_faces;

public:
    Weapon() {}

    Weapon(string name) {

         

        if (name == "Bite") {
            this->type = "melee";
            this->name = name;
            this->damage_bonus = 2;
            this->num_roll = 2;
            this->num_faces = 4;
        }

        if (name == "Claw") {
            this->type = "melee";
            this->name = name;
            this->damage_bonus = 4;
            this->num_roll = 2;
            this->num_faces = 6;
        }

        if (name == "Short sword") {
            this->type = "melee";
            this->name = name;
            this->damage_bonus = 3;
            this->num_roll = 1;
            this->num_faces = 6;
        }

        if (name == "Axe") {
            this->type = "melee";
            this->name = name;
            this->damage_bonus = 5;
            this->num_roll = 1;
            this->num_faces = 12;
        }

        if (name == "Long bow") {
            this->type = "long-range";
            this->name = name;
            this->damage_bonus = 3;
            this->num_roll = 1;
            this->num_faces = 8;
        }
    }

    Weapon (string name, string type, int damage_bonus, int num_roll, int num_faces) {
        this->name = name;
        this->type = type;
        this->damage_bonus = damage_bonus;
        this->num_roll = num_roll;
        this->num_faces = num_faces;
    }

    /*
     * Атака оружия
     *
     * оружие наносит ndm урона
     */
    int attack() {
        return (dice_roll(num_roll, num_faces));
    }

    /*
     * Тип оружия
     *
     * возвращает тип оружия
     */
    string get_type() {
        return type;
    }

    /*
     * Название
     *
     * возвращает название оружия
     */
    string get_name() {
        return name;
    }
};

class Creature {
private:
    string name;
    char literal;
    int hit_points;
    int armor_class;
    int attack_bonus;
    int initiative_bonus;
    int initiative;
    int speed;
    int size_weapons_set;
    Weapon** weapons_set;
    int* coord = new int[2];

public:
    Creature() {}

    Creature(string name) {
        if (name == "Wolf") {
            this->name = name;
            this->literal = 'W';
            this->hit_points = dice_roll(2, 8) + 2;
            this->armor_class = 13;
            this->attack_bonus = 4;
            this->initiative_bonus = 2;
            this->initiative = dice_roll(1, 20) + initiative_bonus;
            this->speed = 8;
            this->size_weapons_set = 1;
            this->weapons_set = new Weapon*[size_weapons_set];
            this->weapons_set[0] = new Weapon("Bite");
        }

        if (name == "Bear") {
            this->name = name;
            this->literal = 'B';
            this->hit_points = dice_roll(4, 10) + 12;
            this->armor_class = 11;
            this->attack_bonus = 6;
            this->initiative_bonus = 0;
            this->initiative = dice_roll(1, 20) + initiative_bonus;
            this->speed = 8;
            this->size_weapons_set = 1;
            this->weapons_set = new Weapon*[size_weapons_set];
            this->weapons_set[0] = new Weapon("Claw");
        }

        if (name == "Barbarian") {
            this->name = name;
            this->literal = 'T';
            this->hit_points = dice_roll(2, 12) + 21;
            this->armor_class = 16;
            this->attack_bonus = 5;
            this->initiative = dice_roll(1, 20) + initiative_bonus;
            this->initiative_bonus = 2;
            this->speed = 8;
            this->size_weapons_set = 1;
            this->weapons_set = new Weapon*[size_weapons_set];
            this->weapons_set[0] = new Weapon("Axe");
        }

        if (name == "Ranger") {
            this->name = name;
            this->literal = 'R';
            this->hit_points = dice_roll(2, 10) + 16;
            this->armor_class = 15;
            this->attack_bonus = 5;
            this->initiative_bonus = 3;
            this->initiative = dice_roll(1, 20) + initiative_bonus;
            this->speed = 6;
            this->size_weapons_set = 2;
            this->weapons_set = new Weapon*[size_weapons_set];
            this->weapons_set[0] = new Weapon("Short sword");
            this->weapons_set[1] = new Weapon("Long bow");
        }
    }

    Creature(char lit, string name, int hit_points, int armor_class, int attack_bonus, int initiative_bonus, int speed, int num_weapon, Weapon** weapons_set) {
        this->literal = lit;
        this->name = name;
        this->hit_points = hit_points;
        this->armor_class = armor_class;
        this->attack_bonus = attack_bonus;
        this->initiative_bonus = initiative_bonus;
        this->speed = speed;
        this->size_weapons_set = num_weapon;
        this->weapons_set = weapons_set;
    }

    /*
     * Символ существа
     *
     * возвращает символ, которым существо отмечается на поле
     */
    char get_lit() {
        return literal;
    }

    /*
     * Инициатива существа
     *
     * возвращает количество очков инициативы существа
     */
    int get_initiative() {
        return initiative;
    }

    /*
     * Установка координат
     *
     * @param x координата х
     * @param y координата у
     * Установка координат существа на поле
     */
    void set_coord(int x, int y) {
        coord[0] = x;
        coord[1] = y;
    }

    /*
     * Получение координат
     *
     * возвращает координаты существа на поле
     */
    int* get_coord() {
        return coord;
    }

    /*
     * Получение очков здоровья
     *
     * возвращает количество очков здороья существа
     */
    int get_hp() {
        return hit_points;
    }

    /*
     * Получение бонусных очков атаки
     *
     * возвращает количество очков бонуса атаки существа
     */
    int get_attack_bonus() {
        return attack_bonus;
    }

    /*
     * Получение очков класса брони
     *
     * возвращает количество очков класса брони
     */
    int get_armor_class() {
        return armor_class;
    }

    /*
     * Получение имени
     *
     * возвращает имя существа
     */
    string get_name() {
        return name;
    }

    /*
     * Получение количества оружия
     *
     * возвращает количество оружия у существа
     */
    int get_size_weapons_set() {
        return size_weapons_set;
    }

    /*
     * Получение массива оружия
     *
     * возвращает ссылку на массив оружия существа
     */
    Weapon** get_weapons_set() {
        return weapons_set;
    }

    /*
     * Получение урона
     *
     * @param damage количество нанесённого урона
     * Отнимает у существа очки здоровья в размере нанесённого ему урона
     */
    void take_damage(int damage) {
        hit_points -= damage;
    }

    /*
     * Получение скорости передвижения
     *
     * возвращает количество очков скорости существа
     */
    int get_speed() {
        return speed;
    }

};

class Area {
private:
    int lenght_area;
    char** area;
    int size_team_A, size_team_B;
    char lit_empty = '.';
    int num_trap;

public:
    Trap** set_trap;
    Creature** team_A;
    Creature** team_B;

    Area(int length_area) {
        this->lenght_area = length_area;
        this->area = new char*[lenght_area];

        for (int i = 0; i < lenght_area; i++) {
            this->area[i] = new char[lenght_area];
        }

        this->size_team_A = 5;
        this->size_team_B = 4;

        // (new)
        this->num_trap = lenght_area * lenght_area / 3;
        while (num_trap + size_team_A + size_team_B > lenght_area * lenght_area)
            num_trap--;

        this->set_trap = new Trap * [num_trap];
        for (int i = 0; i < num_trap; i++)
            this->set_trap[i] = new Trap(1);

        this->team_A = new Creature*[size_team_A];
        this->team_A[0] = new Creature("Wolf");
        this->team_A[1] = new Creature("Wolf");
        this->team_A[2] = new Creature("Wolf");
        this->team_A[3] = new Creature("Wolf");
        this->team_A[4] = new Creature("Bear");

        this->team_B = new Creature*[size_team_B];
        this->team_B[0] = new Creature("Barbarian");
        this->team_B[1] = new Creature("Barbarian");
        this->team_B[2] = new Creature("Ranger");
        this->team_B[3] = new Creature("Ranger");

        fill_area_empty();
        put_trap(set_trap, num_trap);
        put_team(0, team_A, size_team_A);
        put_team(lenght_area-1, team_B, size_team_B);
    }

    int get_num_trap() {
        return num_trap;
    }

    /*
     * Заполнение пустого поля
     *
     * Заполняет поля символами, означающими пустоту
     */
    void fill_area_empty() {
        for (int i = 0; i < lenght_area; i++) {
            for (int k = 0; k < lenght_area; k++) area[i][k] = lit_empty;
        } 
    }

    /*
     * Вывод поля
     *
     * Выводит сетку поля в консоль
     */
    void print_area() {
        for (int i = 0; i < lenght_area; i++) {
            for (int k = 0; k < lenght_area; k++) 
                cout << area[i][k] << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    // (new)
    void put_trap(Trap** set_trap, int num_trap) {
        int current_num_trap = 0;
        while(current_num_trap < num_trap) {
            int x = rand() % lenght_area;
            int y = rand() % lenght_area;

            if (area[x][y] == lit_empty) {
                area[x][y] = set_trap[current_num_trap]->get_lit();
                set_trap[current_num_trap]->set_coord(x, y);
                current_num_trap++;
            }
        }
    }


    /*
     * Выставление существ на поле
     *
     * @param column колонка, на которой начинается выставление
     * @param team команда, которую выставляют
     * @param size_team размер команды
     * Выставляет существ на поле
     */
    void put_team(int column, Creature** team, int size_team) {
        int creature_on_area = 0;
        int direction;

        if (column == 0) direction = 1;
        else direction = -1;

        while (creature_on_area < size_team) {
            if (creature_on_column(column) == lenght_area) column += direction;

            int line = rand() % lenght_area;
            if (area[line][column] == lit_empty) {
                area[line][column] = team[creature_on_area]->get_lit();
                team[creature_on_area]->set_coord(line, column);
                creature_on_area++;
            }
        }
    }

    /*
     * Подсчёт количества существ в колонке
     *
     * @param column номер колонки, которую проверяют
     * Возвращает количество существ в колонке
     */
    int creature_on_column(int column) {
        int num_creature = 0;

        for (int i = 0; i < lenght_area; i++) {
            if (area[i][column] != lit_empty) num_creature++;
        }

        return num_creature;
    }

    /*
     * Размер команды А
     *
     * Возвращает количество существ в команде А
     */
    int get_size_team_A() {
        return size_team_A;
    }

    /*
     * Размер команды В
     *
     * Возвращает количество существ в команде В
     */
    int get_size_team_B() {
        return size_team_B;
    }

    /*
     * Заполнение координаты символом пустоты
     *
     * @param x координата х
     * @param y координата у
     * Заполненяет координату символом пустоты
     */
    void fill_coord_empty(int x, int y) {
        area[x][y] = '.';
    }

    /*
     * Заполнение координаты символом существа
     *
     * @param x координата х
     * @param y координата у
     * @param lit символ существа
     * Заполненяет координату символом существа
     */
    void fill_coord_lit(int x, int y, char lit) {
        area[x][y] = lit;
    }

    // (!) отрицательные х у
    /*
     * Получение символа в координате
     *
     * @param x координата х
     * @param y координата у
     * Возвращает символ из указанной координаты
     */
    char get_lit(int x, int y) {
        return area[x][y];
    }


};

void fill_creature_list(Creature**, Creature**, int, Creature**, int);
void print_creature_list(Creature**, int);
void sort_creature_by_initiative(Creature**, int);
int num_alive(Creature**, int);
Creature* find_enemy_around(Creature*, Creature**, int);
Creature* find_enemy_nearby(Creature*, Creature**, int, int);
bool exist_long_range(Creature*);
Weapon* weapon_selection(Creature*, string);
void attack(Creature* plyer, Creature*, string);
double calc_distance(int , int , int , int );
Creature* go_to_enemy(Creature* , Creature*, Creature**, int, Area* );
void print_alive_creature(Creature** , int , int );
void print_alive_creature_statistic(Creature** , int );
Trap* find_trap(int , int, Trap** , int );

int main()
{
    srand(time(NULL));
    
    // (new)
    const int area_lenght = 10;

    Area* new_area;
    new_area = new Area(area_lenght);
    new_area->print_area();

    int num_creature;
    num_creature = new_area->get_size_team_A() + new_area->get_size_team_B();

    Creature** creature_list;
    creature_list = new Creature*[num_creature];

    fill_creature_list(creature_list, new_area->team_A,  new_area->get_size_team_A(), new_area->team_B, new_area->get_size_team_B());

    print_creature_list(creature_list, num_creature);

    sort_creature_by_initiative(creature_list, num_creature);
    cout << "\nSORTED:" << endl;
    print_creature_list(creature_list, num_creature);
    print_alive_creature_statistic(creature_list, num_creature);

    int num_step = 1;
    int list_step = 0;

    while (num_alive(new_area->team_A, new_area->get_size_team_A()) > 0 and num_alive(new_area->team_B, new_area->get_size_team_B()) > 0) {

        if (list_step == num_creature)
            list_step = 0;

        Creature* player;
        Creature* enemy;
        Creature** enemy_team;
        int size_enemy_team;

        player = creature_list[list_step];

        // Пропуск, если мёртвый
        if (player->get_hp() <= 0) {
            list_step++;
            continue;
        } 

        cout << "--- STEP " << num_step << " ---  ";
        print_alive_creature(creature_list, num_creature, list_step);

        // Определение вражеской команды
        if (player->get_lit() == 'R' or player->get_lit() == 'T') {
            enemy_team = new_area->team_A;
            size_enemy_team = new_area->get_size_team_A();
        }
        else {
            enemy_team = new_area->team_B;
            size_enemy_team = new_area->get_size_team_B();
        }

        // 1. ENEMY AROUND
        // Поиск врага вокруг
        enemy = find_enemy_around(player, enemy_team, size_enemy_team);

        // Атака врага поблизости
        if (player != enemy) {
            attack(player, enemy, "melee");

            // Если враг умер, он исчезает с карты
            if (enemy->get_hp() <= 0) {
                cout << enemy->get_name() << " (" << enemy->get_coord()[0] << ", " << enemy->get_coord()[1] << ") is died! " << endl;
                new_area->fill_coord_empty(enemy->get_coord()[0], enemy->get_coord()[1]);
                enemy->set_coord(-100, -100);
            }

            list_step++;
            num_step++;
            new_area->print_area();

            continue;
        }

        // 2. LONG_RANGE
        // Если лучник
        if (exist_long_range(player)) {
            // Поиск ближайшего врага
            enemy = find_enemy_nearby(player, enemy_team, size_enemy_team, area_lenght);

            if (player != enemy) {
                attack(player, enemy, "long-range");

                // Если враг умер, он исчезает с карты
                if (enemy->get_hp() <= 0) {
                    cout << enemy->get_name() << " (" << enemy->get_coord()[0] << ", " << enemy->get_coord()[1] << ") is died! " << endl;
                    new_area->fill_coord_empty(enemy->get_coord()[0], enemy->get_coord()[1]);
                    enemy->set_coord(-100, -100);
                }

                list_step++;
                num_step++;
                new_area->print_area();

                continue;
            }
        }

        // 3. GO TO ENEMY AND FIGHT
        enemy = go_to_enemy(player, find_enemy_nearby(player, enemy_team, size_enemy_team, area_lenght), enemy_team, size_enemy_team, new_area);
        if (player != enemy) {
            attack(player, enemy, "melee");

            // Если враг умер, он исчезает с карты
            if (enemy->get_hp() <= 0) {
                cout << enemy->get_name() << " (" << enemy->get_coord()[0] << ", " << enemy->get_coord()[1] << ") is died! " << endl;
                new_area->fill_coord_empty(enemy->get_coord()[0], enemy->get_coord()[1]);
                enemy->set_coord(-100, -100);
            }

            list_step++;
            num_step++;
            new_area->print_area();

            continue;
        }

        list_step++;
        num_step++;
        new_area->print_area();     
    }

    if (num_alive(new_area->team_A, new_area->get_size_team_A()) > 0)
        cout << "\n team_A is won!" << endl;
    else
        cout << "\n team_B is won!" << endl;

    print_alive_creature_statistic(creature_list, num_creature);




    //cin.ignore();
}


/*
 * Заполнения листа существ
 *
 * @param creature_list ссылка на массив всех существ на поле
 * @param team_A ссылка на массив существ команды А
 * @param size_team_A размер команды А
 * @param team_B ссылка на массив существ команды В
 * @param size_team_B размер команды В
 * Заполняет лист существ всеми существами из указанных команд
 */
void fill_creature_list(Creature** creature_list, Creature** team_A, int size_team_A, Creature** team_B, int size_team_B) {
    for (int i = 0; i < size_team_A; i++) 
        creature_list[i] = team_A[i];
    
    for (int i = size_team_A; i < (size_team_A + size_team_B); i++)
        creature_list[i] = team_B[i - size_team_A];
}

/*
 * Вывод листа существ
 *
 * @param creature_list ссылка на массив всех существ на поле
 * @param num_creature количество всех существ
 * Выводит последовательность символов = последовательность существ в листе существ
 */
void print_creature_list(Creature** creature_list, int num_creature) {
    for (int i = 0; i < num_creature; i++) {
        if (creature_list[i]->get_hp() > 0)
            cout << creature_list[i]->get_lit() << " ";
    }
    cout << "\n" << endl;
}

/*
 * Сортировка по инициативе
 *
 * @param creature_list ссылка на массив всех существ на поле
 * @param lenght количество всех существ в листе
 * Сортирует лист существ по очкам инициативы в порядке убывания
 */
void sort_creature_by_initiative(Creature** creature_list, int lenght) {
    for (int i = 0; i < lenght; i++) {
        for (int k = 0; k < lenght - 1; k++) {
            if (creature_list[k]->get_initiative() < creature_list[k + 1]->get_initiative()) {
                Creature* jail = creature_list[k];
                creature_list[k] = creature_list[k + 1];
                creature_list[k + 1] = jail;
            }
        }
    }
}

/*
 * Количество живых существ в команде
 *
 * @param team ссылка на массив существ команды
 * @param size_team количество всех существ в команде
 * Возвращает количество живых существ в команде
 */
int num_alive(Creature** team, int size_team) {
    int num_alive = 0;

    for (int i = 0; i < size_team; i++) {
        if (team[i]->get_hp() > 0)
            num_alive++;
    }

    return num_alive;
}

/*
 * Поиск врага вокруг
 *
 * @param player ссылка на объект существа текущего игрока
 * @param enemy_team ссылка на массив существ вражеской команды
 * @param size_enemy_team количество всех существ во вражеской команде
 * Возвращает ссылку на объект врага, если он стоит в одной клетке от игрока
 * Если врага поблизости нет, возвращается ссылка на объект существа игрока
 */
Creature* find_enemy_around(Creature* player, Creature** enemy_team, int size_enemy_team) {
    
    for (int i = 0; i < size_enemy_team; i++) {
        if (enemy_team[i]->get_hp() > 0) {
            
            if ((player->get_coord()[0] - 1 == enemy_team[i]->get_coord()[0] and
                player->get_coord()[1] - 1 == enemy_team[i]->get_coord()[1]) or

                (player->get_coord()[0] - 1 == enemy_team[i]->get_coord()[0] and
                    player->get_coord()[1] + 0 == enemy_team[i]->get_coord()[1]) or

                (player->get_coord()[0] - 1 == enemy_team[i]->get_coord()[0] and
                    player->get_coord()[1] + 1 == enemy_team[i]->get_coord()[1]) or

                (player->get_coord()[0] + 1 == enemy_team[i]->get_coord()[0] and
                    player->get_coord()[1] - 1 == enemy_team[i]->get_coord()[1]) or

                (player->get_coord()[0] + 1 == enemy_team[i]->get_coord()[0] and
                    player->get_coord()[1] + 0 == enemy_team[i]->get_coord()[1]) or

                (player->get_coord()[0] + 1 == enemy_team[i]->get_coord()[0] and
                    player->get_coord()[1] + 1 == enemy_team[i]->get_coord()[1]) or

                (player->get_coord()[0] - 1 == enemy_team[i]->get_coord()[0] and
                    player->get_coord()[1] - 1 == enemy_team[i]->get_coord()[1]) or

                (player->get_coord()[0] - 0 == enemy_team[i]->get_coord()[0] and
                    player->get_coord()[1] - 1 == enemy_team[i]->get_coord()[1]) or

                (player->get_coord()[0] + 0 == enemy_team[i]->get_coord()[0] and
                    player->get_coord()[1] + 1 == enemy_team[i]->get_coord()[1])
                )
                return enemy_team[i];
        }
    }
    return player;
}

/*
 * Поиск ближайшего врага
 *
 * @param player ссылка на объект существа текущего игрока
 * @param enemy_team ссылка на массив существ вражеской команды
 * @param size_enemy_team количество всех существ во вражеской команде
 * Возвращает ссылку на объект врага, который находится ближе всех к игроку
 * Если врага поблизости нет, возвращается ссылка на объект существа игрока
 */
Creature* find_enemy_nearby(Creature* player, Creature** enemy_team, int size_enemy_team, int area_length) {
    Creature* nearest_enemy = player;
    
    // (new)
    double min_distance = calc_distance(0, 0, area_length - 1, area_length - 1);

    for (int i = 0; i < size_enemy_team; i++) {
        if (enemy_team[i]->get_hp() > 0) {

            double distance = calc_distance(enemy_team[i]->get_coord()[0], enemy_team[i]->get_coord()[1],
                player->get_coord()[0], player->get_coord()[1]);

            if (distance < min_distance) {
                min_distance = distance;
                nearest_enemy = enemy_team[i];
            }
        }
    }

    return nearest_enemy;
}

/*
 * Атака врага
 *
 * @param player ссылка на объект существа текущего игрока
 * @param enemy ссылка на объект существа вражеской команды
 * @param attack_type тип атака
 * Наносит урон врагу выбранной атакой и выводит сообщение в консоль
 */
void attack(Creature* player, Creature* enemy, string attack_type) {
    Weapon* weapon;
    
    weapon = weapon_selection(player, attack_type);

    if ((dice_roll(1, 20) + player->get_attack_bonus()) >= enemy->get_armor_class()) {
        int damage;

        damage = weapon->attack();
            
        enemy->take_damage(damage);

        cout << player->get_name() << " (" << player->get_coord()[0] << ", " << player->get_coord()[1] << ") ";
        cout << "SUCCESSFULLY attacked by " << weapon->get_name() << " the ";
        cout << enemy->get_name() << " (" << enemy->get_coord()[0] << ", " << enemy->get_coord()[1] << ") " << endl;

        cout << enemy->get_name() << " (" << enemy->get_coord()[0] << ", " << enemy->get_coord()[1] << ") ";
        cout << "GOT DAMAGE (" << damage << ") \n" << endl;
    }
    else {
        cout << player->get_name() << " (" << player->get_coord()[0] << ", " << player->get_coord()[1] << ") ";
        cout << "UNSUCCESSFULLY attacked by " << weapon->get_name() << " the ";
        cout << enemy->get_name() << " (" << enemy->get_coord()[0] << ", " << enemy->get_coord()[1] << ") \n " << endl;
    }
}

/*
 * Проверка наличия оружия дальнего боя
 *
 * @param player ссылка на объект существа текущего игрока
 * Возвращает true, если у существа игрока есть в наличии оружие дальнего боя, и false, если нет
 */
bool exist_long_range(Creature* player) {
    for (int i = 0; i < player->get_size_weapons_set(); i++) {
        if (player->get_weapons_set()[i]->get_type() == "long-range")
            return true;
    }
    return false;
}

/*
 * Выбор оружия для атаки
 *
 * @param player ссылка на объект существа текущего игрока
 * @param attack_type тип оружия
 * Выбирает оружие исходя из указанного типа
 * Возвращает ссылку на объект выбранного оружия
 */
Weapon* weapon_selection(Creature* player, string attack_type) {
    for (int i = 0; i < player->get_size_weapons_set(); i++) {
        if (player->get_weapons_set()[i]->get_type() == attack_type)
            return player->get_weapons_set()[i];
    }
}

/*
 * Расчёт дистанции до врага
 *
 * @param x_1 координата х первого существа
 * @param y_1 координата у первого существа
 * @param x_2 координата х второго существа
 * @param y_2 координата у второго существа
 * Возвращает расстояние между двумя координатами
 */
double calc_distance(int x_1, int y_1, int x_2, int y_2) {
    int abs_x = abs(x_1 - x_2);
    int abs_y = abs(y_1 - y_2);
    double distance = sqrt(abs_x * abs_x + abs_y * abs_y);

    return distance;
}

Trap* find_trap(int x, int y, Trap** set_trap, int num_trap) {  
    for (int i = 0; i < num_trap; i++) {
        if (set_trap[i]->get_coord()[0] == x and set_trap[i]->get_coord()[1] == y)
            return set_trap[i];
    }
}

/*
 * Передвижение до врага
 *
 * @param player ссылка на объект существа текущего игрока
 * @param enemy ссылка на объект вражеского существа
 * @param enemy_team ссылка на массив существ вражеской команды
 * @param size_enemy_team количество всех существ во вражеской команде
 * @param area ссылка на объект поля
 * Перемещает существа в сторону ближайшего врага
 * Если враг вокруг, возвращает ссылку на объект врага 
 * Если вокруг нет врагов, возвращает ссылку на текущего игрока
 */
Creature* go_to_enemy(Creature* player, Creature* enemy, Creature** enemy_team, int size_enemy_team, Area* area) {

    double distance;
    int enemy_x = enemy->get_coord()[0];
    int enemy_y = enemy->get_coord()[1];
    int player_x = player->get_coord()[0];
    int player_y = player->get_coord()[1];
    int num_step = 0;

    cout << player->get_name() << " (" << player->get_coord()[0] << ", " << player->get_coord()[1] << ") ";
    cout << "MOVED to ";

    distance = calc_distance(enemy_x, enemy_y, player_x, player_y);

    for (int i = 0; i < player->get_speed(); i++) {
        // Если по пути найдёт врага, то передвижение завершено
        if (find_enemy_around(player, enemy_team, size_enemy_team) != player)
            break;

        distance = calc_distance(enemy_x, enemy_y, player_x, player_y);
        
        // UP
        if ((calc_distance(enemy_x, enemy_y, player_x + 1, player_y) < distance) and ((area->get_lit(player_x + 1, player_y) == '.') or (area->get_lit(player_x + 1, player_y) == '#'))) {
            player_x = player_x + 1;
            if (area->get_lit(player_x, player_y) == '#') {
                Trap* trap = find_trap(player_x, player_y, area->set_trap, area->get_num_trap());
                
                trap->set_coord(-100, -100);

                int damage = trap->trap_work(player->get_speed());
                player->take_damage(damage);
                cout << "[" << "trap (" << damage << ")] ";
            }
        }
           
        // DOWN
        else if ((calc_distance(enemy_x, enemy_y, player_x - 1, player_y) < distance) and ((area->get_lit(player_x - 1, player_y) == '.') or (area->get_lit(player_x - 1, player_y) == '#'))) {
            player_x = player_x - 1;
            if (area->get_lit(player_x, player_y) == '#') {
                Trap* trap = find_trap(player_x, player_y, area->set_trap, area->get_num_trap());

                trap->set_coord(-100, -100);

                int damage = trap->trap_work(player->get_speed());
                player->take_damage(damage);
                cout << "[" << "trap (" << damage << ")] ";
            }
        }
            
        // LEFT
        else if ((calc_distance(enemy_x, enemy_y, player_x, player_y - 1) < distance) and ((area->get_lit(player_x, player_y - 1) == '.') or (area->get_lit(player_x, player_y - 1) == '#'))) {
            player_y = player_y - 1;
            if (area->get_lit(player_x, player_y) == '#') {
                Trap* trap = find_trap(player_x, player_y, area->set_trap, area->get_num_trap());

                trap->set_coord(-100, -100);

                int damage = trap->trap_work(player->get_speed());
                player->take_damage(damage);
                cout << "[" << "trap (" << damage << ")] ";
            }
        }
            
        // RIGHT
        else if ((calc_distance(enemy_x, enemy_y, player_x, player_y + 1) < distance) and ((area->get_lit(player_x, player_y + 1) == '.') or (area->get_lit(player_x, player_y + 1) == '#'))) {
            player_y = player_y + 1;   
            if (area->get_lit(player_x, player_y) == '#') {
                Trap* trap = find_trap(player_x, player_y, area->set_trap, area->get_num_trap());

                trap->set_coord(-100, -100);

                int damage = trap->trap_work(player->get_speed());
                player->take_damage(damage);
                cout << "[" << "trap (" << damage << ")] ";
            }
        }
               

        // Обход препятствий (простой)
        // D on RIGHT into UP
        else if (
            (enemy_x > player_x) and
            (player->get_speed() - i >= 2) and
            (area->get_lit(player_x + 1, player_y) != '.') and
            (area->get_lit(player_x, player_y + 1) == '.') and
            (area->get_lit(player_x + 1, player_y + 1) == '.')) {
            cout << "[bypass]";
            player_x = player_x + 1;
            player_y = player_y + 1;
            
            i = i + 1;
        }
        // D on RIGHT into DOWN
        else if (
            (enemy_x > player_x) and
            (player->get_speed() - i >= 2) and
            (area->get_lit(player_x + 1, player_y) != '.') and
            (area->get_lit(player_x, player_y - 1) == '.') and
            (area->get_lit(player_x + 1, player_y - 1) == '.')) {
            cout << "[bypass]";
            player_x = player_x + 1;
            player_y = player_y - 1;
            i = i + 1;
        }
        // D on LEFT into UP
        else if (
            (enemy_x < player_x) and
            (player->get_speed() - i >= 2) and
            (area->get_lit(player_x - 1, player_y) != '.') and
            (area->get_lit(player_x, player_y + 1) == '.') and
            (area->get_lit(player_x - 1, player_y + 1) == '.')) {
            cout << "[bypass]";
            player_x = player_x - 1;
            player_y = player_y + 1;
            i = i + 1;
        }
        // D on LEFT into DOWN
        else if (
            (enemy_x < player_x) and
            (player->get_speed() - i >= 2) and
            (area->get_lit(player_x - 1, player_y) != '.') and
            (area->get_lit(player_x, player_y - 1) == '.') and
            (area->get_lit(player_x - 1, player_y - 1) == '.')) {
            cout << "[bypass]";
            player_x = player_x - 1;
            player_y = player_y - 1;
            i = i + 1;
        }
        // D on UP into RIGHT
        else if (
            (enemy_y > player_y) and
            (player->get_speed() - i >= 2) and
            (area->get_lit(player_x, player_y + 1) != '.') and
            (area->get_lit(player_x + 1, player_y) == '.') and
            (area->get_lit(player_x + 1, player_y + 1) == '.')) {
            cout << "[bypass]";
            player_x = player_x + 1;
            player_y = player_y + 1;
            i = i + 1;
        }
        // D on UP into LEFT
        else if (
            (enemy_y > player_y) and
            (player->get_speed() - i >= 2) and
            (area->get_lit(player_x, player_y + 1) != '.') and
            (area->get_lit(player_x - 1, player_y) == '.') and
            (area->get_lit(player_x - 1, player_y + 1) == '.')) {
            cout << "[bypass]";
            player_x = player_x - 1;
            player_y = player_y + 1;
            i = i + 1;
        }
        // D on DOWN into RIGHT
        else if (
            (enemy_y < player_y) and
            (player->get_speed() - i >= 2) and
            (area->get_lit(player_x, player_y - 1) != '.') and
            (area->get_lit(player_x + 1, player_y) == '.') and
            (area->get_lit(player_x + 1, player_y - 1) == '.')) {
            cout << "[bypass]";
            player_x = player_x + 1;
            player_y = player_y - 1;
            i = i + 1;
        }
        // D on DOWN into LEFT
        else if (
            (enemy_y < player_y) and
            (player->get_speed() - i >= 2) and
            (area->get_lit(player_x, player_y - 1) != '.') and
            (area->get_lit(player_x - 1, player_y) == '.') and
            (area->get_lit(player_x - 1, player_y - 1) == '.')) {
            cout << "[bypass]";
            player_x = player_x - 1;
            player_y = player_y - 1;
            i = i + 1;
        }
        
        area->fill_coord_empty(player->get_coord()[0], player->get_coord()[1]);
        player->set_coord(player_x, player_y);
        area->fill_coord_lit(player->get_coord()[0], player->get_coord()[1], player->get_lit());
    }
    cout << "(" << player->get_coord()[0] << ", " << player->get_coord()[1] << ") \n" << endl;

    return find_enemy_around(player, enemy_team, size_enemy_team);
}

/*
 * Вывод живых существ по инициативе
 *
 * @param creature_list ссылка на массив всех существ на поле
 * @param num_creature количество всех существ в листе
 * @param current_player номер текущего игрока в списке
 * Выводит лист инициативы с выделением текущего игрока
 */
void print_alive_creature(Creature** creature_list, int num_creature, int current_player) {
    for (int i = 0; i < num_creature; i++) {
        if (creature_list[i]->get_hp() > 0) {
            if (current_player == i)
                cout << "[";
            cout << creature_list[i]->get_lit();
            if (current_player == i)
                cout << "]";
            cout<< " ";
        }   
    }
    cout << "\n";
}

/*
 * Вывод статистики по живым существам
 *
 * @param creature_list ссылка на массив всех существ на поле
 * @param num_creature количество всех существ в листе
 * Выводит статистику существ находящихся в живых
 */
void print_alive_creature_statistic(Creature** creature_list, int num_creature) {
    cout << "--- STATISTIC ---\n" << endl;

    for (int i = 0; i < num_creature; i++) {
        if (creature_list[i]->get_hp() > 0) {
            cout << "Name: " << creature_list[i]->get_name() << endl;
            cout << "HP: " << creature_list[i]->get_hp() << endl;
            cout << "Initiative: " << creature_list[i]->get_initiative() << endl;
            cout << "\n";
        }
    }
}

/*
 * Бросок кубиков
 *
 * @param num_roll количество бросков
 * @param num_faces количество сторон кубика
 * Возвращает сумму выпавших значений
 */
int dice_roll(int num_roll, int num_faces) {
    int sum = 0;

    for (int i = 0; i < num_roll; i++) {
        sum += rand() % num_faces + 1;
    }

    return sum;
}