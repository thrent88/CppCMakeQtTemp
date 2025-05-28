//
// Created by Thrent on 2025/5/25.
//

#ifndef DELETESTRUCTION_H
#define DELETESTRUCTION_H

// 删除类的拷贝构造函数、拷贝赋值运算符、移动构造函数和移动赋值运算符
// 以防止类的实例被复制或移动，确保类只能通过特定方式创建和管理。

#define DeleteClassStruction(ClassName) \
    private: \
    ClassName (const ClassName & ) = delete; \
    ClassName & operator=(const ClassName &) = delete; \
    ClassName ( ClassName &&) = delete; \
    ClassName & operator=( ClassName &&) = delete;
#endif //DELETESTRUCTION_H
