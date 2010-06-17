#include <string>
#include <iostream.h>
#include <fstream.h>
using namespace std;

#include "WordGeneratorBase.h"

namespace Dasher {
class CFileWordGenerator : public CWordGeneratorBase {
public:
	CFileWordGenerator(std::string path, int regen) : CWordGeneratorBase(regen) {
	}
	/**
     * The generator function. In this implementation, it reads from a file to produce strings.
     * @see CWordGeneratorBase::Generate
     */
    virtual bool Generate();

	/**
     * Returns the next word that was read
	 */
	virtual std::string GetNextWord();


	/**
     * File path getter
     * @return The path to the file this generator reads from.
     */
	std::string GetPath();

	/**
     * File name getter
	 * @return The actual name of the file being read from
     */
	std::string GetFilename();
	
	/**
     * Sets the source file this generator reads from.
     * @warning This method regenerates the model and gets rid of the old data.
	 * @param newPath The path to the file to load from.
	 */
	void SetSource(std::string newPath);
prviate:
	/**
     * The string that has been generated.
     */
	std::string m_sGeneratedString

	/**
     * The path to the file this generator reads from.
     */
	std::string m_sPath;

	/**
     * The position we're currently reading from in the string.
	 */
	size_t m_uiPos;
};
}
