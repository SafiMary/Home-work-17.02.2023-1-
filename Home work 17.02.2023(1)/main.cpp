#include <iostream>
#include <fstream>
#include <memory>

// SOLID � �������� ��������������
//SOLID :
// 1)Single Resposibility - ������� ������������ ���������������
// ����� (��������) �������� ������ �� ���� � �� ����� ��������������� �� ��������� ��������� ������ ���������.

//2)������� ���������� \ ���������� (Open close principe)
//���� ������ (����������� ��������) ������ ���� ������� ��� ���������� , �� ������� ��� �����������
// �� ���� ������� ���� �� �������� �����������, � ��� ���������� ������ � ����������� �������

//3) ������� ����������� ������ ( Liskov Substitution )
//������� ������� ���������� ������� ���, ������ ����� ����������� ������������  ������� �������� ����   �� ���� �� ����. ���������� �� ���������� � ����������� � ����������.
//
//4)������� ���������� ���������� (interface segrigation)
//����� ����������� ���������� ��������������� ��� ��������, ����� ��� ���� ��������� ������ ����������. ������� ��� ��������, ������. ���� 1 ���������,
//  �� ������ ���, ��� ����������� ������� ������� �� �����. ��� �� ������ ����� ����������� - � ��� ����� ��������
//
//5)������� �������� ������������ (Dependency inversion)
//�� ������� �� ����������, � �� �� ����������. ������ �������� � ������������


class Button {//������� ���������� \ ����������, �� ������� ����������� �����, � ������������ ��� ���������� ����� �����������. ��� ��� ��� �������� ������ �� �� ������
public:
    virtual void render() = 0;
    virtual ~Button() {}
};

class WindowsButton : public Button {//������� ������������ ��������������� , ����� �������� ������ �� ������ Windows � ����� �� ��� ���������������
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
    void rander() {  // ������� �������� ������������, �������� � ����������
        std::shared_ptr<Button> button = createButton();
        button->render();
    }
    virtual std::shared_ptr<Button> createButton() = 0;
    virtual ~Dialog() {}
};
//������� ���������� ����������, ��� � ��� ���� ���������� ����������� ���� �� ��� ���������, � ����������� �� �������������( ��������� ������������)
class WindowsDialog : public Dialog {
public:
    std::shared_ptr<Button> createButton() override {//������� ����������� ������, ����� ������������ � ���������������� ������� �������� ������, ���������� ����� ����� �������� �������� ����
        return std::make_shared<WindowsButton>();//��������� ������, ����� ��������� �� ������ , ����� ��������
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
