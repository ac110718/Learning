#include <cstdio>

struct Element {
    Element(char a, char b, short x) {
        prefix[0] = a;
        prefix[1] = b;
        operating_number = x;
    }
    Element* next;
    Element* previous;
    void insert_after(Element* new_element) {
        new_element->next = this->next;
        this->next = new_element;
    }
    void insert_before(Element* new_element) {
        this->previous = new_element;
    }
    char prefix[2];
    short operating_number;
};

int main() {
    Element trooper1 ('T', 'K', 421);
    Element trooper2 ('F', 'N', 2187);
    Element trooper3 ('L', 'S', 5);
    trooper1.insert_after(&trooper2);
    trooper2.insert_after(&trooper3);
    trooper2.insert_before(&trooper1);
    trooper3.insert_before(&trooper2);

    for (Element *cursor = &trooper1; cursor; cursor = cursor->next) {
        printf("stormtrooper %c%c-%d\n", 
            cursor->prefix[0],
            cursor->prefix[1],
            cursor->operating_number);
    }

    printf("\nBACKWARDS\n");

    for (Element *cursor = &trooper3; cursor; cursor = cursor->previous) {
        printf("stormtrooper %c%c-%d\n", 
            cursor->prefix[0],
            cursor->prefix[1],
            cursor->operating_number);
    }
}