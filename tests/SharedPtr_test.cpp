// Copyright 2020 MIX-1 <danilonil1@yandex.ru>

#include <gtest/gtest.h>
#include <SharedPtr.hpp>

TEST(Example, EmptyTest) {
  EXPECT_TRUE(true);
}

TEST(EmptyConstructer, Nullptr) {
  SharedPtr<int> test;
  EXPECT_EQ(test.get(), nullptr);
  EXPECT_EQ(test.use_count(), 0);
  EXPECT_FALSE(test);
}

TEST(Constructers, Constructers_value) {
  int val = 18;

  SharedPtr<int> sharedPtr1(&val);
  SharedPtr<int> sharedPtr2(sharedPtr1);

  EXPECT_EQ(*sharedPtr1, 18);
  EXPECT_EQ(*sharedPtr2, 18);
  EXPECT_EQ(sharedPtr1.get(), &val);
  EXPECT_EQ(sharedPtr2.get(), &val);
  EXPECT_EQ(sharedPtr1.use_count(), 2);
  EXPECT_EQ(sharedPtr2.use_count(), 2);
  EXPECT_TRUE(sharedPtr1);
  EXPECT_TRUE(sharedPtr2);
}

TEST(Constructers, Constructers_struct) {
  struct Values {
    int val;
  };
  Values val1 = {18};
  SharedPtr<Values> sharedPtr1(&val1);
  SharedPtr<Values> sharedPtr2(sharedPtr1);

  EXPECT_EQ(sharedPtr1->val, 18);
  EXPECT_EQ(sharedPtr2->val, 18);
  EXPECT_EQ(sharedPtr1.get(), &val1);
  EXPECT_EQ(sharedPtr2.get(), &val1);
  EXPECT_EQ(sharedPtr1.use_count(), 2);
  EXPECT_EQ(sharedPtr2.use_count(), 2);
  EXPECT_TRUE(sharedPtr1);
  EXPECT_TRUE(sharedPtr2);
}

TEST(Constructers, Constructers_class) {
  class Values {
   public:
    int val;
  };
  Values val1;
  val1.val = 18;
  SharedPtr<Values> sharedPtr1(&val1);
  SharedPtr<Values> sharedPtr2(sharedPtr1);

  EXPECT_EQ(sharedPtr1->val, 18);
  EXPECT_EQ(sharedPtr2->val, 18);
  EXPECT_EQ(sharedPtr1.get(), &val1);
  EXPECT_EQ(sharedPtr2.get(), &val1);
  EXPECT_EQ(sharedPtr1.use_count(), 2);
  EXPECT_EQ(sharedPtr2.use_count(), 2);
  EXPECT_TRUE(sharedPtr1);
  EXPECT_TRUE(sharedPtr2);
}

TEST(Constructers, Constructers_vector) {
  std::vector<int> val1 = {1, 18, 17};
  SharedPtr<std::vector<int>> sharedPtr1(&val1);
  SharedPtr<std::vector<int>> sharedPtr2(sharedPtr1);

  std::vector<int> val_v = {{1, 18, 17}};

  EXPECT_EQ(*sharedPtr1, val_v);
  EXPECT_EQ(*sharedPtr2, val_v);
  EXPECT_EQ(sharedPtr1.get(), &val1);
  EXPECT_EQ(sharedPtr2.get(), &val1);
  EXPECT_EQ(sharedPtr1.use_count(), 2);
  EXPECT_EQ(sharedPtr2.use_count(), 2);
  EXPECT_TRUE(sharedPtr1);
  EXPECT_TRUE(sharedPtr2);
}

TEST(Accessory_methods, Get) {
  int val = 18;

  SharedPtr<int> sharedPtr1(&val);
  SharedPtr<int> sharedPtr2(sharedPtr1);

  EXPECT_EQ(sharedPtr1.get(), &val);
  EXPECT_EQ(sharedPtr2.get(), &val);
}

TEST(Accessory_methods, Count) {
  int val = 18;

  SharedPtr<int> sharedPtr1(&val);
  SharedPtr<int> sharedPtr2(sharedPtr1);
  SharedPtr<int> sharedPtr3(sharedPtr2);

  EXPECT_EQ(sharedPtr1.use_count(), 3);
  EXPECT_EQ(sharedPtr2.use_count(), 3);
  EXPECT_EQ(sharedPtr3.use_count(), 3);
}

TEST(Accessory_methods, Bool) {
int val = 18;

SharedPtr<int> sharedPtr1(&val);
SharedPtr<int> sharedPtr2(sharedPtr1);

  EXPECT_TRUE(sharedPtr1);
  EXPECT_TRUE(sharedPtr2);
  EXPECT_FALSE(!sharedPtr1);
  EXPECT_FALSE(!sharedPtr2);
}

TEST(Accessory_methods, Swap) {
  int val1 = 18;

  SharedPtr<int> sharedPtr1(&val1);
  SharedPtr<int> sharedPtr2(sharedPtr1);
  EXPECT_EQ(sharedPtr2.use_count(), 2);
  EXPECT_EQ(sharedPtr2.get(), &val1);
  EXPECT_EQ(*sharedPtr2, 18);
  EXPECT_TRUE(sharedPtr2);

  int val2 = 8;

  SharedPtr<int> sharedPtr3(&val2);
  SharedPtr<int> sharedPtr4(sharedPtr3);
  SharedPtr<int> sharedPtr5(sharedPtr4);
  EXPECT_EQ(sharedPtr5.use_count(), 3);
  EXPECT_EQ(sharedPtr5.get(), &val2);
  EXPECT_EQ(*sharedPtr5, 8);
  EXPECT_TRUE(sharedPtr5);

  sharedPtr5.swap(sharedPtr2);
  EXPECT_EQ(sharedPtr2.use_count(), 3);
  EXPECT_EQ(sharedPtr5.use_count(), 2);
  EXPECT_EQ(sharedPtr2.get(), &val2);
  EXPECT_EQ(sharedPtr5.get(), &val1);
  EXPECT_EQ(*sharedPtr2, 8);
  EXPECT_EQ(*sharedPtr5, 18);
  EXPECT_TRUE(sharedPtr2);
  EXPECT_TRUE(sharedPtr5);
}
