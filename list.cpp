
#include <string.h>
#include <stdlib.h>

class list
{
public:
	list(size_t item_size, bool iscircle = false);
	~list();
	void *next();
	void *getitem();
	int setitem(void *item);
	int insert(void *item);
	int gotoitem(void *item, int (*compare)(void *orig, void *chk));
private:
	struct list_elem
	{
		struct list_elem *next;
		void *item;
	} *front, *current;
	size_t item_size;
	bool circular;
};

list::list(size_t item_size, bool iscircle)
{
	front = current = (list::list_elem*)malloc(sizeof(list::list_elem));
	memset(front, 0, sizeof(list::list_elem));
}

list::~list()
{
	current = front->next;
	while(current)
		{
			free(front->item);
			free(front);
			front = current;
			current = current->next;
		}
	free(front);
}

void *list::next()
{
	if(current)
		{
			current = current->next;
			if(!current && circular)
				current = front;
		}
	return (current ? current->item : NULL);
}

int list::setitem(void *item)
{
	if(!current->item)
		current->item = malloc(item_size);
	memcpy(current->item, item, item_size);
	return 1;
}

void *list::getitem()
{
	return (current ? current->item : NULL);
}

int list::insert(void *item)
{
	list::list_elem *next = current->next;
	current->next = (list::list_elem*)malloc(sizeof(list::list_elem));
	current = current->next;
	current->next = next;
	return setitem(item);
}

int list::gotoitem(void *item, int (*compare)(void *orig, void *chk))
{
	list::list_elem *finder = current;
	for(next();
		!compare(item, current->item) && current != finder;
		next())
		{
			if(current == NULL)
				{
					current = front;
					if(!compare(item, current->item))
						break;
				}
		}
	return compare(item, current->item);
}

int main(void)
{
	list *test = new list(13);
	delete test;
	return 0;
}
