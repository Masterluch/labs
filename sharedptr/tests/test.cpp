// Copyright 2021 Masterluch <atim2203@gmail.com>

#include <gtest/gtest.h>

#include <SharedPtr.hpp>

TEST(Example, EmptyTest) { EXPECT_TRUE(true); }

TEST(Constructor, constructor_with_default_ptr) {
  int* ptr_num = new int;
  *ptr_num = 17;
  SharedPtr<int> ptr(ptr_num);

  ASSERT_TRUE(*ptr == 17);
}

TEST(Constructor, constructor_with_sharedptr) {
  int* ptr_num = new int;
  *ptr_num = 17;
  SharedPtr<int> ptr(ptr_num);
  SharedPtr<int> ptr1(ptr);

  ASSERT_TRUE(*ptr1 == 17);
}

TEST(Operator, operator_equal_and_star) {
  int* ptr_num = new int;
  *ptr_num = 17;
  SharedPtr<int> ptr(ptr_num);

  SharedPtr<int> ptr1;
  ptr1 = ptr;

  ASSERT_TRUE((*ptr1 == 17) and (ptr1.use_count() == 2));
}

TEST(Operator, operator_arrow) {
  class A {
   private:
    int _a;

   public:
    A(int a) : _a(a) {}
    int get_a() const { return _a; }
  };

  A* ptr_a = new A(19);
  SharedPtr<A> ptr(ptr_a);

  int result = ptr->get_a();
  ASSERT_TRUE(result == 19);
}

TEST(Method, get_method) {
  int* ptr_num = new int;
  *ptr_num = 17;
  SharedPtr<int> ptr(ptr_num);

  ASSERT_TRUE(ptr.get() == ptr_num);
}

TEST(Method, reset_empty_method) {
  int* ptr_num = new int;
  *ptr_num = 17;
  SharedPtr<int> ptr(ptr_num);
  ptr.reset();

  ASSERT_TRUE((ptr.get() == nullptr) and (ptr.use_count() == 1));
}

TEST(Method, reset_with_default_ptr_method) {
  int* ptr_num = new int;
  *ptr_num = 17;
  SharedPtr<int> ptr(ptr_num);
  int* ptr_num1 = new int;
  *ptr_num1 = 15;
  ptr.reset(ptr_num1);

  ASSERT_TRUE((*ptr == 15) and (ptr.use_count() == 1));
}

TEST(Method, swap_method) {
  int* ptr_num = new int;
  *ptr_num = 17;
  int* ptr_num1 = new int;
  *ptr_num1 = 9;
  SharedPtr<int> ptr(ptr_num);
  SharedPtr<int> ptr1(ptr_num1);
  ptr.swap(ptr1);

  ASSERT_TRUE((*ptr == 9) and (*ptr1 == 17) and (ptr.use_count() == 1) and
              (ptr1.use_count() == 1));
}

TEST(Method, use_count_method) {
  int* ptr_num = new int;
  *ptr_num = 17;
  SharedPtr<int> ptr(ptr_num);
  SharedPtr<int> ptr1(ptr);

  ASSERT_TRUE(ptr.use_count() == 2);
}
