#pragma once
#include "SocketUtil.h"
#include <vector>
#include <memory>
#include <iterator>

class BloodSocket;

class FdSetWrapper {
public:
    FdSetWrapper();

    void AddSocket(const std::shared_ptr<BloodSocket>& socket);

    bool IsSocketActive(const std::shared_ptr<BloodSocket>& socket) const;

    fd_set* GetRawFdSet();
   
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::shared_ptr<BloodSocket>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        iterator(FdSetWrapper* owner, const std::vector<std::shared_ptr<BloodSocket>>& sockets)
            : owner(owner), sockets(sockets), index(0) {
            moveToNextActive();
        }

        value_type operator*() {
            return sockets[index];
        }

        iterator& operator++() {
            moveToNextActive();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const iterator& a, const iterator& b) {
            return a.index == b.index;
        }

        friend bool operator!=(const iterator& a, const iterator& b) {
            return a.index != b.index;
        }

    private:
        FdSetWrapper* owner;
        const std::vector<std::shared_ptr<BloodSocket>>& sockets;
        size_t index;

        void moveToNextActive() {
            while (index < sockets.size() && !owner->IsSocketActive(sockets[index])) {
                ++index;
            }
        }
    };

    iterator begin(const std::vector<std::shared_ptr<BloodSocket>>& sockets) {
        return iterator(this, sockets);
    }

    iterator end(const std::vector<std::shared_ptr<BloodSocket>>& sockets) {
        return iterator(this, sockets);
    }

    iterator begin() {
        return iterator(this, sockets);
    }

    iterator end() {
        return iterator(this, sockets);
    }
private:
    fd_set fdSet;
    std::vector<std::shared_ptr<BloodSocket>> sockets; 

};
