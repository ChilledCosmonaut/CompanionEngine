#pragma once

#include <unordered_map>

namespace gl3::engine::filesystem {
    template<typename Key, typename CacheObject>
    class Cache {
    public:
        typedef typename std::pair<Key, CacheObject> cachedData;
        typedef typename std::list<cachedData>::iterator listPointer;

        Cache(int maxSize){
            this->maxSize = maxSize;
        }

        ~Cache() {

        }

        void AddItem(Key key, CacheObject item) {
            auto cachedObject = cachePointer.find(key);

            if(cachedObject != cachePointer.end()){
                cacheList.erase(cachedObject->second);
            }

            if(cacheList.size() >= maxSize){
                listPointer elementToBeDeleted = std::prev(cacheList->end());
                cachePointer->erase(elementToBeDeleted->first);
                cacheList->pop_back();
            }

            cacheList.push_front(item);
            cachePointer[key] = cacheList->begin();
        }

        bool Contains(Key key) {
            if (cachePointer.find(key) == cachePointer.end())
                return false;
            return true;
        }

        const CacheObject& Get(Key key) {
            auto cachedObject = cachePointer.find(key);
            if (cachedObject == cachePointer.end())
                throw std::range_error("There is no such key in cache");

            cacheList.splice(cacheList.begin(), cacheList, cachedObject->second);
            return cachedObject->second->second;
        }

    private:
        std::unordered_map<Key, listPointer> cachePointer;
        cachedData cacheList {};
        size_t maxSize;
    };
}
