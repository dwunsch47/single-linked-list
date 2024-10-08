#pragma once

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

template <typename Type>
class SingleLinkedList {
    struct Node {
        Node() = default;

        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }

        Type value;
        Node* next_node = nullptr;
    };

    template <typename ValueType>
    class BasicIterator {
        friend class SingleLinkedList;

        explicit BasicIterator(Node* node) : node_(node) {}

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;

        BasicIterator() = default;

        BasicIterator(const BasicIterator<Type>& other) noexcept : node_(other.node_) {}

        BasicIterator& operator=(const BasicIterator& rhs) = default;

        template <typename IT>
        [[nodiscard]] bool operator==(const IT& rhs) const noexcept {
            return node_ == rhs.node_;
        }

        template <typename IT>
        [[nodiscard]] bool operator!=(const IT& rhs) const noexcept {
            return !(*this == rhs);
        }

        BasicIterator& operator++() noexcept {
            assert(node_);
            node_ = node_->next_node;
            return *this;
        }

        BasicIterator operator++(int) noexcept {
            auto last(*this);
            ++(*this);
            return last;
        }

        [[nodiscard]] reference operator*() const noexcept {
            assert(node_);
            return node_->value;
        }

        [[nodiscard]] pointer operator->() const noexcept {
            assert(node_);
            return &node_->value;
        }

    private:
        Node* node_ = nullptr;
    };

public:
    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;

    using Iterator = BasicIterator<Type>;
    using ConstIterator = BasicIterator<const Type>;

    SingleLinkedList() {}

    ~SingleLinkedList() {
        Clear();
    }

    SingleLinkedList(std::initializer_list<Type> values) {
        Transfer(values);
    }

    SingleLinkedList(const SingleLinkedList& other) {
        Transfer(other);
    }

    SingleLinkedList& operator=(const SingleLinkedList& rhs) {
        if (this != &rhs) {
            SingleLinkedList tmp(rhs);
            swap(tmp);
        }
        return *this;
    }

    void swap(SingleLinkedList& other) noexcept {
        std::swap(head_.next_node, other.head_.next_node);
        std::swap(size_, other.size_);
    }

    void PushFront(const Type& value) {
        Node* next = head_.next_node;
        head_.next_node = new Node(value, next);
        ++size_;
    }

    void Clear() noexcept {
        while (head_.next_node != nullptr) {
            PopFront();
        }
    }

    Iterator InsertAfter(ConstIterator pos, const Type& value) {
        assert(pos.node_);
        Node* new_element = new Node(value, pos.node_->next_node);
        pos.node_->next_node = new_element;
        ++size_;
        return Iterator(new_element);
    }

    void PopFront() noexcept {
        assert(!IsEmpty());
        delete std::exchange(head_.next_node, head_.next_node->next_node);
        --size_;
    }

    Iterator EraseAfter(ConstIterator pos) noexcept {
        assert(pos.node_);
        delete std::exchange(pos.node_->next_node, pos.node_->next_node->next_node);
        --size_;
        return Iterator(pos.node_->next_node);
    }

    [[nodiscard]] size_t GetSize() const noexcept {
        return size_;
    }

    [[nodiscard]] bool IsEmpty() const noexcept {
        return size_ == 0;
    }

    [[nodiscard]] Iterator begin() noexcept {
        return Iterator(head_.next_node);
    }

    [[nodiscard]] Iterator end() noexcept {
        return Iterator(nullptr);
    }

    [[nodiscard]] ConstIterator begin() const noexcept {
        return ConstIterator(head_.next_node);
    }

    [[nodiscard]] ConstIterator end() const noexcept {
        return ConstIterator(nullptr);
    }

    [[nodiscard]] ConstIterator cbegin() const noexcept {
        return ConstIterator(head_.next_node);
    }

    [[nodiscard]] ConstIterator cend() const noexcept {
        return ConstIterator(nullptr);
    }

    [[nodiscard]] Iterator before_begin() noexcept {
        return Iterator(&head_);
    }

    [[nodiscard]] ConstIterator cbefore_begin() const noexcept {
        return ConstIterator((Node*)&head_);
    }

    [[nodiscard]] ConstIterator before_begin() const noexcept {
        return ConstIterator((Node*)&head_);
    }

private:
    Node head_;
    size_t size_ = 0;

    template <typename T>
    void Transfer(const T& data) {
        SingleLinkedList tmp;
        auto it = tmp.before_begin();
        for (const auto& element : data) {
            tmp.InsertAfter(it, element);
            ++it;
        }
        swap(tmp);
    }
};

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs == rhs);
}

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return rhs < lhs;
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs > rhs);
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs < rhs);
}