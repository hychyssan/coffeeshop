#define _CRT_SECURE_NO_WARNINGS

#include"database.h"



// ���һ���û��˻��ĺ���
void Database::AddUserAccount(const std::string& username, const std::string& password) {
    userAccounts.push_back({ username, password });
}

// �û���¼��֤�ĺ���
bool Database::ValidateUser(const std::string& username, const std::string& password) {
    for (const auto& account : userAccounts) {
        if (account.username == username && account.password == password) {
            return true; // ��֤�ɹ�
        }
    }
    return false; // ��֤ʧ��
}

bool Database::ShowAllProducts()
{
    if (products.empty())       //����ƷΪ��
    {
        cout << "���޲�Ʒ��" << endl;
        return false;
    }
    else
    {
        int count = 0;
        for (auto it = products.begin(); it != products.end(); it++)
        {
            cout << "��Ʒ" << ++count << "��Ϣ:\n";
            cout << "��ţ�" << it->id << endl
                << "���ƣ�" << it->name << endl
                << "�۸�" << it->price << endl
                << "������" << it->description << endl
                << "���ࣺ" << ProductTypeToString(it->type) << endl
                << "��棺" << it->stock << endl;
        }
        return true;
    }
}

bool Database::AddProduct(const Product& product) // �����Ʒ��Ϣ
{
    // �����Ʒ�Ƿ��Ѿ��������б���
    auto it = std::find_if(products.begin(), products.end(), [&product](const Product& p) {
        return p.id == product.id;
        });

    if (it != products.end()) {
        // ����ҵ���˵����ƷID�Ѵ��ڣ����������ﴦ����������������׳��쳣�򷵻ش������ȣ�
        return false; // �˳�����
    }
    else {
        // ���û���ҵ�����������Ӳ�Ʒ���б���
        products.push_back(product);
        return true;
    }
 }

bool Database::DeleteProduct(int productId) {
    // ʹ�� std::remove_if �㷨�� lambda ���ʽ���Ƴ������ض�id�Ĳ�Ʒ
    auto newEnd = std::remove_if(products.begin(), products.end(),
        [productId](const Product& product) {
            return product.id == productId;
        });

    // ����Ƿ��ҵ���Ҫɾ���Ĳ�Ʒ
    if (newEnd != products.end()) {
        // �Ƴ������д�newEnd��ĩβ������Ԫ��
        products.erase(newEnd, products.end());
        return true;
    }
    else {
        // ���û���ҵ�������false
        return false;
    }
}

    bool Database::EditProduct(const Product & productToUpdate) {
        // ���Ҿ��и���id�Ĳ�Ʒ
        auto it = std::find_if(products.begin(), products.end(),
            [&productToUpdate](const Product& product) {
                return product.id == productToUpdate.id;
            });

        

        if (it != products.end()) {
            // �ҵ��˲�Ʒ��������Ϣ
            it->id = productToUpdate.id;
            it->name = productToUpdate.name;
            it->price = productToUpdate.price;
            it->description = productToUpdate.description;
            it->type = productToUpdate.type;
            it->stock = productToUpdate.stock;
           
            // ����Product���ʵ������������Ը���������Ϣ
            return true;
        }
        else {
            // û���ҵ���Ʒ
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
            cout << "�Ҳ���ָ����Ʒ��" << endl;
            return nullptr;
        }
        else
        {
            return &*re;
        }
    }


    

    bool Database::AddOrder(const Order& order) {       //ʵ���˿�治��ʱ�Զ�ȡ������
        bool flag = true;

        vector<Product>tempProducts = products;     //�����ܲ�Ʒ����
        for (auto& product : order.items)   //����������Ʒ,���᲻����ֿ�治�������
        {
            Product* pProduct = FindProduct(product.id);     //������Ʒ��ַ
            pProduct->stock--;
            if (pProduct->stock < 0)       //������һ����Ʒ����ڹ�����С��0
            {
                flag = false;
                break;
            }
        }
        products = tempProducts;    //����Ʒ��渴ԭ��

        if (flag)       //�����в�Ʒ������ֿ�治�������
        {
            orders.push_back(order);
           
            for (auto& product : order.items)   //����������Ʒ����ȥ���
            {
                Product* pProduct = FindProduct(product.id);     //����������Ʒ��ַ
                {
                    pProduct->stock--;  //��ȥ���
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Database::CancelOrder(int orderNumber)       // ȡ������
    {
        auto it = find_if(orders.begin(), orders.end(), [orderNumber](const Order& order) {
            return order.orderNumber == orderNumber;
            });

        if (it != orders.end() && it->status == OrderStatus::Uncompleted)       //���ҵ��˶������Ҷ���Ϊδ���
        {
            for (auto& product : it->items)      //������Ʒ�����ؿ��
            {
                Product* pProduct = FindProduct(product.id);
                pProduct->stock++;      //��Ӧ��Ʒ���+1
            }
            

            // �ҵ��˶��������Ķ���״̬Ϊ��ȡ��
            it -> status = OrderStatus::Cancelled;
       
            return true;
        }
        else if (it != orders.end())     //���ҵ��˶������Ҷ��������
        {
            return false;
        }
        else 
        {
            // û���ҵ���Ӧ�����ŵĶ���

            return false;
        }
    }

    int Database::CreateOrderNumber() {
        int newOrderNumber = 1; // ��1��ʼ
        for (const auto& order : orders) {
            if (order.orderNumber >= newOrderNumber) {
                newOrderNumber = order.orderNumber + 1; // ȷ���¶������ǵ�ǰ���Ķ����ż�1
            }
        }
        return newOrderNumber;
    }

    bool Database::CompleteOrder(int orderNumber) {
        // ���������б�������Ӧ�Ķ���
        for (auto& order : orders) {
            if (order.orderNumber == orderNumber) {
                // ����ҵ��˶�����������Ƿ��Ѿ����
                if (order.status != OrderStatus::Completed) {
                    order.status = OrderStatus::Completed; // ������״̬����Ϊ�����
                    //std::cout << "���� " << orderNumber << " ����ɡ�" << std::endl;
                    return true;
                }
                else {
                    //std::cout << "���� " << orderNumber << " �Ѿ������״̬��" << std::endl;
                    return false;
                }
            }
        }
        // ���û���ҵ��������������ʾ��Ϣ
        //std::cout << "δ�ҵ�������Ϊ " << orderNumber << " �Ķ������޷����Ϊ��ɡ�" << std::endl;
        return false;
    }

    bool Database::ShowAllOrders()
    {
        if (orders.empty()) {
            std::cout << "û�ж�������ʾ��" << std::endl;
            return false;
        }

        for (const auto& order : orders) {
            std::cout << "�����ţ� " << order.orderNumber << std::endl;
            std::cout << "�˿������� " << order.customer.name << std::endl; // ����Customer�ṹ����һ����Ϊname���ֶ�
            std::cout << "����ʱ�䣺 " << TimePointToString(order.time) << std::endl;
            std::cout << "����״̬�� " << OrderStatusToString(order.status) << std::endl;

            std::cout << "��Ʒ�б�" << std::endl;
            for (const auto& product : order.items) {
                std::cout << "  - ��Ʒ��: " << product.name
                    << ", �۸�: " << product.price
                    << ", ����: " << product.stock << std::endl; // ����Product�а�����Щ�ֶ�
            }

            std::cout << std::endl; // �ڶ�������Ӷ���Ļ����Ա����Ķ�
        }
        return true;
    }


        Order* Database::FindOrder(int orderNumber)    // ���Ҷ�����Ϣ
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



        double Database::CalculateTotalSales(time_t startTime, time_t endTime)// ���������۶�
        {
            double totalSales = 0;
            for (auto& order:orders)
            {
                if (order.time >= startTime && order.time <= endTime && order.status != OrderStatus::Cancelled)         //��������ʱ�䷶Χ����δ��ȡ��
                {
                    for (auto& product : order.items)
                    {
                        totalSales += product.price;
                    }
                }
            }
            return totalSales;
        }


        OrderItem Database::CalculateSalesByProduct(int ProductId,time_t startTime, time_t endTime) // ����ĳ����Ʒ���������
        {
            OrderItem saleData;        //�����Ʒ��������
            saleData.product = *FindProduct(ProductId);      //�ҵ���Ʒ����
            saleData.quantity = 0;
           
            //ͳ����Ʒ������
            for (const auto& order : orders)
            {

                if (order.time >= startTime && order.time <= endTime &&order.status!= OrderStatus::Cancelled)       //��������ʱ�䷶Χ����δ��ȡ��
                {

                    auto count = std::count_if(order.items.begin(), order.items.end(), [ProductId](const Product& item) {
                        return item.id == ProductId;
                        });

                    // �ۼ���Ʒ����������
                    saleData.quantity += count;

                }
            }

            //������������
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