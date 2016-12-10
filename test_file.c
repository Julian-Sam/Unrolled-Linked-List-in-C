// In this example file, we will define an elem as int.
// Change this line to what type you want elem to be. You can also put this
// line in the unrolled-list.h file.
typedef int elem;

#include "unrolled-list.c"



// Required client function for comparision and equality checks for elements.
bool unrolled_equality(elem elem1, elem elem2)
{
  if (elem1 == elem2)
    return true;
  else
    return false;
}

// Optional client function for printing elements of the list.
void printFunction(elem e)
{
  printf("%d\n", e);
}

int main()
{

  // Make new list. Each node has 3 elements size limit. Also pass in the
  // Equality function to compare the elements of type elem.
  ull* new = new_unrolled(3, &unrolled_equality);


  insert_unrolled(1, new);
  insert_unrolled(2, new);

  // Print function.
  // Pass in a list and a print function that prints elements of type elem.
  printList(new, &printFunction);

  delete_unrolled(2,new);
  delete_unrolled(1,new);


  insert_unrolled(3, new);
  insert_unrolled(4, new);
  printList(new, &printFunction);

  delete_unrolled(3,new);
  delete_unrolled(4,new);

  printList(new, &printFunction);

  // Free the list
  free_unrolled(new);
  return 0;
}
