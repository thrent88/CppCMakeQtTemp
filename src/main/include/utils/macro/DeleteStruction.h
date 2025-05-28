//
// Created by Thrent on 2025/5/25.
//

#ifndef DELETESTRUCTION_H
#define DELETESTRUCTION_H

#define DeleteClassStruction(ClassName) \
    private: \
    ClassName (const ClassName & ) = delete; \
    ClassName & operator=(const ClassName &) = delete; \
    ClassName ( ClassName &&) = delete; \
    ClassName & operator=( ClassName &&) = delete;
#endif //DELETESTRUCTION_H
