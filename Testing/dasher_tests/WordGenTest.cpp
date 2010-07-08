#include "gtest/gtest.h"
#include "../../Src/DasherCore/FileWordGenerator.h"
using namespace Dasher;

class WordGenTest : public ::testing::Test {
  public:
    WordGenTest() {
      fullGen = new CFileWordGenerator("test_data/word_gen_full_data.txt");
      singleLineGen = new CFileWordGenerator("test_data/word_gen_single_line.txt");
    }
  
  protected:
    CFileWordGenerator* fullGen;
    CFileWordGenerator* singleLineGen;
};

/*
 * Tests whether the word fullGenerator opens a file
 * correctly.
 */
TEST_F(WordGenTest, FileOpensCorrectly) {
  bool opened = fullGen->GetFileHandle().is_open();
  bool good = fullGen->GetFileHandle().good();
  ASSERT_EQ(opened, true);
  ASSERT_EQ(good, true);
}

/*
 * Tests whether the file name getter returns expected results.
 */
TEST_F(WordGenTest, FilenameExtraction) {
  ASSERT_EQ("word_gen_full_data.txt", fullGen->GetFilename());
}

TEST_F(WordGenTest, WordIteration) {
  ASSERT_EQ("I'm", fullGen->GetNextWord());
  ASSERT_EQ("a", fullGen->GetNextWord());
}

TEST_F(WordGenTest, GetBuffer) {
  std::ifstream fin;
  std::string buffer;
  fin.open("test_data/word_gen_single_line.txt");
  std::getline(fin, buffer);
  
  ASSERT_EQ(buffer, singleLineGen->GetWholeBuffer());
}

TEST_F(WordGenTest, EndsAtEOF) {
  for(int i = 0; i < 1000; i++)
    singleLineGen->GetNextWord();
    
  ASSERT_EQ("", singleLineGen->GetNextWord());
}

