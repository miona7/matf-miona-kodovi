#include "stack.hpp"

namespace matf {
    // nas konstruktor == podrazumevani konstruktor (kompajler ce ga sam izgenerisati)
    Stack::Stack() = default;

    Stack::Stack(const Stack& s) {
        for(auto current = s.m_top; current != nullptr; current = current->next) {
            Push(current->value);
        }
        ReverseList();
    }

    Stack& Stack::operator=(const Stack& s) {
        // copy and swap idiom
        Stack tmp(s);
        std::swap(m_top, tmp.m_top);
        std::swap(m_size, tmp.m_size);
        return *this;

        /*
        if(this != &s) {
            while(m_top) {
                Pop();
            }
            for(auto current = s.m_top; current != nullptr; current = current->next) {
                Push(current->value);
            }
            ReverseList();
        }
        */
    }

    Stack::~Stack() {
        while(m_top) {
            Pop();
        }
    }

    void Stack::Push(element e) {
        m_top = new Node {e, m_top};
        m_size++;
    }

    void Stack::Pop() {
        Node* old_top = m_top;
        m_top = m_top->next;
        delete old_top;
        m_size--;
    }

    element Stack::Top() const {
        if(m_size != 0) {
            return m_top->value;
        } else {
            throw std::invalid_argument("stack is empthy");
        }
    }

    size_t Stack::Size() const {
        return m_size;
    }

    Stack& Stack::operator<<(element e) {
        Push(e);
        return *this;
    }
    
    Stack& Stack::operator>>(element& e) {
        e = Top();
        Pop();
        return *this;
    }

    void Stack::ReverseList() {
        Node* previous = nullptr;
        Node* current = m_top;
        while(current) {
            Node* next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }        
        m_top = previous;
    }

    std::ostream& operator<<(std::ostream& out, const Stack& s) {
        out << "[";

        for(auto current = s.m_top; current != nullptr; current = current->next) {
            out << current->value;
            if(current->next != nullptr) {
                out << ", ";
            }
        }

        return out << "]";
    }
} 
