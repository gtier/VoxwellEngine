//
//  ThreadsafeQueue.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 11/6/20.
//  Copyright © 2020 Griffin Dunaif. All rights reserved.
//

#ifndef ThreadsafeQueue_hpp
#define ThreadsafeQueue_hpp

#include <stdio.h>
#include <queue>
#include <mutex>
#include <utility>

template <class T>
class ThreadsafeQueue
{
public:
    ThreadsafeQueue()
    {
    }
    
    void enqueue(T&& item)
    {
        std::lock_guard<std::mutex> lg(m);
        q.push(std::move(item));
    }
    
    void mv_dequeue(T& mv_dest)
    {
        std::lock_guard<std::mutex> lg(m);
        mv_dest = std::move(q.front());
        q.pop();
    }
    
    bool empty() {
//        std::lock_guard<std::mutex> lg(m);
        return q.empty();
    }
    
private:
    std::queue<T> q;
    std::mutex m;
};

#endif /* ThreadsafeQueue_hpp */
