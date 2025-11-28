#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <exception>

using element = int; 

namespace matf {
    class Stack {

        public:
            Stack();
            Stack(const Stack&);
            Stack& operator=(const Stack&);
            ~Stack();

            void Push(element);
            void Pop();
            element Top() const;

            size_t Size() const;

            Stack& operator<<(element);
            Stack& operator>>(element&);

            friend std::ostream& operator<<(std::ostream&, const Stack&);

        private:
            struct Node {
                element value;
                Node* next;
            };

            Node* m_top = nullptr;
            size_t m_size = 0;

            void ReverseList();
    };

    std::ostream& operator<<(std::ostream&, const Stack&);

}

#endif // STACK_HPP