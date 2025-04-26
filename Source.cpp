#include <iostream>
#include <vector>
using namespace std;

class Herbivore {
protected:
    int weight;
    bool is_alive;

public:
    Herbivore() : weight(0), is_alive(true) {}
    virtual ~Herbivore() = default;

    virtual void eat_grass() = 0;
    int get_weight() const { return weight; }
    bool alive() const { return is_alive; }
    void die() { is_alive = false; }
};

class Carnivore {
protected:
    int power;

public:
    Carnivore() : power(0) {}
    virtual ~Carnivore() = default;

    virtual void eat(Herbivore* herbivore) = 0;
    int get_power() const { return power; }
};


class Continent {
public:
    virtual ~Continent() = default;
    virtual Herbivore* create_herbivore() = 0;
    virtual Carnivore* create_carnivore() = 0;
};


class Wildebeest : public Herbivore {
public:
    Wildebeest() { weight = 150; }
    void eat_grass() override {
        weight += 10;
        cout << "Гну жует траву. Вес теперь: " << weight << " кг." << endl;
    }
};

class Lion : public Carnivore {
public:
    Lion() { power = 200; }
    void eat(Herbivore* herbivore) override {
        if (herbivore->alive() && power > herbivore->get_weight()) {
            herbivore->die();
            power += 10;
            cout << "Лев успешно поохотился. Сила выросла до: " << power << endl;
        }
        else {
            power -= 10;
            cout << "Лев не смог поймать добычу. Сила упала до: " << power << endl;
        }
    }
};

class Africa : public Continent {
public:
    Herbivore* create_herbivore() override { return new Wildebeest(); }
    Carnivore* create_carnivore() override { return new Lion(); }
};

class Kangaroo : public Herbivore {
public:
    Kangaroo() { weight = 200; }
    void eat_grass() override {
        weight += 10;
        cout << "Кенгуру перекусывает травкой. Текущий вес: " << weight << " кг." << endl;
    }
};

class AustralianWolf : public Carnivore {
public:
    AustralianWolf() { power = 180; }
    void eat(Herbivore* herbivore) override {
        if (herbivore->alive() && power > herbivore->get_weight()) {
            herbivore->die();
            power += 10;
            cout << "Австралийский волк поймал травоядное! Сила: " << power << endl;
        }
        else {
            power -= 10;
            cout << "Австралийский волк остался голоден. Сила снизилась до: " << power << endl;
        }
    }
};

class Australia : public Continent {
public:
    Herbivore* create_herbivore() override { return new Kangaroo(); }
    Carnivore* create_carnivore() override { return new AustralianWolf(); }
};

class Bison : public Herbivore {
public:
    Bison() { weight = 300; }
    void eat_grass() override {
        weight += 15;
        cout << "Бизон спокойно ест траву. Вес увеличился до: " << weight << " кг." << endl;
    }
};

class Wolf : public Carnivore {
public:
    Wolf() { power = 200; }
    void eat(Herbivore* herbivore) override {
        if (herbivore->alive() && power > herbivore->get_weight()) {
            herbivore->die();
            power += 10;
            cout << "Волк напал и съел добычу. Текущая сила: " << power << endl;
        }
        else {
            power -= 10;
            cout << "Волк не справился с добычей. Сила уменьшилась: " << power << endl;
        }
    }
};

class NorthAmerica : public Continent {
public:
    Herbivore* create_herbivore() override { return new Bison(); }
    Carnivore* create_carnivore() override { return new Wolf(); }
};

class AnimalWorld {
private:
    vector<Continent*> continents;
    vector<Herbivore*> herbivores;
    vector<Carnivore*> carnivores;

public:
    ~AnimalWorld() {
        for (auto herb : herbivores) delete herb;
        for (auto carn : carnivores) delete carn;
        for (auto cont : continents) delete cont;
    }

    void add_continent(Continent* continent) {
        continents.push_back(continent);
        herbivores.push_back(continent->create_herbivore());
        carnivores.push_back(continent->create_carnivore());
    }

    void meals_herbivores() {
        for (auto& herbivore : herbivores) {
            if (herbivore->alive())
                herbivore->eat_grass();
        }
    }

    void nutrition_carnivores() {
        for (auto& carnivore : carnivores) {
            for (auto& herbivore : herbivores) {
                if (herbivore->alive())
                    carnivore->eat(herbivore);
            }
        }
    }
};

void print_menu() {
    cout << "======= М И Р  Ж И В О Т Н Ы Х =======" << endl;
    cout << "1. Добавить континент — Африка" << endl;
    cout << "2. Добавить континент — Северная Америка" << endl;
    cout << "3. Добавить континент — Австралия" << endl;
    cout << "4. Покормить всех травоядных" << endl;
    cout << "5. Начать охоту хищников" << endl;
    cout << "6. Выход из симуляции" << endl;
    cout << "Введите номер действия: ";
}

int main() {
    setlocale(LC_ALL, "ru");
    AnimalWorld world;
    bool is_running = true;
    int option;

    while (is_running) {
        system("cls");
        print_menu();
        cin >> option;

        switch (option) {
        case 1:
            cout << "Африка добавлена в экосистему." << endl;
            world.add_continent(new Africa());
            break;
        case 2:
            cout << "Северная Америка успешно добавлена." << endl;
            world.add_continent(new NorthAmerica());
            break;
        case 3:
            cout << "Австралия теперь в игре!" << endl;
            world.add_continent(new Australia());
            break;
        case 4:
            cout << "Травоядные пошли на лужайку перекусить..." << endl;
            world.meals_herbivores();
            break;
        case 5:
            cout << "Хищники выходят на охоту!" << endl;
            world.nutrition_carnivores();
            break;
        case 6:
            cout << "Завершение работы программы. До новых встреч!" << endl;
            is_running = false;
            break;
        default:
            cout << "Неверный ввод. Попробуйте выбрать другой пункт." << endl;
            break;
        }
        cout << endl;
        system("pause");
    }

    return 0;
}