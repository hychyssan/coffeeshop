#define _CRT_SECURE_NO_WARNINGS

#ifndef TYPE_H_
#define TYPE_H_

#include<string>
#include<vector>
#include<iostream>
#include<ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include<algorithm>


using namespace std;


enum class ProductType {
	LATTE,			//拿铁	
	AMERICANO,		//美式
	CAKE			//蛋糕
};

// 商品信息结构体
struct Product
{
	int id;					//商品编号
	string name;			//名称
	double price;			//价格
	string description;		//描述
	ProductType type;		//分类
	int stock;				// 商品库存
};


// 顾客信息结构体
struct Customer {
	std::string name;     // 顾客姓名
};


//订单状态枚举
enum class OrderStatus {
	Uncompleted,	// 未完成
	Processing,		// 处理中
	Completed,		// 已完成
	Cancelled	   // 已取消
};


struct Order {
	int  orderNumber;                        // 订单号
	Customer customer;							// 顾客信息
	time_t time; // 订单时间
	OrderStatus status;                         // 订单状态
	vector<Product> items;					// 商品项列表
};

// 订单项结构体
struct OrderItem {
	Product product;  // 商品类型
	int quantity;   // 数量
};


// 用户账户信息结构体
struct UserAccount {
	std::string username; // 用户名
	std::string password; // 密码
};




std::string ProductTypeToString(ProductType type);
// 转换 std::chrono::system_clock::time_point 到字符串的函数
std::string TimePointToString(const time_t& time);
std::string OrderStatusToString(OrderStatus status);







#endif