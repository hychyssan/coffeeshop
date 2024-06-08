#define _CRT_SECURE_NO_WARNINGS

#include"type.h"

std::string ProductTypeToString(ProductType type) {
	switch (type) {
	case ProductType::LATTE: return "Latte Coffee";
	case ProductType::AMERICANO: return "Americano Coffee";
	case ProductType::CAKE:	return "Cake";
	default: return "Unknown";
	}
}


// ת�� std::chrono::system_clock::time_point ���ַ����ĺ���
std::string TimePointToString(const time_t& time) {

	// �� time_t ת��Ϊ tm �ṹ
	std::tm tm = *std::localtime(&time);

	// ʹ�� stringstream �� put_time �� tm ��ʽ��Ϊ�ַ���
	std::stringstream ss;
	ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); // ��ʽ���ַ���

	return ss.str(); // ����ת������ַ���
}



std::string OrderStatusToString(OrderStatus status) {
	switch (status) {
	case OrderStatus::Cancelled: return "Cancelled";
	case OrderStatus::Completed: return "Completed";
	case OrderStatus::Uncompleted:	return "Uncompleted";
	case OrderStatus::Processing:return "Processing";
	default: return "Unknown";
	}
}