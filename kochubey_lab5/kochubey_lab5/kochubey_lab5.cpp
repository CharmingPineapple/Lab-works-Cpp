// kochubey_lab5.cpp 

#include <iostream>
#include <stdlib.h>
using namespace std;

class Spare_Part {
private:


public:
    int replacement_cost;
    int repair_cost;
    int repair_time;
    int service_life;
    double worn;

    string def_breakage;
    string work_type;

    int get_replacement_cost() {
        return replacement_cost;
    }
    int get_repair_cost() {
        return repair_cost;
    }

    Spare_Part() {

    }

    Spare_Part(int repl_cost, int rep_cost, int rep_time, int serv_life, int worn) {
        this->replacement_cost = repl_cost;
        this->repair_cost = repl_cost;
        this->repair_time = rep_time;
        this->service_life = serv_life;
        this->worn = worn;
    }
};

class Shaft : Spare_Part {
private:
    int worn_resist = 20;
public:
    int def_breakage() {
        // 0.15%
        if (rand() % 2000 < 3)
            return repair_time;
        return 0;
    }
    int def_full_breakage() {
        if (worn >= 100)
            return 4;
        if (service_life <= 0)
            return 4;
        return 0;
    }
    int get_replacement_cost() {
        return replacement_cost;
    }
    int get_repair_cost() {
        return repair_cost;
    }
    void work(int intensity) {
        worn += (double) intensity/ worn_resist;
        service_life--;
    }
    Shaft(int repl_cost, int rep_cost, int rep_time, int serv_life, int worn) {
        this->replacement_cost = repl_cost;
        this->repair_cost = repl_cost;
        this->repair_time = rep_time;
        this->service_life = serv_life;
        this->worn = worn;
    }

};

class Electric_Motor : Spare_Part {
private:
    int worn_resist = 15;
public:
    int def_breakage() {
        // 0.3%
        if (rand() % 1000 < 3)
            return repair_time;
        return 0;
    }
    int def_full_breakage() {
        if (worn >= 100)
            return 4;
        if (service_life <= 0)
            return 4;
        return 0;
    }
    int get_replacement_cost() {
        return replacement_cost;
    }
    int get_repair_cost() {
        return repair_cost;
    }
    void work(int intensity) {
        worn += (double)intensity / worn_resist;
        service_life--;
    }
    Electric_Motor(int repl_cost, int rep_cost, int rep_time, int serv_life, int worn) {
        this->replacement_cost = repl_cost;
        this->repair_cost = repl_cost;
        this->repair_time = rep_time;
        this->service_life = serv_life;
        this->worn = worn;
    }
};

class Control_Panel : Spare_Part {
private:
    int worn_resist = 20;
public:
    int def_breakage() {
        // 0.5%
        if (rand() % 200 < 1)
            return repair_time;
        return 0;
    }
    int def_full_breakage() {
        if (worn >= 100)
            return 4;
        if (service_life <= 0)
            return 4;
        return 0;
    }
    int get_replacement_cost() {
        return replacement_cost;
    }
    int get_repair_cost() {
        return repair_cost;
    }
    void work(int intensity) {
        worn += (double)intensity / worn_resist;
        service_life--;
    }
    Control_Panel(int repl_cost, int rep_cost, int rep_time, int serv_life, int worn) {
        this->replacement_cost = repl_cost;
        this->repair_cost = repl_cost;
        this->repair_time = rep_time;
        this->service_life = serv_life;
        this->worn = worn;
    }

};

class Cutting_Head : Spare_Part {
private:
    int worn_resist = 10;
public:
    int def_breakage() {
        // 0.1%
        if (rand()%1000 < 1)
            return repair_time;
        return 0;
    }
    int def_full_breakage() {
        if (worn >= 100)
            return 4;
        if (service_life <= 0)
            return 4;
        return 0;
    }
    int get_replacement_cost() {
        return replacement_cost;
    }
    int get_repair_cost() {
        return repair_cost;
    }
    void work(int intensity) {
        worn += (double)intensity / worn_resist;
        service_life--;
    }
    Cutting_Head(int repl_cost, int rep_cost, int rep_time, int serv_life, int worn) {
        this->replacement_cost = repl_cost;
        this->repair_cost = repl_cost;
        this->repair_time = rep_time;
        this->service_life = serv_life;
        this->worn = worn;
    }
};

class Machine {
private:
    int num_parts;
    // простой
    int downtime;
    // количество заменённых частей
    int replaced_parts;
    // общая стоимость ремонта
    int repair_cost;
    // количество поломок
    int num_breakdown;
    int service_time;

public:
    
    void** spare_parts;
    string* parts_types;
    
    void set_num_parts(int num) {
        this->num_parts = num;
    }
    int get_num_parts() {
        return num_parts;
    }
    void plus_downtime(int time) {
        downtime += time;
    }
    int get_downtime() {
        return downtime;
    }
    void plus_replaced_parts() {
        replaced_parts += 1;
    }
    int get_replaced_parts() {
        return replaced_parts;
    }
    void plus_repair_cost(int cost) {
        repair_cost += cost;
    }
    int get_repair_cost() {
        return repair_cost;
    }
    void plus_breakdown() {
        num_breakdown += 1;
    }
    int get_num_breakdown() {
        return num_breakdown;
    }
    void set_service_time(int time) {
        this->service_time = time;
    }
    void minus_service_time() {
        service_time--;
    }
    int get_service_time() {
        return service_time;
    }

    Machine() {
        this->downtime = 0;
        this->replaced_parts = 0;
        this->repair_cost = 0;
        this->num_breakdown = 0;
        this->service_time = 0;
    }
};


void generation_machine(Machine*);
void machine_work(Machine*, int, int);
void machine_get_worn(Machine*, int);
void machine_service(Machine*);
void print_statistic(Machine*, int);

int main()
{
    srand(time(NULL));

    int answer;
    Machine* machine_array;


    cout << "What type of work do you want to see?" << endl;
    cout << "1.The machine works during the specified time." << endl;
    cout << "2.Simulation of the workshop operation for one year." << endl;
    cout << "Your answer: ";
    cin >> answer;

    if (answer == 1) {
        int num_hours;
        int intensity;

        machine_array = new Machine[1];
        machine_array[0] = Machine();

        cout << "Enter numbers of hours of machine work:";
        cin >> num_hours;
        cout << "Enter intensity of machine work: ";
        cin >> intensity;

        generation_machine(&machine_array[0]);
        //cout << "---test---" << machine_array[0].get_num_parts() << endl;
        machine_work(&machine_array[0], num_hours, intensity);
        
        print_statistic(machine_array, 1);
    }
    else if (answer == 2) {
        int num_machine;

        cout << "Enter number of machine in workshop:";
        cin >> num_machine;
        machine_array = new Machine[num_machine];

        for (int i = 0;i < num_machine;i++) {
            machine_array[i] = Machine();
            generation_machine(&machine_array[i]);
        }
        
        for (int i = 0;i < 12;i++) {
            int intensity = rand() % 5 + 1;

            for (int k = 0; k < num_machine;k++) {
                machine_work(&machine_array[k], 12 * 30, intensity);
            }         
        }

        print_statistic(machine_array, num_machine);
    }

}

/*
 * Генерация станка
 *
 * @param machine объект станка
 * Заполнение массива частей станка случайными частями
*  со случайными значениями параметров
 */
void generation_machine(Machine* machine) {
    int num_parts;

    num_parts = rand() % 5 + 2;

    machine->set_num_parts(num_parts);
    //cout << "---test2---" << machine->get_num_parts() << endl;
    machine->spare_parts = new void*[num_parts];
    machine->parts_types = new string[num_parts];

    for (int i = 0; i < num_parts; i++) {
        switch (rand()%4)
        {
        case 0:
            // replacement_cost: 1.000-10.000; repair_cost: 500-4.000, repair_time: 1-4; service_life: 500-1500; worn: 0-79
            machine->spare_parts[i] = new Shaft(rand()%9001+1000, rand()%3501+500,  rand()%4+1, rand()%1001+500, rand() % 80);
            machine->parts_types[i] = "Shaft";
            break;
        case 1:
            machine->spare_parts[i] = new Electric_Motor(rand() % 9001 + 1000, rand() % 3501 + 500, rand() % 4 + 1, rand() % 1001 + 500, rand() % 80);
            machine->parts_types[i] = "Electric_Motor";
            break;
        case 2:
            machine->spare_parts[i] = new Control_Panel(rand() % 9001 + 1000, rand() % 3501 + 500, rand() % 4 + 1, rand() % 1001 + 500, rand() % 80);
            machine->parts_types[i] = "Control_Panel";
            break;
        case 3:
            machine->spare_parts[i] = new Cutting_Head(rand() % 9001 + 1000, rand() % 3501 + 500, rand() % 4 + 1, rand() % 1001 + 500, rand() % 80);
            machine->parts_types[i] = "Cutting_Head";
            break;
        }
    }

    //cout << "---test3---" << machine->parts_types[1] << endl;
}

/*
 * Моделирование работы станка
 *
 * @param machine объект станка
 * @param time количество часов, в течение которых работает станок
 * @param intensity интенсивность работы станка
 * Каждый час выполняются методы machine_get_worn и machine_service
 * Если станок ремонтируется, выполняется метод minus_service_time
 */
void machine_work(Machine* machine, int time, int intensity) {

    for (int i = 0; i < time; i++) {
        
        if (machine->get_service_time() > 0)
            machine->minus_service_time();
        else {
            machine_get_worn(machine, intensity);
            machine_service(machine);   
        }
        
    }
}

/*
 * Моделирование работы станка в течении часа
 *
 * @param machine объект станка
 * @param intensity интенсивность работы станка
 * Прохождение по массиву частей станка,
 * увеличение их изношенности и уменьшение срока службы через метод work
 */
void machine_get_worn(Machine* machine, int intensity) {
    for (int i = 0; i < machine->get_num_parts(); i++) {
        string type = machine->parts_types[i];

        if (type == "Shaft") {
            ((Shaft*)machine->spare_parts[i])->work(intensity);
        }
        if (type == "Electric_Motor") {
            ((Electric_Motor*)machine->spare_parts[i])->work(intensity);
        }
        if (type == "Control_Panel") {
            ((Control_Panel*)machine->spare_parts[i])->work(intensity);
        }
        if (type == "Cutting_Head") {
            ((Cutting_Head*)machine->spare_parts[i])->work(intensity);
        }
    }
}

/*
 * Обслуживание станка
 *
 * @param machine объект станка
 * Прохождение по массиву частей станка
 * и проверка на наличие поломок или полных поломок частей станка
 */
void machine_service(Machine* machine) {
    int service_time = 0;
    int service_cost = 0;
    
    for (int i = 0; i < machine->get_num_parts(); i++) {
        string type = machine->parts_types[i];
        int repair_time=0;

        if (type == "Shaft") {
            if (((Shaft*)machine->spare_parts[i])->def_full_breakage() > 0) {
                repair_time = 4;

                ((Shaft*)machine->spare_parts[i])->get_replacement_cost();

                machine->plus_replaced_parts();
                machine->plus_repair_cost(((Shaft*)machine->spare_parts[i])->get_replacement_cost());
                machine->spare_parts[i] = new Shaft(rand() % 9001 + 1000, rand() % 3501 + 500, rand() % 4 + 1, rand() % 1851 + 150, rand() % 100);
            }
            else if (((Shaft*)machine->spare_parts[i])->def_breakage() > 0) {
                repair_time = ((Shaft*)machine->spare_parts[i])->def_breakage();

                machine->plus_breakdown();
                machine->plus_repair_cost(((Shaft*)machine->spare_parts[i])->get_repair_cost());
            }
                
        }

        else if (type == "Electric_Motor") {
            if (((Electric_Motor*)machine->spare_parts[i])->def_full_breakage() > 0) {
                repair_time = 4;

                ((Electric_Motor*)machine->spare_parts[i])->get_replacement_cost();

                machine->plus_replaced_parts();
                machine->plus_repair_cost(((Electric_Motor*)machine->spare_parts[i])->get_replacement_cost());
                machine->spare_parts[i] = new Electric_Motor(rand() % 9001 + 1000, rand() % 3501 + 500, rand() % 4 + 1, rand() % 1851 + 150, rand() % 100);
            }
            else if (((Electric_Motor*)machine->spare_parts[i])->def_breakage() > 0) {
                repair_time = ((Electric_Motor*)machine->spare_parts[i])->def_breakage();

                machine->plus_breakdown();
                machine->plus_repair_cost(((Electric_Motor*)machine->spare_parts[i])->get_repair_cost());
            }
        }

        else if (type == "Control_Panel") {
            if (((Control_Panel*)machine->spare_parts[i])->def_full_breakage() > 0) {
                repair_time = 4;

                ((Control_Panel*)machine->spare_parts[i])->get_replacement_cost();

                machine->plus_replaced_parts();
                machine->plus_repair_cost(((Control_Panel*)machine->spare_parts[i])->get_replacement_cost());
                machine->spare_parts[i] = new Control_Panel(rand() % 9001 + 1000, rand() % 3501 + 500, rand() % 4 + 1, rand() % 1851 + 150, rand() % 100);
            }
            else if (((Control_Panel*)machine->spare_parts[i])->def_breakage() > 0) {
                repair_time = ((Control_Panel*)machine->spare_parts[i])->def_breakage();

                machine->plus_breakdown();
                machine->plus_repair_cost(((Control_Panel*)machine->spare_parts[i])->get_repair_cost());
            }
        }

        else if (type == "Cutting_Head") {          
            if (((Cutting_Head*)machine->spare_parts[i])->def_full_breakage() > 0) {
                repair_time = 4;

                ((Cutting_Head*)machine->spare_parts[i])->get_replacement_cost();

                machine->plus_replaced_parts();
                machine->plus_repair_cost(((Cutting_Head*)machine->spare_parts[i])->get_replacement_cost());
                machine->spare_parts[i] = new Cutting_Head(rand() % 9001 + 1000, rand() % 3501 + 500, rand() % 4 + 1, rand() % 1851 + 150, rand() % 100);
            }
            else if (((Cutting_Head*)machine->spare_parts[i])->def_breakage() > 0) {
                repair_time = ((Cutting_Head*)machine->spare_parts[i])->def_breakage();

                machine->plus_breakdown();
                machine->plus_repair_cost(((Cutting_Head*)machine->spare_parts[i])->get_repair_cost());
            }
        }

        if (repair_time > service_time) service_time = repair_time;
    }

    machine->plus_downtime(service_time);
    machine->set_service_time(service_time);
}

/*
 * Вывод статистики о работе станка
 *
 * @param machine объект станка
 * @param num_machine количество станков
 * Прохождение по массиву станков
 * и вывод общей статистики и статистики по каждому станку отдельно
 */
void print_statistic(Machine* machine_array, int num_machine) {
    int sum_replace = 0;
    int sum_downtime = 0;
    int sum_breakdown = 0;
    int sum_cost_rep = 0;
    int max_downtime = 0;

    for (int i = 0; i < num_machine; i++) {
        sum_replace += machine_array[i].get_replaced_parts();
        sum_breakdown += machine_array[i].get_num_breakdown();
        sum_downtime += machine_array[i].get_downtime();
        sum_cost_rep += machine_array[i].get_repair_cost();

        if (max_downtime < machine_array[i].get_downtime())
            max_downtime = machine_array[i].get_downtime();
    }

    cout << "---Statistic---\n\n";
    cout << "Number of replacement parts: " << sum_replace << endl;
    cout << "Number of breakdowns: " << sum_breakdown << endl;
    cout << "Sum of cost repair and replacement: " << sum_cost_rep << endl;
    cout << "Sum of downtime: " << sum_downtime << endl;
    cout << "Maximum total downtime of one machine:" << max_downtime << "\n";

    for (int i = 0; i < num_machine; i++) {
        cout << "\nMachine " << i+1 << ":" << endl;
        cout << "Number of replacement parts: " << machine_array[i].get_replaced_parts() << endl;
        cout << "Number of breakdowns: " << machine_array[i].get_num_breakdown() << endl;
        cout << "Sum of cost repair and replacement: " << machine_array[i].get_repair_cost() << endl;
        cout << "Sum of downtime: " << machine_array[i].get_downtime() << endl;
    }

}