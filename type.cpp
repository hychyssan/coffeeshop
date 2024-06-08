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


// 转换 std::chrono::system_clock::time_point 到字符串的函数
std::string TimePointToString(const time_t& time) {

	// 将 time_t 转换为 tm 结构
	std::tm tm = *std::localtime(&time);

	// 使用 stringstream 和 put_time 将 tm 格式化为字符串
	std::stringstream ss;
	ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); // 格式化字符串

	return ss.str(); // 返回转换后的字符串
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