#include "../../Src/DasherCore/FileWordGenerator.h"
#include "../gtest/gtest.h"

namespace {

class WordGenTest : public ::testing::Test {
	WordGenTest() {
		gen = CFileWordGenerator("file_word_testdata.txt", 0);
	}


	CFileWordGenerator gen;
};

TEST_F(WordGenTest, GeneratesWordsCorrectly) {
	EXPECT_EQ(gen.GetNextWord(), "Today,");
}

}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
