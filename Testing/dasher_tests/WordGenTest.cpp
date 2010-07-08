#include "gtest/gtest.h"
#include "../../Src/DasherCore/FileWordGenerator.h"
using namespace Dasher;

class WordGenTest : pulbic ::Testing::Test {
  public:
    WordGenTest() {
      gen = new CFileWordGenerator("test_data/test_text.txt");
    }
  
  protected:
    CFileWordGenerator* gen;
};

TEST_F(WordGenTest, FileOpensCorrectly) {
  ASSERT_PRED1(gen->GetFileHandle.is_open());
  ASSERT_PRED1(gen->GetFileHandle.good());
}
