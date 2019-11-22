#include "order_weights.cpp"
#include <gtest/gtest.h>

TEST(OrderWeightsTest, Test1) {
  EXPECT_EQ(orderWeight("180 9"), "180 9");
  EXPECT_EQ(orderWeight("103 123 4444 99 2000"), "2000 103 123 4444 99");
  EXPECT_EQ(orderWeight("2000 10003 1234000 44444444 9999 11 11 22 123"), "11 11 2000 10003 22 123 1234000 44444444 9999");
  EXPECT_EQ(orderWeight("3 16 9 38 95 1131268 49455 347464 59544965313 496636983114762 85246814996697"), "3 16 9 38 95 1131268 49455 347464 59544965313 496636983114762 85246814996697");
  EXPECT_EQ(orderWeight("387087 176 351832 100 430372 8 58052 54 175432 120 269974 147 309754 91 404858 67 271476 164 295747 111 40"), "100 111 120 40 8 54 91 164 147 67 176 430372 58052 175432 351832 271476 309754 404858 387087 295747 269974");
  EXPECT_EQ(orderWeight(""), "");
  EXPECT_EQ(orderWeight("136854 88407 348997 18118 82854 195333 145209 208812 147019 39631 427687 26012 371712 236513 378280 76962 471892 117155 255066 474241"), "26012 18118 117155 236513 145209 208812 371712 147019 39631 474241 195333 255066 136854 82854 88407 378280 76962 471892 427687 348997");
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
