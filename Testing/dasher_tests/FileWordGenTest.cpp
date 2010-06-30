#include "gtest/gtest.h"   
#include "FileWordGenerator.h"
using namespace Dasher;

class FileWordGenTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    gen = new CFileWordGenerator("TestData/file_loader_test_data.txt");
  }
  
  CFileWordGenerator* gen;
};


TEST_F(FileWordGenTest, OpensFileCorrectly) {
  ASSERT_TRUE(gen->GetFileHandle().is_open());
}
