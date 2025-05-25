//
// Created by Thrent on 2025/5/25.
//

#ifndef OBJECTSTORE_H
#define OBJECTSTORE_H

#include <map>
#include <QObject>
#include "app/store/ObjectIDs.h"

#define OBJECT_STORE (store::ObjectStore::GetInstance())
#define REGISTER_OBJECT(name, object) (OBJECT_STORE->RegisterObject(name, object))
#define GET_OBJECT(T, name) (OBJECT_STORE->GetObject<T>(name))

namespace store {
    class ObjectStore {
        using ObjectMap = std::map<std::string, QObject *>;

    public:
        // 获取单实例对象
        static ObjectStore *GetInstance();

        /**
         * 注册对象
         * @param name
         * @param object
         * @return
         */
        void RegisterObject(const char* name, QObject *object);

        /**
         * 获取对象
         * @tparam T
         * @param name
         * @return
         */
        template<typename T>
        T *GetObject(const std::string name) {
            if (objectMap.find(name) == objectMap.end()) {
                return nullptr;
            }
            return dynamic_cast<T *>(objectMap[name]);
        }

    private:
        // 禁止外部构造
        ObjectStore();

        // 禁止外部析构
        ~ObjectStore();

        // 禁止外部拷贝构造
        ObjectStore(const ObjectStore &single) = delete;

        // 禁止外部赋值操作
        const ObjectStore &operator=(const ObjectStore &single) = delete;

        ObjectMap objectMap;
        static ObjectStore *instance;
    };
} // store


#endif //OBJECTSTORE_H
