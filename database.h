#define _CRT_SECURE_NO_WARNINGS

#ifndef _DATABASE_H
#define _DATABASE_H

#include<vector>
#include"type.h"
using namespace std;

class Database
{
private:
    std::vector<UserAccount> userAccounts = { UserAccount{"admin", "adminpass"} };       //�˻�����
    std::vector<Product> products;      //��Ʒ����
    std::vector<Order> orders;          //��������

public:

    Database()          //���캯��
    {
        Product a{ 1, "Sweet Coffee", 3.50, "A cup of sugar coffee", ProductType::LATTE, 100 };
        Product b{ 2, "Sour Coffee", 5.50, "A cup of sour coffee", ProductType::AMERICANO, 100 };
        Product c{ 3, "chocolate cake", 10, "A big cake", ProductType::CAKE, 10 };
        products.push_back(a);
        products.push_back(b);
        products.push_back(c);
    }

    //��¼����
    void AddUserAccount(const std::string& username, const std::string& password);
    bool ValidateUser(const std::string& username, const std::string& password);

    // ��Ʒ��Ϣ����
    bool ShowAllProducts();  // ��ʾ������Ʒ��Ϣ
    bool AddProduct(const Product& product); // �����Ʒ��Ϣ
    bool DeleteProduct(int productId);       // ɾ����Ʒ��Ϣ
    bool EditProduct(const Product& product); // �޸���Ʒ��Ϣ
    Product* FindProduct(int productId);     // ������Ʒ��Ϣ

    // ������Ϣ����
    bool AddOrder(const Order& order);    // ��Ӷ���
    bool CancelOrder(int orderNumber);       // ȡ������
    bool CompleteOrder(int orderNumber);     // ��ɶ���
    bool ShowAllOrders();                   // ��ʾ���ж�����Ϣ
    Order* FindOrder(int orderNumber);       // ���Ҷ�����Ϣ

    // ����ͳ�ƹ���
    double CalculateTotalSales(time_t startTime, time_t endTime);       // ���������۶�
    OrderItem CalculateSalesByProduct(int productId,time_t startTime, time_t endTime);     // ����ÿ����Ʒ���������
    vector<OrderItem> CalculateAllSalesInformation(time_t startTime, time_t endTime);

    int CreateOrderNumber();        //�����µĲ��ظ��������
};

#endif 