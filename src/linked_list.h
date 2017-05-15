#ifndef __COLLECTIONS_LINKED_LIST__
#define __COLLECTIONS_LINKED_LIST__


#include <stdlib.h>
#include "entity.h"

typedef entity_t item_t;

/**
 * @brief Doubly linked list node.
 */
typedef struct list_node
{
    struct list_node *prev; /**< previous node        */
    struct list_node *next; /**< next node            */
    item_t       data; /**< item data            */
} list_node_t;


/**
 * @brief Doubly linked list.
 */
typedef struct llist
{
    list_node_t    *head;    /**< list's first node */
    list_node_t    *tail;    /**< list's last node  */
} list_t;


/**
 * @brief Initializes the list structure.
 *
 * The result of this operation is an empty list.
 *
 * @param list      pointer to the @c list structure
 */
void list_init(list_t *list);

/**
 * @brief Returns the number of elements stored in the list.
 *
 * @param list  pointer to the @c list structure
 *
 * @note If the @p list argument is @c NULL, returns @c 0U.
 */
size_t list_size(const list_t *list);


/**
 * @brief Predicate that tells wheter the @a list is empty or not.
 *
 * @param list  pointer to the @c list structure
 * @return @c true if the @a list is empty, @c false otherwise
 *
 * @note If the @p list argument is @c NULL, the function returns @c true.
 */
bool list_empty(const list_t *list);

/**
 * @brief Inserts a new element before the first element in the list.
 *
 * @param list  pointer to the @c list structure
 * @param data  entity to be stored
 * @return @c true if the operation was successful, @c false otherwise
 *
 * @note If any of @p list or @p data is @c NULL, the operation fails.
 */
bool list_push_front(list_t *list, item_t *data);

/**
 * @brief Inserts a new element after the last element in the list.
 *
 * @param list  pointer to the @c list structure
 * @param data  entity to be stored
 * @return @c true if the operation was successful, @c false otherwise
 *
 * @note If any of @p list or @p data is @c NULL, the operation fails.
 */
bool list_push_back(list_t *list, item_t *data);

/**
 * @brief Removes and returns the first element stored in the list.
 *
 * @param list  pointer to the @c list structure
 * @return a pointer from the first node or @c NULL if operation failed.
 *
 * @note If @p list is @c NULL or empty, the operation fails.
 */
item_t list_pop_back(list_t *list);

/**
 * @brief Removes and returns  the last element stored in the list.
 *
 * @param list  pointer to the @c list structure
 * @return a pointer from the last node or @c NULL if operation failed.
 *
 * @note If @p list is @c NULL or empty, the operation fails.
 */
item_t list_pop_front(list_t *list);


/**
 * @brief Inserts a new element at position specified by @p index from the head.
 *
 * The original element at the specified index will be moved after the new one.
 *
 * @param list  the list
 * @param index distance from list's head
 * @param data  pointer to store
 *
 * @note If @p index is @c listSize(&list), then the new element
 * will be appended after the tail.
 *
 * @return @c true if the operation was successful
 */
bool list_insert(list_t *list, size_t index, item_t *data);

/**
 * @brief Returns the element at the position @p index or @c NULL if no such element exists.
 *
 * @param list  the list
 * @param index distance from list's head
 * @return Element or @c NULL if not found.
 */
item_t list_get(list_t *list, size_t index);


/**
 * @brief Returns the element at the position @p index or @c NULL if no such element exists.
 *
 * @param list  the list
 * @param index distance from list's head
 * @param item  item that shall be inserted on spec. @p index
 * @return Element or @c NULL if not found.
 */
item_t list_set(list_t *list, size_t index, item_t item);


/**
 * @brief Returns the element at the position @p index or @c NULL if no such element exists.
 *
 * @param list  the list
 * @param index distance from list's head
 * @return Element or @c NULL if not found.
 */
list_node * list_get_node(list_t *list, size_t index);


/**
 * @brief Removes and returns the element at position @p index or @c NULL if no such element exists.
 *
 * @param list  the list
 * @param index distance from list's head
 * @return Element or @c NULL if not found.
 */
item_t list_remove(list_t *list, size_t index);




#endif // __COLLECTIONS_LINKED_LIST__