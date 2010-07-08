#ifndef __FileWordGenerator_h__
#define __FileWordGenerator_h__

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#include "WordGeneratorBase.h"
#include "DasherInterfaceBase.h"

namespace Dasher {
  
  
/**
 * This class implements the Word Generator interface. This means
 * that after construction, your primary method of retrieving words
 * will be calling GetNextWord(). For specifics on Word Generators,
 * see CWordGeneratorBase.
 * 
 * This class specifically reads words from a given file. Files ARE
 * kept open for the lifetime of this object and the size of the file
 * should not pose an issue. 
 * 
 * However, if you read in a file that has unreasonably long lines,
 * the behavior is undefined as you may cause the file to be read in all
 * at once. 
 */
class CFileWordGenerator : public CWordGeneratorBase {
public:
  CFileWordGenerator(std::string sPath, int iRegen) 
    : m_sPath(sPath),
      m_sCurrentWord(""),
      CWordGeneratorBase(iRegen)
      {Generate();}
  CFileWordGenerator(std::string sPath)
    : m_sPath(sPath),
      m_sCurrentWord(""),
      CWordGeneratorBase(0)
      {Generate();}
      
  virtual ~CFileWordGenerator() {
    m_sFileHandle.close();
  }
  
  
  /**
   * The generator function. In this implementation, it reads from a 
   * file to produce strings.In this implementation, failure means file 
   * io has failed for some reason.
   * @see CWordGeneratorBase::Generate
   */
  virtual bool Generate();

  /**
   * Returns the next word that was read
   * @return The next word in the word generator model if there is one.
   *          Otherwise, returns an empty string.
   */
  virtual std::string GetNextWord();


  /**
   * File path getter
   * @return The path to the file this generator reads from.
   */
  std::string GetPath();

  /**
   * File name getter. Returns the file name and extension, without
   * any slashes.
   * @return The actual name of the file being read from
   */
  std::string GetFilename();
  
  
  std::ifstream& GetFileHandle() { return m_sFileHandle; }
  std::string GetWholeBuffer() { return m_sGeneratedString; }
  size_t GetStringPosition() { return m_uiPos; }

private:
/* ---------------------------------------------------------------------
 * Private Methods
 * ---------------------------------------------------------------------
 */

  /**
   * Find the next word in the generated string buffer.
   * This does NOT return that string, which is why this is not a public
   * facing method. It only updates the current string to be presented.
   * 
   * @warning Ensure that this is called whenever m_sGeneratedString is
   *          remade or whenever the current word is actually presented
   *          to a client.
   */
  void FindNextWord();


/* ---------------------------------------------------------------------
 * Member Variables
 * ---------------------------------------------------------------------
 */

  /**
   * The current word we're looking at. This is the next word that
   * will be returned when GetNextWord is called.
   */
  std::string m_sCurrentWord;

  /**
   * The string that has been generated.
   */
  std::string m_sGeneratedString;

  /**
   * The path to the file this generator reads from.
   */
  std::string m_sPath;

  /**
   * The position we're currently reading from in the string.
   */
  size_t m_uiPos;
  
  /**
   * Flag for whether there are words left in this model.
   */
  bool m_bWordsLeft;
  
  /**
   * The input stream that acts as the handle to the underlying file.
   */
  ifstream m_sFileHandle;
};
}

#endif
