//
// Created by Thrent on 2025/5/25.
//

#include "store/ObjectStore.h"

namespace store {
    ObjectStore::ObjectStore() {
    }

    ObjectStore::~ObjectStore() {
    }

    ObjectStore* ObjectStore::instance = new ObjectStore();

    // 获取单实例对象
    ObjectStore* ObjectStore::GetInstance() {
        return instance;
    }

    void ObjectStore::RegisterObject(const char* name, QObject *object) {
        if (objectMap.find(name) != objectMap.end()) {
            throw std::runtime_error("object already exists");
        }

        if (object == nullptr) {
            throw std::runtime_error("object is null");
        }
        objectMap[name] = object;
    }
} // store