#ifndef __WordGeneratorBase_h__
#define __WordGeneratorBase_h__

#include <string>
using namespace std;

namespace Dasher {
/**
 * The base class for all word generators. Word generators encapsulate
 * logic for simply generating words based on implementation-specific
 * conditions. The benefit of this is that a generator can
 * easily be written that selects words based on a function of the current
 * value of the Sri Lankan rupee and the amount of twitter feeds regarding
 * the winter olympics, for example.
 * 
 * 
 * A typical use case for any class deriving from CWordGeneratorBase
 * would be the following:
 *    1) Construct the object (providing any implementation-specific params)
 *  * 
 *    2) To retrieve a word, simply call GetNextWord. This will continue
 *       until the specific implementation determines that there are no
 *       more words for any reason. When there are no more, GetNextWord
 *       returns the empty string.
 * 
 * Usage Example:
 *    CWordGeneratorBase gen = CWordGeneratorBase(params...);
 *    std::string word;
 *    while ((word = gen.GetNextWord()) != "") {
 *         Operate on the word
 *    }
 */ 
class CWordGeneratorBase {
public:
  CWordGeneratorBase(int regen) : m_iRegenTime(regen), m_bWordsReady(false) 
  {}
  
  CWordGeneratorBase() : m_iRegenTime(0), m_bWordsReady(false)
  {}

  virtual ~CWordGeneratorBase() { } 


  /**
   * Gets a single word based on the generation rules.
   * @pre { Generate must have been called at least once. }
   * @return The next string from this generator
   */
  virtual std::string GetNextWord() = 0;

  /**
   * -- NOT YET IMPLEMENTED --
   * Gets the previous word in the generated string based on generation rules.
   * @pre { Generate must have been called at least once. }
   * @return The previous string from this generator
   */
  //virtual std::string GetPreviousWord() = 0;
  
protected:

  /**
   * The time in seconds after which a generator should regenerate.
   */
  int m_iRegenTime;

  /** 
   * A boolean representing whether the words have been generated yet.
   */
  bool m_bWordsReady;
};
}
#endif
