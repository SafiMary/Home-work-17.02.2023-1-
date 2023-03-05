#include <iostream>
#include <fstream>
#include <memory>

// SOLID и паттерны проектирования
//SOLID :
// 1)Single Resposibility - принцип единственной ответственности
// Класс (сущность) отвечает только за себя и не несет ответственности за изменение состояния других сущностей.

//2)Принцип открытости \ закрытости (Open close principe)
//наши классы (программные сущности) должны быть открыты для расширения , но закрыты для модификации
// То есть базовый клас не подлежит модификации, а все расширение делаем в производных классах

//3) Принцип подстановки Лисков ( Liskov Substitution )
//Функция которая использует базовый тип, должны иметь возможность использовать  подтипы базового типа   не зная об этом. Отвязаться от реализации и привязаться к интерфейсу.
//
//4)Принцип разделения интерфейса (interface segrigation)
//Много интерфейсов специально предназначенных для клиентов, лучше чем один интерфейс общего назначения. Клиенты это сущности, классы. Если 1 интерфейс,
//  то бывает так, что наследникам столько методов не нужно. Или мы делаем много интерфейсов - и нам легче работать
//
//5)Принцип инверсии зависимостей (Dependency inversion)
//Мы зависим от абстракции, а не от реализации. Клиент работает с интерфейсами


class Button {//Принцип открытости \ закрытости, мы создали абстрактный класс, с возможностью его расширения через наследников. При это код базового класса мы не меняем
public:
    virtual void render() = 0;
    virtual ~Button() {}
};

class WindowsButton : public Button {//принцип единственной ответственности , класс отвечает только за кнопку Windows и несет за это ответственность
public:
    void render()override {
        std::cout << "Render Windows Button\n";
    }
};
class HTMLButton : public Button {
public:
    void render()override {
        std::cout << "HTML Windows Button\n";
    }
};

class Dialog {
public:
    void rander() {  // Принцип инверсии зависимостей, работаем с итерфейсом
        std::shared_ptr<Button> button = createButton();
        button->render();
    }
    virtual std::shared_ptr<Button> createButton() = 0;
    virtual ~Dialog() {}
};
//Принцип разделения интерфейса, где у нас есть разделение диалогового окна на два подкласса, в зависимости от необходимости( применяем наследование)
class WindowsDialog : public Dialog {
public:
    std::shared_ptr<Button> createButton() override {//Принцип подстановки Лисков, здесь используется и переопределяется функция базового класса, подставить можно любой подкласс базового типа
        return std::make_shared<WindowsButton>();//создается объект, затем указатель на объект , затем кастится
    }
};
class WebDialog : public Dialog {
public:
    std::shared_ptr<Button> createButton() override {
        return std::make_shared<HTMLButton>();
    }
};


int main(int argc, const char* argv[]) {

    std::shared_ptr<Dialog>dialog;
    std::string config;
    std::cout << "Enter config (Windows or Web) : ";
    std::cin >> config;

    if (config == "Windows") {
        dialog = std::make_shared<WindowsDialog>();
    }
    else if (config == "Web") {
        dialog = std::make_shared<WebDialog>();
    }
    else {
        throw "Error: unknown config";

    }








    return 0;
}
