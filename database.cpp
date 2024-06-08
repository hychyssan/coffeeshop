#define _CRT_SECURE_NO_WARNINGS

#include"database.h"



// 添加一个用户账户的函数
void Database::AddUserAccount(const std::string& username, const std::string& password) {
    userAccounts.push_back({ username, password });
}

// 用户登录验证的函数
bool Database::ValidateUser(const std::string& username, const std::string& password) {
    for (const auto& account : userAccounts) {
        if (account.username == username && account.password == password) {
            return true; // 验证成功
        }
    }
    return false; // 验证失败
}

bool Database::ShowAllProducts()
{
    if (products.empty())       //若产品为空
    {
        cout << "暂无产品。" << endl;
        return false;
    }
    else
    {
        int count = 0;
        for (auto it = products.begin(); it != products.end(); it++)
        {
            cout << "商品" << ++count << "信息:\n";
            cout << "编号：" << it->id << endl
                << "名称：" << it->name << endl
                << "价格：" << it->price << endl
                << "描述：" << it->description << endl
                << "种类：" << ProductTypeToString(it->type) << endl
                << "库存：" << it->stock << endl;
        }
        return true;
    }
}

bool Database::AddProduct(const Product& product) // 添加商品信息
{
    // 检查商品是否已经存在于列表中
    auto it = std::find_if(products.begin(), products.end(), [&product](const Product& p) {
        return p.id == product.id;
        });

    if (it != products.end()) {
        // 如果找到，说明商品ID已存在，可以在这里处理这种情况（例如抛出异常或返回错误代码等）
        return false; // 退出函数
    }
    else {
        // 如果没有找到，就正常添加产品到列表中
        products.push_back(product);
        return true;
    }
 }

bool Database::DeleteProduct(int productId) {
    // 使用 std::remove_if 算法和 lambda 表达式来移除具有特定id的产品
    auto newEnd = std::remove_if(products.begin(), products.end(),
        [productId](const Product& product) {
            return product.id == productId;
        });

    // 检查是否找到了要删除的产品
    if (newEnd != products.end()) {
        // 移除向量中从newEnd到末尾的所有元素
        products.erase(newEnd, products.end());
        return true;
    }
    else {
        // 如果没有找到，返回false
        return false;
    }
}

    bool Database::EditProduct(const Product & productToUpdate) {
        // 查找具有给定id的产品
        auto it = std::find_if(products.begin(), products.end(),
            [&productToUpdate](const Product& product) {
                return product.id == productToUpdate.id;
            });

        

        if (it != products.end()) {
            // 找到了产品，更新信息
            it->id = productToUpdate.id;
            it->name = productToUpdate.name;
            it->price = productToUpdate.price;
            it->description = productToUpdate.description;
            it->type = productToUpdate.type;
            it->stock = productToUpdate.stock;
           
            // 根据Product类的实际情况，还可以更新其他信息
            return true;
        }
        else {
            // 没有找到产品
            return false;
        }
}



    Product* Database::FindProduct(int productId)
    {

        auto re = find_if(begin(products), end(products), [productId](const Product& product) {
            return product.id == productId;
            });
        if(re == products.end())
        {
            cout << "找不到指定商品。" << endl;
            return nullptr;
        }
        else
        {
            return &*re;
        }
    }


    

    bool Database::AddOrder(const Order& order) {       //实现了库存不够时自动取消订单
        bool flag = true;

        vector<Product>tempProducts = products;     //复制总产品数组
        for (auto& product : order.items)   //遍历订单商品,检查会不会出现库存不够的情况
        {
            Product* pProduct = FindProduct(product.id);     //订单商品地址
            pProduct->stock--;
            if (pProduct->stock < 0)       //若其中一个商品库存在购买中小于0
            {
                flag = false;
                break;
            }
        }
        products = tempProducts;    //将产品库存复原；

        if (flag)       //若所有产品不会出现库存不够的情况
        {
            orders.push_back(order);
           
            for (auto& product : order.items)   //遍历订单商品，减去库存
            {
                Product* pProduct = FindProduct(product.id);     //遍历订单商品地址
                {
                    pProduct->stock--;  //减去库存
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Database::CancelOrder(int orderNumber)       // 取消订单
    {
        auto it = find_if(orders.begin(), orders.end(), [orderNumber](const Order& order) {
            return order.orderNumber == orderNumber;
            });

        if (it != orders.end() && it->status == OrderStatus::Uncompleted)       //若找到了订单，且订单为未完成
        {
            for (auto& product : it->items)      //遍历产品，补回库存
            {
                Product* pProduct = FindProduct(product.id);
                pProduct->stock++;      //对应产品库存+1
            }
            

            // 找到了订单，更改订单状态为已取消
            it -> status = OrderStatus::Cancelled;
       
            return true;
        }
        else if (it != orders.end())     //若找到了订单，且订单已完成
        {
            return false;
        }
        else 
        {
            // 没有找到对应订单号的订单

            return false;
        }
    }

    int Database::CreateOrderNumber() {
        int newOrderNumber = 1; // 从1开始
        for (const auto& order : orders) {
            if (order.orderNumber >= newOrderNumber) {
                newOrderNumber = order.orderNumber + 1; // 确保新订单号是当前最大的订单号加1
            }
        }
        return newOrderNumber;
    }

    bool Database::CompleteOrder(int orderNumber) {
        // 遍历订单列表，查找相应的订单
        for (auto& order : orders) {
            if (order.orderNumber == orderNumber) {
                // 如果找到了订单，检查它是否已经完成
                if (order.status != OrderStatus::Completed) {
                    order.status = OrderStatus::Completed; // 将订单状态更新为已完成
                    //std::cout << "订单 " << orderNumber << " 已完成。" << std::endl;
                    return true;
                }
                else {
                    //std::cout << "订单 " << orderNumber << " 已经是完成状态。" << std::endl;
                    return false;
                }
            }
        }
        // 如果没有找到订单，则输出提示信息
        //std::cout << "未找到订单号为 " << orderNumber << " 的订单，无法标记为完成。" << std::endl;
        return false;
    }

    bool Database::ShowAllOrders()
    {
        if (orders.empty()) {
            std::cout << "没有订单可显示。" << std::endl;
            return false;
        }

        for (const auto& order : orders) {
            std::cout << "订单号： " << order.orderNumber << std::endl;
            std::cout << "顾客姓名： " << order.customer.name << std::endl; // 假设Customer结构包含一个名为name的字段
            std::cout << "订单时间： " << TimePointToString(order.time) << std::endl;
            std::cout << "订单状态： " << OrderStatusToString(order.status) << std::endl;

            std::cout << "商品列表：" << std::endl;
            for (const auto& product : order.items) {
                std::cout << "  - 商品名: " << product.name
                    << ", 价格: " << product.price
                    << ", 数量: " << product.stock << std::endl; // 假设Product中包含这些字段
            }

            std::cout << std::endl; // 在订单间添加额外的换行以便于阅读
        }
        return true;
    }


        Order* Database::FindOrder(int orderNumber)    // 查找订单信息
        {
            for (auto& order : orders)
            {
                if (order.orderNumber == orderNumber)
                {
                    return &order;
                }
            }
            return nullptr;
        }



        double Database::CalculateTotalSales(time_t startTime, time_t endTime)// 计算总销售额
        {
            double totalSales = 0;
            for (auto& order:orders)
            {
                if (order.time >= startTime && order.time <= endTime && order.status != OrderStatus::Cancelled)         //当订单在时间范围内且未被取消
                {
                    for (auto& product : order.items)
                    {
                        totalSales += product.price;
                    }
                }
            }
            return totalSales;
        }


        OrderItem Database::CalculateSalesByProduct(int ProductId,time_t startTime, time_t endTime) // 计算某种商品的销售情况
        {
            OrderItem saleData;        //存放商品销售数据
            saleData.product = *FindProduct(ProductId);      //找到商品名称
            saleData.quantity = 0;
           
            //统计商品销售量
            for (const auto& order : orders)
            {

                if (order.time >= startTime && order.time <= endTime &&order.status!= OrderStatus::Cancelled)       //当订单在时间范围内且未被取消
                {

                    auto count = std::count_if(order.items.begin(), order.items.end(), [ProductId](const Product& item) {
                        return item.id == ProductId;
                        });

                    // 累加商品的销售数量
                    saleData.quantity += count;

                }
            }

            //返回销售数据
            return saleData;
        }

        std::vector<OrderItem> Database::CalculateAllSalesInformation(time_t startTime, time_t endTime)
        {
            vector<OrderItem> dataList;
            for (auto& product : products)
            {
                dataList.push_back(CalculateSalesByProduct(product.id, startTime, endTime));
            }

            return dataList;
        }