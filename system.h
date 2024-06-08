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
    bool isUserAuthenticated = false; // 表示用户是否通过验证
public:
    void Run() {
        // 主运行函数，负责登录，展示欢迎信息和菜单，处理用户输入
        // 登录
        while (!isUserAuthenticated) {
            isUserAuthenticated = LoginProcedure();
            if (!isUserAuthenticated) {
                std::cout << "登录失败，请重试。" << std::endl;
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
        std::cout << "请输入用户名: ";
        std::cin >> username;
        std::cout << "请输入密码: ";
        std::cin >> password;

        // 验证用户名和密码
        return database.ValidateUser(username, password);
    }



    void DisplayWelcomeMessage() const {
        std::cout << "Welcome to the Coffee Shop Order Management System" << std::endl;
    }

    void DisplayMenu() const {
        // 简单的用户界面菜单
        cout << "—————————————————————————————————————" << endl;
        std::cout << "Please select an option:" << std::endl;
        std::cout << "1. 显示所有产品信息" << std::endl;
        std::cout << "2. 添加一个新的产品" << std::endl;
        std::cout << "3. 移除一个新的产品" << std::endl;
        std::cout << "4. 创建一个新的订单" << std::endl;
        std::cout << "5. 完成一个订单" << std::endl;
        std::cout << "6.取消一个订单" << std::endl;
        std::cout << "7. 显示所有订单" << std::endl;
        std::cout << "8. 显示一段时间内总销售额" << std::endl;
        std::cout << "9. 显示一段时间内各商品销售情况" << std::endl;
        std::cout << "10. 退出" << std::endl;
        cout << "—————————————————————————————————————" << endl;

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
        // 示范：询问用户输入商品信息，并添加到数据库
        int typeInput;      //producttype类型输入
        Product product;
        std::cout << "输入产品信息 (ID, Name, Price, Description, Category, Stock)" << endl;
        cout << "输入ID:";
        std::cin >> product.id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略前一个输入后的换行符
        cout << "输入名字:";
        std::getline(std::cin, product.name);
        cout << "输入价格:";
        cin >> product.price;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "输入产品描述:";
        getline(cin, product.description);
        cout << "输入产品种类:";
        cin >> typeInput;
        product.type = static_cast<ProductType>(typeInput);         //输入producttype类元素
        cout << "输入产品库存数:";
        cin >> product.stock;
        
        bool flag = database.AddProduct(product);
        if (flag == true)
            std::cout << "产品添加成功." << std::endl;
        else
            std::cout << "产品已存在。";
    }

    void RemoveProductProcedure() {
        // 示范：询问用户要删除的商品ID，并从数据库中删除
        int productId;
        std::cout << "请输入要移除的产品ID: ";
        std::cin >> productId;
        bool flag = database.DeleteProduct(productId);
        if (flag == true)
        {
            std::cout << "产品移除成功." << std::endl;
        }
        else
        {
            std::cout << "未找到产品 ID " << productId << "，删除操作未执行。" << std::endl;
        }
        
    }

    void EditProductProcedure()
    {
        int typeInput;      //producttype类型输入
        Product product;
        std::cout << "输入更改后的产品信息 (ID, Name, Price, Description, Category, Stock)" << endl;
        cout << "输入ID:";
        std::cin >> product.id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略前一个输入后的换行符
        cout << "输入名字:";
        std::getline(std::cin, product.name);
        cout << "输入价格:";
        cin >> product.price;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "输入产品描述:";
        getline(cin, product.description);
        cout << "输入产品种类:";
        cin >> typeInput;
        product.type = static_cast<ProductType>(typeInput);         //输入producttype类元素
        cout << "输入产品库存数:";
        cin >> product.stock;

        bool flag = database.EditProduct(product);
        if (flag == true)
            std::cout << "产品信息修改成功." << std::endl;
        else
            std::cout << "您想要修改的产品不存在。" <<std::endl;
    }

    void CreateOrderProcedure() {
        cout << "开始创建新订单。";

        Order order;
        cout << "请输入顾客姓名：";
        cin >> order.customer.name;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        order.orderNumber = database.CreateOrderNumber();   //生成订单号
        order.status = OrderStatus::Uncompleted; // 初始化订单状态为待处理
        order.time = std::time(nullptr); // 设置订单时间为当前时间

        bool addingProducts = true;
        while (addingProducts == true)
        {
            cout << "请选择订单商品编号 (输入0结束选择):" << endl;
            database.ShowAllProducts(); // 显示所有商品信息
            cout << "请输入选择商品编号：";

            int productId;
            cin >> productId;
            if (productId == 0) {
                addingProducts = false; // 用户完成商品选择
                
            }
            else {
                Product* product = database.FindProduct(productId);
                if (product != nullptr)
                {
                    // 将选择的商品添加到订单中
                    order.items.push_back(*product);
                    cout << "商品添加成功: " << product->name << endl;
                }
                else {
                    cout << "商品编号无效，请重新选择。" << endl;
                }
            }
        }

        bool isAdded = database.AddOrder(order);
        if (isAdded) {
            cout << "订单创建成功，订单编号: " << order.orderNumber << endl;
        }
        else {
            cout << "对不起，您所购买的商品已没有库存，请检查订单。" << endl;      //没有库存时取消订单
        }
    }

    void CancelOrderProcedure()
    {
        if (database.ShowAllOrders())
        {
            int orderId;
            cout << "输入要取消的订单编号：";
            cin >> orderId;
            bool flag = database.CancelOrder(orderId);
            if (flag)
            {
                cout << "订单取消成功。" << endl;
            }
            else
            {
                cout << "找不到可取消订单，请检查你的取消订单编号。" << endl;
            }
        }

        
    }

    void CompleteOrderProcedure() {
        int orderNumber;
        cout << "请输入要完成的订单编号: ";
        cin >> orderNumber;

        Order* order = database.FindOrder(orderNumber); // 查找订单

        if (order == nullptr) {
            // 订单未找到
            cout << "未找到订单号为 " << orderNumber << " 的订单。" << endl;
        }
        else {
            // 检查订单状态
            if (order->status == OrderStatus::Completed) {
                // 订单已经是完成状态
                cout << "订单号 " << orderNumber << " 已经是完成状态。" << endl;
            }
            else if (order->status == OrderStatus::Cancelled)
            {
                cout << "订单号 " << orderNumber << " 已取消，无法完成。" << endl;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
            }
            else {
                // 更新订单状态为已完成
                order->status = OrderStatus::Completed;
                cout << "订单号 " << orderNumber << " 现在标记为已完成。" << endl;
            }
        }
    }

    time_t GetTimeInput(const std::string& prompt) {
        std::tm timeInfo = {};
        std::cout << prompt << std::endl;
        std::cout << "请输入年份: "; std::cin >> timeInfo.tm_year;
        std::cout << "请输入月份: "; std::cin >> timeInfo.tm_mon;
        std::cout << "请输入日期: "; std::cin >> timeInfo.tm_mday;
        std::cout << "请输入小时: "; std::cin >> timeInfo.tm_hour;
        std::cout << "请输入分钟: "; std::cin >> timeInfo.tm_min;
        std::cout << "请输入秒数: "; std::cin >> timeInfo.tm_sec;

        timeInfo.tm_year -= 1900;
        timeInfo.tm_mon -= 1;
        timeInfo.tm_isdst = -1;  // 标记为 '不确定' 是否是夏令时

        return std::mktime(&timeInfo);
    }

    void  DisplayTotalSales()
    {
        time_t startTime;
        time_t endTime;
        double totalsales;

        startTime = GetTimeInput("请输入开始时间：");
        endTime = GetTimeInput("请输入结束时间：");

        
        totalsales = database.CalculateTotalSales(startTime, endTime);       // 计算总销售额

        cout << TimePointToString(startTime) << "到" << TimePointToString(endTime) << "的总销售额为：" << totalsales << endl;       //输出总销售额
    }

    void DisplaySalesByProduct()
    {
        time_t startTime;
        time_t endTime;
        vector<OrderItem> dataList;

        startTime = GetTimeInput("请输入开始时间：");
        endTime = GetTimeInput("请输入结束时间：");

        dataList = database.CalculateAllSalesInformation(startTime, endTime);       //计算出产品销售信息

        cout << TimePointToString(startTime) << "到" << TimePointToString(endTime) << "时间内；" << endl;
        for (auto& data : dataList)
        {
            cout << data.product.name << "的销售数量为：" << data.quantity << "；销售额为：" << data.quantity * data.product.price << endl;      //输出每种商品的销售数量和销售额
        }

    }



};

#endif