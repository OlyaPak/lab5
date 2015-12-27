#include <iostream>     // std::ostream
#include <stdexcept>    // std::out_of_range
#include <string>       // std::to_string()
#include <utility>      // std::swap()

#include "LinkedList.h"

LinkedList& LinkedList::operator=(const LinkedList& rhs)
{
    //TODO(13)
    if (this == &rhs){
        return *this;
    }
    clear();
    Node* node_= rhs.first;
    while(node_)
    {
        push_back(node_->value);
        node_=node_->next;
    }
    std::cout <<  "target len " << size() << " source len " << rhs.size() << std::endl;
    return *this;
}
LinkedList& LinkedList::operator=(LinkedList&& rhs)
{
    //(15)
    //clear();
    swap(*this, rhs);
    return *this;
}

bool LinkedList::operator==(const LinkedList& other) const
{
    //(16) оператор сравнения

    if (this->size() != other.size())
    {
        return false;
    }
    else
    {
        Node* Node_this = this->first;
        Node* Node_other = other.first;
        bool fl=true;
        while (Node_this)
        {
            if (Node_other->value!=Node_this->value)
            {
                fl=false;
            }
            Node_other=Node_other->next;
            Node_this=Node_this->next;
        }
        return fl;
    }
}
bool LinkedList::operator!=(const LinkedList& other) const
{
    //(14) не равны
    if (this->size() != other.size())
    {
        return true;
    }
    else
    {
        Node* Node_this = this->first;
        Node* Node_other = other.first;
        bool fl=false;
        while (Node_this)
        {
            if (Node_other->value=Node_this->value)
            {
                fl=true;
            }
            Node_other=Node_other->next;
            Node_this=Node_this->next;
        }
        return fl;
    }
    //(14)
}

    void LinkedList:: clear()
    {
        //TODO (11)Очистка списка
        while (size_)
            erase (first);
    }

    void LinkedList::erase(const Node* node)
    {
        //(9) удаляет узел
        if (node->next)
            node->next->previous=node->previous;
        else last=node->previous;
        if (node->previous)
            node->previous->next=node->next;
        else first=node->next;
        delete node;
        --size_;
    }

    void LinkedList::pop_back()
//TODO (8) удаляет элемент в конце списка
    {
        erase(last);
    }

    void LinkedList::pop_front()
    {
        //TODO (10) удаляет первый узел
        erase(first);
    }


/*
    LinkedList::Node* LinkedList::insert_after(LinkedList::Node* after)
    {
        return nullptr;
    }


    LinkedList::Node* LinkedList::insert_before(LinkedList::Node* before)
    {
        return nullptr;
    }

*/
    void LinkedList::push_back(const Data& value)
    {
        // TODO добавление нового узла в конец списка
        //(5)
        // создаем переменную типа  узел
        Node* node_= new Node;
        node_->value=value;
        node_->previous=last;
        node_->next = nullptr;
        //добавляем в конец узел,если у нас количество узлов не ноль
        if(last!=nullptr)
        {
            last->next=node_;
        }
        last=node_;
//    иначе добавляем первый элемент
        if(first==nullptr)
        {
            first=node_;
        }
        ++size_;// должен увеличивать размер
    }



    void LinkedList::push_front(const Data& value)
    {
        // добавляет узел в начало
        Node* node_ = new Node;
        node_->value = value;
        node_->previous = nullptr;
        node_->next = first;
        if (first != nullptr)
        {
            first->previous = node_;
        }
        first = node_;
        if (last == nullptr)
        {
            last = node_;
        }
        ++size_;
    }
    void swap(LinkedList& left, LinkedList& right)
    {
        //(12)  TODO меняет местами связные списки
        //достаточно поменять только первый и последний элементы тк
        // они содержат указатели на все остальные элементы
        // HINT: Функция std::swap() меняет значения простых типов.
        std::swap(right.first,left.first);
        std::swap(right.last,left.last);
        std::swap(right.size_,left.size_);
    }

    LinkedList::LinkedList()
    {
        // TODO
        //(3)
        //конструктор пустой инициализации
        first=nullptr;
        last=nullptr;
        size_=0;
    }



    LinkedList::LinkedList(const std::initializer_list<Data> values) :
        LinkedList()
    {
        // По std::initializer_list<T> возможен диапазонный for.
        for (const Data& value : values)
        {
            push_back(value);
        }
    }

    LinkedList::LinkedList(const LinkedList& source)
        :LinkedList()
//(4) конструктор копирования
    {
        // TODO
        // HINT:
        // Здесь нельзя воспользоваться диапазонным for, потому что на данном
        // этапе задания у списка не реализованы итераторы, begin() и end().
        Node* node_=source.first;
        while(node_)
        {
            push_back(node_->value);
            node_= node_->next;
        }
    }


    LinkedList::LinkedList(LinkedList&& source) //конструктор перемещения
        : LinkedList()
    {
        swap(*this, source);
    }

    LinkedList::~LinkedList()
    {
        clear();
    }

    size_t LinkedList::size() const
    {
        return LinkedList::size_;

    }

    Data& LinkedList::value_at(size_t index)
    {
        // TODO(6)
        // возвращает value выбранного узла
        Node* node_ =first;
        int i=0;
        if(index>=size_)
            throw std::out_of_range("Index>size_");
        while(node_)
        {

            if(i==index)
            {
                return node_->value;
            }
            node_=node_->next;
            ++i;
        }
    }

    void LinkedList::remove_at(size_t index)
    {
        //(19)
        // удаляет узел по индексу
        // исключения описанны и вызываются в функции node_at
        Node* node_ = (*this).node_at(index);
        LinkedList::erase(node_);
    }


    void LinkedList::insert_before(size_t index, const Data& value)
    {
        //(17) добавляет узел до выбранного  index с значением value
        Node* node_=new Node;
        int i=0;
//    найдем узел
        node_=(*this).node_at(index);
        Node* node_before=new Node;
        // проверяем не первый ли он
        if(node_==first)
        {
            node_before->previous=nullptr;
            node_before->value=value;
            node_before->next=node_;
            node_->previous=node_before;
            first=node_before;
        }
        else
        {
            node_before->value=value;
            node_before->previous=node_->previous;
            node_before->next=node_;
            //
            node_->previous=node_before;
            if(node_==first)
            {
                node_before->previous=nullptr;
                node_before->value=value;
                node_before->next=node_;
                node_->previous=node_before;
                first=node_before;
            }
            if(node_before->previous!=nullptr)
            {
                node_before->previous->next=node_before;
            }
        }

        ++size_;
    }
    void LinkedList::insert_after(size_t index, const Data& value)
    {
        // (18)добавляет узел после выбранного
        Node* node_=(*this).node_at(index);
        Node* node_after=new Node;
        node_after->value=value;
        //проверяем не последний ли это узел
        if(node_->next=nullptr)
        {
            node_after->next=nullptr;
            node_after->previous=node_;
            node_->next=node_after;
            last=node_after;
        }
        else
        {
            node_after->previous=node_;
            node_after->next=node_->next;
            node_->next=node_after;
            if(node_after->next!=nullptr)
            {
                node_after->next->previous=node_after;
            }
        }
        ++size_;
    }
    LinkedList::Node* LinkedList::node_at(size_t index)
    {
        //(16) возвращает узел по заданному индексу
        // аналогично value_at
        Node* node_ =first;
        int i=0;
        if(index>=size_)
            throw std::out_of_range("Index>size_");
        while(node_)
        {

            if(i==index)
            {
                return node_;
            }
            node_=node_->next;
            ++i;
        }
    }
    std::ostream& operator<<(std::ostream& output, const LinkedList& xs)
    {
        // (7) TODO оператор вывода связного списка должен выводить его как строку в виде [начальный узел, , , , , ,конечный узел]
        // пробелы обязательны!!
        LinkedList::Node* node_ = xs.first;
        output<<"[";
        while(node_!=xs.last)
        {
            output<<node_->value;
            output<<", ";
            node_=node_->next;
        }
        if(xs.last!=nullptr)
        {
            output<<xs.last->value;
        }
        output<<"]";
        return output;
    }
