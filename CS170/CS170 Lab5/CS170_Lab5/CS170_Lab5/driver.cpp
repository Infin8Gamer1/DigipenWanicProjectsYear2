#include <iostream> // cout, endl

#include "Vector.h"

template <typename T>
void Print(const CS170::Vector<T>& array, bool newline = true)
{
  for (unsigned i = 0; i < array.size(); i++)
  {
    std::cout << array[i] << "  ";
  }

  std::cout << "(size=" << array.size() << ", capacity=" << 
                           array.capacity() << ", allocs=" << 
                           array.allocations() << ")";
  if (newline)
    std::cout << std::endl;
}

template <typename T>
void PrintPartial(const CS170::Vector<T>& array, bool newline = true)
{
  for (unsigned i = 1; i < array.size(); i *= 2)
  {
    std::cout << array[i - 1] << "  ";
  }

  std::cout << "(size=" << array.size() << ", capacity=" << 
                           array.capacity() << ", allocs=" << 
                           array.allocations() << ")";
  if (newline)
    std::cout << std::endl;
}

void TestSwap1(void)
{
  std::cout << "\n********** TestSwap1 **********\n";
  CS170::Vector<int> a, b, c;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(i + 1);
  for (int i = 0; i < 5; i++)
    b.push_back(10 * (i + 1));

  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);

  std::cout << "swapv a,b:\n";
  a.swapv(b);
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);

  std::cout << "swapv a,c:\n";
  a.swapv(c);
  std::cout << "a: ";
  Print(a);
  std::cout << "c: ";
  Print(c);

  std::cout << "swapv b,b:\n";
  b.swapv(b);
  std::cout << "b: ";
  Print(b);
}

void TestReverse1(void)
{
  int count = 10;
  std::cout << "\n********** TestReverse1 **********\n";
  CS170::Vector<int> a;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(i + 1);

  Print(a);
  a.reverse();
  std::cout << "Reversed:\n";
  Print(a);

  std::cout << "Remove last element:\n";
  a.pop_back();
  Print(a);
  a.reverse();
  std::cout << "Reversed:\n";
  Print(a);
}

void TestReverse2(void)
{
  int count = 10;
  std::cout << "\n********** TestReverse2 **********\n";
  CS170::Vector<int> a;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(i + 1);

  Print(a);
  a.reverse();
  std::cout << "Reversed:\n";
  Print(a);

  while (!a.empty())
  {
    if (a.size() % 2) // odd
    {
      std::cout << "Remove last element:\n";
      a.pop_back();
    }
    else // even
    {
      std::cout << "Remove first element:\n";
      a.pop_front();
    }
    Print(a);
    a.reverse();
    std::cout << "Reversed:\n";
    Print(a);
  }
}

void TestEqual1(void)
{
  std::cout << "\n********** TestEqual1 **********\n";
  CS170::Vector<int> a, b, c;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(i + 1);
  for (int i = 0; i < 10; i++)
    b.push_back(i + 1);

  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);

  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "remove last element of a:\n";
  a.pop_back();
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);
  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "remove last element of b:\n";
  b.pop_back();
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);
  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "change last element of b to 100:\n";
  b[b.size() - 1] = 100;
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);
  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";
}

void TestSubscriptEx(void)
{
  std::cout << "\n********** TestSubscriptEx **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  int size = sizeof(ia)/sizeof(*ia);
  std::cout << "Construct from int array:\n";

  const CS170::Vector<int> a(ia, size); // const
  CS170::Vector<int> b(ia, size);       // non-const
  Print(a);
  Print(b);

  try
  {
    int index = a.size() * 2; // illegal
    std::cout << "accessing subscript on const vector: a[" << index << "]" << std::endl;
    std::cout << "a[" << index << "] = " << a[index] << std::endl;
  }
  catch(const CS170::SubscriptError &se)
  {
    std::cout << "Bad subscript: " << se.GetSubscript() << std::endl;
  }

  try
  {
    int index = b.size() * 2; // illegal
    std::cout << "accessing subscript on non-const vector: b[" << index << "]" << std::endl;
    std::cout << "b[" << index << "] = " << b[index] << std::endl;
  }
  catch(const CS170::SubscriptError &se)
  {
    std::cout << "Bad subscript: " << se.GetSubscript() << std::endl;
  }

}

void TestInsertEx(void)
{
  std::cout << "\n********** TestInsertEx **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  int size = sizeof(ia)/sizeof(*ia);
  std::cout << "Construct from int array:\n";
  CS170::Vector<int> a(ia, size);
  Print(a);

  try
  {
    int index = a.size() * 3; // illegal
    std::cout << "insert integer at index " << index << ":\n";
    a.insert(99, index);
  }
  catch(const CS170::SubscriptError &se)
  {
    std::cout << "Bad subscript: " << se.GetSubscript() << std::endl;
  }
}

void TestSwapStress(void)
{
  std::cout << "\n********** TestSwapStress **********\n";
  CS170::Vector<int> a, b, c;

  int count = 1000000;

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
  {
    a.push_back(i);
    b.push_back(i * 2);
    c.push_back(i * 3);
  }

  std::cout << "Swapping...\n";
  CS170::Vector<int> x;
  for (int i = 0; i < 10000001; i++)
  {
    a.swapv(b);
    b.swapv(c);
    c.swapv(a);
  }

  PrintPartial(a);
  PrintPartial(b);
  PrintPartial(c);

  std::cout << "Done...\n";
}

void TestShrink1(void)
{
  std::cout << "\n********** TestShrink1 **********\n";
  CS170::Vector<int> a;

  std::cout << "push_back 8 integers:\n";
  for (int i = 0; i < 8; i++)
    a.push_back(i);
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "pop last 3:\n";
  a.pop_back();
  a.pop_back();
  a.pop_back();
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "push_back one integer:\n";
  a.push_back(100);
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "clear:\n";
  a.clear();
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);
}

int main(void)
{
  TestSwap1();
  TestReverse1();
  TestReverse2();
  TestEqual1();
  TestShrink1();

  TestSubscriptEx();
  TestInsertEx();

  TestSwapStress();

  return 0;
}
