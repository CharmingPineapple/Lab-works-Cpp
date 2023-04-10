// kochubey_lab3.cpp


#include <stdlib.h>
#include <iostream>
#include <cmath>
 

using namespace std;



struct Circle {
private:
    double radius;
    const double PI = 3.141592653589793;
    
public:
    double get_radius() {
        return radius;
    };

    double get_area() {
        return PI * radius * radius;
    }

    Circle(double radius) {
        this->radius = radius;
    }
};

struct Square {
private:
    double length;
    
public:
    double get_length() {
        return length;
    };

    double get_area() {
        return length*length;
    }

    Square(double length) {
        this->length = length;
    }
};

struct Rectangle {
private: 
    double length, width;
    
public:
    double get_length() {
        return length;
    };
    double get_width() {
        return width;
    };

    double get_area() {
        return length*width;
    }

    Rectangle(double length, double width) {
        this->length = length;
        this->width = width;
    }
};

struct Triangle {
private :
    double a, b, c;
    double angle_ab;
    //double angle_bc, angle_ac;
    const double PI = 3.141592653589793;
    
public:
    double get_a() {
        return a;
    };
    double get_b() {
        return b;
    };
    double get_c() {
        return c;
    };
    double get_angle_ab() {
        return angle_ab;
    };
    /*double get_angle_bc() {
        return angle_bc;
    };
    double get_angle_ac() {
        return angle_ac;
    };*/
    double get_area() {
        double area = (double) (a * b * sin(angle_ab * PI / 180) / 2);
        //double p = (a + b + c) / 2;
        //double area = sqrt(p * (p - a) * (p - b) * (p - c));
        return area;
    }

    Triangle(double a, double b, double angle_ab) {
        this->a = a;
        this->b = b;
        this->c = sqrt(a * a + b * b - 2 * a * b * cos(angle_ab * PI / 180));

        this->angle_ab = angle_ab;
        //this->angle_bc = acos((b * b + c * c - a * a) / (2 * b * c)) * 180 / PI;
        //this->angle_ac = 180 - angle_bc - angle_ab;
    }

    /*Triangle(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }*/
    
};


void sum_of_area(void**, string*, int);
void num_of_types(string*, int);
void area_over_cin(void**, string*, int);
void circumcircle_radius(void**, string*, int);
void generation_figures(void**, string*, int);
void printing_figures(void**, string*, int);

int main()
{
    srand(time(NULL));

    const int NUMBER_OF_FIGURES = 5;
    void* figures[NUMBER_OF_FIGURES];
    string figures_types[NUMBER_OF_FIGURES];
    //string figures_types[NUMBER_OF_FIGURES] = {"triangle", "rectangle", "square", "circle", "triangle" };

    generation_figures(figures, figures_types, NUMBER_OF_FIGURES);

    /*Triangle triangle(6, 8, 90);
    Rectangle rectangle(4, 5);
    Square square(7);
    Circle circle(3);
    Triangle triangle_2(6, 6, 60);*/

    printing_figures(figures, figures_types, NUMBER_OF_FIGURES);
    sum_of_area(figures, figures_types, NUMBER_OF_FIGURES);
    num_of_types(figures_types, NUMBER_OF_FIGURES);
    area_over_cin(figures, figures_types, NUMBER_OF_FIGURES);
    circumcircle_radius(figures, figures_types, NUMBER_OF_FIGURES);

}

/*
 * Вычисление суммы площадей всех фигур
 *
 * @param figures массив объектов разных фигур.
 * @param figures_types массив последовательности названий сруктур фигур.
 * @param num_of_figures количество фигур.
 * Прохождение по массиву фигур и суммирование их площадей.
 */
void sum_of_area(void** figures, string* figures_types, int num_of_figures) {
      double sum_of_area = 0;
    for (int i = 0; i < num_of_figures; i++) {
        string type = figures_types[i];
        if (type == "triangle") sum_of_area += ((Triangle*)figures[i])->get_area();
        else if (type == "rectangle") sum_of_area += ((Rectangle*)figures[i])->get_area();
        else if (type == "square") sum_of_area += ((Square*)figures[i])->get_area();
        else if (type == "circle") sum_of_area += ((Circle*)figures[i])->get_area();
    }
    cout << "The sum of the areas of the figures: " << sum_of_area << endl;
}

/*
 * Подсчёт количества типов фигур
 *
 * @param figures_types массив последовательности названий сруктур фигур.
 * @param num_of_figures количество фигур.
 * Прохождение по массиву и подсчёт количества типов фигур.
 */
void num_of_types(string* figures_types, int num_of_figures) {
    int num_of_types[4] = {0, 0, 0, 0};
    
    for (int i = 0;i < num_of_figures;i++) {
        string type = figures_types[i];

        if (type == "triangle") num_of_types[0]++;
        else if (type == "rectangle") num_of_types[1]++;
        else if (type == "square") num_of_types[2]++;
        else if (type == "circle") num_of_types[3]++;
    }
    cout << "\nNum of triangle = " << num_of_types[0] << ";" << endl;
    cout << "Num of rectangle = " << num_of_types[1] << ";" << endl;
    cout << "Num of square = " << num_of_types[2] << ";" << endl;
    cout << "Num of circle = " << num_of_types[3] << ";" << endl;
}

/*
 * Вывод площадей фигур, которые больше площади, введённой пользователем
 *
 * @param figures массив объектов разных фигур.
 * @param figures_types массив последовательности названий сруктур фигур.
 * @param num_of_figures количество фигур.
 * Ввод площади пользователем, сравнение с площадью фигур, вывод фигур, чьи площади больше введённой.
 */
void area_over_cin(void** figures, string* figures_types, int num_of_figures) {
    int user_area = 0;
    cout << "\nEnter your area: ";
    cin >> user_area;
    cout << "Firgures with area over than your number:\n";

    for (int i = 0; i < num_of_figures; i++) {     
        double area;
        string type = figures_types[i];

        if (type == "triangle") {
            area = ((Triangle*)figures[i])->get_area();
            if (area > user_area) cout << "Triangle: " << area << endl;
        } 
        else if (type == "rectangle") {
            area = ((Rectangle*)figures[i])->get_area();
            if (area > user_area) cout << "Rectangle: " << area << endl;
        }
        else if (type == "square") {
            area = ((Square*)figures[i])->get_area();
            if (area > user_area) cout << "Square: " << area << endl;
        }
        else if (type == "circle") {
            area = ((Circle*)figures[i])->get_area();
            if (area > user_area) cout << "Circle: " << area << endl;
        }      
    }    
}

/*
 * Вычисление радиуса описанной окружности для всех фигур
 *
 * @param figures массив объектов разных фигур.
 * @param figures_types массив последовательности названий сруктур фигур.
 * @param num_of_figures количество фигур.
 * Вычисление радиуса описанной окружности для каждой из фигур. 
 * Максимальный радиус - искомая окружность.
 */
void circumcircle_radius(void** figures, string* figures_types, int num_of_figures) {
    double max_radius = 0;
    double current_radius = 0;

    for (int i = 0; i < num_of_figures; i++) {
        string type = figures_types[i];

        if (type == "triangle") {
            Triangle* p_triangle = ((Triangle*)figures[i]);
            current_radius = (p_triangle->get_a() * p_triangle->get_b() * p_triangle->get_c()) / (4 * p_triangle->get_area());
        }
        else if (type == "rectangle") {
            Rectangle* p_rectangle = ((Rectangle*)figures[i]);
            current_radius = sqrt(pow(p_rectangle->get_length(), 2) + pow(p_rectangle->get_width(), 2)) / 2;
        }
        else if (type == "square") {
            Square* p_square = ((Square*)figures[i]);
            current_radius = sqrt(2*pow(p_square->get_length(), 2)) / 2;
        }
        else if (type == "circle") {
            Circle* p_circle = ((Circle*)figures[i]);
            current_radius = p_circle->get_radius();
        }

        if (max_radius < current_radius) max_radius = current_radius;
    }

    cout << "\nRadius of circumcircle for all figures: " << max_radius << endl;
}

/*
 * Вычисление радиуса описанной окружности для всех фигур
 *
 * @param figures массив объектов разных фигур.
 * @param figures_types массив последовательности названий сруктур фигур.
 * @param num_of_figures количество фигур.
 * Заполнения массива figures - объектами случайных фигур, 
 * массива figures_types - соответствующими типами фигур.
 */
void generation_figures(void** figures, string* figures_types, int num_of_figures) {
    for (int i = 0;i < num_of_figures; i++) {
        switch ((int)rand()%4)
        {
        case 0:
            figures[i] = new Triangle((rand() % 10 + 1), (rand() % 10 + 1), (rand() % 140 + 10));
            figures_types[i] = "triangle";
            break;
        case 1:
            figures[i] = new Rectangle((rand() % 10 + 1), (rand() % 10 + 1));
            figures_types[i] = "rectangle";
            break;
        case 2:
            figures[i] = new Square((rand() % 10 + 2));
            figures_types[i] = "square";
            break;
        case 3:
            figures[i] = new Circle((rand() % 5 + 1));
            figures_types[i] = "circle";
            break;
        }
    }
}

/*
 * Вычисление радиуса описанной окружности для всех фигур
 *
 * @param figures массив объектов разных фигур.
 * @param figures_types массив последовательности названий сруктур фигур.
 * @param num_of_figures количество фигур.
 * Вывод основных полей структур фигур и их площади по порядку в массиве.
 */
void printing_figures(void** figures, string* figures_types, int num_of_figures) {
    for (int i = 0; i < num_of_figures; i++) {
        if (figures_types[i] == "triangle") {
            Triangle* p_triangle = ((Triangle*)figures[i]);
            cout << "Triangle:" << endl;
            cout << "a: " << p_triangle->get_a() << endl;
            cout << "b: " << p_triangle->get_b() << endl;
            cout << "c: " << p_triangle->get_c() << endl;
            cout << "angle_ab: " << p_triangle->get_angle_ab() << endl;
            cout << "area: " << p_triangle->get_area() << "\n\n";
        }

        else if (figures_types[i] == "rectangle") {
            Rectangle* p_rectangle = ((Rectangle*)figures[i]);
            cout << "Rectangle: " << endl;
            cout << "length: " << p_rectangle->get_length() << endl;
            cout << "width: " << p_rectangle->get_width() << endl;
            cout << "area: " << p_rectangle->get_area() << "\n\n";
        }

        else if (figures_types[i] == "square") {
            Square* p_square = ((Square*)figures[i]);
            cout << "Square: " << endl;
            cout << "length: " << p_square->get_length() << endl;
            cout << "area: " << p_square->get_area() << "\n\n";
        }

        else if (figures_types[i] == "circle") {
            Circle* p_circle = ((Circle*)figures[i]);
            cout << "Circle: " << endl;
            cout << "radius: " << p_circle->get_radius() << endl;
            cout << "area: " << p_circle->get_area() << "\n\n";
        }
    }
}



