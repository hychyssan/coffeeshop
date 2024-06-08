#define _CRT_SECURE_NO_WARNINGS

#ifndef _DATABASE_H
#define _DATABASE_H

#include<vector>
#include"type.h"
using namespace std;

class Database
{
private:
    std::vector<UserAccount> userAccounts = { UserAccount{"admin", "adminpass"} };       //账户密码
    std::vector<Product> products;      //产品数据
    std::vector<Order> orders;          //订单数据

public:

    Database()          //构造函数
    {
        Product a{ 1, "Sweet Coffee", 3.50, "A cup of sugar coffee", ProductType::LATTE, 100 };
        Product b{ 2, "Sour Coffee", 5.50, "A cup of sour coffee", ProductType::AMERICANO, 100 };
        Product c{ 3, "chocolate cake", 10, "A big cake", ProductType::CAKE, 10 };
        products.push_back(a);
        products.push_back(b);
        products.push_back(c);
    }

    //登录管理
    void AddUserAccount(const std::string& username, const std::string& password);
    bool ValidateUser(const std::string& username, const std::string& password);

    // 商品信息管理
    bool ShowAllProducts();  // 显示所有商品信息
    bool AddProduct(const Product& product); // 添加商品信息
    bool DeleteProduct(int productId);       // 删除商品信息
    bool EditProduct(const Product& product); // 修改商品信息
    Product* FindProduct(int productId);     // 查找商品信息

    // 订单信息管理
    bool AddOrder(const Order& order);    // 添加订单
    bool CancelOrder(int orderNumber);       // 取消订单
    bool CompleteOrder(int orderNumber);     // 完成订单
    bool ShowAllOrders();                   // 显示所有订单信息
    Order* FindOrder(int orderNumber);       // 查找订单信息

    // 财务统计功能
    double CalculateTotalSales(time_t startTime, time_t endTime);       // 计算总销售额
    OrderItem CalculateSalesByProduct(int productId,time_t startTime, time_t endTime);     // 计算每种商品的销售情况
    vector<OrderItem> CalculateAllSalesInformation(time_t startTime, time_t endTime);

    int CreateOrderNumber();        //创建新的不重复订单编号
};

#endif 