#define _CRT_SECURE_NO_WARNINGS

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include<iostream>
#include"database.h"
#include"type.h"

class System
{
private:
	Database database;
    bool isUserAuthenticated = false; // ��ʾ�û��Ƿ�ͨ����֤
public:
    void Run() {
        // �����к����������¼��չʾ��ӭ��Ϣ�Ͳ˵��������û�����
        // ��¼
        while (!isUserAuthenticated) {
            isUserAuthenticated = LoginProcedure();
            if (!isUserAuthenticated) {
                std::cout << "��¼ʧ�ܣ������ԡ�" << std::endl;
            }
        }
        DisplayWelcomeMessage();
        bool isRunning = true;
        while (isRunning) {
            DisplayMenu();
            int choice = GetUserInput();
            isRunning = ProcessUserChoice(choice);
        }
    }

private:
    bool LoginProcedure() {
        std::string username, password;
        bool flag = false;      
        std::cout << "�������û���: ";
        std::cin >> username;
        std::cout << "����������: ";
        std::cin >> password;

        // ��֤�û���������
        return database.ValidateUser(username, password);
    }



    void DisplayWelcomeMessage() const {
        std::cout << "Welcome to the Coffee Shop Order Management System" << std::endl;
    }

    void DisplayMenu() const {
        // �򵥵��û�����˵�
        cout << "��������������������������������������������������������������������������" << endl;
        std::cout << "Please select an option:" << std::endl;
        std::cout << "1. ��ʾ���в�Ʒ��Ϣ" << std::endl;
        std::cout << "2. ���һ���µĲ�Ʒ" << std::endl;
        std::cout << "3. �Ƴ�һ���µĲ�Ʒ" << std::endl;
        std::cout << "4. ����һ���µĶ���" << std::endl;
        std::cout << "5. ���һ������" << std::endl;
        std::cout << "6.ȡ��һ������" << std::endl;
        std::cout << "7. ��ʾ���ж���" << std::endl;
        std::cout << "8. ��ʾһ��ʱ���������۶�" << std::endl;
        std::cout << "9. ��ʾһ��ʱ���ڸ���Ʒ�������" << std::endl;
        std::cout << "10. �˳�" << std::endl;
        cout << "��������������������������������������������������������������������������" << endl;

    }

    int GetUserInput() const {
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        return choice;
    }

    bool ProcessUserChoice(int choice) {
        switch (choice) {
        case 1:
            database.ShowAllProducts();
            break;
        case 2:
            AddProductProcedure();
            break;
        case 3:
            RemoveProductProcedure();
            break;
        case 4:
            CreateOrderProcedure();
            break;
        case 5:
            CompleteOrderProcedure();
            break;
        case 6:
            CancelOrderProcedure();
            break;
        case 7:
            database.ShowAllOrders();
            break;
        case 8:
            DisplayTotalSales();
            break;
        case 9:
            DisplaySalesByProduct();
            break;
        case 10:
            return false; // Exit the loop and terminate the program
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
        return true; // Continue running
    }

    void AddProductProcedure() {
        // ʾ����ѯ���û�������Ʒ��Ϣ������ӵ����ݿ�
        int typeInput;      //producttype��������
        Product product;
        std::cout << "�����Ʒ��Ϣ (ID, Name, Price, Description, Category, Stock)" << endl;
        cout << "����ID:";
        std::cin >> product.id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ����ǰһ�������Ļ��з�
        cout << "��������:";
        std::getline(std::cin, product.name);
        cout << "����۸�:";
        cin >> product.price;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "�����Ʒ����:";
        getline(cin, product.description);
        cout << "�����Ʒ����:";
        cin >> typeInput;
        product.type = static_cast<ProductType>(typeInput);         //����producttype��Ԫ��
        cout << "�����Ʒ�����:";
        cin >> product.stock;
        
        bool flag = database.AddProduct(product);
        if (flag == true)
            std::cout << "��Ʒ��ӳɹ�." << std::endl;
        else
            std::cout << "��Ʒ�Ѵ��ڡ�";
    }

    void RemoveProductProcedure() {
        // ʾ����ѯ���û�Ҫɾ������ƷID���������ݿ���ɾ��
        int productId;
        std::cout << "������Ҫ�Ƴ��Ĳ�ƷID: ";
        std::cin >> productId;
        bool flag = database.DeleteProduct(productId);
        if (flag == true)
        {
            std::cout << "��Ʒ�Ƴ��ɹ�." << std::endl;
        }
        else
        {
            std::cout << "δ�ҵ���Ʒ ID " << productId << "��ɾ������δִ�С�" << std::endl;
        }
        
    }

    void EditProductProcedure()
    {
        int typeInput;      //producttype��������
        Product product;
        std::cout << "������ĺ�Ĳ�Ʒ��Ϣ (ID, Name, Price, Description, Category, Stock)" << endl;
        cout << "����ID:";
        std::cin >> product.id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ����ǰһ�������Ļ��з�
        cout << "��������:";
        std::getline(std::cin, product.name);
        cout << "����۸�:";
        cin >> product.price;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "�����Ʒ����:";
        getline(cin, product.description);
        cout << "�����Ʒ����:";
        cin >> typeInput;
        product.type = static_cast<ProductType>(typeInput);         //����producttype��Ԫ��
        cout << "�����Ʒ�����:";
        cin >> product.stock;

        bool flag = database.EditProduct(product);
        if (flag == true)
            std::cout << "��Ʒ��Ϣ�޸ĳɹ�." << std::endl;
        else
            std::cout << "����Ҫ�޸ĵĲ�Ʒ�����ڡ�" <<std::endl;
    }

    void CreateOrderProcedure() {
        cout << "��ʼ�����¶�����";

        Order order;
        cout << "������˿�������";
        cin >> order.customer.name;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        order.orderNumber = database.CreateOrderNumber();   //���ɶ�����
        order.status = OrderStatus::Uncompleted; // ��ʼ������״̬Ϊ������
        order.time = std::time(nullptr); // ���ö���ʱ��Ϊ��ǰʱ��

        bool addingProducts = true;
        while (addingProducts == true)
        {
            cout << "��ѡ�񶩵���Ʒ��� (����0����ѡ��):" << endl;
            database.ShowAllProducts(); // ��ʾ������Ʒ��Ϣ
            cout << "������ѡ����Ʒ��ţ�";

            int productId;
            cin >> productId;
            if (productId == 0) {
                addingProducts = false; // �û������Ʒѡ��
                
            }
            else {
                Product* product = database.FindProduct(productId);
                if (product != nullptr)
                {
                    // ��ѡ�����Ʒ��ӵ�������
                    order.items.push_back(*product);
                    cout << "��Ʒ��ӳɹ�: " << product->name << endl;
                }
                else {
                    cout << "��Ʒ�����Ч��������ѡ��" << endl;
                }
            }
        }

        bool isAdded = database.AddOrder(order);
        if (isAdded) {
            cout << "���������ɹ����������: " << order.orderNumber << endl;
        }
        else {
            cout << "�Բ��������������Ʒ��û�п�棬���鶩����" << endl;      //û�п��ʱȡ������
        }
    }

    void CancelOrderProcedure()
    {
        if (database.ShowAllOrders())
        {
            int orderId;
            cout << "����Ҫȡ���Ķ�����ţ�";
            cin >> orderId;
            bool flag = database.CancelOrder(orderId);
            if (flag)
            {
                cout << "����ȡ���ɹ���" << endl;
            }
            else
            {
                cout << "�Ҳ�����ȡ���������������ȡ��������š�" << endl;
            }
        }

        
    }

    void CompleteOrderProcedure() {
        int orderNumber;
        cout << "������Ҫ��ɵĶ������: ";
        cin >> orderNumber;

        Order* order = database.FindOrder(orderNumber); // ���Ҷ���

        if (order == nullptr) {
            // ����δ�ҵ�
            cout << "δ�ҵ�������Ϊ " << orderNumber << " �Ķ�����" << endl;
        }
        else {
            // ��鶩��״̬
            if (order->status == OrderStatus::Completed) {
                // �����Ѿ������״̬
                cout << "������ " << orderNumber << " �Ѿ������״̬��" << endl;
            }
            else if (order->status == OrderStatus::Cancelled)
            {
                cout << "������ " << orderNumber << " ��ȡ�����޷���ɡ�" << endl;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
            }
            else {
                // ���¶���״̬Ϊ�����
                order->status = OrderStatus::Completed;
                cout << "������ " << orderNumber << " ���ڱ��Ϊ����ɡ�" << endl;
            }
        }
    }

    time_t GetTimeInput(const std::string& prompt) {
        std::tm timeInfo = {};
        std::cout << prompt << std::endl;
        std::cout << "���������: "; std::cin >> timeInfo.tm_year;
        std::cout << "�������·�: "; std::cin >> timeInfo.tm_mon;
        std::cout << "����������: "; std::cin >> timeInfo.tm_mday;
        std::cout << "������Сʱ: "; std::cin >> timeInfo.tm_hour;
        std::cout << "���������: "; std::cin >> timeInfo.tm_min;
        std::cout << "����������: "; std::cin >> timeInfo.tm_sec;

        timeInfo.tm_year -= 1900;
        timeInfo.tm_mon -= 1;
        timeInfo.tm_isdst = -1;  // ���Ϊ '��ȷ��' �Ƿ�������ʱ

        return std::mktime(&timeInfo);
    }

    void  DisplayTotalSales()
    {
        time_t startTime;
        time_t endTime;
        double totalsales;

        startTime = GetTimeInput("�����뿪ʼʱ�䣺");
        endTime = GetTimeInput("���������ʱ�䣺");

        
        totalsales = database.CalculateTotalSales(startTime, endTime);       // ���������۶�

        cout << TimePointToString(startTime) << "��" << TimePointToString(endTime) << "�������۶�Ϊ��" << totalsales << endl;       //��������۶�
    }

    void DisplaySalesByProduct()
    {
        time_t startTime;
        time_t endTime;
        vector<OrderItem> dataList;

        startTime = GetTimeInput("�����뿪ʼʱ�䣺");
        endTime = GetTimeInput("���������ʱ�䣺");

        dataList = database.CalculateAllSalesInformation(startTime, endTime);       //�������Ʒ������Ϣ

        cout << TimePointToString(startTime) << "��" << TimePointToString(endTime) << "ʱ���ڣ�" << endl;
        for (auto& data : dataList)
        {
            cout << data.product.name << "����������Ϊ��" << data.quantity << "�����۶�Ϊ��" << data.quantity * data.product.price << endl;      //���ÿ����Ʒ���������������۶�
        }

    }



};

#endif