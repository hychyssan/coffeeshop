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
	LATTE,			//����	
	AMERICANO,		//��ʽ
	CAKE			//����
};

// ��Ʒ��Ϣ�ṹ��
struct Product
{
	int id;					//��Ʒ���
	string name;			//����
	double price;			//�۸�
	string description;		//����
	ProductType type;		//����
	int stock;				// ��Ʒ���
};


// �˿���Ϣ�ṹ��
struct Customer {
	std::string name;     // �˿�����
};


//����״̬ö��
enum class OrderStatus {
	Uncompleted,	// δ���
	Processing,		// ������
	Completed,		// �����
	Cancelled	   // ��ȡ��
};


struct Order {
	int  orderNumber;                        // ������
	Customer customer;							// �˿���Ϣ
	time_t time; // ����ʱ��
	OrderStatus status;                         // ����״̬
	vector<Product> items;					// ��Ʒ���б�
};

// ������ṹ��
struct OrderItem {
	Product product;  // ��Ʒ����
	int quantity;   // ����
};


// �û��˻���Ϣ�ṹ��
struct UserAccount {
	std::string username; // �û���
	std::string password; // ����
};




std::string ProductTypeToString(ProductType type);
// ת�� std::chrono::system_clock::time_point ���ַ����ĺ���
std::string TimePointToString(const time_t& time);
std::string OrderStatusToString(OrderStatus status);







#endif