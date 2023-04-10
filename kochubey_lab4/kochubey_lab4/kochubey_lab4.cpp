// kochubey_lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdlib.h>
#include <iostream>
using namespace std;



class Hexagon {
private:
    double length;
    

public:
    double get_length() {
        return length;
    };
    

    double get_area() {
        return (3*sqrt(3)/2)*length*length;
    }
    Hexagon(double length) {
        this->length = length;
        
    }
};

class Rectangle {
private:
    double length, width;
    //double circumcircle_radius;

public:
    double get_length() {
        return length;
    };
    double get_width() {
        return width;
    };
    /*double get_circumcircle_radius() {
        return circumcircle_radius;
    };*/

    double get_area() {
        return length * width;
    }

    Rectangle(double length, double width) {
        this->length = length;
        this->width = width;
        //this->circumcircle_radius = sqrt(pow(length, 2) + pow(width, 2)) / 2;
    }
};

class Circle {
private:
    double radius;
    //double circumcircle_radius;
    const double PI = 3.141592653589793;

public:
    double get_radius() {
        return radius;
    };
    /*double get_circumcircle_radius() {
        return circumcircle_radius;
    };*/

    double get_area() {
        return PI * radius * radius;
    }

    Circle(double radius) {
        this->radius = radius;
        //this->circumcircle_radius = radius;
    }
};

class Figure {
private:
    double circumcircle_radius;
    double x, y;
    double vector_x, vector_y;
    //
    string type_name;
    void* p_figure;

public:
    double get_circumcircle_radius() {
        return circumcircle_radius;
    };
    void set_xy(double a, double b) {
        this->x = a;
        this->y = b;
    }
    void set_vector(double x, double y) {
        this->vector_x = x;
        this->vector_y = y;
    }
    void shift() {
        x += vector_x;
        y += vector_y;  
    }
    double get_x() {
        return this->x;
    }
    double get_y() {
        return this->y;
    }
    double get_vector_x() {
        return vector_x;
    }
    double get_vector_y() {
        return vector_y;
    }
    double get_area() {
        if (type_name == "Hexagon") return ((Hexagon*)p_figure)->get_area();
        else if (type_name == "Rectangle") return ((Rectangle*)p_figure)->get_area();
        else if (type_name == "Circle") return ((Circle*)p_figure)->get_area();
    }
    string get_type() {
        return type_name;
    }

    Figure() {

    }

    Figure(string type_name, void* p_figure) {
        this->type_name = type_name;
        this->p_figure = p_figure;

        if (type_name == "Hexagon")
            this->circumcircle_radius = ((Hexagon*)this->p_figure)->get_length();
        
        else if (type_name == "Rectangle")
            this->circumcircle_radius = sqrt(pow(((Rectangle*)this->p_figure)->get_length(), 2) + pow(((Rectangle*)this->p_figure)->get_width(), 2)) / 2;
           
        else if (type_name == "Circle")
            this->circumcircle_radius = ((Circle*)this->p_figure)->get_radius();
            
        
    }
};

class Scene {
private:
    int height, width;
    int num_figures;


public:
   Figure* figures_array;
   string* figures_types;
   
   void set_num_figures(int num) {
       this->num_figures = num;
   }
   int get_num_figures() {
       return num_figures;
   }

   int get_height() {
       return height;
   }
   int get_width() {
       return width;
   }

   Scene(int height,int width) {
       this->height = height;
       this->width = width;
   }
};

//void generation_figures(Scene*, int, Figure**);
//int put_figure(Scene*, Figure*);

int generation_figures(Scene, Figure**, int);
int put_figure(Figure**, Figure*, int, int, int);
void sum_area(Figure**, int);

void moving(Figure**, int, int, int, int);
void set_vector(Figure**, int);
void moving_figures(Figure** , int);
void changing_vector(Figure**, int, int, int);
void touch_border(Figure*, int, int);
void touch_other_figure(Figure*, Figure*);
void print_figures(Figure** , int );

int main()
{
    srand(time(NULL));

    int num_of_figures;
    int height, width;
    int time_mls_10 = 10;

    cout << "Enter height of scene: ";
    cin >> height;
    cout << "Enter width of scene: ";
    cin >> width;
    cout << "Enter number of figures on scene: ";
    cin >> num_of_figures;
    
    Scene new_scene = Scene(height, width);
    new_scene.figures_array = new Figure[num_of_figures];
    new_scene.figures_types = new string[num_of_figures];

    //generation_figures(&new_scene, num_of_figures, &new_scene.figures_array);

    new_scene.set_num_figures(generation_figures(new_scene, &new_scene.figures_array, num_of_figures));

    //cout << new_scene.figures_array[0].

    // test
    cout << "num figures on scene:" << new_scene.get_num_figures() << endl;

    sum_area(&new_scene.figures_array, new_scene.get_num_figures());

    moving(&new_scene.figures_array, new_scene.get_num_figures(), new_scene.get_width(), new_scene.get_height(), time_mls_10);
    //cout << "Num figures on scene: " << new_scene.get_num_figures() << endl;
}


/*
 * Генерация фигур
 *
 * @param scene объект сцены
 * @param figures_array массив фигур, хранящийся в классе сцены.
 * @param num_figures количество фигур, необходимое сгенерировать
 * Заполнение массива figures_array случайными фигурами,
*  которым случайно присваиваются координаты на сцене.
 */
int generation_figures(Scene scene, Figure** figures_array, int num_figures) {
    int num_figures_on_scene = 0;

    for (int i = 0; i < num_figures; i++) {
        bool limit = false;
        for (int k = 0; k < 100; k++) {
            // creating figure
            switch (rand() % 3)
            {
            case 0:
                figures_array[i] = new Figure("Hexagon", new Hexagon(rand() % 5 + 1));
                break;
            case 1:
                figures_array[i] = new Figure("Rectangle", new Rectangle(rand() % 10 + 1, rand()%10 + 1));
                break;
            case 2:
                figures_array[i] = new Figure("Circle", new Circle(rand() % 5 + 1));
                break;
            }
            
            //set coordinates of figure
            figures_array[i]->set_xy(rand() % scene.get_width(), rand() % scene.get_height());
            
            // test
            cout << "radius:" << figures_array[i]->get_circumcircle_radius() << endl;
            cout << "coord:" << figures_array[i]->get_x() << ", " << figures_array[i]->get_y() << endl;


            if (put_figure(figures_array, figures_array[i], i, scene.get_width(), scene.get_height()) == 1) break;
            if (k == 99) limit = true;
        }

        if (limit) {
            cout << "Putting figures is limited. Current num of figures on scene: " << i << endl;
            return i;
            break;
        }
        num_figures_on_scene = i;
        
        
    }
    return num_figures_on_scene + 1;
}

/*
 * Выставление фигуры на сцену
 * 
 * @param figures_array массив фигур, хранящийся в классе сцены.
 * @param figure объект фигуры, которая ставится на сцену
 * @param num_figures текущее количество фигур на сцене
 * @param lim_x, lim_y - границы сцены
 * Проверка на пересечение объекта figure с другими фигурами или границами сцены
 * и выставление на сцену по заданным координатам
 */
int put_figure(Figure** figures_array, Figure* figure, int num_figures, int lim_x, int lim_y) {
    
    // check for intersection with other figures
    for (int i = 0; i < num_figures; i++) {
        double min_distance = sqrt(pow(abs(figures_array[i]->get_x() - figure->get_x() ), 2) 
            + pow(abs(figures_array[i]->get_y() - figure->get_y()), 2));

        // test
        cout << "\nmin distance: " << min_distance << endl;
        cout << "distance: " << (figures_array[i]->get_circumcircle_radius() + figure->get_circumcircle_radius()) << "\n" << endl;

        if (min_distance <= (figures_array[i]->get_circumcircle_radius() + figure->get_circumcircle_radius()))
            return 0;

    }

    // check for intersection with borders
    if (figure->get_x() + figure->get_circumcircle_radius() >= lim_x) return 0;
    if (figure->get_y() + figure->get_circumcircle_radius() >= lim_y) return 0;
    if (figure->get_x() - figure->get_circumcircle_radius() <= 0) return 0;
    if (figure->get_y() - figure->get_circumcircle_radius() <= 0) return 0;

    //test
    cout << "--accept--" << endl;

    return 1;
}

/*
 * Вычисление суммы площадей фигур на сцене
 *
 * @param figures_array массив фигур, хранящийся в классе сцены.
 * @param num_figures текущее количество фигур на сцене
 * Прохождение по массиву figures_array и складывание площадей каждой из фигур на сцене.
 */
void sum_area(Figure** figures_array, int num_figures) {
    double sum_area = 0;
      
    for (int i = 0; i < num_figures; i++) {
        sum_area += figures_array[i]->get_area();
    }
   
    cout << "The sum of the areas of the figures: " << sum_area << endl;
}

/*
 * Движение фигур на сцене
 *
 * @param figures_array массив фигур, хранящийся в классе сцены.
 * @param num_figures текущее количество фигур на сцене
 * @param lim_x, lim_y - границы сцены
 * Движение фигур осуществляется 3 методами:
 * set_vector - установка скоростей фигур
 * moving_figures - передвижение фигур в соответствии с их скоростью
 * changing_vector - изменение направления движения в зависимости от текущих столкновений
 */
void moving(Figure** figures_array, int num_figures, int lim_x, int lim_y, int time_mls_10) {

    set_vector(figures_array, num_figures);
    //int time_sec = 5;

    for (int i = 0; i < time_mls_10+1; i++) {
        cout << "\n" << 0.01 * i << " second:\n";
        moving_figures(figures_array, num_figures);
        print_figures(figures_array, num_figures);
        changing_vector(figures_array, num_figures, lim_x, lim_y);
    }

}

/*
 * Установка скорости/направления движения фигуры
 *
 * @param figures_array массив фигур, хранящийся в классе сцены.
 * @param num_figures текущее количество фигур на сцене
 * Установка случайного вектора движения для каждой из фигур
 */
void set_vector(Figure** figures_array, int num_figures) {
    int moving_factor = 1;
    int negative_x = 1;
    int negative_y = 1;

    if (rand() % 2 == 0) negative_x = -1;
    if (rand() % 2 == 0) negative_y = -1;

    for (int i = 0; i < num_figures; i++) {
        figures_array[i]->set_vector((rand() % 3) * moving_factor * negative_x, (rand() % 3) * moving_factor * negative_y);
    }
}

/*
 * Выполнение движения фигур
 *
 * @param figures_array массив фигур, хранящийся в классе сцены.
 * @param num_figures текущее количество фигур на сцене
 * Выполнение движения фигур на сцене на вектор их скорости
 */
void moving_figures(Figure** figures_array, int num_figures) {
    for (int i = 0; i < num_figures; i++) {
        figures_array[i]->shift();
    }
}

/*
 * Изменение направления вектора фигуры
 *
 * @param figures_array массив фигур, хранящийся в классе сцены.
 * @param num_figures текущее количество фигур на сцене
 * @param lim_x, lim_y - границы сцены
 * Изменение вектора фигуры осуществляется 2 методами:
 * touch_border - проверка на касание с границами сцены 
 * touch_other_figure - проверка на касание с границами других фигур
 */
void changing_vector(Figure** figures_array, int num_figures, int lim_x, int lim_y) {
    for (int i = 0; i < num_figures; i++) {
        
        
        touch_border(figures_array[i], lim_x, lim_y);
         
        for (int k = 0; k < num_figures; k++) {
           
            touch_other_figure(figures_array[i], figures_array[k]);
        }

    }
}

/*
 * Вывод данных о текущих фигурах
 *
 * @param figures_array массив фигур, хранящийся в классе сцены.
 * @param num_figures текущее количество фигур на сцене
 * Прохождение по массиву фигур и вывод данных о коорд., радиусе, типе фигуры
 */
void print_figures(Figure** figures_array, int num_figures) {
    for (int i = 0; i < num_figures; i++) {
        cout << figures_array[i]->get_type() << " coord: " << figures_array[i]->get_x() << ", " << figures_array[i]->get_y() 
            << " radius: " << figures_array[i]->get_circumcircle_radius() << endl;
    }
}

/*
 * Изменение направления вектора фигуры при касании со границами сцены
 *
 * @param figure - объект рассматриваемой фигуры
 * @param lim_x, lim_y - границы сцены
 * Изменение вектора фигуры в зависимости от касания с вертикальной или горизонтальной стенками
 */
void touch_border(Figure* figure, int lim_x, int lim_y) {
    double radius;
    
    radius = figure->get_circumcircle_radius();

    if  (figure->get_x() + radius >= lim_x) {
        figure->set_vector(-(figure->get_vector_x()), figure->get_vector_y());
        cout << figure->get_type() << " with radius " << figure->get_circumcircle_radius() << " touch with right border" << endl;
    }
    if (figure->get_x() - radius <= 0) {
        figure->set_vector(-(figure->get_vector_x()), figure->get_vector_y());
        cout << figure->get_type() << " with radius " << figure->get_circumcircle_radius() << " touch with left border" << endl;
    }

    if (figure->get_y() - radius <= 0) {
        figure->set_vector(figure->get_vector_x(), -(figure->get_vector_y())); 
        cout << figure->get_type() << " with radius " << figure->get_circumcircle_radius() << " touch with bottom border" << endl;
    }
    if (figure->get_y() + radius >= lim_y) {
        figure->set_vector(figure->get_vector_x(), -(figure->get_vector_y()));
        cout << figure->get_type() << " with radius " << figure->get_circumcircle_radius() << " touch with top border" << endl;
    }
        
}

/*
 * Изменение направления вектора фигуры при касании границ других фигур
 *
 * @param figure - объект рассматриваемой фигуры
 * @param other_figure - объект фигуры с которой может столкнуться рассматриваемая фигура
 * touch vertical or horizon - столкновение по вертикали или горизонтали и изменение направления вектора
 * touch other part of circle - столкновение с иной частью границ фигуры,
*  вычисление нового направления вектора.
 */
void touch_other_figure(Figure* figure, Figure* other_figure) {
    double min_distance;
    const double PI = 3.141592653589793;

    // if it is the same figure
    if ((figure->get_x() == other_figure->get_x()) 
        and (figure->get_y() == other_figure->get_y()) 
            and (figure->get_area() == other_figure->get_area()))
        return;

    min_distance = sqrt(pow(abs(other_figure->get_x() - figure->get_x()), 2)
        + pow(abs(other_figure->get_y() - figure->get_y()), 2));

    if (min_distance <= (other_figure->get_circumcircle_radius() + figure->get_circumcircle_radius())) {

        // touch vertical or horizon
        if (figure->get_x() == other_figure->get_x() and figure->get_y() < other_figure->get_y()) {
            figure->set_vector(-(figure->get_x()), figure->get_y());
            cout << figure->get_type() << " with radius " << figure->get_circumcircle_radius() << " touch with top border of another figure" << endl;
        } 
        else if (figure->get_x() == other_figure->get_x() and figure->get_y() > other_figure->get_y()) {
            figure->set_vector(-(figure->get_x()), figure->get_y());
            cout << figure->get_type() << " with radius " << figure->get_circumcircle_radius() << " touch with bottom border of another figure" << endl;
        }
        else if (figure->get_y() == other_figure->get_y() and figure->get_x() < other_figure->get_x()) {
            figure->set_vector(figure->get_x(), -(figure->get_y()));
            cout << figure->get_type() << " with radius " << figure->get_circumcircle_radius() << " touch with left border of another figure" << endl;
        }
        else if (figure->get_y() == other_figure->get_y() and figure->get_x() > other_figure->get_x()) {
            figure->set_vector(figure->get_x(), -(figure->get_y()));
            cout << figure->get_type() << " with radius " << figure->get_circumcircle_radius() << " touch with right border of another figure" << endl;
        }
        else {
            // touch other part of circle

            double vector_speed_length = sqrt(pow(abs(figure->get_x() - figure->get_vector_x()), 2) + pow(abs(figure->get_y() - figure->get_vector_y()), 2));
            //double sum_radius = figure->get_circumcircle_radius() + other_figure->get_circumcircle_radius();
            double figure_distance = sqrt(pow(abs(figure->get_x() - other_figure->get_x()), 2) + pow(abs(figure->get_y() - other_figure->get_y()), 2));
            //double ratio = sum_radius / vector_speed_length;
          
            double ratio = vector_speed_length / (figure_distance - vector_speed_length);

            double x_m, y_m;

            x_m = (figure->get_x() + ratio * other_figure->get_x()) / (1 + ratio);
            y_m = (figure->get_y() + ratio * other_figure->get_y()) / (1 + ratio);

            double x_shrink, y_shrink;

            x_shrink = figure->get_x() - x_m;
            y_shrink = figure->get_y() - x_m;

            //coord second vector
            //double x_2, y_2;
            double new_vector_x, new_vector_y;

            //x_2 = figure->get_x() - x_shrink;
            //y_2 = figure->get_y() - y_shrink;



            ///
            //x_2 = -(other_figure->get_x() - (sin(45 * PI / 180) * (sum_radius - vector_speed_length) / 2));
            //y_2 = -(other_figure->get_y() - (sin(45 * PI / 180) * (sum_radius - vector_speed_length) / 2));

            //x_2 = - (other_figure->get_x() - figure->get_x()) / ratio;
            //y_2 = -(other_figure->get_y() - figure->get_y()) / ratio;

            //new_vector_x = (figure->get_vector_x() + x_2) / 2;
            //new_vector_y = (figure->get_vector_y() + y_2) / 2;
            new_vector_x = (figure->get_vector_x() + x_shrink) / 2;
            new_vector_y = (figure->get_vector_y() + y_shrink) / 2;

            figure->set_vector(new_vector_x, new_vector_y);
            cout << figure->get_type() << " with radius " << figure->get_circumcircle_radius() 
                << " touch with some part of border of another figure" << endl;
            
            //double new_vector_length = sqrt(pow(abs(figure->get_x() - new_vector_x), 2) + pow(abs(figure->get_y() - new_vector_y), 2));
            double new_vector_length = sqrt(pow(abs(figure->get_x() - new_vector_x), 2) + pow(abs(figure->get_y() - new_vector_y), 2));
            
            //cout << "--Check for right vector--\n" << "first vector length: " << vector_speed_length 
             //   << "; new vector lenght: " << new_vector_length << endl;
        }
            

        
        //if ()


        /*double external_cathet = sqrt(pow( abs(other_figure->get_x() - figure->get_x()), 2) + pow(abs(other_figure->get_y() - figure->get_y()), 2));
        double sum_radius = figure->get_circumcircle_radius() + other_figure->get_circumcircle_radius();
        double vector_length = sqrt(pow(abs(figure->get_vector_x()), 2) + pow(abs(figure->get_vector_y()), 2));
        double external_angle = acos( (pow(vector_length,2) + pow(sum_radius, 2) - pow(external_cathet, 2))/(2*sum_radius*vector_length)) * 180 / PI;*/
    }
       

}



