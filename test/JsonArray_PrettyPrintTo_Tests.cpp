// Copyright Benoit Blanchon 2014
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson/JsonArray.hpp>
#include <ArduinoJson/JsonObject.hpp>
#include <ArduinoJson/JsonValue.hpp>
#include <ArduinoJson/StaticJsonBuffer.hpp>

using namespace ArduinoJson;

class JsonArray_PrettyPrintTo_Tests : public testing::Test {
 protected:
  JsonArray array;
  StaticJsonBuffer<30> json;

  virtual void SetUp() { array = json.createArray(); }

  void outputMustBe(const char *expected) {
    size_t n = array.prettyPrintTo(buffer, sizeof(buffer));
    EXPECT_STREQ(expected, buffer);
    EXPECT_EQ(strlen(expected), n);
  }

 private:
  char buffer[256];
};

TEST_F(JsonArray_PrettyPrintTo_Tests, Empty) { outputMustBe("[]"); }

TEST_F(JsonArray_PrettyPrintTo_Tests, OneElement) {
  array.add(1);

  outputMustBe(
      "[\r\n"
      "  1\r\n"
      "]");
}

TEST_F(JsonArray_PrettyPrintTo_Tests, TwoElements) {
  array.add(1);
  array.add(2);

  outputMustBe(
      "[\r\n"
      "  1,\r\n"
      "  2\r\n"
      "]");
}

TEST_F(JsonArray_PrettyPrintTo_Tests, EmptyNestedArrays) {
  array.createNestedArray();
  array.createNestedArray();

  outputMustBe(
      "[\r\n"
      "  [],\r\n"
      "  []\r\n"
      "]");
}

TEST_F(JsonArray_PrettyPrintTo_Tests, NestedArrays) {
  JsonArray nested1 = array.createNestedArray();
  nested1.add(1);
  nested1.add(2);

  JsonObject nested2 = array.createNestedObject();
  nested2["key"] = 3;

  outputMustBe(
      "[\r\n"
      "  [\r\n"
      "    1,\r\n"
      "    2\r\n"
      "  ],\r\n"
      "  {\r\n"
      "    \"key\": 3\r\n"
      "  }\r\n"
      "]");
}