#ifndef __ITERATOR_H__ 
#define __ITERATOR_H__ 

// #include "composite.h" 
#include <iostream>
#include <stack>

using namespace std;

class Base;

class Iterator { 
    protected: 
        Base* self_ptr; 
        Base* current_ptr; 
    public: 
        Iterator(Base* ptr) { this->self_ptr = ptr; current_ptr = NULL; }; 
        // Iterator(Base* ptr1, Base* ptr2) { this->self_ptr = ptr1; this->current_ptr = ptr2; }; 
        
        /* Sets up the iterator to start at the beginning of traversal */ 
        virtual void first() = 0; 
        /* Move onto the next element */ 
        virtual void next() = 0; 
        /* Returns if you have finished iterating through all elements */ 
        virtual bool is_done() = 0; 
        /* Return the element the iterator is currently at */ 
        virtual Base* current() = 0; 
}; 

class OperatorIterator : public Iterator { 
    public: 
        OperatorIterator(Base* ptr) : Iterator(ptr) {}; 

        void first() {
            Iterator* temp_itr = self_ptr->get_left()->create_iterator();
            
            if (temp_itr)
                temp_itr->first();
        }; 
        void next() {
            Iterator* temp_itr = self_ptr->get_left()->create_iterator();

            if (temp_itr)
                temp_itr->first();
            else {
                temp_itr = self_ptr->get_right()->create_iterator();

                if (temp_itr)
                    temp_itr->first();
                else 
                    return;    
            }  
        }; 
        bool is_done() { return false; }; 
        Base* current() {
            // if (self_ptr->get_left()) {
            //     return self_ptr->get_left();
            // }
            // else if (self_ptr->get_right()) {
            //     return self_ptr->get_right();
            // }
            // else {
            //     return NULL;
            // }
            return self_ptr;
        }; 
}; 

class UnaryIterator : public Iterator { 
    public: 
        UnaryIterator(Base* ptr) : Iterator(ptr) {}; 

        void first() {
            Iterator* temp_itr = self_ptr->get_left()->create_iterator();
            
            if (temp_itr)
                temp_itr->first();
        }; 
        void next() {
            Iterator* temp_itr = self_ptr->get_left()->create_iterator();

            if (temp_itr)
                temp_itr->first();
            else 
                return;    
        }; 
        bool is_done() { return false; }; 
        Base* current() {
            // if (self_ptr->get_left()) {
            //     return self_ptr->get_left();
            // }
            // else {
            //     return NULL;
            // }
            return self_ptr;
        }; 
}; 

class NullIterator : public Iterator { 
    public: 
        NullIterator(Base* ptr) : Iterator(ptr) {}; 

        void first() { return; }; 
        void next() { return; }; 
        bool is_done() { return true; }; 
        Base* current() { return NULL; }; 
}; 

class PreOrderIterator : public Iterator { 
    protected:
        stack<Iterator*> itr;
    
    public: 
        PreOrderIterator(Base* ptr) : Iterator(ptr) {}; 

        void first() {
            // Empty the stack (just in case we had something leftover from another run) 
            // Create an iterator for the Base* that we built the iterator for 
            // Initialize that iterator and push it onto the stack 
            while (!itr.empty()) {
                itr.pop();
            }

            Iterator* temp_itr = self_ptr->get_left()->create_iterator();

            if (temp_itr)
                temp_itr->first();

            itr.push(temp_itr);
        }; 
        
        void next() {
            // Create an iterator for the item on the top of the stack 
            // Initialize the iterator and push it onto the stack 
            // As long as the top iterator on the stack is_done(), pop it off the stack and then advance whatever iterator is now on top of the stack 
            Base* temp_base = this->current();

            if (temp_base) {
                Iterator* temp_itr = temp_base->create_iterator();
                temp_itr->first();
                itr.push(temp_itr);
            }

            if (itr.top()->is_done()) {
                itr.pop();
                if (!itr.empty())
                    itr.top()->next();
            }
        }; 
        
        bool is_done() {
            // Return true if there are no more elements on the stack to iterate 
            if (itr.size() == 0) 
                return true;

            return false;    
        };

        Base* current() {
            // Return the current for the top iterator in the stack 
            if (itr.size() > 0) {
                return itr.top()->current();
            }
            return NULL;
        }; 
}; 

#endif //__ITERATOR_H__ 