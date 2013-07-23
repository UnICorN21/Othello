#ifndef TOOLS_H
#define TOOLS_H

/**
  * Tools class.
  **/
class Tools {
public:
    /**
    * Delete all pieces of the list, except the list itself.
    * \param list A pointer to the list to delete.
    **/
    template<class T>
    static void deleteList(std::list<T *> * list) {
        if(list != NULL) {
            while(!list->empty()) {
                T * elt = list->front();
                delete elt;
                list->pop_front();
            }
        }
    }
};

#endif // TOOLS_H
